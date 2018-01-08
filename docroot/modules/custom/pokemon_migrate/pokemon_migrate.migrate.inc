<?php

/**
 * @file
 * Contains the imports
 */

use Drupal\file\Entity\File;
use Drupal\taxonomy\Entity\Term;
use Pokemon\Pokemon;

/**
 * Migrate the set.
 */
function pokemon_migrate_sets($sets = [], $existing_nodes = [], &$context) {
  // Do heavy coding here...
  foreach ($sets as $set) {

    if (isset($existing_nodes[$set->getCode()]->drupal_id)) {
      // Do stuff when the node already exists, update and stuff.
    }
    else {

      // Create directory.
      $directory = file_stream_wrapper_uri_normalize( "public://cards/" . $set->getCode());
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
        'field_set_series' => $set->getSeries(), //@TODO.
        'field_set_standard_legal' => $set->isStandardLegal(),
        'field_set_symbol' => [
          'target_id' => $symbol_file->id(),
          'alt' => $set->getName() . ' symbol',
          'title' => $set->getName() . 'symbol',
        ],
        'field_set_total_cards' => $set->getTotalCards(),
      ]);
      $term->save();

      try {
        \Drupal::database()->insert('pokemon_migrate')
          ->fields([
            'drupal_id',
            'entity_type',
            'bundle',
            'ptcgapi_id',
          ])
          ->values([
            $term->id(),
            'taxonomy',
            'set',
            $set->getCode(),
          ])
          ->execute();
      } catch (Exception $e) {

        $tmp = '';
      }
    }

  }

}

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