<?php

/**
 * Parses and selects automatically the HTML content to be parsed and embedded in a Word document
 *
 * @category   Phpdocx
 * @package    transform
 * @copyright  Copyright (c) 2009-2011 Narcea Producciones Multimedia S.L.
 *             (http://www.2mdc.com)
 * @license    http://www.phpdocx.com/wp-content/themes/lightword/pro_license.php
 * @version    
 * @link       http://www.phpdocx.com
 * @since      File available since Release ?
 */
class ExtractHTMLContents {

    const SIBLINGS_WEIGHT = 8;// p-siblings weight
    const RAW_CHARS_WEIGHT = 0;//number of chars weight
    const RAW_UNLINK_CHARS_WEIGHT = 0;//number of chars after removing links weight
    const TEXT_CHARS_WEIGHT = 20;//number of text chars weight
    const TEXT_UNLINK_CHARS_WEIGHT = 50;//number of text chars after removing links weight
    const TEXT_RATIO_WEIGHT = 5;//ratio text chars vs. total chars
    const TEXT_UNLINK_RATIO_WEIGHT = 25;//ratio text chars (without links) vs. total chars
    const RAW_POSITION_WEIGHT = 5;//weight associated with the raw position
    const TEXT_POSITION_WEIGHT = 30;//weight associated with the text position
    
    /**
     * Other factors to weight
     *  0. Check if there are CSS for printing (this should also be checked in Word2HTML)
     *  1. Element has <p> childs: probably content
     *  2. Stop words:
     *      In tags: classes or ids containing the "menu" keyword
     *      In content: for example words like 'home', 'contact', 'about us', ...
     *  3. type of links: external, internal, anchors
     *  4. Dublin Core tags
     */
    
    /**
     *
     * @access public
     * @static
     * @var array
     */
    private static $evaluateNodes;
    
    /**
     *
     * @access public
     * @static
     * @var array
     */
    private static $nodeStack;
    
    /**
     *
     * @access public
     * @static
     * @var string
     */
    public static $HTMLContent;
    
    /**
     *
     * @access public
     * @static
     * @var array
     */
    private static $parsedNodes;
    

    /**
     * Class constructor
     */
    public function __construct($html, $threshold = 50) 
    {
        $this->threshold = $threshold;
        $this->pruned = true;
        //We assume by the time being that the $html is UTF-8 encoded
        if(class_exists('tidy')){
            try{
                $tidy = new tidy();
                $tidy = tidy_parse_string($html, array('output-xhtml' => true, 
                                                      'markup' => false, 
                                                      'wrap' => 0, 
                                                      'wrap-asp' => false, 
                                                      'wrap-jste' => false, 
                                                      'wrap-php' => false, 
                                                      'wrap-sections' => false,
                                                      'new-inline-tags' => 'footnote, endnote'), 
                                                      'utf8');
                $filteredHTML= $tidy->html();
                self::$HTMLContent = $filteredHTML->value;
            }
            catch(Exception $e){
                throw new Exception('Problem with Tidy validation. Verify HTML source or tidy installation.');
            }
        }else{
            $doc = new DOMDocument();
            $doc->preserveWhiteSpace = false;
            $doc->formatOutput = false;
            $html = str_replace("\r\n"," ",$html);
            $html = str_replace("\n"," ",$html);
            $html = preg_replace( '/\s+/', ' ', $html );
            $doc->loadHTML($html);
            self::$HTMLContent = @$doc->saveXML();
        }
        self::$HTMLContent = preg_replace('/>(\s*$\s*)</me', "strpos('$0', ' ') === false?'><':'> <'", self::$HTMLContent);
        
        $this->totalNumberChars = strlen(self::$HTMLContent);
        $this->totalNumberTextChars = strlen(strip_tags(self::$HTMLContent));
        
        $this->HTMLDOM = new DOMDocument();
        $this->HTMLDOM->loadHTML(self::$HTMLContent);
        
        $this->bodyNode = $this->HTMLDOM->getElementsByTagName('body')->item(0);
        
        self::$parsedNodes = array('div', 'ul', 'table', 'tr', 'td');
        self::$evaluateNodes = array('div', 'ul');
    }

    /**
     * Class destructor
     */
    public function __destruct() {}

/**
     * This is the main mathod to extract the "valid content"
     *
     * @access private
     * @param string $WordML
     */
    public function parseHTML() 
    {
        while($this->pruned){
            $this->pruned = false;
            $this->parseChildNodes($this->bodyNode, array('depth' => 0));
            $HTMLXPath = new DOMXPath($this->HTMLDOM);
            $query = '//*[@removeNode = "1"]';
            $affectedNodes = $HTMLXPath->query($query);
            foreach($affectedNodes as $node){
              $node->parentNode->removeChild($node);  
            }
        }
        return $this->HTMLDOM->saveHTML();
    }
    
    /**
     * This is the method that associates a value between to a HTML node
     *
     * @access private
     * @param $DOMNode $node
     * @return float
     */
    public function evaluateNode($node) 
    {
        $weight = 0;
        $strNode = $node->ownerDocument->saveXML($node);
        $nodeRawPosition = strpos(self::$HTMLContent, $strNode);
        if(strlen(strip_tags($strNode)) >0){
            $nodeTextPosition = strpos(strip_tags(self::$HTMLContent), strip_tags($strNode));
        }else{
            $nodeTextPosition = 0;
        }
        $rawCount = $this->countFullChars($node);
        $textCount = $this->countTextChars($node);
        $rawUnlinkCount = $this->countFullChars($this->pruneLinks($node));
        $textUnlinkCount = $this->countTextChars($this->pruneLinks($node));
        //Evaluate siblings weight
        if(is_object($node->nextSibling) && $node->nextSibling->nodeName == 'p'){
            $weight += (4 * ExtractHTMLContents::SIBLINGS_WEIGHT);
        }
        if(is_object($node->nextSibling) && $node->nextSibling->nodeName == 'p'){
            $weight += (6 * ExtractHTMLContents::SIBLINGS_WEIGHT);
        }
        //Evaluate raw position
        //Compute the distance from the middle raw char of full HTML code to the middle raw char of the node
        $middleRawDistance = abs(round( (float)$this->totalNumberChars/2) - ($nodeRawPosition + round( (float)$rawCount/2)));
        $weight += ExtractHTMLContents::RAW_POSITION_WEIGHT * (round( (float) $this->totalNumberChars/2) - $middleRawDistance)/round( (float)$this->totalNumberChars/2);
        
        //Evaluate text position
        //Compute the distance from the middle text char of full HTML code to the middle text char of the node
        $middleTextDistance = abs(round((float)$this->totalNumberTextChars/2) - ($nodeTextPosition + round((float)$textCount/2)));
        $weight += ExtractHTMLContents::TEXT_POSITION_WEIGHT * (round((float)$this->totalNumberTextChars/2) - $middleTextDistance)/round((float)$this->totalNumberTextChars/2);

        //Evaluate the total number of chars
        $weight += ExtractHTMLContents::RAW_CHARS_WEIGHT * ($rawCount/100);
        
        //Evaluate the total number of text chars
        $weight += ExtractHTMLContents::TEXT_CHARS_WEIGHT * ($textCount/100);
        
        //Evaluate the total number of chars with links removed
        $weight += ExtractHTMLContents::RAW_UNLINK_CHARS_WEIGHT * ($rawCount/100);
        
        //Evaluate the total number of text chars with links removed
        $weight += ExtractHTMLContents::TEXT_UNLINK_CHARS_WEIGHT * ($textCount/100);
        
        //Evaluate the total number of chars with links removed
        $weight += ExtractHTMLContents::TEXT_RATIO_WEIGHT * ($textCount/$rawCount);
        
        //Evaluate the total number of text chars with links removed
        $weight += ExtractHTMLContents::TEXT_UNLINK_RATIO_WEIGHT * ($textUnlinkCount/$rawCount);   

        
        
        return $weight;
        
    }
    
    private function parseChildNodes($HTMLNode, $aux)
    {
        $aux['depth']++;
        $this->refreshNodeStack($aux['depth']);
        $purged = 'nonPurged';
        if(in_array($HTMLNode->nodeName, self::$evaluateNodes)){
            $purged = $this->purgeHTML($HTMLNode);
        }
        if($purged == 'purged'){
            $this->pruned = true;
        }
	if($purged == 'nonPurged' && $HTMLNode->hasChildNodes()){
            $childs = $HTMLNode->childNodes;
            foreach($childs as $child){
                if(in_array($child->nodeName, self::$parsedNodes)){
                    $this->parseChildNodes($child, $aux);
                }
            }
	}
    }
    
    /**
     * This is the method that remove "unwanted" div or ul block elements
     *
     * @access private
     * @param $DOMNode $node
     * @return boolean
     */
    public function purgeHTML($node) 
    {        
        $nodeValue = $this->evaluateNode($node);
        if($nodeValue < $this->threshold && $node->nodeName != 'body'){
            $node->setAttribute('removeNode', 1);
            return 'purged';
        } 
        return 'nonPurged';
    }
    
    /**
     * Counts the number of text characters inside a HTML node
     *
     * @access private
     * @param DOMNode $node
     * @return int
     */
    public function countTextChars($node) 
    {
        $str = $node->nodeValue;
        $numChars = strlen($str);
        return $numChars;    
    }
    
    /**
     * Counts the full number of characters inside a HTML node
     *
     * @access private
     * @param DOMNode $node
     * @return int
     */
    public function countFullChars($node) 
    {
        $str = $node->ownerDocument->saveXML($node);
        $numChars = strlen($str);
        return $numChars;    
    }
    
    /**
     * Removes the links of a given node
     *
     * @access private
     * @param DOMNode $node
     * @return DOMNode
     */
    public function pruneLinks($node) 
    {
        $newNode = $node->cloneNode(true);
        $linkNodes = $newNode->getElementsByTagName('a');
        foreach($linkNodes as $link){
            $link->parentNode->removeChild($link);
        }
        return $newNode;    
    }
    
    /**
     * Update node stack
     *
     * @access private
     * @param int $depth
     * @return void
     */
    private function refreshNodeStack($depth)
    {
        for($j = $depth; $j < count(self::$nodeStack); $j++){
            unset(self::$nodeStack[$j]);
        }
    }
    

}
