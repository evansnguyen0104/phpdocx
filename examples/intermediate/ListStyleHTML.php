<?php

/**
 * Creates a custom style to be used in combination with CSS styles within the embedHTML method.
 *
 * @category   Phpdocx
 * @package    examples
 * @subpackage intermediate
 * @copyright  Copyright (c) 2009-2013 Narcea Producciones Multimedia S.L.
 *             (http://www.2mdc.com)
 * @license    http://www.phpdocx.com/wp-content/themes/lightword/pro_license.php
 * @version    2013.08.26
 * @link       http://www.phpdocx.com
 * @since      2013.08.26
 */

require_once('../../classes/CreateDocx.inc');

$docx = new CreateDocx();
//Custom options
$latinListOptions = array();
$latinListOptions[0]['type'] = 'lowerLetter';
$latinListOptions[0]['format'] = '%1.';
$latinListOptions[1]['type'] = 'lowerRoman';
$latinListOptions[1]['format'] = '%1.%2.';
//Create the list style with name: latin
$docx->createListStyle('latin', $latinListOptions);
//HTML
$html = '<ul class="latin"><li>item 1 <ul><li>subitem 1.1</li><li>subitem 1.2</li></ul></li><li>item 2</li></ul>';
//Insert HTML into the Word document using the custom latin list style
$docx->embedHTML($html, array('customListStyles' => true));
//Save the Word document
$docx->createDocx('../docx/example_createListStyleHTML');