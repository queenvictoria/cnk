<?php
/**
 * @file
 * cnk_product.features.user_permission.inc
 */

/**
 * Implementation of hook_user_default_permissions().
 */
function cnk_product_user_default_permissions() {
  $permissions = array();

  // Exported permission: administer commerce_product entities
  $permissions['administer commerce_product entities'] = array(
    'name' => 'administer commerce_product entities',
    'roles' => array(
      0 => 'administrator',
    ),
    'module' => 'commerce_product',
  );

  // Exported permission: administer product pricing
  $permissions['administer product pricing'] = array(
    'name' => 'administer product pricing',
    'roles' => array(
      0 => 'administrator',
    ),
    'module' => 'commerce_product_pricing_ui',
  );

  // Exported permission: administer product types
  $permissions['administer product types'] = array(
    'name' => 'administer product types',
    'roles' => array(
      0 => 'administrator',
    ),
    'module' => 'commerce_product',
  );

  // Exported permission: create commerce_product entities
  $permissions['create commerce_product entities'] = array(
    'name' => 'create commerce_product entities',
    'roles' => array(
      0 => 'administrator',
    ),
    'module' => 'commerce_product',
  );

  // Exported permission: create commerce_product entities of bundle product
  $permissions['create commerce_product entities of bundle product'] = array(
    'name' => 'create commerce_product entities of bundle product',
    'roles' => array(
      0 => 'administrator',
    ),
    'module' => 'commerce_product',
  );

  // Exported permission: create product_display content
  $permissions['create product_display content'] = array(
    'name' => 'create product_display content',
    'roles' => array(),
  );

  // Exported permission: delete any product_display content
  $permissions['delete any product_display content'] = array(
    'name' => 'delete any product_display content',
    'roles' => array(),
  );

  // Exported permission: delete own product_display content
  $permissions['delete own product_display content'] = array(
    'name' => 'delete own product_display content',
    'roles' => array(),
  );

  // Exported permission: edit any commerce_product entity
  $permissions['edit any commerce_product entity'] = array(
    'name' => 'edit any commerce_product entity',
    'roles' => array(
      0 => 'administrator',
    ),
    'module' => 'commerce_product',
  );

  // Exported permission: edit any commerce_product entity of bundle product
  $permissions['edit any commerce_product entity of bundle product'] = array(
    'name' => 'edit any commerce_product entity of bundle product',
    'roles' => array(
      0 => 'administrator',
    ),
    'module' => 'commerce_product',
  );

  // Exported permission: edit any product_display content
  $permissions['edit any product_display content'] = array(
    'name' => 'edit any product_display content',
    'roles' => array(),
  );

  // Exported permission: edit own commerce_product entities
  $permissions['edit own commerce_product entities'] = array(
    'name' => 'edit own commerce_product entities',
    'roles' => array(
      0 => 'administrator',
    ),
    'module' => 'commerce_product',
  );

  // Exported permission: edit own commerce_product entities of bundle product
  $permissions['edit own commerce_product entities of bundle product'] = array(
    'name' => 'edit own commerce_product entities of bundle product',
    'roles' => array(
      0 => 'administrator',
    ),
    'module' => 'commerce_product',
  );

  // Exported permission: edit own product_display content
  $permissions['edit own product_display content'] = array(
    'name' => 'edit own product_display content',
    'roles' => array(),
  );

  // Exported permission: rate content
  $permissions['rate content'] = array(
    'name' => 'rate content',
    'roles' => array(
      0 => 'administrator',
      1 => 'authenticated user',
    ),
    'module' => 'fivestar',
  );

  // Exported permission: view any commerce_product entity
  $permissions['view any commerce_product entity'] = array(
    'name' => 'view any commerce_product entity',
    'roles' => array(
      0 => 'administrator',
    ),
    'module' => 'commerce_product',
  );

  // Exported permission: view any commerce_product entity of bundle product
  $permissions['view any commerce_product entity of bundle product'] = array(
    'name' => 'view any commerce_product entity of bundle product',
    'roles' => array(
      0 => 'administrator',
    ),
    'module' => 'commerce_product',
  );

  // Exported permission: view own commerce_product entities
  $permissions['view own commerce_product entities'] = array(
    'name' => 'view own commerce_product entities',
    'roles' => array(
      0 => 'administrator',
    ),
    'module' => 'commerce_product',
  );

  // Exported permission: view own commerce_product entities of bundle product
  $permissions['view own commerce_product entities of bundle product'] = array(
    'name' => 'view own commerce_product entities of bundle product',
    'roles' => array(
      0 => 'administrator',
    ),
    'module' => 'commerce_product',
  );

  return $permissions;
}
