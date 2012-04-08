<?php
/**
 * @author Joseph 'Hardolaf' Warner <hardolaf@gmail.com>
 */
class TimeCGTPOSTHandler extends DataHandler {
    //Restrict all data from modification.
    protected $name;
    protected $method;
    protected $timestamp;
    protected $years;
    protected $days;
    protected $hours;
    protected $mins;
    protected $secs;

    public function __construct(Array $response) {
        //Basic information that does not change.
        $this->name = 'time-CGT';
        $this->method = 'POST';

        //Variable information provided the response
        $response = $response['result'];
        $this->timestamp = $response->timestamp;
        $this->years = $response->years;
        $this->days = $response->days;
        $this->hours = $response->hours;
        $this->mins = $response->mins;
        $this->secs = $response->secs;
    }
}

?>
