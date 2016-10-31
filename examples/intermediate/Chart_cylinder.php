<?php

/**
 * Stacked horizontal cylinder chart in 3D with text and title.
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

$docx = new CreateDocx();

$docx->addBreak();

$text = 'Lorem ipsum dolor sit amet, consectetur adipisicing elit, ' .
    'sed do eiusmod tempor incididunt ut labore et dolore magna aliqua. Ut ' .
    'enim ad minim veniam, quis nostrud exercitation ullamco laboris nisi ut' .
    'aliquip ex ea commodo consequat. Duis aute irure dolor in reprehenderit ' .
    'in voluptate velit esse cillum dolore eu fugiat nulla pariatur. ' .
    'Excepteur sint occaecat cupidatat non proident, sunt in culpa qui ' .
    'officia deserunt mollit anim id est laborum.';

$paramsText = array(
    'font' => 'Arial',
	'sz' => 12
);

$docx->addText($text, $paramsText);

$docx->addBreak();

$legends = array(
    'legend' => array('sequence 1', 'sequence 2', 'sequence 3'),
    'Category 1' => array(9.3, 2.4, 2),
    'Category 2' => array(2.5, 4.4, 1),
    'Category 3' => array(3.5, 1.8, 0.5),
    'Category 4' => array(1.5, 8, 1)
);

$args = array(
    'data' => $legends,
    'type' => 'bar3DChartCylinder',
    'title' => 'Cylinder chart',
    'color' => 2,
    'textWrap' => 0,
    'sizeX' => 15, 'sizeY' => 15,
    'showPercent' => 1,
    'font' => 'Arial',
    'groupBar' => 'stacked',
    'legendPos' => 'none',
	  'border' => 1,
    'showtable' => 1,
	  'hgrid' => 3,
	  'vgrid' => 3
);
$docx->addChart($args);

$docx->createDocx('../docx/example_chart_cylinder');
