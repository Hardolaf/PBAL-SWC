<?php
require_once('/../path.php');

/**
 * @author Joseph 'Hardolaf' Warner
 */
class TimeRealPOSTHandler extends DataHandler {
    //Restrict all data from modification.
    protected $name;
    protected $method;
    protected $timeZone;
    protected $timeStamp;

    public function __construct(Array $response) {
        //Basic information that does not change.
        $this->name = 'time-real';
        $this->method = 'POST';
        $this->timeZone = 'Australia/ACT';

        //Variable information provided the response
        $response = $response['result'];
        $this->timestamp = $response->time;
    }
}

?>
