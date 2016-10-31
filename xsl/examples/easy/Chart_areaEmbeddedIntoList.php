<?php

/**
 * Inserts a 3D area chart with a table embedded in a list into a Word document.
 *
 * @category   Phpdocx
 * @package    examples
 * @subpackage easy
 * @copyright  Copyright (c) 2009-2013 Narcea Producciones Multimedia S.L.
 *             (http://www.2mdc.com)
 * @license    http://www.phpdocx.com/wp-content/themes/lightword/pro_license.php
 * @version    2012.12.26
 * @link       http://www.phpdocx.com
 * @since      File available since Release 2.7
 */
require_once '../../classes/CreateDocx.inc';

$docx = new CreateDocx();


$completedData = array(
    'legend' => array('data 1', 'data 2', 'data 3'),
    'data 1' => array('10', 0, 5),
    'data 2' => array('20', 60, 3),
    'data 3' => array('50', 33, 7),
    'data 4' => array('25', 0, 0)
);

$paramsChart = array(
    'data' => $completedData,
    'type' => 'area3DChart',
    'title' => 'Area 3D Chart with simple data and legends',
    'color' => '5',
    'perspective' => '30',
    'rotX' => '30',
    'rotY' => '30',
    'font' => 'Arial',
    'jc' => 'right',
    'showtable' => 0,
    'textWrap' => '4',
    'sizeX' => '10',
    'sizeY' => '20',
    'legendPos' => 't',
    'legendOverlay' => '0',
    'border' => '1',
    'haxLabelDisplay' => 'horizontal',
    'vaxLabelDisplay' => 'horizontal',
    'hgrid' => '1',
    'vgrid' => '3',
);

$paramsChart['title'] ='Area 3D Chart embedded in a list';
$chart = $docx->addElement('addGraphic', $paramsChart);
$valuesList = array(
    'area 1',
    $chart,
    'area 2',
    'area 3',
);
$paramsList = array('val' => 1);
$docx->addList($valuesList, $paramsList);

$docx->createDocx('../docx/example_chart_area3d_list');