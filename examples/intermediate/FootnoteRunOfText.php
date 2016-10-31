<?php

/**
 * Inserts an footnote in the middle of a run of text.
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

$footnoteData = $docx->addFootnote(
    array(
        'textDocument' => '',
        'textFootnote' => 'This is the footnote text.',
        'rawWordML' => true,
    )
);

$footnoteFragment = $docx->createWordMLFragment($footnoteData);
                    

$text = array();
$text[]= array('text' => 'Here comes the footnote');
$text[]= $footnoteFragment;
$text[]= array('text' => ' and some other text.');

$paragraphOptions = array('i' => 'on');

$docx->addText($text, $paragraphOptions);

$docx->createDocx('../docx/example_run_footnote');