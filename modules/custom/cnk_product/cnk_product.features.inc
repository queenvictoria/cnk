<?php
/**
 * @file
 * cnk_product.features.inc
 */

/**
 * Implementation of hook_commerce_product_default_types().
 */
function cnk_product_commerce_product_default_types() {
  $items = array(
    'product' => array(
      'type' => 'product',
      'name' => 'Product',
      'description' => 'A basic product type.',
      'help' => '',
      'module' => 'commerce_product_ui',
    ),
  );
  return $items;
}

/**
 * Implementation of hook_node_info().
 */
function cnk_product_node_info() {
  $items = array(
    'product_display' => array(
      'name' => t('Product display'),
      'base' => 'node_content',
      'description' => t('Use <em>product displays</em> to present Add to Cart form for products to your customers.'),
      'has_title' => '1',
      'title_label' => t('Title'),
      'help' => '',
    ),
  );
  return $items;
}
