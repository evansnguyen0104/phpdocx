<?php

/**
 * Creates a table with embeded styles.
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

$docx = new CreateDocx();

$frameworks = array(
				array('name' => 'Code Igniter',
					'ajax' => 'Prototype/script.aculo.us, jQuery/jQuery UI',
					'mvc' => 'Modified active record pattern',
					'orm' => 'No',
					'security' => 'Yes'
				),
				array('name' => 'Drupal',
					'ajax' => 'jQuery/jQuery UI, more',
					'mvc' => 'No',
					'orm' => 'Optional module',
					'security' => 'Yes'
				),
				array('name' => 'eZ Components',
					'ajax' => 'No',
					'mvc' => 'Yes',
					'orm' => 'Yes',
					'security' => 'Yes'
				),
				array('name' => 'Symfony',
					'ajax' => 'Prototype, script.aculo.us, Unobtrusive Ajax ' .
							'with UJS and PJS plugins',
					'mvc' => 'Push',
					'orm' => 'Yes',
					'security' => 'Plugin'
				),
				array('name' => 'Zend Framework',
					'ajax' => 'Toolkit-independent',
					'mvc' => 'Push and Pull',
					'orm' => 'Yes',
					'security' => 'ACL-based'
				)
);

$headerStyle[0] = array(
	'b' => 'single',
	'font' => 'Arial',
);

$table[] = array(
    '',
    'Ajax',
	'MVC framework',
    'ORM',
	'Security Framework(s)'
);

foreach ($frameworks as $framework) {
	$headerStyle[0]['text'] = $framework['name'];
    $table[] = array(
        $docx->addElement('addText', $headerStyle),
        $framework['ajax'],
        $framework['mvc'],
        $framework['orm'],
        $framework['security']
    );
}
    
$paramsTable = array(
    'TBLSTYLEval' => 'MediumShading1PHPDOCX',
    'border' => 'single',
    'border_sz' => 20,
    'border_spacing' => 0,
    'border_color' => '000000',
    'jc' => 'center',
    'size_col' => 2800
);

$docx->addTable($table, $paramsTable);

$docx->createDocx('../docx/example_table_styled');