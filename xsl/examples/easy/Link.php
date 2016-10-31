<?php

/**
 * Insert a link into a Word document.
 *
 * @category   Phpdocx
 * @package    examples
 * @subpackage easy
 * @copyright  Copyright (c) 2009-2013 Narcea Producciones Multimedia S.L.
 *             (http://www.2mdc.com)
 * @license    http://www.phpdocx.com/wp-content/themes/lightword/pro_license.php
 * @version    2012.12.26
 * @link       http://www.phpdocx.com
 * @since      2012.12.26
 */
require_once '../../classes/CreateDocx.inc';

$docx = new CreateDocx();

$docx->addLink('Link to Google', array('url'=> 'http://www.google.es', 'font' => 'Arial', 'color' => 'blue', 'u' => 'single'));

$docx->addText('We are now going to insert the link in a table cell:');

$LINKdata = $docx->addLink('Link to Google', array('url'=> 'http://www.google.es', 'font' => 'Arial', 'color' => 'blue', 'u' => 'single', 'rawWordML' => true));

$fragment = $docx->createWordMLFragment($LINKdata);

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

$docx->createDocx('../docx/example_link');