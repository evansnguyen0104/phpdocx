<?php

/**
 * Imports (twice) a RTF file into the Word document.
 *
 * @category   Phpdocx
 * @package    examples
 * @subpackage easy
 * @copyright  Copyright (c) 2009-2013 Narcea Producciones Multimedia S.L.
 *             (http://www.2mdc.com)
 * @license    http://www.phpdocx.com/wp-content/themes/lightword/pro_license.php
 * @version    2012.12.26
 * @link       http://www.phpdocx.com
 * @since      File available since Release 2.3
 */
require_once '../../classes/CreateDocx.inc';

$docx = new CreateDocx();

$docx->addText('RTF content');

$docx->addRTF(array('pathRTF' => '../files/Text.rtf'));

$docx->addText('Now we are going to insert twice the same RTF in different table cells:');

$rtfData = $docx->addRTF(array('pathRTF' => '../files/Text.rtf', 'rawWordML' => true));

$fragment = $docx->createWordMLFragment($rtfData);

$valuesTable = array(
    array(
        11,
        $fragment,
    ),
    array(
        $fragment,
        22,
    ),
);

$paramsTable = array(
    'border' => 'single',
    'border_sz' => 5,
);

$test = $docx->addTable($valuesTable, $paramsTable);
$docx->addText('End RTF content');

$docx->createDocx('../docx/example_rtf');
