<?php

/**
 * @file
 * Contains attack_entity.page.inc.
 *
 * Page callback for Attack entity entities.
 */

use Drupal\Core\Render\Element;

/**
 * Prepares variables for Attack entity templates.
 *
 * Default template: attack_entity.html.twig.
 *
 * @param array $variables
 *   An associative array containing:
 *   - elements: An associative array containing the user information and any
 *   - attributes: HTML attributes for the containing element.
 */
function template_preprocess_attack_entity(array &$variables) {
  // Fetch AttackEntity Entity Object.
  $attack_entity = $variables['elements']['#attack_entity'];

  // Helpful $content variable for templates.
  foreach (Element::children($variables['elements']) as $key) {
    $variables['content'][$key] = $variables['elements'][$key];
  }
}
