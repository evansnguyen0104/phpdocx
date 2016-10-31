<?php

/**
 * Inserts a table with predetermined column sizes in the Word document.
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

$valuesTable = array(
    array(
        '',
        'Col 1',
        'Col 2'
    ),
    array(
        'Row 1',
        22,
        23
    ),
    array(
        'Row 2',
        32,
        33
    ),
);

$widthTableCols = array(
    1000,
    2500,
    3000
);

$paramsTable = array(
    'border' => 'single',
    'border_sz' => 20,
    'size_col' => $widthTableCols
);



$docx->addTable($valuesTable, $paramsTable);

$docx->createDocx('../docx/example_table_size_cols');