<?php
/**
 * @author Joseph 'Hardolaf' Warner <hardolaf@gmail.com>
 */
class NewsGnsEconomyPUTHandler extends NewsGnsHandlerAbstract {

    public function __construct(Array $response) {
        //Basic information that does not change.
        $this->name = 'news-gns-economy';
        $this->method = 'PUT';

        $this->__constructData($response['result']);
    }
}

?>
