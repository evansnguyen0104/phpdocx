<?php

/**
 * Adds page borders to the Word document.
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
$options = array(
	'border-width' => 48,
	'border-top-color' => 'FF0000'
);
$docx->addPageBorders($options);
$text= 'This is just a chunk of text that we will repeat couple of times to fill up some space. ';
$text .= $text;
$docx->addText($text);
$docx->addText('Another chunk of text');
$docx->addText($text);
$docx->createDocx('../docx/example_pageborders');