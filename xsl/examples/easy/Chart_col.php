<?php

/**
 * Insert a col chart into a Word document.
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
    'November 2010' => array('28.6', '44.0', '20.5', '4.0', '2.3'),
    'December 2010' => array('27.5', '43.5', '22.4', '3.8', '2.2'),
    'January 2011' => array('26.6', '42.8', '23.8', '4.0', '2.5')
);

$paramsChart = array(
    'data' => $colChartValues,
    'type' => 'colChart',
    'title' => 'W3C Browser Statistics',
    'color' => 2,
    'sizeX' => 15,
    'sizeY' => 15,
    'jc' => 'center',
    'groupBar' => 'clustered',
    'font' => 'Lucida Console'
);
$docx->addChart($paramsChart);

$docx->createDocx('../docx/example_chart_col');
