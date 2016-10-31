<?php

/**
 * Creates a document with different types of customized elements.
 *
 * @category   Phpdocx
 * @package    examples
 * @subpackage intermediate
 * @copyright  Copyright (c) 2009-2013 Narcea Producciones Multimedia S.L.
 *             (http://www.2mdc.com)
 * @license    http://www.phpdocx.com/wp-content/themes/lightword/pro_license.php
 * @version    2012.12.26
 * @link       http://www.phpdocx.com
 * @since      File available since Release 2.2
 */
require_once '../../classes/CreateDocx.inc';

$users = array(
				0 => array('name' => 'Don Mattingly',
							'value1' => '0.2',
							'value2' => '0.4',
							'value3' => '0.6',
							),
				1 => array('name' => 'Brian Sipe',
							'value1' => '0.3',
							'value2' => '0.3',
							'value3' => '0.4',
							),
				2 => array('name' => 'Julius Erving',
							'value1' => '0.1',
							'value2' => '0.2',
							'value3' => '0.7',
							)
);
				

foreach ($users as $user) {
	
	$docx = new CreateDocx();
	
	$docx->addBreak(array('type' => 'line'));

	$text = array();
	
	$text[] =
	    array(
	        'text' => 'Hi, ',
	);
	
	$text[] =
	    array(
	        'text' => $user['name'],
	        'b' => 'single',
	);
	
	$text[] =
	    array(
	        'text' => ' this is a sample text.'
	);
	
	$docx->addText($text);
	
	$docx->addBreak(array('type' => 'line'));
	
	$docx->addText('Lorem ipsum dolor sit amet, consectetur: ');
	
	$paramsList = array(
    	'val' => 1,
		'bullets' => array(3, 1, 2)
	);
	
	$valuesList = array(
	    'Donec tellus justo',
		    array(
		        'faucibus nec commodo quis',
		        'dignissim ut ipsum',
		        'Aenean hendrerit interdum',
				    array(
				        'Morbi malesuada luctus libero',
				        'sodales est placerat eget',
				        'Aenean eget nulla vel'
				    ),
		    ),
	    'enim viverra iaculis',
	    'aliquet aliquam nisl',
	);
	$docx->addList($valuesList, $paramsList);

	$docx->addBreak(array('type' => 'page'));
	
	$legends = array(
	    'legend1' => array($user['value1']),
	    'legend2' => array($user['value2']),
	    'legend3' => array($user['value3'])
	);
	$args = array(
	    'data' => $legends,
	    'type' => 'pie3DChart',
	    'title' => $user['name'] . '\'s chart',
	    'rotX' => 20, 'rotY' => 20, 'perspective' => 30,
	    'color' => 2,
	    'textWrap' => 0,
	    'sizeX' => 10, 'sizeY' => 10,
	    'jc' => 'left',
	    'showPercent' => 1,
	    'font' => 'Times New Roman'
	);
	$docx->addChart($args);
	
	$docx->createDocx('../docx/example_multidocument_' . $user['name']);

}