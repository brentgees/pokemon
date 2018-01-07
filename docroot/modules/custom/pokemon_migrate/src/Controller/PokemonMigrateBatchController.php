<?php

/**
 * @file
 * Contains \Drupal\pokemon_migrate\Controller\PokemonMigrateBatchController.
 */

namespace Drupal\pokemon_migrate\Controller;

use Pokemon\Pokemon;

/**
 * Class PokemonMigrateBatchController.
 *
 * @package Drupal\pokemon_migrate\Controller
 */
class PokemonMigrateBatchController {

  /**
   * Perform batch.
   */
  public function content() {
    $sets = Pokemon::Set()->all();

    $batch = array(
      'title' => t('Exporting'),
      'operations' => array(
        array('pokemon_migrate_sets', array($sets)),
      ),
      'finished' => 'pokemon_migrate_finished_callback',
      'file' => drupal_get_path('module', 'pokemon_migrate') . '/pokemon_migrate.migrate.inc',
    );

    batch_set($batch);
    return batch_process('<front>');
    //    return batch_process('user');
  }
}