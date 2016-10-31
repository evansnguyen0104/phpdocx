<?php

/**
 * Generate a DOCX file
 *
 * @category   Phpdocx
 * @package    create
 * @copyright  Copyright (c) 2009-2013 Narcea Producciones Multimedia S.L.
 *             (http://www.2mdc.com)
 * @license    http://www.phpdocx.com/wp-content/themes/lightword/pro_license.php
 * @version    2013.11.20
 * @link       http://www.phpdocx.com
 * @since      File available since Release 1.0
 */

error_reporting(E_ALL & ~E_STRICT & ~E_NOTICE);
require_once dirname(__FILE__) . '/AutoLoader.inc';
AutoLoader::load();
require_once dirname(__FILE__) . '/Phpdocx_config.inc';

class CreateDocx extends CreateDocument
{
    const NAMESPACEWORD = 'w';
    const SCHEMA_IMAGEDOCUMENT =
    'http://schemas.openxmlformats.org/officeDocument/2006/relationships/image';
    const SCHEMA_OFFICEDOCUMENT =
    'http://schemas.openxmlformats.org/officeDocument/2006/relationships/officeDocument';

    /**
     *
     * @access public
     * @var array
     * @static
     */
    public static $bidi;
    /**
     *
     * @access public
     * @var array
     * @static
     */
    public static $rtl;
    /**
     *
     * @var string
     * @access public
     * @static
     */
    public static $PHPDOCXStyles;
    /**
     *
     * @var array
     * @access public
     * @static
     */
    public static $customLists;
    /**
     *
     * @access public
     * @static
     * @var integer
     */
    public static $numUL;
    /**
     *
     * @access public
     * @var integer
     */
    public static $numOL;
    /**
     *
     * @var string
     * @access public
     * @static
     */
    public static $orderedListStyle;
    /**
     *
     * @var string
     * @access public
     * @static
     */
    public static $unorderedListStyle;
    /**
     *
     * @access public
     * @var array
     */
    public $fileGraphicTemplate;
    /**
     *
     * @access private
     * @var boolean
     */
    private $footerAdded;
    /**
     *
     * @access private
     * @var boolean
     */
    private $headerAdded;
    /**
     *
     * @access public
     * @var string
     */
    public $graphicTemplate;
    /**
     *
     * @access public
     * @static
     * @var int
     */
    public static $intIdWord;
    /**
     *
     * @access public
     * @static
     * @var Logger
     */
    public static $log;
    /**
     *
     * @access public
     * @static
     * @var array
     */
     public static $sectionProperties = array('w:footnotePr',
                                              'w:endnotePr',
                                              'w:type',
                                              'w:pgSz',
                                              'w:pgMar',
                                              'w:paperSrc',
                                              'w:pgBorders',
                                              'w:lnNumType',
                                              'w:pgNumType',
                                              'w:cols',
                                              'w:formProt',
                                              'w:vAlign',
                                              'w:noEndnote',
                                              'w:titlePg',
                                              'w:textDirection',
                                              'w:bidi',
                                              'w:rtlGutter',
                                              'w:docGrid',
                                              'w:printerSettings',
                                              'w:sectPrChange'
                                               );
    /**
     *
     * @access public
     * @static
     * @var array
     */
     public static $settings = array('w:writeProtection',
                                    'w:view',
                                    'w:zoom',
                                    'w:removePersonalInformation',
                                    'w:removeDateAndTime',
                                    'w:doNotDisplayPageBoundaries',
                                    'w:displayBackgroundShape',
                                    'w:printPostScriptOverText',
                                    'w:printFractionalCharacterWidth',
                                    'w:printFormsData',
                                    'w:embedTrueTypeFonts',
                                    'w:embedSystemFonts',
                                    'w:saveSubsetFonts',
                                    'w:saveFormsData',
                                    'w:mirrorMargins',
                                    'w:alignBordersAndEdges',
                                    'w:bordersDoNotSurroundHeader',
                                    'w:bordersDoNotSurroundFooter',
                                    'w:gutterAtTop',
                                    'w:hideSpellingErrors',
                                    'w:hideGrammaticalErrors',
                                    'w:activeWritingStyle',
                                    'w:proofState',
                                    'w:formsDesign',
                                    'w:attachedTemplate',
                                    'w:linkStyles',
                                    'w:stylePaneFormatFilter',
                                    'w:stylePaneSortMethod',
                                    'w:documentType',
                                    'w:mailMerge',
                                    'w:revisionView',
                                    'w:trackRevisions',
                                    'w:doNotTrackMoves',
                                    'w:doNotTrackFormatting',
                                    'w:documentProtection',
                                    'w:autoFormatOverride',
                                    'w:styleLockTheme',
                                    'w:styleLockQFSet',
                                    'w:defaultTabStop',
                                    'w:autoHyphenation',
                                    'w:consecutiveHyphenLimit',
                                    'w:hyphenationZone',
                                    'w:doNotHyphenateCaps',
                                    'w:showEnvelope',
                                    'w:summaryLength',
                                    'w:clickAndTypeStyle',
                                    'w:defaultTableStyle',
                                    'w:evenAndOddHeaders',
                                    'w:bookFoldRevPrinting',
                                    'w:bookFoldPrinting',
                                    'w:bookFoldPrintingSheets',
                                    'w:drawingGridHorizontalSpacing',
                                    'w:drawingGridVerticalSpacing',
                                    'w:displayHorizontalDrawingGridEvery',
                                    'w:displayVerticalDrawingGridEvery',
                                    'w:doNotUseMarginsForDrawingGridOrigin',
                                    'w:drawingGridHorizontalOrigin',
                                    'w:drawingGridVerticalOrigin',
                                    'w:doNotShadeFormData',
                                    'w:noPunctuationKerning',
                                    'w:characterSpacingControl',
                                    'w:printTwoOnOne',
                                    'w:strictFirstAndLastChars',
                                    'w:noLineBreaksAfter',
                                    'w:noLineBreaksBefore',
                                    'w:savePreviewPicture',
                                    'w:doNotValidateAgainstSchema',
                                    'w:saveInvalidXml',
                                    'w:ignoreMixedContent',
                                    'w:alwaysShowPlaceholderText',
                                    'w:doNotDemarcateInvalidXml',
                                    'w:saveXmlDataOnly',
                                    'w:useXSLTWhenSaving',
                                    'w:saveThroughXslt',
                                    'w:showXMLTags',
                                    'w:alwaysMergeEmptyNamespace',
                                    'w:updateFields',
                                    'w:hdrShapeDefaults',
                                    'w:footnotePr',
                                    'w:endnotePr',
                                    'w:compat',
                                    'w:docVars',
                                    'w:rsids',
                                    'm:mathPr',
                                    'w:uiCompat97To2003',
                                    'w:attachedSchema',
                                    'w:themeFontLang',
                                    'w:clrSchemeMapping',
                                    'w:doNotIncludeSubdocsInStats',
                                    'w:doNotAutoCompressPictures',
                                    'w:forceUpgrade',
                                    'w:captions',
                                    'w:readModeInkLockDown',
                                    'w:smartTagType',
                                    'sl:schemaLibrary',
                                    'w:shapeDefaults',
                                    'w:doNotEmbedSmartTags',
                                    'w:decimalSymbol',
                                    'w:listSeparator'
                                    );
    /**
     *
     * @access private
     * @var string
     */
    private $_background;
     /**
     *
     * @access private
     * @var string
     */
    private $_backgroundColor;
     /**
     *
     * @access private
     * @var string
     */
    private $_baseTemplateFilesPath;
   /**
     *
     * @access private
     * @var string
     */
    private $_baseTemplatePath;
   /**
     *
     * @access private
     * @var string
     */
    private $_baseTemplateZip;
    /**
     *
     * @access private
     * @var array
     */
    private $_bookmarksIds;
   /**
     *
     * @access private
     * @var boolean
     */
    private $_compatibilityMode;
    /**
     *
     * @access private
     * @var string
     */
    private $_contentTypeC;
    /**
     *
     * @access private
     * @var string
     */
    private $_defaultFont;
    /**
     *
     * @access private
     * @var Debug
     */
    private $_debug;
    /**
     *
     * @access private
     * @var array
     */
    private $_defaultPHPDOCXStyles;
    /**
     *
     * @access private
     * @var boolean
     */
    private $_defaultTemplate;
    /**
     *
     * @access private
     * @var boolean
     */
    private $_docm;
    /**
     *
     * @access private
     * @var string
     */
    private $_docPropsAppC;
    /**
     *
     * @access private
     * @var string
     */
    private $_docPropsAppT;
    /**
     *
     * @access private
     * @var string
     */
    private $_docPropsCoreC;
    /**
     *
     * @access private
     * @var string
     */
    private $_docPropsCoreT;
    /**
     *
     * @access private
     * @var string
     */
    private $_docPropsCustomC;
    /**
     *
     * @access private
     * @var string
     */
    private $_docPropsCustomT;
    /**
     *
     * @access private
     * @var string
     */
    private static $_encodeUTF;
    /**
     *
     * @access private
     * @var string
     */
    private $_extension;
    /**
     *
     * @access private
     * @var int
     */
    private $_idImgHeader;
    /**
     *
     * @access private
     * @var int
     */
    private $_idRels;
    /**
     *
     * @access private
     * @var array
     */
    private $_idWords;
    /**
     *
     * @access private
     * @var string
     */
    private $_language;
    /**
     *
     * @access private
     * @var boolean
     */
    private $_macro;
    /**
     *
     * @access private
     * @var int
     */
    private $_markAsFinal;
    /**
     *
     * @access private
     * @var array
     */
    private $_parsedStyles;
    /**
     *
     * @access private
     * @var array
     */
    private $_phpdocxconfig;
    /**
     *
     * @access private
     * @var array
     */
    private $_relsHeader;
    /**
     *
     * @access private
     * @var array
     */
    private $_relsHeaderFooterImage;
    /**
     *
     * @access private
     * @var array
     */
    private $_relsHeaderFooterImageExternal;
    /**
     *
     * @access private
     * @var array
     */
    private $_relsHeaderFooterLink;
     /**
     *
     * @access private
     * @var array
     */
    private $_relsFooter;
    /**
     *
     * @access private
     * @var array
     */
    private $_relsNotesExternalImage;
    /**
     *
     * @access private
     * @var array
     */
    private $_relsNotesImage;
    /**
     *
     * @access private
     * @var array
     */
    private $_relsNotesLink;
    /**
     *
     * @access private
     * @var string
     */
    private $_relsRelsC;
    /**
     *
     * @access private
     * @var string
     */
    private $_relsRelsT;
     /**
     *
     * @access private
     * @var string
     */
    private $_sectPr;
    /**
     * Directory path used for temporary files
     *
     * @access private
     * @var string
     */
    private $_tempDir;
    /**
     * Path of temp file to use as DOCX file
     *
     * @access private
     * @var string
     */
    private $_tempFile;
    /**
     * Paths of temps files to use as DOCX file
     *
     * @access private
     * @var array
     */
    private $_tempFileXLSX;
    /**
     * Custom numberings used by the replaceTemplateVariabeByHTML
     *
     * @access private
     * @var array
     */
    private $_templateCustomNumberings;
    /**
     * Numberings used by the replaceTemplateVariabeByHTML
     *
     * @access private
     * @var array
     */
    private $_templateNumberings;
    /**
     * Unique id for the insertion of new elements
     *
     * @access private
     * @var string
     */
    private $_uniqid;
    /**
     *
     * @access private
     * @var string
     */
    private $_wordDocumentC;
    /**
     *
     * @access private
     * @var string
     */
    private $_wordDocumentT;
    /**
     *
     * @access private
     * @var string
     */
    private $_wordDocumentStyles;
    /**
     *
     * @access private
     * @var string
     */
    private $_wordEndnotesC;
    /**
     *
     * @access private
     * @var string
     */
    private $_wordEndnotesT;
    /**
     *
     * @access private
     * @var string
     */
    private $_wordFontTableC;
    /**
     *
     * @access private
     * @var string
     */
    private $_wordFontTableT;
    /**
     *
     * @access private
     * @var array
     */
    private $_wordFooterC;
    /**
     *
     * @access private
     * @var array
     */
    private $_wordFooterT;
    /**
     *
     * @access private
     * @var string
     */
    private $_wordFootnotesC;
    /**
     *
     * @access private
     * @var string
     */
    private $_wordFootnotesT;
    /**
     *
     * @access private
     * @var array
     */
    private $_wordHeaderC;
    /**
     *
     * @access private
     * @var array
     */
    private $_wordHeaderT;
    /**
     *
     * @access private
     * @var string
     */
    private $_wordNumberingC;
    /**
     *
     * @access private
     * @var string
     */
    private $_wordNumberingT;
    /**
     *
     * @access private
     * @var string
     */
    private $_wordRelsDocumentRelsC;
    /**
     *
     * @access private
     * @var DOMDocument
     */
    private $_wordRelsDocumentRelsT;
    /**
     *
     * @access private
     * @var array
     */
    private $_wordRelsFooterRelsC;
    /**
     *
     * @access private
     * @var array
     */
    private $_wordRelsFooterRelsT;
    /**
     *
     * @access private
     * @var array
     */
    private $_wordRelsHeaderRelsC;
    /**
     *
     * @access private
     * @var array
     */
    private $_wordRelsHeaderRelsT;
    /**
     *
     * @access private
     * @var string
     */
    private $_wordSettingsC;
    /**
     *
     * @access private
     * @var string
     */
    private $_wordSettingsT;
    /**
     *
     * @access private
     * @var string
     */
    private $_wordStylesC;
    /**
     *
     * @access private
     * @var string
     */
    private $_wordStylesT;
    /**
     *
     * @access private
     * @var string
     */
    private $_wordThemeThemeT;
    /**
     *
     * @access private
     * @var string
     */
    private $_wordThemeThemeC;
    /**
     *
     * @access private
     * @var string
     */
    private $_wordWebSettingsC;
    /**
     *
     * @access private
     * @var string
     */
    private $_wordWebSettingsT;
    /**
     *
     * @access private
     * @var ZipArchive
     */
    private $_zipDocx;

    /**
     * Construct
     *
     * @access public
     * @param string $baseTemplatePath. Optional, basicTemplate.docx as default
     */
    public function __construct($baseTemplatePath = PHPDOCX_BASE_TEMPLATE)
    {
        $this->_debug = Debug::getInstance();

        $this->_phpdocxconfig = PhpdocxUtilities::parseConfig();

        $this->_background = '';
        $this->_backgroundColor = 'FFFFFF';
        $this->_baseTemplateFilesPath;
        if ($baseTemplatePath == 'docm') {
            $this->_baseTemplatePath = PHPDOCX_BASE_FOLDER.'phpdocxBaseTemplate.docm';
            $this->_docm = true;
            $this->_defaultTemplate = true;
            $this->_extension = 'docm';
        } else if($baseTemplatePath == 'docx') {
            $this->_baseTemplatePath = PHPDOCX_BASE_FOLDER.'phpdocxBaseTemplate.docx';
            $this->_docm = false;
            $this->_defaultTemplate = true;
            $this->_extension = 'docx';
        } else {
            if ($baseTemplatePath == PHPDOCX_BASE_TEMPLATE) {
                $this->_defaultTemplate = true;
            } else {
                $this->_defaultTemplate = false;
            }
            $this->_baseTemplatePath = $baseTemplatePath;
            $extensionArray = explode('.', $this->_baseTemplatePath);
            $extension = array_pop($extensionArray);
            $this->_extension = $extension;
            if ($extension == 'docm') {
                $this->_docm = true;
            } else if ($extension == 'docx') {
                $this->_docm = false;
            } else {
                PhpdocxLogger::logger('Invalid base template extension', 'fatal');
            }
        }
        $this->_baseTemplateZip = new ZipArchive();
        $this->_bookmarksIds = array();
        $this->_idRels = array();
        $this->_idWords = array();
        $this->_idImgHeader = 1;
        $this->_idRels = 1;
        self::$intIdWord = rand(9999999,99999999);
        self::$_encodeUTF = 0;
        $this->_language = 'en-US';
        $this->_markAsFinal = 0;
        $this->graphicTemplate = array();
        $this->fileGraphicTemplate = array();
        $this->_zipDocx = new ZipArchive();
        if ($this->_phpdocxconfig['settings']['temp_path']) {
            $this->_tempDir = $this->_phpdocxconfig['settings']['temp_path'];
        } else {
            $this->_tempDir = self::getTempDir();
        }
        $this->_tempFile = tempnam($this->_tempDir, 'document');
        $this->_templateNumberings;
        $this->_templateCustomNumberings;
        $this->_zipDocx->open($this->_tempFile, ZipArchive::OVERWRITE);
        $this->_compatibilityMode = false;
        PhpdocxLogger::logger('Create a temp file to use as initial ZIP file. ' .
            'DOCX is a ZIP file.', 'info');
        // sign is set false as default
        $this->_sign = false;
        $this->_relsRelsC = '';
        $this->_relsRelsT = '';
        $this->_contentTypeC = '';
        $this->_contentTypeT = NULL;
        $this->_defaultFont = '';
        $this->_docPropsAppC = '';
        $this->_docPropsAppT = '';
        $this->_docPropsCoreC = '';
        $this->_docPropsCoreT = '';
        $this->_docPropsCustomC = '';
        $this->_docPropsCustomT = '';
        $this->_macro = 0;
        $this->_relsHeader = array();
        $this->_relsFooter = array();
        $this->_parsedStyles = array();
        $this->_relsHeaderFooterImage = array();
        $this->_relsHeaderFooterImageExternal = array();
        $this->_relsHeaderFooterLink = array();
        $this->_relsNotesExternalImage = array();
        $this->_relsNotesImage = array();
        $this->_relsNotesLink = array();
        $this->_sectPr = NULL;
        $this->_tempFileXLSX = array();
        $this->_uniqid = 'phpdocx_'.uniqid();
        $this->_wordDocumentT = '';
        $this->_wordDocumentC = '';
        $this->_wordDocumentStyles = '';
        $this->_wordEndnotesC = '';
        $this->_wordEndnotesT = '';
        $this->_wordFontTableT = '';
        $this->_wordFontTableC = '';
        $this->_wordFooterC = array();
        $this->_wordFooterT = array();
        $this->_wordFootnotesC = '';
        $this->_wordFootnotesT = '';
        $this->_wordHeaderC = array();
        $this->_wordHeaderT = array();
        $this->_wordNumberingC;
        $this->_wordNumberingT;
        $this->_wordRelsDocumentRelsC = '';
        $this->_wordRelsDocumentRelsT = NULL;
        $this->_wordRelsHeaderRelsC = array();
        $this->_wordRelsHeaderRelsT = array();
        $this->_wordRelsFooterRelsC = array();
        $this->_wordRelsFooterRelsT = array();
        $this->_wordSettingsT = '';
        $this->_wordSettingsC = '';
        $this->_wordStylesT = '';
        $this->_wordStylesC = '';
        $this->_wordThemeThemeT = '';
        $this->_wordThemeThemeC = '';
        $this->_wordWebSettingsT = '';
        $this->_wordWebSettingsC = '';

        $this->_defaultPHPDOCXStyles = array('Default Paragraph Font PHPDOCX', //This is the default paragraph font style used in multiple places
                                            'List Paragraph PHPDOCX', //This is the style used for the defolt ordered and unorderd lists
                                            'Title PHPDOCX', //This style is used by the addTitle method
                                            'Subtitle PHPDOCX', //This style is used by the addTitle method
                                            'Normal Table PHPDOCX', //This style is used for the basic table
                                            'Table Grid PHPDOCX', //This style is for basic tables and is also used to embed HTML tables with border="1"
                                            'footnote Text PHPDOCX', //This style is used for default footnotes
                                            'footnote text Car PHPDOCX', //The character style for footnotes
                                            'footnote Reference PHPDOCX', // The style for the footnote
                                            'endnote Text PHPDOCX', //This style is used for default endnotes
                                            'endnote text Car PHPDOCX', //The character style for endnotes
                                            'endnote Reference PHPDOCX', // The style for the endnote
                                            'annotation reference PHPDOCX', //styles for comments
                                            'annotation text PHPDOCX', //styles for comments
                                            'Comment Text Char PHPDOCX', //styles for comments
                                            'annotation subject PHPDOCX', //styles for comments
                                            'Comment Subject Char PHPDOCX', //styles for comments
                                            'Balloon Text PHPDOCX', //styles for comments
                                            'Balloon Text Char PHPDOCX'); //styles for comments
        //Some variables to control that some v2.4 keep working
        $this->footerAdded = false;
        $this->headerAdded = false;
        //
        self::$customLists = array();
        self::$PHPDOCXStyles = '<w:styles xmlns:w="http://schemas.openxmlformats.org/wordprocessingml/2006/main" >
                                        <w:style w:type="character" w:styleId="DefaultParagraphFontPHPDOCX">
                                            <w:name w:val="Default Paragraph Font PHPDOCX"/>
                                            <w:uiPriority w:val="1"/>
                                            <w:semiHidden/>
                                            <w:unhideWhenUsed/>
                                        </w:style>
                                        <w:style w:type="paragraph" w:styleId="ListParagraphPHPDOCX">
                                            <w:name w:val="List Paragraph PHPDOCX"/>
                                            <w:basedOn w:val="Normal"/>
                                            <w:uiPriority w:val="34"/>
                                            <w:qFormat/>
                                            <w:rsid w:val="00DF064E"/>
                                            <w:pPr>
                                                <w:ind w:left="720"/>
                                                <w:contextualSpacing/>
                                            </w:pPr>
                                        </w:style>
                                        <w:style w:type="paragraph" w:styleId="TitlePHPDOCX">
                                            <w:name w:val="Title PHPDOCX"/>
                                            <w:basedOn w:val="Normal"/>
                                            <w:next w:val="Normal"/>
                                            <w:link w:val="TitleCarPHPDOCX"/>
                                            <w:uiPriority w:val="10"/>
                                            <w:qFormat/>
                                            <w:rsid w:val="00DF064E"/>
                                            <w:pPr>
                                                <w:pBdr>
                                                    <w:bottom w:val="single" w:sz="8" w:space="4" w:color="4F81BD" w:themeColor="accent1"/>
                                                </w:pBdr>
                                                <w:spacing w:after="300" w:line="240" w:lineRule="auto"/>
                                                <w:contextualSpacing/>
                                            </w:pPr>
                                            <w:rPr>
                                                <w:rFonts w:asciiTheme="majorHAnsi" w:eastAsiaTheme="majorEastAsia" w:hAnsiTheme="majorHAnsi" w:cstheme="majorBidi"/>
                                                <w:color w:val="17365D" w:themeColor="text2" w:themeShade="BF"/>
                                                <w:spacing w:val="5"/>
                                                <w:kern w:val="28"/>
                                                <w:sz w:val="52"/>
                                                <w:szCs w:val="52"/>
                                            </w:rPr>
                                        </w:style>
                                        <w:style w:type="character" w:customStyle="1" w:styleId="TitleCarPHPDOCX">
                                            <w:name w:val="Title Car PHPDOCX"/>
                                            <w:basedOn w:val="DefaultParagraphFontPHPDOCX"/>
                                            <w:link w:val="TitlePHPDOCX"/>
                                            <w:uiPriority w:val="10"/>
                                            <w:rsid w:val="00DF064E"/>
                                            <w:rPr>
                                                <w:rFonts w:asciiTheme="majorHAnsi" w:eastAsiaTheme="majorEastAsia" w:hAnsiTheme="majorHAnsi" w:cstheme="majorBidi"/>
                                                <w:color w:val="17365D" w:themeColor="text2" w:themeShade="BF"/>
                                                <w:spacing w:val="5"/>
                                                <w:kern w:val="28"/>
                                                <w:sz w:val="52"/>
                                                <w:szCs w:val="52"/>
                                            </w:rPr>
                                        </w:style>
                                        <w:style w:type="paragraph" w:styleId="SubtitlePHPDOCX">
                                            <w:name w:val="Subtitle PHPDOCX"/>
                                            <w:basedOn w:val="Normal"/>
                                            <w:next w:val="Normal"/>
                                            <w:link w:val="SubtitleCarPHPDOCX"/>
                                            <w:uiPriority w:val="11"/>
                                            <w:qFormat/>
                                            <w:rsid w:val="00DF064E"/>
                                            <w:pPr>
                                                <w:numPr>
                                                    <w:ilvl w:val="1"/>
                                                </w:numPr>
                                            </w:pPr>
                                            <w:rPr>
                                                <w:rFonts w:asciiTheme="majorHAnsi" w:eastAsiaTheme="majorEastAsia" w:hAnsiTheme="majorHAnsi" w:cstheme="majorBidi"/>
                                                <w:i/>
                                                <w:iCs/>
                                                <w:color w:val="4F81BD" w:themeColor="accent1"/>
                                                <w:spacing w:val="15"/>
                                                <w:sz w:val="24"/>
                                                <w:szCs w:val="24"/>
                                            </w:rPr>
                                        </w:style>
                                        <w:style w:type="character" w:customStyle="1" w:styleId="SubtitleCarPHPDOCX">
                                            <w:name w:val="Subtitle Car PHPDOCX"/>
                                            <w:basedOn w:val="DefaultParagraphFontPHPDOCX"/>
                                            <w:link w:val="SubtitlePHPDOCX"/>
                                            <w:uiPriority w:val="11"/>
                                            <w:rsid w:val="00DF064E"/>
                                            <w:rPr>
                                                <w:rFonts w:asciiTheme="majorHAnsi" w:eastAsiaTheme="majorEastAsia" w:hAnsiTheme="majorHAnsi" w:cstheme="majorBidi"/>
                                                <w:i/>
                                                <w:iCs/>
                                                <w:color w:val="4F81BD" w:themeColor="accent1"/>
                                                <w:spacing w:val="15"/>
                                                <w:sz w:val="24"/>
                                                <w:szCs w:val="24"/>
                                            </w:rPr>
                                        </w:style>
                                        <w:style w:type="table" w:styleId="NormalTablePHPDOCX">
                                            <w:name w:val="Normal Table PHPDOCX"/>
                                            <w:uiPriority w:val="99"/>
                                            <w:semiHidden/>
                                            <w:unhideWhenUsed/>
                                            <w:qFormat/>
                                            <w:pPr>
                                                <w:spacing w:after="0" w:line="240" w:lineRule="auto"/>
                                            </w:pPr>
                                            <w:tblPr>
                                                <w:tblInd w:w="0" w:type="dxa"/>
                                                <w:tblCellMar>
                                                    <w:top w:w="0" w:type="dxa"/>
                                                    <w:left w:w="108" w:type="dxa"/>
                                                    <w:bottom w:w="0" w:type="dxa"/>
                                                    <w:right w:w="108" w:type="dxa"/>
                                                </w:tblCellMar>
                                            </w:tblPr>
                                        </w:style>
                                        <w:style w:type="table" w:styleId="TableGridPHPDOCX">
                                            <w:name w:val="Table Grid PHPDOCX"/>
                                            <w:uiPriority w:val="59"/>
                                            <w:rsid w:val="00493A0C"/>
                                            <w:pPr>
                                                <w:spacing w:after="0" w:line="240" w:lineRule="auto"/>
                                            </w:pPr>
                                            <w:tblPr>
                                                <w:tblInd w:w="0" w:type="dxa"/>
                                                <w:tblBorders>
                                                    <w:top w:val="single" w:sz="4" w:space="0" w:color="auto"/>
                                                    <w:left w:val="single" w:sz="4" w:space="0" w:color="auto"/>
                                                    <w:bottom w:val="single" w:sz="4" w:space="0" w:color="auto"/>
                                                    <w:right w:val="single" w:sz="4" w:space="0" w:color="auto"/>
                                                    <w:insideH w:val="single" w:sz="4" w:space="0" w:color="auto"/>
                                                    <w:insideV w:val="single" w:sz="4" w:space="0" w:color="auto"/>
                                                </w:tblBorders>
                                                <w:tblCellMar>
                                                    <w:top w:w="0" w:type="dxa"/>
                                                    <w:left w:w="108" w:type="dxa"/>
                                                    <w:bottom w:w="0" w:type="dxa"/>
                                                    <w:right w:w="108" w:type="dxa"/>
                                                </w:tblCellMar>
                                            </w:tblPr>
                                        </w:style>
                                        <w:style w:type="character" w:styleId="CommentReferencePHPDOCX">
                                            <w:name w:val="annotation reference PHPDOCX"/>
                                            <w:basedOn w:val="DefaultParagraphFontPHPDOCX"/>
                                            <w:uiPriority w:val="99"/>
                                            <w:semiHidden/>
                                            <w:unhideWhenUsed/>
                                            <w:rsid w:val="00E139EA"/>
                                            <w:rPr>
                                                <w:sz w:val="16"/>
                                                <w:szCs w:val="16"/>
                                            </w:rPr>
                                        </w:style>
                                        <w:style w:type="paragraph" w:styleId="CommentTextPHPDOCX">
                                            <w:name w:val="annotation text PHPDOCX"/>
                                            <w:basedOn w:val="Normal"/>
                                            <w:link w:val="CommentTextCharPHPDOCX"/>
                                            <w:uiPriority w:val="99"/>
                                            <w:semiHidden/>
                                            <w:unhideWhenUsed/>
                                            <w:rsid w:val="00E139EA"/>
                                            <w:pPr>
                                                <w:spacing w:line="240" w:lineRule="auto"/>
                                            </w:pPr>
                                            <w:rPr>
                                                <w:sz w:val="20"/>
                                                <w:szCs w:val="20"/>
                                            </w:rPr>
                                        </w:style>
                                        <w:style w:type="character" w:customStyle="1" w:styleId="CommentTextCharPHPDOCX">
                                            <w:name w:val="Comment Text Char PHPDOCX"/>
                                            <w:basedOn w:val="DefaultParagraphFontPHPDOCX"/>
                                            <w:link w:val="CommentTextPHPDOCX"/>
                                            <w:uiPriority w:val="99"/>
                                            <w:semiHidden/>
                                            <w:rsid w:val="00E139EA"/>
                                            <w:rPr>
                                                <w:sz w:val="20"/>
                                                <w:szCs w:val="20"/>
                                            </w:rPr>
                                        </w:style>
                                        <w:style w:type="paragraph" w:styleId="CommentSubjectPHPDOCX">
                                            <w:name w:val="annotation subject PHPDOCX"/>
                                            <w:basedOn w:val="CommentTextPHPDOCX"/>
                                            <w:next w:val="CommentTextPHPDOCX"/>
                                            <w:link w:val="CommentSubjectCharPHPDOCX"/>
                                            <w:uiPriority w:val="99"/>
                                            <w:semiHidden/>
                                            <w:unhideWhenUsed/>
                                            <w:rsid w:val="00E139EA"/>
                                            <w:rPr>
                                                <w:b/>
                                                <w:bCs/>
                                            </w:rPr>
                                        </w:style>
                                        <w:style w:type="character" w:customStyle="1" w:styleId="CommentSubjectCharPHPDOCX">
                                            <w:name w:val="Comment Subject Char PHPDOCX"/>
                                            <w:basedOn w:val="CommentTextCharPHPDOCX"/>
                                            <w:link w:val="CommentSubjectPHPDOCX"/>
                                            <w:uiPriority w:val="99"/>
                                            <w:semiHidden/>
                                            <w:rsid w:val="00E139EA"/>
                                            <w:rPr>
                                                <w:b/>
                                                <w:bCs/>
                                                <w:sz w:val="20"/>
                                                <w:szCs w:val="20"/>
                                            </w:rPr>
                                        </w:style>
                                        <w:style w:type="paragraph" w:styleId="BalloonTextPHPDOCX">
                                            <w:name w:val="Balloon Text PHPDOCX"/>
                                            <w:basedOn w:val="Normal"/>
                                            <w:link w:val="BalloonTextCharPHPDOCX"/>
                                            <w:uiPriority w:val="99"/>
                                            <w:semiHidden/>
                                            <w:unhideWhenUsed/>
                                            <w:rsid w:val="00E139EA"/>
                                            <w:pPr>
                                                <w:spacing w:after="0" w:line="240" w:lineRule="auto"/>
                                            </w:pPr>
                                            <w:rPr>
                                                <w:rFonts w:ascii="Tahoma" w:hAnsi="Tahoma" w:cs="Tahoma"/>
                                                <w:sz w:val="16"/>
                                            <w:szCs w:val="16"/>
                                            </w:rPr>
                                        </w:style>
                                        <w:style w:type="character" w:customStyle="1" w:styleId="BalloonTextCharPHPDOCX">
                                            <w:name w:val="Balloon Text Char PHPDOCX"/>
                                            <w:basedOn w:val="DefaultParagraphFontPHPDOCX"/>
                                            <w:link w:val="BalloonTextPHPDOCX"/>
                                            <w:uiPriority w:val="99"/>
                                            <w:semiHidden/>
                                            <w:rsid w:val="00E139EA"/>
                                            <w:rPr>
                                                <w:rFonts w:ascii="Tahoma" w:hAnsi="Tahoma" w:cs="Tahoma"/>
                                                <w:sz w:val="16"/>
                                                <w:szCs w:val="16"/>
                                            </w:rPr>
                                        </w:style>
                                        <w:style w:type="paragraph" w:styleId="footnoteTextPHPDOCX">
                                            <w:name w:val="footnote Text PHPDOCX"/>
                                            <w:basedOn w:val="Normal"/>
                                            <w:link w:val="footnoteTextCarPHPDOCX"/>
                                            <w:uiPriority w:val="99"/>
                                            <w:semiHidden/>
                                            <w:unhideWhenUsed/>
                                            <w:rsid w:val="006E0FDA"/>
                                            <w:pPr>
                                                <w:spacing w:after="0" w:line="240" w:lineRule="auto"/>
                                            </w:pPr>
                                            <w:rPr>
                                                <w:sz w:val="20"/>
                                                <w:szCs w:val="20"/>
                                            </w:rPr>
                                        </w:style>
                                        <w:style w:type="character" w:customStyle="1" w:styleId="footnoteTextCarPHPDOCX">
                                            <w:name w:val="footnote Text Car PHPDOCX"/>
                                            <w:basedOn w:val="DefaultParagraphFontPHPDOCX"/>
                                            <w:link w:val="footnoteTextPHPDOCX"/>
                                            <w:uiPriority w:val="99"/>
                                            <w:semiHidden/>
                                            <w:rsid w:val="006E0FDA"/>
                                            <w:rPr>
                                                <w:sz w:val="20"/>
                                                <w:szCs w:val="20"/>
                                            </w:rPr>
                                        </w:style>
                                        <w:style w:type="character" w:styleId="footnoteReferencePHPDOCX">
                                        <w:name w:val="footnote Reference PHPDOCX"/>
                                        <w:basedOn w:val="DefaultParagraphFontPHPDOCX"/>
                                        <w:uiPriority w:val="99"/>
                                        <w:semiHidden/>
                                        <w:unhideWhenUsed/>
                                        <w:rsid w:val="006E0FDA"/>
                                        <w:rPr>
                                            <w:vertAlign w:val="superscript"/>
                                        </w:rPr>
                                    </w:style>
                                    <w:style w:type="paragraph" w:styleId="endnoteTextPHPDOCX">
                                        <w:name w:val="endnote Text PHPDOCX"/>
                                        <w:basedOn w:val="Normal"/>
                                        <w:link w:val="endnoteTextCarPHPDOCX"/>
                                        <w:uiPriority w:val="99"/>
                                        <w:semiHidden/>
                                        <w:unhideWhenUsed/>
                                        <w:rsid w:val="006E0FDA"/>
                                        <w:pPr>
                                            <w:spacing w:after="0" w:line="240" w:lineRule="auto"/>
                                        </w:pPr>
                                        <w:rPr>
                                            <w:sz w:val="20"/>
                                            <w:szCs w:val="20"/>
                                        </w:rPr>
                                    </w:style>
                                    <w:style w:type="character" w:customStyle="1" w:styleId="endnoteTextCarPHPDOCX">
                                        <w:name w:val="endnote Text Car PHPDOCX"/>
                                        <w:basedOn w:val="DefaultParagraphFontPHPDOCX"/>
                                        <w:link w:val="endnoteTextPHPDOCX"/>
                                        <w:uiPriority w:val="99"/>
                                        <w:semiHidden/>
                                        <w:rsid w:val="006E0FDA"/>
                                        <w:rPr>
                                            <w:sz w:val="20"/>
                                            <w:szCs w:val="20"/>
                                        </w:rPr>
                                    </w:style>
                                    <w:style w:type="character" w:styleId="endnoteReferencePHPDOCX">
                                        <w:name w:val="endnote Reference PHPDOCX"/>
                                        <w:basedOn w:val="DefaultParagraphFontPHPDOCX"/>
                                        <w:uiPriority w:val="99"/>
                                        <w:semiHidden/>
                                        <w:unhideWhenUsed/>
                                        <w:rsid w:val="006E0FDA"/>
                                        <w:rPr>
                                            <w:vertAlign w:val="superscript"/>
                                        </w:rPr>
                                    </w:style>
                                 </w:styles>';

          self::$unorderedListStyle = '<w:abstractNum w:abstractNumId="" xmlns:w="http://schemas.openxmlformats.org/wordprocessingml/2006/main" >
                                        <w:multiLevelType w:val="hybridMultilevel"/>
                                        <w:lvl w:ilvl="0" w:tplc="">
                                            <w:start w:val="1"/>
                                            <w:numFmt w:val="bullet"/>
                                            <w:lvlText w:val=""/>
                                            <w:lvlJc w:val="left"/>
                                            <w:pPr>
                                                <w:ind w:left="720" w:hanging="360"/>
                                            </w:pPr>
                                            <w:rPr>
                                                <w:rFonts w:ascii="Symbol" w:hAnsi="Symbol" w:hint="default"/>
                                            </w:rPr>
                                        </w:lvl>
                                        <w:lvl w:ilvl="1" w:tplc="0C0A0003" w:tentative="1">
                                            <w:start w:val="1"/>
                                            <w:numFmt w:val="bullet"/>
                                            <w:lvlText w:val="o"/>
                                            <w:lvlJc w:val="left"/>
                                            <w:pPr>
                                                <w:ind w:left="1440" w:hanging="360"/>
                                            </w:pPr>
                                            <w:rPr>
                                                <w:rFonts w:ascii="Courier New" w:hAnsi="Courier New" w:cs="Courier New" w:hint="default"/>
                                            </w:rPr>
                                        </w:lvl>
                                        <w:lvl w:ilvl="2" w:tplc="0C0A0005" w:tentative="1">
                                            <w:start w:val="1"/>
                                            <w:numFmt w:val="bullet"/>
                                            <w:lvlText w:val=""/>
                                            <w:lvlJc w:val="left"/>
                                            <w:pPr>
                                                <w:ind w:left="2160" w:hanging="360"/>
                                            </w:pPr>
                                            <w:rPr>
                                                <w:rFonts w:ascii="Wingdings" w:hAnsi="Wingdings" w:hint="default"/>
                                            </w:rPr>
                                        </w:lvl>
                                        <w:lvl w:ilvl="3" w:tplc="0C0A0001" w:tentative="1">
                                            <w:start w:val="1"/>
                                            <w:numFmt w:val="bullet"/>
                                            <w:lvlText w:val=""/>
                                            <w:lvlJc w:val="left"/>
                                            <w:pPr>
                                                <w:ind w:left="2880" w:hanging="360"/>
                                            </w:pPr>
                                            <w:rPr>
                                                <w:rFonts w:ascii="Symbol" w:hAnsi="Symbol" w:hint="default"/>
                                            </w:rPr>
                                        </w:lvl>
                                        <w:lvl w:ilvl="4" w:tplc="0C0A0003" w:tentative="1">
                                            <w:start w:val="1"/>
                                            <w:numFmt w:val="bullet"/>
                                            <w:lvlText w:val="o"/>
                                            <w:lvlJc w:val="left"/>
                                            <w:pPr>
                                                <w:ind w:left="3600" w:hanging="360"/>
                                            </w:pPr>
                                            <w:rPr>
                                                <w:rFonts w:ascii="Courier New" w:hAnsi="Courier New" w:cs="Courier New" w:hint="default"/>
                                            </w:rPr>
                                        </w:lvl>
                                        <w:lvl w:ilvl="5" w:tplc="0C0A0005" w:tentative="1">
                                            <w:start w:val="1"/>
                                            <w:numFmt w:val="bullet"/>
                                            <w:lvlText w:val=""/>
                                            <w:lvlJc w:val="left"/>
                                            <w:pPr>
                                                <w:ind w:left="4320" w:hanging="360"/>
                                            </w:pPr>
                                            <w:rPr>
                                                <w:rFonts w:ascii="Wingdings" w:hAnsi="Wingdings" w:hint="default"/>
                                            </w:rPr>
                                        </w:lvl>
                                        <w:lvl w:ilvl="6" w:tplc="0C0A0001" w:tentative="1">
                                            <w:start w:val="1"/>
                                            <w:numFmt w:val="bullet"/>
                                            <w:lvlText w:val=""/>
                                            <w:lvlJc w:val="left"/>
                                            <w:pPr>
                                                <w:ind w:left="5040" w:hanging="360"/>
                                            </w:pPr>
                                            <w:rPr>
                                                <w:rFonts w:ascii="Symbol" w:hAnsi="Symbol" w:hint="default"/>
                                            </w:rPr>
                                        </w:lvl>
                                        <w:lvl w:ilvl="7" w:tplc="0C0A0003" w:tentative="1">
                                            <w:start w:val="1"/>
                                            <w:numFmt w:val="bullet"/>
                                            <w:lvlText w:val="o"/>
                                            <w:lvlJc w:val="left"/>
                                            <w:pPr>
                                                <w:ind w:left="5760" w:hanging="360"/>
                                            </w:pPr>
                                            <w:rPr>
                                                <w:rFonts w:ascii="Courier New" w:hAnsi="Courier New" w:cs="Courier New" w:hint="default"/>
                                            </w:rPr>
                                        </w:lvl>
                                        <w:lvl w:ilvl="8" w:tplc="0C0A0005" w:tentative="1">
                                            <w:start w:val="1"/>
                                            <w:numFmt w:val="bullet"/>
                                            <w:lvlText w:val=""/>
                                            <w:lvlJc w:val="left"/>
                                            <w:pPr>
                                                <w:ind w:left="6480" w:hanging="360"/>
                                            </w:pPr>
                                            <w:rPr>
                                                <w:rFonts w:ascii="Wingdings" w:hAnsi="Wingdings" w:hint="default"/>
                                            </w:rPr>
                                        </w:lvl>
                                    </w:abstractNum>';

        self::$orderedListStyle ='<w:abstractNum w:abstractNumId="" xmlns:w="http://schemas.openxmlformats.org/wordprocessingml/2006/main" >
                                        <w:multiLevelType w:val="hybridMultilevel"/>
                                        <w:lvl w:ilvl="0" w:tplc="">
                                            <w:start w:val="1"/>
                                            <w:numFmt w:val="decimal"/>
                                            <w:lvlText w:val="%1."/>
                                            <w:lvlJc w:val="left"/>
                                            <w:pPr>
                                                <w:ind w:left="720" w:hanging="360"/>
                                            </w:pPr>
                                        </w:lvl>
                                        <w:lvl w:ilvl="1" w:tplc="" w:tentative="1">
                                            <w:start w:val="1"/>
                                            <w:numFmt w:val="lowerLetter"/>
                                            <w:lvlText w:val="%2."/>
                                            <w:lvlJc w:val="left"/>
                                            <w:pPr>
                                                <w:ind w:left="1440" w:hanging="360"/>
                                            </w:pPr>
                                        </w:lvl>
                                        <w:lvl w:ilvl="2" w:tplc="" w:tentative="1">
                                            <w:start w:val="1"/>
                                            <w:numFmt w:val="lowerRoman"/>
                                            <w:lvlText w:val="%3."/>
                                            <w:lvlJc w:val="right"/>
                                            <w:pPr>
                                                <w:ind w:left="2160" w:hanging="180"/>
                                            </w:pPr>
                                        </w:lvl>
                                        <w:lvl w:ilvl="3" w:tplc="" w:tentative="1">
                                            <w:start w:val="1"/>
                                            <w:numFmt w:val="decimal"/>
                                            <w:lvlText w:val="%4."/>
                                            <w:lvlJc w:val="left"/>
                                            <w:pPr>
                                                <w:ind w:left="2880" w:hanging="360"/>
                                            </w:pPr>
                                        </w:lvl>
                                        <w:lvl w:ilvl="4" w:tplc="" w:tentative="1">
                                            <w:start w:val="1"/>
                                            <w:numFmt w:val="lowerLetter"/>
                                            <w:lvlText w:val="%5."/>
                                            <w:lvlJc w:val="left"/>
                                            <w:pPr>
                                                <w:ind w:left="3600" w:hanging="360"/>
                                            </w:pPr>
                                        </w:lvl>
                                        <w:lvl w:ilvl="5" w:tplc="" w:tentative="1">
                                            <w:start w:val="1"/>
                                            <w:numFmt w:val="lowerRoman"/>
                                            <w:lvlText w:val="%6."/>
                                            <w:lvlJc w:val="right"/>
                                            <w:pPr>
                                                <w:ind w:left="4320" w:hanging="180"/>
                                            </w:pPr>
                                        </w:lvl>
                                        <w:lvl w:ilvl="6" w:tplc="" w:tentative="1">
                                            <w:start w:val="1"/>
                                            <w:numFmt w:val="decimal"/>
                                            <w:lvlText w:val="%7."/>
                                            <w:lvlJc w:val="left"/>
                                            <w:pPr>
                                                <w:ind w:left="5040" w:hanging="360"/>
                                            </w:pPr>
                                        </w:lvl>
                                        <w:lvl w:ilvl="7" w:tplc="" w:tentative="1">
                                            <w:start w:val="1"/>
                                            <w:numFmt w:val="lowerLetter"/>
                                            <w:lvlText w:val="%8."/>
                                            <w:lvlJc w:val="left"/>
                                            <w:pPr>
                                                <w:ind w:left="5760" w:hanging="360"/>
                                            </w:pPr>
                                        </w:lvl>
                                        <w:lvl w:ilvl="8" w:tplc="" w:tentative="1">
                                            <w:start w:val="1"/>
                                            <w:numFmt w:val="lowerRoman"/>
                                            <w:lvlText w:val="%9."/>
                                            <w:lvlJc w:val="right"/>
                                            <w:pPr>
                                                <w:ind w:left="6480" w:hanging="180"/>
                                            </w:pPr>
                                        </w:lvl>
                                    </w:abstractNum>';

        try {
            GenerateDocx::beginDocx();
        }
        catch (Exception $e) {
            PhpdocxLogger::logger($e->getMessage(), 'fatal');
        }


        //We now try to open the zip file defined as base template
        try {
            $openBaseTemplate = $this->_baseTemplateZip->open($this->_baseTemplatePath);
            if ($openBaseTemplate !== true) {
                throw new Exception('Error while opening the Base Template: please, check the path');
            }
        }
        catch (Exception $e) {
            PhpdocxLogger::logger($e->getMessage(), 'fatal');
        }

        //We now extract the contents of the base template into a temp dir for further manipulation
        try {
            $this->_baseTemplateFilesPath = $this->_tempDir.'/'.uniqid(true);
            $extractBaseTemplate =$this->_baseTemplateZip->extractTo($this->_baseTemplateFilesPath);
            if ($extractBaseTemplate !== true) {
                throw new Exception('Error while extracting the Base Template: there may be problems writing in the default tmp folder');
            }
        }
        catch (Exception $e) {
          PhpdocxLogger::logger($e->getMessage(), 'fatal');
        }

        //We should now check if there is any structured content as front page  to include it in the resulting document

        try{
            $baseTemplateDocumentT = $this->_baseTemplateZip->getFromName('word/document.xml');
            if ($baseTemplateDocumentT == '') {
                throw new Exception('Error while extracting the document.xml file from the base template');
            }
        }
        catch (Exception $e) {
            PhpdocxLogger::logger($e->getMessage(), 'fatal');
        }
        $baseDocument = new DOMDocument();
        $baseDocument->loadXML($baseTemplateDocumentT);
        $docXpath = new DOMXPath($baseDocument);
        $docXpath->registerNamespace('w', 'http://schemas.openxmlformats.org/wordprocessingml/2006/main');
        $queryDoc = '//w:body/w:sdt';
        $docNodes = $docXpath->query($queryDoc);

        if ($docNodes->length > 0){
            if($docNodes->item(0)->nodeName == 'w:sdt'){
                $tempDoc = new DomDocument();
                $sdt =$tempDoc->importNode($docNodes->item(0), true);
                $newNode = $tempDoc->appendChild($sdt);
                $frontPage = $tempDoc->saveXML($newNode);
                $this->_wordDocumentC .= $frontPage;
            }
        }

        //Let us extract now the section information to include it at the end of the document.xml file

        $sectPr = $baseDocument->getElementsByTagName('sectPr')->item(0);
        $this->_sectPr = new DOMDocument();
        $sectNode = $this->_sectPr->importNode($sectPr, true);
        $this->_sectPr->appendChild($sectNode);

        //Let us extract the contents of the [Content_Types].xml file for further manipulation

        try {
            $baseTemplateContentTypeT = $this->_baseTemplateZip->getFromName('[Content_Types].xml');
            if ($baseTemplateContentTypeT  == '') {
                throw new Exception('Error while extracting the [Content_Types].xml file from the base template');
            }
        }
        catch (Exception $e) {
            PhpdocxLogger::logger($e->getMessage(), 'fatal');
        }
        $this->_contentTypeT = new DOMDocument();
        $this->_contentTypeT->loadXML($baseTemplateContentTypeT);

        //We are going to include the standard image defaults

        $this->generateDEFAULT('gif', 'image/gif');
        $this->generateDEFAULT('jpg', 'image/jpg');
        $this->generateDEFAULT('png', 'image/png');
        $this->generateDEFAULT('jpeg', 'image/jpeg');
        $this->generateDEFAULT('bmp', 'image/bmp');


        //Let us extract the document.xml.rels for further manipulation
        try {
            $baseTemplateDocumentRelsT = $this->_baseTemplateZip->getFromName('word/_rels/document.xml.rels');
            if ($baseTemplateDocumentRelsT == '') {
                throw new Exception('Error while extracting the document.xml.rels file from the base template');
            }
        }
        catch (Exception $e) {
            PhpdocxLogger::logger($e->getMessage(), 'fatal');
        }

        $this->_wordRelsDocumentRelsT = new DOMDocument();
        $this->_wordRelsDocumentRelsT->loadXML($baseTemplateDocumentRelsT);
        $relationships = $this->_wordRelsDocumentRelsT->getElementsByTagName('Relationship');

        //Now we have to take care of the case that the template used is not one of the default preprocessed templates

        if ($this->_defaultTemplate) {
            self::$numUL = 1;
            self::$numOL = rand(9999, 999999999);

            //Let's get the original template numbering.xml file as a DOMdocument
            try {
                $this->_wordNumberingT = $this->_baseTemplateZip->getFromName('word/numbering.xml');
                if ($this->_wordNumberingT == '') {
                    throw new Exception('Error while extracting the numbering file from the base template');
                }
            }
            catch (Exception $e) {
                PhpdocxLogger::logger($e->getMessage(), 'fatal');
            }
        } else {
            //We should do now some cleaning of the files from the base template zip
            //Let us first look at the document.xml.rels file to analyze the contents
            //Let us analyze its structure
            //In order to do that we should parse word/_rels/document.xml.rels
            $counter = $relationships->length -1;

            for ($j=$counter; $j > -1; $j--) {
                $completeType = $relationships->item($j)->getAttribute('Type');
                $target = $relationships->item($j)->getAttribute('Target');
                $tempArray = explode('/', $completeType);
                $type = array_pop($tempArray);
                //This array holds the data that has to be changed in settings.xml
                $arrayCleaner = array();

                switch($type){
                    case 'header':
                        //TODO: this should be changed if we use default templates with headers
                        array_push($this->_relsHeader,$target);
                        break;
                    case 'footer':
                        //TODO: this should be changed if we use default templates with footers
                        array_push($this->_relsFooter,$target);
                        break;
                    case 'chart':
                        $this->recursiveDelete($this->_baseTemplateFilesPath.'/word/charts');
                        $this->_wordRelsDocumentRelsT->documentElement->removeChild($relationships->item($j));
                        break;
                    case 'embeddings':
                        $this->recursiveDelete($this->_baseTemplateFilesPath.'/word/embeddings');
                        $this->_wordRelsDocumentRelsT->documentElement->removeChild($relationships->item($j));
                        break;
                }

            }

           //Let us now manage the numbering.xml and style.xml files
           // We are going to use some default styles, for example, in the creation of lists, footnotes, titles, ...
           // So we should make sure that it is included in the styles.xml document
           $this->importStyles(PHPDOCX_BASE_TEMPLATE, 'merge', $this->_defaultPHPDOCXStyles);
           //Let us first check if the base template file has a numbering.xml file
           $numRef = rand(9999999, 99999999);
           self::$numUL = $numRef;
           self::$numOL = $numRef +1;

           if(file_exists($this->_baseTemplateFilesPath.'/word/numbering.xml')) {
                //Let's get the original template numbering.xml file as a DOMdocument
                try {
                    $this->_wordNumberingT = $this->_baseTemplateZip->getFromName('word/numbering.xml');
                    if ($this->_wordNumberingT == '') {
                        throw new Exception('Error while extracting the numbering file from the base template');
                    }
                } catch (Exception $e) {
                    PhpdocxLogger::logger($e->getMessage(), 'fatal');
                }
                $this->_wordNumberingT = $this->importSingleNumbering($this->_wordNumberingT, self::$unorderedListStyle, self::$numUL);
                $this->_wordNumberingT = $this->importSingleNumbering($this->_wordNumberingT, self::$orderedListStyle, self::$numOL);
            }else{
                $this->_wordNumberingT = $this->generateBaseWordNumbering();
                $this->_wordNumberingT = $this->importSingleNumbering($this->_wordNumberingT, self::$unorderedListStyle, self::$numUL);
                $this->_wordNumberingT = $this->importSingleNumbering($this->_wordNumberingT, self::$orderedListStyle, self::$numOL);
                //Now we should include the corresponding relationshipand Override
                    $this->_wordRelsDocumentRelsC .= $this->generateRELATIONSHIP(
                     'rId' . rand(99999999, 999999999), 'numbering', 'numbering.xml'
                    );
                    $this->generateOVERRIDE('/word/numbering.xml','application/vnd.openxmlformats-officedocument.wordprocessingml.numbering+xml');
            }

            //Let us now make sure that there are the corresponding xmls, with all their relationships for endnotes and footnotes
            if(!file_exists($this->_baseTemplateFilesPath.'/word/endnotes.xml') ||
               !file_exists($this->_baseTemplateFilesPath.'/word/footnotes.xml') ||
               !file_exists($this->_baseTemplateFilesPath.'/word/comments.xml')){

                $notesZip = new ZipArchive();
                try {
                    $openNotesZip = $notesZip->open(PHPDOCX_BASE_TEMPLATE);
                    if ($openNotesZip !== true){
                    throw new Exception('Error while opening the standard base template to extract the word/footnotes.xml  and word/endnotes.xml file');
                    }
                }
                catch (Exception $e) {
                    PhpdocxLogger::logger($e->getMessage(), 'fatal');
                }

                if(!file_exists($this->_baseTemplateFilesPath.'/word/footnotes.xml')){
                    $notesZip->extractTo($this->_baseTemplateFilesPath, 'word/footnotes.xml');
                    //Now we should include the corresponding relationshipand Override
                    $this->_wordRelsDocumentRelsC .= $this->generateRELATIONSHIP(
                     'rId' . rand(99999999, 999999999), 'footnotes', 'footnotes.xml'
                    );
                   $this->generateOVERRIDE('/word/footnotes.xml','application/vnd.openxmlformats-officedocument.wordprocessingml.footnotes+xml');
                }
                if(!file_exists($this->_baseTemplateFilesPath.'/word/_rels/footnotes.xml.rels')){
                    $notesZip->extractTo($this->_baseTemplateFilesPath, 'word/footnotes.xml.rels');
                }
                if(!file_exists($this->_baseTemplateFilesPath.'/word/endnotes.xml')){
                    $notesZip->extractTo($this->_baseTemplateFilesPath, 'word/endnotes.xml');
                    //Now we should include the corresponding relationshipand Override
                    $this->_wordRelsDocumentRelsC .= $this->generateRELATIONSHIP(
                     'rId' . rand(99999999, 999999999), 'endnotes', 'endnotes.xml'
                    );
                   $this->generateOVERRIDE('/word/endnotes.xml','application/vnd.openxmlformats-officedocument.wordprocessingml.endnotes+xml');
                }
                if(!file_exists($this->_baseTemplateFilesPath.'/word/_rels/endnotes.xml.rels')){
                    $notesZip->extractTo($this->_baseTemplateFilesPath, 'word/endnotes.xml.rels');
                }
                if(!file_exists($this->_baseTemplateFilesPath.'/word/comments.xml')){
                    $notesZip->extractTo($this->_baseTemplateFilesPath, 'word/comments.xml');
                    //Now we should include the corresponding relationshipand Override
                    $this->_wordRelsDocumentRelsC .= $this->generateRELATIONSHIP(
                     'rId' . rand(99999999, 999999999), 'comments', 'comments.xml'
                    );
                   $this->generateOVERRIDE('/word/comments.xml','application/vnd.openxmlformats-officedocument.wordprocessingml.comments+xml');
                }
                if(!file_exists($this->_baseTemplateFilesPath.'/word/_rels/comments.xml.rels')){
                    $notesZip->extractTo($this->_baseTemplateFilesPath, 'word/comments.xml.rels');
                }
            }
        }
        //To finish we make sure that we are using the default paper size and the default language
        $this->modifyPageLayout($this->_phpdocxconfig['settings']['paper_size']);
        $this->setLanguage($this->_phpdocxconfig['settings']['language']);

        //set bidi and rtl static variables
        if(isset($this->_phpdocxconfig['settings']['bidi'])){
            self::$bidi = $this->_phpdocxconfig['settings']['bidi'];
        }else{
            self::$bidi = false;
        }
        if(isset($this->_phpdocxconfig['settings']['rtl'])){
            self::$rtl = $this->_phpdocxconfig['settings']['rtl'];
        }else{
            self::$rtl = false;
        }
        if(self::$bidi || self::$rtl){
            $this->setRTL(array('bidi' => self::$bidi, 'rtl' => self::$rtl));
        }

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
     * Magic method, returns current word XML
     *
     * @access public
     * @return string Return current word
     */
    public function __toString()
    {
        $this->generateTemplateWordDocument();
        PhpdocxLogger::logger('Get document template content.', 'debug');
        return $this->_wordDocumentT;
    }
    /**
     * Setter
     *
     * @access public
     */
    public function setExtension($extension)
    {
        $this->_extension = $extension;
    }

    /**
     * Getter
     *
     * @access public
     */
    public function getExtension()
    {
        return $this->_extension;
    }
    /**
     * Setter
     *
     * @access public
     */
    public function setTemporaryDirectory($tempDir)
    {
        $this->_tempDir = $tempDir;
    }

    /**
     * Getter
     *
     * @access public
     */
    public function getTemporaryDirectory()
    {
        return $this->_tempDir;
    }

    /**
     * Setter
     *
     * @access public
     */
    public function setXmlContentTypes($xmlContentTypes)
    {
        $this->_contentTypeC = $xmlContentTypes;
    }

    /**
     * Getter
     *
     * @access public
     */
    public function getXmlContentTypes()
    {
        return $this->_contentTypeC;
    }

    /**
     * Setter
     *
     * @access public
     */
    public function setXmlRelsRels($xmlRelsRels)
    {
        $this->_relsRelsC = $xmlRelsRels;
    }

    /**
     * Getter
     *
     * @access public
     */
    public function getXmlRelsRels()
    {
        return $this->_relsRelsC;
    }

    /**
     * Setter
     *
     * @access public
     */
    public function setXmlDocPropsApp($xmlDocPropsApp)
    {
        $this->_docPropsAppC = $xmlDocPropsApp;
    }

    /**
     * Getter
     *
     * @access public
     */
    public function getXmlDocPropsApp()
    {
        return $this->_docPropsAppC;
    }

    /**
     * Setter
     *
     * @access public
     */
    public function setXmlDocPropsCore($xmlDocPropsCore)
    {
        $this->_docPropsCoreC = $xmlDocPropsCore;
    }

    /**
     * Getter
     *
     * @access public
     */
    public function getXmlDocPropsCore()
    {
        return $this->_docPropsCoreC;
    }

    /**
     * Setter
     *
     * @access public
     */
    public function setXmlDocPropsCustom($xmlDocPropsCustom)
    {
        $this->_docPropsCustomC = $xmlDocPropsCustom;
    }

    /**
     * Getter
     *
     * @access public
     */
    public function getXmlDocPropsCustom()
    {
        return $this->_docPropsCustomC;
    }

    /**
     * Setter
     *
     * @access public
     */
    public function setXmlWordDocument($xmlWordDocument)
    {
        $this->_wordDocumentC = $xmlWordDocument;
    }

    /**
     * Getter
     *
     * @access public
     */
    public function getXmlWordDocumentContent()
    {
        return $this->_wordDocumentC;
    }

    /**
     * Setter
     *
     * @access public
     */
    public function setXmlWordDocumentStyles($xmlWordDocumentStyles)
    {
        $this->_wordDocumentStyles = $xmlWordDocumentStyles;
    }

    /**
     * Getter
     *
     * @access public
     */
    public function getXmlWordDocumentStyles()
    {
        return $this->_wordDocumentStyles;
    }

    /**
     * Setter
     *
     * @access public
     */
    public function setXmlWordEndnotes($xmlWordEndnotes)
    {
        $this->_wordEndnotesC = $xmlWordEndnotes;
    }

    /**
     * Getter
     *
     * @access public
     */
    public function getXmlWordEndnotes()
    {
        return $this->_wordEndnotesC;
    }

    /**
     * Setter
     *
     * @access public
     */
    public function setXmlWordFontTable($xmlWordFontTable)
    {
        $this->_wordFontTableC = $xmlWordFontTable;
    }

    /**
     * Getter
     *
     * @access public
     */
    public function getXmlWordFontTable()
    {
        return $this->_wordFontTableC;
    }

    /**
     * Setter
     *
     * @access public
     */
    public function setXmlWordFooter1($xmlWordFooter)
    {
        $this->_wordFooterC = $xmlWordFooter;
    }

    /**
     * Getter
     *
     * @access public
     */
    public function getXmlWordFooter1()
    {
        return $this->_wordFooterC;
    }

    /**
     * Setter
     *
     * @access public
     */
    public function setXmlWordHeader1($xmlWordHeader)
    {
        $this->_wordHeaderC = $xmlWordHeader;
    }

    /**
     * Getter
     *
     * @access public
     */
    public function getXmlWordHeader1()
    {
        return $this->_wordHeaderC;
    }

    /**
     * Setter
     *
     * @access public
     */
    public function setXmlWordRelsDocumentRels($xmlWordRelsDocumentRels)
    {
        $this->_wordRelsDocumentRelsC = $xmlWordRelsDocumentRels;
    }

    /**
     * Getter
     *
     * @access public
     */
    public function getXmlWordRelsDocumentRels()
    {
        return $this->_wordRelsDocumentRelsC;
    }

    /**
     * Setter
     *
     * @access public
     */
    public function setXmlWordSettings($xmlWordSettings)
    {
        $this->_wordSettingsC = $xmlWordSettings;
    }

    /**
     * Getter
     *
     * @access public
     */
    public function getXmlWordSettings()
    {
        return $this->_wordSettingsC;
    }

    /**
     * Setter
     *
     * @access public
     */
    public function setXmlWordStyles($xmlWordStyles)
    {
        $this->_wordStylesC = $xmlWordStyles;
    }

    /**
     * Getter
     *
     * @access public
     */
    public function getXmlWordStyles()
    {
        return $this->_wordStylesC;
    }

    /**
     * Setter
     *
     * @access public
     */
    public function setXmlWordThemeTheme1($xmlWordThemeTheme)
    {
        $this->_wordThemeThemeC = $xmlWordThemeTheme;
    }

    /**
     * Getter
     *
     * @access public
     */
    public function getXmlWordThemeTheme1()
    {
        return $this->_wordThemeThemeC;
    }

    /**
     * Setter
     *
     * @access public
     */
    public function setXmlWordWebSettings($xmlWordWebSettings)
    {
        $this->_wordWebSettingsC = $xmlWordWebSettings;
    }

    /**
     * Setter
     *
     * @access public
     */
    public function getXml_Word_WebSettings()
    {
        return $this->_wordWebSettingsC;
    }

    /**
     * Adds a background image to the document
     *
     * @access public
     * @example ../examples/easy/BackgroundImage.php
     * @param string $path
     */
    public function addBackgroundImage($path)
    {
        //Let us extract some basic info about the background image
        $image = pathinfo($path);
        $extension = $image['extension'];
        $imageName = $image['filename'];
        //We define an unique identifier
        $tempId = uniqid(true);
        $identifier = 'rId'. $tempId;

        //We construct the background WordML code
        $this->_background ='<w:background w:color="' . $this->_backgroundColor . '">
                      <v:background id="id_'.uniqid().'" o:bwmode="white" o:targetscreensize="800,600">
                      <v:fill r:id="'.$identifier.'" o:title="tit_'.uniqid(true).'" recolor="t" type="frame" />
                      </v:background></w:background>';
        //We make sure that there exists the corresponding content type
        $this->generateDEFAULT($extension, 'image/'.$extension);
        //We copy the image in the media folder
        $backgroundImage = file_get_contents($path);
        if(!is_dir($this->_baseTemplateFilesPath.'/word/media')){
              mkdir($this->_baseTemplateFilesPath.'/word/media');
        }
        $backgroundImageHandle = fopen($this->_baseTemplateFilesPath.'/word/media/img'.$tempId.'.'.$extension, "w+");
        $contents = fwrite($backgroundImageHandle, $backgroundImage);
        fclose($backgroundImageHandle);
        //We insert the relationship
        $relsImage = '<Relationship Id="'.$identifier.'" Type="http://schemas.openxmlformats.org/officeDocument/2006/relationships/image" Target="media/img'.$tempId.'.'.$extension.'" />';
        $relsNodeImage = $this->_wordRelsDocumentRelsT->createDocumentFragment();
        $relsNodeImage->appendXML($relsImage);
        $this->_wordRelsDocumentRelsT->documentElement->appendChild($relsNodeImage);
        //Now we have to modify the settings to display the background image
        try {
            $settings = fopen($this->_baseTemplateFilesPath.'/word/settings.xml', "r");
            $baseTemplateSettingsT = fread($settings, 1000000);
            fclose($settings);
            if ($baseTemplateSettingsT == '') {
                throw new Exception('Error while extracting settings.xml file from the base template to insert the background image');
            }
        }
        catch (Exception $e) {
            PhpdocxLogger::logger($e->getMessage(), 'fatal');
        }

        $this->_wordSettingsT = new DOMDocument();
        $this->_wordSettingsT->loadXML($baseTemplateSettingsT);
        $settingsImage = $this->_wordSettingsT->createDocumentFragment();
        $settingsImage->appendXML('<w:displayBackgroundShape xmlns:w="http://schemas.openxmlformats.org/wordprocessingml/2006/main" />');
        $this->_wordSettingsT->documentElement->appendChild($settingsImage);
        $newSettings = $this->_wordSettingsT->saveXML();
        $settingsHandle = fopen($this->_baseTemplateFilesPath.'/word/settings.xml', "w+");
        $contents = fwrite($settingsHandle, $newSettings);
        fclose($settingsHandle);

    }

    /**
     *
     * @param string $html
     * @param array $options
     * @deprecated
     */
    public function addBasicHTML($html = '<html><body></body></html>', $options = array())
    {
        $this->embedHTML($html, $options);
    }

    /**
     * Adds a bookmart start or end tag
     *
     * @access public
     * @example ../examples/easy/Bookmarks.php
     * @param array $options
     * Values:
     * 'type' (start, end)
     * 'name' (string)
     * 'rawWordML' (boolean)
     */
    public function addBookmark($options = array('type' => null, 'name' => null, 'rawWordML' => false))
    {
        $type = $options['type'];
        $name = $options['name'];
        //First we check for the requested parameters
        if (empty($type) || empty($name)) {
            PhpdocxLogger::logger('The addBookmark method is lacking at least one required parameter', 'fatal');
        }
        if ($type == 'start') {
           $bookmarkId = rand(9999999, 999999999);
           $bookmark = '<w:bookmarkStart w:id="' .$bookmarkId. '" w:name="' .$name. '" />';
           $this->_bookmarksIds[$name] = $bookmarkId;
        } else if($type == 'end') {
            if (empty($this->_bookmarksIds[$name])) {
                PhpdocxLogger::logger('You are trying to end a nonexisting bookmark', 'fatal');
            }
            $bookmark = '<w:bookmarkEnd w:id="' .$this->_bookmarksIds[$name]. '" />';
            unset($this->_bookmarksIds[$name]);
        } else {
            PhpdocxLogger::logger('The addBookmark type is incorrect', 'fatal');
        }
        PhpdocxLogger::logger('Adds a bookmark' . $type . ' to the Word document.', 'info');
        if (isset($options['rawWordML']) && $options['rawWordML']) {
            return (string) $bookmark;
        } else {
            $this->_wordDocumentC .= (string) $bookmark;
        }
    }

    /**
     * Add a break
     *
     * @access public
     * @example ../examples/easy/PageBreak.php
     * @example ../examples/intermediate/Chart_footnote.php
     * @example ../examples/intermediate/FooterPager.php
     * @example ../examples/intermediate/Multidocument.php
     * @example ../examples/advanced/Report.php
     * @param string $options
     *  Values:
     * 'type' (line, page, column)
     * 'rawWordML' (boolean)
     */
    public function addBreak($options = array('type' => 'line', 'rawWordML' => false))
    {
        $break = CreatePage::getInstance();
        $break->generatePageBreak($options['type']);
        PhpdocxLogger::logger('Add break to word document.', 'info');
        if(isset($options['rawWordML']) && $options['rawWordML']){
            return (string) $break;
        }else{
            $this->_wordDocumentC .= (string) $break;
        }
    }

    /**
     * Add a chart
     *
     * @access public
     * @example ../examples/easy/Chart.php
     * @example ../examples/easy/Chart_area3D.php
     * @example ../examples/easy/Chart_bar.php
     * @example ../examples/easy/Chart_barStacked.php
     * @example ../examples/easy/Chart_bubble.php
     * @example ../examples/easy/Chart_col.php
     * @example ../examples/easy/Chart_doughnut.php
     * @example ../examples/easy/Chart_line.php
     * @example ../examples/easy/Chart_ofPieChart_bar.php
     * @example ../examples/easy/Chart_ofPieChart_pie.php
     * @example ../examples/easy/Chart_percentstaked.php
     * @example ../examples/easy/Chart_radar.php
     * @example ../examples/easy/Chart_scatter.php
     * @example ../examples/easy/Chart_surface.php
     * @example ../examples/intermediate/Chart.php
     * @example ../examples/intermediate/Chart_cylinder.php
     * @example ../examples/intermediate/Chart_footnote.php
     * @example ../examples/intermediate/Multidocument.php
     * @example ../examples/advanced/Report.php
     * @param array $options
     *  Values: 'color' (1, 2, 3...) color scheme,
     *  'perspective' (20, 30...),
     *  'rotX' (20, 30...),
     *  'rotY' (20, 30...),
     *  'data' (array of values),
     *  'float' (left, right, center) floating image. It only applies if textWrap is not inline (default value).
     *  'font' (Arial, Times New Roman...),
     *  'groupBar' (clustered, stacked, percentStacked),
     *  'horizontalOffset' (int) given in emus (1cm = 360000 emus)
     *  'jc' (center, left, right),
     *  'showPercent' (0, 1),
     *  'sizeX' (10, 11, 12...),
     *  'sizeY' (10, 11, 12...),
     *  'textWrap' (0 (inline), 1 (square), 2 (front), 3 (back), 4 (up and bottom)),
     *  'verticalOffset' (int) given in emus (1cm = 360000 emus)
     *  'title',
     *  'type' (barChart, bar3DChart, bar3DChartCylinder, bar3DChartCone,  bar3DChartPyramid, colChart, col3DChart,
     *          col3DChartCylinder,  col3DChartCone, bar3DChartPyramid, pieChart, pie3DChart, lineChart, line3DChart,
     *          areaChart, area3DChart, radar, scatterChart, surfaceChart,ofpiechar, doughnut, bublechart)
     *  'legendPos' (r, l, t, b, none),
     *  'legendOverlay' (0, 1),
     *  'border' (0, 1),
     *  'haxLabel' horizontal axis label,
     *  'vaxLabel' vertical axis label,
     *  'showtable' (0, 1) shows the table of values,
     *  'vaxLabelDisplay' (rotated, vertical, horizontal),
     *  'haxLabelDisplay' (rotated, vertical, horizontal),
     *  'hgrid' (0, 1, 2, 3),
     *  'vgrid' (0, 1, 2, 3),
     *  'style' this work only in radar charts.
     *  'gapWidth' distance between the pie and the second chart(ofpiechart)
     *  'secondPieSize' : size of the second chart(ofpiechart)
     *  'splitType' how decide to split the values :auto(Default Split), cust(Custom Split), percent(Split by Percentage), pos(Split by Position), val(Split by Value)
     *  'splitPos' split position , integer or float
     *  'custSplit' array of index to split
     *  'subtype' type of the second chart pie or bar
     *  'explosion' distance between the diferents values
     *  'holeSize' size of the hole in doughnut type
     *  'symbol'  array of symbols(scatter chart)
     *  'symbolSize' the size of the simbols
     *  'smooth' smooth the line (scatter chart)
     *  'wireframe' boolean(surface chart)to remove content color and only leave the border colors
     *  'showValue' (0,1) shows the values inside the chart
     *  'showCategory' (0,1) shows the category inside the chart
     *  'rawWordML' (boolean)
     */
    public function addChart($options = array('rawWordML' => false))
    {
        PhpdocxLogger::logger('Create chart.', 'debug');
        try {
            if (isset($options['data']) && isset($options['type'])) {
                self::$intIdWord++;
                PhpdocxLogger::logger('New ID ' . self::$intIdWord . ' . Chart.', 'debug');
                $type = $options['type'];
                if(strpos($type, 'Chart') === false)
                    $type .= 'Chart';

                $graphic = CreateChartFactory::createObject($type);

                if ($graphic->createGraphic(self::$intIdWord, $options) != false) {
                    PhpdocxLogger::logger('Add chart word/charts/chart' . self::$intIdWord .
                        '.xml to DOCX.', 'info');
                    $this->_zipDocx->addFromString(
                        'word/charts/chart' . self::$intIdWord . '.xml',
                        $graphic->getXmlChart()
                    );
                    $this->_wordRelsDocumentRelsC .=
                        $this->generateRELATIONSHIP(
                            'rId' . self::$intIdWord, 'chart',
                            'charts/chart' . self::$intIdWord . '.xml'
                        );
                    $this->generateDEFAULT('xlsx', 'application/octet-stream');
                    $this->generateOVERRIDE(
                        '/word/charts/chart' . self::$intIdWord . '.xml',
                        'application/vnd.openxmlformats-officedocument.' .
                        'drawingml.chart+xml'
                    );
                } else {
                    throw new Exception(
                        'There was an error related to the chart.'
                    );
                }
                $excel = $graphic->getXlsxType();

                $this->_tempFileXLSX[self::$intIdWord] =
                    tempnam($this->_tempDir, 'documentxlsx');
                if (
                    $excel->createXlsx(
                        $this->_tempFileXLSX[self::$intIdWord],
                        $options['data']
                    ) != false
                ) {
                    $this->_zipDocx->addFile(
                        $this->_tempFileXLSX[self::$intIdWord],
                        'word/embeddings/datos' . self::$intIdWord . '.xlsx'
                    );

                    $chartRels = CreateChartRels::getInstance();
                    $chartRels->createRelationship(self::$intIdWord);
                    $this->_zipDocx->addFromString(
                        'word/charts/_rels/chart' . self::$intIdWord .
                        '.xml.rels',
                        (string) $chartRels
                    );
                }
                if(isset($options['rawWordML']) && $options['rawWordML']){
                        return (string) $graphic;
                    }else{
                        $this->_wordDocumentC .= (string) $graphic;
                    }
            } else {
                throw new Exception(
                    'Images must have "data" and "type" values.'
                );
            }
        }
        catch (Exception $e) {
            PhpdocxLogger::logger($e->getMessage(), 'fatal');
        }
    }

    /**
     * Adds a comment
     *
     * @access public
     * @example ../examples/easy/Comment.php
     * @param array $options
     *  Values:
     * 'textDocument'(mixed) a string of text to appear in the document body as anchor for the comment or an array with the text and associated text options
     * 'textComment' (mixed) a string of text to be used as the comment text or a WordML fragment
     * 'initials' (string)
     * 'author' (string)
     * 'date' (string)
     * 'rawWordML' (boolean)
     */
    public function addComment($options = array('rawWordML' => false))
    {
        $id = rand(9999,32766);//this number can not be bigger than 32767
        $idBookmark = uniqid(true);
        if($options['textComment'] instanceof WordMLFragment){
            $commentBase ='<w:comment w:id="'.$id.'"';
            if(isset($options['initials'])){
                $commentBase .= ' w:initials="' . $options['initials'] . '"';
            }
            if(isset($options['author'])){
                $commentBase .= ' w:author="' . $options['author'] . '"';
            }
            if(isset($options['date'])){
                $commentBase .= ' w:date="' . date("Y-m-d\TH:i:s\Z", strtotime($options['date'])) . '"';
            }
            $commentBase .= ' xmlns:ve="http://schemas.openxmlformats.org/markup-compatibility/2006"
                xmlns:o="urn:schemas-microsoft-com:office:office"
                xmlns:r="http://schemas.openxmlformats.org/officeDocument/2006/relationships"
                xmlns:m="http://schemas.openxmlformats.org/officeDocument/2006/math"
                xmlns:v="urn:schemas-microsoft-com:vml"
                xmlns:wp="http://schemas.openxmlformats.org/drawingml/2006/wordprocessingDrawing"
                xmlns:w10="urn:schemas-microsoft-com:office:word"
                xmlns:w="http://schemas.openxmlformats.org/wordprocessingml/2006/main"
                xmlns:wne="http://schemas.microsoft.com/office/word/2006/wordml"
                >';
            $commentBase .= $this->parseWordMLNote('comment', $options['textComment'], array(), array());
            $commentBase .= '<w:bookmarkStart w:id="' . $idBookmark . '" w:name="_GoBack"/><w:bookmarkEnd w:id="' . $idBookmark . '"/>';
            $commentBase .= '</w:comment>';
        }else{
            $commentBase = '<w:comment w:id="' . $id . '"';
            if (isset($options['initials'])) {
                $commentBase .= ' w:initials="' . $options['initials'] . '"';
            }
            if (isset($options['author'])) {
                $commentBase .= ' w:author="' . $options['author'] . '"';
            }
            if (isset($options['date']) && ($options['date'] instanceof date )) {
                $commentBase .= ' w:date="' . date("Y-m-d\TH:i:s\Z", strtotime($options['date'])) . '"';
            }
            $commentBase .= ' xmlns:w="http://schemas.openxmlformats.org/wordprocessingml/2006/main" ><w:p>
                <w:pPr><w:pStyle w:val="commentTextPHPDOCX"/>';
            if(self::$bidi){
                $commentBase .= '<w:bidi />';
            }
            $commentBase .= '</w:pPr>';
            $commentBase .= '<w:r><w:rPr><w:rStyle w:val="commentReferencePHPDOCX"/>';
            if(self::$rtl){
                $commentBase .= '<w:rtl />';
            }
            $commentBase .= '</w:rPr><w:annotationRef/></w:r>';
            $commentBase .= '<w:r>';
            if(self::$rtl){
                $commentBase .= '<w:rPr><w:rtl /></w:rPr>';
            }
            $commentBase .= '<w:t xml:space="preserve">' . $options['textComment'] . '</w:t></w:r></w:p>';
            $commentBase .= '<w:bookmarkStart w:id="' . $idBookmark . '" w:name="_GoBack"/><w:bookmarkEnd w:id="' . $idBookmark . '"/>';
            $commentBase .= '</w:comment>';
        }
        if(!is_array($options['textDocument'])){
           $options['textDocument'] = array('text' => $options['textDocument']);
        }
        $textOptions = $options['textDocument'];
        $textOptions['rawWordML'] = true;
        $text = $textOptions['text'];
        $textOptions = self::setRTLOptions($textOptions);
        $commentDocument = $this->addText($text, $textOptions);
        $commentStart = '</w:pPr><w:commentRangeStart w:id="' . $id . '"/>';
        $commentEnd .= '<w:commentRangeEnd w:id="' . $id . '"/>
                         <w:r><w:rPr><w:rStyle w:val="CommentReference"/>';
        if(self::$rtl){
            $commentEnd .= '<w.rtl />';
        }
        $commentEnd .= '</w:rPr><w:commentReference w:id="' . $id . '"/></w:r></w:p>';
        //Clean the commentDocument from auxilairy variable
        $commentDocument = preg_replace('/__[A-Z]+__/', '', $commentDocument);
        //Prepare the data
        $commentDocument = str_replace('</w:pPr>', $commentStart, $commentDocument);
        $commentDocument = str_replace('</w:p>', $commentEnd, $commentDocument);


        //We now try to open the zip file defined as base template

        $filename = $this->_baseTemplateFilesPath.'/word/comments.xml';
        $handle = fopen($filename, "r");
        $contents = fread($handle, 999999);
        fclose($handle);


        $this->_wordCommentsT = new DOMDocument();
        $this->_wordCommentsT->loadXML($contents);
        $tempNode = $this->_wordCommentsT->createDocumentFragment();
        $tempNode->appendXML($commentBase);
        $this->_wordCommentsT->documentElement->appendChild($tempNode);

        //We copy the  content into the respective file
        $commentHandler = fopen($this->_baseTemplateFilesPath.'/word/comments.xml', "w+");
        fwrite($commentHandler, $this->_wordCommentsT->saveXML());
        fclose($commentHandler);

        PhpdocxLogger::logger('Add comment to word document.', 'info');

        if(isset($options['rawWordML']) && $options['rawWordML']){
            return (string) $commentDocument;
        }else{
            $this->_wordDocumentC .= (string) $commentDocument;
        }
    }

    /**
     * Adds date and hour to the Word document
     *
     * @access public
     * @example ../examples/easy/DateAndHour.php
     * @param array $options Style options to apply to the date
     *  Values:
     * 'b' (on, off) set to on for right to left languages
     * 'bidi' (on, off)
     * 'color' (ffffff, ff0000...)
     * 'font' (Arial, Times New Roman...)
     * 'i' (on, off)
     * 'jc' (both, center, distribute, left, right)
     * 'pageBreakBefore' (on, off)
     * 'sz' (1, 2, 3...)
     * 'u' (dash, dotted, double, single, wave, words)
     * 'widowControl' (on, off)
     * 'wordWrap' (on, off)
     * 'lineSpacing' 120, 240 (standard), 480...
     * 'indent_left' 100...
     * 'indent_right' 100...
     * 'rawWordML' (boolean)
     * 'rtl' (on, off) set to on for right to left languages
     * 'dateFormat (string) dd/MM/yyyy H:mm:ss (default value) One may define a
     * customised format like dd' of 'MMMM' of 'yyyy' at 'H:mm (resulting in 20 of December of 2012 at 9:30)
     *
     */
    public function addDateAndHour($options = array( 'dateFormat' => 'dd/MM/yyyy H:mm:ss', 'rawWordML' => false))
    {

        $options = self::setRTLOptions($options);
        if(!isset($options['dateFormat'])){
            $options['dateFormat'] = 'dd/MM/yyyy H:mm:ss';
        }
        $textOptions = $options;
        $textOptions['rawWordML'] = true;
        $date = $this->addText('date', $textOptions);
        $date = preg_replace('/__[A-Z]+__/','',$date);
        $dateRef = '<?xml version="1.0" encoding="UTF-8" ?>'.$date;
        $dateRef = str_replace('<w:p>', '<w:p xmlns:w="http://schemas.openxmlformats.org/wordprocessingml/2006/main">', $dateRef);
        $dateDOM = new DOMDocument();
        $dateDOM->loadXML($dateRef);
        $pPrNodes = $dateDOM->getElementsByTagName('pPr');
        if($pPrNodes->length > 0){
            $pPrContent = $dateDOM->saveXML($pPrNodes->item(0));
        }else{
            $pPrContent = '';
        }
        $rPrNodes = $dateDOM->getElementsByTagName('rPr');
        if($rPrNodes->length > 0){
            $rPrContent = $dateDOM->saveXML($rPrNodes->item(0));
        }else{
            $rPrContent = '';
        }
        if($pPrContent != ''){
            $pPrContent = str_replace('</w:pPr>', $rPrContent . '</w:pPr>', $pPrContent);
        }else{
            $pPrContent = '<w:pPr>' . $rPrContent . '</w:pPr>';
        }
        $runs = '<w:r>' . $rPrContent . '<w:fldChar w:fldCharType="begin" /></w:r>';
        $runs .= '<w:r>' . $rPrContent . '<w:instrText xml:space="preserve">TIME \@ &quot;'. $options['dateFormat'] .'&quot;</w:instrText></w:r>';
        $runs .= '<w:r>' . $rPrContent . '<w:fldChar w:fldCharType="separate" /></w:r>';
        $runs .= '<w:r>' . $rPrContent . '<w:t>date</w:t></w:r>';
        $runs .= '<w:r>' . $rPrContent . '<w:fldChar w:fldCharType="end" /></w:r>';

        $date = '<w:p>' . $pPrContent . $runs . '</w:p>';
        PhpdocxLogger::logger('Add a date to word document.', 'info');
        if(isset($options['rawWordML']) && $options['rawWordML']){
            return (string) $date;
        }else{
            $this->_wordDocumentC .= (string) $date;
        }
    }

    /**
     * Embeds a DOCX.
     *
     * @access public
     * @example ../examples/easy/DOCX.php
     * @param array $options
     * Values:
     * 'pathDOCX' (string) path to DOCX
     * 'matchSource' (bool) if true (default value)tries to preserve as much as posible the styles of the docx to be included
     * 'preprocess' (boolean) if true does some preprocessing on the docx file to add
     *  WARNING: beware that the docx to insert gets modified so please make a safeguard copy first
     * 'rawWordML' (boolean)
     */
    public function addDOCX($options = array('matchSource' => true, 'rawWordML' => false, 'preprocess' => false))
    {
        try {
            if ($this->_compatibilityMode) {
              throw new Exception('Running in compatibility mode. Unsupported method.');
            }
            if (file_exists($options['pathDOCX'])) {
                //if preprocess is true we do certain previous manipulation on the docx to embed
                if($options['preprocess']){
                    $this->preprocessDocx($options['pathDOCX']);
                }
                $wordDOCX = EmbedDOCX::getInstance();
                if(isset($options['matchSource']) && $options['matchSource'] === false){
                    $wordDOCX->embed(false);
                }else{
                    $wordDOCX->embed(true);
                }
                PhpdocxLogger::logger('Add DOCX file to word document.', 'info');

                $this->_zipDocx->addFile($options['pathDOCX'], 'word/docx' . $wordDOCX->getId() .
                                                    '.zip');
                $this->_wordRelsDocumentRelsC .= $this->generateRELATIONSHIP(
                    'rDOCXId' . $wordDOCX->getId(), 'aFChunk', 'docx' .
                                                               $wordDOCX->getId() . '.zip', 'TargetMode="Internal"');
                $this->generateDEFAULT('zip', 'application/vnd.openxmlformats-officedocument.wordprocessingml.document.main+xml');
                if (isset($options['rawWordML']) && $options['rawWordML']) {
                    return (string) $wordDOCX . '<w:p />';
                } else {
                    $this->_wordDocumentC .= (string) $wordDOCX;
                }
            } else {
                throw new Exception('File does not exist.');
            }
        }
        catch (Exception $e) {
            PhpdocxLogger::logger($e->getMessage(), 'fatal');
        }
    }

    /**
     * Add an element to embedd in other elements
     *
     * @access public
     * @deprecated
     * @example ../examples/easy/Chart_areaEmbeddedIntoList.php
     * @example ../examples/intermediate/List.php
     * @example ../examples/intermediate/TableStyled.php
     * @param string $type Element type.
     *  Values: 'addImage', 'addGraphic', 'addLink', 'addTextBox', 'addText'
     * @param array $parrams Set of parameters.
     *  Values: same as elements
     * @return Element object
     */
    public function addElement($type, $params = '')
    {
        $type = str_replace('Chart', 'Graphic', $type);
        $type = str_replace('add', 'Create', $type);
        if ($type == 'CreateGraphic') {
            if(strpos($params['type'], 'Chart') === false)
                $params['type'] .= 'Chart';
            //we use the factory to create the object
            $element = CreateChartFactory::createObject($params['type']);
        } else {
            $element = CreateFactory::createObject($type);
        }
        $type = str_replace('Create', 'init', $type);
        $element->$type($params);
        if ($type == 'initImage') {
            PhpdocxLogger::logger('Create embedded image.', 'debug');
            try {
                if (isset($params['name']) && file_exists($params['name'])) {
                    $attrImages = getimagesize($params['name']);
                    try {
                        if ($attrImages['mime'] == 'image/jpg' ||
                            $attrImages['mime'] == 'image/jpeg' ||
                            $attrImages['mime'] == 'image/png' ||
                            $attrImages['mime'] == 'image/gif'
                        ) {
                            self::$intIdWord++;
                            PhpdocxLogger::logger('New ID ' . self::$intIdWord .
                                ' . Embedded image.', 'debug');
                            $type = str_replace('add', 'Create', $type);
                            $dir = $this->parsePath($params['name']);
                            $element->setRId(self::$intIdWord);
                            PhpdocxLogger::logger('Add image ' . $params['name']
                                . ' to DOCX.', 'info');
                            $this->_zipDocx->addFile(
                                $params['name'],
                                'word/media/image' . self::$intIdWord . '.'
                                . $dir['extension']
                            );
                            $this->generateDEFAULT(
                                $dir['extension'], $attrImages['mime']
                            );
                            PhpdocxLogger::logger('Add a new relationship related to image '
                                . $params['name'] . ' .', 'debug');
                            $this->_wordRelsDocumentRelsC .=
                                $this->generateRELATIONSHIP(
                                    'rId'
                                    . self::$intIdWord, 'image', 'media/image'
                                    . self::$intIdWord . '.'
                                    . $dir['extension']
                                );
                        } else {
                            throw new Exception(
                                'Image format is not supported.'
                            );
                        }
                    }
                    catch (Exception $e) {
                        PhpdocxLogger::logger($e->getMessage(), 'fatal');
                    }
                } else {
                    throw new Exception('Image does not exist.');
                }
            }
            catch (Exception $e) {
                PhpdocxLogger::logger($e->getMessage(), 'fatal');
            }
        } elseif ($type == 'initGraphic' || $type == 'initChart') {
            PhpdocxLogger::logger('Create embedded chart.', 'debug');
            try {
                if (isset($params['data']) && isset($params['type'])) {
                    self::$intIdWord++;
                    PhpdocxLogger::logger('New ID ' . self::$intIdWord . ' . Embedded chart.', 'debug');
                    $element->setRId(self::$intIdWord);
                    PhpdocxLogger::logger('Add chart ' . 'word/charts/chart' . self::$intIdWord
                        . '.xml to DOCX.', 'info');

                    $this->_zipDocx->addFromString(
                        'word/charts/chart' . self::$intIdWord . '.xml',
                        $element->createEmbeddedXmlChart()
                    );
                    PhpdocxLogger::logger('Add a new relationship related to chart.', 'debug');
                    $this->_wordRelsDocumentRelsC .=
                        $this->generateRELATIONSHIP(
                            'rId' . self::$intIdWord, 'chart', 'charts/chart' .
                            self::$intIdWord . '.xml'
                        );
                    $this->generateDEFAULT('xlsx', 'application/octet-stream');
                    $this->generateOVERRIDE(
                        '/word/charts/chart' . self::$intIdWord .
                        '.xml',
                        'application/vnd.openxmlformats-officedocument' .
                        '.drawingml.chart+xml'
                    );

                    $excel = $element->getXlsxType();

                    $this->_tempFileXLSX[self::$intIdWord] = tempnam($this->_tempDir, 'documentxlsx');
                    if (
                        $excel->createXlsx(
                            $this->_tempFileXLSX[self::$intIdWord], $params['data'],
                            $params['type']
                        ) != false
                    ) {
                        $this->_zipDocx->addFile(
                            $this->_tempFileXLSX[self::$intIdWord],
                            'word/embeddings/datos' . self::$intIdWord . '.xlsx'
                        );

                        $chartRels = CreateChartRels::getInstance();
                        $chartRels->createRelationship(self::$intIdWord);
                        PhpdocxLogger::logger('Add chart ' . 'word/charts/_rels/chart'
                            . self::$intIdWord . '.xml.rels to DOCX.', 'info');
                        $this->_zipDocx->addFromString(
                            'word/charts/_rels/chart' . self::$intIdWord
                            . '.xml.rels', (string) $chartRels
                        );
                    }
                } else {
                    throw new Exception(
                        'Charts must have "data" and "type" values.'
                    );
                }
            }
            catch (Exception $e) {
                PhpdocxLogger::logger($e->getMessage(), 'fatal');
            }
        }

        return $element;
    }

    /**
     * Adds an endnote
     *
     * @access public
     * @example ../examples/easy/Endnote.php
     * @example ../examples/intermediate/EndnoteAndFootnote.php
     * @param array $options.
     * Values:
     * 'textDocument'(mixed) a string of text to appear in the document body or an array with the text and associated text options
     * 'textEndnote' (mixed) a string of text to be used as the endnote text or a WordML fragment
     * 'endnoteMark' (array) bidi, customMark, font, b, i, color, rtl
     * 'referenceMark' (array) bidi, font, b, i, color, rtl
     * 'rawWordML' (boolean)
     */
    public function addEndnote($options = array('rawWordML' => false))
    {
        $options['endnoteMark'] = self::setRTLOptions($options['endnoteMark']);
        $options['referenceMark'] = self::setRTLOptions($options['referenceMark']);
        $id = rand(9999,32766);//this number can not be bigger than 32767
        if($options['textEndnote'] instanceof WordMLFragment){
            $endnoteBase ='<w:endnote w:id="'.$id.'"
                xmlns:ve="http://schemas.openxmlformats.org/markup-compatibility/2006"
                xmlns:o="urn:schemas-microsoft-com:office:office"
                xmlns:r="http://schemas.openxmlformats.org/officeDocument/2006/relationships"
                xmlns:m="http://schemas.openxmlformats.org/officeDocument/2006/math"
                xmlns:v="urn:schemas-microsoft-com:vml"
                xmlns:wp="http://schemas.openxmlformats.org/drawingml/2006/wordprocessingDrawing"
                xmlns:w10="urn:schemas-microsoft-com:office:word"
                xmlns:w="http://schemas.openxmlformats.org/wordprocessingml/2006/main"
                xmlns:wne="http://schemas.microsoft.com/office/word/2006/wordml"
                >';
            $endnoteBase .= $this->parseWordMLNote('endnote', $options['textEndnote'], $options['endnoteMark'], $options['referenceMark']);
            $endnoteBase .= '</w:endnote>';
        }else{
            $endnoteBase = '<w:endnote w:id="' . $id . '" xmlns:w="http://schemas.openxmlformats.org/wordprocessingml/2006/main"><w:p>
                <w:pPr><w:pStyle w:val="endnoteTextPHPDOCX"/>';
            if(self::$bidi){
                $endnoteBase .= '<w:bidi />';
            }
            $endnoteBase .= '</w:pPr><w:r><w:rPr><w:rStyle w:val="endnoteReferencePHPDOCX"/>';
            //Parse the referenceMark options
            if(isset($options['referenceMark']['font'])){
              $endnoteBase .=  '<w:rFonts w:ascii="' . $options['referenceMark']['font'] .
                                '" w:hAnsi="' . $options['referenceMark']['font'] .
                                '" w:cs="' . $options['referenceMark']['font'] . '"/>';
            }
            if(isset($options['referenceMark']['b'])){
              $endnoteBase .=  '<w:b w:val="' . $options['referenceMark']['b'] . '"/>';
            }
            if(isset($options['referenceMark']['i'])){
              $endnoteBase .=  '<w:i w:val="' . $options['referenceMark']['i'] . '"/>';
            }
            if(isset($options['referenceMark']['color'])){
              $endnoteBase .=  '<w:color w:val="' . $options['referenceMark']['color'] . '"/>';
            }
            if(isset($options['referenceMark']['sz'])){
              $endnoteBase .=  '<w:sz w:val="' . (2 * $options['referenceMark']['sz']) . '"/>';
              $endnoteBase .=  '<w:szCs w:val="' . (2 * $options['referenceMark']['sz']) . '"/>';
            }
            if(isset($options['referenceMark']['rtl']) && $options['referenceMark']['rtl']){
                $endnoteBase .= '<w:rtl />';
            }
            $endnoteBase .= '</w:rPr>';
            if(isset($options['endnoteMark']['customMark'])){
                $endnoteBase .= '<w:t>' . $options['endnoteMark']['customMark'] . '</w:t>';
            }else{
                $endnoteBase .= '<w:endnoteRef/>';
            }
            $endnoteBase .= '</w:r>';
            if(self::$rtl){
                $endnoteBase .= '<w:rPr><w:rtl /></w:rPr>';
            }
            $endnoteBase .= '<w:r><w:t xml:space="preserve">' . $options['textEndnote'] . '</w:t></w:r></w:p>
                </w:endnote>';
        }
        if(!is_array($options['textDocument'])){
           $options['textDocument'] = array('text' => $options['textDocument']);
        }
        $textOptions = $options['textDocument'];
        $textOptions['rawWordML'] = true;
        $text = $textOptions['text'];
        $textOptions = self::setRTLOptions($textOptions);
        $endnoteDocument = $this->addText($text, $textOptions);
        $endnoteMark = '<w:r><w:rPr><w:rStyle w:val="endnoteReferencePHPDOCX" />';
        //Parse the endnoteMark options
        if(isset($options['endnoteMark']['font'])){
          $endnoteMark .=  '<w:rFonts w:ascii="' . $options['endnoteMark']['font'] .
                            '" w:hAnsi="' . $options['endnoteMark']['font'] .
                            '" w:cs="' . $options['endnoteMark']['font'] . '"/>';
        }
        if(isset($options['endnoteMark']['b'])){
          $endnoteMark .=  '<w:b w:val="' . $options['endnoteMark']['b'] . '"/>';
        }
        if(isset($options['endnoteMark']['i'])){
          $endnoteMark .=  '<w:i w:val="' . $options['endnoteMark']['i'] . '"/>';
        }
        if(isset($options['endnoteMark']['color'])){
          $endnoteMark .=  '<w:color w:val="' . $options['endnoteMark']['color'] . '"/>';
        }
        if(isset($options['endnoteMark']['sz'])){
          $endnoteMark .=  '<w:sz w:val="' . (2 * $options['endnoteMark']['sz']) . '"/>';
          $endnoteMark .=  '<w:szCs w:val="' . (2 * $options['endnoteMark']['sz']) . '"/>';
        }
        if(isset($options['endnoteMark']['rtl']) && $options['endnoteMark']['rtl']){
                $endnoteMark .= '<w:rtl />';
        }
        $endnoteMark .= '</w:rPr><w:endnoteReference w:id="'.$id.'" ';
        if(isset($options['endnoteMark']['customMark'])){
            $endnoteMark .= 'w:customMarkFollows="1"/><w:t>' . $options['endnoteMark']['customMark'] . '</w:t>';
        }else{
            $endnoteMark .= '/>';
        }
        $endnoteMark .= '</w:r></w:p>';
        $endnoteDocument = str_replace('</w:p>', $endnoteMark, $endnoteDocument);
        //Clean the endnoteDocument from auxilairy variable
        $endnoteDocument = preg_replace('/__[A-Z]+__/', '', $endnoteDocument);

        //We now try to open the zip file defined as base template

        $filename = $this->_baseTemplateFilesPath.'/word/endnotes.xml';
        $handle = fopen($filename, "r");
        $contents = fread($handle, 999999);
        fclose($handle);


        $this->_wordEndnotesT = new DOMDocument();
        $this->_wordEndnotesT->loadXML($contents);

        $tempNode = $this->_wordEndnotesT->createDocumentFragment();
        $tempNode->appendXML($endnoteBase);
        $this->_wordEndnotesT->documentElement->appendChild($tempNode);

        //We copy the  content into the respective file
        $endnoteHandler = fopen($this->_baseTemplateFilesPath.'/word/endnotes.xml', "w+");
        fwrite($endnoteHandler, $this->_wordEndnotesT->saveXML());
        fclose($endnoteHandler);

        PhpdocxLogger::logger('Add endnote to word document.', 'info');
        if(isset($options['rawWordML']) && $options['rawWordML']){
            return (string) $endnoteDocument;
        }else{
            $this->_wordDocumentC .= (string) $endnoteDocument;
        }
    }

    /**
     * Add a new font
     *
     * @access public
     * @param array $fonts Fonts to add
     */
    public function addFont($fonts)
    {
        $font = CreateFontTable::getInstance();
        $font->createFont($fonts);
        PhpdocxLogger::logger('Add font to fontable document.', 'info');
        $this->_wordFontTableC .= (string) $font;
    }

    /**
     * Add a footer.
     *
     * @access public
     * @example ../examples/easy/Footer.php
     * @example ../examples/intermediate/HeaderAndFooter.php
     * @example ../examples/advanced/Report.php
     * @param array $footer
     * @param array
     *  Values:
     * 'default'(object) WordMLFragment
     * 'even' (object) WordMLFragment
     * 'first' (object) WordMLFragment
     */
    public function addFooter($footers)
    {
        $this->footerAdded = true;
        $this->removeFooters();
        foreach($footers as $key => $value){
            if ($value instanceof WordMLFragment) {
                $this->_wordFooterT[$key] ='<?xml version="1.0" encoding="UTF-8" standalone="yes" ?>
                                            <w:ftr
                                                xmlns:ve="http://schemas.openxmlformats.org/markup-compatibility/2006"
                                                xmlns:o="urn:schemas-microsoft-com:office:office"
                                                xmlns:r="http://schemas.openxmlformats.org/officeDocument/2006/relationships"
                                                xmlns:m="http://schemas.openxmlformats.org/officeDocument/2006/math"
                                                xmlns:v="urn:schemas-microsoft-com:vml"
                                                xmlns:wp="http://schemas.openxmlformats.org/drawingml/2006/wordprocessingDrawing"
                                                xmlns:w10="urn:schemas-microsoft-com:office:word"
                                                xmlns:w="http://schemas.openxmlformats.org/wordprocessingml/2006/main"
                                                xmlns:wne="http://schemas.microsoft.com/office/word/2006/wordml">';
                $this->_wordFooterT[$key] .= (string) $value;
                $this->_wordFooterT[$key] .= '</w:ftr>';
                $this->_wordFooterT[$key] = preg_replace('/__[A-Z]+__/', '', $this->_wordFooterT[$key]);
                //1.Insert image Rels
                //2.Insert external images rels
                //3.Insert Link rels
                $relationships = '';
                if (isset($this->_relsHeaderFooterImage[$key . 'Footer'])) {
                    foreach($this->_relsHeaderFooterImage[$key . 'Footer'] as $key2 => $value2){
                        $relationships .= '<Relationship Id="' . $value2['rId'] . '" Type="http://schemas.openxmlformats.org/officeDocument/2006/relationships/image" Target="media/img' . $value2['rId'] . '.' . $value2['extension'] .'" />';
                    }
                }
                if (isset($this->_relsHeaderFooterExternalImage[$key . 'Footer'])) {
                    foreach($this->_relsHeaderFooterExternalImage[$key . 'Footer'] as $key2 => $value2){
                        $relationships .= '<Relationship Id="' . $value2['rId'] . '" Type="http://schemas.openxmlformats.org/officeDocument/2006/relationships/image" Target="' . $value2['url'] .'" TargetMode="External" />';
                    }
                }
                if (isset($this->_relsHeaderFooterLink[$key . 'Footer'])) {
                    foreach($this->_relsHeaderFooterLink[$key . 'Footer'] as $key2 => $value2){
                        $relationships .= '<Relationship Id="' . $value2['rId'] . '" Type="http://schemas.openxmlformats.org/officeDocument/2006/relationships/hyperlink" Target="' . $value2['url'] .'" TargetMode="External" />';
                    }
                }
                //Now we create the complete rels file relative to that footer
                if ($relationships != '') {
                    $rels = '<?xml version="1.0" encoding="UTF-8" standalone="yes" ?><Relationships xmlns="http://schemas.openxmlformats.org/package/2006/relationships">';
                    $rels .= $relationships;
                    $rels .= '</Relationships>';
                }
                //4.Include the footer xml files
                $footerHandler = fopen($this->_baseTemplateFilesPath.'/word/'. $key . 'Footer.xml', 'w+');
                fwrite($footerHandler, $this->_wordFooterT[$key]);
                fclose($footerHandler);
                //5.Include the footer rels files
                if (isset($rels)) {
                    $footerRelsHandler = fopen($this->_baseTemplateFilesPath.'/word/_rels/'. $key . 'Footer.xml.rels', 'w+');
                    fwrite($footerRelsHandler, $rels);
                    fclose($footerRelsHandler);
                }
                //6. modify the document.xml.rels file
                $newId = uniqid(true);
                $newFooterNode = '<Relationship Id="rId';
                $newFooterNode .= $newId.'" Type="http://schemas.openxmlformats.org/officeDocument/2006/relationships/footer"';
                $newFooterNode .= ' Target="' . $key . 'Footer.xml" />';
                $newNode = $this->_wordRelsDocumentRelsT->createDocumentFragment();
                $newNode->appendXML($newFooterNode);
                $baseNode =$this->_wordRelsDocumentRelsT->documentElement;
                $baseNode->appendChild($newNode);
                //7. modify accordingly the sectPr node
                $newSectNode = '<w:footerReference w:type="'. $key .'" r:id="rId'.$newId.'" xmlns:w="http://schemas.openxmlformats.org/wordprocessingml/2006/main" xmlns:r="http://schemas.openxmlformats.org/officeDocument/2006/relationships"/>';
                $sectNode = $this->_sectPr->createDocumentFragment();
                $sectNode->appendXML($newSectNode);
                $refNode =$this->_sectPr->documentElement->childNodes->item(0);
                $refNode->parentNode->insertBefore($sectNode, $refNode);
                if ($key == 'first') {
                    $this->generateTitlePg();
                } else if($key == 'even') {
                    $this->generateSetting('w:evenAndOddHeaders');
                }
                //6.generate the corresponding Override element in [Content_Types].xml
                $this->generateOVERRIDE(
                    '/word/' . $key . 'Footer.xml',
                    'application/vnd.openxmlformats-officedocument.wordprocessingml.' .
                    'footer+xml'
                );
                //7.Refresh the _relsFooter array
                $this->_relsFooter[] = $key . 'Footer.xml';
                //8.Refresh the arrays used to hold the image and link data
                $this->_relsHeaderFooterImage[$key . 'Footer'] = array();
                $this->_relsHeaderFooterExternalImage[$key . 'Footer'] = array();
                $this->_relsHeaderFooterLink[$key . 'Footer'] = array();
            } else {
                PhpdocxLogger::logger('The footer contents must be WordML fragments', 'fatal');
            }
        }
    }

    /**
     * Adds a footnote
     *
     * @access public
     * @example ../examples/easy/Footnote.php
     * @example ../examples/intermediate/Chart_footnote.php
     * @example ../examples/intermediate/EndnoteAndFootnote.php
     * @param array $options
     *  Values:
     * 'textDocument'(mixed) a string of text to appear in the document body or an array with the text and associated text options
     * 'textFootnote' (mixed) a string of text to be used as the footnote text or a WordML fragment
     * 'footnoteMark' (array) bidi, customMark, font, b, i, color, rtl
     * 'referenceMark' (array) bidi, font, b, i, color, rtl
     * 'rawWordML' (boolean)
     */
    public function addFootnote($options = array('rawWordML' => false))
    {
        $options['footnoteMark'] = self::setRTLOptions($options['footnoteMark']);
        $options['referenceMark'] = self::setRTLOptions($options['referenceMark']);
        $id = rand(9999,32766);//this number can not be bigger than 32767
        if($options['textFootnote'] instanceof WordMLFragment){
            $footnoteBase ='<w:footnote w:id="'.$id.'"
                xmlns:ve="http://schemas.openxmlformats.org/markup-compatibility/2006"
                xmlns:o="urn:schemas-microsoft-com:office:office"
                xmlns:r="http://schemas.openxmlformats.org/officeDocument/2006/relationships"
                xmlns:m="http://schemas.openxmlformats.org/officeDocument/2006/math"
                xmlns:v="urn:schemas-microsoft-com:vml"
                xmlns:wp="http://schemas.openxmlformats.org/drawingml/2006/wordprocessingDrawing"
                xmlns:w10="urn:schemas-microsoft-com:office:word"
                xmlns:w="http://schemas.openxmlformats.org/wordprocessingml/2006/main"
                xmlns:wne="http://schemas.microsoft.com/office/word/2006/wordml"
                >';
            $footnoteBase .= $this->parseWordMLNote('footnote', $options['textFootnote'], $options['footnoteMark'], $options['referenceMark']);
            $footnoteBase .= '</w:footnote>';
        }else{
            $footnoteBase = '<w:footnote w:id="' . $id . '" xmlns:w="http://schemas.openxmlformats.org/wordprocessingml/2006/main"><w:p>
                <w:pPr><w:pStyle w:val="footnoteTextPHPDOCX"/>';
            if(self::$bidi){
                $footnoteBase .= '<w:bidi />';
            }
            $footnoteBase .= '</w:pPr><w:r><w:rPr><w:rStyle w:val="footnoteReferencePHPDOCX"/>';
            //Parse the referenceMark options
            if(isset($options['referenceMark']['font'])){
              $footnoteBase .=  '<w:rFonts w:ascii="' . $options['referenceMark']['font'] .
                                '" w:hAnsi="' . $options['referenceMark']['font'] .
                                '" w:cs="' . $options['referenceMark']['font'] . '"/>';
            }
            if(isset($options['referenceMark']['b'])){
              $footnoteBase .=  '<w:b w:val="' . $options['referenceMark']['b'] . '"/>';
            }
            if(isset($options['referenceMark']['i'])){
              $footnoteBase .=  '<w:i w:val="' . $options['referenceMark']['i'] . '"/>';
            }
            if(isset($options['referenceMark']['color'])){
              $footnoteBase .=  '<w:color w:val="' . $options['referenceMark']['color'] . '"/>';
            }
            if(isset($options['referenceMark']['sz'])){
              $footnoteBase .=  '<w:sz w:val="' . (2 * $options['referenceMark']['sz']) . '"/>';
              $footnoteBase .=  '<w:szCs w:val="' . (2 * $options['referenceMark']['sz']) . '"/>';
            }
            if(isset($options['referenceMark']['rtl']) && $options['referenceMark']['rtl']){
                $footnoteBase .= '<w:rtl />';
            }
            $footnoteBase .= '</w:rPr>';
            if(isset($options['footnoteMark']['customMark'])){
                $footnoteBase .= '<w:t>' . $options['footnoteMark']['customMark'] . '</w:t>';
            }else{
                $footnoteBase .= '<w:footnoteRef/>';
            }
            $footnoteBase .= '</w:r>';
            if(self::$rtl){
                $footnoteBase .= '<w:rPr><w:rtl /></w:rPr>';
            }
            $footnoteBase .= '<w:r><w:t xml:space="preserve">' . $options['textFootnote'] . '</w:t></w:r></w:p>
                </w:footnote>';
        }
        if(!is_array($options['textDocument'])){
           $options['textDocument'] = array('text' => $options['textDocument']);
        }
        $textOptions = $options['textDocument'];
        $textOptions['rawWordML'] = true;
        $text = $textOptions['text'];
        $textOptions = self::setRTLOptions($textOptions);
        $footnoteDocument = $this->addText($text, $textOptions);
        $footnoteMark = '<w:r><w:rPr><w:rStyle w:val="footnoteReferencePHPDOCX" />';
        //Parse the footnoteMark options
        if(isset($options['footnoteMark']['font'])){
          $footnoteMark .=  '<w:rFonts w:ascii="' . $options['footnoteMark']['font'] .
                            '" w:hAnsi="' . $options['footnoteMark']['font'] .
                            '" w:cs="' . $options['footnoteMark']['font'] . '"/>';
        }
        if(isset($options['footnoteMark']['b'])){
          $footnoteMark .=  '<w:b w:val="' . $options['footnoteMark']['b'] . '"/>';
        }
        if(isset($options['footnoteMark']['i'])){
          $footnoteMark .=  '<w:i w:val="' . $options['footnoteMark']['i'] . '"/>';
        }
        if(isset($options['footnoteMark']['color'])){
          $footnoteMark .=  '<w:color w:val="' . $options['footnoteMark']['color'] . '"/>';
        }
        if(isset($options['footnoteMark']['sz'])){
          $footnoteMark .=  '<w:sz w:val="' . (2 * $options['footnoteMark']['sz']) . '"/>';
          $footnoteMark .=  '<w:szCs w:val="' . (2 * $options['footnoteMark']['sz']) . '"/>';
        }
        if(isset($options['footnoteMark']['rtl']) && $options['footnoteMark']['rtl']){
                $footnoteMark .= '<w:rtl />';
        }
        $footnoteMark .= '</w:rPr><w:footnoteReference w:id="'.$id.'" ';
        if(isset($options['footnoteMark']['customMark'])){
            $footnoteMark .= 'w:customMarkFollows="1"/><w:t>' . $options['footnoteMark']['customMark'] . '</w:t>';
        }else{
            $footnoteMark .= '/>';
        }
        $footnoteMark .= '</w:r></w:p>';
        $footnoteDocument = str_replace('</w:p>', $footnoteMark, $footnoteDocument);
        //Clean the footnoteDocument from auxilairy variable
        $footnoteDocument = preg_replace('/__[A-Z]+__/', '', $footnoteDocument);

        //We now try to open the zip file defined as base template

        $filename = $this->_baseTemplateFilesPath.'/word/footnotes.xml';
        $handle = fopen($filename, "r");
        $contents = fread($handle, 999999);
        fclose($handle);


        $this->_wordFootnotesT = new DOMDocument();
        $this->_wordFootnotesT->loadXML($contents);
        $tempNode = $this->_wordFootnotesT->createDocumentFragment();
        $tempNode->appendXML($footnoteBase);
        $this->_wordFootnotesT->documentElement->appendChild($tempNode);

        //We copy the  content into the respective file
        $footnoteHandler = fopen($this->_baseTemplateFilesPath.'/word/footnotes.xml', "w+");
        fwrite($footnoteHandler, $this->_wordFootnotesT->saveXML());
        fclose($footnoteHandler);

        PhpdocxLogger::logger('Add footnote to word document.', 'info');

        if(isset($options['rawWordML']) && $options['rawWordML']){
            return (string) $footnoteDocument;
        }else{
            $this->_wordDocumentC .= (string) $footnoteDocument;
        }
    }

    /**
     * Add a Form element (text field, select or checkbox)
     *
     * @access public
     * @example ../examples/easy/FormElements.php
     * @param mixed $type it can be 'textfield', 'checkbox' or 'select'
     * @param array $options Style options to apply to the text
     *  Values:
     * 'b' (on, off)
     * 'color' (ffffff, ff0000...)
     * 'font' (Arial, Times New Roman...)
     * 'i' (on, off)
     * 'jc' (both, center, distribute, left, right)
     * 'lineBreak' (before, after, both)
     * 'columnBreak' (before, after, both)
     * 'pageBreakBefore' (on, off)
     * 'sz' (1, 2, 3...)
     * 'u' (dash, dotted, double, single, wave, words)
     * 'widowControl' (on, off)
     * 'wordWrap' (on, off)
     * 'lineSpacing' 120, 240 (standard), 480...,
     * 'indent_left' 100...,
     * 'indent_right' 100...
     * 'rawWordML' (boolean)
     * 'defaultValue' (mixed) a string of text for the textfield type,
     * a boolean value for the checkbox type or an integer representing the index (0 based)
     * for the options of a select form element
     * 'selectOptions' (array) an array of options for the dropdown menu
     */
    public function addFormElement($type, $options = array('rawWordML' => false))
    {
        $options = self::setRTLOptions($options);
        $formElementTypes = array('textfield', 'checkbox', 'select');
        if(!in_array($type, $formElementTypes)){
            PhpdocxLogger::logger('The chosen form element type is not available', 'fatal');
        }
        $formElementBase = CreateText::getInstance();
        $ParagraphOptions = $options;
        $ParagraphOptions['rawWordML'] = true;
        $formElementBase->createText(array(array('text' => '__formElement__')), $ParagraphOptions);
        $formElement = CreateFormElement::getInstance();
        $formElement->createFormElement($type, $options, (string)$formElementBase);
        PhpdocxLogger::logger('Add form element to Word document.', 'info');
        if(isset($options['rawWordML']) && $options['rawWordML']){
            return (string) $formElement;
        }else{
            $this->_wordDocumentC .= (string) $formElement;
        }
    }

    /**
     * Add a graphic
     *
     * @access public
     * @example ../examples/easy/Chart.php
     * @example ../examples/easy/Chart_bar.php
     * @example ../examples/intermediate/Chart.php
     * @example ../examples/intermediate/Chart_footnote.php
     * @example ../examples/intermediate/Multidocument.php
     * @example ../examples/advanced/Report.php
     * @param array $dats Parameters of graphic
     *  Values: 'color' (1, 2, 3...), 'perspective' (20, 30...),
     *  'rotX' (20, 30...), 'rotY' (20, 30...), 'data' (array of values),
     *  'font' (Arial, Times New Roman...), 'groupBar' (clustered, stacked),
     *  'jc' (center, left, right), 'showPercent' (0, 1), 'sizeX' (10, 11,
     *   12...), 'sizeY' (10, 11, 12...), 'textWrap' (0 (inline), 1 (square),
     *  2 (front), 3 (back), 4 (up and bottom), 5 (clear)), 'title', 'type'
     *  (barChart, bar3DChart, colChart, col3DChart, pieChart, pie3DChart)
     * @deprecated Use addChart method
     * @see addChart
     */
    public function addGraphic($dats)
    {
        PhpdocxLogger::logger('Create chart.', 'debug');
        try {
            if (isset($dats['data']) && isset($dats['type'])) {
                self::$intIdWord++;
                PhpdocxLogger::logger('New ID ' . self::$intIdWord . ' . Chart.', 'debug');
                $graphic = CreateGraphic::getInstance();
                if ($graphic->createGraphic(self::$intIdWord, $dats) != false) {
                    PhpdocxLogger::logger('Add chart word/charts/chart' . self::$intIdWord .
                        '.xml to DOCX.', 'info');
                    $this->_zipDocx->addFromString(
                        'word/charts/chart' . self::$intIdWord . '.xml',
                        $graphic->getXmlChart()
                    );
                    $this->_wordRelsDocumentRelsC .=
                        $this->generateRELATIONSHIP(
                            'rId' . self::$intIdWord, 'chart',
                            'charts/chart' . self::$intIdWord . '.xml'
                        );
                    $this->_wordDocumentC .= (string) $graphic;
                    $this->generateDEFAULT('xlsx', 'application/octet-stream');
                    $this->generateOVERRIDE(
                        '/word/charts/chart' . self::$intIdWord . '.xml',
                        'application/vnd.openxmlformats-officedocument.' .
                        'drawingml.chart+xml'
                    );
                } else {
                    throw new Exception(
                        'There was an error related to the chart.'
                    );
                }
                $excel = CreateXlsx::getInstance();
                $this->_tempFileXLSX[self::$intIdWord] =
                    tempnam($this->_tempDir, 'documentxlsx');
                if (
                    $excel->createXlsx(
                        $this->_tempFileXLSX[self::$intIdWord],
                        $dats['data'], $dats['type']
                    ) != false
                ) {
                    $this->_zipDocx->addFile(
                        $this->_tempFileXLSX[self::$intIdWord],
                        'word/embeddings/datos' . self::$intIdWord . '.xlsx'
                    );

                    $chartRels = CreateChartRels::getInstance();
                    $chartRels->createRelationship(self::$intIdWord);
                    $this->_zipDocx->addFromString(
                        'word/charts/_rels/chart' . self::$intIdWord .
                        '.xml.rels',
                        (string) $chartRels
                    );
                }
            } else {
                throw new Exception(
                    'Images must have "data" and "type" values.'
                );
            }
        }
        catch (Exception $e) {
            PhpdocxLogger::logger($e->getMessage(), 'fatal');
        }
    }

    /**
     * Add a graphic image
     *
     * @access public
     * @param array $options
     * Values:
     * 'color' (1, 2, 3, 4, 5),
     * 'rotX' (20, 30...),
     * 'data' (array of values),
     * 'sizeX' (10, 11, 12...),
     * 'sizeY' (10, 11, 12...),
     * 'title',
     * 'type' (barChart, bar3DChart,colChart, col3DChart, pieChart, pie3DChart)
     * 'rawWordML' (boolean)
     */
    public function addGraphicImg($options = array('rawWordML' => false))
    {
        PhpdocxLogger::logger('Create image chart.', 'debug');
        try {
            if (isset($options['data']) && isset($options['type'])) {
                $graphic = CreateGraphicImg::getInstance();
                if ($graphic->createGraphicImg($options)) {

                }
                else {
                    throw new Exception(
                        'Unsupported chart type.'
                    );
                }
            } else {
                throw new Exception(
                    'Images must have "data" and "type" values.'
                );
            }
        }
        catch (Exception $e) {
            PhpdocxLogger::logger($e->getMessage(), 'fatal');
        }
    }

    /**
     * Add a graphic template. Replace placeholder with a graphic
     *
     * @access public
     * @param array $options
     * Values: same as charts
     */
    public function addGraphicTemplate($options)
    {
        try {
            if (isset($options['data']) && isset($options['type'])) {
                self::$intIdWord++;
                PhpdocxLogger::logger('New ID ' . self::$intIdWord . ' . Image template.', 'debug');
                $type = $options['type'];
                if(strpos($type, 'Chart') === false)
                    $type .= 'Chart';
                $graphic = CreateChartFactory::createObject($type);

                if ($graphic->createGraphic(self::$intIdWord, $options) != false) {
                    $this->graphicTemplate['arrChartXML'][self::$intIdWord] =
                        $graphic->getXmlChart();
                    $this->graphicTemplate['arrRelationships'][self::$intIdWord] =
                        $this->generateRELATIONSHIPTemplate(
                            'rId' . self::$intIdWord, 'chart',
                            'charts/chart' . self::$intIdWord . '.xml'
                        );
                    $this->graphicTemplate['arrGraphics'][self::$intIdWord] =
                        (string) $graphic;
                    $this->graphicTemplate['arrGenerateDEFAULT'][self::$intIdWord] =
                        '<Default Extension="' . 'xlsx' . '" ContentType="' .
                        'application/octet-stream' . '"> </Default>';
                    $this->graphicTemplate['arrGenerateOVERRIDE'][self::$intIdWord] =
                        '<Override PartName="' . '/word/charts/chart' .
                        self::$intIdWord . '.xml' . '" ContentType="' .
                        'application/vnd.openxmlformats-officedocument.' .
                        'drawingml.chart+xml' . '"> </Override>';
                } else {
                    throw new Exception(
                        'There was an error related to the chart.'
                    );
                }
                $excel = $graphic->getXlsxType();

                $this->_tempFileXLSX[self::$intIdWord] = tempnam($this->_tempDir, 'documentxlsx');
                if (
                    $excel->createXlsx(
                        $this->_tempFileXLSX[self::$intIdWord], $options['data'],
                        $options['type']
                    ) != false
                ) {
                    $this->fileGraphicTemplate['datos' . self::$intIdWord . '.xlsx'] =
                        'word/embeddings/datos' . self::$intIdWord . '.xlsx';

                    $objChartRels = CreateChartRels::getInstance();
                    $objChartRels->createRelationship(self::$intIdWord);
                    $this->fileGraphicTemplate['word/charts/_rels/chart' . self::$intIdWord . '.xml.rels'] =
                        (string) $objChartRels;
                }
            } else {
                throw new Exception(
                    'Charts must have "data" and "type" values.
                ');
            }
        }
        catch (Exception $e) {
            PhpdocxLogger::logger($e->getMessage(), 'fatal');
        }
    }

    /**
     * Add a header.
     *
     * @access public
     * @example ../examples/easy/Header.php
     * @example ../examples/intermediate/HeaderAndFooter.php
     * @example ../examples/advanced/Report.php
     * @param array $headers
     *  Values:
     * 'default'(object) WordMLFragment
     * 'even' (object) WordMLFragment
     * 'first' (object) WordMLFragment
     */
    public function addHeader($headers)
    {
        $this->headerAdded = true;
        $this->removeHeaders();
        foreach($headers as $key => $value){
            if ($value instanceof WordMLFragment){
                $this->_wordHeaderT[$key] ='<?xml version="1.0" encoding="UTF-8" standalone="yes" ?>
                                            <w:hdr
                                                xmlns:ve="http://schemas.openxmlformats.org/markup-compatibility/2006"
                                                xmlns:o="urn:schemas-microsoft-com:office:office"
                                                xmlns:r="http://schemas.openxmlformats.org/officeDocument/2006/relationships"
                                                xmlns:m="http://schemas.openxmlformats.org/officeDocument/2006/math"
                                                xmlns:v="urn:schemas-microsoft-com:vml"
                                                xmlns:wp="http://schemas.openxmlformats.org/drawingml/2006/wordprocessingDrawing"
                                                xmlns:w10="urn:schemas-microsoft-com:office:word"
                                                xmlns:w="http://schemas.openxmlformats.org/wordprocessingml/2006/main"
                                                xmlns:wne="http://schemas.microsoft.com/office/word/2006/wordml">';
                $this->_wordHeaderT[$key] .= (string) $value;
                $this->_wordHeaderT[$key] .= '</w:hdr>';
                $this->_wordHeaderT[$key] = preg_replace('/__[A-Z]+__/', '', $this->_wordHeaderT[$key]);
                //1.Insert image Rels
                //2.Insert external images rels
                //3.Insert Link rels
                $relationships = '';
                if (isset($this->_relsHeaderFooterImage[$key . 'Header'])) {
                    foreach ($this->_relsHeaderFooterImage[$key . 'Header'] as $key2 => $value2) {
                        $relationships .= '<Relationship Id="' . $value2['rId'] . '" Type="http://schemas.openxmlformats.org/officeDocument/2006/relationships/image" Target="media/img' . $value2['rId'] . '.' . $value2['extension'] .'" />';
                    }
                }
                if (isset($this->_relsHeaderFooterExternalImage[$key . 'Header'])) {
                    foreach ($this->_relsHeaderFooterExternalImage[$key . 'Header'] as $key2 => $value2) {
                        $relationships .= '<Relationship Id="' . $value2['rId'] . '" Type="http://schemas.openxmlformats.org/officeDocument/2006/relationships/image" Target="' . $value2['url'] .'" TargetMode="External" />';
                    }
                }
                if (isset($this->_relsHeaderFooterLink[$key . 'Header'])) {
                    foreach ($this->_relsHeaderFooterLink[$key . 'Header'] as $key2 => $value2) {
                        $relationships .= '<Relationship Id="' . $value2['rId'] . '" Type="http://schemas.openxmlformats.org/officeDocument/2006/relationships/hyperlink" Target="' . $value2['url'] .'" TargetMode="External" />';
                    }
                }
                //Now we create the complete rels file relative to that header
                if ($relationships != '') {
                    $rels = '<?xml version="1.0" encoding="UTF-8" standalone="yes" ?><Relationships xmlns="http://schemas.openxmlformats.org/package/2006/relationships">';
                    $rels .= $relationships;
                    $rels .= '</Relationships>';
                }
                //4.Include the header xml files
                $headerHandler = fopen($this->_baseTemplateFilesPath.'/word/'. $key . 'Header.xml', 'w+');
                fwrite($headerHandler, $this->_wordHeaderT[$key]);
                fclose($headerHandler);
                //5.Include the header rels files
                if (isset($rels)) {
                    $headerRelsHandler = fopen($this->_baseTemplateFilesPath.'/word/_rels/'. $key . 'Header.xml.rels', 'w+');
                    fwrite($headerRelsHandler, $rels);
                    fclose($headerRelsHandler);
                }
                //6. modify the document.xml.rels file
                $newId = uniqid(true);
                $newHeaderNode = '<Relationship Id="rId';
                $newHeaderNode .= $newId.'" Type="http://schemas.openxmlformats.org/officeDocument/2006/relationships/header"';
                $newHeaderNode .= ' Target="' . $key . 'Header.xml" />';
                $newNode = $this->_wordRelsDocumentRelsT->createDocumentFragment();
                $newNode->appendXML($newHeaderNode);
                $baseNode =$this->_wordRelsDocumentRelsT->documentElement;
                $baseNode->appendChild($newNode);
                //7. modify accordingly the sectPr node
                $newSectNode = '<w:headerReference w:type="'. $key .'" r:id="rId'.$newId.'" xmlns:w="http://schemas.openxmlformats.org/wordprocessingml/2006/main" xmlns:r="http://schemas.openxmlformats.org/officeDocument/2006/relationships"/>';
                $sectNode = $this->_sectPr->createDocumentFragment();
                $sectNode->appendXML($newSectNode);
                $refNode =$this->_sectPr->documentElement->childNodes->item(0);
                $refNode->parentNode->insertBefore($sectNode, $refNode);
                if ($key == 'first') {
                    $this->generateTitlePg();
                } else if($key == 'even') {
                    $this->generateSetting('w:evenAndOddHeaders');
                }
                //6.generate the corresponding Override element in [Content_Types].xml
                $this->generateOVERRIDE(
                    '/word/' . $key . 'Header.xml',
                    'application/vnd.openxmlformats-officedocument.wordprocessingml.' .
                    'header+xml'
                );
                //7.Refresh the _relsHeader array
                $this->_relsHeader[] = $key . 'Header.xml';
                //8.Refresh the arrays used to hold the image and link data
                $this->_relsHeaderFooterImage[$key . 'Header'] = array();
                $this->_relsHeaderFooterExternalImage[$key . 'Header'] = array();
                $this->_relsHeaderFooterLink[$key . 'Header'] = array();
            } else {
               PhpdocxLogger::logger('The header contents must be WordML fragments', 'fatal');
            }
        }
    }

    /**
     * Adds a heading to the Word document
     *
     * @access public
     * @example ../examples/easy/Heading.php
     * @param string $text the heading text
     * @param int $level can be 1 (default), 2,3, ...
     * @param array $options Style options to apply to the heading
     *  Values:
     * 'bidi' (on, off)
     * 'b' (on, off)
     * 'caps' (on, off) display text in capital letters
     * 'color' (ffffff, ff0000...)
     * 'font' (Cambria (default), Arial, Times New Roman...)
     * 'i' (on, off)
     * 'indent_left' 100...,
     * 'indent_right' 100...
     * 'jc' (both, center, distribute, left, right)
     * 'keepLines' (on, off) keep all paragraph lines on the same page
     * 'keepNext' (on, off) keep in the same page the current paragraph with next paragraph
     * 'lineSpacing' 120, 240 (standard), 360, 480, ...
     * 'pageBreakBefore' (on, off)
     * 'rawWordML' (boolean)
     * 'rtl' (on, off)
     * 'spacingBottom' (int) bottom margin in twentieths of a point
     * 'spacingTop' (int) top margin in twentieths of a point
     * 'sz' (8, 9, 10, ...) size in points
     * 'u' (none, dash, dotted, double, single, wave, words)
     * 'widowControl' (on, off)
     * 'wordWrap' (on, off)
     */
    public function addHeading($text, $level = 1, $options = array('rawWordML' => false))
    {
        $options = self::setRTLOptions($options);
        if(!isset($options['b'])){
            $options['b'] = 'on';
        }
        if(!isset($options['keepLines'])){
            $options['keepLines'] = 'on';
        }
        if(!isset($options['keepNext'])){
            $options['keepNext'] = 'on';
        }
        if(!isset($options['widowControl'])){
            $options['widowControl'] = 'on';
        }
        if(!isset($options['sz'])){
            $options['sz'] = max(15 - $level, 10);
        }
        if(!isset($options['font'])){
            $options['font'] = 'Cambria';
        }
        if(!isset($options['rawWordML'])){
            $options['rawWordML'] = false;
        }

        $options['headingLevel'] = $level;
        $heading = CreateText::getInstance();
        $heading->createText($text, $options);
        PhpdocxLogger::logger('Adds a heading of level ' . $level . 'to the Word document.', 'info');
        if (isset($options['rawWordML']) && $options['rawWordML']) {
            return (string) $heading;
        } else {
            $this->_wordDocumentC .= (string) $heading;
        }
    }

    /**
     * Inserts HTML into a document as alternative content (altChunk).
     * This method IS NOT compatible with PDF conversion or Open Office (use embedHTML instead).
     *
     * @access public
     * @example ../examples/easy/HTML.php
     * @example ../examples/intermediate/BasicHTML.php
     * @example ../examples/intermediate/HTML.php
     * @param array $options
     * Values:
     * 'html' (string)
     * 'rawWordML' (boolean)
     */
    public function addHTML($options = array('html' => '', 'rawWordML' => false))
    {
        try {
            if ($this->_compatibilityMode) {
                throw new Exception('Running in compatibility mode. Unsupported method.');
            }
            $wordHTML = EmbedHTML::getInstance();
            $wordHTML->embed();
            PhpdocxLogger::logger('Embed HTML to word document.', 'info');
            $this->_zipDocx->addFromString('word/html' . $wordHTML->getId() .
                                           '.htm', '<html>' . $options['html'] . '</html>');
            $this->_wordRelsDocumentRelsC .= $this->generateRELATIONSHIP(
                'rHTMLId' . $wordHTML->getId(), 'aFChunk', 'html' .
                                                           $wordHTML->getId() . '.htm', 'TargetMode="Internal"');
            $this->generateDEFAULT('htm', 'application/xhtml+xml');
            if (isset($options['rawWordML']) && $options['rawWordML']) {
                return (string)$wordHTML . '<w:p/>';
            } else {
                $this->_wordDocumentC .= (string)$wordHTML;
            }
        } catch (Exception $e) {
            PhpdocxLogger::logger($e->getMessage(), 'fatal');
        }
    }

    /**
     * Add an image
     *
     * @access public
     * @example ../examples/easy/Image.php
     * @example ../examples/intermediate/Chart_footnote.php
     * @param array $data
     * Values:
     * 'border'(int) 1, 2, 3...
     * 'borderDiscontinuous' (0, 1)
     * 'float' (left, right, center) floating image. It only applies if textWrap is not inline (default value).
     * 'font' (string) Arial, Times New Roman...
     * 'horizontalOffset' (int) given in emus (1cm = 360000 emus). Only applies if there is the image is not floating
     * 'jc' (center, left, right, inside, outside)
     * 'name' (string) path to a local image
     * 'scaling' (int) 50, 100, ..
     * 'sizeX' (int) 10, 11, 12...
     * 'sizeY' (int) 10, 11, 12...
     * 'dpi' (int) dots per inch
     * 'spacingTop' (int) 10, 11...
     * 'spacingBottom' (int) 10, 11...
     * 'spacingLeft' (int) 10, 11...
     * 'spacingRight' (int) 10, 11...
     * 'textWrap' 0 (inline), 1 (square), 2 (front), 3 (back), 4 (up and bottom))
     * 'target' (string): document (default value), defaultHeader, firstHeader, evenHeader, defaultFooter, firstFooter, evenFooter, footnote, endnote, comment
     * 'verticalOffset' (int) given in emus (1cm = 360000 emus)
     * 'rawWordML' (boolean)
     */
    public function addImage($data = '')
    {
        if(!isset($data['target'])){
           $data['target'] = 'document';
        }
        PhpdocxLogger::logger('Create image.', 'debug');
        try {
            if (isset($data['name']) && file_exists($data['name']) == 'true') {
                $attrImage = getimagesize($data['name']);
                try {
                    if ($attrImage['mime'] == 'image/jpg' ||
                        $attrImage['mime'] == 'image/jpeg' ||
                        $attrImage['mime'] == 'image/png' ||
                        $attrImage['mime'] == 'image/gif'
                    ) {
                        self::$intIdWord++;
                        PhpdocxLogger::logger('New ID rId' . self::$intIdWord . ' . Image.', 'debug');
                        $image = CreateImage::getInstance();
                        $data['rId'] = self::$intIdWord;
                        $image->createImage($data);
                        $dir = $this->parsePath($data['name']);
                        PhpdocxLogger::logger('Add image word/media/imgrId' .
                            self::$intIdWord . '.' . $dir['extension'] .
                            '.xml to DOCX.', 'info');
                        $this->_zipDocx->addFile(
                            $data['name'], 'word/media/imgrId' .
                            self::$intIdWord . '.' .
                            $dir['extension']
                        );
                        $this->generateDEFAULT(
                            $dir['extension'], $attrImage['mime']
                        );
                        if ((string) $image != ''){
                            //Here we consider the case where the image will be included in a header or footer
                            if($data['target'] == 'defaultHeader' ||
                               $data['target'] == 'firstHeader' ||
                               $data['target'] == 'evenHeader' ||
                               $data['target'] == 'defaultFooter' ||
                               $data['target'] == 'firstFooter' ||
                               $data['target'] == 'evenFooter'){
                                $this->_relsHeaderFooterImage[$data['target']][] =
                                array('rId' => 'rId' . self::$intIdWord, 'extension' => $dir['extension']);
                            }else if($data['target'] == 'footnote' ||
                                     $data['target'] == 'endnote' ||
                                    $data['target'] == 'comment'){
                                $this->_relsNotesImage[$data['target']][] =
                                array('rId' => 'rId' . self::$intIdWord, 'extension' => $dir['extension']);
                            }else{
                                $this->_wordRelsDocumentRelsC .=
                                    $this->generateRELATIONSHIP(
                                        'rId' . self::$intIdWord, 'image',
                                        'media/imgrId' . self::$intIdWord . '.'
                                        . $dir['extension']
                                    );
                            }
                        }
                        if(isset($data['rawWordML']) && $data['rawWordML']){
                           return (string) $image;
                        }else{
                           $this->_wordDocumentC .= (string) $image;
                        }
                    } else {
                        throw new Exception('Image format is not supported.');
                    }
                }
                catch (Exception $e) {
                    PhpdocxLogger::logger($e->getMessage(), 'fatal');
                }
            } else {
                throw new Exception('Image does not exist.');
            }
        }
        catch (Exception $e) {
            PhpdocxLogger::logger($e->getMessage(), 'fatal');
        }
    }

    /**
     * Adds line numbering
     *
     * @access public
     * @example ../examples/easy/LineNumbering.php
     * @param array $options
     * countBy (int) line number increments to display (default value is 1)
     * start (int) initial line number (default value is 1)
     * distance (int) separation in twentieths of a point between the number and the text (defaults to auto)
     * restart (string) could be:
     *      continuous (default value: the numbering does not get restarted anywhere in the document),
     *      newPage (the numbering restarts at the beginning of every page)
     *      newSection (the numbering restarts at the beginning of every section)
     */
    public function addLineNumbering($options = array())
    {
        //Restart condition available types
        $restart_types = array('continuous', 'newPage', 'newSection');
        //Set defaults
        if(isset($options['countBy']) && is_int($options['countBy'])){
            $increment = $options['countBy'];
        }else{
            $increment = 1;
        }
        if(isset($options['start']) && is_int($options['start'])){
            $start = $options['start'];
        }else{
            $start = 0;
        }
        if(isset($options['distance']) && is_int($options['distance'])){
            $distance = $options['distance'];
        }
        if(isset($options['restart']) && in_array($options['restart'], $restart_types)){
            $condition = $options['restart'];
        }else{
            $condition = 'continuous';
        }
        //Modify existing line numberings if there were any
        if ($this->_sectPr->getElementsByTagName('lnNumType')->length > 0) {
            $this->_sectPr->getElementsByTagName('lnNumType')->item(0)->setAttribute('w:countBy', $increment);
            $this->_sectPr->getElementsByTagName('lnNumType')->item(0)->setAttribute('w:start', $start);
            $this->_sectPr->getElementsByTagName('lnNumType')->item(0)->setAttribute('w:distance', $distance);
            $this->_sectPr->getElementsByTagName('lnNumType')->item(0)->setAttribute('w:restart', $condition);
        } else {//otherwise create it
            $lnNumNode = $this->_sectPr->createDocumentFragment();
            $strNode ='<w:lnNumType w:countBy="'. $increment.'" w:start="'. $start .'" ';
            if(isset($distance)){
            $strNode .= 'w:distance="'. $distance . '" ';
            }
            $strNode .='w:restart="'. $condition .
                      '" xmlns:w="http://schemas.openxmlformats.org/wordprocessingml/2006/main" />';
            $lnNumNode->appendXML($strNode);

            $propIndex = array_search('w:lnNumType', self::$sectionProperties);
            $childNodes = $this->_sectPr->documentElement->childNodes;
            $index = false;
            foreach($childNodes as $node){
                $name = $node->nodeName;
                $index = array_search($node->nodeName, self::$sectionProperties);
                if($index > $propIndex){
                    $node->parentNode->insertBefore($lnNumNode, $node);
                    break;
                }
            }
            //in case no node was found (pretty unlikely) we should append the node
            if (!$index) {
                $this->_sectPr->documentElement->appendChild($lnNumNode);
            }

        }

    }

    /**
     * Add a link
     *
     * @access public
     * @example ../examples/easy/Link.php
     * @example ../examples/advanced/Report.php
     * @param array $options
     * @see addText
     * additional parameter:
     * 'url' (string) URL or #bookmarkName
     *
     */
    public function addLink($text, $options = array('url' => '',
                                                    'font' => '',
                                                    'sz' => '',
                                                    'color' => '0000ff',
                                                    'u' => 'single',
                                                    'rawWordML' => false))
    {
        $options = self::setRTLOptions($options);
        if(substr($options['url'], 0, 1) == '#'){
            $url = 'HYPERLINK \l "' . substr($options['url'], 1) . '"';
        }else{
            $url = 'HYPERLINK "' . $options['url'] . '"';
        }
        if ($text == '') {
            PhpdocxLogger::logger('The linked text is missing', 'fatal');
        } else if($options['url'] == '') {
            PhpdocxLogger::logger('The URL is missing', 'fatal');
        }
        if (isset($options['color'])) {
            $color = $options['color'];
        } else {
            $color = '0000ff';
        }
        if (isset($options['u'])) {
            $u = $options['u'];
        } else {
            $u = 'single';
        }
        $textOptions = $options;
        $textOptions['rawWordML'] = true;
        $link = $this->addText($text, $textOptions);
        $link = preg_replace('/__[A-Z]+__/', '', $link);
        $startNodes ='<w:r><w:fldChar w:fldCharType="begin" /></w:r><w:r>
        <w:instrText xml:space="preserve">'.$url.'</w:instrText>
        </w:r><w:r><w:fldChar w:fldCharType="separate" /></w:r>';
        if(strstr($link, '</w:pPr>')){
            $link = preg_replace('/<\/w:pPr>/', '</w:pPr>'.$startNodes, $link);
        }else{
            $link = preg_replace('/<w:p>/', '<w:p>'.$startNodes, $link);
        }
        $endNode = '<w:r><w:fldChar w:fldCharType="end" /></w:r>';
        $link = preg_replace('/<\/w:p>/', $endNode . '</w:p>', $link);
        PhpdocxLogger::logger('Add link to word document.', 'info');
        if (isset($options['rawWordML']) && $options['rawWordML']) {
            return (string) $link;
        } else {
            $this->_wordDocumentC .= (string) $link;
        }
    }

    /**
     * Add a list
     *
     * @access public
     * @example ../examples/easy/List.php
     * @example ../examples/intermediate/List.php
     * @example ../examples/intermediate/List_nested.php
     * @example ../examples/intermediate/Multidocument.php
     * @param array $data Values of the list
     * @param array $options
     *  Values:
     * 'font' (string), Arial, Times New Roman, ...
     * 'val' (mixed), 0 (clear), 1 (inordinate), 2(numerical) or the name of the created list
     * 'rawWordML' (boolean)
     */
    public function addList($data, $options = array('rawWordML' => false))
    {
        $list = CreateList::getInstance();

        if ($options['val'] == 2){
            self::$numOL++;
            $this->_wordNumberingT = $this->importSingleNumbering($this->_wordNumberingT, self::$orderedListStyle, self::$numOL);
        }
        if (is_string($options['val'])){
            $options['val'] = self::$customLists[$options['val']]['id'];
        }
        $list->createList($data, $options);
        PhpdocxLogger::logger('Add list to word document.', 'info');
        if (isset($options['rawWordML']) && $options['rawWordML']) {
            return (string) $list;
        } else {
            $this->_wordDocumentC .= (string) $list;
        }
    }

    /**
     * Add a macro from a DOC
     *
     * @access public
     * @param string $path Path to a file with macro
     */
    public function addMacroFromDoc($path)
    {
        if (!$this->_docm) {
            PhpdocxLogger::logger('The base template should be a docm to include a macro in your document', 'fatal');
            exit();
        } else if(!file_exists($this->_baseTemplateFilesPath.'/word/vbaData.xml')) {
            PhpdocxLogger::logger('The base template should be a docm and it should include at list a macro', 'fatal');
        }
        $package = new ZipArchive();
        PhpdocxLogger::logger('Open document with a macro.', 'info');
        PhpdocxLogger::logger('Add macro files to DOCX file.', 'info');
        //We copy the contents of vbaData
        $vbaDataHandler = fopen($this->_baseTemplateFilesPath.'/word/vbaData.xml', "w+");
        fwrite($vbaDataHandler, $package->getFromName('word/vbaData.xml'));
        fclose($vbaDataHandler);
        //We copy the contents of vbaProject
        $vbaProjectHandler = fopen($this->_baseTemplateFilesPath.'/word/vbaProject.bin', "w+");
        fwrite($vbaProjectHandler, $package->getFromName('word/vbaProject.bin'));
        fclose($vbaProjectHandler);

        $package->close();
    }

    /**
     * Convert a math eq to DOCX
     *
     * @access public
     * @example ../examples/easy/Math.php
     * @param string $path Path to a file with math eq
     */
    public function addMathDocx($path)
    {
        $package = new ZipArchive();
        PhpdocxLogger::logger('Open document with an existing math eq.', 'info');
        $package->open($path);
        $document = $package->getFromName('word/document.xml');
        $eqs = preg_split('/<[\/]*m:oMathPara>/', $document);
        PhpdocxLogger::logger('Add math eq to word document.', 'info');
        $this->addMathEq('<m:oMathPara>' . $eqs[1] . '</m:oMathPara>');
        $package->close();
    }

    /**
     * Add an existing math eq to DOCX
     *
     * @access public
     * @example ../examples/easy/Math.php
     * @param string $eq Math eq
     * @param bool $rawWordML
     */
    public function addMathEq($eq, $rawWordML = false)
    {
        PhpdocxLogger::logger('Add existing math eq to word document.', 'info');
        if($rawWordML){
            return $eq;
        }else{$this->_wordDocumentC .= '<' . CreateDocx::NAMESPACEWORD . ':p>' .
            (string) $eq . '</' . CreateDocx::NAMESPACEWORD . ':p>';
        }
    }

    /**
     * Convert a math MML eq to DOCX
     *
     * @access public
     * @param string $eq Math eq
     * @param bool $rawWordML
     */
    public function addMathMML($eq, $rawWordML = false)
    {
        $math = CreateMath::getInstance();
        PhpdocxLogger::logger('Convert MathMML eq.', 'debug');
        $math->createMath($eq);
        PhpdocxLogger::logger('Add converted MathMML eq to word document.', 'info');
        $equation = $this->addMathEq('<m:oMathPara>' . (string) $math . '</m:oMathPara>', $rawWordML);
        if($rawWordML){
            return $equation;
        }
    }

    /**
     * Adds a merge field to the Word document
     *
     * @access public
     * @example ../examples/easy/MergeField.php
     * @param string $name
     * @param array $mergeParameters
     * Keys and values:
     * 'format' (Caps, FirstCap, Lower, Upper)
     * 'mappedField' (boolean)
     * 'preserveFormat' (boolean)
     * 'textAfter' string of text to include after the merge field
     * 'textBefore' string of text to include before the merge field
     * 'verticalFormat' (boolean)
     * @param string $format
     * @param array $options style options to apply to the field
     * Keys and values:
     * 'bidi' (on, off)
     * 'b' (on, off)
     * 'color' (ffffff, ff0000...)
     * 'font' (Arial, Times New Roman...)
     * 'i' (on, off)
     * 'jc' (both, center, distribute, left, right)
     * 'pageBreakBefore' (on, off)
     * 'sz' (1, 2, 3...)
     * 'u' (dash, dotted, double, single, wave, words)
     * 'widowControl' (on, off)
     * 'wordWrap' (on, off)
     * 'lineSpacing' 120, 240 (standard), 480...,
     * 'indent_left' 100...,
     * 'indent_right' 100...
     * 'rawWordML' (boolean)
     * 'rtl' (on, off)
     */
    public function addMergeField($name, $mergeParameters = array(), $options = array('rawWordML' => false))
    {
        $options = self::setRTLOptions($options);
        if(!isset($mergeParameters['preserveFormat'])){
           $mergeParameters['preserveFormat'] = true;
        }
        $textOptions = $options;
        $textOptions['rawWordML'] = true;

        $fieldName = '';
        if(isset($mergeParameters['textBefore'])){
            $fieldName .= $mergeParameters['textBefore'];
        }
        $fieldName .= '«' . $name . '»';
        if(isset($mergeParameters['textAfter'])){
            $fieldName .= $mergeParameters['textAfter'];
        }
        $simpleField = $this->addText($fieldName, $textOptions);

        $data = 'MERGEFIELD &quot;' . $name . '&quot; ';
        foreach($mergeParameters as $key => $value){
           switch($key){
               case 'textBefore':
                   $data .= '\b &quot;' . $value . '&quot; ';
               break;
               case 'textAfter':
                   $data .= '\f &quot;' . $value . '&quot; ';
               break;
               case 'mappedField':
                   if($value){
                    $data .= '\m ';
                   }
               break;
               case 'verticalFormat':
                   if($value){
                    $data .= '\v ';
                   }
               break;
               case 'preserveFormat':
                   if($value){
                    $data .= '\* MERGEFORMAT';
                   }
               break;
           }
        }

        $beguin = '<w:fldSimple w:instr=" ' . $data . ' ">';

        $end = '</w:fldSimple>';
        $simpleField = str_replace('<w:r>', $beguin . '<w:r>', $simpleField);
        $simpleField = str_replace('</w:r>', '</w:r>' . $end, $simpleField);

        PhpdocxLogger::logger('Adding a merge field to the Word document.', 'info');

        if (isset($options['rawWordML']) && $options['rawWordML']){
            return (string) $simpleField;
        } else{
            $this->_wordDocumentC .= (string) $simpleField;
        }
    }

    /**
     * Add a MHT file.
     *
     * @access public
     * @example ../examples/easy/MHT.php
     * @param array $options
     * Values:
     * 'pathMHT' (string) path to the MHT file
     * 'rawWordML' (boolean)
     */
    public function addMHT($options = array('rawWordML' => false))
    {
        try {
            if ($this->_compatibilityMode) {
                throw new Exception('Running in compatibility mode. Unsupported method.');
            }
            if (file_exists($options['pathMHT'])) {
                $wordMHT = EmbedMHT::getInstance();
                $wordMHT->embed();
                PhpdocxLogger::logger('Add MHT file to word document.', 'info');
                $this->_zipDocx->addFile($options['pathMHT'], 'word/mht' . $wordMHT->getId() .
                '.mht');
                $this->_wordRelsDocumentRelsC .= $this->generateRELATIONSHIP(
                    'rMHTId' . $wordMHT->getId() , 'aFChunk', 'mht' .
                    $wordMHT->getId() . '.mht', 'TargetMode="Internal"');
                $this->generateDEFAULT('mht', 'message/rfc822');
                if (isset($options['rawWordML']) && $options['rawWordML']) {
                    return (string) $wordMHT . '<w:p />';
                } else {
                    $this->_wordDocumentC .= (string) $wordMHT;
                }
            } else {
                throw new Exception('File does not exist.');
            }
        } catch (Exception $e) {
            PhpdocxLogger::logger($e->getMessage(), 'fatal');
        }
    }

    /**
     * Add a new base template into the templates folder.
     *
     * @access public
     * @param string $path. Must be a valid path to an existing .docx, .dotx o .docm document
     * @param string $name. Must be a valid name for the new base template. It should include the extension
     * @param boolean $overwrite. Optional. If true overwrites any existing template with the given name
     *
     */
    public function addNewBaseTemplate($path, $name, $overwrite=false)
    {
        if (!$overwrite) {
            try {
                $exists = file_exists(PHPDOCX_BASE_FOLDER.'/'.$name);
                if ($exists == true) {
                    throw new Exception('There is a base template by that name. If you want to overwrite it set the overwrite parameter to true');
                }
            } catch (Exception $e) {
                PhpdocxLogger::logger($e->getMessage(), 'fatal');
            }
        }
        try{
            $newTemplate= copy($path, PHPDOCX_BASE_FOLDER.'/'.$name);
            if ($newTemplate !== true) {
                throw new Exception('Error while trying to copy the new template: please, check the path or the permission rights of the template folder');
            }
        } catch (Exception $e) {
            PhpdocxLogger::logger($e->getMessage(), 'fatal');
        }
    }

    /**
     * Add an existing object (XLS or PPTX)
     *
     * @access public
     * @todo Unfinished method
     * @param array $options
     * Values:
     * 'path' (string) path to the object
     * 'type' (string) object type: xlsx, pptx
     * 'rawWordML' (boolean)
     */
    public function addObject($options = array('rawWordML' => false))
    {
        try {
            if (file_exists($options['path']) &&
                ($options['type'] == 'xls' || $options['type'] == 'pptx')) {
                self::$intIdWord++;
                PhpdocxLogger::logger('New ID ' . self::$intIdWord . ' . Object.', 'debug');
                if ($options['type'] == 'xls') {
                    $this->generateDEFAULT(
                        'xls', 'application/vnd.ms-excel'
                    );
                    $this->_wordRelsDocumentRelsC .=
                        $this->generateRELATIONSHIP('rId' . self::$intIdWord,
                            'oleObject',
                            'embeddings/Microsoft_Office_Excel_97-2003_'
                            + 'Worksheet' + self::$intIdWord + '.xls'
                        );
                } elseif ($options['type'] == 'pptx') {
                    $this->generateDEFAULT(
                        'pptx', 'application/vnd.openxmlformats-officedocument'
                        + '.presentationml.presentation'
                    );
                    $this->_wordRelsDocumentRelsC .=
                        $this->generateRELATIONSHIP('rId' . self::$intIdWord,
                            'package',
                            'embeddings/Microsoft_Office_PowerPoint_'
                            + 'PresentationWorksheet' + self::$intIdWord
                            + '.pptx'
                    );
                }
                $this->generateDEFAULT(
                        'emf', 'image/x-emf'
                );
                $object = CreateObject::getInstance();
                $object->createObject($options['path'], $options['type']);
                PhpdocxLogger::logger('Add object to word document.', 'info');
                if (isset($options['rawWordML']) && $options['rawWordML']) {
                    return (string) $object;
                } else {
                    $this->_wordDocumentC .= (string) $object;
                }
            } else {
                throw new Exception('File does not exist or format is not supported.');
            }
        } catch (Exception $e) {
            PhpdocxLogger::logger($e->getMessage(), 'warn');
            throw new Exception('File does not exist or format is not supported.');
        }
    }

    /**
     * Adds page borders
     *
     * @access public
     * @example ../examples/easy/PageBorders.php
     * @param array $options (<side> stands for top, right, bootom or left)
     * 'zOrder' (int)
     * 'display' (string) posible values are:allPages (display page border on all pages, default value),
     *  firstPage(display page border on first page), notFirstPage (display page border on all pages except first)
     * 'offsetFrom' (string) posible values are: page or text
     * border-width (int) page border width in eigths of a point (default value is 4)
     * border-color (string) hexadecimal color ('000000' (default), 'FF0000', ...)
     * border-style (string) none, single, double, ... (default value is  single)
     * border-space (int) border spacing in points (default is 24)
     * border-<side>-width (int) page border width in eighths of a point
     * border-<side>-color (string) hexadecimal color ('000000' (default), 'FF0000', ...)
     * border-<side>-style (string) none, single, double, ... (default value is  single)
     * border-<side>-space (int) border spacing in points (default is 24)
     */
    public function addPageBorders($options = array())
    {
        //Restart condition available types
        $display_types = array('allPages', 'firstPage', 'notFirstPage');
        $offset_types = array('page', 'text');
        $sides = array('top', 'left', 'bottom', 'right');
        $type = array('width' => 4 , 'color' => '000000', 'style' => 'single', 'space' => 24);

        //Set default values
        if(isset($options['zOrder'])){
            $zOrder = $options['zOrder'];
        }else{
            $zOrder = 1000;
        }
        if(isset($options['display']) && in_array($options['display'], $display_types)){
            $display = $options['display'];
        }else{
            $display = 'allPages';
        }
         if(isset($options['offsetFrom']) && in_array($options['offsetFrom'], $offset_types)){
            $offsetFrom = $options['offsetFrom'];
        }else{
            $offsetFrom = 'page';
        }
        foreach($type as $key => $value){
            foreach($sides as $side){
                if(isset($options['border-' . $side . '-' . $key])){
                    $opt['border-' . $side . '-' . $key] = $options['border-' . $side . '-' . $key];
                }else if(isset($options['border-' . $key])){
                    $opt['border-' . $side . '-' . $key] = $options['border-' . $key];
                }else{
                    $opt['border-' . $side . '-' . $key] = $value;
                }
            }
        }

        //If there is any previous pgBorders tag remove it
        if ($this->_sectPr->getElementsByTagName('pgBorders')->length > 0) {
            $pgBorder =$this->_sectPr->getElementsByTagName('pgBorders')->item(0);
            $pgBorder->parentNode->removeChild($pgBorder);
        }
        //Now we insert the requested page borders
        $pgBordersNode = $this->_sectPr->createDocumentFragment();
        $strNode = '<w:pgBorders ';
        $strNode .= 'xmlns:w="http://schemas.openxmlformats.org/wordprocessingml/2006/main" ';
        $strNode .= 'w:zOrder="' . $zOrder . '" w:display="' . $display . '" w:offsetFrom="' . $offsetFrom . '" >';
        foreach($sides as $side){
            $strNode .='<w:' . $side . ' w:val="' .  $opt['border-' . $side . '-style'] . '" ';
            $strNode .= 'w:color="' . $opt['border-' . $side . '-color'] . '" ';
            $strNode .= 'w:sz="' . $opt['border-' . $side . '-width'] . '" ';
            $strNode .= 'w:space="' . $opt['border-' . $side . '-space'] . '" />';
        }
        $strNode .= '</w:pgBorders>';
        $pgBordersNode->appendXML($strNode);

        $propIndex = array_search('w:pgBorders', self::$sectionProperties);
        $childNodes = $this->_sectPr->documentElement->childNodes;
        $index = false;
        foreach($childNodes as $node){
            $name = $node->nodeName;
            $index = array_search($node->nodeName, self::$sectionProperties);
            if($index > $propIndex){
                $node->parentNode->insertBefore($pgBordersNode, $node);
                break;
            }
        }
        //in case no node was found (pretty unlikely) we should append the node
        if (!$index) {
            $this->_sectPr->documentElement->appendChild($pgBordersNode);
        }

    }

    /**
     * Adds a page number to the document
     * WARNING: if the page number is not added to a header or footer the user may
     * need to press F9 in the MS Word interface to update its value to the current page
     *
     * @access public
     * @example ../examples/easy/PageNumber.php
     * @example ../examples/intermediate/FooterPager.php
     * @param mixed $type (String): numerical, alphabetical.
     * @param array $options Style options to apply to the numbering
     *  Values:
     * 'bidi' (on, off)
     * 'b' (on, off)
     * 'color' (ffffff, ff0000...)
     * 'font' (Arial, Times New Roman...)
     * 'i' (on, off)
     * 'jc' (both, center, distribute, left, right)
     * 'pageBreakBefore' (on, off)
     * 'sz' (1, 2, 3...)
     * 'u' (dash, dotted, double, single, wave, words)
     * 'widowControl' (on, off)
     * 'wordWrap' (on, off)
     * 'lineSpacing' 120, 240 (standard), 480...,
     * 'indent_left' 100...,
     * 'indent_right' 100...
     * 'defaultValue' (int)
     * 'rawWordML' (boolean)
     * 'rtl' (on, off)
     *
     */
    public function addPageNumber($type = 'numerical', $options = array('defaultValue' => 1, 'rawWordML' => false))
    {
        $options = self::setRTLOptions($options);
        if(!isset($options['defaultValue'])){
            if($type == 'numerical'){
                $options['defaultValue'] = '1';
            }else if($type == 'alphabetical'){
                $options['defaultValue'] = 'a';
            }
        }
        $textOptions = $options;
        $textOptions['rawWordML'] = true;
        $pageNumber = $this->addText($options['defaultValue'], $textOptions);
        if ($type == 'alphabetical') {
            $beguin = '<w:fldSimple w:instr="PAGE \* alphabetic \* MERGEFORMAT">';
        } else {
            $beguin = '<w:fldSimple w:instr="PAGE \* MERGEFORMAT">';
        }
        $end = '</w:fldSimple>';
        $pageNumber = str_replace('<w:r>', $beguin . '<w:r>', $pageNumber);
        $pageNumber = str_replace('</w:r>', '</w:r>' . $end, $pageNumber);
        PhpdocxLogger::logger('Add page number to word document.', 'info');
        if (isset($options['rawWordML']) && $options['rawWordML']) {
            return (string) $pageNumber;
        } else {
            $this->_wordDocumentC .= (string) $pageNumber;
        }
    }

    /**
     * Adds a complex paragraph to a Word document
     *
     * @access public
     * @example ../examples/intermediate/ComplexParagraph.php
     * @example ../examples/intermediate/EmbeddedShapes.php
     * @param array $options
     *  @see CreateDocx->addText()
     * 'spacingBottom' (int) bottom margin in points
     * 'spacingTop'(int) top margin in points
     * 'target' (string) document (default value), defaultHeader, firstHeader, evenHeader, defaultFooter, firstFooter, evenFooter.
     * 'rawWordML' (boolean)
     * @param array $parameters :
     *  values: 'type' (text, lineBreak, link, bookmark, image, footnote, endnote, arc, curve, line, polyline, rect, roundrect, shape, oval)
     *  @see CreateDocx->addText()
     *  Extra options
     *  type link: 'URL' (http://... or #anchor)
     *  type bookmark: 'markerName' (string)
     *  type image: @see CreateDocx->addImage()
     *  'position' (inline, left, right)
     *  types arc, curve, line, polyline, rect, roundrect, shape, oval: @see CreateDocx->addShape()
     */
    public function addParagraph($parameters, $options)
    {
        if(!isset($options['target'])){
            $options['target'] = 'document';
        }
        $rawParagraph = '';
        try {
            $customHTML = CustomHTML::getInstance();
            $pHTML = $customHTML->paragraphHTML($parameters, $options);
            if(isset($options['rawWordML']) && $options['rawWordML'] === true){
                $rawParagraph = $this->embedHTML($pHTML[0], array('target' => $options['target'], 'downloadImages' => true, 'parseAnchors' => true, 'rawWordML' => true));
            }else{
                $this->embedHTML($pHTML[0], array('downloadImages' => true, 'parseAnchors' => true));
            }
            if(count($pHTML[1]) > 0){
                foreach($pHTML[1] as $key => $value){
                    $footnoteWordML = new HTML2WordML($this->_baseTemplateFilesPath);
                    $dataML = $footnoteWordML->render($value, array());
                    $footnoteML = (string) $dataML[0];
                    $footnoteBase ='<w:footnote w:id="'.$key.'" xmlns:w="http://schemas.openxmlformats.org/wordprocessingml/2006/main">'.$footnoteML.'</w:footnote>';
                    //Let us get the font color and family to modify accordingly the superscript
                    $tempSubstring = explode('<w:rPr>', $footnoteBase);
                    $content = explode('</w:rPr>', $tempSubstring[1]);
                    $rStyle = str_replace('<w:vertAlign w:val="superscript" />','',$content[0]);
                    $aux = '<w:r><w:rPr>' .$rStyle. '<w:vertAlign w:val="superscript" /></w:rPr><w:footnoteRef/></w:r>';
                    //We now insert the superscript into the footnote
                    $footnoteBase = str_replace('</w:pPr><w:r>', '</w:pPr>'.$aux.'<w:r>', $footnoteBase);
                    //Let us open the footnotes.xml file to insert the new footnote
                    $filename = $this->_baseTemplateFilesPath.'/word/footnotes.xml';
                    $handle = fopen($filename, "r");
                    $contents = fread($handle, 999999);
                    fclose($handle);

                    $this->_wordFootnotesT = new DOMDocument();
                    $this->_wordFootnotesT->loadXML($contents);

                    $tempNode = $this->_wordFootnotesT->createDocumentFragment();
                    $tempNode->appendXML($footnoteBase);
                    $this->_wordFootnotesT->documentElement->appendChild($tempNode);

                    //We copy the  content into the respective file
                    $footnoteHandler = fopen($this->_baseTemplateFilesPath.'/word/footnotes.xml', "w+");
                    fwrite($footnoteHandler, $this->_wordFootnotesT->saveXML());
                    fclose($footnoteHandler);
                }
            }
            if(count($pHTML[2]) > 0){
                foreach($pHTML[2] as $key => $value){
                    $endnoteWordML = new HTML2WordML($this->_baseTemplateFilesPath);
                    $dataML = $endnoteWordML->render($value, array());
                    $endnoteML = (string) $dataML[0];
                    $endnoteBase ='<w:endnote w:id="'.$key.'" xmlns:w="http://schemas.openxmlformats.org/wordprocessingml/2006/main">'.$endnoteML.'</w:endnote>';
                    //Let us get the font color and family to modify accordingly the superscript
                    $tempSubstring = explode('<w:rPr>', $endnoteBase);
                    $content = explode('</w:rPr>', $tempSubstring[1]);
                    $rStyle = str_replace('<w:vertAlign w:val="superscript" />','',$content[0]);
                    $aux = '<w:r><w:rPr>' .$rStyle. '<w:vertAlign w:val="superscript" /></w:rPr><w:endnoteRef/></w:r>';
                    //We now insert the superscript into the endnote
                    $endnoteBase = str_replace('</w:pPr><w:r>', '</w:pPr>'.$aux.'<w:r>', $endnoteBase);
                    //Let us open the endnotes.xml file to insert the new endnote
                    $filename = $this->_baseTemplateFilesPath.'/word/endnotes.xml';
                    $handle = fopen($filename, "r");
                    $contents = fread($handle, 999999);
                    fclose($handle);


                    $this->_wordEndnotesT = new DOMDocument();
                    $this->_wordEndnotesT->loadXML($contents);

                    $tempNode = $this->_wordEndnotesT->createDocumentFragment();
                    $tempNode->appendXML($endnoteBase);
                    $this->_wordEndnotesT->documentElement->appendChild($tempNode);

                    //We copy the  content into the respective file
                    $endnoteHandler = fopen($this->_baseTemplateFilesPath.'/word/endnotes.xml', "w+");
                    fwrite($endnoteHandler, $this->_wordEndnotesT->saveXML());
                    fclose($endnoteHandler);
                }
            }
            //Now we are going to check if there are any shapes to be included
            if(count($pHTML[3]) > 0){
                for($j = 0; $j < count($pHTML[3]); $j++){
                    $type = $pHTML[3][$j]['type'];
                    $pHTML[3][$j]['rawWordML'] = true;
                    $shapeData = $this->addShape($type, $pHTML[3][$j]);
                    //Now we have to substitute in the document <w:t xml:space="preserve">PHPDOCX_shape_2</w:t>
                    //by the corresponding <w:pict>
                    if(isset($options['rawWordML']) && $options['rawWordML'] === true){
                        $rawParagraph = str_replace('<w:t xml:space="preserve">PHPDOCX_shape_'.$j.'</w:t>', $shapeData, $rawParagraph);
                    }else{
                        $this->_wordDocumentC = str_replace('<w:t xml:space="preserve">PHPDOCX_shape_'.$j.'</w:t>', $shapeData, $this->_wordDocumentC);
                    }
                }
            }
        }

        catch (Exception $e) {
            PhpdocxLogger::logger($e->getMessage(), 'fatal');
        }
        if (isset($options['rawWordML']) && $options['rawWordML'] === true) {
            $paragraphObj = new WordML();
            $paragraphObj->createRawWordML($rawParagraph);
            return $paragraphObj;
        }
    }

    /**
     * Add properties to document
     *
     * @access public
     * @example ../examples/easy/Properties.php
     * @param array $values Parameters to use
     *  Values: 'title', 'subject', 'creator', 'keywords', 'description',
     *  'category', 'contentStatus', 'Manager','Company', 'custom' ('name' => array('type' => 'value'))
     */

    public function addProperties($values)
    {
        $prop = CreateProperties::getInstance();
        if (!empty($values['title'])
                || !empty($values['subject'])
                || !empty($values['creator'])
                || !empty($values['keywords'])
                || !empty($values['description'])
                || !empty($values['category'])
                || !empty($values['contentStatus'])) {
            $prop->createProperties($values, $this->_baseTemplateFilesPath);
        }
        if($values['contentStatus'] == 'Final'){
            $prop->createPropertiesCustom(array('_MarkAsFinal' => array('boolean' => 'true')), $this->_baseTemplateFilesPath);
            //We now write the new Override node associated to the new custon.xml file en [Content_Types].xml

            $this->generateOVERRIDE(
            '/docProps/custom.xml',
            'application/vnd.openxmlformats-officedocument.' .
            'custom-properties+xml'
            );
        }
        if (!empty($values['Manager']) || !empty($values['Company'])) {
            $prop->createPropertiesApp($values, $this->_baseTemplateFilesPath);
        }
        if (!empty($values['custom']) && is_array($values['custom'])) {
            $prop->createPropertiesCustom($values['custom'], $this->_baseTemplateFilesPath);

            //We now write the new Override node associated to the new custon.xml file en [Content_Types].xml
            $this->generateOVERRIDE(
            '/docProps/custom.xml',
            'application/vnd.openxmlformats-officedocument.' .
            'custom-properties+xml'
            );

        }
        PhpdocxLogger::logger('Adding properties to word document.', 'info');
    }

    /**
     * Adds a simple field to the Word document
     * WARNING: if the page number is not added to a header or footer the user may
     * need to press F9 in the MS Word interface to update its value to the current page
     *
     * @access public
     * @example ../examples/easy/SimpleField.php
     * @param $fieldName the field value. Available fields are:
     * AUTHOR, COMMENTS, DOCPROPERTY, FILENAME, FILESIZE, KEYWORDS,
     * LASTSAVEDBY, NUMCHARS, NUMPAGES, NUMWORDS, SUBJECT, TEMPLATE, TITLE
     * @param string $type: date, numeric or general.
     * @param string $format
     * @param array $options style options to apply to the field
     * Values:
     * 'bidi' (on, off)
     * 'b' (on, off)
     * 'color' (ffffff, ff0000...)
     * 'font' (Arial, Times New Roman...)
     * 'i' (on, off)
     * 'jc' (both, center, distribute, left, right)
     * 'pageBreakBefore' (on, off)
     * 'sz' (1, 2, 3...)
     * 'u' (dash, dotted, double, single, wave, words)
     * 'widowControl' (on, off)
     * 'wordWrap' (on, off)
     * 'lineSpacing' 120, 240 (standard), 480...,
     * 'indent_left' 100...,
     * 'indent_right' 100...
     * 'defaultValue' (mixed)
     * 'doNotShadeFormData' (bool)
     * 'updateFields' (bool)
     * 'rawWordML' (boolean)
     * 'rtl' (on, off)
     *
     */
    public function addSimpleField($fieldName, $type = 'general', $format = '', $options = array('rawWordML' => false))
    {
        $options = self::setRTLOptions($options);
        $availableTypes = array('date' =>'\@', 'numeric' => '\#', 'general' => '\*');
        $fieldOptions = array();
        if(isset($options['doNotShadeFormData']) && $options['doNotShadeFormData']){
            $fieldOptions['doNotShadeFormData'] = true;
        }
        if(isset($options['updateFields']) && $options['updateFields']){
            $fieldOptions['updateFields'] = true;
        }
        if(count($fieldOptions) > 0){
            $this->docxSettings($fieldOptions);
        }
        $textOptions = $options;
        $textOptions['rawWordML'] = true;

        $simpleField = $this->addText($fieldName, $textOptions);

        $data = $fieldName . ' ';
        if(!empty($format)){
            $data .= $availableTypes[$type] . ' ' . $format . ' ';
        }
        $data .= '\* MERGEFORMAT';
        $beguin = '<w:fldSimple w:instr=" ' . $data . ' ">';

        $end = '</w:fldSimple>';
        $simpleField = str_replace('<w:r>', $beguin . '<w:r>', $simpleField);
        $simpleField = str_replace('</w:r>', '</w:r>' . $end, $simpleField);

        PhpdocxLogger::logger('Adding a simple field to the Word document.', 'info');
        //In order to preserve the run styles we have to insert them within the <w:pPr> tag
        if(isset($options['rawWordML']) && $options['rawWordML']){
            return (string) $simpleField;
        }else{
            $this->_wordDocumentC .= (string) $simpleField;
        }
    }

    /**
     * Add a raw WordML
     *
     * @access public
     * @param string $wml WordML to add
     * @deprecated See addWordML
     */
    public function addRawWordML($wml)
    {
        PhpdocxLogger::logger('Add raw WordML.', 'info');
        $this->_wordDocumentC .= $wml;
    }

    /**
     * Add a RTF file. Keep content and styles.
     *
     * @access public
     * @example ../examples/easy/RTF.php
     * @param array $options
     * Values:
     * 'pathRTF' (string) path to the RTF file
     * 'rawWordML' (boolean)
     */
    public function addRTF($options = array('rawWordML' => false))
    {
        try {
            if ($this->_compatibilityMode) {
              throw new Exception('Running in compatibility mode. Unsupported method.');
            }
            if (file_exists($options['pathRTF'])) {
                $wordRTF = EmbedRTF::getInstance();
                $wordRTF->embed();
                PhpdocxLogger::logger('Add RTF file to word document.', 'info');
                $this->_zipDocx->addFile($options['pathRTF'], 'word/rtf' . $wordRTF->getId() .
                '.rtf');
                $this->_wordRelsDocumentRelsC .= $this->generateRELATIONSHIP(
                    'rRTFId' . $wordRTF->getId() , 'aFChunk', 'rtf' .
                    $wordRTF->getId() . '.rtf', 'TargetMode="Internal"');
                $this->generateDEFAULT('rtf', 'application/rtf');
                if(isset($options['rawWordML']) && $options['rawWordML']){
                    return (string) $wordRTF . '<w:p/>';
                }else{
                    $this->_wordDocumentC .= (string) $wordRTF;
                }
            } else {
                throw new Exception('File does not exist.');
            }
        }
        catch (Exception $e) {
            PhpdocxLogger::logger($e->getMessage(), 'fatal');
        }
    }

     /**
     * Adds a section
     *
     * @access public
     * @example ../examples/easy/Section.php
     * @param string sectionType (string): nextPage, nextColumn, continuous, evenPage, oddPage
     * @param array paperType (string): A4, A3, letter, legal, A4-landscape, A3-landscape, letter-landscape, legal-landscape, custom
     * @param array options
     * Values:
     * width (int): measurement in twips (twentieths of a point)
     * height (int): measurement in twips (twentieths of a point)
     * numberCols (int): number of columns
     * orient (string): portrait, landscape
     * marginTop (int): measurement in twips (twentieths of a point)
     * marginRight (int): measurement in twips (twentieths of a point)
     * marginBottom (int): measurement in twips (twentieths of a point)
     * marginLeft (int): measurement in twips (twentieths of a point)
     * marginHeader (int): measurement in twips (twentieths of a point)
     * marginFooter (int): measurement in twips (twentieths of a point)
     * gutter (int): measurement in twips (twentieths of a point)
     * bidi (on, off)
     * rtl (on, off)
     */

    public function addSection($sectionType = 'nextPage', $paperType = 'custom', $options = array())
    {
        $options = self::setRTLOptions($options);
        if (!$paperType) {
            $paperType = $this->_phpdocxconfig['settings']['paper_size'];
        }
        $previousSectionPr = '<w:p><w:pPr>'.$this->_sectPr->saveXML().'</w:pPr></w:p>';
        $previousSectionPr = str_replace('<?xml version="1.0"?>', '', $previousSectionPr);
        $this->_wordDocumentC .= (string) $previousSectionPr;
        $this->modifyPageLayout($paperType, $options);
        $nodeSz = $this->_sectPr->getElementsByTagName('pgSz')->item(0);
        $typeNode = $this->_sectPr->createDocumentFragment();
        $typeNode->appendXML('<w:type xmlns:w="http://schemas.openxmlformats.org/wordprocessingml/2006/main" w:val="'.$sectionType.'" />');
        $nodeSz->parentNode->insertBefore($typeNode, $nodeSz);
    }

    /**
     * Add a shape
     *
     * @access public
     * @example ../examples/intermediate/Shapes.php
     * @param string $type Type of shape to draw
     *  Values:arc, curve, line, polyline, rect, roundrect, shape, oval
     * @param array $options
     * General options:
     * 'width' in points
     * 'height' in points
     * 'position' (absolute, relative)
     * 'margin-top' in points
     * 'margin-left' in points
     * 'z-index' integer
     * 'strokecolor' (#ff0000, #00ffff, ...)
     * 'strokeweight' (1.0pt, 3.5pt, ...)
     * 'fillcolor' (#ff0000, #00ffff, ...)
     * 'rawWordML' (boolean)
     * Options for especific type:
     * arc: 'startAngle' (0, 45, 90, ...), 'endAngle' (0, 45, 90, ...)
     * line and curve: 'from' and 'to' (initial and final points in x,y format)
     * curve: 'control1' (x,y), 'control2' (x,y)
     * polyline: 'points' (x1,y1 x2,y2 ....)
     * roundrect: 'arcsize' (0.5, 1.8, ...)
     * shape: 'path' (VML path), 'coordsize' (x,y)
     */
    public function addShape($type, $options = array('rawWordML' => false))
    {
        $shape = new CreateShape();
        $shapeData = $shape->createShape($type, $options);
        PhpdocxLogger::logger('Add a ' . $type . 'to the Word document.', 'info');
        if(isset($options['rawWordML']) && $options['rawWordML']){
            return '<w:p><w:r>'. $shapeData . '</w:r></w:p>';
        }else{
            $paragraphShape = '<w:p><w:r>'. $shapeData . '</w:r></w:p>';
            $this->_wordDocumentC .= $paragraphShape;
        }
    }

    /**
     * Add a Structured Document Tag
     *
     * @access public
     * @example ../examples/easy/StructuredDocumentTag.php
     * @param mixed $type it can be 'comboBox', 'date', 'dropDownList' or 'richText'
     * @param array $options Style options to apply to the text
     *  Values:
     * 'b' (on, off)
     * 'color' (ffffff, ff0000...)
     * 'font' (Arial, Times New Roman...)
     * 'i' (on, off)
     * 'jc' (both, center, distribute, left, right)
     * 'lineBreak' (before, after, both)
     * 'columnBreak' (before, after, both)
     * 'pageBreakBefore' (on, off)
     * 'sz' (1, 2, 3...)
     * 'u' (dash, dotted, double, single, wave, words)
     * 'widowControl' (on, off)
     * 'wordWrap' (on, off)
     * 'lineSpacing' 120, 240 (standard), 480...,
     * 'indent_left' 100...,
     * 'indent_right' 100...
     * 'placeholderText (string) text to be shown by default
     * 'alias' (string) the label that will be shown by the structured document tag
     * 'lock' (string) locking properties: sdtLocked (cannot be deleted),
     * contentLocked (contents can not be edited directly), unlocked (default value: no locking) and sdtContentLocked (contents can not be directyly edited or the structured tag removed)
     * 'tag' (string) a programmatic tag
     * 'temporary (boolean) if true the structured tag is removed after editing
     * 'rawWordML' (boolean)
     * 'listItems' (array) an array of arrays each one of them containing the text to show and value
     */
    public function addStructuredDocumentTag($type, $options = array('rawWordML' => false))
    {
        $sdtTypes = array('comboBox', 'date', 'dropDownList', 'richText');
        if(!in_array($type, $sdtTypes)){
            PhpdocxLogger::logger('The chosen Structured Document Tag type is not available', 'fatal');
            exit();
        }
        $sdtBase = CreateText::getInstance();
        $ParagraphOptions = $options;
        $ParagraphOptions['rawWordML'] = true;
        $ParagraphOptions['text'] = $options['placeholderText'];
        $sdtBase->createText(array($ParagraphOptions), $ParagraphOptions);
        $sdt = CreateStructuredDocumentTag::getInstance();
        $sdt->createStructuredDocumentTag($type, $options, (string)$sdtBase);
        PhpdocxLogger::logger('Add Structured Document Tag to Word document.', 'info');
        if(isset($options['rawWordML']) && $options['rawWordML']){
            return (string) $sdt;
        }else{
            $this->_wordDocumentC .= (string) $sdt;
        }
    }

    /**
     * Add a subdocument to a master document. The document should be in the
     * same folder as the final master document
     *
     * @param string $path path to the subdocument
     * @param string $destination path to where the subdocument should be stored
     * if empty is assumed to remain in its original folder
     * @access public
     */
    public function addSubDocument($originalPath, $destination = '')
    {
        $rId = 'rId'.uniqid(true);
        $this->_wordDocumentC .= '<w:p><w:pPr><w:pStyle w:val="Heading2PHPDOCX" /></w:pPr><w:subDoc r:id ="'.$rId.'" /></w:p>';
        $this->generateRELATIONSHIP($rId, 'subDocument', $originalPath, 'TargetMode="External"');
    }

    /**
     * Add a table.
     *
     * @access public
     * @example ../examples/easy/Table.php
     * @example ../examples/intermediate/Table.php
     * @example ../examples/intermediate/TableStyled.php
     * @example ../examples/advanced/Report.php
     * @param array $tableData an array of arrays with the table data organized by rows
     * Each cell content may be a string, WordMLFragment or array.
     * If the cell contents are in the form of an array its keys and posible values are:
     *      'value' (mixed) a string or WordMLFragment
     *      'rowspan' (int)
     *      'colspan' (int)
     *      'width' (int) in twentieths of a point
     *      'border' (none, single, double, dashed, threeDEngrave, threeDEmboss, outset, inset)
     *      'border_color' (ffffff, ff0000)
     *      'border_spacing' (0, 1, 2...)
     *      'border_sz' (10, 11...) in eights of a point
     *      'border_<side>' (none, single, double, dashed, threeDEngrave, threeDEmboss, outset, inset) where the side may be: top, left, right or bottom
     *      'border_<side>_color' (ffffff, ff0000)
     *      'border_<side>_spacing' (0, 1, 2...)
     *      'border_<side>_sz' (10, 11...)
     *      'background_color' (ffffff, ff0000)
     *      'noWrap' (boolean)
     *      'cellMargin' (mixed) an integer value or an array:
     *          'top' (int) in twentieths of a point
     *          'right' (int) in twentieths of a point
     *          'bottom' (int) in twentieths of a point
     *          'left' (int) in twentieths of a point
     *      'textDirection' (string) available values are: tbRl and btLr
     *      'fitText' (boolean) if true fits the text to the size of the cell
     *      'vAlign' (string) vertical align of text: top, center, both or bottom
     *
     * @param array $tableProperties Parameters to use
     *  Values:
     *  'bidi' (on, off) set it to on for right to left languages
     *  'border' (none, single, double, dashed, threeDEngrave, threeDEmboss, outset, inset)
     *  'border_color' (ffffff, ff0000)
     *  'border_spacing' (0, 1, 2...)
     *  'border_sz' (10, 11...) in eights of a point
     *  'border_settings' (all, outside, inside) if all (default value) the border styles apply to all table borders.
     *  If the value is set to outside or inside the border styles will only apply to the outside or inside boreders respectively.
     *  'cantSplitRows' (boolean) set global row split properties (can be overriden by rowProperties)
     *  'cellMargin' (array) the keys are top, right, bottom and left and the values is given in twips (twentieths of a point)
     *  'cellSpacing' (int) given in twips (twentieths of a point)
     *  'float' (array) with the following keys and values:
     *      'textMargin_top' (int) in twentieths of a point
     *      'textMargin_right' (int) in twentieths of a point
     *      'textMargin_bottom' (int) in twentieths of a point
     *      'textMargin_left' (int) in twentieths of a point
     *      'align' (string) posible values are: left, center, right, outside, inside
     *  'font' (Arial, Times New Roman...)
     *  'indent' (int) given in twips (twentieths of a point)
     *  'jc' (center, left, right)
     *  'decimalTab'
     *  'size_col': column width fix (int)
     *              column width variable (array)
     *  'tableWidth' (array) its posible keys and values are:
     *      'type' (pct, dxa) pct if the value refers to percentage and dxa if the value is given in twentieths of a point (twips)
     *      'value' (int)
     *  'TBLSTYLEval' (string) Word table style
     *  'rawWordML' (boolean)
     *
     * @param array $rowProperties (array) a cero based array. Each entry is an array with keys and values:
     *      'cantSplit' (boolean)
     *      'minHeight' (int) in twentieths of a point
     *      'height' (int) in twentieths of a point
     *      'tblHeader' (boolean) if true this row repeats at the beguinning of each new page
     */
    public function addTable($tableData, $tableProperties= array('rawWordML' => false), $rowProperties = array())
    {
        $tableProperties = self::setRTLOptions($tableProperties);
        $table = CreateTable::getInstance();
        $table->createTable($tableData, $tableProperties, $rowProperties);
        PhpdocxLogger::logger('Add table to Word document.', 'info');
        if(isset($tableProperties['rawWordML']) && $tableProperties['rawWordML']){
            return (string) $table;
        }else{
            $this->_wordDocumentC .= (string) $table;
        }
    }

    /**
     * Add a table of contents (TOC)
     *
     * @access public
     * @example ../examples/easy/TableContents.php
     * @param array $options
     *  Values:
     * 'autoUpdate' (boolean) if true it will try to update the TOC when first opened
     * 'displayLevels' (string) must be of the form '1-3' where the first number is
     * the start level an the second the end level. If not defined all existing levels are shown
     * @param (array) $legend
     * Values:
     * 'pStyle' (string) Word style to be used. Run parseStyles() to check all available paragraph styles
     * 'b' (on, off)
     * 'color' (ffffff, ff0000...)
     * 'font' (Arial, Times New Roman...)
     * 'i' (on, off)
     * 'indent_left' 100...,
     * 'indent_right' 100...
     * 'jc' (both, center, distribute, left, right)
     * 'keepLines' (on, off) keep all paragraph lines on the same page
     * 'keepNext' (on, off) keep in the same page the current paragraph with next paragraph
     * 'lineSpacing' 120, 240 (standard), 480...,
     * 'pageBreakBefore' (on, off)
     * 'sz' (8, 9, 10, ...)
     * 'text' (string)
     * 'u' (none, dash, dotted, double, single, wave, words)
     * 'widowControl' (on, off)
     * 'wordWrap' (on, off)
     * @param (string) $stylesTOC path to the docx with the required styles for the Table of Contents
     */
    public function addTableContents($options = array(), $legend = array(), $stylesTOC = '')
    {
        $legend = self::setRTLOptions($legend);
        if(!empty($stylesTOC)){
            $this->importStyles($stylesTOC, 'merge', array('TDC1', 'TDC2', 'TDC3', 'TDC4', 'TDC5', 'TDC6', 'TDC7', 'TDC8', 'TDC9'), 'styleID');
        }
        if(empty($legend['text'])){
            $legend['text'] = 'Click here to update the Table of Contents';
        }
        $legendOptions = $legend;
        unset($legendOptions['text']);
        $legendOptions['rawWordML'] = true;
        $legendData = $this->addText(array($legend), $legendOptions);
        $tableContents = CreateTableContents::getInstance();
        $tableContents->createTableContents($options, $legendData);
        if($options['autoUpdate']){
            $this->generateSetting('w:updateFields');
        }
        PhpdocxLogger::logger('Add table of contents to word document.', 'info');
        $this->_wordDocumentC .= (string) $tableContents;
    }

    /**
     * Add a DOCX file as a template
     *
     * @access public
     * @example ../examples/easy/Template.php
     * @example ../examples/easy/Template_docx.php
     * @example ../examples/easy/Template_html.php
     * @example ../examples/easy/Template_image.php
     * @example ../examples/easy/Template_mht.php
     * @example ../examples/easy/Template_rtf.php
     * @example ../examples/easy/Template_text.php
     * @example ../examples/intermediate/Template.php
     * @example ../examples/intermediate/Template_image.php
     * @example ../examples/intermediate/Template_multitext.php
     * @param string $path Path to the template file
     */
    public function addTemplate($path)
    {
        $numRef = rand(9999999, 99999999);
        CreateDocx::$numUL = $numRef;
        CreateDocx::$numOL = $numRef +1;
        $template = CreateTemplate::getInstance();
        try {
            if (file_exists($path)) {
                PhpdocxLogger::logger('Open template ' . $path . '.', 'info');
                $template->openTemplate($path);
            } else {
                throw new Exception('File ' . $path . ' not exists');
            }
        } catch (Exception $e) {
            PhpdocxLogger::logger($e->getMessage(), 'fatal');
        }
    }

    /**
     * Replace a variable with a chart.
     *
     * @access public
     * @example ../examples/easy/Template_chart.php
     * @param string $var Value of the variable
     * @param string $chart Chart to add
     *  Values: same as charts.
     */
    public function addTemplateChart($var, $chart)
    {
        $template = CreateTemplate::getInstance();
        PhpdocxLogger::logger('Assign as chart variable ' . $var . ' in template.', 'info');
        $this->addGraphicTemplate($chart);
        PhpdocxLogger::logger('Replace chart variable ' . $var . ' in template.', 'info');
        $template->replaceChart($var);
    }

    /**
     * Replace a variable with a checkbox.
     *
     * @access public
     * @example ../examples/easy/Template_checkbox.php
     * @param string $var Value of the variable. String
     * @param string $value
     */
    public function addTemplateCheckBox($var, $value = false)
    {
        $template = CreateTemplate::getInstance();
        PhpdocxLogger::logger('Replace text variable ' . $var . ' with a checkbox.', 'info');
        $template->replaceCheckBox($var, $value);
    }

    /**
     * Replace a variable image template with a new image.
     *
     * @access public
     * @example ../examples/easy/Template_image.php
     * @param string $var Value of the variable
     * @param string $pathImage Path of the new image
     * @param array $options
     * Values:
     * width (mixed): the value in cm (float) or 'auto' (use image size)
     * height (mixed): the value in cm (float) or 'auto' (use image size)
     * dpi (int): dots per inch. This parameter is only taken into account if width or height are set to auto.
     * If any of these parameters is not set the width and/or height of the placeholder image will be preserved
     */
    public function addTemplateImage($var, $pathImage, $options = array())
    {
        if (!file_exists($pathImage)) {
            throw new Exception('File ' . $path . ' not exists');
        }

        $template = CreateTemplate::getInstance();
        PhpdocxLogger::logger('Assign and replace image variable ' . $var . ' in template.', 'info');
        $template->replaceImage($var, $pathImage, $options);
    }

    /**
     * Replace a variable with a text, HTML, DOCX, RTF, MHT.
     *
     * @access public
     * @example ../examples/easy/Template.php
     * @example ../examples/intermediate/Template.php
     * @param mixed $var Value of the variable. String, html or array of values
     * @param string $value Text value, type of value, CSS or text array
     *  Values type of template: list, table,
     * @param mixed $settings Template settings or content type
     *  Content types: html, rtf, docx, mht
     */
    public function addTemplateVariable($var, $value = '', $settings = '')
    {
        $template = CreateTemplate::getInstance();
        PhpdocxLogger::logger('Assign and replace text variable ' . $var . ' in template.', 'info');
        $template->replaceVariable($var, $value, $settings);
    }

    /**
     * Add a text
     *
     * @access public
     * @example ../examples/easy/Text.php
     * @example ../examples/easy/Text_columns.php
     * @example ../examples/easy/Text_cursive.php
     * @example ../examples/easy/Text_linespacing.php
     * @example ../examples/intermediate/FooterPager.php
     * @example ../examples/intermediate/Multidocument.php
     * @example ../examples/intermediate/Text.php
     * @example ../examples/advanced/Report.php
     * @param mixed $textParams if a string just the text to be included, if an
     * array is or an array of arrays with each element containing
     * the text to be inserted and their formatting properties or a an instance of WordMLFragment
     * Array values:
     * 'text' (string) the run of text to be inserted
     * 'b' (on, off)
     * 'caps' (on, off) display text in capital letters
     * 'color' (ffffff, ff0000...)
     * 'columnBreak' (before, after, both) inserts a column break before, after or both, a run of text
     * 'font' (Arial, Times New Roman...)
     * 'i' (on, off)
     * 'lineBreak' (before, after, both) inserts a line break before, after or both, a run of text
     * 'sz' (1, 2, 3...)
     * 'tab' (boolean) inserts a tab. Default value is false
     * 'spaces': number of spaces at the beguinning of the run of text
     * 'u' (none, dash, dotted, double, single, wave, words)
     * 'rtl' (on, off)
     * @param array $paragraphParams Style options to apply to the whole paragraph
     *  Values:
     * 'pStyle' (string) Word style to be used. Run parseStyles() to check all available paragraph styles
     * 'b' (on, off)
     * 'bidi' (on, off)
     * 'caps' (on, off) display text in capital letters
     * 'color' (ffffff, ff0000...)
     * 'contextualSpacing' (on, off) ignore spacing above and below when using identical styles
     * 'firstLineIndent' 100, 200, ...
     * 'font' (Arial, Times New Roman...)
     * 'hanging' 100, 200, ...
     * 'i' (on, off)
     * 'indent_left' 100...,
     * 'indent_right' 100...
     * 'jc' (both, center, distribute, left, right)
     * 'keepLines' (on, off) keep all paragraph lines on the same page
     * 'keepNext' (on, off) keep in the same page the current paragraph with next paragraph
     * 'lineSpacing' 120, 240 (standard), 360, 480, ...
     * 'pageBreakBefore' (on, off)
     * 'rawWordML' (boolean)
     * 'rtl' (on, off)
     * 'spacingBottom' (int) bottom margin in twentieths of a point
     * 'spacingTop' (int) top margin in twentieths of a point
     * 'sz' (8, 9, 10, ...) size in points
     * 'tabPositions' (array) each entry is an associative array with the following keys and values
     *      'type' (string) can be clear, left (default), center, right, decimal, bar and num
     *      'leader' (string) can be none (default), dot, hyphen, underscore, heavy and middleDot
     *      'position' (int) given in twentieths of a point
     * if there is a tab and the tabPositions array is not defined the standard tab position (default of 708) will be used
     * 'textDirection' (lrTb, tbRl, btLr, lrTbV, tbRlV, tbLrV) text flow direction
     * 'u' (none, dash, dotted, double, single, wave, words)
     * 'widowControl' (on, off)
     * 'wordWrap' (on, off)
     */
    public function addText($textParams, $paragraphParams = array('rawWordML' => false))
    {
        $paragraphParams = self::setRTLOptions($paragraphParams);
        $text = CreateText::getInstance();
        $text->createText($textParams, $paragraphParams);
        PhpdocxLogger::logger('Add text to word document.', 'info');
        if (isset($paragraphParams['rawWordML']) && $paragraphParams['rawWordML']) {
            return (string) $text;
        } else {
            $this->_wordDocumentC .= (string) $text;
        }
    }

    /**
     * Add a textbox
     *
     * @access public
     * @example ../examples/easy/TextBox.php
     * @example ../examples/intermediate/TextBox.php
     * @param array $text these are the same parameters used in the addText method
     * The first array entry is the text to be included in the text box, the second one
     * is itself another array with all the standard text formatting options
     * @param array $options includes the specific textbox options
     *  Values:
     * 'border' (int)
     * 'border_color (string) color (black, red,...) or hexadecimal value (#ff0000, #0000ff, ...)
     * 'align' (center, left, right)
     * 'fillcolor' (string) color (black, red,...) or hexadecimal value (#ff0000, #0000ff, ...)
     * 'width' (float) width in cm
     * 'height' (float) height in cm
     * 'textWrap' (tight, square, through, none)
     * 'margin_left' (float) distance in cm
     * 'margin_top' (float) distance in cm
     * 'padding_bottom' (float) distance in cm
     * 'padding_left' (float) distance in cm
     * 'padding_right' (float) distance in cm
     * 'padding_top' (float) distance in cm
     * 'rawWordML' (boolean)
     */
    public function addTextBox($text, $options = array('rawWordML' => false))
    {
        //TODO: does not support RTL
        $textBox = CreateTextBox::getInstance();
        $textBox->createTextBox($text, $options);
        PhpdocxLogger::logger('Add textbox to word document.', 'info');
        if (isset($options['rawWordML']) && $options['rawWordML']) {
            return (string) $textBox;
        } else {
            $this->_wordDocumentC .= (string) $textBox;
        }
    }

    /**
     * Adds WordML to the document.
     *
     * @access public
     * @example ../examples/easy/WordML.php
     * @param array $options
     * Values:
     * 'wordML' (string) WordML to add
     * 'rawWordML' (boolean)
     */
    public function addWordML($options = array('rawWordML' => false))
    {
        if(isset($options['rawWordML']) && $options['rawWordML']){
            $wordXML = new WordML();
            $wordXML->CreateRawWordML($options['wordML']);
            return $wordXML;
        }else{
            $this->_wordDocumentC .= (String) $options['wordML'];
        }
    }

    /**
     * @access public
     * @param string $variableName
     * @param string $type can be 'block'(default value): removes the containing paragraph or 'inline': just removes the variable.
     *
     */
    public function cleanTemplateVariable($variableName, $type='block')
    {
        if($type == 'inline'){
            $this->addTemplateVariable($variableName, '');
        }else{
            $template = CreateTemplate::getInstance();
            PhpdocxLogger::logger('Remove a template variable', 'info');
            $template->removeVariable($variableName, $type);
        }
    }

    /**
     * Eliminates all block type elements from a WordML string
     *
     * @access public
     */
    public function cleanWordMLBlockElements($wordML)
    {
        $wordMLChunk = new DOMDocument();
        $namespaces = 'xmlns:ve="http://schemas.openxmlformats.org/markup-compatibility/2006" xmlns:o="urn:schemas-microsoft-com:office:office" xmlns:r="http://schemas.openxmlformats.org/officeDocument/2006/relationships" xmlns:m="http://schemas.openxmlformats.org/officeDocument/2006/math" xmlns:v="urn:schemas-microsoft-com:vml" xmlns:wp="http://schemas.openxmlformats.org/drawingml/2006/wordprocessingDrawing" xmlns:w10="urn:schemas-microsoft-com:office:word" xmlns:w="http://schemas.openxmlformats.org/wordprocessingml/2006/main" xmlns:wne="http://schemas.microsoft.com/office/word/2006/wordml" ';
        $wordML = '<?xml version="1.0" encoding="UTF-8" standalone="yes" ?><w:root '.$namespaces.'>'.$wordML;
        $wordML = $wordML.'</w:root>';
        $wordMLChunk->loadXML($wordML);
        $wordMLXpath = new DOMXPath($wordMLChunk);
        $wordMLXpath->registerNamespace('w', 'http://schemas.openxmlformats.org/wordprocessingml/2006/main');
        $wordMLXpath->registerNamespace('m', 'http://schemas.openxmlformats.org/wordprocessingml/2006/math');
        $query= '//w:r[not(ancestor::w:hyperlink)] | //w:hyperlink | //w:bookmarkStart | //w:bookmarkEnd | //w:commentRangeStart | //w:commentRangeEnd | //m:oMath';
        $wrNodes = $wordMLXpath->query($query);
        $blockCleaned = '';
        foreach ($wrNodes as $node){
           $nodeR = $node->ownerDocument->saveXML($node);
           $blockCleaned .= $nodeR;
        }

        return $blockCleaned;
    }

    /**
     * Clear all BLOCK tags
     *
     * @access public
     */
    public function clearBlocks()
    {
        PhpdocxLogger::logger('Clear all blocks.', 'info');
        CreateTemplate::deleteAllBlocks();
    }

    /**
     * Generate a new DOCX file
     *
     * @access public
     * @example ../examples/easy/Text.php
     * @example ../examples/advanced/Report.php
     * @param string $args[0] File name
     * @param string $args[1] Page style
     *  Values: 'bottom' (4000, 4001...), 'columns' (1, 2, 3), 'left' (4000, 4001...),
     *  'orient' (landscape), 'right' (4000, 4001), 'titlePage' (1),
     *  'top' (4000, 4001)
     */
    public function createDocx()
    {
        $args = func_get_args();
        if (!empty($args[0])) {
            $fileName = $args[0];
        } else {
            $fileName = 'document';
        }
        PhpdocxLogger::logger('Set DOCX name to: ' . $fileName . '.', 'info');
        if (!CreateTemplate::getBlnTemplate()) {
            PhpdocxLogger::logger('DOCX is a new file, not a template.', 'debug');
            try {
               GenerateDocx::beginDocx();
            }
            catch (Exception $e) {
                PhpdocxLogger::logger($e->getMessage(), 'fatal');
            }

            //We copy the rels content into the respective file
            $relsHandler = fopen($this->_baseTemplateFilesPath.'/word/_rels/document.xml.rels', "w+");
            fwrite($relsHandler, $this->_wordRelsDocumentRelsT->saveXML());
            fclose($relsHandler);
            //We also copy the contents of the [Content_types].xml file
            $contentTypesHandler = fopen($this->_baseTemplateFilesPath.'/[Content_Types].xml', "w+");
            fwrite($contentTypesHandler, $this->_contentTypeT->saveXML());
            fclose($contentTypesHandler);

            $arrArgsPage = array();
            if (isset($args[1])) {
                PhpdocxLogger::logger('Modify page layout.', 'debug');
                $this->modifyPageLayout('custom', $args[1]);
            }

            $this->generateTemplateWordDocument($arrArgsPage);
            if ($this->_debug->getActive() == 1) {
                PhpdocxLogger::logger('Debug is active, add messages to objDebug.', 'debug');
                libxml_use_internal_errors(true);
                simplexml_load_string(
                    $this->_wordDocumentT, 'SimpleXMLElement', LIBXML_NOWARNING
                );
                $xmlErrors = libxml_get_errors();
                if (is_array($xmlErrors)) {
                    $this->_debug->addMessage($xmlErrors);
                    libxml_clear_errors();
                }
            }

            PhpdocxLogger::logger('Add word/document.xml content to DOCX file.', 'info');

            $documentHandler = fopen($this->_baseTemplateFilesPath.'/word/document.xml', "w+");
            if (self::$_encodeUTF) {
                $contentDocumentXML = utf8_encode($this->_wordDocumentT);
                //TODO: sot out encoding problems
                fwrite($documentHandler, utf8_encode($this->_wordDocumentT));
            } else {
                if ($this->_phpdocxconfig['settings']['encode_to_UTF8'] == 'true' && !PhpdocxUtilities::isUtf8($this->_wordDocumentT)) {
                    $contentDocumentXML = utf8_encode($this->_wordDocumentT);
                } else {
                    $contentDocumentXML = $this->_wordDocumentT;
                }
                fwrite($documentHandler, $this->_wordDocumentT);
            }
            fclose($documentHandler);

            // repair document.xml
            $repair = Repair::getInstance();
            $repair->setXML($contentDocumentXML);
            $repair->addParapraphEmptyTablesTags();
            $documentHandler = fopen($this->_baseTemplateFilesPath.'/word/document.xml', "w+");
            fwrite($documentHandler, (string)$repair);
            fclose($documentHandler);

            if (file_exists(dirname(__FILE__) . '/RepairPDF.inc')) {
                if ($this->_compatibilityMode) {
                    $contentRepairPDF = RepairPDF::repairTablesPDFConversion($contentDocumentXML);
                    $documentHandler = fopen($this->_baseTemplateFilesPath.'/word/document.xml', "w+");
                    fwrite($documentHandler, (string)$contentRepairPDF);
                    fclose($documentHandler);
                }
            }

            $numberingHandler = fopen($this->_baseTemplateFilesPath.'/word/numbering.xml', "w+");
            fwrite($numberingHandler, $this->_wordNumberingT);
            fclose($numberingHandler);

            PhpdocxLogger::logger('Close ZIP file', 'info');

            //Check if there are rels for footnotes, endnotes and comments
            if(!empty($this->_relsNotesImage['footnote']) ||
               !empty($this->_relsNotesExternalImage['footnote']) ||
               !empty($this->_relsNotesLink['footnote'])){
                $this->generateRelsNotes('footnote');
            }
            if(!empty($this->_relsNotesImage['endnote']) ||
               !empty($this->_relsNotesExternalImage['endnote']) ||
               !empty($this->_relsNotesLink['endnote'])){
                $this->generateRelsNotes('endnote');
            }
            if(!empty($this->_relsNotesImage['comment']) ||
               !empty($this->_relsNotesExternalImage['comment']) ||
               !empty($this->_relsNotesLink['comment'])){
                $this->generateRelsNotes('comment');
            }

            $this->recursiveInsert($this->_zipDocx, $this->_baseTemplateFilesPath, $this->_baseTemplateFilesPath);

            //Lets now insert the photos inserted by the embedHTML method
            if (is_dir($this->_baseTemplateFilesPath.'/word/mediaTemplate')){
                $contentsDir = scandir($this->_baseTemplateFilesPath.'/word/mediaTemplate');
                $predefinedExtensions = explode(',', PHPDOCX_ALLOWED_IMAGE_EXT);
                foreach($contentsDir as $element){
                    $arrayExtension = explode('.', $element);
                    $extension = strtolower(array_pop($arrayExtension));
                    if (in_array($extension, $predefinedExtensions)){
                        $this->_zipDocx->addFile($this->_baseTemplateFilesPath.'/word/mediaTemplate/'.$element, 'word/media/'.$element);
                    }
                    //Now we remove the image from the mediaTemplate folder
                    $this->_zipDocx->deleteName('word/mediaTemplate/'.$element);
                }
                //And now we delete the mediaTemplate folder
                $deleteMediaTemplate = $this->_zipDocx->deleteName('word/mediaTemplate/');
            }

            //Check if there are openbookmars and if so throw an error
            if (count($this->_bookmarksIds) > 0) {
                PhpdocxLogger::logger('There are unclosed bookmarks. Please, check that all open bookmarks tags are properly closed.', 'fatal');
            }


            $this->_zipDocx->close();

            $arrpathFile = pathinfo($fileName);
            PhpdocxLogger::logger('Copy DOCX file using a new name.', 'info');
            copy(
                $this->_tempFile,
                $fileName . '.' . $this->_extension
            );

            if ($this->_debug->getActive() == 1) {
                PhpdocxLogger::logger('Debug is active, show messages.', 'debug');
                echo $this->_debug;
            }
        } else {
            PhpdocxLogger::logger('DOCX is a template.', 'debug');
            PhpdocxLogger::logger('Create a temp copy of the file, to generate a new DOCX.', 'info');
            $finalFileName = $fileName . '.' . $this->_extension;
            $fileName = tempnam($this->_tempDir, $fileName);
            copy(CreateTemplate::$path, $fileName);
            $zipDocxTemplate = new ZipArchive();
            try {
                if ($zipDocxTemplate->open($fileName)) {
                    if (count(CreateTemplate::getFooter()) > 0) {
                        $footers = CreateTemplate::getFooter();
                        foreach ($footers as $key => $footer) {
                            PhpdocxLogger::logger('Footer exists, replace ' . $key . ' with a new footer.', 'info');
                            $zipDocxTemplate->addFromString($key, $footer);
                        }
                    }
                    if (count(CreateTemplate::getHeader()) > 0) {
                        $headers = CreateTemplate::getHeader();
                        foreach ($headers as $key => $header) {
                            PhpdocxLogger::logger('Footer exists, replace ' . $key . ' with a new header.', 'info');
                            $zipDocxTemplate->addFromString($key, $header);
                        }
                    }
                    if (CreateTemplate::getRelsDocumentXMLRels() != '') {
                        PhpdocxLogger::logger('Document.xml.rels exists, replace word/_rels/' .
                            'document.xml.rels with a new document.', 'info');
                        $zipDocxTemplate->addFromString(
                            'word/_rels/document.xml.rels',
                            CreateTemplate::getRelsDocumentXMLRels()
                        );
                    }
                    if (count(CreateTemplate::$placeholderImages) > 0) {
                        PhpdocxLogger::logger('There is one or more images as placeholders, . ' .
                            'replace them.', 'info');
                        CreateTemplate::replaceImages($zipDocxTemplate);
                    }
                    if (count(CreateTemplate::$placeholderHeaderImages) > 0) {
                        PhpdocxLogger::logger('There is one or more images in the header as placeholders, . ' .
                            'replace them.', 'info');
                        CreateTemplate::replaceHeaderMediaImages($zipDocxTemplate);
                    }
                    if (CreateTemplate::$totalTemplateCharts > 0) {
                        PhpdocxLogger::logger('There is one or more charts as placeholders, . ' .
                            'replace them.', 'info');
                        for ($i = CreateTemplate::$ridInitTemplateCharts + 1;
                            $i <= self::$intIdWord; $i++
                        ) {
                            $zipDocxTemplate->addFromString(
                                'word/charts/chart' . $i . '.xml',
                                $this->graphicTemplate['arrChartXML'][$i]
                            );
                            CreateTemplate::replaceVariableChart(
                                $this->graphicTemplate['arrGraphics'][$i],
                                $i
                            );
                            $zipDocxTemplate->addFile(
                                $this->_tempFileXLSX[$i],
                                $this->fileGraphicTemplate['datos' . $i . '.xlsx']
                            );
                            $zipDocxTemplate->addFromString(
                                'word/charts/_rels/chart' . $i . '.xml.rels',
                                $this->fileGraphicTemplate['word/charts/_rels/chart' . $i . '.xml.rels']
                            );

                            CreateTemplate::addContentTypes(
                                $this->graphicTemplate['arrGenerateOVERRIDE'][$i]
                            );
                            CreateTemplate::addContentTypes(
                                $this->graphicTemplate['arrGenerateDEFAULT'][$i]
                            );
                            CreateTemplate::addRelationship(
                                $this->graphicTemplate['arrRelationships'][$i]
                            );
                        }

                    }
                    PhpdocxLogger::logger('Replace [Content_Types].xml with a new document.', 'info');
                    $zipDocxTemplate->addFromString(
                        '[Content_Types].xml',
                        CreateTemplate::getContentTypes()
                    );
                    PhpdocxLogger::logger('Replace word/_rels/document.xml.rels with a new ' .
                        'document.', 'info');
                    $zipDocxTemplate->addFromString(
                        'word/_rels/document.xml.rels',
                        CreateTemplate::getRelsDocumentXMLRels()
                    );
                    $this->_wordNumberingT = CreateTemplate::getNumbering();
                    if($this->_wordNumberingT == ''){
                        $this->_wordNumberingT = $this->generateBaseWordNumbering();
                    }

                    $this->_wordNumberingT = $this->importSingleNumbering($this->_wordNumberingT, self::$unorderedListStyle, self::$numUL);
                    if(is_array($this->_templateNumberings)){
                    foreach($this->_templateNumberings as $value){
                        $this->_wordNumberingT = $this->importSingleNumbering($this->_wordNumberingT, self::$orderedListStyle, $value);
                     }
                    }
                    //We should also take care of the custom lists if they exist
                    if (is_array($this->_templateCustomNumberings)) {
                        foreach($this->_templateCustomNumberings as $value){
                            $this->_wordNumberingT = $this->importSingleNumbering($this->_wordNumberingT,
                                                                                  self::$customLists[$value['name']]['wordML'],
                                                                                  $value['id']);
                        }
                    }

                    $zipDocxTemplate->addFromString(
                        'word/numbering.xml',
                        $this->_wordNumberingT
                    );
                    $this->_wordStylesT = CreateTemplate::getStyles();
                    $importingStyles = new DOMDocument();
                    $importingStyles->loadXML(self::$PHPDOCXStyles);
                    $this->_wordStylesT = $this->addStylesTemplate($this->_wordStylesT, $importingStyles);

                    $zipDocxTemplate->addFromString(
                        'word/styles.xml',
                        $this->_wordStylesT
                    );

                    PhpdocxLogger::logger('Replace word/document.xml with a new document.', 'info');
                    if (self::$_encodeUTF) {
                        $contentDocumentXML = utf8_encode(CreateTemplate::getDocument());
                        $zipDocxTemplate->addFromString(
                            'word/document.xml',
                            utf8_encode(CreateTemplate::getDocument())
                        );
                    } else {
                        if ($this->_phpdocxconfig['settings']['encode_to_UTF8'] == 'true' && !PhpdocxUtilities::isUtf8(CreateTemplate::getDocument())) {
                            $contentDocumentXML = utf8_encode(CreateTemplate::getDocument());
                            $zipDocxTemplate->addFromString(
                                'word/document.xml', utf8_encode(CreateTemplate::getDocument())
                            );
                        } else {
                            $contentDocumentXML = CreateTemplate::getDocument();
                            $zipDocxTemplate->addFromString(
                                'word/document.xml', CreateTemplate::getDocument()
                            );
                        }
                    }
                    PhpdocxLogger::logger('Add embedded files.', 'info');
                    foreach (CreateTemplate::$embedFiles as $files) {
                        if (isset($files['src_string'])) {
                            $zipDocxTemplate->addFromString(
                                'word/' . $files['dest_file'], $files['src_string']
                            );
                        } elseif (isset($files['src_file'])) {
                            $zipDocxTemplate->addFile($files['src_file'], 'word/' . $files['dest_file']);
                        }
                    }
                    //Lets now insert the photos inserted by the replaceTemplateVariableByHTML
                    if(is_dir($this->_baseTemplateFilesPath.'/word/mediaTemplate')){

                        $contentsDir = scandir($this->_baseTemplateFilesPath.'/word/mediaTemplate');
                        $predefinedExtensions = array('gif', 'png', 'jpg', 'jpeg', 'bmp');
                        foreach($contentsDir as $element){
                            $arrayExtension = explode('.', $element);
                            $extension = strtolower(array_pop($arrayExtension));
                            if (in_array($extension, $predefinedExtensions)){
                                $zipDocxTemplate->addFile($this->_baseTemplateFilesPath.'/word/mediaTemplate/'.$element, 'word/media/'.$element);
                            }
                        }
                    }
                    PhpdocxLogger::logger('End of file, close it.', 'info');

                    // repair document.xml
                    $repair = Repair::getInstance();
                    $repair->setXML($contentDocumentXML);
                    $repair->addParapraphEmptyTablesTags();
                    $zipDocxTemplate->addFromString(
                        'word/document.xml', (string)$repair
                    );

                    $zipDocxTemplate->close();
                    copy($fileName, $finalFileName);
                    // delete temp file
                    CleanTemp::clean($fileName);
                    CleanTemp::clean($this->_baseTemplateFilesPath);

                } else {
                    throw new Exception('Unable to create DOCX file.');
                }
                CreateTemplate::reset();
            }
            catch (Exception $e) {
                PhpdocxLogger::logger($e->getMessage(), 'fatal');
            }
        }
        // delete temp file charts
        foreach ($this->_tempFileXLSX as $xlsxFile) {
            CleanTemp::clean($xlsxFile);
        }
        // delete temp file
        CleanTemp::clean($this->_tempFile);
        CleanTemp::clean($this->_baseTemplateFilesPath);
    }

    /**
     * Generate and download a new DOCX file
     *
     * @access public
     * @param string $args[0] File name
     * @param string $args[1] Page style
     *  Values: 'bottom' (4000, 4001...), 'left' (4000, 4001...),
     *  'orient' (landscape), 'right' (4000, 4001), 'titlePage' (1),
     *  'top' (4000, 4001)
     * @param string $args[2] Download file name
     */
    public function createDocxAndDownload()
    {
        $args = func_get_args();

        try {
            if (isset($args[1])) {
                $this->createDocx($args[0], $args[1]);
            } else {
                $this->createDocx($args[0]);
            }
        }
        catch (Exception $e) {
            PhpdocxLogger::logger($e->getMessage(), 'fatal');
        }

        if (!empty($args[0])) {
            $fileName = $args[0];
            $completeName = explode("/",$args[0]);
            $fileNameDownload = array_pop($completeName);
        } else {
            $fileName = 'document';
            $fileNameDownload = 'document';
        }

        if (!empty($args[2])) {
            $fileNameDownload = $args[2];
        } else {
            $fileNameDownload = 'document.docx';
        }

        PhpdocxLogger::logger('Download file ' . $fileNameDownload . '.' . $this->_extension . '.', 'info');
        header(
            'Content-Type: application/vnd.openxmlformats-officedocument.' .
            'wordprocessingml.document'
        );
        header(
            'Content-Disposition: attachment; filename="' . $fileNameDownload . '"'
        );
        header('Content-Transfer-Encoding: binary');
        header('Content-Length: ' . filesize($fileName . '.' . $this->_extension));
        readfile($fileName . '.' . $this->_extension);
    }

    /**
     * Delete a block of content markep up between BLOCK tags
     *
     * @access public
     * @param string $blockName Block to remove
     */
    public function deleteTemplateBlock($blockName)
    {
        PhpdocxLogger::logger('Delete block ' . $blockName . '.', 'info');
        CreateTemplate::deleteBlock($blockName);
    }

    /**
     * Disable debug mode
     *
     * @access public
     * @deprecated
     */
    public function disableDebug()
    {
        PhpdocxLogger::logger('Disable debug', 'info');
        $this->_debug->disableDebug();
    }

    /**
     * Stablish the general docx settings in settings.xml
     *
     * @access public
     * @example ../examples/easy/Settings.php
     * @param array settings
     * Keys and values:
     * 'view' (string): none(default), print, outline, masterPages, normal (draft view), web
     * 'zoom'(mixed): a percentage or none, fullPage (display one full page), bestFit (display page width), textFit (display text width)
     * 'mirrorMargins' (bool) if true interchanges inside and outside margins in odd and even pages
     * 'bordersDoNotSurroundHeader' (bool)
     * 'bordersDoNotSurroundFooter' (bool)
     * 'gutterAtTop' (bool)
     * 'hideSpellingErrors' (bool)
     * 'hideGrammaticalErrors' (bool)
     * 'documentType' (string): notSpecified (default), letter, eMail
     * 'trackRevisions' (bool)
     * 'defaultTabStop'(int) in twips (twentieths of a point)
     * 'autoHyphenation' (bool)
     * 'consecutiveHyphenLimit'(int): maximum number of consecutively hyphenated lines
     * 'hyphenationZone' (int) distance in twips (twentieths of a point)
     * 'doNotHyphenateCaps' (bool): do not hyphenate capital letters
     * 'defaultTableStyle' (string): the table style to be used by default
     * 'bookFoldRevPrinting' (bool): reverse book fold printing
     * 'bookFoldPrinting' (bool): book fold printing
     * 'bookFoldPrintingSheets' (int): number of pages per booklet
     * 'doNotShadeFormData' (bool)
     * 'noPunctuationKerning' (bool): never kern punctuation characters
     * 'printTwoOnOne' (bool): print two pages per sheet
     * 'savePreviewPicture' (bool): generate thumbnail for document on save
     * 'updateFields' (bool): automatically recalculate fields on open
     *
     * @return void
     */
    public function docxSettings($settingParameters)
    {
         $settingParams = array(
                 'view',
                 'zoom',
                 'mirrorMargins',
                 'bordersDoNotSurroundHeader',
                 'bordersDoNotSurroundFooter',
                 'gutterAtTop',
                 'hideSpellingErrors',
                 'hideGrammaticalErrors',
                 'documentType',
                 'trackRevisions',
                 'defaultTabStop',
                 'autoHyphenation',
                 'consecutiveHyphenLimit',
                 'hyphenationZone',
                 'doNotHyphenateCaps',
                 'defaultTableStyle',
                 'bookFoldRevPrinting',
                 'bookFoldPrinting',
                 'bookFoldPrintingSheets',
                 'doNotShadeFormData',
                 'noPunctuationKerning',
                 'printTwoOnOne',
                 'savePreviewPicture',
                 'updateFields'
            );
        try{
            $settings = fopen($this->_baseTemplateFilesPath.'/word/settings.xml', "r");
            $baseTemplateSettingsT = fread($settings, 1000000);
            fclose($settings);
            if ($baseTemplateSettingsT == '') {
                throw new Exception('Error while extracting settings.xml file from the base template to insert the selected element');
            }
        }
        catch (Exception $e) {
            PhpdocxLogger::logger($e->getMessage(), 'fatal');
        }

        $this->_wordSettingsT = new DOMDocument();
        $this->_wordSettingsT->loadXML($baseTemplateSettingsT);
        foreach($settingParameters as $tag => $value){
            if((!in_array($tag, $settingParams))){
               PhpdocxLogger::logger('That setting tag is not supported.', 'info');
            }else{
            $settingIndex = array_search('w:' . $tag, self::$settings);
            $selectedElements = $this->_wordSettingsT->documentElement->getElementsByTagName($tag);
            if($selectedElements->length == 0){
                $settingsElement = $this->_wordSettingsT->createDocumentFragment();
                if($tag == 'zoom'){
                    if(is_integer($value)){
                        $settingsElement->appendXML('<w:' . $tag . ' xmlns:w="http://schemas.openxmlformats.org/wordprocessingml/2006/main" w:percent = "' . $value . '"/>');
                    }else{
                        $settingsElement->appendXML('<w:' . $tag . ' xmlns:w="http://schemas.openxmlformats.org/wordprocessingml/2006/main" w:val = "' . $value . '"/>');
                    }
                }else{
                    $settingsElement->appendXML('<w:' . $tag . ' xmlns:w="http://schemas.openxmlformats.org/wordprocessingml/2006/main" w:val = "' . $value . '"/>');
                }
                $childNodes = $this->_wordSettingsT->documentElement->childNodes;
                $index = false;
                foreach($childNodes as $node){
                    $name = $node->nodeName;
                    $index = array_search($node->nodeName, self::$settings);
                    if($index > $settingIndex){
                        $node->parentNode->insertBefore($settingsElement, $node);
                        break;
                    }
                }
                //in case no node was found (pretty unlikely)we should append the node
                if (!$index) {
                    $this->_wordSettingsT->documentElement->appendChild($settingsElement);
                    }

                }else{//that setting is already present
                    if($tag == 'zoom'){
                        $selectedElements->item(0)->removeAttribute('w:val');
                        $selectedElements->item(0)->removeAttribute('w:percent');
                        if(is_integer($value)){
                            $selectedElements->item(0)->setAttribute('w:percent', $value);
                        }else{
                            $selectedElements->item(0)->setAttribute('w:val', $value);
                        }
                    }else{
                       $selectedElements->item(0)->setAttribute('w:val', $value);
                    }
                }
            }
        }
        $newSettings = $this->_wordSettingsT->saveXML();
        $settingsHandle = fopen($this->_baseTemplateFilesPath.'/word/settings.xml', "w+");
        $contents = fwrite($settingsHandle, $newSettings);
        fclose($settingsHandle);
    }

    /**
     *
     * Transform a word document to a text file
     *
     * @example ../examples/easy/Docx2Text.php
     * @param string $path. Path to the docx from which we wish to import the content
     * @param string $path. Path to the text file output
     * @param array styles.
     * keys: table => true/false,list => true/false, paragraph => true/false, footnote => true/false, endnote => true/false, chart => (0=false,1=array,2=table)
     */
    public static function docx2txt($from, $to, $options = array()) {
        $text = new Docx2Text($options);
        $text->setDocx($from);
        $text->extract($to);
    }

    /**
     * Embed HTML into the Word document by parsing the HTML code and converting it into WordML
     * It preserves many CSS styles
     *
     * @access public
     * @example ../examples/easy/EmbedSimpleHTML.php
     * @example ../examples/intermediate/EmbedExternalHTML.php
     * @example ../examples/intermediate/EmbedHTMLinTable.php
     * @param string $html HTML to add. Must be a valid XHTML
     * @param array $options:
     * isFile (boolean),
     * baseURL (string),
     * customListStyles (bool) if true try to use the predefined customm lists
     * downloadImages (boolean),
     * filter (string) could be an string denoting the id, class or tag to be filtered.
     * If you want only a class introduce .classname, #idName for an id or <htmlTag> for a particular tag. One can also use
     * standard XPath expresions supported by PHP.
     * 'parseAnchors' (boolean),
     * 'parseDivs' (paragraph, table): parses divs as paragraphs or tables,
     * 'parseFloats' (boolean),
     * 'strictWordStyles' (boolean) if true ignores all CSS styles and uses the styles set via the wordStyles option (see next)
     * 'wordStyles' (array) associates a particular class, id or HTML tag to a Word style
     * 'target' (string) document (default value), defaultHeader, firstHeader, evenHeader, defaultFooter, firstFooter, evenFooter, footnote, endnote and or comment.
     * 'rawWordML' (boolean)
     */
    public function embedHTML($html = '<html><body></body></html>', $options = array())
    {
        if(!isset($options['target'])){
           $options['target'] = 'document';
        }
        if (!class_exists('Tidy')) {
            PhpdocxLogger::logger('Tidy is not installed. Htmlawed library will be used to clean the HTML.', 'warning');
        }

        $htmlDOCX = new HTML2WordML($this->_baseTemplateFilesPath);
        $sFinalDocX = $htmlDOCX->render($html, $options);
        PhpdocxLogger::logger('Add converted HTML to word document.', 'info');

        $this->HTMLRels($sFinalDocX, $options);
        //We should also take care of the ordered lsit if they exist
        if (is_array($sFinalDocX[3])) {
            foreach($sFinalDocX[3] as $value){
                $this->_wordNumberingT = $this->importSingleNumbering($this->_wordNumberingT, self::$orderedListStyle, $value);
            }
        }
        //We should also take care of the custom lists if they exist
        if (is_array($sFinalDocX[4])) {
            foreach($sFinalDocX[4] as $value){
                //We have to remove from the name the random indentifier
                $realNameArray =explode('_', $value['name']);
                $value['name'] = $realNameArray[0];
                $this->_wordNumberingT = $this->importSingleNumbering($this->_wordNumberingT,
                                                                      self::$customLists[$value['name']]['wordML'],
                                                                      $value['id']);
            }
        }

        if (isset($options['rawWordML']) && $options['rawWordML'] === true) {
            return (string) $sFinalDocX[0];
        } else {
            $this->_wordDocumentC .= (string) $sFinalDocX[0];
        }

    }

    /**
     * Enable compatibility mode for OpenOffice and MS Office 2003 CP. Avoid using unsupported methods
     *
     * @access public
     */
    public function enableCompatibilityMode()
    {
        PhpdocxLogger::logger('Enable compatibility mode.', 'info');
        $this->_compatibilityMode = true;
    }

    /**
     * Enable debug mode
     *
     * @access public
     * @deprecated
     */
    public function enableDebug()
    {
        PhpdocxLogger::logger('Enable debug.', 'info');
        $this->_debug->enableDebug();
    }

  /**
     * Return template variables (placeholders)
     *
     * @access public
     * @example ../examples/easy/Template_variables.php
     * @return array
     */
    public function getTemplateVariables()
    {
        $template = CreateTemplate::getInstance();
        PhpdocxLogger::logger('Return template variables.', 'info');
        return $template->returnAllVariables();
    }

    /**
     * Return the XML of the given Template
     *
     * @access public
     * @return array
     */
    public function getTemplateXML()
    {
        $templateXML = CreateXML::getInstance();
        PhpdocxLogger::logger('Return the XML of the given Template.', 'info');
        self::getTemplateVariables();

        $templateXML->XML();

        return $templateXML->getXML();
    }

    /**
     * Imports an existing style sheet from an existing docx document.
     *
     * @access public
     * @example ../examples/easy/ImportWordStyles.php
     * @param string $path. Must be a valid path to an existing .docx, .dotx o .docm document
     * @param string $type. You may choose 'replace' (overwrites the current styles) or 'merge' (adds the selected styles)
     * @param array $myStyles. A list of specific styles to be merged. If it is empty or the choosen type is 'replace' it will be ignored.
     */
    public function importStyles($path, $type= 'replace', $myStyles= array(), $styleIdentifier = 'styleName')
    {
        $zipStyles = new ZipArchive();
       try {
        $openStyle = $zipStyles->open($path);
        if ($openStyle !== true) {
           throw new Exception('Error while opening the Style Template: please, check the path');
         }
        }
        catch (Exception $e) {
            PhpdocxLogger::logger($e->getMessage(), 'fatal');
        }
        if ($type == 'replace') {
            //Now we overwrite the original styles file
            try {
                $extractingStyleFile = $zipStyles->extractTo($this->_baseTemplateFilesPath.'/','word/styles.xml');
                if (!$extractingStyleFile) {
                    throw new Exception('Error while trying to overwrite the styles.xml of the base template');
                }
            }
            catch (Exception $e) {
                PhpdocxLogger::logger($e->getMessage(), 'fatal');
            }
            //In order not to loose certain styles needed for certain PHPDOCX methods we should merge them
            $this->importStyles(PHPDOCX_BASE_TEMPLATE, 'merge', $this->_defaultPHPDOCXStyles);
        } else {
            //We will first extract the new styles from the external docx
            try {
                $newStyles = $zipStyles->getFromName('word/styles.xml');
                if ($newStyles == '') {
                    throw new Exception('Error while extracting the styles from the external docx');
                }
            }
            catch (Exception $e) {
                PhpdocxLogger::logger($e->getMessage(), 'fatal');
            }
        //let's parse the different styles via XPath
        $newStylesDoc = new DOMDocument();
        $newStylesDoc->loadXML($newStyles);
        $stylesXpath = new DOMXPath($newStylesDoc);
        $stylesXpath->registerNamespace('w', 'http://schemas.openxmlformats.org/wordprocessingml/2006/main');
        $queryStyle = '//w:style';
        $styleNodes = $stylesXpath->query($queryStyle);

        //Let's get the original styles as a DOMdocument
        try{
            $styleHandler = fopen($this->_baseTemplateFilesPath.'/word/styles.xml', 'r');
            $styleXML = fread($styleHandler, filesize($this->_baseTemplateFilesPath.'/word/styles.xml'));
            fclose($styleHandler);
            $this->_wordStylesT = $styleXML;
            if ($styleXML == '') {
                throw new Exception('Error while extracting the style file from the base template');
            }
        }
        catch (Exception $e) {
            PhpdocxLogger::logger($e->getMessage(), 'fatal');
        }
        $stylesDocument = new DomDocument();
        $stylesDocument->loadXML($this->_wordStylesT);
        $baseNode = $stylesDocument->documentElement;
        $stylesDocumentXPath = new DOMXPath($stylesDocument);
        $stylesDocumentXPath->registerNamespace('w', 'http://schemas.openxmlformats.org/wordprocessingml/2006/main');
        $query = '//w:style';
        $originalNodes = $stylesDocumentXPath->query($query);

        //Now we start to insert the new styles at the end of the styles.xml
        foreach($styleNodes as $node){
           // in order to avoid duplicated Ids we first remove from the
           // original styles.xml any duplicity with the new ones
           // TODO: check performance
            foreach($originalNodes as $oldNode){
                if($styleIdentifier == 'styleID'){
                    if($oldNode->getAttribute('w:styleId') == $node->getAttribute('w:styleId')
                       &&  in_array($oldNode->getAttribute('w:styleId'), $myStyles)){
                        $oldNode->parentNode->removeChild($oldNode);
                    }
                }else{
                    $oldName = $oldNode->getElementsByTagName('w:name');
                    if($oldNode->getAttribute('w:styleId') == $node->getAttribute('w:styleId')
                       &&  in_array($oldName, $myStyles)){
                        $oldNode->parentNode->removeChild($oldNode);
                    }
                }
            }
           if(count($myStyles)>0){
               //Lets insert the selected styles
               if($styleIdentifier == 'styleID'){
                   if(in_array($node->getAttribute('w:styleId'), $myStyles)){
                    $insertNode = $stylesDocument->importNode($node, true);
                    $baseNode->appendChild($insertNode);
                   }
               }else{
               $nodeChilds = $node->childNodes;
               foreach($nodeChilds as $child){
                   if ($child->nodeName == 'w:name'){
                       $styleName = $child->getAttribute('w:val');
                       if(in_array($styleName, $myStyles)){
                        $insertNode = $stylesDocument->importNode($node, true);
                        $baseNode->appendChild($insertNode);
                       }
                    }
                  }
               }
           }else{
           $insertNode = $stylesDocument->importNode($node, true);
           $baseNode->appendChild($insertNode);
           }
        }
        $this->_wordStylesT = $stylesDocument->saveXML();
        try {
            $stylesFile=fopen($this->_baseTemplateFilesPath.'/word/styles.xml', 'w');
            if ($stylesFile == false) {
                throw new Exception('Error while opening the base template styles.xml file');
            }
        } catch (Exception $e) {
            PhpdocxLogger::logger($e->getMessage(), 'fatal');
        }
        try {
            $writeStyles = fwrite($stylesFile,$this->_wordStylesT);
            if ($writeStyles == 0) {
                throw new Exception('There were no new styles written');
            }
        } catch (Exception $e) {
            PhpdocxLogger::logger($e->getMessage(), 'fatal');
        }

      }
      PhpdocxLogger::logger('Importing styles from an external docx.', 'info');
    }

    /**
     * Imports an existing theme from an existing docx document.
     *
     * @access public
     * @param string $path. Must be a valid path to an existing .docx, .dotx o .docm document
     */
    public function importThemeXML($path){
        try {
            $zipTheme = new ZipArchive();
            $extractingThemeFile = $zipTheme->extractTo($this->_baseTemplateFilesPath.'/','word/theme/theme1.xml');
            if (!$extractingThemeFile) {
                throw new Exception('Error while trying to overwrite the theme1.xml of the base template');
            }
        }
        catch (Exception $e) {
            PhpdocxLogger::logger($e->getMessage(), 'fatal');
        }
    }

    /**
     * Imports an existing webSettings.xml file from an existing docx document.
     *
     * @access public
     * @param string $path. Must be a valid path to an existing .docx, .dotx o .docm document
     */
    public function importWebSettingsXML($path){
        try {
            $zipWebSettings = new ZipArchive();
            $extractingWebSettingsFile = $zipTheme->extractTo($this->_baseTemplateFilesPath.'/','word/webSettings.xml');
            if (!$extractingWebSettingsFile) {
                throw new Exception('Error while trying to overwrite the webSettings.xml of the base template');
            }
        }
        catch (Exception $e) {
            PhpdocxLogger::logger($e->getMessage(), 'fatal');
        }
    }

    /**
     * Imports an existing settings.xml file from an existing docx document.
     *
     * @access public
     * @param string $path. Must be a valid path to an existing .docx, .dotx o .docm document
     */
    public function importSettingsXML($path){
        try {
            $zipSettings = new ZipArchive();
            $extractingSettingsFile = $zipTheme->extractTo($this->_baseTemplateFilesPath.'/','word/settings.xml');
            if (!$extractingSettingsFile) {
                throw new Exception('Error while trying to overwrite the settings.xml of the base template');
            }
        }
        catch (Exception $e) {
            PhpdocxLogger::logger($e->getMessage(), 'fatal');
        }
    }

    /**
     * Imports an existing fontTable.xml file from an existing docx document.
     *
     * @access public
     * @param string $path. Must be a valid path to an existing .docx, .dotx o .docm document
     */
    public function importFontTableXML($path){
        try {
            $zipFontTable = new ZipArchive();
            $extractingFontTableFile = $zipTheme->extractTo($this->_baseTemplateFilesPath.'/','word/fontTable.xml');
            if (!$extractingFontTableFile) {
                throw new Exception('Error while trying to overwrite the fontTable.xml of the base template');
            }
        }
        catch (Exception $e) {
            PhpdocxLogger::logger($e->getMessage(), 'fatal');
        }
    }

    /**
     * Modify the value of a series of input fields.
     *
     * @access public
     * @example ../examples/easy/ModifyInputFields.php
     * @param array $data With the key, the name of the variable and the value the value of the input text
     */
    public function modifyInputFields($data)
    {
        $template = CreateTemplate::getInstance();
        PhpdocxLogger::logger('Modify input field', 'info');
        $template->modifyInputText($data);
    }

    /**
     * Modify page layout
     *
     * @access public
     * @example ../examples/intermediate/modifyPageLayout.php
     * @param array paperType (string): A4, A3, letter, legal, A4-landscape, A3-landscape, letter-landscape, legal-landscape, custom
     * @param array options
     * Values:
     * width (int): measurement in twips (twentieths of a point)
     * height (int): measurement in twips (twentieths of a point)
     * numberCols (int): integer
     * orient (string): portrait, landscape
     * marginTop (int): measurement in twips (twentieths of a point)
     * marginRight (int): measurement in twips (twentieths of a point)
     * marginBottom (int): measurement in twips (twentieths of a point)
     * marginLeft (int): measurement in twips (twentieths of a point)
     * marginHeader (int): measurement in twips (twentieths of a point)
     * marginFooter (int): measurement in twips (twentieths of a point)
     * gutter (int): measurement in twips (twentieths of a point)
     * bidi (on, off): set to 'on' for right to left languages
     * rtlGutter (on, off): set to 'on' for right to left languages
     */
    public function modifyPageLayout($paperType = 'letter', $options = array())
    {
       $options = self::setRTLOptions($options);
       $paperTypes = array('A4',
                            'A3',
                            'letter',
                            'legal',
                            'A4-landscape',
                            'A3-landscape',
                            'letter-landscape',
                            'legal-landscape',
                            'custom');

        $layoutOptions = array( 'width',
                                'height',
                                'numberCols',
                                'orient',
                                'code',
                                'marginTop',
                                'marginRight',
                                'marginBottom',
                                'marginLeft',
                                'marginHeader',
                                'marginFooter',
                                'gutter',
                                'bidi',
                                'rtlGutter');
        $referenceSizes = array(
                'A4' => array(
                            'width' => '11906',
                            'height' => '16838',
                            'numberCols' => '1',
                            'orient' => 'portrait',
                            'code' => '9',
                            'marginTop' => '1417',
                            'marginRight' => '1701',
                            'marginBottom' => '1417',
                            'marginLeft' => '1701',
                            'marginHeader' => '708',
                            'marginFooter' => '708',
                            'gutter' => '0'
                        ),
                'A4-landscape' => array(
                            'width' => '16838',
                            'height' => '11906',
                            'numberCols' => '1',
                            'orient' => 'landscape',
                            'code' => '9',
                            'marginTop' => '1701',
                            'marginRight' => '1417',
                            'marginBottom' => '1701',
                            'marginLeft' => '1417',
                            'marginHeader' => '708',
                            'marginFooter' => '708',
                            'gutter' => '0'
                        ),
                'A3' => array(
                            'width' => '16839',
                            'height' => '23814',
                            'numberCols' => '1',
                            'orient' => 'portrait',
                            'code' => '8',
                            'marginTop' => '1417',
                            'marginRight' => '1701',
                            'marginBottom' => '1417',
                            'marginLeft' => '1701',
                            'marginHeader' => '708',
                            'marginFooter' => '708',
                            'gutter' => '0'
                        ),
                'A3-landscape' => array(
                            'width' => '23814',
                            'height' => '16839',
                            'numberCols' => '1',
                            'orient' => 'landscape',
                            'code' => '8',
                            'marginTop' => '1701',
                            'marginRight' => '1417',
                            'marginBottom' => '1701',
                            'marginLeft' => '1417',
                            'marginHeader' => '708',
                            'marginFooter' => '708',
                            'gutter' => '0'
                        ),
                'letter' => array(
                            'width' => '12240',
                            'height' => '15840',
                            'numberCols' => '1',
                            'orient' => 'portrait',
                            'code' => '1',
                            'marginTop' => '1417',
                            'marginRight' => '1701',
                            'marginBottom' => '1417',
                            'marginLeft' => '1701',
                            'marginHeader' => '708',
                            'marginFooter' => '708',
                            'gutter' => '0'
                        ),
                'letter-landscape' => array(
                            'width' => '15840',
                            'height' => '12240',
                            'numberCols' => '1',
                            'orient' => 'landscape',
                            'code' => '1',
                            'marginTop' => '1701',
                            'marginRight' => '1417',
                            'marginBottom' => '1701',
                            'marginLeft' => '1417',
                            'marginHeader' => '708',
                            'marginFooter' => '708',
                            'gutter' => '0'
                        ),
                'legal' => array(
                            'width' => '12240',
                            'height' => '20160',
                            'numberCols' => '1',
                            'orient' => 'portrait',
                            'code' => '5',
                            'marginTop' => '1417',
                            'marginRight' => '1701',
                            'marginBottom' => '1417',
                            'marginLeft' => '1701',
                            'marginHeader' => '708',
                            'marginFooter' => '708',
                            'gutter' => '0'
                        ),
                'legal-landscape' => array(
                            'width' => '20160',
                            'height' => '12240',
                            'numberCols' => '1',
                            'orient' => 'landscape',
                            'code' => '5',
                            'marginTop' => '1701',
                            'marginRight' => '1417',
                            'marginBottom' => '1701',
                            'marginLeft' => '1417',
                            'marginHeader' => '708',
                            'marginFooter' => '708',
                            'gutter' => '0'
                        ),
            );

        try {
            if(!in_array($paperType, $paperTypes)) {
                throw new Exception('You have used an invalid paper size');
            }
        }
        catch (Exception $e) {
            PhpdocxLogger::logger($e->getMessage(), 'fatal');
        }


        $layout = array();
        foreach ($layoutOptions as $opt) {
            if (isset($referenceSizes[$paperType][$opt])) {
               $layout[$opt] = $referenceSizes[$paperType][$opt];
            }
        }
        foreach ($layoutOptions as $opt) {
            if (isset($options[$opt])) {
               $layout[$opt] = $options[$opt];
            }
        }
        if (isset($layout['width'])) {
            $this->_sectPr->getElementsByTagName('pgSz')->item(0)->setAttribute('w:w', $layout['width']);
        }
        if (isset($layout['height'])) {
            $this->_sectPr->getElementsByTagName('pgSz')->item(0)->setAttribute('w:h', $layout['height']);
        }
        if (isset($layout['orient'])) {
            $this->_sectPr->getElementsByTagName('pgSz')->item(0)->setAttribute('w:orient', $layout['orient']);
        }
        if (isset($layout['code'])) {
            $this->_sectPr->getElementsByTagName('pgSz')->item(0)->setAttribute('w:code', $layout['code']);
        }
        if (isset($layout['marginTop'])) {
            $this->_sectPr->getElementsByTagName('pgMar')->item(0)->setAttribute('w:top', $layout['marginTop']);
        }
        if (isset($layout['marginRight'])) {
            $this->_sectPr->getElementsByTagName('pgMar')->item(0)->setAttribute('w:right', $layout['marginRight']);
        }
        if (isset($layout['marginBottom'])) {
            $this->_sectPr->getElementsByTagName('pgMar')->item(0)->setAttribute('w:bottom', $layout['marginBottom']);
        }
        if (isset($layout['marginLeft'])) {
            $this->_sectPr->getElementsByTagName('pgMar')->item(0)->setAttribute('w:left', $layout['marginLeft']);
        }
        if (isset($layout['marginHeader'])) {
            $this->_sectPr->getElementsByTagName('pgMar')->item(0)->setAttribute('w:header', $layout['marginHeader']);
        }
        if (isset($layout[$paperType]['marginFooter'])) {
            $this->_sectPr->getElementsByTagName('pgMar')->item(0)->setAttribute('w:footer', $layout['marginFooter']);
        }
        if (isset($layout['gutter'])) {
            $this->_sectPr->getElementsByTagName('pgMar')->item(0)->setAttribute('w:gutter', $layout['gutter']);
        }

        if (isset($layout['bidi'])) {
            $bidiNodes = $this->_sectPr->getElementsByTagName('bidi');

            if($bidiNodes->length > 0){
                $bidiNodes->item(0)->setAttribute('w:val', $layout['bidi']);
            }else{
               $bidi = $this->_sectPr->createElementNS('http://schemas.openxmlformats.org/wordprocessingml/2006/main', 'w:bidi');
               $bidi->setAttributeNS('http://schemas.openxmlformats.org/wordprocessingml/2006/main', 'w:val', $layout['bidi']);
               $this->_sectPr->documentElement->appendChild($bidi);
            }
        }
        if (isset($layout['rtlGutter'])) {
            $bidiNodes = $this->_sectPr->getElementsByTagName('w:rtlGutter');
            if($bidiNodes->length > 0){
                $bidiNodes->item(0)->setAttribute('w:val', $layout['rtlGutter']);
            }else{
               $bidi = $this->_sectPr->createElementNS('http://schemas.openxmlformats.org/wordprocessingml/2006/main','w:rtlGutter');
               $bidi->setAttributeNS('http://schemas.openxmlformats.org/wordprocessingml/2006/main', 'w:val', $layout['rtlGutter']);
               $this->_sectPr->documentElement->appendChild($bidi);
            }
        }

        //Now we look at the case of numberCols
        if (isset($layout['numberCols'])) {
            if ($this->_sectPr->getElementsByTagName('cols')->length > 0) {
                $this->_sectPr->getElementsByTagName('cols')->item(0)->setAttribute('w:num', $layout['numberCols']);
            } else {
                $colsNode = $this->_sectPr->createDocumentFragment();
                $colsNode->appendXML('<w:cols w:num="'.$layout['numberCols'].'" xmlns:w="http://schemas.openxmlformats.org/wordprocessingml/2006/main" />');
                $this->_sectPr->documentElement->appendChild($colsNode);
            }
        }
    }

    /**
     * Parses a WordML fragment to be inserted as a footnote or endnote
     *
     * @access private
     * @param string $type it can be footnote, endnote or comment
     * @param WordMLFragment object $wordMLFragment
     * @param array $markOptions the note mark options
     * @param array $referenceOptions the note reference options
     * @return string
     */
    private function parseWordMLNote($type, $wordMLFragment, $markOptions = array(), $referenceOptions = array())
    {
        $referenceOptions = self::setRTLOptions($referenceOptions);
        $strFrag = (string) $wordMLFragment;
        $basePIni = '<w:p><w:pPr><w:pStyle w:val="' . $type . 'TextPHPDOCX"/>';
        if(isset($referenceOptions['bidi']) && $referenceOptions['bidi'] == on){
            $basePIni .= '<w:bidi />';
        }
        $basePIni .= '</w:pPr>';
        $run .= '<w:r><w:rPr><w:rStyle w:val="' . $type .'ReferencePHPDOCX"/>';
        //Parse the referenceMark options
        if(isset($referenceOptions['font'])){
          $run .=  '<w:rFonts w:ascii="' . $referenceOptions['font'] .
                            '" w:hAnsi="' . $referenceOptions['font'] .
                            '" w:cs="' . $referenceOptions['font'] . '"/>';
        }
        if(isset($referenceOptions['b'])){
          $run .=  '<w:b w:val="' . $referenceOptions['b'] . '"/>';
        }
        if(isset($referenceOptions['i'])){
          $run .=  '<w:i w:val="' . $referenceOptions['i'] . '"/>';
        }
        if(isset($referenceOptions['color'])){
          $run .=  '<w:color w:val="' . $referenceOptions['color'] . '"/>';
        }
        if(isset($referenceOptions['sz'])){
          $run .=  '<w:sz w:val="' . (2 * $referenceOptions['sz']) . '"/>';
          $run .=  '<w:szCs w:val="' . (2 * $referenceOptions['sz']) . '"/>';
        }
        if(isset($referenceOptions['rtl']) && $referenceOptions['rtl'] == 'on'){
            $basePIni .= '<w:rtl />';
        }
        $run .= '</w:rPr>';
        if(isset($markOptions['customMark'])){
            $run .= '<w:t>' . $markOptions['customMark'] . '</w:t>';
        }else{
            if($type != 'comment'){
                $run .= '<w:' . $type .'Ref/>';
            }
        }
        $run .= '</w:r>';
        $basePEnd ='</w:p>';
        //Check if the WordML fragment starts with a paragraph
        $startFrag = substr($strFrag,0 ,5);
        if($startFrag == '<w:p>'){
            $strFrag = preg_replace('/<\/w:pPr>/', '</w:pPr>' . $run, $strFrag, 1);
        }else{
            $strFrag = $basePIni . $run . $basePEnd . $strFrag;
        }
        return $strFrag;
    }

    /**
     * Gets the Ids associated with the different styles in the current document or an external docx.
     * It returns a docx with all the available paragraph, list and table styles.
     *
     * @access public
     * @example ../examples/easy/ParseStyles.php
     * @param string $path. Optional, if empty lists the Ids of the current style sheet
     */
    public function parseStyles($path='')
    {
       if($path != ''){
            $tempTitle = explode('/',$path);
            $title = array_pop($tempTitle);
            $parseStyles = new ZipArchive();
            try {
                $openParseStyle = $parseStyles->open($path);
                if ($openParseStyle !== true) {
                    throw new Exception('Error while opening the Style sheet to be tested: please, check the path');
                }
            }
            catch (Exception $e) {
                PhpdocxLogger::logger($e->getMessage(), 'fatal');
            }

            try {
                $parsedStyles = $parseStyles->getFromName('word/styles.xml');
                if ($parsedStyles == '') {
                    throw new Exception('Error while extracting the styles to be parsed from the external docx');
                }
            }
            catch (Exception $e) {
                PhpdocxLogger::logger($e->getMessage(), 'fatal');
            }

            try {
                $parsedNumberings = $parseStyles->getFromName('word/numbering.xml');
                if ($parsedNumberings == '') {
                    throw new Exception('Error while extracting the numberings to be parsed from the external docx');
                }
            }
            catch (Exception $e) {
                PhpdocxLogger::logger($e->getMessage(), 'fatal');
            }
        } else {
            $tempTitle = explode('/',PHPDOCX_BASE_TEMPLATE);
            $title = array_pop($tempTitle);
            $parsedStyles = $this->_baseTemplateZip->getFromName('word/styles.xml');
            $parsedNumberings = $this->_baseTemplateZip->getFromName('word/numbering.xml');
        }


        //We now include certain sample content to create the resulting style docx

        $myParagraph = 'This is some sample paragraph test';
        $myList = array('item 1', 'item 2', array('subitem 2_1', 'subitem 2_2'), 'item 3', array('subitem 3_1', 'subitem 3_2', array('sub_subitem 3_2_1', 'sub_subitem 3_2_1')), 'item 4');
        $myTable = array(
                            array(
                            'Title A',
                            'Title B',
                            'Title C'
                            ),
                            array(
                            'First row A',
                            'First row B',
                            'First row C'
                            ),
                            array(
                            'Second row A',
                            'Second row B',
                            'Second row C'
                            )
                         );

        //let's parse the different list numberings from
        $this->addText('List styles: '.$title, array('jc' => 'center', 'color' => 'b90000', 'b' => 'single', 'sz' => '18', 'u' => 'double'));

        $wordListChunk ='<w:p><w:pPr><w:rPr><w:b/></w:rPr></w:pPr>
        <w:r><w:rPr><w:b/></w:rPr><w:t>SAMPLE CODE:</w:t></w:r>
        </w:p><w:tbl><w:tblPr><w:tblW w:w="0" w:type="auto"/>
        <w:shd w:val="clear" w:color="auto" w:fill="DDD9C3"/>
        <w:tblLook w:val="04A0"/></w:tblPr><w:tblGrid>
        <w:gridCol w:w="8644"/></w:tblGrid><w:tr><w:tc>
        <w:tcPr><w:tcW w:w="8644" w:type="dxa"/>
        <w:shd w:val="clear" w:color="auto" w:fill="DCDAC4"/>
        </w:tcPr><w:p><w:pPr><w:spacing w:before="200"/></w:pPr>
        <w:r><w:t>$</w:t></w:r><w:r>
        <w:t>myList</w:t></w:r><w:r>
        <w:t xml:space="preserve"> = array(\'item 1\', </w:t>
        </w:r><w:r>
        <w:br/>
        <w:t xml:space="preserve">                             </w:t>
        </w:r><w:r>
        <w:t xml:space="preserve">\'item 2\', </w:t>
        </w:r><w:r><w:br/>
        <w:t xml:space="preserve">                             </w:t>
        </w:r><w:r><w:t>array(\'</w:t></w:r><w:r><w:t>subitem</w:t>
        </w:r><w:r>
        <w:t xml:space="preserve"> 2_1\', </w:t></w:r><w:r><w:br/>
        <w:t xml:space="preserve">                                        </w:t>
        </w:r><w:r><w:t>\'</w:t>
        </w:r><w:r><w:t>subitem</w:t></w:r><w:r>
        <w:t xml:space="preserve"> 2_2\'), </w:t></w:r><w:r><w:br/>
        <w:t xml:space="preserve">                             </w:t>
        </w:r><w:r><w:t xml:space="preserve">\'item 3\', </w:t></w:r>
        <w:r><w:br/>
        <w:t xml:space="preserve">                             </w:t>
        </w:r><w:r><w:t>array(\'</w:t></w:r><w:r><w:t>subitem</w:t>
        </w:r><w:r><w:t xml:space="preserve"> 3_1\', </w:t></w:r>
        <w:r><w:br/>
        <w:t xml:space="preserve">                                        </w:t>
        </w:r><w:r><w:t>\'</w:t></w:r><w:r><w:t>subitem</w:t></w:r>
        <w:r><w:t xml:space="preserve"> 3_2\', </w:t></w:r><w:r><w:br/>
        <w:t xml:space="preserve">                                        </w:t>
        </w:r><w:r><w:t>array(\'</w:t></w:r><w:r><w:t>sub_subitem</w:t></w:r><w:r>
        <w:t xml:space="preserve"> 3_2_1\', </w:t></w:r><w:r><w:br/>
        <w:t xml:space="preserve">                                                   </w:t>
        </w:r><w:r><w:t>\'</w:t></w:r><w:r><w:t>sub_subitem</w:t></w:r><w:r>
        <w:t xml:space="preserve"> 3_2_1\')),</w:t></w:r><w:r><w:br/>
        <w:t xml:space="preserve">                             </w:t>
        </w:r><w:r><w:t xml:space="preserve"> \'item 4\');</w:t></w:r></w:p>
        <w:p><w:pPr><w:spacing w:before="200"/></w:pPr>
        <w:r><w:t>addList</w:t></w:r><w:r><w:t>($</w:t></w:r>
        <w:r><w:t>myList</w:t></w:r><w:r><w:t>, array(\'</w:t></w:r>
        <w:r><w:t>val</w:t></w:r><w:r>
        <w:t>\' =</w:t></w:r><w:r><w:t>&gt; NUMID</w:t></w:r>
        <w:r><w:t>))</w:t></w:r></w:p></w:tc></w:tr></w:tbl><w:p><w:pPr></w:pPr>
        </w:p>
        <w:p><w:pPr><w:rPr><w:b/></w:rPr></w:pPr>
        <w:r><w:rPr><w:b/></w:rPr><w:t>SAMPLE RESULT:</w:t></w:r>
        </w:p>';
        if ($parsedNumberings) {
            $NumberingsDoc = new DOMDocument();
            $NumberingsDoc->loadXML($parsedNumberings);
            $numberXpath = new DOMXPath($NumberingsDoc);
            $numberXpath->registerNamespace('w', 'http://schemas.openxmlformats.org/wordprocessingml/2006/main');
            $queryNumber = '//w:num';
            $numberingsNodes = $numberXpath->query($queryNumber);
            foreach($numberingsNodes as $node){
                $wordListChunkTemp = str_replace('NUMID',$node->getAttribute('w:numId'), $wordListChunk);
                $this->_wordDocumentC .= $wordListChunkTemp;
                $this->addList($myList, array('val' => (int)$node->getAttribute('w:numId')));
                $this->addBreak(array('type' => 'page'));
            }
        }

        $this->addText('Paragraph and Table styles: '.$title, array('jc' => 'center', 'color' => 'b90000', 'b' => 'single', 'sz' => '18', 'u' => 'double'));

        //let's parse the different styles via XPath
        $StylesDoc = new DOMDocument();
        $StylesDoc->loadXML($parsedStyles);
        $parseStylesXpath = new DOMXPath($StylesDoc);
        $parseStylesXpath->registerNamespace('w', 'http://schemas.openxmlformats.org/wordprocessingml/2006/main');
        $query = '//w:style';
        $parsedNodes = $parseStylesXpath->query($query);
        //Lets list the present styles and their respective Ids
        $count=1;
        foreach($parsedNodes as $node){
          $styleId = $node->getAttribute('w:styleId');
          $styleType= $node->getAttribute('w:type');
          $styleDefault = $node->getAttribute('w:default');
          $styleCustom= $node->getAttribute('w:custom');
          $nodeChilds = $node->childNodes;
          foreach($nodeChilds as $child){
          if ($child->nodeName == 'w:name'){
             $styleName = $child->getAttribute('w:val');
              }
           }
           $this->parsedStyles[$count]= array('id'=>$styleId, 'name'=>$styleName, 'type'=>$styleType,'default'=>$styleDefault, 'custom'=>$styleCustom);


           $default = ($styleDefault == 1)?'true':'false';
           $custom = ($styleCustom == 1)?'true':'false';

           $wordMLChunk = '<w:tbl><w:tblPr><w:tblW w:w="0" w:type="auto"/>
                </w:tblPr><w:tblGrid><w:gridCol w:w="4322"/><w:gridCol w:w="4322"/>
                </w:tblGrid><w:tr><w:tc><w:tcPr><w:tcW w:w="4322" w:type="dxa"/>
                <w:shd w:val="clear" w:color="auto" w:fill="BD1503"/>
                </w:tcPr><w:p><w:pPr><w:spacing w:after="0"/><w:rPr>
                <w:color w:val="FFFFFF"/></w:rPr></w:pPr><w:r><w:rPr>
                <w:color w:val="FFFFFF"/></w:rPr><w:t>NAME:</w:t></w:r></w:p>
                </w:tc><w:tc><w:tcPr><w:tcW w:w="4322" w:type="dxa"/>
                <w:shd w:val="clear" w:color="auto" w:fill="BD1503"/></w:tcPr>
                <w:p><w:pPr><w:spacing w:after="0"/><w:rPr><w:color w:val="FFFFFF"/>
                </w:rPr></w:pPr><w:r><w:rPr><w:color w:val="FFFFFF"/>
                </w:rPr><w:t>'.$styleName.'</w:t></w:r></w:p></w:tc>
                </w:tr><w:tr><w:tc><w:tcPr><w:tcW w:w="4322" w:type="dxa"/>
                <w:shd w:val="clear" w:color="auto" w:fill="3E3E42"/>
                </w:tcPr><w:p><w:pPr><w:spacing w:after="0" w:line="240" w:lineRule="auto"/>
                <w:rPr><w:color w:val="FFFFFF"/></w:rPr></w:pPr><w:r>
                <w:rPr><w:color w:val="FFFFFF"/></w:rPr><w:t>Type</w:t>
                </w:r><w:r><w:rPr><w:color w:val="FFFFFF"/></w:rPr>
                <w:t>:</w:t></w:r></w:p></w:tc><w:tc><w:tcPr>
                <w:tcW w:w="4322" w:type="dxa"/>
                <w:shd w:val="clear" w:color="auto" w:fill="3E3E42"/>
                </w:tcPr><w:p><w:pPr>
                <w:spacing w:after="0" w:line="240" w:lineRule="auto"/>
                <w:rPr><w:color w:val="FFFFFF"/></w:rPr></w:pPr><w:r>
                <w:rPr><w:color w:val="FFFFFF"/></w:rPr>
                <w:t>'.$styleType.'</w:t></w:r></w:p></w:tc></w:tr>
                <w:tr><w:tc><w:tcPr>
                <w:tcW w:w="4322" w:type="dxa"/>
                <w:shd w:val="clear" w:color="auto" w:fill="3E3E42"/>
                </w:tcPr><w:p><w:pPr>
                <w:spacing w:after="0" w:line="240" w:lineRule="auto"/>
                <w:rPr><w:color w:val="FFFFFF"/></w:rPr></w:pPr><w:r>
                <w:rPr><w:color w:val="FFFFFF"/></w:rPr>
                <w:t>ID:</w:t></w:r></w:p></w:tc><w:tc>
                <w:tcPr><w:tcW w:w="4322" w:type="dxa"/>
                <w:shd w:val="clear" w:color="auto" w:fill="3E3E42"/>
                </w:tcPr><w:p><w:pPr>
                <w:spacing w:after="0" w:line="240" w:lineRule="auto"/>
                <w:rPr><w:color w:val="FFFFFF"/></w:rPr></w:pPr><w:r>
                <w:rPr><w:color w:val="FFFFFF"/></w:rPr>
                <w:t>'.$styleId.'</w:t></w:r></w:p></w:tc></w:tr><w:tr><w:tc><w:tcPr>
                <w:tcW w:w="4322" w:type="dxa"/>
                <w:shd w:val="clear" w:color="auto" w:fill="3E3E42"/></w:tcPr>
                <w:p><w:pPr><w:spacing w:after="0" w:line="240" w:lineRule="auto"/>
                <w:rPr><w:color w:val="FFFFFF"/></w:rPr></w:pPr><w:r>
                <w:rPr><w:color w:val="FFFFFF"/></w:rPr><w:t>Default:</w:t></w:r>
                </w:p></w:tc><w:tc><w:tcPr><w:tcW w:w="4322" w:type="dxa"/>
                <w:shd w:val="clear" w:color="auto" w:fill="3E3E42"/>
                </w:tcPr><w:p><w:pPr>
                <w:spacing w:after="0" w:line="240" w:lineRule="auto"/>
                <w:rPr><w:color w:val="FFFFFF"/></w:rPr></w:pPr>
                <w:r><w:rPr><w:color w:val="FFFFFF"/></w:rPr>
                <w:t>'.$default.'</w:t></w:r></w:p></w:tc></w:tr><w:tr>
                <w:tc><w:tcPr><w:tcW w:w="4322" w:type="dxa"/>
                <w:shd w:val="clear" w:color="auto" w:fill="3E3E42"/>
                </w:tcPr><w:p><w:pPr>
                <w:spacing w:after="0" w:line="240" w:lineRule="auto"/>
                <w:rPr><w:color w:val="FFFFFF"/></w:rPr></w:pPr>
                <w:r><w:rPr><w:color w:val="FFFFFF"/></w:rPr><w:t>Custom</w:t>
                </w:r><w:r><w:rPr><w:color w:val="FFFFFF"/></w:rPr>
                <w:t>:</w:t></w:r></w:p></w:tc><w:tc><w:tcPr>
                <w:tcW w:w="4322" w:type="dxa"/>
                <w:shd w:val="clear" w:color="auto" w:fill="3E3E42"/>
                </w:tcPr><w:p><w:pPr>
                <w:spacing w:after="0" w:line="240" w:lineRule="auto"/>
                <w:rPr><w:color w:val="FFFFFF"/></w:rPr></w:pPr><w:r>
                <w:rPr><w:color w:val="FFFFFF"/></w:rPr><w:t>'.$custom.'</w:t>
                </w:r></w:p></w:tc></w:tr></w:tbl>
                <w:p w:rsidR="000F6147" w:rsidRDefault="000F6147" w:rsidP="00B42E7D">
                <w:pPr><w:spacing w:after="0"/></w:pPr></w:p>
                <w:p w:rsidR="00DC3ACE" w:rsidRDefault="00DC3ACE">
                <w:pPr><w:rPr><w:b/></w:rPr></w:pPr><w:r>
                <w:rPr><w:b/></w:rPr><w:t>SAMPLE CODE:</w:t></w:r></w:p>
                <w:tbl><w:tblPr><w:tblW w:w="0" w:type="auto"/>
                <w:shd w:val="clear" w:color="auto" w:fill="DDD9C3"/>
                </w:tblPr><w:tblGrid><w:gridCol w:w="8644"/>
                </w:tblGrid><w:tr><w:tc><w:tcPr><w:tcW w:w="8644" w:type="dxa"/>
                <w:shd w:val="clear" w:color="auto" w:fill="DCDAC4"/></w:tcPr>
                <w:p w:rsidR="00DC3ACE" w:rsidRDefault="00DC3ACE">
                <w:pPr><w:spacing w:before="200" /></w:pPr><w:r>
                <w:t>CODEX</w:t></w:r></w:p></w:tc></w:tr></w:tbl><w:p/><w:p>
                <w:pPr><w:rPr><w:b/></w:rPr></w:pPr><w:r><w:rPr><w:b/>
                </w:rPr><w:t>SAMPLE RESULT:</w:t></w:r></w:p>
                ';

           switch($styleType){
               case 'table':
                   $wordMLChunk = str_replace('CODEX',"addTable(array(array('Title A','Title B','Title C'),array('First row A','First row B','First row C'),array('Second row A','Second row B','Second row C')), array('TBLSTYLEval'=> '$styleId'))", $wordMLChunk);
                   $this->_wordDocumentC .= $wordMLChunk;
                   $params = array('TBLSTYLEval'=> $styleId);
                   $this->addTable($myTable, $params);
                   if($count%2 == 0){
                   $this->_wordDocumentC .= '<w:p><w:r><w:br w:type="page"/></w:r></w:p>';
                   }else{
                    $this->_wordDocumentC .= '<w:p /><w:p />';
                   }
                   $count++;
                   break;
               case 'paragraph':
                   $myPCode = "addText('This is some sample paragraph test', array('pStyle' => '".$styleId."'))";
                   $wordMLChunk = str_replace('CODEX',$myPCode, $wordMLChunk);
                   $this->_wordDocumentC .= $wordMLChunk;
                   $params = array('pStyle'=> $styleId);
                   $this->addText($myParagraph, $params);
                   if($count%2 == 0){
                    $this->_wordDocumentC .= '<w:p><w:r><w:br w:type="page"/></w:r></w:p>';
                   }else{
                    $this->_wordDocumentC .= '<w:p /><w:p />';
                   }
                   $count++;
                   break;
           }

        }

    }

    /**
     * Parse DOCX file and extract content
     *
     * @access public
     * @example ../examples/easy/Parser.php
     * @param string $path Path to DOCX file
     */
    public function readDOCX($path)
    {
        $parser = Parser::getInstance();
        try {
            $parser->readFile($path);
        }
        catch (Exception $e) {
            PhpdocxLogger::logger($e->getMessage(), 'fatal');
        }
        PhpdocxLogger::logger('Read DOCX file.', 'info');
    }

    /**
     * Replace a header image with a new image.
     *
     * @access public
     * @example ../examples/intermediate/ReplaceHeaderImage.php
     * @param string $var Value of the variable
     * @param string $pathImage Path of the new image
     */
    public function replaceHeaderImage($var, $pathImage)
    {
        $template = CreateTemplate::getInstance();
        PhpdocxLogger::logger('Assign and replace image variable ' . $var . ' in header.', 'info');
        $template->replaceHeaderImage($var, $pathImage);
    }

    /**
     * Replace a template variable with WordML obtained from HTML via the
     * embedHTML method.
     *
     * @access public
     * @example ../examples/easy/ReplaceTemplateVariableByHTML.php
     * @param string $var Value of the variable.
     * @param type inline or block
     * @param string $html HTML source
     * @param array $options:
     * isFile (boolean),
     * customListStyles (bool) if true try to use the predefined customm lists
     * baseURL (string),
     * downloadImages (boolean),
     * filter (string) could be an string denoting the id, class or tag to be filtered.
     * If you want only a class introduce .classname, #idName for an id or <htmlTag> for a particular tag. One can also use
     * standard XPath expresions supported by PHP.
     * 'parseAnchors' (boolean),
     * 'parseDivs' (paragraph, table): parses divs as paragraphs or tables,
     * 'parseFloats' (boolean),
     * 'strictWordStyles' (boolean) if true ignores all CSS styles and uses the styles set via the wordStyles option (see next)
     * 'wordStyles' (array) associates a particular class, id or HTML tag to a Word style
     *
     */
    public function replaceTemplateVariableByHTML($var, $type, $html = '<html><body></body></html>', $options = array())
    {
        $htmlDOCX = new HTML2WordML($this->_baseTemplateFilesPath);
        $wordHTML = $htmlDOCX->render($html, $options);
        $template = CreateTemplate::getInstance();
        PhpdocxLogger::logger('Assign and replace  variable ' . $var . ' in template by HTML.', 'info');

        //We now clean the wordML to take into account the case where we want an 'inline' replace
        if($type == 'block'){
            $wordHTMLString = $wordHTML[0];
        }else{
            $wordHTMLString = $this->cleanWordMLBlockElements($wordHTML[0]);
        }

        $template->replaceVariableByHTML($var, $type, $wordHTMLString);
        $template->TemplateHTMLRels($wordHTML, $options, $this->_baseTemplateFilesPath);

        if(is_array($this->_templateNumberings)){
            $this->_templateNumberings = array_merge($this->_templateNumberings, $wordHTML[3]);
        }else{
            $this->_templateNumberings = $wordHTML[3];
        }
        if(is_array($this->_templateCustomNumberings)){
            $this->_templateCustomNumberings = array_merge($this->_templateCustomNumberings, $wordHTML[4]);
        }else{
            $this->_templateCustomNumberings = $wordHTML[4];
        }
    }

    /**
     * Changes the background color of the document
     *
     * @access public
     * @example ../examples/easy/BackgroundColor.php
     * @param string $color
     * Values: hexadecimal color value without # (ffff00, 0000ff, ...)
     */
    public function setBackgroundColor($color)
    {
        $this->_backgroundColor = $color;
        //We construct the background WordML code
        if ($this->_background == '') {
           $this->_background ='<w:background w:color="' . $color . '" />';
           //We have to modify the settings.xml file
            try {
                $settings = fopen($this->_baseTemplateFilesPath.'/word/settings.xml', "r");
                $baseTemplateSettingsT = fread($settings, 1000000);
                fclose($settings);
                if ($baseTemplateSettingsT == '') {
                    throw new Exception('Error while extracting settings.xml file from the base template to insert the background image');
                }
            }
            catch (Exception $e) {
                PhpdocxLogger::logger($e->getMessage(), 'fatal');
            }
            $this->_wordSettingsT = new DOMDocument();
            $this->_wordSettingsT->loadXML($baseTemplateSettingsT);
            $settingsImage = $this->_wordSettingsT->createDocumentFragment();
            $settingsImage->appendXML('<w:displayBackgroundShape xmlns:w="http://schemas.openxmlformats.org/wordprocessingml/2006/main" />');
            $this->_wordSettingsT->documentElement->appendChild($settingsImage);
            $newSettings = $this->_wordSettingsT->saveXML();
            $settingsHandle = fopen($this->_baseTemplateFilesPath.'/word/settings.xml', "w+");
            $contents = fwrite($settingsHandle, $newSettings);
            fclose($settingsHandle);
        } else {
           $this->_background = str_replace('w:color="FFFFFF"', 'w:color="' . $color . '"', $this->_background);
        }
    }

    /**
     * Change the default font
     *
     * @access public
     * @param string $symbol
     *  Values: '.', ',',...
     */
    public function setDecimalSymbol($symbol)
    {
        //Let's get the original settings.xml as a DOMdocument
        try {
            $settingsHandler = fopen($this->_baseTemplateFilesPath.'/word/settings.xml', 'r');
            $settingsXML = fread($settingsHandler, filesize($this->_baseTemplateFilesPath.'/word/settings.xml'));
            fclose($settingsHandler);
            if ($settingsXML == '') {
                throw new Exception('Error while extracting the settings file from the base template to stablish default decimal symbol');
            }
        }
        catch (Exception $e) {
            PhpdocxLogger::logger($e->getMessage(), 'fatal');
        }
        $settingsDocument = new DomDocument();
        $settingsDocument->loadXML($settingsXML);
        $decimalNodes = $settingsDocument->getElementsByTagName('decimalSymbol');
        $decimalNode = $decimalNodes->item(0);
        $newDecimalNode = $settingsDocument->createElement('w:decimalSymbol', '');
        $newDecimalNode->setAttribute('w:val', $symbol);
        $decimalNode->parentNode->replaceChild($newDecimalNode, $decimalNode);
        $settingsXML = $settingsDocument->saveXML();
        try {
            $settingsFile=fopen($this->_baseTemplateFilesPath.'/word/settings.xml', 'w');
            if ($settingsFile == false) {
                throw new Exception('Error while opening the base template settings.xml file');
            }
        }
        catch (Exception $e) {
            PhpdocxLogger::logger($e->getMessage(), 'fatal');
        }
        try {
            $writeSettings = fwrite($settingsFile, $settingsXML);
            if ($writeSettings == 0) {
                throw new Exception('There was an error while trying to set the decimal Symbol');
            }
        }
        catch (Exception $e) {
            PhpdocxLogger::logger($e->getMessage(), 'fatal');
        }
        PhpdocxLogger::logger('Change decimal symbol.', 'info');

    }

    /**
     * Change the default font
     *
     * @access public
     * @example ../examples/easy/SetDefaultFont.php
     * @param string $font The new font
     *  Values: 'Arial', 'Times New Roman'...
     */
    public function setDefaultFont($font)
    {
        $this->_defaultFont = $font;
        //Let's get the original theme as a DOMdocument
        try {
            $themeHandler = fopen($this->_baseTemplateFilesPath.'/word/theme/theme1.xml', 'r');
            $themeXML = fread($themeHandler, filesize($this->_baseTemplateFilesPath.'/word/theme/theme1.xml'));
            fclose($themeHandler);
            if ($themeXML == '') {
                throw new Exception('Error while extracting the theme file from the base template to stablish default font');
            }
        }
        catch (Exception $e) {
            PhpdocxLogger::logger($e->getMessage(), 'fatal');
        }
        $themeDocument = new DomDocument();
        $themeDocument->loadXML($themeXML);
        $latinNode = $themeDocument->getElementsByTagName('latin');
        $latinNode->item(0)->setAttribute('typeface', $font);
        $latinNode->item(1)->setAttribute('typeface', $font);

        $themeXML = $themeDocument->saveXML();
        try {
            $themeFile=fopen($this->_baseTemplateFilesPath.'/word/theme/theme1.xml', 'w');
            if ($themeFile == false) {
                throw new Exception('Error while opening the base template theme1.xml file');
            }
        }
        catch (Exception $e) {
            PhpdocxLogger::logger($e->getMessage(), 'fatal');
        }
        try {
            $writeTheme = fwrite($themeFile, $themeXML);
            if ($writeTheme == 0) {
                throw new Exception('There was an error while trying to set the default font');
            }
        }
        catch (Exception $e) {
            PhpdocxLogger::logger($e->getMessage(), 'fatal');
        }
        PhpdocxLogger::logger('Change default font.', 'info');

    }

    /**
     * Transform to UTF-8 charset
     *
     * @access public
     */
    public function setEncodeUTF8()
    {
        self::$_encodeUTF = 1;
    }

    /**
     * Change default language.
     * @example ../examples/easy/Language.php
     * @param $lang Locale: en-US, es-ES...
     * @access public
     */
    public function setLanguage($lang = null)
    {
        if (!$lang) {
            $lang = 'en-US';
        }
        //Let's get the original styles as a DOMdocument
        try{
            $styleHandler = fopen($this->_baseTemplateFilesPath.'/word/styles.xml', 'r');
            $styleXML = fread($styleHandler, 10000000);
            fclose($styleHandler);
            $this->_wordStylesT = $styleXML;
            if ($styleXML == '') {
                throw new Exception('Error while extracting the style file from the base template to stablish default language');
            }
        }
        catch (Exception $e) {
            PhpdocxLogger::logger($e->getMessage(), 'fatal');
        }
        $stylesDocument = new DomDocument();
        $stylesDocument->loadXML($this->_wordStylesT);
        $langNode = $stylesDocument->getElementsByTagName('lang');
        $langNode->item(0)->setAttribute('w:val', $lang);
        $langNode->item(0)->setAttribute('w:eastAsia', $lang);

        $this->_wordStylesT = $stylesDocument->saveXML();
        try {
            $stylesFile=fopen($this->_baseTemplateFilesPath.'/word/styles.xml', 'w');
            if ($stylesFile == false) {
                throw new Exception('Error while opening the base template styles.xml file');
            }
        }
        catch (Exception $e) {
            PhpdocxLogger::logger($e->getMessage(), 'fatal');
        }
        try {
            $writeStyles = fwrite($stylesFile,$this->_wordStylesT );
            if ($writeStyles == 0) {
                throw new Exception('There was an error while trying to set the default language');
            }
        }
        catch (Exception $e) {
            PhpdocxLogger::logger($e->getMessage(), 'fatal');
        }

        PhpdocxLogger::logger('Set language.', 'info');
    }



    /**
     * Mark the document as final
     *
     * @access public
     * @example ../examples/easy/MarkAsFinal.php
     *
     */
    public function setMarkAsFinal()
    {
        $this->_markAsFinal = 1;
        $this->addProperties(array('contentStatus' => 'Final'));
        $this->generateOVERRIDE(
            '/docProps/custom.xml',
            'application/vnd.openxmlformats-officedocument.' .
            'custom-properties+xml'
        );
    }

        /**
     * sets global right to left options
     * @access public
     * @param array $options
     * values:
     *  'bidi' (bool)
     *  'rtl' (bool)
     * @return void
     */
    public function setRTL($options = array('bidi' => true, 'rtl' => true)){
        if(isset($options['bidi']) && $options['bidi']){
            self::$bidi = true;
        }
        if(isset($options['rtl']) && $options['rtl']){
            self::$rtl = true;
        }
        $this->modifyPageLayout('custom', array('bidi' => $options['bidi'], 'rtlGutter' => $options['rtl']));
        //set footnotes and endnotes separators for bidi and rtl
        //open footnotes
        $filename = $this->_baseTemplateFilesPath.'/word/footnotes.xml';
        $handle = fopen($filename, "r");
        $contents = fread($handle, 999999);
        fclose($handle);

        $this->_wordFootnotesT = new DOMDocument();
        $this->_wordFootnotesT->loadXML($contents);

        //open endnotes
        $filename = $this->_baseTemplateFilesPath.'/word/endnotes.xml';
        $handle = fopen($filename, "r");
        $contents = fread($handle, 999999);
        fclose($handle);

        $this->_wordEndnotesT = new DOMDocument();
        $this->_wordEndnotesT->loadXML($contents);


        $notesArray = array('footnote' => $this->_wordFootnotesT, 'endnote' => $this->_wordEndnotesT);
        foreach($notesArray as $note => $value){
            $noteXPath = new DOMXPath($value);
            $noteXPath->registerNamespace('w', 'http://schemas.openxmlformats.org/wordprocessingml/2006/main');
            $query = '//w:' . $note . '[@w:type="separator"] | //w:' . $note . '[@w:type="continuationSeparator"]';
            $selectedNodes = $noteXPath->query($query);
            foreach($selectedNodes as $node){
                $pPrNode = $node->getElementsbyTagName('pPr')->item(0);
                $bidiNodes = $node->getElementsbyTagName('bidi');
                if($bidiNodes->length > 0){
                    $bidiNodes->item(0)->setAttribute('w:val', $options['bidi']);
                }else{
                    $bidi = $pPrNode->ownerDocument->createElement('w:bidi');
                    $bidi->setAttribute('w:val', $options['bidi']);
                    $pPrNode->appendChild($bidi);
                }
                $rtlNodes = $node->getElementsbyTagName('rtl');
                if($rtlNodes->length > 0){
                    $rtlNodes->item(0)->setAttribute('w:val', $options['rtl']);
                }else{
                    $rtl = $pPrNode->ownerDocument->createElement('w:rtl');
                    $rtl->setAttribute('w:val', $options['rtl']);
                    $pPrNode->appendChild($rtl);
                }
            }
        }
        //We copy the  content into the respective files
        $footnoteHandler = fopen($this->_baseTemplateFilesPath.'/word/footnotes.xml', "w+");
        fwrite($footnoteHandler, $this->_wordFootnotesT->saveXML());
        fclose($footnoteHandler);

        $endnoteHandler = fopen($this->_baseTemplateFilesPath.'/word/endnotes.xml', "w+");
        fwrite($endnoteHandler, $this->_wordEndnotesT->saveXML());
        fclose($endnoteHandler);
    }

    /**
     * sets global right to left options for the different methods
     * @access public
     * @static
     * @param array $options
     * @return array
     */
    public static function setRTLOptions($options){
        if(!isset($options['bidi']) && CreateDocx::$bidi){
            $options['bidi'] = 'on';
        }
        if(!isset($options['rtl']) && CreateDocx::$rtl){
            $options['rtl'] = 'on';
        }
        return $options;
    }

    /**
     * Set the symbol surrounding varibles (placeholders)
     *
     * @access public
     * @param string $symbol The new symbol. Optional, $ as default
     */
    public function setTemplateSymbol($symbol = '$')
    {
        PhpdocxLogger::logger('Change template symbol.', 'info');
        CreateTemplate::setTemplateSymbol($symbol);
    }

    /**
     * Checks or unchecks a Word template checkbox.
     *
     * @access public
     * @example ../examples/easy/TickCheckbox.php
     * @param string $var variables name
     * @param int $value 1 (check) or 0 (uncheck)
     */
    public function tickCheckbox($var, $value = 1)
    {
        if($value != 0 && $value != 1){
            PhpdocxLogger::logger('The value maust be 0 or 1', 'fatal');
        }
        $template = CreateTemplate::getInstance();
        PhpdocxLogger::logger('Tick or not a checkbox', 'info');
        $template->checkCheckbox($var, $value);
    }



    /**
     * Transform DOCX to PDF, ODT, SXW, RTF, DOC, TXT, HTML or WIKI
     *
     * @access public
     * @example ../examples/advanced/Transform.php
     * @param string $docSource
     * @param string $docDestination
     * @param string $tempDir
     * @param array $options :
     *      · method : 'direct' (default), 'script' ; 'direct' method uses
     *                  passthru and 'script' uses a external script.
     *                  If you're using Apache and 'direct' doesn't work use 'script'
     *      · 'odfconverter' : true (default) or false. Use odf-converter.
     * @param string $version 32, 64 or null (default). If null autodetect
     * @return void
     */
    public function transformDocx($docSource, $docDestination, $tempDir = null, $options = array(), $version = null) {
        try {
            if (!$this->_compatibilityMode) {
                throw new Exception('Running in compatibility mode. Unsupported method.');
            }
            $convert = new TransformDocAdv();
            $convert->transformDocument($docSource, $docDestination, $tempDir, $options, $version);
        } catch (Exception $e) {
            PhpdocxLogger::logger($e->getMessage(), 'fatal');
        }
    }

    /**
     * If PHPDocX is installed in a server with a working copy of Word 2007 or newer you may
     * use it to do format conversions.
     * Supported formats, DOCX and DOC to PDF, RTF, HTML and DOC
     * @access public
     * @param $docSource You should use the full Windows path to the docx (remember to escape backslashes)
     * @param $docDestination ou should use the full Windows path to the docx (remember to escape backslashes)
     * @return void
     */
    public function transformDocxUsingMSWord($docSource, $docDestination) {
        $convert = new MSWordInterface();
        $convert->transformFormat($docSource, $docDestination);
    }

    /**
     *
     * Insert the content of a text file into a word document trying to hold the styles
     *
     * @example ../examples/easy/Text2Docx.php
     * @param string $path. Path to the text file from which we insert into docx document
     * @param array of style values
     * keys: styleTbl, styleLst, styleP
     */
    public function txt2docx($text_filename, $options = array()) {
        $text = new Text2Docx($text_filename, $options);
        PhpdocxLogger::logger('Add text from text file.', 'info');
        $this->_wordDocumentC .= (string) $text;
    }

    /**
     * Create a new style to use in your Word document.
     *
     * @access public
     * @example ../examples/easy/CreateListStyle.php
     * @param string $name the name we want to give to the created list
     * @param array $listOptions an array with the different styling options for each level:
     *  'type' can be decimal, lowerLetter, ....
     *  'font' Symbol, Courier new, Wingdings, ...
     *  'format' the default one is '%1.' for firs level, '%2' for second level and so long so forth
     *  'hanging' the extra space for the numbering, should be big enough to accomodate it, the default is 360
     *  'left' the left indent. The default value is 720 times the list level
     */
    public function createListStyle($name, $listOptions = array())
    {
       $newStyle = new CreateListStyle();
       $style = $newStyle->addListStyle($name, $listOptions);
       $listId = rand(9999, 999999999);
       $this->_wordNumberingT = $this->importSingleNumbering($this->_wordNumberingT, $style, $listId);
       self::$customLists[$name]['id'] = $listId;
       self::$customLists[$name]['wordML'] = $style;
    }

    /**
     * Create a new paragraph style and linked char style to be used in your Word document.
     *
     * @access public
     * @example ../examples/easy/CreateParagraphStyle.php
     * @param string $name the name we want to give to the created style
     * @param mixed $styleOptions it includes the required style options
     * Array values:
     * 'b' (on, off)
     * 'border' (on, off) if "on" you may set:
     *      border-width (int) page border width in eigths of a point (default value is 4)
     *      border-color (string) hexadecimal color ('000000' (default), 'FF0000', ...)
     *      border-style (string) none, single, double, ... (default value is  single)
     *      border-space (int) border spacing in points (default is 24)
     *      border-<side>-width (int) page border width in eights of a point
     *      border-<side>-color (string) hexadecimal color ('000000' (default), 'FF0000', ...)
     *      border-<side>-style (string) none, single, double, ... (default value is  single)
     *      border-<side>-space (int) border spacing in points (default is 24)
     * 'caps' (on, off) display text in capital letters
     * 'color' (ffffff, ff0000...)
     * 'contextualSpacing' (on, off) ignore spacing above and below when using identical styles
     * 'font' (Arial, Times New Roman...)
     * 'hanging' 100, ....
     * 'i' (on, off)
     * 'indent_left' 100...,
     * 'indent_right' 100...
     * 'indent_firstLine' 100, ...
     * 'jc' (both, center, distribute, left, right)
     * 'keepLines' (on, off) keep all paragraph lines on the same page
     * 'keepNext' (on, off) keep in the same page the current paragraph with next paragraph
     * 'lineSpacing' 120, 240 (standard), 360, 480, ...
     * 'outlineLvl' (int) heading level (1-9)
     * 'pageBreakBefore' (on, off)
     * 'spacingBottom' (int) bottom margin in twentieths of a point
     * 'spacingTop' (int) top margin in twentieths of a point
     * 'smallCaps' (on, off) display text in small caps
     * 'sz' (8, 9, 10, ...) size in points
     * 'textDirection' (lrTb, tbRl, btLr, lrTbV, tbRlV, tbLrV) text flow direction
     * 'u' (none, dash, dotted, double, single, wave, words)
     * 'widowControl' (on, off)
     * 'wordWrap' (on, off)
     */
    public function createParagraphStyle($name, $styleOptions = array())
    {
       $newStyle = new CreateParagraphStyle();
       $style = $newStyle->addParagraphStyle($name, $styleOptions);

       //Let's get the original styles
        try{
            $styleHandler = fopen($this->_baseTemplateFilesPath.'/word/styles.xml', 'r');
            $styleXML = fread($styleHandler, 1000000);
            fclose($styleHandler);
            if ($styleXML == '') {
                throw new Exception('Error while extracting the style file from the base template');
            }
        }
        catch (Exception $e) {
            PhpdocxLogger::logger($e->getMessage(), 'fatal');
        }
        //append the new styles as a string at the end of the styles file
        $styleXML = str_replace('</w:styles>', $style[0] . '</w:styles>', $styleXML);
        $styleXML = str_replace('</w:styles>', $style[1] . '</w:styles>', $styleXML);

        //Reload the styles file
        try {
            $stylesFile=fopen($this->_baseTemplateFilesPath.'/word/styles.xml', 'w');
            if ($stylesFile == false) {
                throw new Exception('Error while opening the base template styles.xml file');
            }
        }
        catch (Exception $e) {
            PhpdocxLogger::logger($e->getMessage(), 'fatal');
        }
        try {
            $writeStyles = fwrite($stylesFile, $styleXML);
            if ($writeStyles == 0) {
                throw new Exception('There was an error while inserting the new style');
            }
        } catch (Exception $e) {
            PhpdocxLogger::logger($e->getMessage(), 'fatal');
        }
    }

    /**
     * Creates a WordML fragment.
     *
     * @access public
     * @example ../examples/easy/WordMLFragment.php
     * @example ../examples/intermediate/EmbedHTMLinTable.php
     * @param mixed $data, string or array
     */
    public function createWordMLFragment($data)
    {
       $wordMLFragment = new WordMLFragment();
       if(!empty($data) && !is_array($data)){
           $wordMLFragment->addRawWordML($data);
       }else if(!empty($data) && is_array($data)){
           foreach($data as $key => $value){
               $wordMLFragment->addRawWordML($value);
           }
       }
       return $wordMLFragment;
    }

    /*** End old API ***/

    /**
     * Add default endnote
     *
     * @access private
     */
    private function addDefaultEndnote()
    {
        $endnote = CreateEndnote::getInstance();
        $endnote->createInitEndnote(array('type' => 'separator'));
        $this->_wordEndnotesC .= (string) $endnote;
        $endnote = CreateEndnote::getInstance();
        $endnote->createInitEndnote(array('type' => 'continuationSeparator'));
        $this->_wordEndnotesC .= (string) $endnote;
    }

    /**
     * Add default footnote
     *
     * @access private
     */
    private function addDefaultFootnote()
    {
        $footnote = CreateFootnote::getInstance();
        $footnote->createInitFootnote(array('type' => 'separator'));
        $this->_wordFootnotesC .= (string) $footnote;
        $footnote = CreateFootnote::getInstance();
        $footnote->createInitFootnote(
            array('type' => 'continuationSeparator')
        );
        $this->_wordFootnotesC .= (string) $footnote;
    }

    /**
     * Add an image in the footer
     *
     * @param array $dats Image to add and paramaters to use
     * @return string
     */
    private function addImageFooter($dats = '')
    {
        try {
            if (isset($dats['name']) && file_exists($dats['name'])) {
                $arrAtributos = getimagesize($dats['name']);
                try {
                    if (
                        $arrAtributos['mime'] == 'image/jpg' ||
                        $arrAtributos['mime'] == 'image/jpeg' ||
                        $arrAtributos['mime'] == 'image/png' ||
                        $arrAtributos['mime'] == 'image/gif'
                    ) {
                        self::$intIdWord++;
                        PhpdocxLogger::logger('New ID ' . self::$intIdWord . ' . Image footer.', 'debug');
                        $img = CreateImage::getInstance();
                        $dats['rId'] = self::$intIdWord;
                        $img->createImage($dats);
                        $xmlHeaderImg = (string) $img;
                        $dir = $this->parsePath($dats['name']);
                        PhpdocxLogger::logger('Add image header word/media/image' .
                            self::$intIdWord . '.' . $dir['extension'] .
                            '.xml to DOCX.', 'info');
                        $this->_zipDocx->addFile(
                            $dats['name'], 'word/media/image' .
                            self::$intIdWord . '.' . $dir['extension']
                        );
                        $this->generateDEFAULT(
                            $dir['extension'], $arrAtributos['mime']
                        );
                        if ((string) $img != '') {
                            $this->_wordRelsFooterRelsC .=
                                $this->generateRELATIONSHIPTemplate(
                                    'rId' . self::$intIdWord, 'image',
                                    'media/image' . self::$intIdWord .
                                    '.' . $dir['extension']
                                );
                            return $xmlHeaderImg;
                        } else {
                            throw new Exception(
                                'Image format is not supported.'
                            );
                        }
                    } else {
                        throw new Exception('Image does not exist.');
                    }
                } catch (Exception $e) {
                    PhpdocxLogger::logger($e->getMessage(), 'fatal');
                }
            }
        } catch (Exception $e) {
            PhpdocxLogger::logger($e->getMessage(), 'fatal');
        }
    }

    /**
     * Add an image in the header
     *
     * @param array $dats Image to add and paramaters to use
     * @return string
     */
    private function addImageHeader($dats = '')
    {
        try {
            if (isset($dats['name']) && file_exists($dats['name'])) {
                $attrImage = getimagesize($dats['name']);
                try {
                    if (
                        $attrImage['mime'] == 'image/jpg' ||
                        $attrImage['mime'] == 'image/jpeg' ||
                        $attrImage['mime'] == 'image/png' ||
                        $attrImage['mime'] == 'image/gif'
                    ) {
                        self::$intIdWord++;
                        PhpdocxLogger::logger('New ID ' . self::$intIdWord . ' . Image header.', 'debug');
                        $img = CreateImage::getInstance();
                        $dats['rId'] = self::$intIdWord;
                        $img->createImage($dats);
                        $xmlHeaderImg = (string) $img;
                        $dir = $this->parsePath($dats['name']);
                        PhpdocxLogger::logger('Add image header word/media/image' .
                            self::$intIdWord . '.' .
                            $dir['extension'] . '.xml to DOCX.', 'info');
                        $this->_zipDocx->addFile(
                            $dats['name'],
                            'word/media/image' . self::$intIdWord . '.' .
                            $dir['extension']
                        );
                        $this->generateDEFAULT(
                            $dir['extension'], $attrImage['mime']
                        );
                        if ((string) $img != '') {
                            $this->_wordRelsHeaderRelsC .=
                                $this->generateRELATIONSHIPTemplate(
                                    'rId' . self::$intIdWord, 'image',
                                    'media/image' . self::$intIdWord . '.' .
                                    $dir['extension']
                                );
                            return $xmlHeaderImg;
                        } else {
                            throw new Exception(
                                'Image format is not supported.'
                            );
                        }
                    } else {
                        throw new Exception('Image does not exist.');
                    }
                } catch (Exception $e) {
                    PhpdocxLogger::logger($e->getMessage(), 'fatal');
                }
            }
        } catch (Exception $e) {
            PhpdocxLogger::logger($e->getMessage(), 'fatal');
        }
    }

    /**
     * Add settings
     *
     * @access private
     */
    private function addSettings()
    {
        $settings = CreateSettings::getInstance();
        $settings->generateSettings();
        PhpdocxLogger::logger('Add settings to settings document.', 'info');
        $this->_wordSettingsC .= (string) $settings;
    }

    /**
     * Add style
     *
     * @param string lang Language
     * @access private
     */
    private function addStyle($lang = 'en-US')
    {
        $style = CreateStyle::getInstance();
        $style->createStyle($lang);
        PhpdocxLogger::logger('Add styles to styles document.', 'info');
        $this->_wordStylesC .= (string) $style;
    }

    /**
     * Imports styles into the template stylesheet.
     *
     * @access private
     * @param string $templateStyles
     * @param DOMDocument $importedStylesheet
     */
    private function addStylesTemplate($templateStyles, $importedStylesheet)
    {

        $templateStylesheet = new DomDocument();
        $templateStylesheet->loadXML($templateStyles);
        //let's parse the different styles via XPath

        $stylesXpath = new DOMXPath($importedStylesheet);
        $stylesXpath->registerNamespace('w', 'http://schemas.openxmlformats.org/wordprocessingml/2006/main');
        $queryStyle = '//w:style';
        $styleNodes = $stylesXpath->query($queryStyle);

        //Let's get the original styles as a DOMNode
        $stylesDocument = new DomDocument();
        $stylesDocument->loadXML($templateStyles);
        $baseNode = $stylesDocument->documentElement;

        //Now we start to insert the new styles at the end of the styles.xml
        foreach ($styleNodes as $node) {
           // in order to avoid duplicated Ids we first remove from the
           // original styles any duplicity with the new ones
            $originalNodes = $stylesDocument->childNodes;
            foreach($originalNodes as $oldNode) {
                if ($oldNode->getAttribute('w:styleId') == $node->getAttribute('w:styleId')) {
                    $oldNode->parent->removeChild($oldNode);
                }
            }
            $insertNode = $stylesDocument->importNode($node, true);
            $baseNode->appendChild($insertNode);
        }
        PhpdocxLogger::logger('Importing styles into the template stylesheet.', 'info');

        return $stylesDocument->saveXML();
    }

    /**
     * Add websettings
     *
     * @access private
     */
    private function addWebSettings()
    {
        $webSettings = CreateWebSettings::getInstance();
        $webSettings->generateWebSettings();
        PhpdocxLogger::logger('Add web settings to web settings document.', 'info');
        $this->_wordWebSettingsC .= (string) $webSettings;
    }

    /**
     * Clean template
     *
     * @access private
     */
    private function cleanTemplate()
    {
        PhpdocxLogger::logger('Remove existing template tags.', 'debug');
        $this->_wordDocumentT = preg_replace(
            '/__[A-Z]+__/',
            '',
            $this->_wordDocumentT
        );
    }

    /**
     * Generate content type
     *
     * @access private
     */
    private function generateContentType()
    {
        try {
            GenerateDocx::beginDocx();
        } catch (Exception $e) {
            PhpdocxLogger::logger($e->getMessage(), 'fatal');
        }
        $this->generateDEFAULT(
            'rels', 'application/vnd.openxmlformats-package.relationships+xml'
        );
        $this->generateDEFAULT('xml', 'application/xml');
        $this->generateDEFAULT('htm', 'application/xhtml+xml');
        $this->generateDEFAULT('rtf', 'application/rtf');
        $this->generateDEFAULT('zip', 'application/vnd.openxmlformats-officedocument.wordprocessingml.document.main+xml');
        $this->generateDEFAULT('mht', 'message/rfc822');
        $this->generateDEFAULT('wml', 'application/vnd.openxmlformats-officedocument.wordprocessingml.document.main+xml');
        $this->generateOVERRIDE(
            '/word/numbering.xml',
            'application/vnd.openxmlformats-officedocument.wordprocessingml.' .
            'numbering+xml'
        );
        $this->generateOVERRIDE(
            '/word/styles.xml',
            'application/vnd.openxmlformats-officedocument.wordprocessingml' .
            '.styles+xml'
        );
        $this->generateOVERRIDE(
            '/docProps/app.xml',
            'application/vnd.openxmlformats-officedocument.extended-' .
            'properties+xml'
        );
        $this->generateOVERRIDE(
            '/docProps/custom.xml',
            'application/vnd.openxmlformats-officedocument.' .
            'custom-properties+xml'
        );
        $this->generateOVERRIDE(
            '/word/settings.xml', 'application/' .
            'vnd.openxmlformats-officedocument.wordprocessingml.settings+xml'
        );
        $this->generateOVERRIDE(
            '/word/theme/theme1.xml',
            'application/vnd.openxmlformats-officedocument.theme+xml'
        );
        $this->generateOVERRIDE(
            '/word/fontTable.xml',
            'application/vnd.openxmlformats-officedocument.wordprocessingml.' .
            'fontTable+xml'
        );
        $this->generateOVERRIDE(
            '/word/webSettings.xml',
            'application/vnd.openxmlformats-officedocument.wordprocessingml' .
            '.webSettings+xml'
        );
        if ($this->_wordFooterC != '' || $this->_wordHeaderC != '') {
            $this->generateOVERRIDE(
                '/word/header.xml',
                'application/vnd.openxmlformats-officedocument.' .
                'wordprocessingml.header+xml'
            );
            $this->generateOVERRIDE(
                '/word/footer.xml',
                'application/vnd.openxmlformats-officedocument.' .
                'wordprocessingml.footer+xml'
            );
            $this->generateOVERRIDE(
                '/word/footnotes.xml',
                'application/vnd.openxmlformats-officedocument.' .
                'wordprocessingml.footnotes+xml'
            );
            $this->generateOVERRIDE(
                '/word/endnotes.xml',
                'application/vnd.openxmlformats-officedocument.' .
                'wordprocessingml.endnotes+xml'
            );
        }
        $this->generateOVERRIDE(
            '/docProps/core.xml',
            'application/vnd.openxmlformats-package.core-properties+xml'
        );
    }

    /**
     * Generate DEFAULT
     *
     * @access private
     */
    private function generateDEFAULT($extension, $contentType)
    {
        $strContent = $this->_contentTypeT->saveXML();
        if (
            strpos($strContent, 'Extension="' . $extension)
            === false
        ) {
            $strContentTypes = '<Default Extension="'.$extension .'" ContentType="'. $contentType .'"> </Default>';
            $tempNode = $this->_contentTypeT->createDocumentFragment();
            $tempNode->appendXML($strContentTypes);
            $this->_contentTypeT->documentElement->appendChild($tempNode);
        }
    }

    /**
     *
     *
     * @access private
     */
    private function generateDefaultFonts()
    {
        $font = array(
            'name' => 'Calibri', 'pitch' => 'variable', 'usb0' => 'A00002EF',
            'usb1' => '4000207B', 'usb2' => '00000000', 'usb3' => '00000000',
            'csb0' => '0000009F', 'csb1' => '00000000', 'family' => 'swiss',
            'charset' => '00', 'panose1' => '020F0502020204030204'
        );
        $this->addFont($font);
        $font = array(
            'name' => 'Times New Roman', 'pitch' => 'variable',
            'usb0' => 'E0002AEF', 'usb1' => 'C0007841', 'usb2' => '00000009',
            'usb3' => '00000000', 'csb0' => '000001FF', 'csb1' => '00000000',
            'family' => 'roman', 'charset' => '00',
            'panose1' => '02020603050405020304'
        );
        $this->addFont($font);
        $font = array(
            'name' => 'Cambria', 'pitch' => 'variable', 'usb0' => 'A00002EF',
            'usb1' => '4000004B', 'usb2' => '00000000', 'usb3' => '00000000',
            'csb0' => '0000009F', 'csb1' => '00000000', 'family' => 'roman',
            'charset' => '00', 'panose1' => '02040503050406030204'
        );
        $this->addFont($font);
    }

    /**
     * Generate DefaultWordRels
     *
     * @access private
     */
    private function generateDefaultWordRels()
    {
        self::$intIdWord++;
        PhpdocxLogger::logger('New ID ' . self::$intIdWord . ' . numbering.xml.', 'debug');
        $this->_wordRelsDocumentRelsC .= $this->generateRELATIONSHIP(
            'rId' . self::$intIdWord, 'numbering', 'numbering.xml'
        );
        self::$intIdWord++;
        PhpdocxLogger::logger('New ID ' . self::$intIdWord . ' . theme/theme1.xml.', 'debug');
        $this->_wordRelsDocumentRelsC .= $this->generateRELATIONSHIP(
            'rId' . self::$intIdWord, 'theme', 'theme/theme1.xml'
        );
        self::$intIdWord++;
        PhpdocxLogger::logger('New ID ' . self::$intIdWord . ' . numbering.xml.', 'debug');
        $this->_wordRelsDocumentRelsC .= $this->generateRELATIONSHIP(
            'rId' . self::$intIdWord, 'webSettings', 'webSettings.xml'
        );
        self::$intIdWord++;
        PhpdocxLogger::logger('New ID ' . self::$intIdWord . ' . webSettings.xml.', 'debug');
        $this->_wordRelsDocumentRelsC .= $this->generateRELATIONSHIP(
            'rId' . self::$intIdWord, 'fontTable', 'fontTable.xml'
        );
        self::$intIdWord++;
        PhpdocxLogger::logger('New ID ' . self::$intIdWord . ' . fontTable.xml.', 'debug');
        $this->_wordRelsDocumentRelsC .= $this->generateRELATIONSHIP(
            'rId' . self::$intIdWord, 'settings', 'settings.xml'
        );
        self::$intIdWord++;
        PhpdocxLogger::logger('New ID ' . self::$intIdWord . ' . settings.xml.', 'debug');
        $this->_wordRelsDocumentRelsC .= $this->generateRELATIONSHIP(
            'rId' . self::$intIdWord, 'styles', 'styles.xml'
        );
    }


    /**
     * Generate OVERRIDE
     *
     * @access private
     * @param string $partName
     * @param string $contentType
     */
    private function generateOVERRIDE($partName, $contentType)
    {
        $strContent = $this->_contentTypeT->saveXML();
        if (
            strpos($strContent, 'PartName="' . $partName . '"')
            === false
        ) {
            $strContentTypes = '<Override PartName="'.$partName.'" ContentType="'.$contentType.'" />';
            $tempNode = $this->_contentTypeT->createDocumentFragment();
            $tempNode->appendXML($strContentTypes);
            $this->_contentTypeT->documentElement->appendChild($tempNode);
        }
    }

    /**
     * Generate RELATIONSHIP
     *
     * @access private
     */
    private function generateRELATIONSHIP()
    {
        $arrArgs = func_get_args();
        if ($arrArgs[1] == 'vbaProject') {
            $type =
            'http://schemas.microsoft.com/office/2006/relationships/vbaProject';
        } else {
            $type =
            'http://schemas.openxmlformats.org/officeDocument/2006/' .
            'relationships/' . $arrArgs[1];
        }

        if (!isset($arrArgs[3])) {
            $nodeWML = '<Relationship Id="' . $arrArgs[0] . '" Type="' . $type .
               '" Target="' . $arrArgs[2] . '"></Relationship>';

        } else {
            $nodeWML = '<Relationship Id="' . $arrArgs[0] . '" Type="' . $type .
               '" Target="' . $arrArgs[2] . '" ' . $arrArgs[3] .
               '></Relationship>';
        }
      $relsNode = $this->_wordRelsDocumentRelsT->createDocumentFragment();
       $relsNode->appendXML($nodeWML);
       $this->_wordRelsDocumentRelsT->documentElement->appendChild($relsNode);


    }

        /**
     * Gnerate RELATIONSHIP
     *
     * @access private
     */
    private function generateRELATIONSHIPTemplate()
    {
        $arrArgs = func_get_args();
        if ($arrArgs[1] == 'vbaProject') {
            $type =
            'http://schemas.microsoft.com/office/2006/relationships/vbaProject';
        } else {
            $type =
            'http://schemas.openxmlformats.org/officeDocument/2006/' .
            'relationships/' . $arrArgs[1];
        }

        if (!isset($arrArgs[3])) {
            $nodeWML = '<Relationship Id="' . $arrArgs[0] . '" Type="' . $type .
               '" Target="' . $arrArgs[2] . '"></Relationship>';

        } else {
            $nodeWML = '<Relationship Id="' . $arrArgs[0] . '" Type="' . $type .
               '" Target="' . $arrArgs[2] . '" ' . $arrArgs[3] .
               '></Relationship>';
        }
       /*$relsNode = $this->_wordRelsDocumentRelsT->createDocumentFragment();
       $relsNode->appendXML($nodeWML);
       $this->_wordRelsDocumentRelsT->documentElement->appendChild($relsNode);*/

       return $nodeWML;
    }

    /**
     * Modify/create the rels files for footnotes, endnotes and comments
     * @param string $type can be footnote, endnote or comment
     * @access private
     */
    private function generateRelsNotes($type)
    {
        try {
            $relsFile = $this->_baseTemplateZip->getFromName('word/_rels/' . $type . 's.xml.rels');
            if (!$relsFile) {
                $relsFile = '<?xml version="1.0" encoding="UTF-8" standalone="yes"?><Relationships xmlns="http://schemas.openxmlformats.org/package/2006/relationships"></Relationships>';
                throw new Exception('The ' . $type . '.xml.rels file from the base template was not found. PHPDocX generated it.');
            }
        }
        catch (Exception $e) {
            PhpdocxLogger::logger($e->getMessage(), 'info');
        }
        $relsDOM = new DOMDocument();
        $relsDOM->loadXML($relsFile);

        if(!empty($this->_relsNotesImage[$type])){
            foreach($this->_relsNotesImage[$type] as $key => $value){
                $nodeWML = '<Relationship Id="' . $value['rId'] . '" Type="http://schemas.openxmlformats.org/officeDocument/2006/relationships/image" Target="media/img' . $value['rId'] . '.' . $value['extension'] .'" ></Relationship>';
                $relsNode = $relsDOM->createDocumentFragment();
                $relsNode->appendXML($nodeWML);
                $relsDOM->documentElement->appendChild($relsNode);
            }
        }
        if(!empty($this->_relsNotesExternalImage[$type])){
            foreach($this->_relsNotesExternalImage[$type] as $key => $value){
                $nodeWML = '<Relationship Id="' . $value['rId'] . '" Type="http://schemas.openxmlformats.org/officeDocument/2006/relationships/image" Target="' . $value['url'] . '" TargetMode="External" ></Relationship>';
                $relsNode = $relsDOM->createDocumentFragment();
                $relsNode->appendXML($nodeWML);
                $relsDOM->documentElement->appendChild($relsNode);
            }
        }
        if(!empty($this->_relsNotesLink[$type])){
            foreach($this->_relsNotesLink[$type] as $key => $value){
                $nodeWML = '<Relationship Id="' . $value['rId'] . '" Type="http://schemas.openxmlformats.org/officeDocument/2006/relationships/hyperlink" Target="' . $value['url'] . '" TargetMode="External" ></Relationship>';
                $relsNode = $relsDOM->createDocumentFragment();
                $relsNode->appendXML($nodeWML);
                $relsDOM->documentElement->appendChild($relsNode);
            }
        }

        $noteHandler = fopen($this->_baseTemplateFilesPath . '/word/_rels/' . $type . 's.xml.rels', 'w+');
        fwrite($noteHandler, $relsDOM->saveXML());
        fclose($noteHandler);
    }

    /**
     * Generate SECTPR
     *
     * @access private
     * @param array $args Section style
     */
    private function generateSECTPR($args = '')
    {
        $page = CreatePage::getInstance();
        $page->createSECTPR($args);
        $this->_wordDocumentC .= (string) $page;
    }

    /**
     * Generates an element in settings.xml
     *
     * @access private
     */
    private function generateSetting($tag)
    {
        if((!in_array($tag, self::$settings))){
           PhpdocxLogger::logger('Incorrect setting tag', 'fatal');
        }
        $settingIndex = array_search($tag, self::$settings);
        try{
            $settings = fopen($this->_baseTemplateFilesPath.'/word/settings.xml', "r");
            $baseTemplateSettingsT = fread($settings, 1000000);
            fclose($settings);
            if ($baseTemplateSettingsT == '') {
                throw new Exception('Error while extracting settings.xml file from the base template to insert the selected element');
            }
        }
        catch (Exception $e) {
            PhpdocxLogger::logger($e->getMessage(), 'fatal');
        }

        $this->_wordSettingsT = new DOMDocument();
        $this->_wordSettingsT->loadXML($baseTemplateSettingsT);
        $selectedElements = $this->_wordSettingsT->documentElement->getElementsByTagName($tag);
        if($selectedElements->length == 0){
            $settingsElement = $this->_wordSettingsT->createDocumentFragment();
            $settingsElement->appendXML('<' . $tag . ' xmlns:w="http://schemas.openxmlformats.org/wordprocessingml/2006/main" />');
            $childNodes = $this->_wordSettingsT->documentElement->childNodes;
            $index = false;
            foreach($childNodes as $node){
                $name = $node->nodeName;
                $index = array_search($node->nodeName, self::$settings);
                if($index > $settingIndex){
                    $node->parentNode->insertBefore($settingsElement, $node);
                    break;
                }
            }
            //in case no node was found (pretty unlikely)we should append the node
            if (!$index) {
                $this->_wordSettingsT->documentElement->appendChild($settingsElement);
            }
            $newSettings = $this->_wordSettingsT->saveXML();
            $settingsHandle = fopen($this->_baseTemplateFilesPath.'/word/settings.xml', "w+");
            $contents = fwrite($settingsHandle, $newSettings);
            fclose($settingsHandle);
        }

    }

    /**
     * Generate ContentType XML template
     *
     * @access private
     */
    private function generateTemplateContentType()
    {
        $this->_wordContentTypeT =
            '<?xml version="1.0" encoding="UTF-8" standalone="yes" ?>' .
            '<Types xmlns="http://schemas.openxmlformats.org/package/2006/' .
            'content-types">' . $this->_contentTypeC . '</Types>';
    }

    /**
     * Generate DocPropsApp XML template
     *
     * @access private
     */
    private function generateTemplateDocPropsApp()
    {
        $this->_docPropsAppT =
            '<?xml version="1.0" encoding="UTF-8" standalone="yes"?>' .
            '<Properties xmlns="http://schemas.openxmlformats.org/' .
            'officeDocument/2006/extended-properties" xmlns:vt="' .
            'http://schemas.openxmlformats.org/officeDocument/2006/' .
            'docPropsVTypes"><Template>Normal.dotm</Template><TotalTime>' .
            '0</TotalTime><Pages>1</Pages><Words>1</Words><Characters>1'
            . '</Characters><Application>Microsoft Office Word</Application>' .
            '<DocSecurity>4</DocSecurity><Lines>1</Lines><Paragraphs>1' .
            '</Paragraphs><ScaleCrop>false</ScaleCrop>';
        if ($this->_docPropsAppC) {
            $this->_docPropsAppT .= $this->_docPropsAppC;
        } else {
            $this->_docPropsAppT .= '<Company>Company</Company>';
        }
        $this->_docPropsAppT .= '<LinksUpToDate>false</LinksUpToDate>' .
            '<CharactersWithSpaces>1</CharactersWithSpaces><SharedDoc>' .
            'false</SharedDoc><HyperlinksChanged>false</HyperlinksChanged>' .
            '<AppVersion>12.0000</AppVersion></Properties>';
    }

    /**
     * Generate DocPropsCore XML template
     *
     * @access private
     */
    private function generateTemplateDocPropsCore()
    {
        date_default_timezone_set('UTC');
        if ($this->_markAsFinal) {
            $this->_docPropsCoreT =
                '<?xml version="1.0" encoding="UTF-8" standalone="yes"?>' .
                '<cp:coreProperties xmlns:cp="http://schemas.openxmlformats' .
                '.org/package/2006/metadata/core-properties" ' .
                'xmlns:dc="http://purl.org/dc/elements/1.1/" xmlns:dcterms' .
                '="http://purl.org/dc/terms/" xmlns:dcmitype="http://purl' .
                '.org/dc/dcmitype/" xmlns:xsi="http://www.w3.org/2001/XML' .
                'Schema-instance"><dc:title>Title</dc:title><dc:subject>' .
                'Subject</dc:subject><dc:creator>2mdc</dc:creator>' .
                '<dc:description>Description</dc:description>' .
                '<cp:lastModifiedBy>user</cp:lastModifiedBy><cp:revision>1' .
                '</cp:revision><dcterms:created xsi:type="dcterms:W3CDTF">' .
                date('c') . '</dcterms:created><dcterms:modified ' .
                'xsi:type="dcterms:W3CDTF">' . date('c') .
                '</dcterms:modified><cp:contentStatus>Final' .
                '</cp:contentStatus></cp:coreProperties>';
        } else {
            $this->_docPropsCoreT =
                '<?xml version="1.0" encoding="UTF-8" standalone="yes"?> ' .
                '<cp:coreProperties xmlns:cp="http://schemas.openxmlformats' .
                '.org/package/2006/metadata/core-properties" ' .
                'xmlns:dc="http://purl.org/dc/elements/1.1/" ' .
                'xmlns:dcterms="http://purl.org/dc/terms/" ' .
                'xmlns:dcmitype="http://purl.org/dc/dcmitype/" ' .
                'xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance">' .
                '<dc:title>Title</dc:title><dc:subject>Subject</dc:subject>' .
                '<dc:creator>2mdc</dc:creator><dc:description>Description' .
                '</dc:description><cp:lastModifiedBy>user' .
                '</cp:lastModifiedBy><cp:revision>1</cp:revision>' .
                '<dcterms:created xsi:type="dcterms:W3CDTF">' . date('c') .
                '</dcterms:created><dcterms:modified xsi:type="dcterms:W3CDTF' .
                '">' . date('c') . '</dcterms:modified></cp:coreProperties>';
        }
    }

    /**
     * Generate DocPropsCustom XML template
     *
     * @access private
     */
    private function generateTemplateDocPropsCustom()
    {
        $this->_docPropsCustomT =
            '<?xml version="1.0" encoding="UTF-8" standalone="yes"?>' .
            '<Properties xmlns="http://schemas.openxmlformats.org/' .
            'officeDocument/2006/custom-properties" xmlns:vt="http://' .
            'schemas.openxmlformats.org/officeDocument/2006/docPropsVTypes">' .
            '<property fmtid="{D5CDD505-2E9C-101B-9397-08002B2CF9AE}" ' .
            'pid="2" name="_MarkAsFinal"><vt:bool>true</vt:bool></property>' .
            '</Properties>';
    }

    /**
     * Generate RelsRels XML template
     *
     * @access private
     */
    private function generateTemplateRelsRels()
    {
        $this->_relsRelsT =
            '<?xml version="1.0" encoding="UTF-8" standalone="yes"?>' .
            '<Relationships xmlns="http://schemas.openxmlformats.org/package/' .
            '2006/relationships">' .
            $this->generateRELATIONSHIP(
                'rId3', 'extended-properties', 'docProps/app.xml'
            ) .
            '<Relationship Id="rId2" Type="http://schemas.openxmlformats' .
            '.org/package/2006/relationships/metadata/core-properties"' .
            ' Target="docProps/core.xml"/>' .
            $this->generateRELATIONSHIP(
                'rId1', 'officeDocument', 'word/document.xml'
            );
        if ($this->_markAsFinal) {
            $this->_relsRelsT .=
                '<Relationship Id="rId4" Type="http://schemas' .
                '.openxmlformats.org/officeDocument/2006/relationships/' .
                'custom-properties" Target="docProps/custom.xml"/>';
        }
        $this->_relsRelsT .= '</Relationships>';
    }

    /**
     * Generate WordDocument XML template
     *
     * @access private
     */
    private function generateTemplateWordDocument()
    {
        $arrArgs = func_get_args();
        //$this->generateSECTPR($arrArgs[0]);
        $this->_wordDocumentC .= $this->_sectPr->saveXML($this->_sectPr->documentElement);//FIXME: I am insertying by hand the sections of the base template
        if (!empty($this->_wordHeaderC)) {
            $this->_wordDocumentC = str_replace(
                '__GENERATEHEADERREFERENCE__',
                '<' . CreateDocx::NAMESPACEWORD . ':headerReference ' .
                CreateDocx::NAMESPACEWORD . ':type="default" r:id="rId' .
                $this->_idWords['header'] . '"></' .
                CreateDocx::NAMESPACEWORD . ':headerReference>',
                $this->_wordDocumentC
            );
        }
        if (!empty($this->_wordFooterC)) {
            $this->_wordDocumentC = str_replace(
                '__GENERATEFOOTERREFERENCE__',
                '<' . CreateDocx::NAMESPACEWORD . ':footerReference ' .
                CreateDocx::NAMESPACEWORD . ':type="default" r:id="rId' .
                $this->_idWords['footer'] . '"></' .
                CreateDocx::NAMESPACEWORD . ':footerReference>',
                $this->_wordDocumentC
            );
        }
        $this->_wordDocumentT =
            '<?xml version="1.0" encoding="UTF-8" standalone="yes"?>' .
            '<' . CreateDocx::NAMESPACEWORD . ':document xmlns:ve=' .
            '"http://schemas.openxmlformats.org/markup-compatibility/2006" ' .
            'xmlns:o="urn:schemas-microsoft-com:office:office"' .
            ' xmlns:r="http://schemas.openxmlformats.org/officeDocument/2006' .
            '/relationships" xmlns:m="http://schemas.openxmlformats.org/' .
            'officeDocument/2006/math" xmlns:v="urn:schemas-microsoft-com:vml"'.
            ' xmlns:wp="http://schemas.openxmlformats.org/drawingml/2006/' .
            'wordprocessingDrawing" xmlns:w10="urn:schemas-microsoft-com:' .
            'office:word" xmlns:w="http://schemas.openxmlformats.org/' .
            'wordprocessingml/2006/main" xmlns:wne="http://schemas' .
            '.microsoft.com/office/word/2006/wordml">' .
            $this->_background.
            '<' . CreateDocx::NAMESPACEWORD . ':body>' .
            $this->_wordDocumentC .
            '</' . CreateDocx::NAMESPACEWORD . ':body>' .
            '</' . CreateDocx::NAMESPACEWORD . ':document>';
        $this->cleanTemplate();
    }

    /**
     * Generate WordEndnotes XML template
     *
     * @access private
     */
    private function generateTemplateWordEndnotes()
    {
        $this->_wordEndnotesT =
            '<?xml version="1.0" encoding="UTF-8" standalone="yes"?>' .
            '<' . CreateDocx::NAMESPACEWORD . ':endnotes xmlns:ve' .
            '="http://schemas.openxmlformats.org/markup-compatibility/2006" ' .
            'xmlns:o="urn:schemas-microsoft-com:office:office" xmlns:r="' .
            'http://schemas.openxmlformats.org/officeDocument/2006/' .
            'relationships" xmlns:m="http://schemas.openxmlformats.org/' .
            'officeDocument/2006/math" xmlns:v="urn:schemas-microsoft-com:' .
            'vml" xmlns:wp="http://schemas.openxmlformats.org/drawingml/2006' .
            '/wordprocessingDrawing" xmlns:w10="urn:schemas-microsoft-com:' .
            'office:word" xmlns:w="http://schemas.openxmlformats.org/' .
            'wordprocessingml/2006/main" xmlns:wne="http://schemas' .
            '.microsoft.com/office/word/2006/wordml">' .
            $this->_wordEndnotesC .
            '</' . CreateDocx::NAMESPACEWORD . ':endnotes>';
        self::$intIdWord++;
        PhpdocxLogger::logger('New ID ' . self::$intIdWord . ' . Endnotes.', 'debug');
        $this->_wordRelsDocumentRelsC .= $this->generateRELATIONSHIP(
            'rId' . self::$intIdWord, 'endnotes', 'endnotes.xml'
        );
        $this->generateOVERRIDE(
            '/word/endnotes.xml',
            'application/vnd.openxmlformats-officedocument.wordprocessingml' .
            '.endnotes+xml'
        );
    }

    /**
     * Generate WordFontTable XML template
     *
     * @access private
     */
    private function generateTemplateWordFontTable()
    {
        $this->_wordFontTableT =
            '<?xml version="1.0" encoding="UTF-8" standalone="yes" ?>' .
            '<' . CreateDocx::NAMESPACEWORD . ':fonts xmlns:r="http://' .
            'schemas.openxmlformats.org/officeDocument/2006/' .
            'relationships" xmlns:w="http://schemas.openxmlformats.org/' .
            'wordprocessingml/2006/main">' . $this->_wordFontTableC .
            '</' . CreateDocx::NAMESPACEWORD . ':fonts>';
    }

    /**
     * Generate WordFooter XML template
     *
     * @access private
     */
    private function generateTemplateWordFooter()
    {
        self::$intIdWord++;
        PhpdocxLogger::logger('New ID ' . self::$intIdWord . ' . Footer.', 'debug');
        $this->_idWords['footer'] = self::$intIdWord;
        $this->_wordFooterT =
            '<?xml version="1.0" encoding="UTF-8" standalone="yes"?>
            <' . CreateDocx::NAMESPACEWORD . ':ftr xmlns:ve' .
            '="http://schemas.openxmlformats.org/markup-compatibility/' .
            '2006" xmlns:o="urn:schemas-microsoft-com:office:office" xmlns' .
            ':r="http://schemas.openxmlformats.org/officeDocument/2006/' .
            'relationships" xmlns:m="http://schemas.openxmlformats.org/' .
            'officeDocument/2006/math" xmlns:v="urn:schemas-microsoft-com:vml' .
            '" xmlns:wp="http://schemas.openxmlformats.org/drawingml/2006/' .
            'wordprocessingDrawing" xmlns:w10="urn:schemas-microsoft-com:' .
            'office:word" xmlns:w="http://schemas.openxmlformats.org/' .
            'wordprocessingml/2006/main" xmlns:wne="http://schemas' .
            '.microsoft.com/office/word/2006/wordml">' . $this->_wordFooterC .
            '</' . CreateDocx::NAMESPACEWORD . ':ftr>';
        $this->_wordRelsDocumentRelsC .= $this->generateRELATIONSHIP(
            'rId' . self::$intIdWord, 'footer', 'footer.xml'
        );

        return 'rId' . self::$intIdWord;
    }

    /**
     * Generate WordFootnotes XML template
     *
     * @access private
     */
    private function generateTemplateWordFootnotes()
    {
        $this->_wordFootnotesT =
            '<?xml version="1.0" encoding="UTF-8" standalone="yes"?>' .
            '<' . CreateDocx::NAMESPACEWORD . ':footnotes xmlns:ve="' .
            'http://schemas.openxmlformats.org/markup-compatibility/2006" ' .
            'xmlns:o="urn:schemas-microsoft-com:office:office" xmlns:r="' .
            'http://schemas.openxmlformats.org/officeDocument/2006/' .
            'relationships" xmlns:m="http://schemas.openxmlformats.org/' .
            'officeDocument/2006/math" xmlns:v="urn:schemas-microsoft-com:' .
            'vml" xmlns:wp="http://schemas.openxmlformats.org/drawingml/2006' .
            '/wordprocessingDrawing" xmlns:w10="urn:schemas-microsoft-com:' .
            'office:word" xmlns:w="http://schemas.openxmlformats.org/' .
            'wordprocessingml/2006/main" xmlns:wne="http://schemas.microsoft' .
            '.com/office/word/2006/wordml">' . $this->_wordFootnotesC .
            '</' . CreateDocx::NAMESPACEWORD . ':footnotes>';
        self::$intIdWord++;
        PhpdocxLogger::logger('New ID ' . self::$intIdWord . ' . Footnotes.', 'debug');
        $this->_wordRelsDocumentRelsC .= $this->generateRELATIONSHIP(
            'rId' . self::$intIdWord, 'footnotes', 'footnotes.xml'
        );
        $this->generateOVERRIDE(
            '/word/footnotes.xml',
            'application/vnd.openxmlformats-officedocument.wordprocessingml' .
            '.footnotes+xml'
        );
    }

    /**
     * Generate WordHeader XML template
     *
     * @access private
     */
    private function generateTemplateWordHeader()
    {
        self::$intIdWord++;
        PhpdocxLogger::logger('New ID ' . self::$intIdWord . ' . Header.', 'debug');
        $this->_idWords['header'] = self::$intIdWord;
        $this->_wordHeaderT = '<?xml version="1.0" encoding="UTF-8" ' .
            'standalone="yes"?>' .
            '<' . CreateDocx::NAMESPACEWORD .
            ':hdr xmlns:ve="http://schemas.openxmlformats.org/markup' .
            '-compatibility/2006" xmlns:o="urn:schemas-microsoft-com:' .
            'office:office" xmlns:r="http://schemas.openxmlformats.org/' .
            'officeDocument/2006/relationships" xmlns:m="http://schemas' .
            '.openxmlformats.org/officeDocument/2006/math" xmlns:v="urn:' .
            'schemas-microsoft-com:vml" xmlns:wp="http://schemas' .
            '.openxmlformats.org/drawingml/2006/wordprocessingDrawing" ' .
            'xmlns:w10="urn:schemas-microsoft-com:office:word" xmlns:w="' .
            'http://schemas.openxmlformats.org/wordprocessingml/2006/' .
            'main" xmlns:wne="http://schemas.microsoft.com/office/word/' .
            '2006/wordml"> ' . $this->_wordHeaderC .
            '</' . CreateDocx::NAMESPACEWORD . ':hdr>';
        $this->_wordRelsDocumentRelsC .= $this->generateRELATIONSHIP(
            'rId' . self::$intIdWord, 'header', 'header.xml'
        );
        return 'rId' . self::$intIdWord;
    }

    /**
     * Generate WordNumbering XML template
     *
     * @access private
     */
    private function generateTemplateWordNumbering()
    {
        $this->_wordNumberingT =
            '<?xml version="1.0" encoding="UTF-8" standalone="yes"?>' .
            '<w:numbering xmlns:ve="http://schemas.openxmlformats' .
            '.org/markup-compatibility/2006" xmlns:o="urn:schemas-' .
            'microsoft-com:office:office" xmlns:r="http://schemas' .
            '.openxmlformats.org/officeDocument/2006/relationships" ' .
            'xmlns:m="http://schemas.openxmlformats.org/officeDocument/' .
            '2006/math" xmlns:v="urn:schemas-microsoft-com:vml" xmlns:' .
            'wp="http://schemas.openxmlformats.org/drawingml/2006/' .
            'wordprocessingDrawing" xmlns:w10="urn:schemas-microsoft-com' .
            ':office:word" xmlns:w="http://schemas.openxmlformats.org/' .
            'wordprocessingml/2006/main" xmlns:wne="http://schemas.' .
            'microsoft.com/office/word/2006/wordml"><w:abstractNum w:'
            . 'abstractNumId="0"><w:nsid w:val="713727AE"/><w:multiLevelType' .
            ' w:val="hybridMultilevel"/><w:tmpl w:val="F0B4B6B8"/>' .
            '<w:lvl w:ilvl="0" w:tplc="0C0A0001"><w:start w:val="1"/>' .
            '<w:numFmt w:val="bullet"/><w:lvlText w:val=""/><w:lvlJc ' .
            'w:val="left"/><w:pPr><w:ind w:left="720" w:hanging="360"/>' .
            '</w:pPr><w:rPr><w:rFonts w:ascii="Symbol" w:hAnsi="Symbol" ' .
            'w:hint="default"/></w:rPr></w:lvl><w:lvl w:ilvl="1" ' .
            'w:tplc="0C0A0003" w:tentative="1"><w:start w:val="1"/>' .
            '<w:numFmt w:val="bullet"/><w:lvlText w:val="o"/><w:lvlJc ' .
            'w:val="left"/><w:pPr><w:ind w:left="1440" w:hanging="360"/>' . '
                </w:pPr><w:rPr><w:rFonts w:ascii="Courier New" w:hAnsi=' .
            '"Courier New" w:cs="Courier New" w:hint="default"/></w:rPr>' .
            '</w:lvl><w:lvl w:ilvl="2" w:tplc="0C0A0005" w:tentative="1">' .
            '<w:start w:val="1"/><w:numFmt w:val="bullet"/><w:lvlText ' .
            'w:val=""/><w:lvlJc w:val="left"/><w:pPr><w:ind w:left="2160" ' .
            'w:hanging="360"/></w:pPr><w:rPr><w:rFonts w:ascii="Wingdings" ' .
            'w:hAnsi="Wingdings" w:hint="default"/></w:rPr></w:lvl><w:lvl ' .
            'w:ilvl="3" w:tplc="0C0A0001" w:tentative="1"><w:start ' .
            'w:val="1"/><w:numFmt w:val="bullet"/><w:lvlText w:val=""/>' .
            '<w:lvlJc w:val="left"/><w:pPr><w:ind w:left="2880" w:hanging=' .
            '"360"/></w:pPr><w:rPr><w:rFonts w:ascii="Symbol" w:hAnsi=' .
            '"Symbol" w:hint="default"/></w:rPr></w:lvl><w:lvl w:ilvl="4" ' .
            'w:tplc="0C0A0003" w:tentative="1"><w:start w:val="1"/>' .
            '<w:numFmt w:val="bullet"/><w:lvlText w:val="o"/><w:lvlJc ' .
            'w:val="left"/><w:pPr><w:ind w:left="3600" w:hanging="360"/>' .
            '</w:pPr><w:rPr><w:rFonts w:ascii="Courier New" w:hAnsi=' .
            '"Courier New" w:cs="Courier New" w:hint="default"/></w:rPr>' .
            '</w:lvl><w:lvl w:ilvl="5" w:tplc="0C0A0005" w:tentative="1">' .
            '<w:start w:val="1"/><w:numFmt w:val="bullet"/><w:lvlText ' .
            'w:val=""/><w:lvlJc w:val="left"/><w:pPr><w:ind w:left="4320" ' .
            'w:hanging="360"/></w:pPr><w:rPr><w:rFonts w:ascii="Wingdings" ' .
            'w:hAnsi="Wingdings" w:hint="default"/></w:rPr></w:lvl><w:lvl ' .
            'w:ilvl="6" w:tplc="0C0A0001" w:tentative="1"><w:start ' .
            'w:val="1"/><w:numFmt w:val="bullet"/><w:lvlText w:val=""/>' .
            '<w:lvlJc w:val="left"/><w:pPr><w:ind w:left="5040" ' .
            'w:hanging="360"/></w:pPr><w:rPr><w:rFonts w:ascii="Symbol" ' .
            'w:hAnsi="Symbol" w:hint="default"/></w:rPr></w:lvl><w:lvl ' .
            'w:ilvl="7" w:tplc="0C0A0003" w:tentative="1"><w:start ' .
            'w:val="1"/><w:numFmt w:val="bullet"/><w:lvlText w:val="o"/>' .
            '<w:lvlJc w:val="left"/><w:pPr><w:ind w:left="5760" ' .
            'w:hanging="360"/></w:pPr><w:rPr><w:rFonts w:ascii="Courier New" ' .
            'w:hAnsi="Courier New" w:cs="Courier New" w:hint="default"/>' .
            '</w:rPr></w:lvl><w:lvl w:ilvl="8" w:tplc="0C0A0005" ' .
            'w:tentative="1"><w:start w:val="1"/><w:numFmt w:val="bullet"' .
            '/><w:lvlText w:val=""/><w:lvlJc w:val="left"/><w:pPr><w:ind ' .
            'w:left="6480" w:hanging="360"/></w:pPr><w:rPr><w:rFonts ' .
            'w:ascii="Wingdings" w:hAnsi="Wingdings" w:hint="default"/>' .
            '</w:rPr></w:lvl></w:abstractNum><w:num w:numId="1">' .
            '<w:abstractNumId w:val="0"/></w:num></w:numbering>';
    }

    /**
     * Generate WordNumbering XML template
     *
     * @access private
     */
    private function generateTemplateWordNumberingStyles()
    {
        $this->_wordNumberingT =
            '<?xml version="1.0" encoding="UTF-8" standalone="yes"?>' .
            '<w:numbering xmlns:ve="http://schemas.openxmlformats' .
            '.org/markup-compatibility/2006" xmlns:o="urn:schemas-' .
            'microsoft-com:office:office" xmlns:r="http://schemas' .
            '.openxmlformats.org/officeDocument/2006/relationships" ' .
            'xmlns:m="http://schemas.openxmlformats.org/officeDocument/' .
            '2006/math" xmlns:v="urn:schemas-microsoft-com:vml" xmlns:' .
            'wp="http://schemas.openxmlformats.org/drawingml/2006/' .
            'wordprocessingDrawing" xmlns:w10="urn:schemas-microsoft-com' .
            ':office:word" xmlns:w="http://schemas.openxmlformats.org/' .
            'wordprocessingml/2006/main" xmlns:wne="http://schemas.' .
            'microsoft.com/office/word/2006/wordml"><w:abstractNum w:'
            . 'abstractNumId="0"><w:nsid w:val="713727AE"/><w:multiLevelType' .
            ' w:val="hybridMultilevel"/><w:tmpl w:val="F0B4B6B8"/>' .
            $this->_wordDocumentStyles . '</w:abstractNum><w:num w:numId="1">' .
            '<w:abstractNumId w:val="0"/></w:num></w:numbering>';
    }

    /**
     * Generate WordRelsDocumentRels XML template
     *
     * @access private
     */
    private function generateTemplateWordRelsDocumentRels()
    {
        $this->_wordRelsDocumentRelsT =
            '<?xml version="1.0" encoding="UTF-8" standalone="yes"?>' .
            '<Relationships xmlns="http://schemas.openxmlformats.org/' .
            'package/2006/relationships">' . $this->_wordRelsDocumentRelsC .
            '</Relationships>';
    }

    /**
     * Generate WordRelsFooterRels XML template
     *
     * @access private
     */
    private function generateTemplateWordRelsFooterRels()
    {
        $this->_wordRelsFooterRelsT =
            '<?xml version="1.0" encoding="UTF-8" standalone="yes"?>' .
            '<Relationships xmlns="http://schemas.openxmlformats.org/' .
            'package/2006/relationships">' . $this->_wordRelsFooterRelsC .
            '</Relationships>';
    }

    /**
     * Generate WordRelsHeaderRels XML template
     *
     * @access private
     */
    private function generateTemplateWordRelsHeaderRels()
    {
        $this->_wordRelsHeaderRelsT =
            '<?xml version="1.0" encoding="UTF-8" standalone="yes"?>' .
            '<Relationships xmlns="http://schemas.openxmlformats.org/' .
            'package/2006/relationships">' . $this->_wordRelsHeaderRelsC .
            '</Relationships>';
    }

    /**
     * Generate WordSettings XML template
     *
     * @access private
     */
    private function generateTemplateWordSettings()
    {
        $this->_wordSettingsT = $this->_wordSettingsC;
    }

    /**
     * Generate WordStyles XML template
     *
     * @access private
     */
    private function generateTemplateWordStyles()
    {
        $this->_wordStylesT =
            '<?xml version="1.0" encoding="UTF-8" standalone="yes"?><' .
            CreateDocx::NAMESPACEWORD . ':styles xmlns:r="http://' .
            'schemas.openxmlformats.org/officeDocument/2006/relationships' .
            '" xmlns:w="http://schemas.openxmlformats.org/wordprocessingml/' .
            '2006/main">' . $this->_wordStylesC .
            '</' . CreateDocx::NAMESPACEWORD . ':styles>';
    }

    /**
     * Generate WordThemeTheme1 XML template
     *
     * @access private
     */
    private function generateTemplateWordThemeTheme1()
    {
        $this->addTheme($this->_defaultFont);
        $this->_wordThemeThemeT =
            '<?xml version="1.0" encoding="UTF-8" standalone="yes" ?><' .
            CreateTheme1::NAMESPACEWORD . ':theme xmlns:a="http://' .
            'schemas.openxmlformats.org/drawingml/2006/main" name="' .
            'Tema de Office">' . $this->_wordThemeThemeC .
            '</' . CreateTheme1::NAMESPACEWORD . ':theme>';
    }

    /**
     * Generate WordWebSettings XML template
     *
     * @access private
     */
    private function generateTemplateWordWebSettings()
    {
        $this->_wordWebSettingsT = $this->_wordWebSettingsC;
    }

    /**
     * Generates a TitlePg element in SectPr
     *
     * @access private
     */
    private function generateTitlePg()
    {
        $foundNodes = $this->_sectPr->documentElement->getElementsByTagName('w:TitlePg');
        if($foundNodes->length == 0){
            $newSectNode = '<w:titlePg xmlns:w="http://schemas.openxmlformats.org/wordprocessingml/2006/main" />';
            $sectNode = $this->_sectPr->createDocumentFragment();
            $sectNode->appendXML($newSectNode);
            $refNode =$this->_sectPr->documentElement->appendChild($sectNode);
        }
    }

    /**
     * To add support of sys_get_temp_dir for PHP versions under 5.2.1
     *
     * @access private
     * @return string
     */
    public static function getTempDir() {
        if ( !function_exists('sys_get_temp_dir')) {
            function sys_get_temp_dir() {
                if ($temp = getenv('TMP')) {
                    return $temp;
                }
                if ($temp = getenv('TEMP')) {
                    return $temp;
                }
                if ($temp = getenv('TMPDIR')) {
                    return $temp;
                }
                $temp = tempnam(__FILE__,'');
                if (file_exists($temp)) {
                    unlink($temp);
                    return dirname($temp);
                }
                return null;
            }
        } else {
            return sys_get_temp_dir();
        }
    }

    /**
     * Takes care of the links and images asociated with an HTML chunck processed
     * by the embedHTML method
     *
     * @access private
     * @param array $sFinalDocX an arry with the required link and image data
     */
    private function HTMLRels($sFinalDocX, $options)
    {
        $relsLinks = '';
        if ($options['target'] == 'defaultHeader' ||
           $options['target'] == 'firstHeader' ||
           $options['target'] == 'evenHeader' ||
           $options['target'] == 'defaultFooter' ||
           $options['target'] == 'firstFooter' ||
           $options['target'] == 'evenFooter') {
            foreach ($sFinalDocX[1] as $key => $value) {
                $this->_relsHeaderFooterLink[$options['target']][] =
                array('rId' => $key, 'url' => $value);
            }
        }else if($options['target'] == 'footnote' ||
                 $options['target'] == 'endnote' ||
                 $options['target'] == 'comment'){
            foreach ($sFinalDocX[1] as $key => $value) {
                $this->_relsNotesLink[$options['target']][] =
                array('rId' => $key, 'url' => $value);
            }
        }else{
            foreach ($sFinalDocX[1] as $key => $value) {
              $relsLinks .= '<Relationship Id="'.$key.'" Type="http://schemas.openxmlformats.org/officeDocument/2006/relationships/hyperlink" Target="'.$value.'" TargetMode="External" />';
            }
            if ($relsLinks != '') {
                $relsNode = $this->_wordRelsDocumentRelsT->createDocumentFragment();
                $relsNode->appendXML($relsLinks);
                $this->_wordRelsDocumentRelsT->documentElement->appendChild($relsNode);
            }
        }

        $relsImages = '';

        if($options['target'] == 'defaultHeader' ||
            $options['target'] == 'firstHeader' ||
            $options['target'] == 'evenHeader' ||
            $options['target'] == 'defaultFooter' ||
            $options['target'] == 'firstFooter' ||
            $options['target'] == 'evenFooter'){
            foreach ($sFinalDocX[2] as $key => $value) {
            //We should remove the first three 'rId' characters in this case
            $value = array_shift(explode('?', $value));
            if (isset($options['downloadImages']) && $options['downloadImages']) {
                $arrayExtension = explode('.', $value);
                $extension = strtolower(array_pop($arrayExtension));
                $predefinedExtensions = array('gif', 'png', 'jpg', 'jpeg', 'bmp');
                if (!in_array($extension, $predefinedExtensions)) {
                    $this->generateDEFAULT($extension, 'image/'.$extension);
                }

                $this->_relsHeaderFooterImage[$options['target']][] = array('rId' => $key, 'extension' => $extension);
              } else {
                  $this->_relsHeaderFooterExternalImage[$options['target']][] = array('rId' => $key, 'url' => $value);
              }
            }
       }else if($options['target'] == 'footnote' ||
                $options['target'] == 'endnote' ||
                $options['target'] == 'comment'){
           foreach ($sFinalDocX[2] as $key => $value) {
            //We should remove the first three 'rId' characters in this case
            $value = array_shift(explode('?', $value));
            if (isset($options['downloadImages']) && $options['downloadImages']) {
                $arrayExtension = explode('.', $value);
                $extension = strtolower(array_pop($arrayExtension));
                $predefinedExtensions = array('gif', 'png', 'jpg', 'jpeg', 'bmp');
                if (!in_array($extension, $predefinedExtensions)) {
                    $this->generateDEFAULT($extension, 'image/'.$extension);
                }

                $this->_relsNotesImage[$options['target']][] = array('rId' => $key, 'extension' => $extension);
              } else {
                  $this->_relsNotesExternalImage[$options['target']][] = array('rId' => $key, 'url' => $value);
              }
            }

        }else {
            foreach ($sFinalDocX[2] as $key => $value) {
                $valueArray = explode('?', $value);
                $value = array_shift($valueArray);
                if (isset($options['downloadImages']) && $options['downloadImages']) {
                    $arrayExtension = explode('.', $value);
                    $extension = strtolower(array_pop($arrayExtension));
                    $predefinedExtensions = array('gif', 'png', 'jpg', 'jpeg', 'bmp');
                    if (! in_array($extension, $predefinedExtensions)) {
                        $this->generateDEFAULT($extension, 'image/'.$extension);
                    }
                  $relsImages .= '<Relationship Id="'.$key.'" Type="http://schemas.openxmlformats.org/officeDocument/2006/relationships/image" Target="media/img'.$key.'.'.$extension.'" />';
                } else {
                    $relsImages .= '<Relationship Id="'.$key.'" Type="http://schemas.openxmlformats.org/officeDocument/2006/relationships/image" Target="'.$value.'" TargetMode="External" />';
                }
            }

            if ($relsImages != '') {
                $relsNodeImages = $this->_wordRelsDocumentRelsT->createDocumentFragment();
                $relsNodeImages->appendXML($relsImages);
                $this->_wordRelsDocumentRelsT->documentElement->appendChild($relsNodeImages);
            }
        }
    }

    /**
     * Parse path dir
     *
     * @access private
     * @param string $dir Directory path
     */
    private function parsePath($dir)
    {
        $slash = 0;
        $path = '';
        if (($slash = strrpos($dir, '/')) !== false) {
            $slash += 1;
            $path = substr($dir, 0, $slash);
        }
        $punto = strpos(substr($dir, $slash), '.');

        $nombre = substr($dir, $slash, $punto);
        $extension = substr($dir, $punto + $slash + 1);
        return array(
            'path' => $path, 'nombre' => $nombre, 'extension' => $extension
        );
    }

    /**
     * Preprocess a docx for the addDOCX method
     * By the time being we only remove the w:nsid and w:tmpl nodes from the
     * numbering.xml file
     *
     * @param string $path path to file
     */
    private function preprocessDocx($pathDOCX){
        PhpdocxLogger::logger('Preprocess a docx for embeding with the addDOCX method.', 'debug');
        try {
            $embedZip = new ZipArchive();
            if ($embedZip->open($pathDOCX) === true) {
               //The docx was succesfully unzipped
            } else {
                throw new Exception(
                    'it was not posible to unzip the docx file.'
                );
            }
            $numberingXML = $embedZip->getFromName('word/numbering.xml');
            $numberingDOM = new DOMDocument();
            $numberingDOM->loadXML($numberingXML);
            $numberingXPath = new DOMXPath($numberingDOM);
            $numberingXPath->registerNamespace('w', 'http://schemas.openxmlformats.org/wordprocessingml/2006/main');
            //we have to remove the w:nsid and w:tmpl elements to avoid conflicts
            $nsidQuery = '//w:nsid | //w:tmpl';
            $nsidNodes = $numberingXPath->query($nsidQuery);
            foreach($nsidNodes as $node){
              $node->parentNode->removeChild($node);
            }
            $newNumbering = $numberingDOM->saveXML();
            $embedZip->addFromString('word/numbering.xml', $newNumbering);
            $embedZip->close();
        }
        catch (Exception $e) {
            PhpdocxLogger::logger($e->getMessage(), 'fatal');
        }

    }

     /**
     * Delete a file or recursively delete a directory
     *
     * @param string $str path to file or directory
     */
    private function recursiveDelete($str){
        if(is_file($str)){
            return @unlink($str);
        }
        elseif(is_dir($str)){
            $scan = glob(rtrim($str,'/').'/*');
            foreach($scan as $index=>$path){
                $this->recursiveDelete($path);
            }
            return @rmdir($str);
        }
    }


     /**
     *
     * Adds directory contents recursively into a zip.
     *
     * @param string $fileName. The path to the dir to add.
     *
     * @param string $myZip. The zip where the contents of the dir should be added.
     *
     */
    private function recursiveInsert($myZip, $fileName, $basePath){
         $length = strlen($basePath);
         if(is_dir($fileName)){
            $contentsDir = scandir($fileName);
            foreach($contentsDir as $element){
              if($element != "." && $element !=".."){
                 $this->recursiveInsert($myZip, $fileName."/".$element, $basePath);
                 }
            }
         }else{
            $newName = substr($fileName, $length + 1);
            $myZip->addFile($fileName, $newName);
         }
     }

     /**
     *
     * Includes data in the setting.xml file.
     *
     * @param array $settings. The string with the nodes that should be included in the settings.xml file.
     *
     */
    private function includeSettings($data){
        try{
            $baseSettings = $this->_baseTemplateZip->getFromName('word/settings.xml');
            if ($baseSettings == '') {
        throw new Exception('Error while extracting the settings.xml file from the base template');
            }
        }
        catch (Exception $e) {
            PhpdocxLogger::logger($e->getMessage(), 'fatal');
        }

        $settingsDoc = new DOMDocument();
        $settingsDoc->loadXML($baseSettings);
        $settings = $settingsDoc->documentElement;

        foreach($data as $key => $value){
            $newNode = $settingsDoc->createDocumentFragment();
            $newNode->appendXML($value);
            $settings->appendChild($newNode);
        }

        $settingsHandler = fopen($this->_baseTemplateFilesPath.'/word/settings.xml', "w+");
        fwrite($settingsHandler, $settingsDoc->saveXML());
        fclose($documentHandler);
     }

     /**
     *
     * Removes headers and footers.
     *
     */
    public function removeHeadersAndFooters(){
        $this->removeHeaders();
        $this->removeFooters();
    }

     /**
     *
     * Removes existing headers.
     *
     */
    public function removeHeaders(){
        foreach($this->_relsHeader as $key => $value){
            //Let us first remove the actual header files
            $this->recursiveDelete($this->_baseTemplateFilesPath.'/word/'.$value);
            $this->recursiveDelete($this->_baseTemplateFilesPath.'/word/_rels/'.$value.'.rels');

            //Now we should modify the rels file
            $relationships = $this->_wordRelsDocumentRelsT->getElementsByTagName('Relationship');
            $counter = $relationships->length -1;
            for($j=$counter; $j > -1; $j--){
                $target = $relationships->item($j)->getAttribute('Target');
                if($target == $value){
                  $this->_wordRelsDocumentRelsT->documentElement->removeChild($relationships->item($j));
                }
            }
            //We should also remove the corresponding override tags from [Content_Types].xml
            $overrides = $this->_contentTypeT->getElementsByTagName('Override');
            $counter = $overrides->length -1;
            for($j=$counter; $j > -1; $j--){
                $target = $overrides->item($j)->getAttribute('PartName');
                if($target == '/word/'.$value){
                  $this->_contentTypeT->documentElement->removeChild($overrides->item($j));
                }
            }
        }


        //We should change the section properties
        $headers = $this->_sectPr->getElementsByTagName('headerReference');
        $counter = $headers->length -1;
        for($j=$counter; $j > -1; $j--){
            $this->_sectPr->documentElement->removeChild($headers->item($j));
        }
        $titlePage = $this->_sectPr->getElementsByTagName('titlePg');
        $counter = $titlePage->length -1;
        for($j=$counter; $j > -1; $j--){
            $this->_sectPr->documentElement->removeChild($titlePage->item($j));
        }
        //Finally, we remove, if it exists, the evenAndOddHeader element from settings
        $this->removeSetting('w:evenAndOddHeaders');

    }

      /**
     *
     * Removes existing footers.
     *
     */
    public function removeFooters(){
        foreach($this->_relsFooter as $key => $value){
            //Let us first remove the actual header files
            $this->recursiveDelete($this->_baseTemplateFilesPath.'/word/'.$value);
            $this->recursiveDelete($this->_baseTemplateFilesPath.'/word/_rels/'.$value.'.rels');

            //Now we should modify the rels file
            $relationships = $this->_wordRelsDocumentRelsT->getElementsByTagName('Relationship');
            $counter = $relationships->length -1;
            for($j=$counter; $j > -1; $j--){
                $target = $relationships->item($j)->getAttribute('Target');
                if($target == $value){
                  $this->_wordRelsDocumentRelsT->documentElement->removeChild($relationships->item($j));
                }
            }
            //We should also remove the corresponding override tags from [Content_Types].xml
            $overrides = $this->_contentTypeT->getElementsByTagName('Override');
            $counter = $overrides->length -1;
            for($j=$counter; $j > -1; $j--){
                $target = $overrides->item($j)->getAttribute('PartName');
                if($target == '/word/'.$value){
                  $this->_contentTypeT->documentElement->removeChild($overrides->item($j));
                }
            }
        }
        //We should change the section properties
        $footers = $this->_sectPr->getElementsByTagName('footerReference');
        $counter = $footers->length -1;
        for($j=$counter; $j > -1; $j--){
            $this->_sectPr->documentElement->removeChild($footers->item($j));
        }
        $titlePage = $this->_sectPr->getElementsByTagName('titlePg');
        $counter = $titlePage->length -1;
        for($j=$counter; $j > -1; $j--){
            $this->_sectPr->documentElement->removeChild($titlePage->item($j));
        }
        //Finally, we remove, if it exists, the evenAndOddHeader element from settings
        $this->removeSetting('w:evenAndOddHeaders');
    }

    /**
     * Removes an element from settings.xml
     *
     * @access private
     */
    private function removeSetting($tag)
    {

        try{
            $settings = fopen($this->_baseTemplateFilesPath.'/word/settings.xml', "r");
            $baseTemplateSettingsT = fread($settings, 1000000);
            fclose($settings);
            if ($baseTemplateSettingsT == '') {
                throw new Exception('Error while extracting settings.xml file from the base template to remove the tag element');
            }
        }
        catch (Exception $e) {
            PhpdocxLogger::logger($e->getMessage(), 'fatal');
        }

        $this->_wordSettingsT = new DOMDocument();
        $this->_wordSettingsT->loadXML($baseTemplateSettingsT);
        $settingsHeader = $this->_wordSettingsT->documentElement->getElementsByTagName($tag);
        if($settingsHeader->length > 0){
            $this->_wordSettingsT->documentElement->removeChild($settingsHeader->item(0));
            $newSettings = $this->_wordSettingsT->saveXML();
            $settingsHandle = fopen($this->_baseTemplateFilesPath.'/word/settings.xml', "w+");
            $contents = fwrite($settingsHandle, $newSettings);
            fclose($settingsHandle);
        }

    }
    /**
     *
     * Inserts a new numbering style.
     *
     * @param string $numberingsXML the numberings.xml that we wish to modify
     * @param string $newNumbering the new numbering style we wish to add.
     * @param string $numberId a unique integer that determines the numbering id
     * and the abstract numbering id
     */
    public function importSingleNumbering($numberingsXML, $newNumbering, $numberId, $originalAbstractNumId=''){
        //First we insert the $newNumbering into $numberingsXML

        $myNumbering = new DOMDocument();
        $myNumbering->loadXML($numberingsXML);
        //Let us now modify the w:abstractNumId atribute
        $newNumbering = str_replace('<w:abstractNum w:abstractNumId="'.$originalAbstractNumId.'"','<w:abstractNum w:abstractNumId="'.$numberId.'"', $newNumbering);
        $newNumbering = str_replace('w:tplc=""', 'w:tplc="'.rand(10000000, 99999999).'"', $newNumbering);
        $new = $myNumbering->createDocumentFragment();
        $new->appendXML($newNumbering);
        $base = $myNumbering->documentElement->firstChild;
        $base->parentNode->insertBefore($new, $base);
        $numberingsXML = $myNumbering->saveXML();

        //Now we include the relationshiop
        $newNum = '<w:num w:numId="'.$numberId.'"><w:abstractNumId w:val="'.$numberId.'" /></w:num>';
        $numberingsXML = str_replace('</w:numbering>', $newNum.'</w:numbering>', $numberingsXML);

        return $numberingsXML;
    }
    /**
     *
     * creates an empty word numbering base string
     */
    public function generateBaseWordNumbering(){
        //We copy the numbering.xml file from the standard PHPDocX template into the new base template
        $numZip = new ZipArchive();
        try {
            $openNumZip = $numZip->open(PHPDOCX_BASE_TEMPLATE);
            if ($openNumZip !== true) {
                throw new Exception('Error while opening the standard base template to extract the word/numbering.xml file');
            }
        } catch (Exception $e) {
            PhpdocxLogger::logger($e->getMessage(), 'fatal');
        }
        $baseWordNumbering = $numZip->getFromName('word/numbering.xml');

        return $baseWordNumbering;
    }

     /**
     *
     * Inserts new headers and/or footers from a word file.
     *
     * @example ../examples/easy/ImportHeaderAndFooter.php
     * @param string $path. Path to the docx from which we wish to import the header and/or footer
     * @param string $type. Declares if we want to import only the header, only the footer or both.
     * Values: header, footer, headerAndFooter (default value)
     */
    public function importHeadersAndFooters($path, $type='headerAndFooter'){
        switch ($type) {
            case 'headerAndFooter':
                $this->removeHeadersAndFooters();
                break;
            case 'header':
                $this->removeHeaders();
                break;
            case 'footer':
                $this->removeFooters();
                break;
        }
        //Let us first get parse and extract the relevant files from the docx with the new headers/footers
        try {
            $baseHeadersFooters = new ZipArchive();
            $openHeadersFooters = $baseHeadersFooters->open($path);
            if ($openHeadersFooters !== true) {
                throw new Exception('Error while opening the docx to extract the header and/or footer');
            }
        } catch (Exception $e) {
            PhpdocxLogger::logger($e->getMessage(), 'fatal');
        }

        //We now extract its contents into a temp dir for further manipulation
        try {
            $baseHeadersFootersFilesPath = $this->_tempDir.'/'.uniqid(true);
            $extractHeadersFooters =$baseHeadersFooters->extractTo($baseHeadersFootersFilesPath);
            if ($extractHeadersFooters !== true) {
                throw new Exception('Error while extracting the contents of the docx file that containes the header and/or footer: there may be problems writing in the default tmp folder');
            }
        } catch (Exception $e) {
            PhpdocxLogger::logger($e->getMessage(), 'fatal');
        }
        //We need to extract the different roles: default, even or first played by the different headers and footers
        //In order to do that we should first parse the node sectPr from the document.xml file

        try {
            $docHeadersFooters = $baseHeadersFooters->getFromName('word/document.xml');
            if ($docHeadersFooters == '') {
                throw new Exception('Error while extracting the document.xml file from the docx from which we want to get the feaders and/or footers');
            }
        } catch (Exception $e) {
            PhpdocxLogger::logger($e->getMessage(), 'fatal');
        }

        $docHeadersFootersContent = new DOMDocument();
        $docHeadersFootersContent ->loadXML($docHeadersFooters);

        //We now extract the first sectPr element in the document

        $docSectPr = $docHeadersFootersContent->getElementsByTagName('sectPr')->item(0);

        $headerTypes = array();
        $footerTypes = array();
        $titlePg = false;
        foreach($docSectPr->childNodes as $value){
            if($value->nodeName == 'w:headerReference'){
                $headerTypes[$value->getAttribute('r:id')] = $value->getAttribute('w:type');
            }else if($value->nodeName == 'w:footerReference'){
                $footerTypes[$value->getAttribute('r:id')] = $value->getAttribute('w:type');
            }
        }
        //We now should chek if the first and even headers and footers are shown in the original Word document
        $titlePg = false;
        if ($docHeadersFootersContent->getElementsByTagName('titlePg')->length > 0) {
           $titlePg = true;
        }
        try {
            $settingsHeadersFooters = $baseHeadersFooters->getFromName('word/settings.xml');
            if ($settingsHeadersFooters == '') {
                throw new Exception('Error while extracting the settings.xml file from the docx from which we want to get the headers and/or footers');
            }
        } catch (Exception $e) {
            PhpdocxLogger::logger($e->getMessage(), 'fatal');
        }

        $settingsHeadersFootersContent = new DOMDocument();
        $settingsHeadersFootersContent ->loadXML($settingsHeadersFooters);

        if($settingsHeadersFootersContent->getElementsByTagName('evenAndOddHeaders')->length > 0){
           $this->generateSetting('w:evenAndOddHeaders');
        }

        //Let us read the _rels/document.xml.rels to see which footers and headers we do have to get
        try {
            $baseHeadersFootersRelsT = $baseHeadersFooters->getFromName('word/_rels/document.xml.rels');
            if ($baseHeadersFootersRelsT == '') {
                throw new Exception('Error while extracting the document.xml.rels file from the docx from which we want to get the feaders and/or footers');
            }
        } catch (Exception $e) {
            PhpdocxLogger::logger($e->getMessage(), 'fatal');
        }


        //Let us analyze its structure
        //In order to do that we should parse word/_rels/document.xml.rels
        $wordHeadersFootersRelsT = new DOMDocument();
        $wordHeadersFootersRelsT->loadXML($baseHeadersFootersRelsT);
        $relationships = $wordHeadersFootersRelsT->getElementsByTagName('Relationship');

        $counter = $relationships->length -1;

        for($j=$counter; $j > -1; $j--){
            $rId = $relationships->item($j)->getAttribute('Id');
            $completeType = $relationships->item($j)->getAttribute('Type');
            $target = $relationships->item($j)->getAttribute('Target');
            $myType = array_pop(explode('/', $completeType));

            switch($myType){
                case 'header':
                    $relsHeader[$rId]= $target;
                    break;
                case 'footer':
                    $relsFooter[$rId]= $target;
                    break;
            }
        }

            //Let start the looping over the $relsHeader and/or $relsFooter arrays

            if($type == 'headerAndFooter' || $type == 'header'){

                foreach ($relsHeader as $key => $value){
                  //First we check if there is a rels file for each header
                    if (file_exists($baseHeadersFootersFilesPath.'/word/_rels/'.$value.'.rels')) {
                        try {
                            $headersRelsT = $baseHeadersFooters->getFromName('word/_rels/'.$value.'.rels');
                            if ($headersRelsT == '') {
                                throw new Exception('Error while extracting the rels file for the header');
                            }
                        } catch (Exception $e) {
                            PhpdocxLogger::logger($e->getMessage(), 'fatal');
                        }

                       //Now we should parse the corresponding rels file to copy and rename the images included in the header
                        $wordHeadersRelsT = new DOMDocument();
                        $wordHeadersRelsT->loadXML($headersRelsT);
                        $relations = $wordHeadersRelsT->getElementsByTagName('Relationship');

                        $countrels = $relations->length -1;

                        for ($j=$countrels; $j > -1; $j--) {
                            $completeType = $relations->item($j)->getAttribute('Type');
                            $target = $relations->item($j)->getAttribute('Target');
                            $myType = array_pop(explode('/', $completeType));

                            switch($myType){
                                case 'image':
                                    $refExtension = array_pop(explode('.', $target));
                                    $refImage = 'media/image'.uniqid(true).'.'.$refExtension;
                                    //We change the attibute to the new name
                                    $relations->item($j)->setAttribute('Target', $refImage);
                                    //We copy the image in the base template with the new name
                                    if(!file_exists($this->_baseTemplateFilesPath.'/word/media')){
                                       $test2 = mkdir($this->_baseTemplateFilesPath.'/word/media');
                                    }
                                    copy($baseHeadersFootersFilesPath.'/word/'.$target, $this->_baseTemplateFilesPath.'/word/'.$refImage);
                                    //We copy the associated rels file
                                    $newRels = fopen($this->_baseTemplateFilesPath.'/word/_rels/'.$value.'.rels', 'w+');
                                    fwrite($newRels, $wordHeadersRelsT->saveXML());
                                    //We should make sure that the corresponding image types are included in [Content_Types].xml
                                    $imageTypeFound = false;
                                    foreach($this->_contentTypeT->documentElement->childNodes as $node){
                                        if ($node->nodeName == 'Default' && $node->getAttribute('Extension') == $refExtension){
                                            $imageTypeFound = true;
                                        }
                                    }
                                    if(!$imageTypeFound){
                                        $newDefaultNode = '<Default Extension="'.$refExtension.'" ContentType="image/'.$refExtension.'" />';
                                        $newDefault = $this->_contentTypeT->createDocumentFragment();
                                        $newDefault->appendXML($newDefaultNode);
                                        $baseDefaultNode =$this->_contentTypeT->documentElement;
                                        $baseDefaultNode->appendChild($newDefault);
                                    }
                                    break;
                            }
                        }
                    }

                    //Now we copy the corresponding header xml files
                    copy($baseHeadersFootersFilesPath.'/word/'.$value, $this->_baseTemplateFilesPath.'/word/'.$value);
                    //We should now modify the /_rels/document.xml.rels of the base template to include the new element
                    $newId = uniqid(true);
                    $newHeaderNode = '<Relationship Id="rId';
                    $newHeaderNode .= $newId.'" Type="http://schemas.openxmlformats.org/officeDocument/2006/relationships/header"';
                    $newHeaderNode .= ' Target="'.$value.'" />';
                    $newNode = $this->_wordRelsDocumentRelsT->createDocumentFragment();
                    $newNode->appendXML($newHeaderNode);
                    $baseNode =$this->_wordRelsDocumentRelsT->documentElement;
                    $baseNode->appendChild($newNode);

                    //As well as the section DOMNode
                    $newSectNode = '<w:headerReference w:type="'.$headerTypes[$key].'" r:id="rId'.$newId.'" xmlns:w="http://schemas.openxmlformats.org/wordprocessingml/2006/main" xmlns:r="http://schemas.openxmlformats.org/officeDocument/2006/relationships"/>';
                    $sectNode = $this->_sectPr->createDocumentFragment();
                    $sectNode->appendXML($newSectNode);
                    $refNode =$this->_sectPr->documentElement->childNodes->item(0);
                    $refNode->parentNode->insertBefore($sectNode, $refNode);

                    //And we have to include the corresponding <Override> in [Content_Types].xml
                    $newOverrideNode = '<Override PartName="/word/'.$value.'" ContentType="application/vnd.openxmlformats-officedocument.wordprocessingml.header+xml" />';
                    $newOverride = $this->_contentTypeT->createDocumentFragment();
                    $newOverride->appendXML($newOverrideNode);
                    $baseOverrideNode =$this->_contentTypeT->documentElement;
                    $baseOverrideNode->appendChild($newOverride);
                }
            }
            if($type == 'headerAndFooter' || $type == 'footer'){

                foreach ($relsFooter as $key => $value){
                  //First we check if there is a rels file for each header
                    if (file_exists($baseHeadersFootersFilesPath.'/word/_rels/'.$value.'.rels')) {
                        try{
                            $footersRelsT = $baseHeadersFooters->getFromName('word/_rels/'.$value.'.rels');
                            if ($footersRelsT == '') {
                                throw new Exception('Error while extracting the rels file for the footer');
                            }
                        } catch (Exception $e) {
                            PhpdocxLogger::logger($e->getMessage(), 'fatal');
                        }

                       //Now we should parse the corresponding rels file to copy and rename the images included in the header
                        $wordFootersRelsT = new DOMDocument();
                        $wordFootersRelsT->loadXML($footersRelsT);
                        $relations = $wordFootersRelsT->getElementsByTagName('Relationship');

                        $countrels = $relations->length -1;

                        for($j=$countrels; $j > -1; $j--){
                            $completeType = $relations->item($j)->getAttribute('Type');
                            $target = $relations->item($j)->getAttribute('Target');
                            $myType = array_pop(explode('/', $completeType));

                            switch($myType){
                                case 'image':
                                    $refExtension = array_pop(explode('.', $target));
                                    $refImage = 'media/image'.uniqid(true).'.'.$refExtension;
                                    //We change the attibute to the new name
                                    $relations->item($j)->setAttribute('Target', $refImage);
                                    //We copy the image in the base template with the new name
                                    if(!file_exists($this->_baseTemplateFilesPath.'/word/media')){
                                       $test2 = mkdir($this->_baseTemplateFilesPath.'/word/media');
                                    }
                                    copy($baseHeadersFootersFilesPath.'/word/'.$target, $this->_baseTemplateFilesPath.'/word/'.$refImage);
                                    //We copy the associated rels file
                                    $newRels = fopen($this->_baseTemplateFilesPath.'/word/_rels/'.$value.'.rels', 'w+');
                                    fwrite($newRels, $wordFootersRelsT->saveXML());
                                    //We should make sure that the corresponding image types are included in [Content_Types].xml
                                    $imageTypeFound = false;
                                    foreach($this->_contentTypeT->documentElement->childNodes as $node){
                                        if ($node->nodeName == 'Default' && $node->getAttribute('Extension') == $refExtension){
                                            $imageTypeFound = true;
                                        }
                                    }
                                    if(!$imageTypeFound){
                                        $newDefaultNode = '<Default Extension="'.$refExtension.'" ContentType="image/'.$refExtension.'" />';
                                        $newDefault = $this->_contentTypeT->createDocumentFragment();
                                        $newDefault->appendXML($newDefaultNode);
                                        $baseDefaultNode =$this->_contentTypeT->documentElement;
                                        $baseDefaultNode->appendChild($newDefault);
                                    }
                                    break;
                            }
                        }
                    }

                    //Now we copy the corresponding header xml files
                    copy($baseHeadersFootersFilesPath.'/word/'.$value, $this->_baseTemplateFilesPath.'/word/'.$value);
                    //We should now modify the /_rels/document.xml.rels of the base template to include the new element
                    $newId = uniqid(true);
                    $newFooterNode = '<Relationship Id="rId';
                    $newFooterNode .= $newId.'" Type="http://schemas.openxmlformats.org/officeDocument/2006/relationships/footer"';
                    $newFooterNode .= ' Target="'.$value.'" />';
                    $newNode = $this->_wordRelsDocumentRelsT->createDocumentFragment();
                    $newNode->appendXML($newFooterNode);
                    $baseNode =$this->_wordRelsDocumentRelsT->documentElement;
                    $baseNode->appendChild($newNode);

                    //As well as the section DOMNode
                    $newSectNode = '<w:footerReference w:type="'.$footerTypes[$key].'" r:id="rId'.$newId.'" xmlns:w="http://schemas.openxmlformats.org/wordprocessingml/2006/main" xmlns:r="http://schemas.openxmlformats.org/officeDocument/2006/relationships"/>';
                    $sectNode = $this->_sectPr->createDocumentFragment();
                    $sectNode->appendXML($newSectNode);
                    $refNode =$this->_sectPr->documentElement->childNodes->item(0);
                    $refNode->parentNode->insertBefore($sectNode, $refNode);

                    //And we have to include the corresponding <Override> in [Content_Types].xml
                    $newOverrideNode = '<Override PartName="/word/'.$value.'" ContentType="application/vnd.openxmlformats-officedocument.wordprocessingml.footer+xml" />';
                    $newOverride = $this->_contentTypeT->createDocumentFragment();
                    $newOverride->appendXML($newOverrideNode);
                    $baseOverrideNode =$this->_contentTypeT->documentElement;
                    $baseOverrideNode->appendChild($newOverride);


                }
            }

            if($titlePg){
                $this->generateTitlePg();
            }

    }
}
