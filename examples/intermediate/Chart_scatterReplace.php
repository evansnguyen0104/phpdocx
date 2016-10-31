<?php

/**
 * Replace the data from a scatter chart with the data give by the client
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
    array(1, 0),
    array(2, 2),
    array(3, 4),
    array(4, 6),
    array(5, 8),
    array(6, 10),
    array(7, 12),   
);

$docx = new DocxUtilities();
$source = "../files/example_scatter_chart.docx";
$target = '../docx/example_scatter_chart_replace_data.docx';
$data = array(
    0 => $completedData,
    1 => $completedData,    
);
$docx->replaceChartData($source, $target, $data);