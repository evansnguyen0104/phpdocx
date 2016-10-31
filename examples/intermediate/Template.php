<?php

/**
 * Template table example.
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

$settings = array(
    'header' => true
);

$docx->addTemplate('../files/TemplateTable.docx');

$docx->addTemplateVariable(
    array(
        array(
            'NAME' => 'Product A',
            'WEIGHT' => '10',
            'PRICE' => '5',
        ),
        array(
            'NAME' => 'Product B',
            'WEIGHT' => '20',
            'PRICE' => '30',
        ),
        array(
            'NAME' => 'Product C',
            'WEIGHT' => '25',
            'PRICE' => '7',
        ),
        array(
            'NAME' => 'Product D',
            'WEIGHT' => '25',
            'PRICE' => '7',
        )
    ),
    'table',
    $settings
);

$docx->addTemplateVariable('TOTALWEIGHT', '55');

$docx->addTemplateVariable('TOTALPRICE', '42');

$docx->addTemplateVariable('MYNAME', 'David Hume');

$docx->createDocx('../docx/example_template');