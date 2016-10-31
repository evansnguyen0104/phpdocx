<?php

/**
 * Logger
 *
 * @category   Phpdocx
 * @copyright  Copyright (c) 2009-2011 Narcea Producciones Multimedia S.L.
 *             (http://www.2mdc.com)
 * @license    http://www.phpdocx.com/wp-content/themes/lightword/pro_license.php
 * @version    2013.01.09
 * @link       http://www.phpdocx.com
 * @since      2013.01.09
 */

class PhpdocxLogger
{
    /**
     *
     * @access private
     * @static
     * @var string
     */
    private static $_log = NULL;

    /**
     * Singleton, return instance of class
     *
     * @access public
     * @param $message Message to send to logging framework
     * @param $level Allowed values: trace, debug, info, warn, error, fatal
     * @static
     */
    public static function logger($message, $level)
    {
        $levels = array(
            'debug', 
            'info', 
            'notice', 
            'warning', 
            'error', 
            'fatal',
        );

        if (!self::$_log) {
            Logger::configure(dirname(__FILE__) . '/../config/log4php.xml');
            self::$_log = Logger::getLogger('phpdocx_logger');
        }

        // only some levels are valid
        if (in_array($level, $levels)) {
            $stringLevel = strtolower($level);
            self::$_log->info($message);

            // stop phpdocx if fatal level
            if ($level == 'fatal') {
                throw new Exception($message);
            }
        }
    }
}