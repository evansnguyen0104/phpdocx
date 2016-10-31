<?php

/**
 * Replace the data from a pie chart with the data give by the client
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
    'data 1' => array('1'),
    'data 2' => array('200'),
    'data 3' => array('5')
);
$docx = new DocxUtilities();
$source = "../files/example_pie_chart_completed.docx";
$target = '../docx/example_pie_chart_completed_replace_data.docx';
$data = array(
    0 => $simpleData,
    1 => $simpleData,    
);
$docx->replaceChartData($source, $target, $data);