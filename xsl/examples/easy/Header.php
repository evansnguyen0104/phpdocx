<?php

/**
 * Creates a simple header for the Word document.
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

$headerImage = $docx->addImage(array('name' => '../files/img/image.png', 'dpi' => 300, 'rawWordML' => true, 'target' => 'defaultHeader'));
$myImage = $docx->createWordMLFragment(array($headerImage));

$docx->addHeader(array('default' => $myImage));

$docx->createDocx('../docx/example_header');
