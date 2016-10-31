<?php

/**
 * Inserts a merge field into a Word document.
 *
 * @category   Phpdocx
 * @package    examples
 * @subpackage easy
 * @copyright  Copyright (c) 2009-2013 Narcea Producciones Multimedia S.L.
 *             (http://www.2mdc.com)
 * @license    http://www.phpdocx.com/wp-content/themes/lightword/pro_license.php
 * @version    2013.10.28
 * @link       http://www.phpdocx.com
 * @since      2013.10.28
 */

require_once '../../classes/CreateDocx.inc';

$docx = new CreateDocx();
//Text field

$mergeParameters = array('format' => 'Upper', 'textBefore' => 'An example: ', 'textAfter' => ' and that is it');
$options = array('b' => 'on');
$docx->addMergeField('MyMergeField example', $mergeParameters, $options);

$docx->createDocx('../docx/example_mergefield');
