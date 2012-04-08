<?php
/**
 * @author Joseph 'Hardolaf' Warner <hardolaf@gmail.com>
 */
abstract class DataHandler {

    //Required for all classes to work
    protected $name;
    protected $method;

    public function __get($name) {
        return $this->$name;
    }

    public function __toString() {
        return $this->name.'::'.$this->method;
    }
}

?>
