<?php

function services_commerce_addressbook_services_resources() {
  $resources = array(
    'services_commerce_addressbook' => array(
      'actions' => array(

        'create' => array(
          'help' => t('services fro commerce address book to create one.'),
          'file' => array(
            'type' => 'inc',
            'module' => 'services_commerce_addressbook',
            'name' => 'services_commerce_addressbook.resource',
          ),
          'callback' => 'services_commerce_addressbook_create',
          // 'access callback' => '_services_commerce_addressbook_resource_access',
          // 'access callback file' => array(
          //   'type' => 'inc',
          //   'module' => 'services_commerce_addressbook',
          //   'name' => 'services_commerce_addressbook.resource',
          // ),
          // 'access arguments' => array('access content'),
          // 'access arguments append' => TRUE,
        ),
        'update' => array(
          'help' => t('services for commerce address book to update one'),
          'file' => array(
            'type' => 'inc',
            'module' => 'services_commerce_addressbook',
            'name' => 'services_commerce_addressbook.resource',
          ),
          'callback' => 'services_commerce_addressbook_update',
          'args' => array(
            array(
              'name'         => 'country_code',
              'type'         => 'string',
              'description'  => t('The country code.'),
              'source'       => array('data' => 'country_code'),
              'optional'     => FALSE,
            ),
          ),
          'access callback' => '_services_commerce_addressbook_resource_access',
          'access callback file' => array(
            'type' => 'inc',
            'module' => 'services_commerce_addressbook',
            'name' => 'services_commerce_addressbook.resource',
          ),
          'access arguments' => array('access content'),
          'access arguments append' => TRUE,
        ),
        'delete' => array(
          'help' => t('services for commerce address book to delete on.'),
          'file' => array(
            'type' => 'inc',
            'module' => 'services_commerce_addressbook',
            'name' => 'services_commerce_addressbook.resource',
          ),
          'callback' => 'services_commerce_addressbook_delete',
          'args' => array(
            array(
              'name'         => 'country_code',
              'type'         => 'string',
              'description'  => t('The country code.'),
              'source'       => array('data' => 'country_code'),
              'optional'     => FALSE,
            ),
          ),
          'access callback' => '_services_commerce_addressbook_resource_access',
          'access callback file' => array(
            'type' => 'inc',
            'module' => 'services_commerce_addressbook',
            'name' => 'services_commerce_addressbook.resource',
          ),
          'access arguments' => array('access content'),
          'access arguments append' => TRUE,
        ),
      ),
    ),
  );
  return $resources;
}

