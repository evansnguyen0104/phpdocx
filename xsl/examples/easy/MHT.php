<?php

/**
 * Inserts an external MHT file into a Word document.
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

$docx->addText('MHT content');

$docx->addMHT(array('pathMHT' => '../files/Web.mht'));

$docx->addText('We are now going to insert the MHT in a table cell:');


$MHTdata = $docx->addMHT(array('pathMHT' => '../files/Web.mht', 'rawWordML' => true));

$fragment = $docx->createWordMLFragment($MHTdata);

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

$docx->addText('End MHT content');

$docx->createDocx('../docx/example_mht');
