<?php

/**
 * Creates a paragraph style and and inserts a text with that same style via de addText method.
 *
 * @category   Phpdocx
 * @package    examples
 * @subpackage easy
 * @copyright  Copyright (c) 2009-2013 Narcea Producciones Multimedia S.L.
 *             (http://www.2mdc.com)
 * @license    http://www.phpdocx.com/wp-content/themes/lightword/pro_license.php
 * @version    2013.09.06
 * @link       http://www.phpdocx.com
 * @since      File available since Release 3.4
 */
require_once '../../classes/CreateDocx.inc';

$docx = new CreateDocx();
//Style options
$style = array(
	'color' => '999999',//text color
	'border' => 'on',
	'border-color' => '990000',
	'border-width' => 12,
	'indent_left' => 920
	);
//Create custom style
$docx->createParagraphStyle('myStyle', $style);
$text= 'A paragraph in grey color with a thick red border and a big left indentation.';
$docx->addText($text, array('pStyle' => 'myStyle'));
$docx->createDocx('../docx/example_paragraphstyle');