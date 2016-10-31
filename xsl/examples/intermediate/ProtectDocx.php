<?php

/**
 * Password protects the contents of a docx.
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
$source = '../files/Text.docx';
$target = '../docx/example_protected.docx';
$docx->protectDocx($source, $target, array('password' => 'phpdocx'));