<?php

 /**
 * Insert a surface chart into a Word document.
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

$completedData = array(
    'legend' => array('Serie 1', 'Serie 2', 'Serie 3'),
    'Categoría 1' => array('4.3', 2.4, 2),
    'Categoría 2' => array('2.5', 4.4, 2),
    'Categoría 3' => array('3.5', 1.8, 3),
    'Categoría 4' => array('4.5', 2.8, 5),
    'Categoría 5' => array('5', 2, 3)
);

$paramsChart = array(
    'data' => $completedData,
    'type' => 'surfaceChart',
    'legendPos' => 'r',
    'legendOverlay' => false,
    'sizeX' => 10, 
    'sizeY' => 10,
    'jc' => 'right',
    'color' => 2,
    'border' => 0,
    'hgrid' => 0,
    'vgrid' => 0,
    'font' => 'Times New Roman',   
    'showtable' => true
);
$docx->addChart($paramsChart);

$paramsChart = array(
    'data' => $completedData,
    'type' => 'surfaceChart',
    'legendPos' => 't',
    'legendOverlay' => true,
    'sizeX' => 10, 
    'sizeY' => 10,
    'border' => 1,
    'color' => 2,
    'jc' => 'center',
    'wireframe' => true,
    'hgrid' => 1,
    'vgrid' => 1,
    'font' => 'Arial',
);
$docx->addChart($paramsChart);

$paramsChart = array(
    'data' => $completedData,
    'type' => 'surface3DChart',
    'legendPos' => 'l',
    'sizeX' => 10, 
    'sizeY' => 10,
    'border' => 3,
    'color' => 3,
    'jc' => 'left',
    'wireframe' => true,
    'hgrid' => 2,
    'vgrid' => 2,
);
$docx->addChart($paramsChart);

$paramsChart = array(
    'data' => $completedData,
    'type' => 'surface3DChart',
    'legendPos' => 'b',
    'sizeX' => 10, 
    'sizeY' => 10,
    'color' => 4,
    'border' => 6,
    'wireframe' => false,
    'hgrid' => 3,
    'vgrid' => 3,
);
$docx->addChart($paramsChart);

$chart = $docx->addElement('addGraphic', $paramsChart);

$valuesList = array(
    'Line 1',
    $chart,
    'Line 2',
    'Line 3',
);
$paramsList = array('val' => 1);
$docx->addList($valuesList, $paramsList);

$docx->createDocx('../docx/example_chart_surface');