<?php
/**
 * @file
 * aunz_commerce_shipping_rules.rules_defaults.inc
 */

/**
 * Implementation of hook_default_rules_configuration().
 */
function aunz_commerce_shipping_rules_default_rules_configuration() {
  $items = array();
  $items['rules_flat_rate_au'] = entity_import('rules_config', '{ "rules_flat_rate_au" : {
      "LABEL" : "Flat rate to Australia",
      "PLUGIN" : "reaction rule",
      "WEIGHT" : "3",
      "REQUIRES" : [ "commerce_order", "commerce_shipping" ],
      "ON" : [ "commerce_shipping_methods" ],
      "IF" : [
        { "commerce_order_compare_address" : {
            "commerce_order" : [ "commerce_order" ],
            "address_field" : "commerce_customer_shipping|commerce_customer_address",
            "address_component" : "country",
            "value" : "AU"
          }
        },
        { "NOT commerce_order_compare_address" : {
            "commerce_order" : [ "commerce_order" ],
            "address_field" : "commerce_customer_shipping|commerce_customer_address",
            "address_component" : "country",
            "value" : "NZ"
          }
        }
      ],
      "DO" : [
        { "commerce_shipping_enable_flat_rate" : {
            "commerce_order" : [ "commerce-order" ],
            "shipping_method" : { "value" : {
                "method_id" : "flat_rate",
                "shipping_label" : "Flat rate to Australia",
                "settings" : {
                  "shipping_price" : "10",
                  "shipping_rates" : {
                    "AUD" : { "AUD" : "10", "include_tax" : "gst" },
                    "CAD" : { "CAD" : "10", "include_tax" : "gst" },
                    "EUR" : { "EUR" : "10", "include_tax" : "gst" },
                    "GBP" : { "GBP" : "10", "include_tax" : "gst" },
                    "HKD" : { "HKD" : "10", "include_tax" : "gst" },
                    "JPY" : { "JPY" : "10", "include_tax" : "gst" },
                    "NZD" : { "NZD" : "10", "include_tax" : "gst" },
                    "SGD" : { "SGD" : "10", "include_tax" : "gst" },
                    "USD" : { "USD" : "10", "include_tax" : "gst" }
                  },
                  "rate_type" : "product",
                  "label" : "Flat rate to Australia",
                  "include_tax" : "gst"
                }
              }
            }
          }
        }
      ]
    }
  }');
  $items['rules_flat_rate_nz'] = entity_import('rules_config', '{ "rules_flat_rate_nz" : {
      "LABEL" : "Flat rate to New Zealand",
      "PLUGIN" : "reaction rule",
      "WEIGHT" : "2",
      "REQUIRES" : [ "commerce_order", "commerce_shipping" ],
      "ON" : [ "commerce_shipping_methods" ],
      "IF" : [
        { "commerce_order_compare_address" : {
            "commerce_order" : [ "commerce_order" ],
            "address_field" : "commerce_customer_shipping|commerce_customer_address",
            "address_component" : "country",
            "value" : "NZ"
          }
        },
        { "NOT commerce_order_compare_address" : {
            "commerce_order" : [ "commerce_order" ],
            "address_field" : "commerce_customer_shipping|commerce_customer_address",
            "address_component" : "country",
            "value" : "AU"
          }
        }
      ],
      "DO" : [
        { "commerce_shipping_enable_flat_rate" : {
            "commerce_order" : [ "commerce-order" ],
            "shipping_method" : { "value" : {
                "method_id" : "flat_rate",
                "shipping_label" : "Flat rate to New Zealand",
                "settings" : {
                  "shipping_price" : "10",
                  "shipping_rates" : {
                    "AUD" : { "AUD" : "10", "include_tax" : "gst" },
                    "CAD" : { "CAD" : "10", "include_tax" : "gst" },
                    "EUR" : { "EUR" : "10", "include_tax" : "gst" },
                    "GBP" : { "GBP" : "10", "include_tax" : "gst" },
                    "HKD" : { "HKD" : "10", "include_tax" : "gst" },
                    "JPY" : { "JPY" : "10", "include_tax" : "gst" },
                    "NZD" : { "NZD" : "10", "include_tax" : "gst" },
                    "SGD" : { "SGD" : "10", "include_tax" : "gst" },
                    "USD" : { "USD" : "10", "include_tax" : "gst" }
                  },
                  "rate_type" : "product",
                  "label" : "Flat rate to New Zealand",
                  "include_tax" : "gst"
                }
              }
            }
          }
        }
      ]
    }
  }');
  $items['rules_free_shipping_au'] = entity_import('rules_config', '{ "rules_free_shipping_au" : {
      "LABEL" : "Free shipping within Australia",
      "PLUGIN" : "reaction rule",
      "REQUIRES" : [ "commerce_order", "commerce_shipping" ],
      "ON" : [ "commerce_shipping_methods" ],
      "IF" : [
        { "commerce_order_compare_address" : {
            "commerce_order" : [ "commerce_order" ],
            "address_field" : "commerce_customer_shipping|commerce_customer_address",
            "address_component" : "country",
            "value" : "AU"
          }
        }
      ],
      "DO" : [
        { "commerce_shipping_enable_flat_rate" : {
            "commerce_order" : [ "commerce-order" ],
            "shipping_method" : { "value" : {
                "method_id" : "flat_rate",
                "shipping_label" : "Free shipping within Australia",
                "settings" : {
                  "shipping_price" : "0",
                  "shipping_rates" : {
                    "AUD" : { "AUD" : "0", "include_tax" : "_none" },
                    "CAD" : { "CAD" : "0", "include_tax" : "_none" },
                    "EUR" : { "EUR" : "0", "include_tax" : "_none" },
                    "GBP" : { "GBP" : "0", "include_tax" : "_none" },
                    "HKD" : { "HKD" : "0", "include_tax" : "_none" },
                    "JPY" : { "JPY" : "0", "include_tax" : "_none" },
                    "NZD" : { "NZD" : "0", "include_tax" : "_none" },
                    "SGD" : { "SGD" : "0", "include_tax" : "_none" },
                    "USD" : { "USD" : "0", "include_tax" : "_none" }
                  },
                  "rate_type" : "order",
                  "label" : "Free shipping within Australia",
                  "include_tax" : "_none"
                }
              }
            }
          }
        }
      ]
    }
  }');
  $items['rules_free_shipping_nz'] = entity_import('rules_config', '{ "rules_free_shipping_nz" : {
      "LABEL" : "Free shipping within New Zealand",
      "PLUGIN" : "reaction rule",
      "REQUIRES" : [ "commerce_order", "commerce_shipping" ],
      "ON" : [ "commerce_shipping_methods" ],
      "IF" : [
        { "commerce_order_compare_address" : {
            "commerce_order" : [ "commerce_order" ],
            "address_field" : "commerce_customer_shipping|commerce_customer_address",
            "address_component" : "country",
            "value" : "NZ"
          }
        }
      ],
      "DO" : [
        { "commerce_shipping_enable_flat_rate" : {
            "commerce_order" : [ "commerce-order" ],
            "shipping_method" : { "value" : {
                "method_id" : "flat_rate",
                "shipping_label" : "Free shipping within New Zealand",
                "settings" : {
                  "shipping_price" : "0",
                  "shipping_rates" : {
                    "AUD" : { "AUD" : "0", "include_tax" : "_none" },
                    "CAD" : { "CAD" : "0", "include_tax" : "_none" },
                    "EUR" : { "EUR" : "0", "include_tax" : "_none" },
                    "GBP" : { "GBP" : "0", "include_tax" : "_none" },
                    "HKD" : { "HKD" : "0", "include_tax" : "_none" },
                    "JPY" : { "JPY" : "0", "include_tax" : "_none" },
                    "NZD" : { "NZD" : "0", "include_tax" : "_none" },
                    "SGD" : { "SGD" : "0", "include_tax" : "_none" },
                    "USD" : { "USD" : "0", "include_tax" : "_none" }
                  },
                  "rate_type" : "order",
                  "label" : "Free shipping within New Zealand",
                  "include_tax" : "_none"
                }
              }
            }
          }
        }
      ]
    }
  }');
  return $items;
}
