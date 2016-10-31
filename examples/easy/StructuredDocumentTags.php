<?php

/**
 * Inserts structured document tags (combo box, date picker, dropdown menu and rich text box) into a Word document.
 *
 * @category   Phpdocx
 * @package    examples
 * @subpackage advanced
 * @copyright  Copyright (c) 2009-2013 Narcea Producciones Multimedia S.L.
 *             (http://www.2mdc.com)
 * @license    http://www.phpdocx.com/wp-content/themes/lightword/pro_license.php
 * @version    2013.02.28
 * @link       http://www.phpdocx.com
 * @since      2013.02.28
 */

require_once '../../classes/CreateDocx.inc';

$docx = new CreateDocx();

//Combo box
$list = array(array('First Choice', 1),array('second choice', 2),array('Third choice', 3));
$docx->addStructuredDocumentTag('comboBox', array('listItems' => $list, 'placeholderText' => 'Choose a value or write it down', 'alias' => 'Combo Box', 'sz' => 14, 'i' => 'on', 'color' => 'FF0000', 'b' => 'on', 'u' => 'double', 'font' => 'Algerian'));
//date
$docx->addStructuredDocumentTag('date', array('placeholderText' => 'Choose a date', 'alias' => 'Date picker', 'sz' => 12, 'i' => 'on', 'color' => '777777', 'b' => 'on', 'font' => 'Calibri'));
//dropdown
$list = array(array('One', 1),array('Two', 2),array('Three', 3));
$docx->addStructuredDocumentTag('comboBox', array('listItems' => $list, 'placeholderText' => 'Choose a value', 'alias' => 'Dropdown menu', 'sz' => 12));
//richText
$docx->addStructuredDocumentTag('richText', array('listItems' => $list, 'placeholderText' => 'This text is locked', 'alias' => 'Rich text', 'sz' => 11, 'i' => 'on', 'color' => 'FF0000', 'b' => 'on', 'lock' => 'contentLocked'));

$docx->createDocx('../docx/example_structured_document_tags');
