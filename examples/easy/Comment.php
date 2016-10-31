<?php

/**
 * Inserts a coment in the middle of a run of text.
 *
 * @category   Phpdocx
 * @package    examples
 * @subpackage easy
 * @copyright  Copyright (c) 2009-2013 Narcea Producciones Multimedia S.L.
 *             (http://www.2mdc.com)
 * @license    http://www.phpdocx.com/wp-content/themes/lightword/pro_license.php
 * @version    2013.08.26
 * @link       http://www.phpdocx.com
 * @since      2013.08.26
 */

require_once '../../classes/CreateDocx.inc';

$docx = new CreateDocx();

$commentData = $docx->addComment(
    array(
        'textDocument' => 'comment',
        'textComment' => 'The comment we want to insert.',
        'initials' => 'PT',
        'author' => 'PHPDocX Team',
        'date' => '10 September 2000',
        'rawWordML' => true,
    )
);

$commentFragment = $docx->createWordMLFragment($commentData);


$text = array();
$text[]= array('text' => 'Here comes the ');
$text[]= $commentFragment;
$text[]= array('text' => ' and some other text.');

$paragraphOptions = array('i' => 'on');

$docx->addText($text, $paragraphOptions);


$docx->createDocx('../docx/example_comment');