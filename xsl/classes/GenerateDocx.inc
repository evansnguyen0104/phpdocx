<?php

/**
 * Check for a valid license for IP
 *
 * @category   Phpdocx
 * @package    license
 * @copyright  Copyright (c) 2009-2013 Narcea Producciones Multimedia S.L.
 *             (http://www.2mdc.com)
 * @license    http://www.phpdocx.com/wp-content/themes/lightword/pro_license.php
 * @version    2013.03.04
 * @link       http://www.phpdocx.com
 * @since      File available since Release 1.0
 */
class GenerateDocx
{

    /**
     * Check for a valid license
     *
     * @access public
     * @return boolean
     */
    public static function beginDocx()
    {
        $xzerod = '';
        $xzerob = '';
        $xzeroc = '';
        $xcomp = '';
        $phpdocxconfig = PhpdocxUtilities::parseConfig();

        if (!isset($_SERVER['SERVER_NAME'])) {
            return;
        } else {
            $xzerod = trim($phpdocxconfig['license']['code']);
            $xzerob = trim(gethostbyname($_SERVER['SERVER_NAME']));
            $xzeroc = trim($_SERVER['SERVER_NAME']);
            $xcomp = trim($phpdocxconfig['license']['domain']);
        }

        if (
            preg_match('/^192.168./', $xzeroc) ||
            preg_match('/^172./', $xzeroc) ||
            preg_match('/^192.168./', $xzerob) ||
            preg_match('/^172./', $xzerob) ||
            preg_match('/^10./', $xzerob) ||
            preg_match('/^127.0.0./', $xzerob) ||
            preg_match('/localhost/', $xzeroc)
        ) {
            return;
        } elseif ($xzerod == md5($xzeroc . '_docx')) {
            return;
        } elseif ($xzerod == md5($xzerob . '_docx')) {
            return;
        }

        $serverNameSeg = explode('.', trim($_SERVER['SERVER_NAME']));
        $serverNamePart = '';
        $serverNameSegI = count($serverNameSeg);
        for ($i = $serverNameSegI-1; $i >= 0; $i--) { 
            if (empty($serverNamePart)) {
                $serverNamePart = $serverNameSeg[$i];
            } else {
                $serverNamePart = $serverNameSeg[$i] . '.' . $serverNamePart;
            }
            if ($xzerod == md5($serverNamePart . '_docx')) {
                return;
            }
        }

        throw new Exception('There is not a valid license');
    }

}
