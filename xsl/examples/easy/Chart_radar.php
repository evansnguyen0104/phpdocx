<?php

/**
 * Insert radar charts into a Word document with different styling options.
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
    'Category 2' => array(8.5, 4.4, 1),
    'Category 3' => array(6.5, 1.8, 0.5),
    'Category 4' => array(8.5, 3, 1),
    'Category 5' => array(6, 5, 2.6),
);

$args = array(
    'data' => $legends,
    'type' => 'radar',
    'style' => 'radar',
    'title' => 'Radar chart',
    'sizeX' => 15, 'sizeY' => 15,
    'legendPos' => 't',
    'border' => 1,
    'vgrid' => 1
);
$docx->addChart($args);

$args = array(
    'data' => $legends,
    'type' => 'radar',
    'style' => 'marker',
    'title' => 'Radar chart',
    'sizeX' => 15, 'sizeY' => 15,
    'legendPos' => 't',
    'border' => 1,
    'vgrid' => 1
);
$docx->addChart($args);

$args = array(
    'data' => $legends,
    'type' => 'radar',
    'style' => 'filled',
    'title' => 'Radar chart',
    'sizeX' => 15, 'sizeY' => 15,
    'legendPos' => 't',
    'border' => 1,
    'vgrid' => 1
);
$docx->addChart($args);

$docx->createDocx('../docx/example_chart_radar');