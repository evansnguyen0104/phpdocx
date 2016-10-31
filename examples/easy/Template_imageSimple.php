<?php

/**
 * Replace a template image by an external image.
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
require_once '../../classes/CreateDocx.inc';

$objDocx = new CreateDocx();

$objDocx->addTemplate('../files/TemplateImage.docx');

$objDocx->addTemplateImage('IMAGE', '../files/img/logo_phpdocx.gif');

$objDocx->createDocx('../docx/example_template_imageSimple');
