<?php

/**
 * Adds various chunks of HTML code in a DOCX file
 *
 * @category   Phpdocx
 * @package    examples
 * @subpackage intermediate
 * @copyright  Copyright (c) 2009-2013 Narcea Producciones Multimedia S.L.
 *             (http://www.2mdc.com)
 * @license    http://www.phpdocx.com/wp-content/themes/lightword/pro_license.php
 * @version    2012.12.26
 * @link       http://www.phpdocx.com
 * @since      File available since Release 2.2
 */
require_once '../../classes/CreateDocx.inc';

$docx = new CreateDocx();

$html = '
<div class="index_destacado clear">

  <h3 style="margin-bottom: 0; padding-bottom: 0">Dynamical generation of DOCX</h3>
  <h4 style="font-size: 14px; color: #999999; margin-top: 0; font-weight: bold; margin-bottom: 18px">
    Conversion plugin to PDF, DOC, HTML, ODT, ...
  </h4>
  <div class="index_destacado_left">
      <p class="subtitle"><strong>PHPDocX</strong> is a <strong>PHP library</strong> designed to generate completely dynamic, fully customizable and digitally signed Word documents.</p>
       <a href="http://www.phpdocx.com/download" class="download_home">Download Now PHPDocX</a>
      <p class="plus-info">or <a href="http://www.phpdocx.com/demo" title="Try our Online Demo">Try our Online Demo!</a></p>
      <p>You may create native .docx reports extracting data directly <strong>from any database or spreadsheet</strong> and export them to other popular formats (PDF, DOC, HTML, ODT, ...) with the help of the conversion plugin. These reports may include editable graphs (only docx), images, tables, headers, footers, etcetera.</p>
      <p>PHPDocX can create, and digitally sign if required, <strong>Word documents</strong> from scratch or use predefined templates to simplify your work. With a few lines of code you may integrate PHPDocX in your website or intranet and offer a valuable service to your customers and employees.</p>
  </div>

  <div class="index_destacado_right">
      <div class="compatible">
        <h5>
          100% compatibility:
          <img width="100" src="http://www.phpdocx.com/sites/all/themes/zen_phpdocx/images/100_compatibility.gif" alt="100% compatibility">
        </h5>
      </div>
      <div class="index_destacado_video">
     <img width="400" src="http://www.phpdocx.com/sites/all/themes/zen_phpdocx/images/composite_home.png" alt="PHPDocx">
      </div>
      <div id="digital-signature">
        <h3>
          <a title="Digital Signature for DOCX and PDF documents" href="http://www.phpdocx.com/documentation/digital-signature-docx-pdf-PHP">Digitally sign your Word and PDF documents with PHPDocX</a>
        </h3>
        <p>Add a digital signature to your Word and PDF documents: on your server and just with PHP.</p>
      </div>
  </div>
</div>';

$docx->addHTML(array('html' => $html));

$docx->createDocx('../docx/example_html');
