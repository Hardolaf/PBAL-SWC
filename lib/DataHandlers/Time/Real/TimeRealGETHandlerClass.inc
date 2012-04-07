<?php
require_once('/../path.php');

/**
 * @author Joseph 'Hardolaf' Warner
 */
class TimeRealGetHandler extends DataHandler {
    //Restrict all data from modification.
    protected $name;
    protected $method;
    protected $timestamp;
    protected $timeZone;

    public function __construct(Array $response) {
        //Basic information that does not change.
        $this->name = 'time-real';
        $this->method = 'GET';
        $this->timeZone = 'Australia/ACT';

        //Variable information provided the response
        $response = $response['time-real'];
        $this->timestamp = $response->time;
    }
}

?>
