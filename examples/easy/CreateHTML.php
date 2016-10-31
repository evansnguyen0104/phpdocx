<?php

/**
 * Transform DOCX into HTML
 *
 * @category   Phpdocx
 * @package    examples
 * @subpackage easy
 * @copyright  Copyright (c) 2009-2013 Narcea Producciones Multimedia S.L.
 *             (http://www.2mdc.com)
 * @license    http://www.phpdocx.com/wp-content/themes/lightword/pro_license.php
 * @version    1.8
 * @link       http://www.phpdocx.com
 * @since      File available since Release 1.8
 */
require_once '../../classes/CreateDocx.inc';

$document = new TransformDoc();
$document->setStrFile('../files/Text.docx');
$document->generateXHTML();
$document->validatorXHTML();
echo $document->getStrXHTML();
