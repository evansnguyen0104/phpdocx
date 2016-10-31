<?php

/**
 * Inserts a percent stacked chart into a Word document.
 *
 * @category   Phpdocx
 * @package    examples
 * @subpackage easy
 * @copyright  Copyright (c) 2009-2013 Narcea Producciones Multimedia S.L.
 *             (http://www.2mdc.com)
 * @license    http://www.phpdocx.com/wp-content/themes/lightword/pro_license.php
 * @version    2012.12.26
 * @link       http://www.phpdocx.com
 * @since      File available since Release 2.7
 */
require_once '../../classes/CreateDocx.inc';

$docx = new CreateDocx();
$completedData = array(
    'legend' => array('Data 1', 'Data 2', 'Data 3'),
    'data 1' => array('10', 0, 5),
    'data 2' => array('20', 60, 3),
    'data 3' => array('50', 33, 7),
    'data 4' => array('25', 0, 0)
);
$paramsChart = array(
    'data' => $completedData,
    'type' => 'col3DChart',
    'groupBar' => 'percentStacked',
    'title' => 'Completed bar 3D Chart',
    'color' => '5',
    'perspective' => '30',
    'rotX' => '30',
    'rotY' => '30',
    'font' => 'Arial',
    'jc' => 'right',
    'showtable' => 1,
    'textWrap' => '4',
    'sizeX' => '10',
    'sizeY' => '10',
    'legendPos' => 't',
    'legendOverlay' => '0',
    'border' => '1',
    'haxLabel' => 'label horizontal',
    'vaxLabel' => 'label vertical',
    'haxLabelDisplay' => 'horizontal',
    'vaxLabelDisplay' => 'horizontal',
    'hgrid' => '3',
    'vgrid' => '2',
);
$docx->addChart($paramsChart);

$docx->createDocx('../docx/example_chart_percentStacked');