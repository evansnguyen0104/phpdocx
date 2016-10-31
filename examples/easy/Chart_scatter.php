<?php

/**
 * Insert a scatter chart into a Word document.
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
    array(10, 0),
    array(17, 2),
    array(18, 4),
    array(25, 6),
    array(30, 7),
    array(50, 10),
    array(35, 9),
);

$paramsChart = array(
    'data' => $completedData,
    'type' => 'scatterChart',    
    'border' => 1,
    'color' => 2,
    'jc' => 'center',
    'legendPos' => 'none',
    'legendOverlay' => true,
    'symbol' => 'line',//dot, line
    'showValue' => true,
    'hgrid' => 1,
    'vgrid' => 1,
    'smooth' => true
);
$docx->addChart($paramsChart);

$paramsChart = array(
    'data' => $completedData,
    'type' => 'scatterChart',    
    'border' => 2.25,
    'jc' => 'left',
    'color' => 3,
    'legendPos' => 'l',
    'font' => 'Calibri',
    'symbol' => 'line',//dot, line
    'smooth' => true,
    'showCategory' => true,
    'hgrid' => 2,
    'vgrid' => 2,
);
$docx->addChart($paramsChart);

$paramsChart = array(
    'data' => $completedData,
    'type' => 'scatterChart',    
    'border' => 6,
    'color' => 4,
    'legendPos' => 't',
    'font' => 'Arial',
    'symbol' => 'dot',//dot, line
    'showValue' => true,
    'showCategory' => true,
    'hgrid' => 3,
    'vgrid' => 3,
);
$docx->addChart($paramsChart);

$paramsChart = array(
    'data' => $completedData,
    'type' => 'scatterChart',    
    'border' => 0,
    'color' => 5,
    'legendPos' => 'r',
    'smooth' => true
);
$docx->addChart($paramsChart);

$paramsChart = array(
    'data' => $completedData,
    'type' => 'scatterChart',    
    'border' => 0,
    'color' => 1,
    'jc' => 'right',
    'legendPos' => 'r',
    'legendOverlay' => true,
    'font' => 'Times New Roman',  
    'haxLabel' => 'vertical label',
    'vaxLabel' => 'horizontal label',
    'haxLabelDisplay' => 'rotated',
    'vaxLabelDisplay' => 'rotated',
    'hgrid' => 0,
    'symbol' => 'line',//dot, line
    'vgrid' => 0,   
    'showtable' => true
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

$docx->createDocx('../docx/example_chart_scatter');