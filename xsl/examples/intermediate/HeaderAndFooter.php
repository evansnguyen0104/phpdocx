<?php

/**
 * Inserts a header and footer with font styles.
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

$customLayout = array(
                    'width' => '11906',
                    'height' => '16838',
                    'numberCols' => '1',
                    'orient' => 'portrait',
                    'code' => '9',
                    'marginTop' => '1617',
                    'marginRight' => '1701',
                    'marginBottom' => '1417',
                    'marginLeft' => '1701',
                    'marginHeader' => '308',
                    'marginFooter' => '708',
                    'gutter' => '0'       
                );
$docx->modifyPageLayout('custom', $customLayout);

$headerImage = $docx->addImage(array('name' => '../files/img/image.png', 'dpi' => 300, 'rawWordML' => true, 'target' => 'defaultHeader'));
$myImage = $docx->createWordMLFragment(array($headerImage));

$pager = $docx->addPageNumber('numerical', array('jc' =>'right', 'rawWordML' => true));
$myPager = $docx->createWordMLFragment(array($pager));

$valuesTable = array(
    array(
        $myImage,
        $myPager
    )
);

$options = array('size_col' => array(4000, 4400), 'border' => 0, 'rawWordML' => true);

$headerTable = $docx->addTable($valuesTable, $options);
$myHeader = $docx->createWordMLFragment(array($headerTable));

$docx->addHeader(array('default' => $myHeader));

$htmlFooter ='<p style="font-weight: bold; text-align: center">A footer generated with HTML.</p>';
$footer = $docx->embedHTML($htmlFooter, array('rawWordML' => true, 'target' => 'defaultFooter'));
$myFooter = $docx->createWordMLFragment(array($footer));

$docx->addFooter(array('default' =>$myFooter));

$docx->addText('A Word document with a header and footer that illustrates how to include images and page numbering.');

$docx->createDocx('../docx/example_header_and_footer');