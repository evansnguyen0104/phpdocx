<?php

/**
 * Inserts a simple text in bold Arial font.
 *
 * @category   Phpdocx
 * @package    examples
 * @subpackage easy
 * @copyright  Copyright (c) 2009-2013 Narcea Producciones Multimedia S.L.
 *             (http://www.2mdc.com)
 * @license    http://www.phpdocx.com/wp-content/themes/lightword/pro_license.php
 * @version    2013.05.20
 * @link       http://www.phpdocx.com
 * @since      2013.05.20
 */

require_once '../../classes/CreateDocx.inc';

$docx = new CreateDocx();

$text = 'Lorem ipsum dolor sit amet, consectetur adipisicing elit, ' .
    'sed do eiusmod tempor incididunt ut labore et dolore magna aliqua.';

$title = 'Title....';

$options = array(
    'color' => 'FF0000',
    'i' => 'on',
    'jc' => 'center',
    'sz' => 13
    );

$docx->addHeading($title."1",0);
$docx->addText($text);

$docx->addHeading($title."2",3);
$docx->addText($text);

$docx->addHeading($title."3",1,$options);
$docx->addText($text);

$docx->createDocx('../docx/example_heading');
