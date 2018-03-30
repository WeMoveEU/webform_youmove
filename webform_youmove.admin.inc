<?php

function webform_youmove_menu() {

  // Module configuration menu item
  $items['admin/config/content/webform/webform_youmove'] = array(
    'title' => t('WEMOVE - YouMove Webform (Campaign)'),
    'page callback' => 'drupal_get_form',
    'page arguments' => array('webform_youmove_admin_settings_form'),
    'access arguments' => array('administer site configuration'),
    'type' => MENU_NORMAL_ITEM,
    'file' =>'webform_youmove.admin.inc', );


  $items['node/%webform_menu/submission/%webform_menu_submission/publish'] = array(
      'title' => t('Publish'),
      'page callback' => '_submission_publish_func_callback',
      'page arguments' => array('submission',1,3),
      'access callback' => '_submission_publish_func_access',
      'access arguments' => array('submission',1,3),
      'type' => MENU_LOCAL_TASK,
      'weight' => 100,
       'options' => array(
        'attributes' => array(
          'class' => array('link-publish')
        )
      ), 
  );
  $items['node/%webform_menu/submission/%webform_menu_submission/edit/publish'] = array(
      'title' => t('Publish'),
      'page callback' => '_submission_publish_func_callback',
      'page arguments' => array('submission',1,3),
      'access callback' => '_submission_publish_func_access',
      'access arguments' => array('submission',1,3),
      'type' => MENU_LOCAL_TASK,
      'weight' => 100,
      'options' => array(
        'attributes' => array(
          'class' => array('link-publish')
        )
      ),
  );

  return $items;
}


function webform_youmove_admin_settings_form($form, &$form_state) {
  $form['ymw_user_dashboard_url'] = array(
    '#type' => 'textfield',
    '#title' => t('YouMove user dashboard URL'),
    '#default_value' => variable_get('webform_youmove__ymw_user_dashboard_url'),
    '#required' => TRUE,
  );
  $form['ymw_user_role_name'] = array(
    '#type' => 'textfield',
    '#title' => t('YouMove user role name'),
    '#default_value' => variable_get('webform_youmove__ymw_user_role_name'),
    '#required' => TRUE,
  );
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
  $form['ymw_is_published_positive_value'] = array(
    '#type' => 'textfield',
    '#title' => t('Webform publishing indicator field positive value'),
    '#default_value' => variable_get('webform_youmove__ymw_settings')['published_positive_value'],
    '#required' => TRUE,
  );
  $form['ymw_title_ID'] = array(
    '#type' => 'textfield',
    '#title' => t('Webform submission title field key'),
    '#default_value' => variable_get('webform_youmove__ymw_settings')['title_ID'],
    '#required' => TRUE,
  );
  $form['ymw_speakout_link_ID'] = array(
    '#type' => 'textfield',
    '#title' => t('Webform speakout link field key'),
    '#default_value' => variable_get('webform_youmove__ymw_settings')['speakout_link_ID'],
    '#required' => TRUE,
  );
  $form['ymw_language_ID'] = array(
    '#type' => 'textfield',
    '#title' => t('Webform language field key'),
    '#default_value' => variable_get('webform_youmove__ymw_settings')['language_ID'],
    '#required' => TRUE,
  );  
   
  $form['ymw_user_data_fieldset_ID'] = array(
    '#type' => 'textfield',
    '#title' => t('Webform user data fieldset key'),
    '#default_value' => variable_get('webform_youmove__ymw_settings')['user_data_fieldset_ID'],
    '#required' => TRUE,
  );

  $form['ymw_contact'] = array(
    '#type' => 'fieldset',
    '#title' => t('Contact'),
    '#collapsible' => false,
  );
  $form['ymw_contact']['ymw_contact_fieldset_ID'] = array(
    '#type' => 'textfield',
    '#title' => t('Fieldset key'),
    '#default_value' => variable_get('webform_youmove__ymw_settings')[contact_fieldset_ID],
    '#required' => TRUE,
  );
  $form['ymw_contact']['ymw_contact_name_ID'] = array(
    '#type' => 'textfield',
    '#title' => t('Name field key'),
    '#default_value' => variable_get('webform_youmove__ymw_settings')[contact_name_ID],
    '#required' => TRUE,
  );
  $form['ymw_contact']['ymw_contact_mail_ID'] = array(
    '#type' => 'textfield',
    '#title' => t('Mail field key'),
    '#default_value' => variable_get('webform_youmove__ymw_settings')[contact_mail_ID],
    '#required' => TRUE,
  );
  

  $form['ymw_login'] = array(
    '#type' => 'fieldset',
    '#title' => t('Login form'),
    '#collapsible' => false,
  );
  $form['ymw_login']['ymw_login_fieldset_ID'] = array(
    '#type' => 'textfield',
    '#title' => t('Fieldset key'),
    '#default_value' => variable_get('webform_youmove__ymw_settings')[login_fieldset_ID],
    '#required' => TRUE,
  );
  $form['ymw_login']['ymw_login_name_ID'] = array(
    '#type' => 'textfield',
    '#title' => t('Name field key'),
    '#default_value' => variable_get('webform_youmove__ymw_settings')[login_name_ID],
    '#required' => TRUE,
  );
  $form['ymw_login']['ymw_login_password_ID'] = array(
    '#type' => 'textfield',
    '#title' => t('Password field key'),
    '#default_value' => variable_get('webform_youmove__ymw_settings')[login_password_ID],
    '#required' => TRUE,
  );
    

  $form['ymw_disabled_fields'] = array(
    '#type' => 'textarea',
    '#title' => t('Webform submission disabled fields (edition) (UNPUBLISHED)'),
    '#default_value' => variable_get('webform_youmove__ymw_settings')['disabled_fields'],
    '#required' => TRUE,
    '#description' => t('Field keys, separated by commas'),
  );
  
  $form['ymw_disabled_fields__published'] = array(
    '#type' => 'textarea',
    '#title' => t('Webform submission disabled fields (edition) (PUBLISHED)'),
    '#default_value' => variable_get('webform_youmove__ymw_settings')['disabled_fields__published'],
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
  $form['ymw_hidden_fields__user_logged'] = array(
    '#type' => 'textarea',
    '#title' => t('Webform submission hidden fields (user logged)'),
    '#default_value' => variable_get('webform_youmove__ymw_settings')['hidden_fields__user_logged'],
    '#required' => TRUE,
    '#description' => t('Field keys, separated by commas'),
  );
  $form['ymw_hidden_fields__user_not_logged'] = array(
    '#type' => 'textarea',
    '#title' => t('Webform submission hidden fields (user anonymous)'),
    '#default_value' => variable_get('webform_youmove__ymw_settings')['hidden_fields__user_not_logged'],
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

  $settings['disabled_fields'] =  $form_state['values']['ymw_disabled_fields'];
  $settings['disabled_fields__published'] = $form_state['values']['ymw_disabled_fields__published'];
  $settings['hidden_fields'] =  $form_state['values']['ymw_hidden_fields'];
  $settings['hidden_fields__user_logged'] = $form_state['values']['ymw_hidden_fields__user_logged'];
  $settings['hidden_fields__user_not_logged'] = $form_state['values']['ymw_hidden_fields__user_not_logged'];
  $settings['published_ID'] =  $form_state['values']['ymw_is_published_ID'];
  $settings['published_positive_value'] = $form_state['values']['ymw_is_published_positive_value'];
  $settings['language_ID'] =  $form_state['values']['ymw_language_ID'];
  $settings['speakout_link_ID'] =  $form_state['values']['ymw_speakout_link_ID'];
  $settings['title_ID'] =  $form_state['values']['ymw_title_ID'];
  $settings['user_data_fieldset_ID'] =  $form_state['values']['ymw_user_data_fieldset_ID']; 

  $settings['contact_fieldset_ID'] = $form_state['values']['ymw_contact_fieldset_ID'];
  $settings['contact_name_ID'] = $form_state['values']['ymw_contact_name_ID'];
  $settings['contact_mail_ID'] = $form_state['values']['ymw_contact_mail_ID'];
  
  $settings['login_fieldset_ID'] = $form_state['values']['ymw_login_fieldset_ID'];
  $settings['login_name_ID'] = $form_state['values']['ymw_login_name_ID'];
  $settings['login_password_ID'] = $form_state['values']['ymw_login_password_ID'];

  $settings['submission_view_title'] = $form_state['values']['ymw_submission_view_title'];
  $settings['submission_edit_title'] = $form_state['values']['ymw_submission_edit_title'];
  $settings['registration_mail_body'] = $form_state['values']['ymw_registration_mail_body'];

  variable_set('webform_youmove__ymw_user_dashboard_url', $form_state['values']['ymw_user_dashboard_url']);
  variable_set('webform_youmove__ymw_ID', $form_state['values']['ymw_ID']);
  variable_set('webform_youmove__ymw_user_role_name', $form_state['values']['ymw_user_role_name']);
  variable_set('webform_youmove__ymw_settings',$settings);
}
