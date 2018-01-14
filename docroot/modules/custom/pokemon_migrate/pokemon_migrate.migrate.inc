<?php

/**
 * @file
 * Contains the imports
 */

use Drupal\file\Entity\File;
use Drupal\node\Entity\Node;
use Drupal\taxonomy\Entity\Term;
use Pokemon\Pokemon;

/**
 * Migrate the set.
 *
 * @throws \Drupal\Component\Plugin\Exception\InvalidPluginDefinitionException
 * @throws \Exception
 */
function pokemon_migrate_sets($sets = [], $existing_nodes = [], &$context) {
  // Do heavy coding here...
  foreach ($sets as $set) {

    if (isset($existing_nodes[$set->getCode()]->drupal_id)) {
      // Do stuff when the node already exists, update and stuff.
    }
    else {

      // Create directory.
      $directory = file_stream_wrapper_uri_normalize("public://cards/" . $set->getCode());
      file_prepare_directory($directory, FILE_CREATE_DIRECTORY);

      // Logo.
      $logo = file_get_contents($set->getLogoUrl());
      $size = getimagesize($set->getLogoUrl());
      $extension = image_type_to_extension($size[2]);
      $logo_file = file_save_data($logo, 'public://cards/' . $set->getCode() . '/logo' . $extension, FILE_EXISTS_REPLACE);

      // Symbol.
      $symbol = file_get_contents($set->getSymbolUrl());
      $size = getimagesize($set->getSymbolUrl());
      $extension = image_type_to_extension($size[2]);
      $symbol_file = file_save_data($symbol, 'public://cards/' . $set->getCode() . '/symbol' . $extension, FILE_EXISTS_REPLACE);

      // Release date.
      $date = str_replace('/', '-', $set->getReleaseDate());
      $release_date = date('Y-m-d', strtotime($date));

      $context['results'][] = 'Imported' . $set->getName();
      $context['message'] = 'Importing ' . $set->getName();
      $term = Term::create([
        'name' => $set->getName(),
        'vid' => 'set',
        'field_set_code' => $set->getCode(),
        'field_set_expanded_legal' => $set->isExpandedLegal(),
        'field_set_logo' => [
          'target_id' => $logo_file->id(),
          'alt' => $set->getName() . ' logo',
          'title' => $set->getName() . 'logo',
        ],
        'field_set_ptcgo_code' => $set->getPtcgoCode(),
        'field_set_release_date' => $release_date,
        'field_set_series' => [
          'target_id' => pokemon_migrate_create_or_select_term($set->getSeries(), 'series'),
        ],
        'field_set_standard_legal' => $set->isStandardLegal(),
        'field_set_symbol' => [
          'target_id' => $symbol_file->id(),
          'alt' => $set->getName() . ' symbol',
          'title' => $set->getName() . 'symbol',
        ],
        'field_set_total_cards' => $set->getTotalCards(),
      ]);
      $term->save();

      \Drupal::database()->insert('pokemon_migrate')
        ->fields([
          'drupal_id',
          'entity_type',
          'bundle',
          'ptcgapi_id',
          'updated',
        ])
        ->values([
          $term->id(),
          'taxonomy',
          'set',
          $set->getCode(),
          time(),
        ])
        ->execute();

    }

  }

}

/**
 * Migrate the cards.
 *
 * @throws \Drupal\Component\Plugin\Exception\InvalidPluginDefinitionException
 * @throws \Exception
 */
function pokemon_migrate_cards($cards = [], $existing_nodes = [], &$context) {
  foreach ($cards as $card) {
    if (isset($existing_nodes[$card->getId()]->drupal_id)) {
      // Do stuff when the node already exists, update and stuff.
    }
    else {
      $context['results'][] = 'Imported' . $card->getName();
      $context['message'] = 'Importing ' . $card->getName();

      // Create directory.
      $directory = file_stream_wrapper_uri_normalize("public://cards/" . $card->getSetCode());
      file_prepare_directory($directory, FILE_CREATE_DIRECTORY);

      // Image.
      $image = file_get_contents($card->getImageUrlHiRes());
      $size = getimagesize($card->getImageUrlHiRes());
      $extension = image_type_to_extension($size[2]);
      $image_file = file_save_data($image, 'public://cards/' . $card->getSetCode() . '/' . $card->getNumber() . $extension, FILE_EXISTS_REPLACE);

      // Types.
      $field_card_types = [];
      foreach ($card->getTypes() as $type) {
        $field_card_types[]['target_id'] = pokemon_migrate_create_or_select_term($type, 'types');
      }
      $node = Node::create([
        'type' => 'card',
        'title' => $card->getName(),
        'field_card_artist' => [
          'target_id' => pokemon_migrate_create_or_select_term($card->getArtist(), 'artist'),
        ],
        'field_card_hp' => $card->getHp(),
        'field_card_id' => $card->getId(),
        'field_card_image' => [
          'target_id' => $image_file->id(),
          'alt' => $card->getName(),
          'title' => $card->getName(),
        ],
        'field_card_national_pokedex_numb' => $card->getNationalPokedexNumber(),
        'field_card_number' => $card->getNumber(),
        'field_card_rarity' => [
          'target_id' => pokemon_migrate_create_or_select_term($card->getRarity(), 'rarity'),
        ],
        'field_card_retreat_cost' => $card->getRetreatCost(),
        'field_card_series' => [
          'target_id' => pokemon_migrate_create_or_select_term($card->getSeries(), 'series'),
        ],
        'field_card_set' => [
          'target_id' => pokemon_migrate_create_or_select_term($card->getSet(), 'set'),
        ],
        'field_card_subtype' => [
          'target_id' => pokemon_migrate_create_or_select_term($card->getSubtype(), 'subtype'),
        ],
        'field_card_supertype' => [
          'target_id' => pokemon_migrate_create_or_select_term($card->getSupertype(), 'supertype'),
        ],
        'field_card_types' => $field_card_types,
      ]);

      $node->save();

      \Drupal::database()->insert('pokemon_migrate')
        ->fields([
          'drupal_id',
          'entity_type',
          'bundle',
          'ptcgapi_id',
          'updated',
        ])
        ->values([
          $node->id(),
          'node',
          'card',
          $card->getId(),
          time(),
        ])
        ->execute();
    }
  }
}

/**
 * Finish callback.
 */
function pokemon_migrate_finished_callback($success, $results, $operations) {
  // The 'success' parameter means no fatal PHP errors were detected. All
  // other error management should be handled using 'results'.
  if ($success) {
    $message = \Drupal::translation()->formatPlural(
      count($results),
      'One post processed.', '@count posts processed.'
    );
  }
  else {
    $message = t('Finished with an error.');
  }
  drupal_set_message($message);
  //$_SESSION['disc_migrate_batch_results'] = $results;
}