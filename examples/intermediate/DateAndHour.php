<?php

/**
 * Inserts the date in a run of text.
 *
 * @category   Phpdocx
 * @package    examples
 * @subpackage intermediate
 * @copyright  Copyright (c) 2009-2013 Narcea Producciones Multimedia S.L.
 *             (http://www.2mdc.com)
 * @license    http://www.phpdocx.com/wp-content/themes/lightword/pro_license.php
 * @version    2013.03.06
 * @link       http://www.phpdocx.com
 * @since      File available since Release 3.2
 */

require_once '../../classes/CreateDocx.inc';

$docx = new CreateDocx();

$dateOptions = array('b' => 'on',
'color' => 'b70000',
'dateFormat' => "dd' of 'MMMM' of 'yyyy",
'rawWordML' => true);

$dateData = $docx->addDateAndHour($dateOptions);
$dateFragment = $docx->createWordMLFragment($dateData);

$text = array();
$text[]= array('text' => 'Today is the ');
$text[]= $dateFragment;
$text[]= array('text' => ' and it is a beautiful day.');

$docx->addText($text);

$docx->createDocx('../docx/example_date');