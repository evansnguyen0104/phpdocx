<?php

/**
 * Inserts a simple table into the Word document.
 *
 * @category   Phpdocx
 * @package    examples
 * @subpackage easy
 * @copyright  Copyright (c) 2009-2013 Narcea Producciones Multimedia S.L.
 *             (http://www.2mdc.com)
 * @license    http://www.phpdocx.com/wp-content/themes/lightword/pro_license.php
 * @version    2012.12.26
 * @link       http://www.phpdocx.com
 * @since      File available since Release 1.8
 */
require_once '../../classes/CreateDocx.inc';

$docx = new CreateDocx();

$valuesTable = array(
    array(
        11,
        12
    ),
    array(
        21,
        22
    ),
);

$paramsTable = array(
    'border' => 'single',
    'border_sz' => 20
);


$docx->addTable($valuesTable, $paramsTable);

$docx->addText('Now we are going to insert table within tables:');

$valuesTable = array(
    array(
        a,
        b
    ),
    array(
        c,
        d
    ),
);

$paramsTable = array(
    'border' => 'single',
    'border_sz' => 5,
    'rawWordML' => true
);


$docx->addTable($valuesTable, $paramsTable);

$TABLEdata = $docx->addTable($valuesTable, $paramsTable);;

$fragment = $docx->createWordMLFragment($TABLEdata);

$valuesTable = array(
    array(
        11,
        $fragment
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

$docx->createDocx('../docx/example_table');