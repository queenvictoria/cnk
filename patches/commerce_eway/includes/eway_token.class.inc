<?php

class eway_token extends eway_base {

  function __construct($settings) {
    parent::__construct($settings);
    // Currently a testing URL for the beagle mode does not exist.
    // When one does, add the URL as per the options above.
    $this->url = ($this->testing) ? 'https://www.eway.com.au/gateway/ManagedPaymentService/test/managedCreditCardPayment.asmx?WSDL' : 'https://www.eway.com.au/gateway/ManagedPaymentService/managedCreditCardPayment.asmx?WSDL';
  }

  protected function prepare_request ($settings, $description, $charge, $credit_card, $address, $order_id, $uid, $mail) {
    $ManagedCustomerId = db_query ('select eway_id from {commerce_eway_token} where uid = :uid', array (':uid' => $uid))->fetchField();
    if (!$ManagedCustomerId) {
      $this->ManagedCustomerId = 0;
      // If user is logged in, we can register details.
      // Else user will only be created much later, so we cannot use
      // token billing at this time.
      $success = $this->new_managed_customer ($settings, $credit_card, $address, $uid, $mail);
    }
    else
      $this->ManagedCustomerId = $ManagedCustomerId;

    if ($this->ManagedCustomerId) {
      unset ($this->cvn_processor);
      $this->xml_data = array(
        'managedCustomerID' => $this->testing ? COMMERCE_PAYMENT_EWAY_TOKEN_TEST_CUSTOMER_ID : $this->ManagedCustomerId,
        'amount' => intval($charge['amount']),
        'invoiceReference' => $order_id,
        'invoiceDescription' => $description,
      );
    }
    else {
      module_load_include ('class.inc', 'commerce_payment_eway', 'includes/eway_cvn_xml');
      $this->cvn_processor = new eway_cvn_xml ($settings);
      $this->cvn_processor->prepare_request ($settings, $description, $charge, $credit_card, $address, $order_id, $uid, $mail);
    }
  }

  /*
   * Pay via the CVN processor, or use token billing if setup.
   * Call process_payment if you are sure the person has been setup
   * for token billing.
   */
  protected function process_request () {
    if (isset ($this->cvn_processor)) {
      // If cvn processor set, we could not register customer details,
      // so use "traditional" processing.
      $this->cvn_processor->process_request();
      $response = $this->cvn_processor->return_info['eway_response'];
    }
    else {
      if ($this->ManagedCustomerId)
        $response = $this->soap_call('ProcessPayment', $this->xml_data);
      else
        $response = $this->last_response;
    }
    $this->return_info = array(
      'eway_response' => $response,
    );
  }

  /*
   * Store customer data on eWAY server
   */
  protected function new_managed_customer ($settings, $credit_card, $address, $CustomerRef, $mail) {
    // We must supply a first and last name, else call will fail
    $first_name = $address['first_name']? $address['first_name'] : substr ($address['name_line'], 0, strpos ($address['name_line'], ' '));
    if (!$first_name)
      $first_name = $address['name_line'];
    $last_name = $address['last_name']? $address['last_name'] : substr ($address['name_line'], strpos ($address['name_line'], ' ') + 1);
    if (!$last_name)
      $last_name = $address['name_line'];
    $this->xml_data = array(
      'Title' => 'Prof.', // TODO: Don't hard code this when there is a better way.
      'FirstName' => $first_name,
      'LastName' => $last_name,
      'Address' => $address['thoroughfare'],
      'Suburb' => $address['locality'],
      'State' => $address['locality'],
      'Company' => '',
      'PostCode' => $address['postal_code'],
      'Country' => strtolower($address['country']),
      'CustomerRef' => $CustomerRef,
      'Email' => $mail,
      'Fax' => '',
      'Phone' => '',
      'Mobile' => '',
      'JobDesc' => '',
      'Comments' => '',
      'URL' => '',
      'CCNumber' => _commerce_payment_eway_get_data('cc_number', $settings, $credit_card['number']),
      'CCNameOnCard' => $address['name_line'],
      'CCExpiryMonth' => sprintf('%02d', $credit_card['exp_month']),
      'CCExpiryYear' => substr($credit_card['exp_year'], -2),
    );

    if ($CustomerRef) {
      $this->create_customer ($this->xml_data['CustomerRef'], $this->xml_data);
      $response = $this->last_response;
    }

    if (!$CustomerRef || !$response['txStatus']) {
      $this->unsaved_customer_data = $this->xml_data;
      $response['txStatus'] = true;
    }

    $this->last_response = $response;

    return $response['txStatus'];
  }

  /*
   * If user is not registered, we can only store token until user has
   * been registered. We keep track of the request, and once user has
   * been registered, this function can be used to actually save user
   * data.
   */
  function create_customer ($CustomerRef, $customer_data) {
    $customer_data['CustomerRef'] = $this->testing ? COMMERCE_PAYMENT_EWAY_TOKEN_TEST_CUSTOMER_REF : $CustomerRef;
    $response = $this->soap_call('CreateCustomer', $customer_data);

    if ($response['txStatus']) {
      $this->ManagedCustomerId = $response['CreateCustomerResult'];
      db_insert ('commerce_eway_token')->fields (array ('uid' => $CustomerRef, 'eway_id' => $this->ManagedCustomerId))->execute();
      $this->unsaved_customer_data = false;
      if ($this->log_to_watchdog) {
        watchdog('commerce_payment_eway', 'User %uid setup for token billing', array('%uid' => $CustomerRef));
      }
    }

    $this->last_response = $response;
    return $response['txStatus'];
  }

  /*
   * Get the stored user data from eWay 
   */
  function query_customer ($managedCustomerID) {
    $customer_data['managedCustomerID'] = $this->testing ? COMMERCE_PAYMENT_EWAY_TOKEN_TEST_CUSTOMER_ID : $managedCustomerID;
    $response = $this->soap_call('QueryCustomer', $customer_data);
    $this->last_response = $response;
    if ($response['txStatus']) {
      if ($this->log_to_watchdog) {
        watchdog('commerce_payment_eway', 'User %uid token data retrieved', array('%uid' => $response['QueryCustomerResult']['CustomerRef']));
      }
      $this->last_response = $response;
      return $response['QueryCustomerResult'];
    } else {
	  return $response['txReturnDescription'];
	}
  }

/* 
 * Merge existing results with incoming details from the update form.
 * Update eWay.
 * Return result.
 * @todo add watchdog logging
 */
  function update_customer ($managedCustomerID, $customer_data) {
    $customer_data['managedCustomerID'] = $this->testing ? COMMERCE_PAYMENT_EWAY_TOKEN_TEST_CUSTOMER_ID : $managedCustomerID;
//	get the existing data ( can we cache this ? )
	$existing_data = $this->query_customer($customer_data['managedCustomerID']);
	$customer_data = array_merge($existing_data, $customer_data);
    $response = $this->soap_call('UpdateCustomer', $customer_data);
    $this->last_response = $response;

    if ($response['txStatus'] == 'true' ) {
      if ($this->log_to_watchdog) {
//        watchdog('commerce_payment_eway', 'User %uid token data updated', array('%uid' => $response['QueryCustomerResult']['CustomerRef']));
      }
      return TRUE;
    } else {
	  return $response['txReturnDescription'];
	}

  }

/* 
 * @todo remove customer data from eway
	Delete eWay.
	Delete row from our table
	Return result.
*/
  function delete_customer ($managedCustomerID, $uid) {
    $customer_data['managedCustomerID'] = $this->testing ? COMMERCE_PAYMENT_EWAY_TOKEN_TEST_CUSTOMER_ID : $managedCustomerID;

	if ( $uid ) {
    	$ManagedCustomerId = db_query('DELETE FROM {commerce_eway_token} where uid = :uid', array (':uid' => $uid));
	} else {
    	$ManagedCustomerId = db_query('DELETE FROM {commerce_eway_token} where token = :token', array (':token' => $managedCustomerID));		
	}

//	is there a method for this? waiting to hear from eway
//    $response = $this->soap_call('UpdateCustomer', $customer_data);
//    $this->last_response = $response;
	return TRUE;

    if ($response['txStatus'] == 'true' ) {
      if ($this->log_to_watchdog) {
//        watchdog('commerce_payment_eway', 'User %uid token data updated', array('%uid' => $response['QueryCustomerResult']['CustomerRef']));
      }
      return TRUE;
    } else {
	  return $response['txReturnDescription'];
	}
  }

  /*
   * Token billing.
   */
  function process_payment ($ManagedCustomerId, $amount, $invoice_reference, $description) {
    $this->xml_data = array(
      'managedCustomerID' => $this->testing ? COMMERCE_PAYMENT_EWAY_TOKEN_TEST_CUSTOMER_ID : $this->ManagedCustomerId,
      'amount' => intval($amount),
      'invoiceReference' => $invoice_reference,
      'invoiceDescription' => $description,
      );
    $response = $this->soap_call('ProcessPayment', $this->xml_data);
    $this->return_info = array(
      'eway_response' => $response,
    );
  }

  /**
   * The actual SOAP call using the NuSOAP library.
   */
  protected function soap_call($operation, $params) {
    $namespace = 'https://www.eway.com.au/gateway/managedpayment';
    $endpoint = $this->url;

    $header = '<eWAYHeader xmlns="' . $namespace . '">
      <eWAYCustomerID>' . $this->customer_id . '</eWAYCustomerID>
      <Username>' . $this->user_name  . '</Username>
      <Password>' . $this->password  . '</Password>
      </eWAYHeader>'; // TODO: replace with soapval

    if (@include_once(_commerce_payment_eway_nusoap_path())) {
      $client = new nusoap_client($endpoint, TRUE);
      $client->response_timeout = 50;
      $result = $client->call($operation, $params, $namespace, '', $header);
    }
    else {
      $result = FALSE;
    }

    foreach ($params as $id => $key) {
      if (in_array($id, array('CCNumber'))) {
        // Don't log the CC number in plan text!
        $params[$id] = '**** **** **** ' . substr ($params[$id], -4);
      }
    }
    // Add a message to watchdog logs if in test mode to inform users of the
    // unusual rounding of the amount values.
    $test_mode_msg = $this->testing ? t('NOTE: The eWAY module is in test mode. In test mode the amount value will be rounded down to the nearest dollar, which will be zero for values less than 1 dollar.') : '';
    if ($this->log_to_watchdog) {
      watchdog('commerce_payment_eway', 'SOAP Call (%operation) request: %request, response: %response @test_mode_msg', array('%operation' => $operation, '%request' => var_export($params, TRUE), '%response' => var_export($result, TRUE), '@test_mode_msg' => $test_mode_msg));
    }

    if (!$result) {
      $response = false;
    }
    elseif (isset ($result['faultcode'])) {
      $response = array (
        'txStatus' => 'false',
        'txReturnNo' => (string) $result['faultcode'],
        'txReturnDescription' => (string) $result['faultstring'],
      );
    }
    elseif (isset ($result['ewayResponse'])) {
      $response = array (
        'txStatus' => 'true',
        'txReturnNo' => 0,
        'txReturnDescription' => (string) $result['ewayResponse']['ewayTrxnError'],
        'txTransactionNumber' => (string) $result['ewayResponse']['ewayTrxnNumber'],
      );
    }
    else {
      $response = $result + array (
        'txStatus' => 'true',
        'txReturnNo' => 0,
        'txReturnDescription' => '',
        'txTransactionNumber' => '',
      );
    }
    return $response;
  }

}

