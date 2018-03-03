<?php

function services_commerce_customer_profile_services_resources() {
  $resources = array(
    'commerce_customer_profile' => array(
      'operations' => array(
        'retrieve' => array(
          'help' => t('services for commerce customer profile to retrieve one.'),
          'file' => array(
            'type' => 'inc',
            'module' => 'services_commerce_customer_profile',
            'name' => 'services_commerce_customer_profile.resource',
          ),
          'callback' => '_services_commerce_customer_profile_retrieve',
          'access callback' => '_services_commerce_customer_profile_reosource_access',
          'args' => array(
             array(
               'name' => 'id',
               'type' => 'int',
               'description' => 'The id of the user to get',
               'source' => array('path' => '0'),
               'optional' => FALSE,
             ),
            ),
        ),
        'create' => array(
          'help' => t('services for commerce customer profile to create one.'),
          'file' => array(
            'type' => 'inc',
            'module' => 'services_commerce_customer_profile',
            'name' => 'services_commerce_customer_profile.resource',
          ),
          'callback' => '_services_commerce_customer_profile_create',
          'args' => array(
            array(
              'name'         => 'data',
              'type'         => 'array',
              'description'  => t('The commerce customer profile data to set on create.'),
              'source'       => 'data',
              'optional'     => FALSE,
            ),
          ),
          'access callback' => '_services_commerce_customer_profile_reosource_access',
        ),
        'update' => array(
          'help' => t('services for commerce customer profile to update one'),
          'file' => array(
            'type' => 'inc',
            'module' => 'services_commerce_customer_profile',
            'name' => 'services_commerce_customer_profile.resource',
          ),
          'callback' => '_services_commerce_customer_profile_update',
          'args' => array(
            array(
              'name' => 'profile_id',
              'type' => 'int',
              'description' => 'The commerce customer profile ID of the commerce customer profile to update.',
              'optional' => FALSE,
              'source' => array('path' => 0),
            ),
            array(
              'name'         => 'data',
              'type'         => 'array',
              'description'  => t('The commerce customer profile data to set on update.'),
              'source'       => 'data',
              'optional'     => FALSE,
            ),
          ),
          'access callback' => '_services_commerce_customer_profile_reosource_access',
        ),
      ),
    ),
  );
  return $resources;
}

