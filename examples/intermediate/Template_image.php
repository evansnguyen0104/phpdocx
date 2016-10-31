<?php

/**
 * Replaces a series of images inserted in a table.
 *
 * @category   Phpdocx
 * @package    examples
 * @subpackage intermediate
 * @copyright  Copyright (c) 2009-2013 Narcea Producciones Multimedia S.L.
 *             (http://www.2mdc.com)
 * @license    http://www.phpdocx.com/wp-content/themes/lightword/pro_license.php
 * @version    2012.12.26
 * @link       http://www.phpdocx.com
 * @since      File available since Release 2,3
 */
require_once '../../classes/CreateDocx.inc';

$docx = new CreateDocx();

$docx->addTemplate('../files/TemplateTableImage.docx');

$docx->addTemplateImage('IMAGE1', '../files/img/imageP1.png');
$docx->addTemplateImage('IMAGE2', '../files/img/imageP2.png');
$docx->addTemplateImage('IMAGE3', '../files/img/imageP3.png');


$docx->createDocx('../docx/example_template_image');