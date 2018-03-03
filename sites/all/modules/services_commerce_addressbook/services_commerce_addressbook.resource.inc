<?php

/**
 * Determines whether the current user can access to a resource.
 *
 * @param string $permission
 *   String indicating which permission to check access for.
 *
 * @return boolean
 *   Boolean indicating whether or not the user has access to the resource.
 *
 * @see user_access()
 */
function _services_commerce_addressbook_reosource_access($permission) {
  return user_access($permission);
}

function services_commerce_addressbook_create(){
  module_load_include('inc', 'commerce_addressbook', 'commerce_addressbook.user');
  global $user;

  $profile = new stdClass();
  $profile->type = 'shipping';
  $profile->uid = '1';
  $profile->status = '1';

  // Address field
  $profile->field_commerce_customer_address['und'][0]['province'] = "30";
  $profile->field_commerce_customer_address['und'][0]['city'] = '367';
  $profile->field_commerce_customer_address['und'][0]['county'] = '3100';
  $profile->field_address['und'][0] = "详细地址10";
  $profile->field_postcode['und'][0] = '邮编10';
  $profile->field_consignee['und'][0] = "收货人10";
  $profile->field_consignee_mobile['und'][0] = "手机号10";
  $profile->field_consignee_phone['und'][0] = "电话10";
  $profile->field_consignee_email['und'][0] = "邮箱10";

  commerce_customer_profile_save($profile);
}
/**
 * @see country_get_list()
 */
function services_commerce_addressbook_country_get_list() {
  include_once DRUPAL_ROOT . '/includes/locale.inc';
  return country_get_list();
}

/**
 * @see addressfield_get_address_format()
 */
function services_commerce_addressbook_get_address_format($country_code) {
  module_load_include('inc', 'addressfield', 'addressfield.address_formats');
  return addressfield_get_address_format($country_code);
}

/**
 * @see addressfield_get_administrative_areas()
 */
function services_commerce_addressbook_get_administrative_areas($country_code) {
  module_load_include('inc', 'addressfield', 'addressfield.administrative_areas');
  return addressfield_get_administrative_areas($country_code);
}

/**
 * @see services_commerce_addressbook_get_address_format()
 * @see services_commerce_addressbook_get_administrative_areas()
 */
function services_commerce_addressbook_get_address_format_and_administrative_areas($country_code) {
  $result = new stdClass();
  $result->address_format = services_commerce_addressbook_get_address_format($country_code);
  $result->administrative_areas = services_commerce_addressbook_get_administrative_areas($country_code);
  return $result;
  /*return = array(
    'address_format' => services_commerce_addressbook_get_address_format($country_code),
    'administrative_areas' => services_commerce_addressbook_get_administrative_areas($country_code)
  );*/
}

