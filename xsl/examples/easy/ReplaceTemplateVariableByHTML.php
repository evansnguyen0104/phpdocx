<?php

/**
 * Embed some HTML in a Word document: table with row and col spans.
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
$docx->addTemplate('../files/testHTML2mdc.docx');

$docx->replaceTemplateVariableByHTML('ADDRESS', 'inline', '<p style="font-family: verdana; font-size: 11px">C/ Matías Turrión 24, Madrid 28043 <b>Spain</b></p>', array('isFile' => false, 'parseDivsAsPs' => true, 'downloadImages' => false));
$docx->replaceTemplateVariableByHTML('CHUNK_1', 'block', 'http://www.2mdc.com/PHPDOCX/example.html', array('isFile' => true, 'parseDivsAsPs' => true,  'filter' => 'capa_bg_bottom', 'downloadImages' => true));
$docx->replaceTemplateVariableByHTML('CHUNK_2', 'block', 'http://www.2mdc.com/PHPDOCX/example.html', array('isFile' => true, 'parseDivsAsPs' => false,  'filter' => 'lateral', 'downloadImages' => true));

$docx->createDocx('../docx/example_replaceTemplateVariableByHTML');