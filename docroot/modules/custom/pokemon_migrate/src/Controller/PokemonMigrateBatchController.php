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

//    $result = \Drupal::entityQuery('taxonomy_term')
//      ->condition('vid', 'set')
//      ->execute();
//    entity_delete_multiple('taxonomy_term', $result);

    // Get previously imported nodes.
    $query = \Drupal::database()->select('pokemon_migrate', 'pm');
    $query->fields('pm');
    $result = $query->execute()->fetchAllAssoc('ptcgapi_id');

    $sets = Pokemon::Set()->all();

    $batch = array(
      'title' => t('Exporting'),
      'operations' => array(
        array('pokemon_migrate_sets', array($sets, $result)),
      ),
      'finished' => 'pokemon_migrate_finished_callback',
      'file' => drupal_get_path('module', 'pokemon_migrate') . '/pokemon_migrate.migrate.inc',
    );

    batch_set($batch);
    return batch_process('<front>');
  }
}