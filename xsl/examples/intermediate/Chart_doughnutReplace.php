<?php

/**
 * Replace the data from a doughnut chart with the data give by the client
 *
 * @category   Phpdocx
 * @package    examples
 * @subpackage intermediate
 * @copyright  Copyright (c) 2009-2013 Narcea Producciones Multimedia S.L.
 *             (http://www.2mdc.com)
 * @license    http://www.phpdocx.com/wp-content/themes/lightword/pro_license.php
 * @version    2012.12.26
 * @link       http://www.phpdocx.com
 * @since      2012.12.26
 */

require_once '../../classes/CreateDocx.inc';

$simpleData = array(
    'legend' => array('Simple Data'),
    'data 1' => array('10'),
    'data 2' => array('2'),
    'data 3' => array('13'),
    'data 4' => array('14')
);


$docx = new DocxUtilities();
$source = "../files/example_doughnutChart.docx";
$target = '../docx/example_doughnutChart_replace_data.docx';
$data = array(
	0 => $simpleData,	
);
$docx->replaceChartData($source, $target, $data);