<?php

/**
 * Insert an image into a Word document.
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

$paramsImg = array(
    'name' => '../files/img/image.png',
    'scaling' => 50,
    'spacingTop' => 100,
    'spacingBottom' => 100,
    'spacingLeft' => 100,
    'spacingRight' => 100,
    'textWrap' => 1,
    'border' => 1,
    'borderDiscontinuous' => 1
);

$docx->addImage($paramsImg);

$docx->addText('Now we are going to insert twice the same image in a table cell:');

$paramsImg = array(
    'name' => '../files/img/image.png',
    'scaling' => 50,
    'spacingTop' => 10,
    'spacingBottom' => 10,
    'spacingLeft' => 100,
    'spacingRight' => 0,
    'textWrap' => 1,
    'border' => 1,
    'borderDiscontinuous' => 1,
    'rawWordML' => true
);

$imageData = $docx->addImage($paramsImg);

$fragment = $docx->createWordMLFragment(array($imageData, $imageData));

$valuesTable = array(
    array(
        11,
        12
    ),
    array(
        $fragment,
        22
    ),
);

$paramsTable = array(
    'border' => 'single',
    'border_sz' => 5,
);

$test = $docx->addTable($valuesTable, $paramsTable);

$docx->createDocx('../docx/example_image');