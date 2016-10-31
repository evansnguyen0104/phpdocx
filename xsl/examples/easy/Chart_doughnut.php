<?php

/**
 * Insert a doughnut chart into a Word document.
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

$simpleData = array(
    'legend' => array('Simple Data'),
    'data 1' => array('10'),
    'data 2' => array('20'),
    'data 3' => array('50'),
    'data 4' => array('25')
);
$docx = new CreateDocx();

$paramsChart = array(
    'data' => $simpleData,
    'type' => 'doughnutChart',
    'title' => 'Most Simple doughnut Chart with simple data',
    'font' => 'Times New Roman',
    'showPercent' => true,
    'showValue' => true,
    'showCategory' => true,
    'explosion' => 25,
    'border' => 3,
    'holeSize' => 25,
    'sizeX' => 15,
    'sizeY' => 15,
    'jc' => 'right',
    'color' => '2',
    'legendPos' => 'r',
    'legendOverlay' => true,
    'showtable' => true,
    'hgrid' => 2,
    'vgrid' => 2,
    'showtable' => true,
);
$docx->addChart($paramsChart);

$paramsChart = array(
    'data' => $simpleData,
    'type' => 'doughnutChart',
    'title' => 'Most Simple doughnut Chart with simple data',
    'showPercent' => true,
    'jc' => 'center',
    'color' => '2',
    'font' => 'Arial',
    'legendPos' => 't',
);
$chart = $docx->addElement('addGraphic', $paramsChart);
$valuesList = array(
    'Line 1',
    $chart,
    'Line 2',
    'Line 3',
);
$paramsList = array('val' => 1);
$docx->addList($valuesList, $paramsList);

$docx->createDocx('../docx/example_chart_doughnut');