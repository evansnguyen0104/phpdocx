<?php

/**
 * Creates a WordML fragment composed of twice the same table that is inserted within another table
 *
 * @category   Phpdocx
 * @package    examples
 * @subpackage easy
 * @copyright  Copyright (c) 2009-2013 Narcea Producciones Multimedia S.L.
 *             (http://www.2mdc.com)
 * @license    http://www.phpdocx.com/wp-content/themes/lightword/pro_license.php
 * @version    2012.12.26
 * @link       http://www.phpdocx.com
 * @since      2012.12.26
 */
require_once '../../classes/CreateDocx.inc';

$docx = new CreateDocx();

$valuesTable = array(
    array(
        11,
        12
    ),
    array(
        21,
        22
    ),
);

$paramsTable = array(
    'border' => 'single',
    'border_sz' => 4,
    'rawWordML' => true
);

$myTable = $docx->addTable($valuesTable, $paramsTable);

$fragment = $docx->createWordMLFragment(array($myTable, $myTable));

$valuesTable2 = array(
    array(
        a,
        b
    ),
    array(
        $fragment,
        c
    ),
);

$paramsTable2 = array(
    'border' => 'single',
    'border_sz' => 20,
);

$docx->addTable($valuesTable2, $paramsTable2);

$docx->createDocx('../docx/example_wordMLFragment');