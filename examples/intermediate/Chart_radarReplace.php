<?php

/**
 * Replace the data from a radar chart with the data give by the client
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
    'legend' => array('Completed', 'Data', 'Example'),
    'Category 1' => array(0.3, 1.4, 2),
    'Category 2' => array(3.5, 4.4, 5),
    'Category 3' => array(6.5, 7.8, 8.5),
    'Category 4' => array(9.5, 10, 11),
    'Category 5' => array(12.6, 13.5, 14.6),
);
$docx = new DocxUtilities();
$source = "../files/example_radar_chart.docx";
$target = '../docx/example_radar_chart_replace_data.docx';
$data = array(
    0 => $completedData,
    1 => $completedData,    
);
$docx->replaceChartData($source, $target, $data);