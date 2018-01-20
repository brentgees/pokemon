<?php

namespace Drupal\pokemon_deck\Form;

use Drupal\Core\Form\ConfigFormBase;
use Drupal\Core\Form\FormStateInterface;

/**
 * Class DeckPtcgoSubmit.
 */
class DeckPtcgoSubmit extends ConfigFormBase {

  /**
   * {@inheritdoc}
   */
  protected function getEditableConfigNames() {
    return [
      'pokemon_deck.deckptcgosubmit',
    ];
  }

  /**
   * {@inheritdoc}
   */
  public function getFormId() {
    return 'deck_ptcgo_submit';
  }

  /**
   * {@inheritdoc}
   */
  public function buildForm(array $form, FormStateInterface $form_state) {
    $config = $this->config('pokemon_deck.deckptcgosubmit');
    $form['decklist'] = [
      '#type' => 'textarea',
      '#title' => $this->t('Enter deck here (ptcgo format)'),
      '#default_value' => $config->get('decklist'),
    ];
    return parent::buildForm($form, $form_state);
  }

  /**
   * {@inheritdoc}
   */
  public function validateForm(array &$form, FormStateInterface $form_state) {
    parent::validateForm($form, $form_state);
  }

  /**
   * {@inheritdoc}
   */
  public function submitForm(array &$form, FormStateInterface $form_state) {
    parent::submitForm($form, $form_state);

    $this->config('pokemon_deck.deckptcgosubmit')
      ->set('decklist', $form_state->getValue('decklist'))
      ->save();
  }

}
