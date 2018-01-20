<?php

/**
 * @file Drush commands.
 */

use Pokemon\Pokemon;

/**
 * Implements hook_drush_command().
 */
function pokemon_migrate_drush_command() {
  $items = array();

  $items['migrate-reset'] = [
    'description' => 'Resets and Migrates everything.',
    'arguments' => [],
    'drupal dependencies' => ['pokemon_migrate'],
    'aliases' => ['migrate:reset'],
  ];

  $items['migrate-sets'] = [
    'description' => 'Migrates the sets.',
    'arguments' => [],
    'drupal dependencies' => ['pokemon_migrate'],
    'aliases' => ['migrate:sets'],
  ];

  $items['migrate-cards'] = [
    'description' => 'Migrates the cards.',
    'arguments' => [],
    'drupal dependencies' => ['pokemon_migrate'],
    'aliases' => ['migrate:cards'],
  ];
  return $items;
}

/**
 * Callback function drush_pokemon_migrate_migrate_cards()
 */
function drush_pokemon_migrate_migrate_cards() {
  module_load_include('inc', 'pokemon_migrate', 'pokemon_migrate.migrate');
  $query = \Drupal::database()->select('pokemon_migrate', 'pm');
  $query->fields('pm');
  $query->condition('entity_type', 'node');
  $query->condition('bundle', 'card');
  $result = $query->execute()->fetchAllAssoc('ptcgapi_id');

  $cards = Pokemon::Card()->where(['setCode' => 'sm2', 'pageSize' => '1000'])->all();

  $context = [];
  pokemon_migrate_cards($cards, $result, $context);
}

/**
 * Callback function drush_pokemon_migrate_migrate_cards()
 */
function drush_pokemon_migrate_migrate_sets() {
  module_load_include('inc', 'pokemon_migrate', 'pokemon_migrate.migrate');
  // Get previously imported nodes.
  $query = \Drupal::database()->select('pokemon_migrate', 'pm');
  $query->fields('pm');
  $query->condition('entity_type', 'taxonomy');
  $query->condition('bundle', 'set');
  $result = $query->execute()->fetchAllAssoc('ptcgapi_id');

  $sets = Pokemon::Set()->all();

  $context = [];
  pokemon_migrate_sets($sets, $result, $context);
}

/**
 * Callback function drush_pokemon_migrate_migrate_cards()
 */
function drush_pokemon_migrate_migrate_reset() {
  // Delete terms.
  $result = \Drupal::entityQuery('taxonomy_term')
    ->condition('vid', 'set')
    ->execute();
  entity_delete_multiple('taxonomy_term', $result);

  // Delete nodes.
  $result = \Drupal::entityQuery('node')
    ->condition('type', 'card')
    ->execute();
  entity_delete_multiple('node', $result);

  // Empty database.
  db_truncate('pokemon_migrate')->execute();
  drush_pokemon_migrate_migrate_sets();
  drush_pokemon_migrate_migrate_cards_all();
}

/**
 * Callback function drush_pokemon_migrate_migrate_cards()
 */
function drush_pokemon_migrate_migrate_cards_all() {
  module_load_include('inc', 'pokemon_migrate', 'pokemon_migrate.migrate');
  $query = \Drupal::database()->select('pokemon_migrate', 'pm');
  $query->fields('pm');
  $query->condition('entity_type', 'node');
  $query->condition('bundle', 'card');
  $result = $query->execute()->fetchAllAssoc('ptcgapi_id');

  $sets = Pokemon::Set()->all();
  $context = [];
  foreach ($sets as $set) {
    $cards = Pokemon::Card()->where(['setCode' => $set->getCode(), 'pageSize' => '1000'])->all();
    pokemon_migrate_cards($cards, $result, $context);
  }
}
