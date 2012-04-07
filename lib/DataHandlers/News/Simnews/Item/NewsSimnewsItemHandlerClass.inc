<?php
require_once('path.php');

/**
 * @author Hardolaf
 */
class NewsSimnewsItemGETHandler extends DataHandler {

    protected $name;
    protected $method;
    protected $url;
    protected $logo;
    protected $author;
    protected $lastEditHandle;
    protected $lastEditDate;
    protected $lastEditSec;
    protected $title;
    protected $body;
    protected $postdate;
    protected $postdateUNIX;
    protected $id;
    protected $category;

    public function __construct(Array $response) {
        //Basic information that does not change.
        $this->name = 'news-simnews-item';
        $this->method = 'GET';

        $response = $response['simnews-item'];
        $this->url = $response->url;
        $this->logo = $response->logo;
        $this->author = $response->author;
        $this->lastEditHandle = $response->lastEditHandle;
        $this->lastEditDate = $response->lastEditDate;
        $this->lastEditSec = $response->lastEditSec;
        $this->title = $response->title;
        $this->body = $response->body;
        $this->postdate = $response->postdate;
        $this->postdateUNIX = $response->postdateUNIX;
        $this->id = $response->id;
        $this->category = $response->category;
    }
}

?>
