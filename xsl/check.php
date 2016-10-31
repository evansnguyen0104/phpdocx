<?php
/*
 * PHPDocX Configuration test
 */

error_reporting(E_ALL & ~E_STRICT & ~E_NOTICE);

$output = '';

$break = isset($_SERVER['HTTP_USER_AGENT']) ? '<br />' : PHP_EOL;
$isWeb = isset($_SERVER['HTTP_USER_AGENT']) ? true : false;

if ($isWeb) {
	$output .= '<html>';
	$output .= '<head>';
	$output .= '<title>PHPDocX configuration test</title>';
	$output .= '<style type="text/css">';
	$output .= 'body {
		background: #fcfcfc;
		font-family: Arial, Sans-Serif;;
	}';
	$output .= '#page {
		border: 1px solid #ababab;
		margin: 15px auto 0 auto;
		width: 900px;
		background: #F3F3F3;
		-webkit-border-radius: 5px;
		-moz-border-radius: 5px;
		border-radius: 5px;
	}';
	$output .= '#info {
		margin: 10px;
		background: white;
		padding: 15px 20px 10px 20px;
	}';
	$output .= '#header {
		background: url("http://www.phpdocx.com/sites/all/themes/zen_phpdocx/images/logo_cabecera.gif") no-repeat;
		border-bottom: 1px solid #EC008C;
		height: 100px;
		padding: 0 10px 10px 150px;
	}';
	$output .= '#header h1 {
		margin: 0px;
		color: #EC008C;
	}';
	$output .= '#sidebar {
		float: left;
		width: 90px;
	}';
	$output .= '#content {

	}';
	$output .= 'ul {
		list-style-type: none;
		margin:20px;
		padding:0;
	}';
	$output .= 'li {
		padding:10px;
	}';
	$output .= 'li.odd {
		background: #fcfcfc;
		border-top: 1px solid #EEE;
	}';
	$output .= 'li.even {
		border-top: 1px solid #EEE;
	}';
	$output .= '.testok {
		padding:5px;
		margin: 0 10px 0 0;
		color: #FFFFFF;
		background-color: #008000;
		-webkit-border-radius: 5px;
		-moz-border-radius: 5px;
		border-radius: 5px;
		display: inline-block;
		width:50px;
		font-size: 11px;
		text-align:center;
	}';
	$output .= '.testko {
		padding:5px;
		margin: 0 10px 0 0;
		color: #FFFFFF;
		background-color: #FE2E2E;
		-webkit-border-radius: 5px;
		-moz-border-radius: 5px;
		border-radius: 5px;
		display: inline-block;
		width:50px;
		font-size: 11px;
		text-align:center;
	}';
	$output .= '.testwarn {
		padding:5px;
		margin: 0 10px 0 0;
		color: #FFFFFF;
		background-color: #dd9118;
		-webkit-border-radius: 5px;
		-moz-border-radius: 5px;
		border-radius: 5px;
		display: inline-block;
		width:50px;
		font-size: 11px;
		text-align:center;
	}';
	$output .= '.comment {
		margin: 70px;
		font-size: 11px;
	}';
	$output .= 'textarea {
		width: 650px;
		height: 150px;
	}';
	$output .= '.clear {clear: both;}';
	$output .= '</style>';
	$output .= '</head>';
	$output .= '<body>';
	$output .= '<div id="page">';
	$output .= '<div id="info">';
	$output .= '<div id="header">';
	$output .= '<h1>PHPDocX configuration test</h1>';
	$output .= '<span>Welcome to PHPDocX checker</span>';
	$output .= '</div>';
	$output .= '<div id="content">';
	$output .= '<ul class="checks">';
}

$version = explode('.', PHP_VERSION);

$iPhpVersion = $version[0] * 10000 + $version[1] * 100 + $version[2];

// PHP version
if ($isWeb) {
	$output .= '<li class="odd">';
}
if ($iPhpVersion < 50000) {
	if ($isWeb) {
		$output .= '<span class="testko">';
	}
	$output .= 'Error ';
	if ($isWeb) {
		$output .= '</span>';
	}
    $output .= 'Your PHP version (' . PHP_VERSION . '), is too old, please update to PHP 5' . $break;
} else {
	if ($isWeb) {
		$output .= '<span class="testok">';
	}
	$output .= 'OK ';
	if ($isWeb) {
		$output .= '</span>';
	}
	$output .= 'PHP version is ' . PHP_VERSION . $break;
}
if ($isWeb) {
	$output .= '</li>';
}

// ZipArchive support
if ($isWeb) {
	$output .= '<li class="even">';
}
if (!class_exists('ZipArchive')) {
	if ($isWeb) {
		$output .= '<span class="testko">';
	}
	$output .= 'Error ';
	if ($isWeb) {
		$output .= '</span>';
	}
	$output .= 'You must install ZIP support for PHP' . $break;
} else {
	if ($isWeb) {
		$output .= '<span class="testok">';
	}
	$output .= 'OK ';
	if ($isWeb) {
		$output .= '</span>';
	}
	$output .= 'Zip support is enabled.' . $break;
}
if ($isWeb) {
	$output .= '</li>';
}


// XSL support
if ($isWeb) {
	$output .= '<li class="odd">';
}
if (!class_exists('XSLTProcessor')) {
	if ($isWeb) {
		$output .= '<span class="testko">';
	}
	$output .= 'Error ';
	if ($isWeb) {
		$output .= '</span>';
	}
	$output .= 'You must install XSL support for PHP' . $break;
} else {
	if ($isWeb) {
		$output .= '<span class="testok">';
	}
	$output .= 'OK ';
	if ($isWeb) {
		$output .= '</span>';
	}
	$output .= 'XSL support is enabled.' . $break;
}
if ($isWeb) {
	$output .= '</li>';
}


// DOM support
if ($isWeb) {
	$output .= '<li class="even">';
}
if (!class_exists('DOMDocument')) {
	if ($isWeb) {
		$output .= '<span class="testko">';
	}
	$output .= 'Error ';
	if ($isWeb) {
		$output .= '</span>';
	}
	$output .= 'You must install DOM support for PHP' . $break;
} else {
	if ($isWeb) {
		$output .= '<span class="testok">';
	}
	$output .= 'OK ';
	if ($isWeb) {
		$output .= '</span>';
	}
	$output .= 'DOM support is enabled.' . $break;
}
if ($isWeb) {
	$output .= '</li>';
}


// SimpleXML support
if ($isWeb) {
	$output .= '<li class="odd">';
}
if (!class_exists('SimpleXMLElement')) {
	if ($isWeb) {
		$output .= '<span class="testko">';
	}
	$output .= 'Error ';
	if ($isWeb) {
		$output .= '</span>';
	}
	$output .= 'You must install XML support for PHP' . $break;
} else {
	if ($isWeb) {
		$output .= '<span class="testok">';
	}
	$output .= 'OK ';
	if ($isWeb) {
		$output .= '</span>';
	}
	$output .= 'XML support is enabled.' . $break;
}
if ($isWeb) {
	$output .= '</li>';
}

// Tidy support
if ($isWeb) {
	$output .= '<li class="even">';
}
if (!class_exists('Tidy')) {
	if ($isWeb) {
		$output .= '<span class="testwarn">';
	}
	$output .= 'Warning ';
	if ($isWeb) {
		$output .= '</span>';
	}
	$output .= 'We recommend you to install Tidy for PHP if you want use embedHTML in your Word documents. Htmlawed class will be used instead of Tidy.' . $break;
} else {
	if ($isWeb) {
		$output .= '<span class="testok">';
	}
	$output .= 'OK ';
	if ($isWeb) {
		$output .= '</span>';
	}
	$output .= 'Tidy support is enabled.' . $break;
}
if ($isWeb) {
	$output .= '</li>';
}

// Examples path write access
if ($isWeb) {
	$output .= '<li class="odd">';
}
if (!is_writable('examples/docx')) {
	if ($isWeb) {
		$output .= '<span class="testwarn">';
	}
	$output .= 'Warning ';
	if ($isWeb) {
		$output .= '</span>';
	}
	$output .= 'The path examples/docx used by the examples isn\'t writable.' . $break;
} else {
	if ($isWeb) {
		$output .= '<span class="testok">';
	}
	$output .= 'OK ';
	if ($isWeb) {
		$output .= '</span>';
	}
	$output .= 'The path examples/docx used by the examples is writable.' . $break;
}
if ($isWeb) {
	$output .= '</li>';
}

// Check license
if ($isWeb) {
	$output .= '<li class="odd">';
}
if (file_exists('classes/GenerateDocx.inc')) {
	require_once 'classes/PhpdocxUtilities.inc';
	require_once 'classes/GenerateDocx.inc';
	try {
		$license = GenerateDocx::beginDocx();
		if ($isWeb) {
			$output .= '<span class="testok">';
		}
		$output .= 'OK ';
		if ($isWeb) {
			$output .= '</span>';
		}
		$output .= 'The license is valid for the current domain/server.' . $break;
	} catch (Exception $e) {
		if ($isWeb) {
			$output .= '<span class="testko">';
		}
		$output .= 'Error ';
		if ($isWeb) {
			$output .= '</span>';
		}
		$output .= 'The license is not valid for the current domain/server.' . $break;
		$output .= '<span class="comment">Please add the license code in config/phpdocxconfig.ini file.</span>' . $break;
	}
	if ($isWeb) {
		$output .= '</li>';
	}
}

// Check temp folder
if ($isWeb) {
	$output .= '<li class="even">';
}
require_once 'classes/CreateDocx.inc';
$isWritable = is_writable(CreateDocx::getTempDir());
if (!$isWritable) {
	if ($isWeb) {
		$output .= '<span class="testko">';
	}
	$output .= 'Error ';
	if ($isWeb) {
		$output .= '</span>';
	}
	$output .= 'The library can\'t write to temp folder. You can set a custom tmp path in config/phpdocx_config.ini file.' . $break;
} else {
	if ($isWeb) {
		$output .= '<span class="testok">';
	}
	$output .= 'OK ';
	if ($isWeb) {
		$output .= '</span>';
	}
	$output .= 'The library can write to temp folder.' . $break;
}
if ($isWeb) {
	$output .= '</li>';
}

// TransformDocAdv file exists
if ($isWeb) {
	$output .= '<li class="even">';
}
if (file_exists('classes/TransformDocAdv.inc')) {
	$fp = @fsockopen('localhost', 8100, $errno, $errstr, 30);
	if (!$fp) {
		if ($isWeb) {
			$output .= '<span class="testwarn">';
		}
		$output .= 'Warning ';
		if ($isWeb) {
			$output .= '</span>';
		}
   		$output .= 'You\'re not running OpenOffice in headless mode on port 8100.' . $break;
	} else {
		if ($isWeb) {
			$output .= '<span class="testok">';
		}
		$output .= 'OK ';
		if ($isWeb) {
			$output .= '</span>';
		}
		$output .= 'OpenOffice is running in headless mode on port 8100.' . $break;
	}
	if (strtoupper(substr(PHP_OS, 0, 3)) == 'WIN') {
		if (file_exists('classes/TransformDocAdv.inc')) {
			if ($isWeb) {
				$output .= '<span class="comment">You can download OpenOffice from http://www.openoffice.org/download</span>' . $break;
			}
		}
	} elseif (strtoupper(substr(PHP_OS, 0, 3)) == 'LIN') {
		if (file_exists('classes/TransformDocAdv.inc')) {
			if ($isWeb) {
				$output .= '<span class="comment">PHPDocX includes OpenOffice but you can download a custom version from http://www.openoffice.org/download</span>' . $break;
			}
		}
	}
	/*
	// steps to install the plugin
	if ($isWeb) {
		$output .= '<span>Click here if you need help to install the conversion plugin.</span>' . $break;
		$output .= '<ol class="sublevel">';
			$output .= '<li>';
				$output .= '<span>OpenOffice is used to transform DOCX to PDF and other formats.</span>';
				$output .= '<span>Do a test.</span>';
				$output .= '<span id="test-output-openoffice">Do a test.</span>';
			$output .= '</li>';
			$output .= '<li>';
				$output .= '<span>OdfConverter allows to transform DOCX to ODT to get the best output when the document has tables or complex content. PHPDocX includes OdfConverter versions for Linux 32 bits and 64 bits and Windows.</span>';
				$output .= '<span>Do a test.</span>';
				$output .= '<span id="test-output-odfconverter">Do a test.</span>';
			$output .= '</li>';
			$output .= '<li>';
				$output .= '<span>PHPDocX includes four options to do the transformation: with or without OdfConverter and using passthru or an external script. The method to use will depend on your server config and access permissions.</span>';
				$output .= '<span>Test OpenOffice with OdfConverter using the direct method.</span>';
				$output .= '<span>Test OpenOffice without OdfConverter using the direct method.</span>';
				$output .= '<span>Test OpenOffice with OdfConverter using the script method.</span>';
				$output .= '<span>Test OpenOffice without OdfConverter using the script method.</span>';
				$output .= '<span id="test-output-run">Do a test.</span>';
			$output .= '</li>';
		$output .= '</ol>';
	}*/
}
if ($isWeb) {
	$output .= '</li>';
}

// Info output
if ($isWeb) {
	$output .= '<li class="even">';
}

if ($isWeb) {
	$output .= '<span>';
}
if ($isWeb) {
	$output .= '</span>';
}
$output .= $break . $break;
$output .= 'If you have any issue or problem please send us the following info:' . $break;
if ($isWeb) {
	$output .= '<textarea onClick="this.select();">';
}
require_once 'classes/CreateDocx.inc';
require_once 'classes/PhpdocxUtilities.inc';
$output .= 'PHP_VERSION: ' . PHP_VERSION . "\n";
$output .= 'PHP_OS: ' . PHP_OS . "\n";
$output .= 'PHP_UNAME: ' . php_uname() . "\n";
$output .= 'CODE: ' . $phpdocxconfig['license']['code'] . "\n";
$output .= 'SERVER_NAME: ' . $_SERVER['SERVER_NAME'] . "\n";
$output .= 'SERVER_SOFTWARE: ' . $_SERVER['SERVER_SOFTWARE'] . "\n";
$output .= 'SERVER_ADDR: ' . $_SERVER['SERVER_ADDR'] . "\n";
$output .= 'SERVER_PROTOCOL: ' . $_SERVER['SERVER_PROTOCOL'] . "\n";
$output .= 'HTTP_HOST: ' . $_SERVER['HTTP_HOST'] . "\n";
$output .= 'HTTP_X_FORWARDED_FOR: ' . $_SERVER['HTTP_X_FORWARDED_FOR'] . "\n";
$output .= 'PHP_SELF: ' . $_SERVER['PHP_SELF'] . "\n";
$output .= 'XSLTProcessor: ' . class_exists('XSLTProcessor') . "\n";
$output .= 'ZipArchive: ' . class_exists('ZipArchive') . "\n";
$output .= 'DomDocument: ' . class_exists('DomDocument') . "\n";
$output .= 'SimpleXMLElement: ' . class_exists('SimpleXMLElement') . "\n";
$output .= 'Tidy: ' . class_exists('Tidy') . "\n";
$output .= 'IS_WRITABLE DEFAULT TEMP: ' . is_writable(CreateDocx::getTempDir()) . "\n";

if ($isWeb) {
	$output .= '</textarea>';
}
if ($isWeb) {
	$output .= '</li>';
}


if ($isWeb) {
	$output .= '</ul>';
	$output .= '</div>';
	$output .= '<div class="clear" />';
	$output .= '</div>';
	$output .= '</div>';
	$output .= '</body>';
	$output .= '</html>';
}

echo $output;