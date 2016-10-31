<?php

/**
 * Create a DOCX file. Transform DOCX to PDF
 *
 * @category   Phpdocx
 * @package    examples
 * @subpackage easy
 * @copyright  Copyright (c) 2009-2013 Narcea Producciones Multimedia S.L.
 *             (http://www.2mdc.com)
 * @license    http://www.phpdocx.com/wp-content/themes/lightword/pro_license.php
 * @version    2012.12.26
 * @link       http://www.phpdocx.com
 * @since      File available since Release 2.5
 */
require_once '../../classes/TransformDocAdv.inc';

$docx = new CreateDocx();

$docx->enableCompatibilityMode();

$text = 'Lorem ipsum dolor sit amet, consectetur adipisicing elit, ' .
    'sed do eiusmod tempor incididunt ut labore et dolore magna aliqua. Ut ' .
    'enim ad minim veniam, quis nostrud exercitation ullamco laboris nisi ut' .
    'aliquip ex ea commodo consequat. Duis aute irure dolor in reprehenderit ' .
    'in voluptate velit esse cillum dolore eu fugiat nulla pariatur. ' .
    'Excepteur sint occaecat cupidatat non proident, sunt in culpa qui ' .
    'officia deserunt mollit anim id est laborum.';

$paramsText = array(
    'b' => 'single',
    'font' => 'Arial'
);

$docx->addText($text, $paramsText);

$docx->createDocx('example_text');

// using default method
$docx->transformDocx('example_text.docx', 'example_text.pdf');

// using default method without OdfConverter
//$docx->transformDocx('example_text.docx', 'example_text.pdf', null, array('odfconverter' => false));

// using an external script
//$docx->transformDocx('example_text.docx', 'example_text2.pdf', null, array('method' => 'script'));

// using an external script without OdfConverter
//$docx->transformDocx('example_text.docx', 'example_text3.pdf', null, array('method' => 'script', 'odfconverter' => false));
