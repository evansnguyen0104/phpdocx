<?php

/**
 * Inserts a paragraph with complex formatting, floating images, links, bookmarks, footnotes/endnotes.
 *
 * @category   Phpdocx
 * @package    examples
 * @subpackage intermediate
 * @copyright  Copyright (c) 2009-2013 Narcea Producciones Multimedia S.L.
 *             (http://www.2mdc.com)
 * @license    http://www.phpdocx.com/wp-content/themes/lightword/pro_license.php
 * @version    2012.12.26
 * @link       http://www.phpdocx.com
 * @since      File available since Release 2.6
 */

require_once '../../classes/CreateDocx.inc';

$docx = new CreateDocx();

$docx->addText('This is a simple paragraph.');

$options =array('jc' => 'left',
                'sz' => '11',
               );

$run_1 =array('color' => 'ff0000',
              'font' => 'Arial',
              'i' => 'single',
              'sz' => '11',
              'type' => 'text',
              'text' => 'This is a run of text written in Arial 11pt, red and italics to illustrate how easy is to apply formatting to a run of text. '
               );
$break = array('type' => 'lineBreak');
$run_2 =array('color' => '00ff00',
              'font' => 'Arial',
              'sz' => '12',
              'type' => 'text',
              'text' => 'This is a run of text written in Arial 12pt and green color so you may check how properties are inherited or not from the general paragraph options. '
               );    
$image_1 = array('type' => 'image',
                    'src' => '../files/img/logo_header.jpg', 
                    'border' => 1, 
                    'borderColor' => '444',
                    'spacingLeft' => 20, 
                    'spacingRight' => 0, 
                    'spacingTop' => 10, 
                    'spacingBottom' => 10, 
                    'position' => 'right');                          
$run_3 =array('sz' => '11',
              'type' => 'text',
              'text' => 'This run of text is written in normal black text with the default document font (usually calibri).
                         Since PHPDocX v2.6 we may insert in a simple manner paragraphs that include complex formatting,
                         floating images, links, bookmarks and even footnotes and endnotes in a very simple manner. '
               ); 
$run_4 =array('type' => 'text',
              'text' => 'To include a footnote'
               ); 
$footnote_1 = array('type' => 'footnote',
                    'sz' => '10',
                    'color' => '555',
                    'text' => 'You can even style the footnotes content, please, look in the documentation.'      
										);         
$run_5 =array('type' => 'text',
              'text' => 'in the middle of the paragraph is as simple as this.'
               );              
$link_1 =array('type' => 'link',
               'URL' => 'http://www.phpdocx.com',
               'text' => ' We also include this link'
               );
$bookmark_1 = array('type' => 'link',
                    'markerName' => 'personal',
                    'sz' => '11',
                    'text' => '. And we finish this paragraph bookmarking this run of text.'      
										);                
               
$parameters = array($run_1, $break, $run_2, $image_1, $run_3, $run_4, $footnote_1, $run_5, $link_1, $bookmark_1);

$docx->addParagraph($parameters, $options);

$run_1=array('type' => 'text',
              'text' => 'We may now link internally to the bookmark we have included '
               );              
$link_1 =array('type' => 'link',
               'URL' => '#personal',
               'text' => 'here'
               );
$run_3=array('type' => 'text',
              'text' => ' just by including a URL parameter as it is done usually with anchors.'
               );
               
$parameters2 = array($run_1, $link_1, $run_3);     
$docx->addParagraph($parameters2, $options);
         


$docx->addText('We are now going to insert the first complex paragraph in a table cell:');

$options =array('jc' => 'left',
                'sz' => '11',
                'rawWordML' => true
               );
$Pdata = $docx->addParagraph($parameters, $options);

$fragment = $docx->createWordMLFragment($Pdata);

$valuesTable = array(
    array(
        11,
        12
    ),
    array(
        $fragment,
        22
    ),
);

$paramsTable = array(
    'border' => 'single',
    'border_sz' => 5,
);

$test = $docx->addTable($valuesTable, $paramsTable);

$docx->createDocx('../docx/example_complex_paragraph');