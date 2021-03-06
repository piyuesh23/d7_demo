<?php

/**
 * @file
 * A class used for entity email type.
 */

/**
 * UI controller
 */
class EntityEmailTypeUIController extends EntityDefaultUIController {

  /**
   * Overridden to customize the field location.
   */
  public function entityFormSubmitBuildEntity($form, &$form_state) {
    // We cannot use entity_form_submit_build_entity() any more.
    // We have extra fields which needs to be saved.
    $entity = $form_state['entity_email_type'];

    // Extract form values.
    form_state_values_clean($form_state);

    foreach ($form_state['values'] as $key => $value) {
      if ($key != 'mail') {
        $entity->$key = $value;
      }
    }

    // Invoke all specified builders for copying form values to entity
    // properties.
    // @see entity_form_submit_build_entity()
    if (isset($form['#entity_builders'])) {
      foreach ($form['#entity_builders'] as $function) {
        $function('entity_email_type', $entity, $form, $form_state);
      }
    }

    field_attach_submit('entity_email_type', $entity, $form['mail'], $form_state);

    return $entity;
  }

}

/**
 * The Controller for EntityEmailType entities
 */
class EntityEmailTypeAPIControllerExportable extends EntityAPIControllerExportable {
  public function __construct($entityType) {
    parent::__construct($entityType);
  }

  /**
   * Create a entity_email_type - we first set up the values that are specific
   * to our entity_email_type schema but then also go through 
   * the EntityAPIControllerExportable function.
   *
   * @param $type
   *   The machine-readable type of the entity_email_type.
   *
   * @return
   *   A entity_email_type object with all default fields initialized.
   */
  public function create(array $values = array()) {
    // Add values that are specific to our Model.
    $values += array(
      'is_new' => TRUE,
      'subject' => '',
    );

    $entity_email_type = parent::create($values);
    return $entity_email_type;
  }

}

/**
 * The class used for Entity Email Type entity.
 */
class EntityEmailType extends Entity {

  public $eid;

  /**
   * The machine name of the entity email type.
   *
   * @var string
   */
  public $name;

  /**
   * The human-redable name of the entity email type.
   *
   * @var string
   */
  public $label;

  public $subject;

  public function __construct($values = array()) {
    parent::__construct($values, 'entity_email_type');
  }

  /**
   * Retrieves the configured subject in a certain language.
   *
   * @param $langcode
   *   The language code of the Subject field, the content should be
   *   extracted from.
   * @param $options
   *   Array of options to pass to the metadata-wrapper:
   *   - 'field name': The name of the Mail Body field, the content should be
   *     extracted from.
   *   - 'sanitize': Indicate if text should be escaped.
   *
   * @return
   *   A string with the content from the field.
   */
  public function getSubject($langcode = LANGUAGE_NONE, $options = array()) {
    return $this->subject;
  }  

  /**
   * Retrieves the configured mail body in a certain language.
   *
   * @param $langcode
   *   The language code of the Mail Body field, the content should be
   *   extracted from.
   * @param $options
   *   Array of options to pass to the metadata-wrapper:
   *   - 'field name': The name of the Mail Body field, the content should be
   *     extracted from.
   *   - 'sanitize': Indicate if text should be escaped.
   *
   * @return
   *   A string with the content from the field.
   */
  public function getMailBodyPlain($langcode = LANGUAGE_NONE, $options = array()) {
    // Set default values.
    $options += array(
        // As the text is already sanitized, it does not really matter if we
        // enable sanitizing, as it would be default. However, one can change the
        // field instance (e.g. to have no text processing) we make sure we still
        // properly sanitize the value.
        'sanitize' => TRUE,
        // The field name from which the text should be extracted.
        'field name' => ENTITY_EMAIL_FIELD_MAIL_BODY_PLAIN,
        // Determine if the text of just a single delta should be returned.
        'partials' => FALSE,
        'partial delta' => 0,
    );

    $field_name = ENTITY_EMAIL_FIELD_MAIL_BODY_PLAIN;

    if (!$field = field_info_field($field_name)) {
      throw new Exception(format_string('Field %field does not exist.', array('%field' => $field_name)));
    }

    if (empty($field['settings']['entity_email_text'])) {
      throw new Exception(format_string('Field %field is not a entity_email_mail_body.', array('%field' => $field_name)));
    }

    $wrapper = entity_metadata_wrapper('entity_email_type', $this);

    if (empty($langcode) && module_exists('locale')) {
      // Get the langcode from the current language.
      global $language;
      $langcode = $language->language;
    }

    // Let the metadata wrapper deal with the language.
    $value_wrapper = $wrapper->language($langcode)->$options['field name'];

    $property_item = $value_wrapper->value($options);

    return $property_item;
  }
  
  /**
   * Retrieves the configured mail body in a certain language.
   *
   * @param $langcode
   *   The language code of the Mail Body field, the content should be
   *   extracted from.
   * @param $options
   *   Array of options to pass to the metadata-wrapper:
   *   - 'field name': The name of the Mail Body field, the content should be
   *     extracted from.
   *   - 'sanitize': Indicate if text should be escaped.
   *
   * @return
   *   A string with the content from the field.
   */
  public function getMailBody($langcode = LANGUAGE_NONE, $options = array()) {
    // Set default values.
    $options += array(
        // As the text is already sanitized, it does not really matter if we
        // enable sanitizing, as it would be default. However, one can change the
        // field instance (e.g. to have no text processing) we make sure we still
        // properly sanitize the value.
        'sanitize' => TRUE,
        // The field name from which the text should be extracted.
        'field name' => ENTITY_EMAIL_FIELD_MAIL_BODY,
        // Determine if the text of just a single delta should be returned.
        'partials' => FALSE,
        'partial delta' => 0,
    );

    $field_name = ENTITY_EMAIL_FIELD_MAIL_BODY;

    if (!$field = field_info_field($field_name)) {
      throw new Exception(format_string('Field %field does not exist.', array('%field' => $field_name)));
    }

    if (empty($field['settings']['entity_email_text'])) {
      throw new Exception(format_string('Field %field is not a entity_email_mail_body.', array('%field' => $field_name)));
    }

    $property = entity_metadata_wrapper('entity_email_type', $this);

    if (empty($langcode) && module_exists('locale')) {
      // Get the langcode from the current language.
      global $language;
      $langcode = $language->language;
    }

    // Let the metadata wrapper deal with the language.
    $property = $property->language($langcode)->$options['field name'];
    $property_item = $property->value($options);

    return $property_item['value'];
  }
  
  /**
   * Retrieves the configured mail body in a certain language.
   *
   * @param $langcode
   *   The language code of the Mail Body field, the content should be
   *   extracted from.
   * @param $options
   *   Array of options to pass to the metadata-wrapper:
   *   - 'field name': The name of the Mail Body field, the content should be
   *     extracted from.
   *   - 'sanitize': Indicate if text should be escaped.
   *
   * @return
   *   A string with the content from the field.
   */
  public function getAttachments($langcode = LANGUAGE_NONE, $options = array()) {
    $options += array(
        // As the text is already sanitized, it does not really matter if we
        // enable sanitizing, as it would be default. However, one can change the
        // field instance (e.g. to have no text processing) we make sure we still
        // properly sanitize the value.
        'sanitize' => TRUE,
        // The field name from which the text should be extracted.
        'field name' => ENTITY_EMAIL_FIELD_MAIL_ATTACHEMENT,
        // Determine if the text of just a single delta should be returned.
        'partials' => FALSE,
        'partial delta' => 0,
    );

    $field_name = ENTITY_EMAIL_FIELD_MAIL_ATTACHEMENT;

    if (!$field = field_info_field($field_name)) {
      throw new Exception(format_string('Field %field does not exist.', array('%field' => $field_name)));
    }

    if (empty($field['settings']['entity_email_file'])) {
      throw new Exception(format_string('Field %field is not a entity_email_mail_body.', array('%field' => $field_name)));
    }

    $property = entity_metadata_wrapper('entity_email_type', $this);

    if (empty($langcode) && module_exists('locale')) {
      // Get the langcode from the current language.
      global $language;
      $langcode = $language->language;
    }

    // Let the metadata wrapper deal with the language.
    $property = $property->language($langcode)->$options['field name'];
    $property_items = $property->value($options);

    return $property_items;
  }  

  public function save() {
    if (isset($this->is_new) && $this->is_new) {
      $this->created = REQUEST_TIME;
    }
    $this->updated = REQUEST_TIME;

    parent::save();
    // Clear the entity property info cache, as changed argument-keys result
    // in different entity property info.
    entity_property_info_cache_clear();

    // Clear the field info cache, so extra fields info is purged.
    _field_info_collate_fields(TRUE);
  }

  protected function defaultUri() {
    return array('path' => 'admin/structure/entity_email_type/manage/' . $this->name);
  }

}
