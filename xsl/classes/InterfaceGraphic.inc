<?php

/**
 * Interface for charts
 *
 * @category   Phpdocx
 * @package    license
 * @copyright  Copyright (c) 2009-2013 Narcea Producciones Multimedia S.L.
 *             (http://www.2mdc.com)
 * @license    http://www.phpdocx.com/wp-content/themes/lightword/pro_license.php
 * @version    2.7
 * @link       http://www.phpdocx.com
 * @since      File available since Release 2.7
 */
interface InterfaceGraphic {
	/**
     * Create embedded xml chart
     *
     * @access public
     */
    public function createEmbeddedXmlChart();

    /**
     * return the tags where the data is written
     *
     * @access public
     */
    public function dataTag();

    /**
     * return the object type of the xlsx
     *
     * @access public
     */
    public function getXlsxType();
}