<?php

class eway_beagle extends eway_xml_common {

   function __construct($settings) {
      // Currently a testing URL for the beagle mode does not exist.
      // When one does, add the URL as per the options above.
     parent::__construct($settings);
     $this->url = 'https://www.eway.com.au/gateway_cvn/xmlbeagle.asp';
   }

   function prepare_request ($settings, $description, $charge, $credit_card, $address, $order_id, $uid, $mail) {
     parent::prepare_request ($settings, $description, $charge, $credit_card, $address, $order_id, $uid, $mail);
     $this->xml_data['ewayCVN'] = $credit_card['code'];
     $this->xml_data['ewayCustomerIPAddress'] = $_SERVER['REMOTE_ADDR'];
     $this->xml_data['ewayCustomerBillingCountry'] = $address['country'];
   }

}