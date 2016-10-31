<?php

/**
 * Replace the data from a bubble chart with the data give by the client
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

$completedData = array(
    array(25, 10, 5),    
    array(20, 5, 4),    
    array(15, 0, 3),    
    array(10, 15, 2),    
);

$docx = new DocxUtilities();
$source = "../files/example_bubble_chart.docx";
$target = '../docx/example_bubble_chart_replace_data.docx';
$data = array(
	0 => $completedData,
	1 => $completedData,	
);
$docx->replaceChartData($source, $target, $data);