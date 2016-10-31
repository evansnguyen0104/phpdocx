<?php

/**
 * ikcs or unticks a checkbox in a Word template.
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
 
$docx->addTemplate('../files/Checkbox.docx');
 
$docx->tickCheckbox ('check1', 1);
$docx->tickCheckbox ('check2', 0);
$docx->tickCheckbox ('check3', 1);
 
$docx->createDocx('../docx/example_tickCheckbox');