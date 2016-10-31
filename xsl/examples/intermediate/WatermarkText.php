<?php

/**
 * Inserts a text watermark in an existing docx.
 *
 * @category   Phpdocx
 * @package    examples
 * @subpackage intermediate
 * @copyright  Copyright (c) 2009-2013 Narcea Producciones Multimedia S.L.
 *             (http://www.2mdc.com)
 * @license    http://www.phpdocx.com/wp-content/themes/lightword/pro_license.php
 * @version    2012.12.26
 * @link       http://www.phpdocx.com
 * @since      2012.12.26
 */
require_once '../../classes/CreateDocx.inc';

$docx = new DocxUtilities();
$source = '../files/Text.docx';
$target = '../docx/example_watermarkText.docx';
$docx->watermarkDocx($source, $target, $type = 'text', $options = array('text' => 'PHPDocX'));