<?php

function _services_china_address_field_reosource_access() {
  return TRUE;
}

function services_china_address_field_region($id){
	$query = db_select('china_address', 'china_address');
  	$query->fields('china_address', array('region_id','parent_id','region_name'));

  	//$query->condition('china_address.parent_id',$id);

  	$result = $query->execute()->fetchAll();

	return $result;//entity_load('china_address', array($result), array(), FALSE);
}
