<?php

function services_china_address_field_services_resources() {
  $resources = array(
    'china_address' => array(
        'retrieve' => array(
          'help' => t('services for china address field to retrieve region.'),
          'file' => array(
            'type' => 'inc',
            'module' => 'services_china_address_field',
            'name' => 'services_china_address_field.resource',
          ),
          'callback' => 'services_china_address_field_region',
          'access callback' => '_services_china_address_field_reosource_access',
           'args' => array(
             array(
               'name' => 'id',
               'type' => 'int',
               'description' => 'The id of the regon to get',
               'source' => array('path' => '0'),
               'optional' => FALSE,
             ),
             ),
        ),
    ),
  );
  return $resources;
}

