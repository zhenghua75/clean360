<?php

function _services_commerce_customer_profile_reosource_access() {
  return TRUE;
}

function _services_commerce_customer_profile_retrieve($id) {
  $query = db_select('commerce_addressbook_defaults', 'addressbook');
  $query->fields('addressbook', array('profile_id'));

  $query->condition('addressbook.uid',$id);

  $query->fields('profile', array('profile_id'));
  $query -> leftJoin('commerce_customer_profile','profile', 'addressbook.profile_id=profile.profile_id');

  $query->condition('profile.status', 1);
  $query->condition('profile.type', 'shipping');
  $result = $query->execute()->fetchField(0);

  $query = db_select('china_address', 'china_address');
  $query->fields('china_address', array('region_id','parent_id','region_name','region_type'));
  $result1 = $query->execute()->fetchAll();

  $commerce_customer_profile = commerce_customer_profile_load($result);

  $commerce_customer_profile->field_commerce_customer_address['zh-hans'][0]['regions']=$result1;

  return $commerce_customer_profile;
}

function _services_commerce_customer_profile_create($data){
  $profile = new stdClass();
  //$profile->profile_id = $data['profile_id'];
  $profile->uid= $data['uid'];
  //$profile->created = $data['created'];
  //$profile->revision_id =$data['revision_id'];
  $profile->type='shipping';
  $profile->data=FALSE;
  $profile->status=1;

  $profile->field_commerce_customer_address = array('zh-hans' =>array(0=>array(
    'province'=>$data['field_commerce_customer_address']['zh-hans'][0]['value']['province'],
    'city'=>$data['field_commerce_customer_address']['zh-hans'][0]['value']['city'],
    'county'=>$data['field_commerce_customer_address']['zh-hans'][0]['value']['county'],
    'detail'=>NULL
    )));

  $profile->field_address=array('zh-hans'=>array(0=>array(
    'value'=>$data['field_address']['zh-hans'][0]['value'],
    'format'=>NULL,
    'safe_value'=>$data['field_address']['zh-hans'][0]['value']
    )));

  $profile->field_postcode=array('zh-hans'=>array(0=>array(
    'value' =>$data['field_postcode']['zh-hans'][0]['value'],
    'format'=>NULL,
    'safe_value' =>$data['field_postcode']['zh-hans'][0]['value']
    )));

  $profile->field_consignee=array('zh-hans'=>array(0=>array(
    'value'=>$data['field_consignee']['zh-hans'][0]['value'],
    'format'=>NULL,
    'safe_value'=>$data['field_consignee']['zh-hans'][0]['value']
    )));

  $profile->field_consignee_mobile=array('zh-hans'=>array(0=>array(
    'value' =>$data['field_consignee_mobile']['zh-hans'][0]['value'],
    //'format'=>NULL,
    //'safe_value' =>$data['field_consignee_mobile']['zh-hans'][0]['value']
    )));

  $profile->field_consignee_phone=array('zh-hans'=>array(0=>array(
    'value'=>$data['field_consignee_phone']['zh-hans'][0]['value'],
    //'format'=>NULL,
    //'safe_value'=>$data['field_consignee_phone']['zh-hans'][0]['value']
    )));

  $profile->field_consignee_email=array('zh-hans'=>array(0=>array(
    'email'=>$data['field_consignee_email']['zh-hans'][0]['value'],
    //'format'=>NULL,
    //'safe_value'=>$data['field_consignee_email']['zh-hans'][0]['value']
    )));

  return commerce_customer_profile_save($profile);

}

function _services_commerce_customer_profile_update($profile_id, $data){
  $profile = new stdClass();
  $profile->profile_id = $data['profile_id'];
  $profile->uid= $data['uid'];
  $profile->created = $data['created'];
  $profile->revision_id =$data['revision_id'];
  $profile->type='shipping';
  $profile->data=FALSE;
  $profile->status=1;

  $profile->field_commerce_customer_address = array('zh-hans' =>array(0=>array(
    'province'=>$data['field_commerce_customer_address']['zh-hans'][0]['value']['province'],
    'city'=>$data['field_commerce_customer_address']['zh-hans'][0]['value']['city'],
    'county'=>$data['field_commerce_customer_address']['zh-hans'][0]['value']['county'],
    'detail'=>NULL
    )));

  $profile->field_address=array('zh-hans'=>array(0=>array(
    'value'=>$data['field_address']['zh-hans'][0]['value'],
    'format'=>NULL,
    'safe_value'=>$data['field_address']['zh-hans'][0]['value']
    )));

  $profile->field_postcode=array('zh-hans'=>array(0=>array(
    'value' =>$data['field_postcode']['zh-hans'][0]['value'],
    'format'=>NULL,
    'safe_value' =>$data['field_postcode']['zh-hans'][0]['value']
    )));

  $profile->field_consignee=array('zh-hans'=>array(0=>array(
    'value'=>$data['field_consignee']['zh-hans'][0]['value'],
    'format'=>NULL,
    'safe_value'=>$data['field_consignee']['zh-hans'][0]['value']
    )));

  $profile->field_consignee_mobile=array('zh-hans'=>array(0=>array(
    'value' =>$data['field_consignee_mobile']['zh-hans'][0]['value'],
    //'format'=>NULL,
    //'safe_value' =>$data['field_consignee_mobile']['zh-hans'][0]['value']
    )));

  $profile->field_consignee_phone=array('zh-hans'=>array(0=>array(
    'value'=>$data['field_consignee_phone']['zh-hans'][0]['value'],
    //'format'=>NULL,
    //'safe_value'=>$data['field_consignee_phone']['zh-hans'][0]['value']
    )));

  $profile->field_consignee_email=array('zh-hans'=>array(0=>array(
    'email'=>$data['field_consignee_email']['zh-hans'][0]['value'],
    //'format'=>NULL,
    //'safe_value'=>$data['field_consignee_email']['zh-hans'][0]['value']
    )));

  return commerce_customer_profile_save($profile);

  // $return = new stdClass();
  // $return->profile_id='';
  // return $return;
}