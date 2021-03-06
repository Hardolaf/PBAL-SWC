<?php
/**
 * @author Joseph 'Hardolaf' Warner <hardolaf@gmail.com>
 */
class NewsSimnewsCommunityGETHandler extends NewsSimnewsHandlerAbstract {

    public function __construct(Array $response) {
        //Basic information that does not change.
        $this->name = 'news-simnews-community';
        $this->method = 'GET';

        $this->__constructData($response['simnews-community']);
    }
}

?>
