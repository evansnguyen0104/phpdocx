<?php

/**
 * Inserts a chunk of WordML code into the Word document
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

$wml = '<w:p><w:r><w:t>Hello world!</w:t></w:r></w:p>';

$docx->addWordML(array('wordML' => $wml));

$docx->createDocx('../docx/example_wordml');