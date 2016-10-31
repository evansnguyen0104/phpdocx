<?php

/**
 * Add simple HTML code in a DOCX file
 *
 * @category   Phpdocx
 * @package    examples
 * @subpackage intermediate
 * @copyright  Copyright (c) 2009-2013 Narcea Producciones Multimedia S.L.
 *             (http://www.2mdc.com)
 * @license    http://www.phpdocx.com/wp-content/themes/lightword/pro_license.php
 * @version    2012.12.26
 * @link       http://www.phpdocx.com
 * @since      File available since Release 1.8
 */

require_once '../../classes/CreateDocx.inc';

$docx = new CreateDocx();

$html= '<p>This will insert the name in the document: <strong>
          <span style="font-size:33px;">My name</span></strong></p>';

$docx->addHTML(array('html' => $html));

$docx->createDocx('../docx/example_basic_html');
