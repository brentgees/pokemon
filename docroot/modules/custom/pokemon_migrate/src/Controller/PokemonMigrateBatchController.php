<?php

/**
 * @file
 * Contains \Drupal\pokemon_migrate\Controller\PokemonMigrateBatchController.
 */

namespace Drupal\pokemon_migrate\Controller;

/**
 * Class PokemonMigrateBatchController.
 *
 * @package Drupal\pokemon_migrate\Controller
 */
class PokemonMigrateBatchController {
  public function content() {

    $batch = array(
      'title' => t('Exporting'),
      'operations' => array(
        array('migrate_sets'),
      ),
      'finished' => 'pokemon_migrate_finished_callback',
      'file' => drupal_get_path('module', 'pokemon_migrate') . '/pokemon_migrate.migrate.inc',
    );

    batch_set($batch);
    return batch_process('user');
  }
}