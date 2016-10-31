<?php

/**
 * Replaces a PHPDocX template variable by a Word chart.
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

$docx->addTemplate('../files/TemplateChart.docx');

$legends = array(
    'legend1' => array(10, 11, 12),
    'legend2' => array(30, 21, 12),
    'legend3' => array(40, 41, 42)
);

$paramsChart =
    array(
        'data' => $legends,
        'type' => 'pie3DChart',
        'title' => 'Title',
        'rotX' => 20,
        'rotY' => 20,
        'perspective' => 30,
        'color' => 2,
        'textWrap' => 0,
        'sizeX' => 10,
        'sizeY' => 10,
        'jc' => 'right',
        'showPercent' => 1,
        'font' => 'Times New Roman'
    );

$docx->addTemplateChart('PIECHART', $paramsChart);

$docx->createDocx('../docx/example_template_chart');