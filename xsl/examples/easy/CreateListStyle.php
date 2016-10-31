<?php

/**
 * Creates a custom list and inserts it in a Word document.
 *
 * @category   Phpdocx
 * @package    examples
 * @subpackage easy
 * @copyright  Copyright (c) 2009-2013 Narcea Producciones Multimedia S.L.
 *             (http://www.2mdc.com)
 * @license    http://www.phpdocx.com/wp-content/themes/lightword/pro_license.php
 * @version    2013.09.07
 * @link       http://www.phpdocx.com
 * @since      File available since Release 3.4
 */
require_once '../../classes/CreateDocx.inc';

$docx = new CreateDocx();

$listOptions = array();
$listOptions[0]['type'] = 'decimal';
$listOptions[0]['format'] = '[%1.]';
$listOptions[1]['type'] = 'lowerLetter';
$listOptions[1]['format'] = '[%1.%2.]';
$listOptions[1]['hanging'] = 540;

$docx->createListStyle('new', $listOptions);

$itemList = array(
    'Line 1',
    'Line 2',
    array('subitem_1', 'subitem_2'),
    'Line 4',
    'Line 5'
);

$options = array(
    'val' => 'new'
);
$docx->addText('Notice that the following list has a custom numbering style:');
$docx->addList($itemList, $options);
$docx->addText('Now the same list but with standard numbering:');
$docx->addList($itemList, array('val' => 2));
$html = '<ol class="new"><li>One</li><li>Two<ol class="old"><li>Two - One</li><li>Two - Two</li></ol></li></ol><p>New line.</p>';
$html .= '<ol class="new"><li>One</li><li>Two<ol class="old"><li>Two - One</li><li>Two - Two</li></ol></li></ol><p>New line.</p>';
$docx->addText('And now we insert the HTML lists.');
$docx->embedHTML($html, array('customListStyles' => true));
$docx->addText('And once again the same HTML list:');
$docx->embedHTML($html, array('customListStyles' => true));
$docx->addText('And once again the same HTML list but without custom stiles:');
$docx->embedHTML($html);
$docx->createDocx('../docx/example_liststyle');