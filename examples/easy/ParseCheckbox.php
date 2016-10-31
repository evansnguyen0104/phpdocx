<?php

/**
 * Tikcs or unticks a checkbox in a Word template
 *
 * @category   Phpdocx
 * @package    examples
 * @subpackage easy
 * @copyright  Copyright (c) 2009-2013 Narcea Producciones Multimedia S.L.
 *             (http://www.2mdc.com)
 * @license    http://www.phpdocx.com/wp-content/themes/lightword/pro_license.php
 * @version    2013.05.20
 * @link       http://www.phpdocx.com
 * @since      2013.05.20
 */

require_once '../../classes/DocxUtilities.inc';

$docx = new DocxUtilities();

$values = array (0,1,1);

$docx->parseCheckboxes('../files/Checkbox.docx', '../docx/example_parsecheckboxes.docx', $values);