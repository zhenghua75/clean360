<?php

/**
 * @file
 * Module to provide themed package tracking information.
 *
 * Operates by defining a hook, hook_uc_tracking(), that shipping modules
 * need to implement.  hook_uc_tracking() implementations take the tracking
 * number as the sole argument and return an associative array of strings
 * containing tracking details for that tracking number.  This array is
 * expected to be in the following form:
 *
 * $details['tracking_number']
 * $details['carrier'] - same string as shipping method key
 * $details['status']
 * $details['event'][#]['type']
 * $details['event'][#]['date']
 * $details['event'][#]['time']
 * $details['event'][#]['location']
 *
 * The theme_uc_tracking_detail() function allows easy themeing of the
 * tracking results.
 *
 * @author Tim Rohaly.    <http://drupal.org/user/202830>
 */

/**
 * @addtogroup hooks
 * @{
 */


/******************************************************************************
 * hook_uc_tracking() implementations.  These functions should really be
 * moved to be in the corresponding shipping modules, but until then they're
 * provided here to accomplish the task.
 *****************************************************************************/


/**
 * Implements hook_uc_tracking().
 *
 * @param $tracking_number
 *   USPS Tracking Number.
 *
 * @return $detail
 *   Array containing tracking details ready for themeing.
 */
function hook_uc_tracking($tracking_number) {

  $usps_server    = 'production.shippingapis.com';
  $api_dll        = 'ShippingAPI.dll';
  $connection_url = 'http://' . $usps_server . '/' . $api_dll;

  $request  = '<TrackFieldRequest USERID="' . variable_get('uc_usps_user_id', '') . '">';
  $request .= '<TrackID ID="' . $tracking_number . '"></TrackID>';
  $request .= '</TrackFieldRequest>';
  $request  = 'API=TrackV2&XML=' . urlencode($request);

  $connection_url = $connection_url . '?' . $request;

  $result = drupal_http_request($connection_url, array('method' => 'GET'));
  $response = new SimpleXMLElement($result->data);

  $details = array();
  $details['carrier'] = 'U.S.P.S.';
  $details['tracking_number'] = $tracking_number;

  // Check to see if tracking request failed
  if (strtolower($response->Name) == 'error') {
    drupal_set_message(t('USPS has encountered an error processing your tracking requst.'), 'error');
    $details['status'] = 'ERROR';
    return $details;
  }

  foreach ($response->TrackInfo as $info) {
    if (isset($info->Error)) {
      drupal_set_message(t('USPS has no record of this item. Please verify your information and try again later.'), 'error');
      $details['status'] = 'ERROR';
      return $details;
    }

    $details['status'] = $info->TrackSummary->Event;

    $temp = array();
    $temp['time'] = $info->TrackSummary->EventTime;
    $temp['date'] = $info->TrackSummary->EventDate;
    $temp['type'] = $info->TrackSummary->Event;
    if ($info->TrackSummary->EventCity != '') {
      $temp['location'] = $info->TrackSummary->EventCity;
      if ($info->TrackSummary->EventState != '') {
        $temp['location'] = $temp['location'] . ', ' . $info->TrackSummary->EventState;
        }
    }
    else {
      $temp['location'] = $info->TrackSummary->EventCountry;
    }

    $details['event'][] = $temp;
    foreach ($info->TrackDetail as $detail) {
      $temp['time'] = $detail->EventTime;
      $temp['date'] = $detail->EventDate;
      $temp['type'] = $detail->Event;
      if ($detail->EventCity != '') {
        $temp['location'] = $detail->EventCity;
        if ($detail->EventState != '') {
          $temp['location'] = $temp['location'] . ', ' . $detail->EventState;
          }
      }
      else {
        $temp['location'] = $detail->EventCountry;
      }
      $details['event'][] = $temp;
    }
  }

  return $details;
}


/**
 * Implements hook_uc_tracking().
 *
 * @param $tracking_number
 *   FedEx Tracking Number.
 *
 * @return
 *   Array containing tracking details ready for themeing.
 */
function uc_fedex_uc_tracking($tracking_number) {
  // Set up SOAP call.
  //  Allow tracing so details of request can be retrieved for error logging
  $client = new SoapClient(drupal_get_path('module', 'uc_fedex')
              . '/wsdl-' . variable_get('uc_fedex_server_role', 'testing')
              . '/TrackService_v4.wsdl', array('trace' => 1));

  // FedEx user key and password filled in by user on admin form
  $request['WebAuthenticationDetail'] = array(
    'UserCredential' => array(
      'Key'      => variable_get('uc_fedex_user_credential_key', 0),
      'Password' => variable_get('uc_fedex_user_credential_password', 0),
    )
  );

  // FedEx account and meter number filled in by user on admin form
  $request['ClientDetail'] = array(
      'AccountNumber' => variable_get('uc_fedex_account_number', 0),
      'MeterNumber'   => variable_get('uc_fedex_meter_number', 0),
  );

  // Optional parameter, contains anything
  $request['TransactionDetail'] = array(
    'CustomerTransactionId' => '*** Track Service Request v4 from Ubercart ***'
  );

  // Track Request v4.0.0
  $request['Version'] = array(
    'ServiceId'    => 'trck',
    'Major'        => '4',
    'Intermediate' => '0',
    'Minor'        => '0',
  );

  // Tracking Number
  $request['PackageIdentifier'] = array(
    'Value' => $tracking_number,
    'Type'  => 'TRACKING_NUMBER_OR_DOORTAG',
  );

  // Include Details
  $request['IncludeDetailedScans'] = TRUE;

  //
  // Send the SOAP request to the FedEx server
  //
  try {
    $response = $client->track($request);

    $details = array();
    $details['carrier'] = 'FedEx';
    $details['tracking_number'] = $tracking_number;

    if ($response->HighestSeverity != 'FAILURE' &&
        $response->HighestSeverity != 'ERROR')     {

      $reply = $response->TrackDetails;

      $details['tracking_number'] = $reply->TrackingNumber;
      $details['status']          = $reply->StatusDescription;

      // Handle situation where only one 'Events' is present, in
      // which case SimpleXML returns an object instead of an array
      if (!is_array($reply->Events)) {
        $reply->Events = array($reply->Events);
      }

      // Iterate over Events
      foreach ($reply->Events as $event) {
        $temp  = array();
        $dtime = strtotime(str_replace('T', ' ', $event->Timestamp));
        //$temp['time']       = date('g:i a', $dtime);
        $temp['time']       = format_date($dtime, 'custom', 'g:i a');
        $temp['date']       = format_date($dtime, 'custom', 'F j, Y');
        $temp['type']       = $event->EventDescription;
        $temp['location']   = $event->Address->City . ', ' .
                              $event->Address->StateOrProvinceCode;
        // Location may be empty for initial scan
        if ($temp['location'] == ', ') {
          $temp['location'] = '';
        }
        $details['event'][] = $temp;
      }
    }
    else {
      drupal_set_message(t('Error in processing FedEx tracking transaction.'), 'error');
      foreach ($response->Notifications as $notification) {
        if (is_array($response->Notifications)) {
          drupal_set_message($notification->Severity . ': ' .
                             $notification->Message, 'error');
        }
        else {
          drupal_set_message($notification, 'error');
        }
      }
      $details['status'] = 'ERROR';
    }
    return $details;
  }
  catch (SoapFault $exception) {
    drupal_set_message('<h2>Fault</h2><br /><b>Code:</b>' . $exception->faultcode . '<br /><b>String:</b>' . $exception->faultstring . '<br />', 'error');
  }
}

/**
 * @} End of "addtogroup hooks".
 */
