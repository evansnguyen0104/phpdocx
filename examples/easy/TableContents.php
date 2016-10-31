<?php

/**
 * Inserts a Table of Contents in the Word document.
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

$docx->addText('Table of Contents', array('b' => 'on', 'sz' => 14));
$docx->addTableContents(array('autoUpdate' => true), array('text' => 'Clich here to update the TOC', 'color' => 'B70000', 'b' => 'on', 'sz' => 12), '../files/crazyTOC.docx');
$docx->addText('Chapter 1', array('pStyle' => 'Heading1PHPDOCX'));
$docx->addText('Section', array('pStyle' => 'Heading2PHPDOCX'));
$docx->addText('Another TOC entry', array('pStyle' => 'Heading3PHPDOCX'));

$docx->createDocx('../docx/example_tablecontents');