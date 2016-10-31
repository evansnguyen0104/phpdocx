<?php

/**
 * Inserts automatic page numbering in a header
 *
 * @category   Phpdocx
 * @package    examples
 * @subpackage easy
 * @copyright  Copyright (c) 2009-2013 Narcea Producciones Multimedia S.L.
 *             (http://www.2mdc.com)
 * @license    http://www.phpdocx.com/wp-content/themes/lightword/pro_license.php
 * @version    2012.12.26
 * @link       http://www.phpdocx.com
 * @since      File available since Release 3.0
 */
require_once '../../classes/CreateDocx.inc';

$docx = new CreateDocx();

$options = array('jc' => 'right',
                 'b' => 'on',
                 'sz' => 14,
                 'color' => 'ff0000',
                 'rawWordML' => true);

$numbering = $docx->addPageNumber('numerical', $options);

$WordMLFragment = $docx->createWordMLFragment(array($numbering));

$docx->addHeader(array('default' => $WordMLFragment));

//Now we include a couple of pages to better illustrate the example
$docx->addText('This is the first page.');
$docx->addBreak(array('type' => 'page'));
$docx->addText('This is the second page.');
$docx->addBreak(array('type' => 'page'));
$docx->addText('This is the third page.');

$docx->createDocx('../docx/example_pageNumber');