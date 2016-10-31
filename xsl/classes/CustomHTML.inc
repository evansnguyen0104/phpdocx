<?php

/**
 * Generate custom HTML
 *
 * @category   Phpdocx
 * @package    elements
 * @copyright  Copyright (c) 2009-2013 Narcea Producciones Multimedia S.L.
 *             (http://www.2mdc.com)
 * @license    http://www.phpdocx.com/wp-content/themes/lightword/pro_license.php
 * @version    2011.19.03
 * @link       http://www.phpdocx.com
 * @since      File available since Release 2.6
 */


class CustomHTML
{

    /**
     *
     * @access private
     * @var string
     */
    private static $_instance = NULL;
    /**
     *
     * @access private
     * @var array
     */
    private $_endnotes;
    /**
     *
     * @access private
     * @var array
     */
    private $_footnotes;
    /**
     *
     * @access private
     * @var string
     */
    private $_html;
    /**
     *
     * @access private
     * @var int
     */
    private $_shape;
    /**
     *
     * @access private
     * @var array
     */
    private $_shapes;
    /**
     *
     * @access private
     * @var string
     */
    private $_takenIds;
    
    /**
     * Construct
     *
     * @access public
     */
    public function __construct()
    {
        $this->_html = '';
        $this->_footnotes = array();
        $this->_endnotes = array();
        $this->_takenIds = array();
        $this->_shapes = array();
        $this->_shape = 0;
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
     * Magic method, returns current HTML
     *
     * @access public
     * @return string Return current HTML
     */
    public function __toString()
    {
        return $this->_html;
    }

    /**
     * Singleton, return instance of class
     *
     * @access public
     * @return CreateText
     * @static
     */
    public static function getInstance()
    {
        if (self::$_instance == NULL) {
            self::$_instance = new CustomHTML();
        }
        return self::$_instance;
    }

    /**
     * Creates the HTML associated with a paragraph
     *
     * @access public
     * @param array $parameters
     * @param array $options
     */
    public function paragraphHTML($parameters, $options)
    {
    	$this->_html = '';
        $this->_footnotes = array();
        $this->_endnotes = array();
        $this->_takenIds = array();
        $this->_shapes = array();
        $this->_shape = 0;
        
        $openP = '<p style="';
        $openP .= $this->generateCSSStyle($options);
        $openP .= '" >';
        
        $closeP = '</p>';

        foreach ($parameters as $run) {
            if ($run['type'] == 'text' ||
                $run['type'] == 'link' ||
                $run['type'] == 'bookmark'){
                $this->_html .= $this->runHTML($run);
            }else if($run['type'] == 'lineBreak'){
                $this->_html .= '<br />';
            }else if ($run['type'] == 'image'){
                $this->_html .= $this->imageHTML($run);
            }else if ($run['type'] == 'footnote' || $run['type'] == 'endnote'){
            		$reference = $this->uniqueDecimal($this->_takenIds, 1000, 32761);
                $this->_html .= $this->noteHTML($run, $reference);
                $noteContent = $openP . '<span style="' . $this->generateCSSStyle($run) . '">' . $run['text'] .'</span>' . $closeP;
                if($run['type'] == 'footnote'){
                	$this->_footnotes[$reference] = $noteContent;
                }else if($run['type'] == 'endnote'){
                	$this->_endnotes[$reference] = $noteContent;
                }
            }else if ($run['type'] == 'arc' ||
                      $run['type'] == 'curve' ||
                      $run['type'] == 'line' ||
                      $run['type'] == 'polyline' ||
                      $run['type'] == 'rect' ||
                      $run['type'] == 'roundrect' ||
                      $run['type'] == 'shape' ||
                      $run['type'] == 'oval' ){
                $this->_shapes[] = $run;
                $this->_html .= $this->shapeHTML($this->_shape);
                $this->_shape++;
            }    
        }
        
        
        $this->_html = $openP . $this->_html . $closeP;
            
        return array($this->_html, $this->_footnotes, $this->_endnotes, $this->_shapes);
        
    }
    
    
    
    /**
     * Creates the HTML associated with an image
     *
     * @access private
     * @param array $options
     */
    private function generateCSSStyle($options)
    {
        $phpDocXStyles = array('b' => 'font-weight',
                               'color' => 'color',
                               'font' => 'font-family',
                               'i' => 'font-style',
                               'jc' => 'text-align',
                               'pageBreakBefore' => 'page-break-before: always',
                               'sz' => 'font-size',
                               'u' => 'text-decoration',
                               'widowControl' => 'page-break-before: avoid',
                               'lineSpacing' => 'line-height',
                               'indent_left' => 'margin-left', //in twips
                               'indent_right' => 'margin-right', //in twips
                               'spacingLeft' => 'padding-left', //in twips
                               'spacingRight' => 'padding-right', //in twips
                               'spacingTop' => 'padding-top', //in twips
                               'spacingBottom' => 'padding-bottom', //in twips
                               'border' => 'border-width',
                               'borderColor' => 'border-color',
                               'position' => 'float'
                               );
        $justifications = array('center' => 'center',
                                'both' => 'justify',
                                'left' => 'left',
                                'right' => 'right',
                                'distribute' => 'justify'
                                );
        
        $css = '';
        
        foreach($options as $key => $value){
            if($key == 'b'){
            	if($value == 'single' || $value == 'on' || $value === true){
                $css .='font-weight: bold;';
              }else{
              	$css .='font-weight: normal;';
              }
            }else if($key == 'color'){
                $css .='color: #' .$value. ';';
            }else if($key == 'font'){
                $css .='font-family: ' .$value. ';';
            }else if($key == 'i'){
            	if($value == 'single' || $value == 'on' || $value === true){
                $css .='font-style: italics;';
              }else{
              	$css .='font-style: normal;';
              }
            }else if($key == 'jc'){
                $css .='text-align: ' .$justifications[$value]. ';';
            }else if($key == 'pageBreakBefore'){
                $css .='page-break-before: always;';
            }else if($key == 'sz'){
            		$size = $this->unitTransform($value, 'halfPoints', 'halfPoints');
                $css .='font-size: ' .$value. 'pt;';
            }else if($key == 'u'){
            	if($value == 'single' || $value == 'dash' || $value == 'dotted' || $value == 'double'){
                $css .='text-decoration: underline;';
              }else{
              	$css .='text-decoration: none;';
              }
            }else if($key == 'widowControl'){
                $css .='page-break-before: avoid;';
            }else if($key == 'lineSpacing'){
                $distance = $this->unitTransform($value, 'twips', 'points');
                $css .='line-height: ' .$distance. 'pt;';
            }else if($key == 'indent_left'){
                $distance = $this->unitTransform($value, 'twips', 'points');
                $css .='margin-left: ' .$distance. 'pt;';
            }else if($key == 'indent_right'){
                $distance = $this->unitTransform($value, 'twips', 'points');
                $css .='margin-right: ' .$distance. 'pt;';
            }else if($key == 'spacingLeft'){
                $distance = $this->unitTransform($value, 'points', 'points');
                $css .='padding-left: ' .$distance. 'pt;';
            }else if($key == 'spacingRight'){
                $distance = $this->unitTransform($value, 'points', 'points');
                $css .='padding-right: ' .$distance. 'pt;';
            }else if($key == 'spacingTop'){
                $distance = $this->unitTransform($value, 'points', 'points');
                $css .='padding-top: ' .$distance. 'pt;';
                $css .='margin-top: 0;';
            }else if($key == 'spacingBottom'){
                $distance = $this->unitTransform($value, 'points', 'points');
                $css .='padding-bottom: ' .$distance. 'pt;';
                $css .='margin-bottom: 0;';
            }else if($key == 'border'){
                $width = $this->unitTransform($value, 'pixels', 'pixels');
                $css .='border-style: solid; border-width: ' .$width. 'px;';
            }else if($key == 'borderColor'){
                $css .='border-color: #' .$value. ';';
            }else if($key == 'position'){
            	if($value == 'left' || $value == 'right'){
                $css .='float: ' .$value. ';';
              }
            }
        }
        
        return $css;
        
    }

    /**
     * Creates the HTML associated with an image
     *
     * @access private
     * @param array $options
     */
    private function imageHTML($options)
    {
        $image = '<img src="' .$options['src'] .'" style="';
        $image .= $this->generateCSSStyle($options);
        $image .= '" ';
        if(isset($options['sizeX'])){
        	$width = $this->unitTransform($options['sizeX'], 'pixels', 'pixels');//check units
          $image .= 'width="' .$width. '" ';
        }
        if(isset($options['sizeY'])){
          $height = $this->unitTransform($options['sizeY'], 'pixels', 'pixels');//check units
          $image .= 'height="' .$height. '" ';
        }
        $image .= '/>';    
        return $image;
        
    }
    
    /**
     * Creates the HTML associated with a footnot or endnote
     *
     * @access private
     * @param array $options
     */
    private function noteHTML($options, $reference)
    {
        $note = '';
        $note .= '<samp title="phpdocx_' .$options['type']. '_' .$reference. '" >&nbsp;</samp>';
            
        return $note;
        
    }
    
    /**
     * Creates the HTML associated with a run of text
     *
     * @access private
     * @param array $options
     */
    private function runHTML($options)
    {
        
        if(isset($options['markerName'])){//bookmarks
            $runOfText = '<a name="' .$options['markerName'] .'" style="';
            $runOfText .= $this->generateCSSStyle($options);
            $runOfText .= '">';
            $runOfText .= $options['text'];
            $runOfText .= '</a>';
        }else if(isset($options['URL'])){//link
            $runOfText = '<a  href="' .$options['URL'] .'" style="';
            $runOfText .= $this->generateCSSStyle($options);
            $runOfText .= '">';
            $runOfText .= $options['text'];
            $runOfText .= '</a>';
        }else{
            $runOfText = '<span style="';
            $runOfText .= $this->generateCSSStyle($options);
            $runOfText .= '">';
            $runOfText .= $options['text'];
            $runOfText .= '</span>';    
        }
            
        return $runOfText;
        
    }
    
    /**
     * Creates the HTML associated with a footnot or endnote
     *
     * @access private
     * @param array $options
     */
    private function shapeHTML($number)
    {
        $shape = '';
        $shape .= '<span>PHPDOCX_shape_' . $number . '</span>';
            
        return $shape;
        
    }
    
    /**
     * Generates a unique Decimal number
     * @access public
     * @param int $min
     * @param int $max
     * @return int
     */
     private function uniqueDecimal(&$takenIds = array(), $min=9999, $max=0)
       {
            if ($max == 0){
                    $max = mt_getrandmax();
                }
            $proposedId = mt_rand($min, $max );
            if(in_array($proposedId, $takenIds)){
            	$proposedId = uniqueDecimal($takenIds, $min, $max);
            }
            $takenIds[] = $proposedId;
            return $proposedId;
        }
    
    /**
     * Implements different unit transformations
     *
     * @access private
     * @param int $value
     * @param string $sourceUnit
     * @param string $targetUnit
     */
    private function unitTransform($value, $sourceUnit, $targetUnit)
    {
        if ($sourceUnit == $targetUnit){	
        	return $value;
        }else if($sourceUnit == 'twips' && $targetUnit == 'points'){
        	return $value*20;
        }else if($sourceUnit == 'points' && $targetUnit == 'emus'){
        	return $value*12700;
        }else{
        	return $value;
        }
        
    }

}

