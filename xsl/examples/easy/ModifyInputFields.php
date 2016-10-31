<?php

/**
 * Set the values of the input fields.
 *
 * @category   Phpdocx
 * @package    examples
 * @subpackage easy
 * @copyright  Copyright (c) 2009-2013 Narcea Producciones Multimedia S.L.
 *             (http://www.2mdc.com)
 * @license    http://www.phpdocx.com/wp-content/themes/lightword/pro_license.php
 * @version    2013.12.26
 * @link       http://www.phpdocx.com
 * @since      2013.12.26
 */
require_once '../../classes/CreateDocx.inc';

$docx = new CreateDocx();
$docx->addTemplate('../files/inputFields.docx');

$data = array(
	'textfield_1' => 'first',
	'textfield_2' => 'second',
	'sdt_1' => 'third',
	'sdt_2' => 'fourth'
	);

$docx->modifyInputFields($data);


$docx->createDocx('../docx/inputFields');