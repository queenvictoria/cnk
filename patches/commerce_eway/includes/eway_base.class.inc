<?php

abstract class eway_base {

  function __construct($settings) {
    $this->return_info = false;
    $this->testing = commerce_payment_eway_in_testing_mode($settings);
    $this->log_to_watchdog = _commerce_payment_eway_log_to_watchdog($settings);
    $this->customer_id = _commerce_payment_eway_get_data('customer_id', $settings);
    $this->user_name = _commerce_payment_eway_get_data('user_name', $settings);
    $this->password = _commerce_payment_eway_get_data('password', $settings);
  }

  function charge ($settings, $description, $charge, $credit_card, $address, $order_id, $uid, $mail) {
    $this->prepare_request ($settings, $description, $charge, $credit_card, $address, $order_id, $uid, $mail);
    $this->process_request ();
  }

  abstract protected function prepare_request ($settings, $description, $charge, $credit_card, $address, $order_id, $uid, $mail);

  abstract protected function process_request ();

}