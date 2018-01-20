<?php

namespace Drupal\pokemon_general\Plugin\Field\FieldType;

use Drupal\Component\Utility\Random;
use Drupal\Core\Field\FieldDefinitionInterface;
use Drupal\Core\Field\FieldItemBase;
use Drupal\Core\Field\FieldStorageDefinitionInterface;
use Drupal\Core\Form\FormStateInterface;
use Drupal\Core\StringTranslation\TranslatableMarkup;
use Drupal\Core\TypedData\DataDefinition;

/**
 * Plugin implementation of the 'pokemon_deck_entry' field type.
 *
 * @FieldType(
 *   id = "pokemon_deck_entry",
 *   label = @Translation("Pokemon deck entry"),
 *   description = @Translation("Contains everything for a deck entry (amount, card-id, identical hash)"),
 *   default_widget = "pokemon_deck_entry_text_widget",
 *   default_formatter = "pokemon_deck_entry_text_formatter"
 * )
 */
class PokemonDeckEntry extends FieldItemBase {

  /**
   * {@inheritdoc}
   */
  public static function defaultStorageSettings() {
    return parent::defaultStorageSettings();
  }

  /**
   * {@inheritdoc}
   */
  public static function propertyDefinitions(FieldStorageDefinitionInterface $field_definition) {
    // Prevent early t() calls by using the TranslatableMarkup.
    $properties = [];
    $properties['amount'] = DataDefinition::create('integer')
      ->setLabel(new TranslatableMarkup('The times the card is in the deck.'))
      ->setRequired(TRUE);

    $properties['nid'] = DataDefinition::create('integer')
      ->setLabel(new TranslatableMarkup('The nid of the card'))
      ->setRequired(TRUE);

    $properties['hash_identical'] = DataDefinition::create('string')
      ->setLabel(new TranslatableMarkup('Identical hash'))
      ->setRequired(TRUE);

    return $properties;
  }

  /**
   * {@inheritdoc}
   */
  public static function schema(FieldStorageDefinitionInterface $field_definition) {
    $schema = [
      'columns' => [
        'amount' => [
          'type' => 'int',
          'unsigned' => TRUE,
          'not null' => TRUE,
          'default' => 0,
        ],
        'nid' => [
          'type' => 'int',
          'unsigned' => TRUE,
          'not null' => TRUE,
          'default' => 0,
        ],
        'hash_identical' => [
          'type' => 'varchar',
          'length' => 32,
        ],
      ],
    ];

    return $schema;
  }
//
//  /**
//   * {@inheritdoc}
//   */
//  public function getConstraints() {
//    $constraints = parent::getConstraints();
//
//    if ($max_length = $this->getSetting('max_length')) {
//      $constraint_manager = \Drupal::typedDataManager()->getValidationConstraintManager();
//      $constraints[] = $constraint_manager->create('ComplexData', [
//        'value' => [
//          'Length' => [
//            'max' => $max_length,
//            'maxMessage' => t('%name: may not be longer than @max characters.', [
//              '%name' => $this->getFieldDefinition()->getLabel(),
//              '@max' => $max_length
//            ]),
//          ],
//        ],
//      ]);
//    }
//
//    return $constraints;
//  }
//
//  /**
//   * {@inheritdoc}
//   */
//  public static function generateSampleValue(FieldDefinitionInterface $field_definition) {
//    $random = new Random();
//    $values['value'] = $random->word(mt_rand(1, $field_definition->getSetting('max_length')));
//    return $values;
//  }
//
//  /**
//   * {@inheritdoc}
//   */
//  public function storageSettingsForm(array &$form, FormStateInterface $form_state, $has_data) {
//    $elements = [];
//    return $elements;
//  }

  /**
   * {@inheritdoc}
   */
  public function isEmpty() {
//    $value = $this->get('value')->getValue();
    return FALSE;
  }

}
