<?php

/**
 * Replace the data from a ofPie chart with the data give by the client
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
    'data 2' => array('22'),
    'data 3' => array('3'),
    'data 4' => array('4'),
    'data 5' => array('50'),
    'data 6' => array('6'),
    'data 7' => array('7'),
    'data 8' => array('8'),
    'data 9' => array('90'),
    'data 10' => array('10'),
);

$docx = new DocxUtilities();
$source = "../files/example_ofPieChart.docx";
$target = '../docx/example_ofPieChart_replace_data.docx';
$data = array(
    0 => $simpleData,
    1 => $simpleData,    
);
$docx->replaceChartData($source, $target, $data);