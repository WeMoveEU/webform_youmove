<?php

function webform_youmove_menu() {

  $items['admin/config/content/webform/webform_youmove'] = array(
    'title' => t('WEMOVE - YouMove Webform (Campaign)'),
    'page callback' => 'drupal_get_form',
    'page arguments' => array('webform_youmove_admin_settings_form'),
    'access arguments' => array('administer site configuration'),
    'type' => MENU_NORMAL_ITEM,
    'file' =>'webform_youmove.admin.inc', );

  return $items;
}



function webform_youmove_admin_settings_form($form, &$form_state) {

  $form['ymw_ID'] = array(
    '#type' => 'textfield',
    '#title' => t('Webform ID'),
    '#default_value' => variable_get('webform_youmove__ymw_ID',null),
    '#size' => 4,
    '#maxlength' => 4,
    '#required' => TRUE,
  );
  $form['ymw_is_published_ID'] = array(
    '#type' => 'textfield',
    '#title' => t('Webform publishing indicator field key'),
    '#default_value' => variable_get('webform_youmove__ymw_settings')['published_ID'],
    '#required' => TRUE,
  );
  $form['ymw_user_role_name'] = array(
    '#type' => 'textfield',
    '#title' => t('YouMove user role name'),
    '#default_value' => variable_get('webform_youmove__ymw_user_role_name'),
    '#required' => TRUE,
  );


  $form_components = variable_get('webform_youmove__ymw_components',null);

  $form['ymw_contact'] = array(
    '#type' => 'fieldset',
    '#title' => t('Contact:'),
    '#collapsible' => false,
  );

  foreach($form_components as $form_component) {
    $form['ymw_contact']['ymw_contact_'.$form_component['name']] = array(
        '#type' => 'textfield',
        '#title' => t($form_component['label']),
        '#default_value' => variable_get('webform_youmove__ymw_settings')[$form_component['name']],
        '#required' => TRUE,
    );
  }

  $form['ymw_disabled_fields'] = array(
    '#type' => 'textarea',
    '#title' => t('Webform submission disabled fields (edition)'),
    '#default_value' => variable_get('webform_youmove__ymw_settings')['disabled_fields'],
    '#required' => TRUE,
    '#description' => t('Field keys, separated by commas'),
  );

  $form['ymw_hidden_fields'] = array(
    '#type' => 'textarea',
    '#title' => t('Webform submission hidden fields (preview)'),
    '#default_value' => variable_get('webform_youmove__ymw_settings')['hidden_fields'],
    '#required' => TRUE,
    '#description' => t('Field keys, separated by commas'),
  );

  $form['ymw_submission_view_title'] = array(
    '#type' => 'textfield',
    '#title' => t('Webform submission viewed title'),
    '#default_value' => variable_get('webform_youmove__ymw_settings')['submission_view_title'],
    '#required' => TRUE,
  );

  $form['ymw_submission_edit_title'] = array(
    '#type' => 'textfield',
    '#title' => t('Webform submission edited title'),
    '#default_value' =>
    variable_get('webform_youmove__ymw_settings')['submission_edit_title'],
    '#required' => TRUE,
  );

  $form['ymw_registration_mail_body'] = array(
    '#type' => 'textarea',
    '#title' => t('Registration mail body for new user creation (during campaign submission)'),
    '#rows' => 10,
    '#resizable' => TRUE,
    '#attributes' => array('style' => 'height: auto;'),
    '#default_value' => t(variable_get('webform_youmove__ymw_settings')['registration_mail_body']),
    '#required' => TRUE,
    '#translatable' => TRUE,
  );

  $form['#submit'][] = '_ymw_admin_settings_submit';

  return system_settings_form($form);
}

function _ymw_admin_settings_submit($form, $form_state) {
  $form_components = variable_get('webform_youmove__ymw_components',null);
  $settings = array();

  foreach($form_components as $form_component) {
      $settings[$form_component['name']] = $form_state['values']['ymw_contact_'.$form_component['name']];
  }
  $settings['disabled_fields'] =  $form_state['values']['ymw_disabled_fields'];
  $settings['hidden_fields'] =  $form_state['values']['ymw_hidden_fields'];
  $settings['published_ID'] =  $form_state['values']['ymw_is_published_ID'];
  $settings['submission_view_title'] = $form_state['values']['ymw_submission_view_title'];
  $settings['submission_edit_title'] = $form_state['values']['ymw_submission_edit_title'];
  $settings['registration_mail_body'] = $form_state['values']['ymw_registration_mail_body'];

  variable_set('webform_youmove__ymw_ID', $form_state['values']['ymw_ID']);
  variable_set('webform_youmove__ymw_user_role_name', $form_state['values']['ymw_user_role_name']);
  variable_set('webform_youmove__ymw_settings',$settings);
}
