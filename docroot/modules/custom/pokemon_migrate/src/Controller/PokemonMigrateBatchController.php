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

    // Delete terms.
//    $result = \Drupal::entityQuery('taxonomy_term')
//      ->condition('vid', 'set')
//      ->execute();
//    entity_delete_multiple('taxonomy_term', $result);

    // Get previously imported nodes.
    $query = \Drupal::database()->select('pokemon_migrate', 'pm');
    $query->fields('pm');
    $query->condition('entity_type', 'taxonomy');
    $query->condition('bundle', 'set');
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

  /**
   * Migrates the cards.
   */
  public function migrateCards() {
    // Delete nodes.
    $result = \Drupal::entityQuery('node')
      ->condition('type', 'card')
      ->execute();
    entity_delete_multiple('node', $result);

    // Get previously imported nodes.
    $query = \Drupal::database()->select('pokemon_migrate', 'pm');
    $query->fields('pm');
    $query->condition('entity_type', 'node');
    $query->condition('bundle', 'card');
    $result = $query->execute()->fetchAllAssoc('ptcgapi_id');

    $cards = Pokemon::Card()->where(['setCode' => 'sm2', 'pageSize' => '1000'])->all();

    $batch = array(
      'title' => t('Exporting'),
      'operations' => array(
        array('pokemon_migrate_cards', array($cards, $result)),
      ),
      'finished' => 'pokemon_migrate_finished_callback',
      'file' => drupal_get_path('module', 'pokemon_migrate') . '/pokemon_migrate.migrate.inc',
    );

    batch_set($batch);
    return batch_process('<front>');
  }
}