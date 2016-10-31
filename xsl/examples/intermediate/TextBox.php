<?php 

/**
 * Textbox with all parameters
 *
 * @category   Phpdocx
 * @package    examples
 * @subpackage intermediate
 * @copyright  Copyright (c) 2009-2013 Narcea Producciones Multimedia S.L.
 *             (http://www.2mdc.com)
 * @license    http://www.phpdocx.com/wp-content/themes/lightword/pro_license.php
 * @version    2012.12.26
 * @link       http://www.phpdocx.com
 * @since      File available since Release 2.7
 */

require_once '../../classes/CreateDocx.inc';

$docx = new CreateDocx();

$paramsText = array(
    'b' => 'single',
    'font' => 'Arial'
);

$text = 'Lorem ipsum dolor sit amet, consectetur adipisicing elit, ' .
    'sed do eiusmod tempor incididunt ut labore et dolore magna aliqua. Ut ' .
    'enim ad minim veniam, quis nostrud exercitation ullamco laboris nisi ut' .
    'aliquip ex ea commodo consequat. Duis aute irure dolor in reprehenderit ' .
    'in voluptate velit esse cillum dolore eu fugiat nulla pariatur. ' .
    'Excepteur sint occaecat cupidatat non proident, sunt in culpa qui ' .
    'officia deserunt mollit anim id est laborum.';

$paramsTextBox = array(
    'width' => 5,
    'height' => 15,
    'textWrap' => 'aboveText', //tight,square, none(inline), through, aboveText, belongText
    'jc' => 'left',
    'margin_top' => 0,
	'margin_right' => 0,
	'margin_bottom' => 0,
	'margin_left' => 4,
	'padding_top' => 1,
	'padding_left' => 1,
    'padding_right' => 1,
    'padding_bottom' => 1,
    'fillcolor' => red,
    'border' => 0
);

$docx->addTextBox(
    array(
        'text' => $text,
        'args' => $paramsText
    ),
    $paramsTextBox
);

$docx->createDocx('../docx/example_textbox');
