<?php

namespace Drupal\nicsdru_nidirect_theme;

use Drupal\block\Entity\Block;

/**
 * Theme helper functions.
 *
 * @package Drupal\nicsdru_nidirect_theme
 */
class Helpers {
  /**
   * Loads and returns block content.
   *
   * @param $block_id
   *  machine name of the block to load.
   *
   * @return array|null
   *  Block render array or null if block not found.
   */
  public static function BlockContent($block_id) {
    $block = Block::load($block_id);
    if ($block !== null) {
      return \Drupal::entityTypeManager()->getViewBuilder('block')->view($block);
    }
    return null;
  }


}
