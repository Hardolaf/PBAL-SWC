<?php
/**
 * @author Joseph 'Hardolaf' Warner <hardolaf@gmail.com>
 */
class RatelimitsGETHandler extends DataHandler {

    protected $name;
    protected $method;
    protected $services;

    public function __construct(Array $response) {
        //Basic information that does not change.
        $this->name = 'ratelimits';
        $this->method = 'GET';

        $response = $response['ratelimits'];
        $this->services = array();
        foreach($response->ratelimit as $value) {
            $key = $value->pattern;
            $this->services[$key]['limit'] = $value->limit;
            $this->services[$key]['remaining'] = $value->remaining;
            $this->services[$key]['reset'] = $value->reset;
            $this->services[$key]['reset_time'] = $value->reset_time;
        }
    }
}

?>
