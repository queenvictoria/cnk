<?php

/**
 * Generate the description to send to the payment gateway for the order.
 *
 * @param $products
 *   An array of the products for the order.
 *
 * @ingroup themeable
 */
function theme_commerce_payment_eway_transaction_description($variables) {
  $order = $variables['order'];
  $line_item_ids = array ();
  foreach ($order->commerce_line_items as $l) {
    $line_item_ids[] = $l[0]['line_item_id'];
  }
  $line_items = commerce_line_item_load_multiple($line_item_ids);
  $description = '';
  foreach ($line_items as $line_item) {
    if (!empty($description)) {
      $description .= ' / ';
    }
    $description .= intval ($line_item->quantity) . ' x ' . $line_item->line_item_label;
  }

  return $description;
}
