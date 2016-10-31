<?php

/**
 * Transform a text file into a word document trying to hold the styles
 *
 * @category   Phpdocx
 * @package    examples
 * @subpackage easy
 * @copyright  Copyright (c) 2009-2013 Narcea Producciones Multimedia S.L.
 *             (http://www.2mdc.com)
 * @license    http://www.phpdocx.com/wp-content/themes/lightword/pro_license.php
 * @version    2012.12.26
 * @link       http://www.phpdocx.com
 * @since      File available since Release 1.8
 */
require_once '../../classes/CreateDocx.inc';

$docx = new CreateDocx();

$docx->txt2docx('../files/text_formated.txt');
$docx->txt2docx('../files/text_formated.txt', array('styleTbl' => array('TBLSTYLEval' => 'LightShadingAccent1PHPDOCX'), 'styleLst' => array('val' => 2)));
$docx->txt2docx('../files/text_formated.txt', array('styleTbl' => array('TBLSTYLEval' => 'LightListAccent1PHPDOCX'), 'styleLst' => array('val' => 3) ));
$docx->txt2docx('../files/text_formated.txt', array('styleTbl' => array('TBLSTYLEval' => 'MediumShading2-accent2PHPDOCX'), 'styleLst' => array('val' => 4)));

$widthTableCols = array(
    1000,
    2500,
    3000
);
$docx->txt2docx('../files/text_formated.txt', array('styleTbl' => array('border' => 'single', 'border_sz' => 20, 'size_col' => $widthTableCols), 'styleLst' => array('val' => 5)));

$docx->createDocx('../docx/example_txt2Docx');
