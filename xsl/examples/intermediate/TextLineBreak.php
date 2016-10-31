<?php

/**
 * Inserts a line break between runs of text with different styles in the same paragraph.
 *
 * @category   Phpdocx
 * @package    examples
 * @subpackage intermediate
 * @copyright  Copyright (c) 2009-2011 Narcea Producciones Multimedia S.L.
 *             (http://www.2mdc.com)
 * @license    http://www.phpdocx.com/wp-content/themes/lightword/pro_license.php
 * @version    2013.01.04
 * @link       http://www.phpdocx.com
 * @since      2013.01.04
 */
require_once '../../classes/CreateDocx.inc';

$docx = new CreateDocx();

$text = array();

$text[] =
    array(
        'text' => 'Lorem ipsum',
        'u' => 'single',
        'lineBreak' => 'after'
);

$text[] =
    array(
        'text' => ' sed do eiusmod tempor incididunt',
        'b' => 'on',
        'color' => '000000',
        
);

$docx->addText($text, array('color' => 'b70000'));


$docx->createDocx('../docx/example_text_lineBreak');