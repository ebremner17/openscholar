<?php
/**
 * @file
 * os_orcid.form.inc
 */

/**
* Form builder; Import and/or Update the ORCID based on the orcid_id.
*/
function _os_orcid_manage_orcid($form_state) {

    // Get the orcid_id if there is one for the virtual site user.
    $orcid_id = db_select('os_orcid_id', 'oid')
        ->fields('oid')
        ->condition('oid.uid', _os_orcid_get_vsite_user_id())
        ->execute()
        ->fetchAll();

    $form['orcid']['#id'] = 'orcid';
    $form['orcid']['#title'] = 'ORCID Information';
    $form['orcid']['#weight'] = -200;
    $form['orcid']['#type'] = 'fieldset';

    $form['orcid']['orcid_id']['#type'] = 'textfield';
    $form['orcid']['orcid_id']['#title'] = 'ORCID ID';
    $form['orcid']['orcid_id']['#size'] = 40;
    $form['orcid']['orcid_id']['#maxlength'] = 255;

    // If there is an orcid_id, set it on the form.
    if(count($orcid_id) > 0) {
        $form['orcid']['orcid_id']['#default_value'] = $orcid_id[0]->orcid_id;
    }
    else {
        $form['orcid']['orcid_id']['#default_value'] = '';
    }

    $form['orcid']['orcid_id']['#description'] = 'Enter your ORCID ID, It is in the format XXXX-XXXX-XXXX-XXXX and is available at <a href="http://orcid.org">http://orcid.org</a>.  When this is set, your publication information will be imported to your site.';

    $form['#validate'][] = '_os_orchid_validate';

    $form['submit'] = array(
        '#type' => 'submit',
        '#value' => 'Submit',
    );

    return $form;
}

/**
 * Helper function to validate orcid id
 */
function _os_orchid_validate($form, &$form_state) {
    if(isset($form['orcid']['orcid_id']['#value'])) {
        if(!preg_match('/[0-9]{4}-[0-9]{4}-[0-9]{4}-[0-9]{4}/', $form['orcid']['orcid_id']['#value'])) {
            form_set_error('orchid_id', 'Your orcid id must match the pattern XXXX-XXXX-XXXX-XXXX.');
        }
    }
}
