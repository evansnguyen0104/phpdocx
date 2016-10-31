<?php

/**
 * Inserts a pie chart with a secondary bar chart into a Word document.
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
$simpleData = array(
    'data 1' => array('10'),
    'data 2' => array('20'),
    'data 3' => array('50'),
    'data 4' => array('25'),
    'data 5' => array('5'),
    'data 6' => array('15'),
    'data 7' => array('55'),
    'data 8' => array('75'),
    'data 9' => array('60'),
    'data 10' => array('25'),
);

$paramsChart = array(
    'data' => $simpleData,
    'type' => 'ofPieChart',
    'subtype' => 'bar',
    'title' => 'Secondary bar chart',
    'color' => '2',
    'sizeX' => 15,
    'sizeY' => 15,
    'jc' => 'right',
    'font' => 'Times New Roman',
    'gapWidth' => 150,
    'secondPieSize' => 75,
    'splitType' => 'percent', 
    'splitPos' => 20

);
$docx->addChart($paramsChart);

$docx->createDocx('../docx/example_chart_ofpie_chart_bar');