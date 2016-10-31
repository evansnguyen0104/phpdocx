<?php

/**
 * replaces a placeholder image located in the header.
 *
 * @category   Phpdocx
 * @package    examples
 * @subpackage intermediate
 * @copyright  Copyright (c) 2009-2013 Narcea Producciones Multimedia S.L.
 *             (http://www.2mdc.com)
 * @license    http://www.phpdocx.com/wp-content/themes/lightword/pro_license.php
 * @version    2012.12.26
 * @link       http://www.phpdocx.com
 * @since      File available since Release 2.5.2
 */
 
require_once('../../classes/CreateDocx.inc');

$docx = new CreateDocx();
$docx->addTemplate('../files/headerImageTemplate.docx');

$docx->replaceHeaderImage('LOGO', '../files/img/logo_header.jpg');

$docx->createDocx('../docx/example_replaceHeaderImage');