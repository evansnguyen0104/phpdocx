<?php

/**
 * Inserts a footer with page numbers.
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

$docx = new CreateDocx();

$docx->addText('Page 1 Content');
$docx->addBreak(array('type' => 'page'));

$docx->addText('Page 2 Content');
$docx->addBreak(array('type' => 'page'));

$docx->addText('Page 3 Content');

$pager = $docx->addPageNumber('numerical', array('jc' =>'center', 'rawWordML' => true));

$myFooter = $docx->createWordMLFragment(array($pager));


$docx->addFooter(array('default' => $myFooter));

$docx->createDocx('../docx/example_footer_pager');