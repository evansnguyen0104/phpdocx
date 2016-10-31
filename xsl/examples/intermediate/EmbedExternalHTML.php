<?php

/**
 * Embed some external HTML content
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

$docx= new CreateDocx();

$docx->embedHTML('<h1 style="color: #b70000">The Wikipedia Article on the Periodic Table</h1>');

$html = file_get_contents('http://en.wikipedia.org/wiki/Periodic_table');

$docx->embedHTML($html, array('parseDivsAsPs' => true, 'baseURL' => 'http://en.wikipedia.org/', 'downloadImages' => true, 'filter' => '#bodyContent'));

$docx->modifyPageLayout('A3');

$docx->createDocx('../docx/example_embedExternalHTML');