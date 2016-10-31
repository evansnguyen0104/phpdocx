<?php

/**
 * Inserts a footnote and an endnote into a Word document.
 *
 * @category   Phpdocx
 * @package    examples
 * @subpackage intermediate
 * @copyright  Copyright (c) 2009-2013 Narcea Producciones Multimedia S.L.
 *             (http://www.2mdc.com)
 * @license    http://www.phpdocx.com/wp-content/themes/lightword/pro_license.php
 * @version    2012.12.26
 * @link       http://www.phpdocx.com
 * @since      File available since Release 1.8
 */
require_once '../../classes/CreateDocx.inc';

$docx = new CreateDocx();

$docx->addEndnote(
    array(
        'textDocument' => 'Lorem ipsum dolor sit amet',
        'textEndnote' => 'endnote'
    )
);

$docx->addFootnote(
    array(
        'textDocument' => 'Lorem ipsum dolor sit amet',
        'textFootnote' => 'footnote'
    )
);

$docx->createDocx('../docx/example_endnote_footnote');
