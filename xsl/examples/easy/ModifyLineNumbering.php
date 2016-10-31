<?php

/**
 * Modifies the line numbering properties of an existing Word document.
 *
 * @category   Phpdocx
 * @package    examples
 * @subpackage easy
 * @copyright  Copyright (c) 2009-2013 Narcea Producciones Multimedia S.L.
 *             (http://www.2mdc.com)
 * @license    http://www.phpdocx.com/wp-content/themes/lightword/pro_license.php
 * @version    2013.09.06
 * @link       http://www.phpdocx.com
 * @since      File available since Release 3.4
 */

require_once '../../classes/DocxUtilities.inc';

$newDocx = new DocxUtilities();
$newDocx->setLineNumbering('../files/second.docx', '../docx/example_setLineNumbering.docx', array('start' => 25));