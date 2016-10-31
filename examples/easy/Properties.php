<?php

/**
 * Modify the document properties.
 *
 * @category   Phpdocx
 * @package    examples
 * @subpackage easy
 * @copyright  Copyright (c) 2009-2013 Narcea Producciones Multimedia S.L.
 *             (http://www.2mdc.com)
 * @license    http://www.phpdocx.com/wp-content/themes/lightword/pro_license.php
 * @version    2012.12.26
 * @link       http://www.phpdocx.com
 * @since      File available since Release 2.2
 */
require_once '../../classes/CreateDocx.inc';

$docx = new CreateDocx();

$paramsProperties = array(
    'title' => 'My title',
    'subject' => 'My subject',
    'creator' => 'The creator',
    'keywords' => 'keyword 1, keyword 2, keyword 3',
    'description' => 'The description could be much longer than this',
    'category' => 'My category',
    'contentStatus' => 'Draft',
    'Manager' => 'The boss',
    'Company' => 'My company',
    'custom' => array(
    						'My custom text' => array('text' => 'This is a reasonably large text'), 
    						'My custom number' => array('number' => '4567'),
    						'My custom date' => array('date' => '1962-01-27T23:00:00Z'),
    						'My custom boolean' => array('boolean' => true)
    						)    						
);
$docx->addProperties($paramsProperties);

$docx->createDocx('../docx/example_properties');