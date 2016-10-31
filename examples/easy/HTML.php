<?php

/**
 * Add HTML code to a Word document.
 *
 * @category   Phpdocx
 * @package    examples
 * @subpackage easy
 * @copyright  Copyright (c) 2009-2013 Narcea Producciones Multimedia S.L.
 *             (http://www.2mdc.com)
 * @license    http://www.phpdocx.com/wp-content/themes/lightword/pro_license.php
 * @version    2012.12.26
 * @link       http://www.phpdocx.com
 * @since      File available since Release 2.3
 */
require_once '../../classes/CreateDocx.inc';

$docx = new CreateDocx();

$docx->addText('HTML content');

$html= '<p><strong>PHPDOCX</strong> is a PHP library designed to generate completely dynamic and fully customizable Word documents.</p>';

$docx->addHTML(array('html' => $html));

$docx->addText('End HTML content');

$docx->addText('We are now going to insert the HTML content in a table cell:');

$HTMLdata = $docx->addHTML(array('html' => $html, 'rawWordML' => true));

$fragment = $docx->createWordMLFragment(array($HTMLdata));

$valuesTable = array(
    array(
        11,
        12
    ),
    array(
        $fragment,
        22
    ),
);

$paramsTable = array(
    'border' => 'single',
    'border_sz' => 5,
);

$test = $docx->addTable($valuesTable, $paramsTable);

$docx->createDocx('../docx/example_html');