<?php

/**
 * Removes password protection from a docx.
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

$docx = new CryptoPHPDOCX();
$source = '../files/protectedDocument.docx';
$target = '../docx/example_unprotected.docx';
$docx->removeProtection($source, $target);
