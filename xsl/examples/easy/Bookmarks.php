<?php

/**
 * Adds a bookmark anywhere in a Word document.
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

$docx->addText('Some random text.');
$docx->addBookmark(array('type' => 'start', 'name' => 'bookmark_name'));
$docx->addText('Text that has been bookmarked.');
$docx->addBookmark(array('type' => 'end', 'name' => 'bookmark_name'));
$docx->addText('Another line of text.');
$docx->addParagraph(array(array('text' => 'link to the bookmark.', 'type' => 'link', 'URL' => '#bookmark_name', 'color' => '000000')), array('color' => '000000'));

$docx->createDocx('../docx/example_bookmarks');
