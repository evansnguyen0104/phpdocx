<?php

/**
 * Create embedded elements
 *
 * @category   Phpdocx
 * @package    elements
 * @copyright  Copyright (c) 2009-2013 Narcea Producciones Multimedia S.L.
 *             (http://www.2mdc.com)
 * @license    http://www.phpdocx.com/wp-content/themes/lightword/pro_license.php
 * @version    1.0
 * @link       http://www.phpdocx.com
 * @since      File available since Release 1.0
 */
include_once dirname(__FILE__) . '/CreateElement.inc';

/**
 * Create embedded elements
 *
 * @category   Phpdocx
 * @package    elements
 * @copyright  Copyright (c) 2009-2013 Narcea Producciones Multimedia S.L.
 *             (http://www.2mdc.com)
 * @license    http://www.phpdocx.com/wp-content/themes/lightword/pro_license.php
 * @version    1.0
 * @link       http://www.phpdocx.com
 * @since      Class available since Release 1.0
 */
class CreateEmbeddedElement extends CreateElement
{
    /**
     *
     * @var CreateEmbeddedElement
     * @access private
     * @static
     */
    private static $_instance = NULL;

    /**
     *
     * @var string
     * @access private
     */
    private $_xmlElement;

    /**
     * Construct
     *
     * @access public
     */
    public function __construct()
    {

    }

    /**
     * Destruct
     *
     * @access private
     */
    private function __destruct()
    {

    }
    
    /**
     *
     * @access public
     * @return string
     */
    public function __toString()
    {
        return $this->_xmlElement;
    }

    /**
     *
     * @return CreateEmbeddedElement
     * @access public
     * @static
     */
    public static function getInstance()
    {
        if (self::$_instance == NULL) {
            self::$_instance = new CreateEmbeddedElement();
        }
        return self::$_instance;
    }

    /**
     * Create embedded element
     *
     * @return string
     * @access public
     */
    public function CreateEmbeddedElement()
    {
        $this->_xml = '';
        $args = func_get_args();

        switch ($args[0]) {
            case 'Chart':
                $this->_xmlElement = '';
                break;
            case 'Graphic':
                $this->_xmlElement = '';
                break;
            case 'Image':
                $this->_xmlElement = '';
                break;
            case 'Link':
                $this->_xmlElement = '';
                break;
            case 'Math':
                $this->_xmlElement = '';
                break;
            case 'TextBox':
                $this->_xmlElement = '';
                break;
            default:
                break;
        }
        return $this->_xmlElement;
    }

}
