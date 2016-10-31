<?php

/**
 * Import Word styles from another word file.
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

//You may first check the available styles using the parseStyles('../files/TemplateStyles.docx') methohd

$docx->importStyles('../files/TemplateStyles.docx', 'merge', array('crazyStyle'));

$docx->addText('This is the resulting paragraph with the "CrazyStyle".', array('pStyle' => 'crazyStyle'));

//You may also import a complete XML style sheet by
//$docx->importStyles('../files/TemplateStyles.docx', $type= 'replace');

$docx->createDocx('../docx/example_import_word_styles');
