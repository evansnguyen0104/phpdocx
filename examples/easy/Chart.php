<?php

/**
 * Insert a 3D pie chart into a Word document.
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

$legends = array(
    'legend1' => array(10),
    'legend2' => array(20),
    'legend3' => array(40)
);

$paramsChart = array(
    'data' => $legends,
    'type' => 'pie3DChart',
    'title' => 'Title',
    'rotX' => 20, 
    'rotY' => 20,
    'perspective' => 30,
    'color' => 2,
    'textWrap' => 0,
    'sizeX' => 10,
    'sizeY' => 10,
    'jc' => 'right',
    'showPercent' => 1,
    'font' => 'Times New Roman'
);
$docx->addChart($paramsChart);

$docx->addText('Now we are going to insert the same chart in a table cell:');

$paramsChart = array(
    'data' => $legends,
    'type' => 'pie3DChart',
    'title' => 'Title',
    'rotX' => 20, 
    'rotY' => 20,
    'perspective' => 30,
    'color' => 2,
    'textWrap' => 0,
    'sizeX' => 10,
    'sizeY' => 10,
    'showPercent' => 1,
    'font' => 'Times New Roman',
    'rawWordML' => true
);

$CHARTdata = $docx->addChart($paramsChart);

$fragment = $docx->createWordMLFragment(array($CHARTdata));

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

$docx->createDocx('../docx/example_chart');
