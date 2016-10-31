<?php

/**
 * Embeds shapes into a table using addParagraph
 *
 * @category   Phpdocx
 * @package    examples
 * @subpackage intermediate
 * @copyright  Copyright (c) 2009-2013 Narcea Producciones Multimedia S.L.
 *             (http://www.2mdc.com)
 * @license    http://www.phpdocx.com/wp-content/themes/lightword/pro_license.php
 * @version    2012.12.26
 * @link       http://www.phpdocx.com
 * @since      2012.12.26
 */

require_once '../../classes/CreateDocx.inc';

$docx = new CreateDocx();

$colors = array('red' =>'b70000',
                'grey' => '999999',
                'blue' => '2565ee',
                'green' => '25ee65');

$tableValues = array();

foreach($colors as $key => $value){
	$options = array('spacingTop' => 0, 'spacingBottom' => 0, 'rawWordML' => true);
	$rect = array('type' => 'rect',
                'width' => 10,
                'height' => 10,
                'strokecolor' => '#555555',
                'strokeweight' => '1',
                'fillcolor' => '#'.$value);
	$shapeData = $docx->addParagraph(array($rect), $options);

	$text_1 = array('color' => '000000',
                  'font' => 'Arial',
                  'sz' => '11',
                  'type' => 'text',
                  'text' => 'This is the color of the following chunk of text: '
               );
	$text_2 = array('color' => $value,
                  'font' => 'Arial',
                  'sz' => '11',
                  'type' => 'text',
                  'text' => $key.' characters.'
               );
  $textData = $docx->addParagraph(array($text_1, $text_2), $options);
  
  $shape = $docx->createWordMLFragment($shapeData);
  $text = $docx->createWordMLFragment($textData);

  $tableRow = array($shape, $text);
  $tableValues[] = $tableRow;
}

$tableOptions = array('border' => 'none');
$docx->addTable($tableValues, $tableOptions);

$docx->createDocx('../docx/example_embedded_shapes');