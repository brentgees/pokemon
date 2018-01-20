<?php

namespace Drupal\pokemon_general\Plugin\Field\FieldWidget;

use Drupal\Core\Field\FieldItemListInterface;
use Drupal\Core\Field\WidgetBase;
use Drupal\Core\Form\FormStateInterface;

/**
 * Plugin implementation of the 'pokemon_deck_entry_text_widget' widget.
 *
 * @FieldWidget(
 *   id = "pokemon_deck_entry_text_widget",
 *   label = @Translation("Pokemon deck entry text widget"),
 *   field_types = {
 *     "pokemon_deck_entry"
 *   }
 * )
 */
class PokemonDeckEntryTextWidget extends WidgetBase {

  /**
   * {@inheritdoc}
   */
  public static function defaultSettings() {
    return parent::defaultSettings();
  }

  /**
   * {@inheritdoc}
   */
  public function settingsForm(array $form, FormStateInterface $form_state) {
    $elements = [];

    return $elements;
  }

  /**
   * {@inheritdoc}
   */
  public function settingsSummary() {
    $summary = [];

    return $summary;
  }

  /**
   * {@inheritdoc}
   */
  public function formElement(FieldItemListInterface $items, $delta, array $element, array &$form, FormStateInterface $form_state) {

    $element['amount'] = [
      '#type' => 'textfield',
      '#default_value' => isset($items[$delta]->amount) ? $items[$delta]->amount : 0,
      '#size' => '3',
      '#maxlength' => '2',
    ];

    $element['nid'] = [
      '#type' => 'textfield',
      '#default_value' => isset($items[$delta]->amount) ? $items[$delta]->amount : 0,
      '#size' => '8',
      '#maxlength' => '8',
    ];

    $element['hash_identical'] = [
      '#type' => 'textfield',
      '#default_value' => isset($items[$delta]->amount) ? $items[$delta]->amount : '',
      '#size' => '32',
      '#maxlength' => '32',
    ];

//    $element['value'] = $element + [
//      '#type' => 'textfield',
//      '#default_value' => isset($items[$delta]->value) ? $items[$delta]->value : NULL,
//      '#size' => $this->getSetting('size'),
//      '#placeholder' => $this->getSetting('placeholder'),
//      '#maxlength' => $this->getFieldSetting('max_length'),
//    ];

//    amount
//nid
//hash_identical

    return $element;
  }

}
