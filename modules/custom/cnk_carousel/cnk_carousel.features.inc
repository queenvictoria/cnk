<?php
/**
 * @file
 * cnk_carousel.features.inc
 */

/**
 * Implementation of hook_views_api().
 */
function cnk_carousel_views_api() {
  list($module, $api) = func_get_args();
  if ($module == "views" && $api == "views_default") {
    return array("version" => "3.0");
  }
}

/**
 * Implementation of hook_image_default_styles().
 */
function cnk_carousel_image_default_styles() {
  $styles = array();

  // Exported image style: cnk_carousel
  $styles['cnk_carousel'] = array(
    'name' => 'cnk_carousel',
    'effects' => array(
      1 => array(
        'label' => 'Scale and crop',
        'help' => 'Scale and crop will maintain the aspect-ratio of the original image, then crop the larger dimension. This is most useful for creating perfectly square thumbnails without stretching the image.',
        'effect callback' => 'image_scale_and_crop_effect',
        'form callback' => 'image_resize_form',
        'summary theme' => 'image_resize_summary',
        'module' => 'image',
        'name' => 'image_scale_and_crop',
        'data' => array(
          'width' => '950',
          'height' => '534',
        ),
        'weight' => '1',
      ),
    ),
  );

  return $styles;
}

/**
 * Implementation of hook_node_info().
 */
function cnk_carousel_node_info() {
  $items = array(
    'slide' => array(
      'name' => t('Slide'),
      'base' => 'node_content',
      'description' => t('Create slides to add to carousels.'),
      'has_title' => '1',
      'title_label' => t('Heading'),
      'help' => '',
    ),
  );
  return $items;
}
