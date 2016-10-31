<?php

/**
 * Embed some HTML in a Word document: table with row and col spans.
 *
 * @category   Phpdocx
 * @package    examples
 * @subpackage easy
 * @copyright  Copyright (c) 2009-2013 Narcea Producciones Multimedia S.L.
 *             (http://www.2mdc.com)
 * @license    http://www.phpdocx.com/wp-content/themes/lightword/pro_license.php
 * @version    2012.12.26
 * @link       http://www.phpdocx.com
 * @since      2012.12.26
 */
require_once '../../classes/CreateDocx.inc';

$docx= new CreateDocx();

$html= '<p style="border: 2px solid black; color: red">A short text with a red border.</p>';
$html= '<p>And now we draw a table with border and rawspans and colspans:</p>';
$html.= '<table border="1">';
$html.= '<tbody><tr><td style="background-color: yellow">1_1</td><td rowspan="3" colspan="2">1_2</td></tr>';
$html.='<tr><td>Some random text.</td></tr>';
$html.='<tr><td><ul><li>One</li><li>Two <b>and a half</b></li></ul></td></tr>';
$html.='<tr><td>3_2</td><td>3_3</td><td>3_3</td></tr></tbody>';
$html.= '</table>';
$html.= '<table border="1">';
$html.= '<tbody><tr><td style="background-color: yellow">1_1</td><td rowspan="3" colspan="2">1_2</td></tr>';
$html.='<tr><td>Some random text.</td></tr>';
$html.='<tr><td><ul><li>One</li><li>Two <b>and a half</b></li></ul></td></tr>';
$html.='<tr><td>3_2</td><td>3_3</td><td>3_3</td></tr></tbody>';
$html.= '</table>';
$html.= '<table border="1">';
$html.= '<tbody><tr><td style="background-color: yellow">1_1</td><td rowspan="3" colspan="2">1_2</td></tr>';
$html.='<tr><td>Some random text.</td></tr>';
$html.='<tr><td><ul><li>One</li><li>Two <b>and a half</b></li></ul></td></tr>';
$html.='<tr><td>3_2</td><td>3_3</td><td>3_3</td></tr></tbody>';
$html.= '</table>';
$html.= '<table border="1">';
$html.= '<tbody><tr><td style="background-color: yellow">1_1</td><td rowspan="3" colspan="2">1_2</td></tr>';
$html.='<tr><td>Some random text.</td></tr>';
$html.='<tr><td><ul><li>One</li><li>Two <b>and a half</b></li></ul></td></tr>';
$html.='<tr><td>3_2</td><td>3_3</td><td>3_3</td></tr></tbody>';
$html.= '</table>';
$html.= '<table border="1">';
$html.= '<tbody><tr><td style="background-color: yellow">1_1</td><td rowspan="3" colspan="2">1_2</td></tr>';
$html.='<tr><td>Some random text.</td></tr>';
$html.='<tr><td><ul><li>One</li><li>Two <b>and a half</b></li></ul></td></tr>';
$html.='<tr><td>3_2</td><td>3_3</td><td>3_3</td></tr></tbody>';
$html.= '</table>';
$html.= '<table border="1">';
$html.= '<tbody><tr><td style="background-color: yellow">1_1</td><td rowspan="3" colspan="2">1_2</td></tr>';
$html.='<tr><td>Some random text.</td></tr>';
$html.='<tr><td><ul><li>One</li><li>Two <b>and a half</b></li></ul></td></tr>';
$html.='<tr><td>3_2</td><td>3_3</td><td>3_3</td></tr></tbody>';
$html.= '</table>';
$html.= '<table border="1">';
$html.= '<tbody><tr><td style="background-color: yellow">1_1</td><td rowspan="3" colspan="2">1_2</td></tr>';
$html.='<tr><td>Some random text.</td></tr>';
$html.='<tr><td><ul><li>One</li><li>Two <b>and a half</b></li></ul></td></tr>';
$html.='<tr><td>3_2</td><td>3_3</td><td>3_3</td></tr></tbody>';
$html.= '</table>';
$html.= '<table border="1">';
$html.= '<tbody><tr><td style="background-color: yellow">1_1</td><td rowspan="3" colspan="2">1_2</td></tr>';
$html.='<tr><td>Some random text.</td></tr>';
$html.='<tr><td><ul><li>One</li><li>Two <b>and a half</b></li></ul></td></tr>';
$html.='<tr><td>3_2</td><td>3_3</td><td>3_3</td></tr></tbody>';
$html.= '</table>';
$html.= '<table border="1">';
$html.= '<tbody><tr><td style="background-color: yellow">1_1</td><td rowspan="3" colspan="2">1_2</td></tr>';
$html.='<tr><td>Some random text.</td></tr>';
$html.='<tr><td><ul><li>One</li><li>Two <b>and a half</b></li></ul></td></tr>';
$html.='<tr><td>3_2</td><td>3_3</td><td>3_3</td></tr></tbody>';
$html.= '</table>';
$html.= '<table border="1">';
$html.= '<tbody><tr><td style="background-color: yellow">1_1</td><td rowspan="3" colspan="2">1_2</td></tr>';
$html.='<tr><td>Some random text.</td></tr>';
$html.='<tr><td><ul><li>One</li><li>Two <b>and a half</b></li></ul></td></tr>';
$html.='<tr><td>3_2</td><td>3_3</td><td>3_3</td></tr></tbody>';
$html.= '</table>';
$html.= '<table border="1">';
$html.= '<tbody><tr><td style="background-color: yellow">1_1</td><td rowspan="3" colspan="2">1_2</td></tr>';
$html.='<tr><td>Some random text.</td></tr>';
$html.='<tr><td><ul><li>One</li><li>Two <b>and a half</b></li></ul></td></tr>';
$html.='<tr><td>3_2</td><td>3_3</td><td>3_3</td></tr></tbody>';
$html.= '</table>';
$html.= '<table border="1">';
$html.= '<tbody><tr><td style="background-color: yellow">1_1</td><td rowspan="3" colspan="2">1_2</td></tr>';
$html.='<tr><td>Some random text.</td></tr>';
$html.='<tr><td><ul><li>One</li><li>Two <b>and a half</b></li></ul></td></tr>';
$html.='<tr><td>3_2</td><td>3_3</td><td>3_3</td></tr></tbody>';
$html.= '</table>';
$html.= '<table border="1">';
$html.= '<tbody><tr><td style="background-color: yellow">1_1</td><td rowspan="3" colspan="2">1_2</td></tr>';
$html.='<tr><td>Some random text.</td></tr>';
$html.='<tr><td><ul><li>One</li><li>Two <b>and a half</b></li></ul></td></tr>';
$html.='<tr><td>3_2</td><td>3_3</td><td>3_3</td></tr></tbody>';
$html.= '</table>';
$html.= '<table border="1">';
$html.= '<tbody><tr><td style="background-color: yellow">1_1</td><td rowspan="3" colspan="2">1_2</td></tr>';
$html.='<tr><td>Some random text.</td></tr>';
$html.='<tr><td><ul><li>One</li><li>Two <b>and a half</b></li></ul></td></tr>';
$html.='<tr><td>3_2</td><td>3_3</td><td>3_3</td></tr></tbody>';
$html.= '</table>';
$html.= '<table border="1">';
$html.= '<tbody><tr><td style="background-color: yellow">1_1</td><td rowspan="3" colspan="2">1_2</td></tr>';
$html.='<tr><td>Some random text.</td></tr>';
$html.='<tr><td><ul><li>One</li><li>Two <b>and a half</b></li></ul></td></tr>';
$html.='<tr><td>3_2</td><td>3_3</td><td>3_3</td></tr></tbody>';
$html.= '</table>';
$html.= '<table border="1">';
$html.= '<tbody><tr><td style="background-color: yellow">1_1</td><td rowspan="3" colspan="2">1_2</td></tr>';
$html.='<tr><td>Some random text.</td></tr>';
$html.='<tr><td><ul><li>One</li><li>Two <b>and a half</b></li></ul></td></tr>';
$html.='<tr><td>3_2</td><td>3_3</td><td>3_3</td></tr></tbody>';
$html.= '</table>';
$html.= '<table border="1">';
$html.= '<tbody><tr><td style="background-color: yellow">1_1</td><td rowspan="3" colspan="2">1_2</td></tr>';
$html.='<tr><td>Some random text.</td></tr>';
$html.='<tr><td><ul><li>One</li><li>Two <b>and a half</b></li></ul></td></tr>';
$html.='<tr><td>3_2</td><td>3_3</td><td>3_3</td></tr></tbody>';
$html.= '</table>';

$docx->embedHTML($html);

$docx->createDocx('../docx/example_embedSimpleHTML');