<?php

class CommerceShippingAustraliapost extends CommerceShippingQuote {
  /**
   * The settings form, used to add our custom settings to the rules action
   * settings form.
   */
  public function settings_form(&$form, $rules_settings) {
    $form['shipping_price'] = array(
      '#type' => 'textfield',
      '#title' => t('Shipping price'),
      '#description' => t('Configure what the shipping price per order should be.'),
      '#default_value' => is_array($rules_settings) && isset($rules_settings['shipping_price']) ? $rules_settings['shipping_price'] : 42,
      '#element_validate' => array('rules_ui_element_decimal_validate'),
    );
  }

  /**
   * Define a form that is added when this shipping method is selected during
   * checkout.
   */
  public function submit_form($pane_values, $checkout_pane, $order = NULL) {
    if (empty($order)) {
      $order = $this->order;
    }
    $form = parent::submit_form($pane_values, $checkout_pane, $order);

    // Merge in values from the order.
    if (!empty($order->data['commerce_shipping_australiapost'])) {
      $pane_values += $order->data['commerce_shipping_australiapost'];
    }

    // Merge in default values.
    $pane_values += array(
      'express' => 0,
      'name' => '',
    );

    $form['express'] = array(
      '#type' => 'checkbox',
      '#title' => t('Express delivery'),
      '#description' => t('Express delivery cost twice the normal amount.'),
      '#default_value' => $pane_values['express'],
    );

    $form['name'] = array(
      '#type' => 'textfield',
      '#title' => t('Name'),
      '#description' => t('This is a demonstration field coded to fail validation for single character values.'),
      '#default_value' => $pane_values['name'],
      '#required' => TRUE,
    );

    return $form;
  }

  /**
   * Validation form, to validate the submit form that we can add. If we want
   * to fail the validation we return FALSE, otherwise nothing needs to be
   * done.
   */
  public function submit_form_validate($pane_form, $pane_values, $form_parents = array(), $order = NULL) {
    // Throw an error if a long enough name was not provided.
    if (strlen($pane_values['name']) < 2) {
      form_set_error(implode('][', array_merge($form_parents, array('name'))), t('You must enter a name two or more characters long.'));

      // Even though the form error is enough to stop the submission of the form,
      // it's not enough to stop it from a Commerce standpoint because of the
      // combined validation / submission going on per-pane in the checkout form.
      return FALSE;
    }
  }

  /**
   * The bulk of the shipping method is usually found here. This is where we
   * do the actual calculations to figure out what the shipping costs should
   * be. We can return a single price or for more control an array of arrays
   * containing:
   *    - label
   *    - quantity
   *    - amount
   *    - currency code
   *
   * Only the amount is needed as the rest have default values.
   */
  public function calculate_quote($currency_code, $form_values = array(), $order = NULL, $pane_form = NULL, $pane_values = NULL) {
    if (empty($order)) {
      $order = $this->order;
    }
    $settings = $this->settings;
    $shipping_line_items = array();
    $shipping_line_items[] = array(
      'amount' => commerce_currency_decimal_to_amount($settings['shipping_price'], $currency_code),
      'currency_code' => $currency_code,
      'label' => t('Normal shipping'),
    );
    if (isset($form_values['express']) && $form_values['express']) {
      $shipping_line_items[] = array(
        'amount' => commerce_currency_decimal_to_amount($settings['shipping_price'], $currency_code),
        'currency_code' => $currency_code,
        'label' => t('Express fee'),
      );
    }
    return $shipping_line_items;
  }
}