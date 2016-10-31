<?php

/**
 * Password protects the contents of a PDF.
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

$pdf = new CryptoPHPDOCX();
$source = '../files/Test.pdf';
$target = '../docx/example_protected.pdf';
$pdf->protectPDF($source, $target, array('permissionsBlocked' => array('print', 'annot-forms')));