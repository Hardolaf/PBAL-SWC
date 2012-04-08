<?php
/**
 * @author Joseph 'Hardolaf' Warner <hardolaf@gmail.com> 
 */
class Autoloader {
    public static $instance;

    private $_src=array('Datahandlers/',
        'Datahandlers/',
        'Datahandlers/News/',
        'Datahandlers/News/Gns/',
        'Datahandlers/News/Gns/Auto/',
        'Datahandlers/News/Gns/Economy/',
        'Datahandlers/News/Gns/Item/',
        'Datahandlers/News/Gns/Military/',
        'Datahandlers/News/Gns/Political/',
        'Datahandlers/News/Gns/Social/',
        'Datahandlers/News/Simnews/',
        'Datahandlers/News/Simnews/Community/',
        'Datahandlers/News/Simnews/Item/',
        'Datahandlers/News/Simnews/Player/',
        'Datahandlers/News/Simnews/Item/Technical/',
        'Datahandlers/Ratelimits/',
        'Datahandlers/Time/',
        'Datahandlers/Time/CGT/',
        'Datahandlers/Time/Real/',
        'GUI/',
        'Helpers/',
        'Helpers/News/',
        'Other/',
        'REST/',
        'User/');

    private $_ext=array('Class.inc', '.inc', '.php');

    /* initialize the autoloader class */
    public static function init(){
        if(self::$instance==NULL){
            self::$instance=new self();
        }
        return self::$instance;
    }

    /* put the custom functions in the autoload register when the class is initialized */
    private function __construct(){
        spl_autoload_register(array($this, 'clean'));
        spl_autoload_register(array($this, 'dirty'));
    }

    /* the clean method to autoload the class without any includes, works in most cases */
    private function clean($class){
        global $docroot;
        global $originalIncludePath;
        spl_autoload_extensions(implode(',', $this->_ext));
        foreach($this->_src as $resource){
            set_include_path($docroot . $resource);
            spl_autoload($class);
        }
        set_include_path($originalIncludePath);
    }

    /* the dirty method to autoload the class after including the php file containing the class */
    private function dirty($class){
        global $docroot;
        foreach($this->_src as $resource){
            foreach($this->_ext as $ext){
                @include($docroot . $resource . $class . $ext);
            }
        }
        spl_autoload($class);
    }

}
$originalIncludePath = get_include_path();
$docroot = __DIR__.'/';
Autoloader::init();
?>
