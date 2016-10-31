<?php

/**
 * Searches for a string of text and highlights it.
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
$options = array( 'highlightColor' => 'green',
									'document' => true,
									'endnotes' => true,
									'comments' => true,
									'headersAndFooters' => true,
									'footnotes' => true);
$newDocx->searchAndHighlight('../files/second.docx', '../docx/example_highlightedDocx.docx', 'data', $options);