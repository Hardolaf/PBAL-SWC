<?php
require_once('../NewsSimnewsHandlerAbstractClass.inc');

/**
 * @author Hardolaf
 */
class NewsSimnewsTechnicalGETHandler extends NewsSimnewsHandlerAbstract {

    public function __construct(Array $response) {
        //Basic information that does not change.
        $this->name = 'news-simnews-technical';
        $this->method = 'GET';

        $this->__constructData($response['simnews-technical']);
    }
}

?>
