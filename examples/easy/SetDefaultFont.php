<?php

/**
 * Sets the default font of the document
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

$docx = new CreateDocx();

$docx->setDefaultFont('Comic Sans MS');

$docx->addText('The default font of this document is the all-time favourite Comic Sans MS.');

$docx->createDocx('../docx/example_setDefaultFont');