<?php

/**
 * Create text box
 *
 * @category   Phpdocx
 * @package    elements
 * @copyright  Copyright (c) 2009-2013 Narcea Producciones Multimedia S.L.
 *             (http://www.2mdc.com)
 * @license    http://www.phpdocx.com/wp-content/themes/lightword/pro_license.php
 * @version    2011.19.03
 * @link       http://www.phpdocx.com
 * @since      File available since Release 1.0
 */
include_once dirname(__FILE__) . '/CreateElement.inc';

class CreateTextBox extends CreateElement
{
    const NAMESPACEWORD = 'v';
    const NAMESPACETEXTBOX = 'w10';
    /**
     *
     * @access private
     * @var string
     */
    private $_align;
    /**
     *
     * @access private
     * @var string
     */
    private $_b;
    /**
     *
     * @access private
     * @var int
     */
    private $_border;
    /**
     *
     * @access private
     * @var string
     */
    private $_border_color;
    /**
     *
     * @access private
     * @var string
     */
    private $_color;
    /**
     *
     * @access private
     * @var string
     */
    private $_fillColor;
    /**
     *
     * @access private
     * @var string
     */
    private $_font;
    /**
     *
     * @access private
     * @var string
     */
    private $_height;
    /**
     *
     * @access private
     * @var string
     */
    private $_i;
    /**
     *
     * @access private
     * @static
     * @var CreateTextBox
     */
    private static $_instance = NULL;
    /**
     *
     * @access private
     * @var string
     */
    private $_jc;
    /**
     *
     * @access private
     * @var string
     */
    private $_marginBottom;
    /**
     *
     * @access private
     * @var string
     */
    private $_marginLeft;
    /**
     *
     * @access private
     * @var string
     */
    private $_marginRight;
    /**
     *
     * @access private
     * @var string
     */
    private $_marginTop;
    /**
     *
     * @access private
     * @var string
     */
    private $_pageBreakBefore;
    /**
     *
     * @access private
     * @var string
     */
    private $_sz;
    /**
     *
     * @access private
     * @var string
     */
    private $_text;
    /**
     *
     * @access private
     * @var string
     */
    private $_textJc;
    /**
     *
     * @access private
     * @var string
     */
    private $_u;
    /**
     *
     * @access private
     * @var string
     */
    private $_widowControl;
    /**
     *
     * @access private
     * @var string
     */
    private $_width;
    /**
     *
     * @access private
     * @var string
     */
    private $_wordWrap;
    /**
     *
     * @access private
     * @var string
     */
    private $_padding_top;
    /**
     *
     * @access private
     * @var string
     */
    private $_padding_right;
    /**
     *
     * @access private
     * @var string
     */
    private $_padding_bottom;
    /**
     *
     * @access private
     * @var string
     */
    private $_padding_left;
    


    /**
     * Construct
     *
     * @access public
     */
    public function __construct()
    {
        $this->_text = '';
        $this->_marginTop = '';
        $this->_marginBottom = '';
        $this->_marginRight = '';
        $this->_marginLeft = '';
        $this->_width = '';
        $this->_height = '';
        $this->_align = '';
        $this->_fillColor = '';
        $this->_jc = '';
        $this->_textJc = '';
        $this->_b = '';
        $this->_color = '';
        $this->_i = '';
        $this->_sz = '';
        $this->_u = '';
        $this->_pageBreakBefore = '';
        $this->_widowControl = '';
        $this->_wordWrap = '';
        $this->_font = '';
        $this->_border = 1;
        $this->_border_color = '#000000';
        $this->_padding_top = "";
        $this->_padding_right = "";
        $this->_padding_bottom = "";
        $this->_padding_left = "";      
    }

    /**
     * Destruct
     *
     * @access public
     */
    public function __destruct()
    {

    }

    /**
     * Magic method, returns current XML
     *
     * @access public
     * @return string Return current XML
     */
    public function __toString()
    {
        return $this->_xml;
    }

    /**
     * Singleton, return instance of class
     *
     * @access public
     * @return CreateTextBox
     * @static
     */
    public static function getInstance()
    {
        if (self::$_instance == NULL) {
            self::$_instance = new CreateTextBox();
        }
        return self::$_instance;
    }

    /**
     * Create embedded textbox
     *
     * @access public
     */
    public function createEmbeddedTextBox()
    {
        $this->_xml = '';
        $this->generateQUITAR();
        $this->generateRPR();
        $this->generateNOPROOF();
        $this->generatePICT();
        $this->generateSHAPETYPE();
        $this->generateSTROKE();
        $this->generatePATH();
        $this->generateSHAPE(
            array(
                'margin_top' => $this->_marginTop,
                'margin_bottom' => $this->_marginBottom,
                'margin_right' => $this->_marginRight,
                'margin_left' => $this->_marginLeft,
                'width' => $this->_width,
                'height' => $this->_height,
                'align' => $this->_align,
                'fillcolor' => $this->_fillColor,
                'textWrap' => $this->_textWrap,
                'border' => $this->_border,
                'border_color' => $this->_border_color,
            )
        );
        $this->generateTEXTBOX(
            array(
                'style' => (!isset($this->_height)?'mso-fit-shape-to-text:t':''), 
                'inset' => $this->preparePadding(array(
                'padding_top' => $this->_padding_top,
                'padding_right' => $this->_padding_right,
                'padding_bottom' => $this->_padding_bottom,
                'padding_left' => $this->_padding_left)))
        );
        $this->generateTXBXCONTENT();
        $this->addText(
            $this->_text,
            array(
                'jc' => $this->_textJc,
                'b' => $this->_b,
                'color' => $this->_color,
                'i' => $this->_i,
                'sz' => $this->_sz,
                'u' => $this->_u,
                'pageBreakBefore' => $this->_pageBreakBefore,
                'widowControl' => $this->_widowControl,
                'wordWrap' => $this->_wordWrap,
                'font' => $this->_font
            )
        );
        $this->generateWRAP();
        $this->cleanTemplate();
    }
    /**
     * Create textbox
     *
     * @access public
     * @param array $dat
     * @param array $style
     */
    public function createTextBox($dat, $style = '')
    {
        $this->_xml = '';
        $this->generateP();
        $this->generateR();
        $this->generateRPR();
        $this->generateNOPROOF();
        $this->generatePICT();
        $this->generateSHAPETYPE();
        $this->generateSTROKE();
        $this->generatePATH();
        $this->generateSHAPE($style);
        $this->generateTEXTBOX(array('style' => (!isset($style['height'])?'mso-fit-shape-to-text:t':''), 'inset' => $this->preparePadding($style)));
        $this->generateTXBXCONTENT();
        $this->addText($dat['text'], $dat['args']);
        if(isset($style['textWrap']) && in_array($style['textWrap'], array('tight' ,'square', 'through'))){
            $this->generateWRAP($style);
        }
        $this->cleanTemplate();
    }

    /**
     * Init text box
     *
     * @access public
     * @param array $args[0]
     */
    public function initTextBox()
    {
        $args = func_get_args();
        
        if (!isset($args[0][0]['text'])) {
            $args[0][0]['text'] = '';
        }
        if (!isset($args[1]['margin_top'])) {
            $args[1]['margin_top'] = '';
        }
        if (!isset($args[1]['margin_bottom'])) {
            $args[1]['margin_bottom'] = '';
        }
        if (!isset($args[1]['margin_right'])) {
            $args[1]['margin_right'] = '';
        }
        if (!isset($args[1]['margin_left'])) {
            $args[1]['margin_left'] = '';
        }
        if (!isset($args[1]['width'])) {
            $args[1]['width'] = '';
        }
        if (!isset($args[1]['height'])) {
            $args[1]['height'] = '';
        }
        if (!isset($args[1]['_border'])) {
            $args[1]['border'] = '';
        }
        if (!isset($args[1]['_border_color'])) {
            $args[1]['border_color'] = '';
        }
        if (!isset($args[1]['_padding_top'])) {
            $args[1]['padding_top'] = '';
        }
        if (!isset($args[1]['_padding_right'])) {
            $args[1]['padding_right'] = '';
        }
        if (!isset($args[1]['_padding_bottom'])) {
            $args[1]['padding_bottom'] = '';
        }
        if (!isset($args[1]['_padding_left'])) {
            $args[1]['padding_left'] = '';
        }
        if (!isset($args[1]['align'])) {
            $args[1]['align'] = '';
        }
        if (!isset($args[1]['fillcolor'])) {
            $args[1]['fillcolor'] = '';
        }
        if (!isset($args[1]['textWrap'])) {
            $args[1]['textWrap'] = '';
        }
        if (!isset($args[0][1]['b'])) {
            $args[0][1]['b'] = '';
        }
        if (!isset($args[0][1]['color'])) {
            $args[0][1]['color'] = '';
        }
        if (!isset($args[0][1]['i'])) {
            $args[0][1]['i'] = '';
        }
        if (!isset($args[0][1]['sz'])) {
            $args[0][1]['sz'] = '';
        }
        if (!isset($args[0][1]['u'])) {
            $args[0][1]['u'] = '';
        }
        if (!isset($args[0][1]['pageBreakBefore'])) {
            $args[0][1]['pageBreakBefore'] = '';
        }
        if (!isset($args[0][1]['widowControl'])) {
            $args[0][1]['widowControl'] = '';
        }
        if (!isset($args[0][1]['wordWrap'])) {
            $args[0][1]['wordWrap'] = '';
        }
        if (!isset($args[0][1]['font'])) {
            $args[0][1]['font'] = '';
        }
        
        $this->_text = $args[0][0]['text'];
       
        $this->_textJc = $args[0][1]['args']['jc'];
        $this->_b = $args[0][1]['b'];
        $this->_color = $args[0][1]['color'];
        $this->_i = $args[0][1]['i'];
        $this->_sz = $args[0][1]['sz'];
        $this->_u = $args[0][1]['u'];
        $this->_pageBreakBefore = $args[0][1]['pageBreakBefore'];
        $this->_widowControl = $args[0][1]['widowControl'];
        $this->_wordWrap = $args[0][1]['wordWrap'];
        $this->_font = $args[0][1]['font'];
        
        $this->_border = $args[1]['border'];
        $this->_border_color = $args[1]['border_color'];
        $this->_marginTop = $args[1]['margin_top'];
        $this->_marginBottom = $args[1]['margin_bottom'];
        $this->_marginRight = $args[1]['margin_right'];
        $this->_marginLeft = $args[1]['margin_left'];
        $this->_width = $args[1]['width'];
        $this->_height = $args[1]['height'];
        $this->_align = $args[1]['align'];
        $this->_fillColor = $args[1]['fillcolor'];
        $this->_textWrap = $args[1]['textWrap'];
        $this->_padding_top = $args[1]['padding_top'];
        $this->_padding_right = $args[1]['padding_right'];
        $this->_padding_bottom = $args[1]['padding_bottom'];
        $this->_padding_left = $args[1]['padding_left'];        
    }

    /**
     * Create text in textbox
     *
     * @access protected
     * @param mixed $dat
     * @param array $style
     */
    protected function addText($dat, $style = '')
    {
    $objText = CreateText::getInstance();
        $objText->createText($dat, $style);
        $this->_xml = str_replace(
            '__GENERATETXBXCONTENT__', (string) $objText, $this->_xml
        );
    }

    /**
     * Generate w:shapetype
     *
     * @access protected
     * @param string $id
     * @param string $coordsize
     * @param string $spt
     * @param string $path
     * @param string $id
     */
    protected function generateSHAPETYPE(
        $id = '_x0000_t202', $coordsize = '21600,21600',
        $spt = '202', $path = 'm,l,21600r21600,l21600,xe'
    )
    {
        $this->_xml = str_replace(
            '__GENERATEPICT__', '<' . CreateTextBox::NAMESPACEWORD .
            ':shapetype id="' . $id . '" coordsize="' . $coordsize .
            '" o:spt="' . $spt . '" path="' . $path .
            '">__GENERATESHAPETYPE__</' . CreateTextBox::NAMESPACEWORD .
            ':shapetype>__GENERATEPICT__', $this->_xml
        );
    }

    /**
     * Generate w:stroke
     *
     * @access protected
     * @param string $joinstyle
     */
    protected function generateSTROKE($joinstyle = 'miter')
    {
        $this->_xml = str_replace(
            '__GENERATESHAPETYPE__', '<' . CreateTextBox::NAMESPACEWORD .
            ':stroke joinstyle="' . $joinstyle . '"></' .
            CreateTextBox::NAMESPACEWORD . ':stroke>__GENERATESHAPETYPE__',
            $this->_xml
        );
    }

    /**
     * Generate w:path
     *
     * @access protected
     * @param string $gradientshapeok
     * @param string $connecttype
     */
    protected function generatePATH(
        $gradientshapeok = 't', $connecttype = 'rect'
    )
    {
        $this->_xml = str_replace(
            '__GENERATESHAPETYPE__', '<' . CreateTextBox::NAMESPACEWORD .
            ':path gradientshapeok="' . $gradientshapeok . '" o:connecttype="' .
            $connecttype . '"></' . CreateTextBox::NAMESPACEWORD . ':path>',
            $this->_xml
        );
    }

    /**
     * Generate w:shape
     *
     * @access protected
     * @param array $args[0]
     */
    protected function generateSHAPE()
    {
        $args = func_get_args();
        $id = '_x0000_s1026';
        $type = '#_x0000_t202';
        $style = '';
        if (!empty($args[0]['align']))
            $style .= 'mso-position-horizontal:' . $args[0]['align'] . ';';
        if (!empty($args[0]['margin_top']))
            $style .= 'margin-top:' . $this->convertCm2Pt($args[0]['margin_top']) . 'pt;';
        if (!empty($args[0]['margin_left']))
            $style .= 'margin-left:' . $this->convertCm2Pt($args[0]['margin_left']) . 'pt;';
        if (!empty($args[0]['margin_bottom']))
            $style .= 'margin-bottom:' . $this->convertCm2Pt($args[0]['margin_bottom']) . 'pt;';
        if (!empty($args[0]['margin_right']))
            $style .= 'margin-right:' . $this->convertCm2Pt($args[0]['margin_right']) . 'pt;';



        if (!empty($args[0]['width']) && is_numeric($args[0]['width'])){
            $style .= 'width:' . $this->convertCm2Pt($args[0]['width']) . 'pt;';
        }else{
            $style .= 'mso-width-percent:400;';
        }
        if (!empty($args[0]['height']) && is_numeric($args[0]['height']))
            $style .= 'height:' . $this->convertCm2Pt($args[0]['height']) . 'pt;mso-height-relative:margin;';
        
        $strAux = '';
        if (!empty($args[0]['textWrap'])) {
            if($args[0]['textWrap'] == 'belowText')
                $style .= 'z-index:-251660288;position:absolute;';
            elseif($args[0]['textWrap'] == 'none')
                $style .= "mso-position-horizontal-relative:char;mso-position-vertical:absolute;mso-position-vertical-relative:line;";
            else
                $style .= 'z-index:251660288;position:absolute;';
                
            if($args[0]['textWrap'] == 'tight' || $args[0]['textWrap'] == 'tight'){
                $strAux .= ' wrapcoords="-96 -97 -96 21503 21696 21503 21696 -97 -96 -97" ';
            }
            $style .= 'mso-width-relative:margin;mso-height-relative:margin;';//mso-height-percent:200;
        }else{
            $style .= 'z-index:251660288;position:absolute;';
        }

        $style = substr($style, 0, -1);
        
        $xmlAux = '<' . CreateTextBox::NAMESPACEWORD . ':shape id="' . $id .
            '" type="' . $type . '" style="' . $style . '"' . $strAux;

        if (!empty($args[0]['fillcolor'])) {
            $xmlAux .= ' fillcolor="' . $args[0]['fillcolor'] . '"';
        }
        if (isset($args[0]['border'])) {
            if($args[0]['border'] == 0)
                $xmlAux .= ' stroked="f" ';
            elseif(is_numeric($args[0]['border']))
                $xmlAux .= ' strokeweight="'. $args[0]['border'] . 'pt" ';
        }
        if (isset($args[0]['border_color'])) {
            if($args[0]['border_color'] != ''){
                $xmlAux .= ' strokecolor="' .$args[0]['border_color']. '"';
                        }
        }
        $xmlAux .= '>__GENERATESHAPE__</' . CreateTextBox::NAMESPACEWORD .
            ':shape>';
            
        $this->_xml = str_replace('__GENERATEPICT__', $xmlAux, $this->_xml);
    }


    protected function convertCm2Pt($cm){
        return 28.3464567 * $cm;
    }
    /**
     * Generate w:textbox
     *
     * @access protected
     * @param string $style
     */
    protected function generateTEXTBOX($options = array())
    {
        $this->_xml = str_replace(
            '__GENERATESHAPE__', '<' . CreateTextBox::NAMESPACEWORD .
            ':textbox ' . (!empty($options['style'])?'style="' . $options['style'] . '"':'') . ' ' . (!empty($options['inset'])?'inset="' . $options['inset'] . '"':'') . ' >__GENERATETEXTBOX__</' .
            CreateTextBox::NAMESPACEWORD . ':textbox>__GENERATESHAPE__',
            $this->_xml
        );
    }

    /**
     * Generate w:txbxcontent
     *
     * @access protected
     */
    protected function generateTXBXCONTENT()
    {
        $this->_xml = str_replace(
            '__GENERATETEXTBOX__', '<' . CreateElement::NAMESPACEWORD .
            ':txbxContent>__GENERATETXBXCONTENT__</' .
            CreateElement::NAMESPACEWORD . ':txbxContent>', $this->_xml
        );
    }

    /**
     * Generate w:wrap
     *
     * @access protected
     * @param array $args[0]
     */
    protected function generateWRAP()
    {
        $type = 'through';
        $args = func_get_args();
        if (isset($args[0]['textWrap'])) {
            $type = $args[0]['textWrap'];
            $this->_xml = str_replace(
                '__GENERATESHAPE__', '<' . CreateTextBox::NAMESPACETEXTBOX .
                ':wrap type="' . $type . '"></' .
                CreateTextBox::NAMESPACETEXTBOX . ':wrap>__GENERATESHAPE__',
                $this->_xml
            );
        }
    }
    
    /**
     * Prepare the padding
     *
     * @access protected
     * @param array $args[0]
     */
    private function preparePadding($style){
        $padding = "";
        if((isset($style['padding_top']) && is_numeric($style['padding_top'])) || (isset($style['padding_left']) && is_numeric($style['padding_left'])) 
            || (isset($style['padding_right']) && is_numeric($style['padding_right'])) || (isset($style['padding_bottom']) && is_numeric($style['padding_bottom'])))
        {
            
            if(isset($style['padding_left']) && is_numeric($style['padding_left'])){
                            $padding .= ($style['padding_left']*10).'mm,';
            }else{
                            $padding .= '0mm,';
                        }
                        if(isset($style['padding_top']) && is_numeric($style['padding_top'])){
                $padding .= ($style['padding_top']*10).'mm,';
            }else{
                            $padding .= '0mm,';
                        }
            if(isset($style['padding_right']) && is_numeric($style['padding_right'])){
                $padding .= ($style['padding_right']*10).'mm,';
            }else{
                            $padding .= '0mm,';
                        }
            if(isset($style['padding_bottom']) && is_numeric($style['padding_bottom'])){
                $padding .= ($style['padding_bottom']*10).'mm,';
            }else{
                            $padding .= '0mm,';
                        }
            
        }
        return $padding;
    }
}
