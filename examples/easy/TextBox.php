<?php

/**
 * Inserts a textbox in a Word document.
 *
 * @category   Phpdocx
 * @package    examples
 * @subpackage easy
 * @copyright  Copyright (c) 2009-2013 Narcea Producciones Multimedia S.L.
 *             (http://www.2mdc.com)
 * @license    http://www.phpdocx.com/wp-content/themes/lightword/pro_license.php
 * @version    2012.12.26
 * @link       http://www.phpdocx.com
 * @since      File available since Release 1.8
 */
require_once '../../classes/CreateDocx.inc';

$docx = new CreateDocx();

$paramsText = array(
    'b' => 'single',
    'font' => 'Arial',
    'color' => 'red'
);

$text = 'Lorem ipsum dolor sit amet, consectetur adipisicing elit, ' .
    'sed do eiusmod tempor incididunt ut labore et dolore magna aliqua. Ut ' .
    'enim ad minim veniam, quis nostrud exercitation ullamco laboris nisi ut' .
    'aliquip ex ea commodo consequat. Duis aute irure dolor in reprehenderit ' .
    'in voluptate velit esse cillum dolore eu fugiat nulla pariatur. ' .
    'Excepteur sint occaecat cupidatat non proident, sunt in culpa qui ' .
    'officia deserunt mollit anim id est laborum.';

$options = array(
    'width' => 10,
    'height' => 8,
    'fillcolor' => '#0000ff',
    'textWrap' => 'square',
    'padding_left' => 2.1,
    'padding_top' => 1,
    'padding-right' => 0.5,
    'margin_top' => 1,
    'margin_left' => 2,
    //'border' => 4,
    //'border_color' => 'green'
);

$docx->addTextBox(
    array(
        'text' => $text,
        'args' => $paramsText
    ),
    $options
);

$docx->createDocx('../docx/example_textbox');