<?php

/**
 * Rules integration for eWAY token payments
 */


/**
 * Implements hook_rules_action_info().
 */
function commerce_payment_eway_rules_action_info() {
  $actions = array();

  $actions['commerce_payment_eway_create_customer'] = array(
    'label' => t('Setup for eWAY token billing'),
    'parameter' => array(
      'user' => array(
        'type' => 'user',
        'label' => t('User')),
    ),
    'group' => t('Commerce Payment eWAY'),
    'base' => 'commerce_payment_eway_create_customer',
  );
  $actions['commerce_payment_eway_process_payment'] = array(
    'label' => t('Pay order if setup for eWAY token billing'),
    'parameter' => array(
      'order' => array(
        'type' => 'commerce_order',
        'label' => t('Order')),
    ),
    'group' => t('Commerce Payment eWAY'),
    'base' => 'commerce_payment_eway_process_payment',
  );

  return $actions;
}


/*
 * When token billing is used, we need to register new customers.
 */
function commerce_payment_eway_create_customer ($account) {
  if (isset ($_SESSION['eway_customer_data'])) {
    $customer_data = $_SESSION['eway_customer_data'];
    $settings = $_SESSION['eway_settings'];
    $testing = $customer_data['CCNumber'] == COMMERCE_PAYMENT_EWAY_TEST_CCNUMBER;
    module_load_include ('class.inc', 'commerce_payment_eway','includes/eway_base');
    module_load_include ('class.inc', 'commerce_payment_eway', 'includes/eway_token');
    $processor = new eway_token ($settings);
    // Don't care if this fails
    $success = $processor->create_customer ($account->uid, $customer_data);
    unset ($_SESSION['eway_customer_data']);
    unset ($_SESSION['eway_settings']);
  }
}


/*
 * If token billing is setup, pay for order.
 */
function commerce_payment_eway_process_payment ($order) {
  var_dump ($order);
  $ManagedCustomerId = db_query ('select eway_id from {commerce_eway_token} where uid = :uid', array (':uid' => $order->uid))->fetchField();
  if ($ManagedCustomerId) {

    // Build a description to send to the payment gateway.
    $description = theme('commerce_payment_eway_transaction_description', array('order' => $order));
    // Trim the description to eWay's limit of 10000 characters,
    // which is ridiculously long anyway.
    $description = substr($description, 0, 10000);

    $settings = $order->payment_methods['commerce_payment_eway|commerce_payment_commerce_payment_eway']['settings'];
    $charge = array (
     'amount' => $order->commerce_order_total[LANGUAGE_NONE][0]['amount'],
     'currency_code' => $order->commerce_order_total[LANGUAGE_NONE][0]['currency_code'],
    );
    module_load_include ('class.inc', 'commerce_payment_eway','includes/eway_base');
    module_load_include ('class.inc', 'commerce_payment_eway', 'includes/eway_token');
    $processor = new eway_token ($settings);
    $processor->process_payment ($ManagedCustomerId, $charge['amount'], $order->order_id, $description);
    $transaction = _commerce_payment_eway_save_transaction ($settings, $order, $charge, $processor->return_info);
    $ok = $transaction->status == COMMERCE_PAYMENT_STATUS_SUCCESS;
    if ($ok)
      commerce_checkout_complete ($order);
  }
}
