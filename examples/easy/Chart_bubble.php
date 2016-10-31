<?php

/**
 * Insert a bubble chart into a Word document.
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

$completedData = array(
    array(10, 0, 1),    
    array(15, 2, 2),    
    array(20, 4, 3),    
    array(25, 6, 4),    
);

$docx = new CreateDocx();

$paramsChart = array(
    'data' => $completedData,
    'type' => 'bubbleChart',
    'title' => 'simple bubbles',
    'legendPos' => 't',
    'color' => 2,
    'border' => 1,
	'font' => 'Times New Roman',
    'hgrid' => '2',
    'vgrid' => '2',
    'showPercent' => true,
    'showValue' => true,
    'showCategory' => true,
    'showtable' => true
);
$docx->addChart($paramsChart);

$paramsChart = array(
    'data' => $completedData,
    'type' => 'bubble3DChart',    
    'title' => '3D bubbles',
    'rotX' => 20, 'rotY' => 20, 'perspective' => 30,
    'border' => 3,
	'font' => 'Arial',
    'color' => 3,
    'legendPos' => 'none',
    'jc' => 'right',
    'haxLabel' => 'label horizontal',
    'vaxLabel' => 'label vertical',
    'haxLabelDisplay' => 'horizontal',
    'vaxLabelDisplay' => 'horizontal',
    'hgrid' => '1',
    'vgrid' => '1',
    'showPercent' => true,
    'showValue' => true,
    'showCategory' => true,
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

$docx->createDocx('../docx/example_chart_bubble');