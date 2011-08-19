<?php

$plugin = array(
  // Default ctools properties.
  'title' => t('Australia Post plugin'),
  'description' => t('This plugin is used as an example and documentation of commerce_shipping features.'),
  'handler' => array(
    'class' => 'CommerceShippingAustraliapost',
    'parent' => 'quote_base'
  ),
  // Special Commerce Shipping properties.
  // Display title, used for many frontend displays. Default value is the
  // title property.
  'display_title' => t('Australia Post shipping method'),
  // The shipping label for select form, default value is display_title.
  'shipping_label' => t('Australia Post shipping method radio button'),
  // Boolean indicator indicating if a rule and action should be created.
  'create_rule' => TRUE,
  // Default settings as defined through the settings form on the rules action.
  'settings' => array(
    'shipping_price' => 42,
  ),
  // Define a price component that will be used for this shipping method.
  'price_component' => array(
    'title' => t('Shipping costs from Australia Post module'),
    'display_title' => t('Australia Post shipping costs'),
    'weight' => -40,
  ),
);
