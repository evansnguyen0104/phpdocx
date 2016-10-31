<?php

/**
 * Embed documents in DOCX.
 *
 * @category   Phpdocx
 * @package    elements
 * @package    transform
 * @copyright  Copyright (c) 2009-2013 Narcea Producciones Multimedia S.L.
 *             (http://www.2mdc.com)
 * @license    http://www.phpdocx.com/wp-content/themes/lightword/pro_license.php
 * @version    23.05.2011
 * @link       http://www.phpdocx.com
 * @since      File available since Release 2.3
 */

/**
 * Embed documents in DOCX.
 *
 * @category   Phpdocx
 * @package    elements
 * @package    transform
 * @copyright  Copyright (c) 2009-2013 Narcea Producciones Multimedia S.L.
 *             (http://www.2mdc.com)
 * @license    http://www.phpdocx.com/wp-content/themes/lightword/pro_license.php
 * @version    23.05.2011
 * @link       http://www.phpdocx.com
 * @since      Interface available since Release 2.3
 */
 
interface EmbedDocument {

    /**
     * Return current Id.
     *
     * @abstract
     * @return void
     */
    function getId();

    /**
     * Embed content or file.
     *
     * @abstract
     * @return void
     */
    function embed($matchSource = null);

    /**
     * Generate w:altChunk.
     *
     * @abstract
     * @return void
     */
    function generateALTCHUNK($matchSource = null);
}
