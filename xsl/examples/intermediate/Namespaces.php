<?php

/**
 * Use PHPDocX with a namespace. Only for PHP 5.3+
 *
 * @category   Phpdocx
 * @package    examples
 * @subpackage intermediate
 * @copyright  Copyright (c) 2009-2013 Narcea Producciones Multimedia S.L.
 *             (http://www.2mdc.com)
 * @license    http://www.phpdocx.com/wp-content/themes/lightword/pro_license.php
 * @version    2013.06.20
 * @link       http://www.phpdocx.com
 * @since      2013.06.20
 */
require_once '../../lib/UniversalClassLoader.php';
require_once '../../classes/Phpdocx_Phpdocx.inc';

$loader = new UniversalClassLoader();
$loader->registerPrefixes(array(
    'Phpdocx_' => dirname(__FILE__).'/../classes',
));
$loader->register();

$docx = new \Phpdocx_Phpdocx();

$text = 'Lorem ipsum dolor sit amet, consectetur adipisicing elit.';

$docx->addText($text);

$docx->createDocx('../docx/example_namespaces');