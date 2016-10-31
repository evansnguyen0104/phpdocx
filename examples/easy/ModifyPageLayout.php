<?php

/**
 * Modify the layout of a Word document.
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

for($j=0; $j < 50; $j++){

	$text = 'Lorem ipsum dolor sit amet, consectetur adipisicing elit, ' .
	    'sed do eiusmod tempor incididunt ut labore et dolore magna aliqua. Ut ' .
	    'enim ad minim veniam, quis nostrud exercitation ullamco laboris nisi ut' .
	    'aliquip ex ea commodo consequat. Duis aute irure dolor in reprehenderit ' .
	    'in voluptate velit esse cillum dolore eu fugiat nulla pariatur. ' .
	    'Excepteur sint occaecat cupidatat non proident, sunt in culpa qui ' .
	    'officia deserunt mollit anim id est laborum.';
	
	$docx->addText($text);
}

$docx->modifyPageLayout('A3-landscape', array('numberCols' => '3'));

$docx->createDocx('../docx/example_modify_page_layout');