<?php

/**
 * Insert runs of text with different styles in the same paragraph.
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

$text = array();

$text[] =
    array(
        'text' => 'Lorem ipsum',
        'u' => 'single',
);

$text[] =
    array(
        'text' => ' sed do eiusmod tempor incididunt',
        'b' => 'single',
);

$docx->addText($text);

$docx->createDocx('../docx/example_text');