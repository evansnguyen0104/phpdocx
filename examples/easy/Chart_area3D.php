<?php

/**
 * Insert a 3D area chart into a Word document.
 *
 * @category   Phpdocx
 * @package    examples
 * @subpackage easy
 * @copyright  Copyright (c) 2009-2013 Narcea Producciones Multimedia S.L.
 *             (http://www.2mdc.com)
 * @license    http://www.phpdocx.com/wp-content/themes/lightword/pro_license.php
 * @version    2012.12.26
 * @link       http://www.phpdocx.com
 * @since      File available since Release 2.4
 */
require_once '../../classes/CreateDocx.inc';

$docx = new CreateDocx();

$legends = array(
    'legend' => array('sequence 1', 'sequence 2', 'sequence 3'),
    'Category 1' => array(9.3, 2.4, 2),
    'Category 2' => array(2.5, 4.4, 1),
    'Category 3' => array(3.5, 1.8, 0.5),
    'Category 4' => array(1.5, 8, 1)
);

$args = array(
    'data' => $legends,
    'type' => 'area3DChart',
    'title' => 'Area 3D chart stacked',
    'color' => 5,
    'sizeX' => 15, 'sizeY' => 15,
    'showPercent' => 1,
    'font' => 'Lucida Console',
    'groupBar' => 'stacked',
    'legendPos' => 't',
    'border' => 1,
    'haxLabel' => 'Abscissa',
    'vaxLabel' => 'Ordinate',
    'vaxLabelDisplay' => 'rotated',
    'hgrid' => 2,
    'vgrid' => 1
);
$docx->addChart($args);

$docx->createDocx('../docx/example_chart_area3d');