<?php

/**
 * Insert a Word document within another Word document
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

$docx->addText('DOCX content');

$docx->addDOCX(array('pathDOCX' => '../files/Text.docx'));

$docx->addText('End DOCX content');

$docx->addText('Now we are going to insert twice the same DOCX in a table cell:');

$DOCXdata = $docx->addDOCX(array('pathDOCX' => '../files/Text.docx', 'rawWordML' => true));

$fragment = $docx->createWordMLFragment(array($DOCXdata, $DOCXdata));

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

$docx->createDocx('../docx/example_docx');