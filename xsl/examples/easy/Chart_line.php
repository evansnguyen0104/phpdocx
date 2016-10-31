<?php

/**
 * Insert a Line Chart into a Word document.
 *
 * @category   Phpdocx
 * @package    examples
 * @subpackage easy
 * @copyright  Copyright (c) 2009-2013 Narcea Producciones Multimedia S.L.
 *             (http://www.2mdc.com)
 * @license    http://www.phpdocx.com/wp-content/themes/lightword/pro_license.php
 * @version    2012.12.26
 * @link       http://www.phpdocx.com
 * @since      File available since Release 2.4
 */
require_once '../../classes/CreateDocx.inc';

$docx = new CreateDocx();

$lineChartValues = array(
    'legend' => array('SymbianOS','iOS','BlackBerry OS','Android', 'Sony Ericsson','Samsung','Other'),
    '2010-05' => array('32.92', '29.01', '14.15', '3.94', '9.09', '2.86', '1.11'),
    '2010-06' => array('33.39', '26.66', '14.98', '3.95', '9.81', '3.34', '1.07'),
    '2010-07' => array('32.04', '26.05', '16.45', '7.91', '6.77', '2.93', '1.46'),
    '2010-08' => array('31.54', '25.71', '16.95', '9.22', '6.16', '2.85', '1.43'),
    '2010-09' => array('32.69', '22.85', '17.9', '9.79', '6.59', '2.96', '1.16'),
    '2010-10' => array('32.83', '22.45', '18.19', '10.67', '5.91', '2.83', '1.19'),
    '2010-11' => array('31.93', '21.94', '19.25', '11.61', '5.32', '3.49', '1.2'),
    '2010-12' => array('29.66', '23.57', '18.04', '13.6', '5.13', '4.05', '1.2'),
    '2011-01' => array('30.25', '25.02', '15.03', '14.61', '5.21', '4.33', '1.27'),
    '2011-02' => array('30.66', '24.56', '14.52', '15.16', '5.14', '4.51', '1.26'),
    '2011-03' => array('30.61', '24.38', '14.1', '15.8', '5.1', '4.73', '1.21'),
    '2011-04' => array('31.56', '23.34', '13.54', '16.05', '5.28', '4.99', '1.26'),
    '2011-05' => array('31.36', '22.09', '12.94', '17.63', '5.77', '5.08', '1.4')
);

$paramsChart = array(
    'data' => $lineChartValues,
    'type' => 'lineChart',
    'title' => 'Top 7 Mobile OSs from May 2010 to May 2011',
    'color' => '2',
    'sizeX' => 15,
    'sizeY' => 15,
    'jc' => 'center',
    'groupBar' => 'clustered',
    'font' => 'Arial',
    'hgrid' => 1,
    'vgrid' => 1,
    'legendPos' => 'b',
    'legendOverlay' => 0
);
$docx->addChart($paramsChart);

$options = array(
    'html' => '<span>Source:  <a href="http://statcounter.com/" class="link_destacado">STATCOUNTER</a></span>');

$docx->addHTML($options);

$docx->createDocx('../docx/example_chart_line');
