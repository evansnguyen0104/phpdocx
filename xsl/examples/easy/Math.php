<?php

/**
 * Insert a math equation into a Word document.
 *
 * @category   Phpdocx
 * @package    examples
 * @subpackage easy
 * @copyright  Copyright (c) 2009-2013 Narcea Producciones Multimedia S.L.
 *             (http://www.2mdc.com)
 * @license    http://www.phpdocx.com/wp-content/themes/lightword/pro_license.php
 * @version    2012.12.26
 * @link       http://www.phpdocx.com
 * @since      File available since Release 2.0
 */
require_once '../../classes/CreateDocx.inc';

$docx = new CreateDocx();

$docx->addMathEq(
    '<m:oMathPara>
        <m:oMath><m:r><m:t>∪±∞=~×</m:t></m:r></m:oMath>
    </m:oMathPara>'
);

$docx->addMathDocx('../files/math.docx');

$docx->createDocx('../docx/example_math');