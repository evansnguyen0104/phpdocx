<?php

/**
 * Inserts form elements (textfield, checkbox and select) into a Word document.
 *
 * @category   Phpdocx
 * @package    examples
 * @subpackage easy
 * @copyright  Copyright (c) 2009-2013 Narcea Producciones Multimedia S.L.
 *             (http://www.2mdc.com)
 * @license    http://www.phpdocx.com/wp-content/themes/lightword/pro_license.php
 * @version    2013.02.28
 * @link       http://www.phpdocx.com
 * @since      2013.02.28
 */

require_once '../../classes/CreateDocx.inc';

$docx = new CreateDocx();
//Text field
$docx->addFormElement('textfield', array('sz' => 12, 'i' => 'on', 'color' => '0000CC', 'b' => 'on', 'font' => 'Arial', 'defaultValue' => 'This is a tst'));
//Checkbox
$docx->addFormElement('checkbox', array('sz' => 12, 'i' => 'on', 'color' => '555555', 'b' => 'on', 'font' => 'Calibri', 'defaultValue' => true));
//Select
$docx->addFormElement('select', array('selectOptions' => array('One', 'Two', 'Three', 'Four'), 'sz' => 14, 'i' => 'on', 'color' => 'c90000', 'b' => 'on', 'u' => 'double', 'font' => 'Algerian', 'defaultValue' => 2));

$docx->createDocx('../docx/example_form_element');
