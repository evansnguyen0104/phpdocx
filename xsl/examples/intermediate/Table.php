<?php

/**
 * Creates a table with embeded elements: links and images.
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
    'title' => 'Link to Google',
    'link' => 'http://www.google.es'
);

$link = $docx->addElement('addLink', $paramsLink);

$paramsImg = array(
    'name' => '../files/img/image.png'
);

$image = $docx->addElement('addImage', $paramsImg);

$valuesTable = array(
    array(
        'Title A',
        'Title B',
        'Title C',
    ),
    array(
        'Line A',
        $link,
        $image,
    )
);

$paramsTable = array(
    'TBLSTYLEval' => 'MediumShading1PHPDOCX',
    'border' => 'single',
    'border_sz' => 20,
    'border_spacing' => 0,
    'border_color' => 'ff0000',
    'jc' => 'center',
    'size_col' => 1200
);

$docx->addTable($valuesTable, $paramsTable);
$docx->createDocx('../docx/example_table');