<?php

/**
 * Inserts current date and hour into a Word document
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

$options_1 = array('b' => 'on',
                 'sz' => 12,
                 'color' => 'b70000',
                 'dateFormat' => 'dd/MM/yyyy H:mm:ss',
                 'rawWordML' => true);

$date = $docx->addDateAndHour($options_1);

$WordMLFragment = $docx->createWordMLFragment(array($date));

$docx->addHeader(array('default' => $WordMLFragment));

$docx->addText('Let us include now different examples of the addDateAndHour with different date formatting:');

$options_2 = array('jc' => 'center', 
                 'b' => 'on',
                 'sz' => 14,
                 'color' => '333333',
                 'dateFormat' => "dd' of 'MMMM' of 'yyyy' at 'H:mm");

$docx->addDateAndHour($options_2);

$options_3 = array('b' => 'on',
                 'sz' => 11,
                 'color' => 'blue',
                 'dateFormat' => "MM'-'dd'-'yy");

$docx->addDateAndHour($options_3);

$docx->createDocx('../docx/example_dateAndHour');