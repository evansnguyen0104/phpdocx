<?php

/**
 * List with embeded elements: image, list, chart and textbox
 *
 * @category   Phpdocx
 * @package    examples
 * @subpackage intermediate
 * @copyright  Copyright (c) 2009-2013 Narcea Producciones Multimedia S.L.
 *             (http://www.2mdc.com)
 * @license    http://www.phpdocx.com/wp-content/themes/lightword/pro_license.php
 * @version    2012.12.26
 * @link       http://www.phpdocx.com
 * @since      File available since Release 1.8
 */
require_once '../../classes/CreateDocx.inc';

$docx = new CreateDocx();

$paramsLink = array(
    'url' => 'http://www.google.es',
    'sz' => 24,
    'u' => 'single',
    'rawWordML' => true
);

$link = $docx->addLink('Link to Google', $paramsLink);

$myLink = $docx->createWordMLFragment($link);

$paramsImage = array(
    'name' => '../files/img/image.png',
    'dpi' => 300,
    'rawWordML' => true
);

$image = $docx->addImage($paramsImage);
$myImage = $docx->createWordMLFragment($image);

$legends = array(
    'legend1' => array(10),
    'legend2' => array(24),
    'legend3' => array(40)
);

$paramsChart = array(
    'data' => $legends,
    'type' => 'pie3DChart',
    'title' => 'Title',
    'rawWordML' => true
);
$chart = $docx->addChart($paramsChart);
$myChart = $docx->createWordMLFragment($chart);



$valuesList = array(
    'Line 1',
    $myLink,
    $myImage,
    $myChart,
    'Line 2',
    'Line 3'
);
$paramsList = array(
    'val' => 1
);
$docx->addList($valuesList, $paramsList);

$docx->createDocx('../docx/example_list');