<?php

/**
 * @file
 * Contains the imports
 */

use Drupal\taxonomy\Entity\Term;
use Pokemon\Pokemon;

/**
 * Migrate the set.
 */
function pokemon_migrate_sets($sets = array(), &$context) {
  // Do heavy coding here...

  foreach ($sets as $set) {

    $context['results'][] = 'Imported' . $set->getName();
    $context['message'] = 'Importing ' . $set->getName();
    $term = Term::create([
      'name' => $set->getName(),
      'vid' => 'set',
      'field_set_code' => $set->getCode(),
      'field_set_expanded_legal' => $set->isExpandedLegal(),
//      'field_set_logo' => $set->getLogoUrl(),
      'field_set_ptcgo_code' => $set->getPtcgoCode(),
//      'field_set_release_date' => $set->getReleaseDate(),
      'field_set_series' => $set->getSeries(),
      'field_set_standard_legal' => $set->isStandardLegal(),
//      'field_set_symbol' => $set->getSymbolUrl(),
      'field_set_total_cards' => $set->getTotalCards(),
    ])->save();;
  }

//  switch ($type) {
//    case 'courses':
//      $message = 'migrating courses...';
//      $context['results'][] = $options;
//      break;
//    default:
//      $message = 'migrating somethine else...';
//      break;
//  }


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