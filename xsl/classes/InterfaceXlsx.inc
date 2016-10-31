<?php

/**
 * Interface for xlsx
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
interface InterfaceXlsx {
	/**
     * Create a excel sheet
     *
     * @access public
     */
    public function createExcelSheet($dats);

    /**
     * Create a shared string file from the xlsx
     *
     * @access public
     */
    public function createExcelSharedStrings($dats);

    /**
     * return a table file from the xlsx
     *
     * @access public
     */
    public function createExcelTable($dats);
}