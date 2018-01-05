<?php

/**
 * @file
 * Contains the imports
 */

/**
 * Migrate the sets
 */
function migrate_sets(&$context) {

  // Do heavy coding here...
  $message = 'migrating';

//  switch ($type) {
//    case 'courses':
//      $message = 'migrating courses...';
//      $context['results'][] = $options;
//      break;
//    default:
//      $message = 'migrating somethine else...';
//      break;
//  }

  $context['results'][] = 'test';

  $context['message'] = $message;
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