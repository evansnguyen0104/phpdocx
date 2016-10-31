<?php

/**
 * removes a template variable and its container paragraph from a PHPDocX Word template.
 *
 * @category   Phpdocx
 * @package    examples
 * @subpackage easy
 * @copyright  Copyright (c) 2009-2013 Narcea Producciones Multimedia S.L.
 *             (http://www.2mdc.com)
 * @license    http://www.phpdocx.com/wp-content/themes/lightword/pro_license.php
 * @version    2013.02.28
 * @link       http://www.phpdocx.com
 * @since      2013.02.28
 */

require_once '../../classes/CreateDocx.inc';


$docx = new CreateDocx();

$docx->addTemplate('../files/TemplateClean.docx');

$docx->cleanTemplateVariable('VARIABLE', 'block');

$docx->createDocx('../docx/example_clean_template_variable');


