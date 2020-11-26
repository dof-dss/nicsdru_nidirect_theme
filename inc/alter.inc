<?php

use Drupal\Core\Form\FormStateInterface;

/**
 * Implements hook_page_attachmentsldc_alter().
 */
function nicsdru_nidirect_theme_page_attachments_alter(array &$page) {

  // Attach layout builder styles for authenticated users.
  $userCurrent = \Drupal::currentUser();

  if ($userCurrent->isAuthenticated()) {
    $page['#attached']['library'][] = 'nicsdru_nidirect_theme/authenticated-styles';
  }
}



/**
 * Implements hook_form_BASE_FORM_ID_alter().
 */
function nicsdru_nidirect_theme_form_node_preview_form_select_alter(&$form, FormStateInterface $form_state, $form_id) {
  // Additional styles to the node preview form.
  unset($form['view_mode']);
  $form['backlink']['#options']['attributes']['class'] += [
    'btn-standard',
    'call-to-action',
  ];
}

/**
 * Implements hook_theme_suggestions_HOOK_alter().
 */
function nicsdru_nidirect_theme_theme_suggestions_field_alter(array &$suggestions, array $variables) {
  // Force related info/More useful links fields to use the
  // related_info template.
  if ($variables['element']['#field_name'] === 'field_related_info') {
    $suggestions = ['field__field_related_info'];
  }
}
