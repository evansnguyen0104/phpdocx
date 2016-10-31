<?php

/**
 * Insert a stacked bar chart into a Word document.
 *
 * @category   Phpdocx
 * @package    examples
 * @subpackage easy
 * @copyright  Copyright (c) 2009-2013 Narcea Producciones Multimedia S.L.
 *             (http://www.2mdc.com)
 * @license    http://www.phpdocx.com/wp-content/themes/lightword/pro_license.php
 * @version    2012.12.26
 * @link       http://www.phpdocx.com
 * @since      File available since Release 2.2
 */
require_once '../../classes/CreateDocx.inc';

$docx = new CreateDocx();

$colChartValues = array(
    'legend' => array('Internet Explorer', 'Firefox', 'Chrome', 'Safari', 'Opera'),
    'January 2011' => array('26.6', '42.8', '23.8', '4.0', '2.5'),
    'February 2011' => array('26.5', '42.4', '24.1', '4.1', '2.5'),
    'March 2011' => array('25.8', '42.2', '25.0', '4.0', '2.5'),
    'April 2011' => array('24.3', '42.9', '25.6', '4.1', '2.6'),
    'May 2011' => array('24.9', '42.4', '25.9', '4.0', '2.4'),
    'June 2011' => array('23.2', '42.2', '27.9', '3.7', '2.4')
);

$paramsChart = array(
    'data' => $colChartValues,
    'type' => 'barChart',
    'title' => 'W3C Browser Statistics',
    'color' => 2,
    'sizeX' => 15,
    'sizeY' => 15,
    'jc' => 'center',
    'groupBar' => 'stacked',
    'font' => 'Lucida Console',
    'legendPos' => 't',
);
$docx->addChart($paramsChart);

$docx->createDocx('../docx/example_chart_bar_stacked');