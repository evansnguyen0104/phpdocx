<?php

/**
 * Searches for a string of text and replace it by another one.
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

require_once '../../classes/DocxUtilities.inc';

$newDocx = new DocxUtilities();
$options = array( 'document' => true,
									'endnotes' => true,
									'comments' => true,
									'headersAndFooters' => true,
									'footnotes' => true);

$newDocx->searchAndReplace('../files/second.docx', '../docx/example_replacedDocx.docx', 'data', 'required data', $options);