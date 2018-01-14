<?php

namespace Drupal\pokemon_general\Entity;

use Drupal\views\EntityViewsData;

/**
 * Provides Views data for Attack entity entities.
 */
class AttackEntityViewsData extends EntityViewsData {

  /**
   * {@inheritdoc}
   */
  public function getViewsData() {
    $data = parent::getViewsData();

    // Additional information for Views integration, such as table joins, can be
    // put here.

    return $data;
  }

}
