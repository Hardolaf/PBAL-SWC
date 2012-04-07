<?php
require_once('path.php');

/**
 * @author Hardolaf
 */
class NewsGNSItemGETHandler extends DataHandler {

    protected $name;
    protected $method;
    protected $url;
    protected $logo;
    protected $author;
    protected $hacked;
    protected $location;
    protected $faction;
    protected $factionType;
    protected $title;
    protected $body;
    protected $postdate;
    protected $postdateUNIX;
    protected $id;
    protected $category;

    public function __construct(Array $response) {
        //Basic information that does not change.
        $this->name = 'news-gns-item';
        $this->method = 'GET';

        $response = $response['gns-item'];
        $this->url = $response->url;
        $this->logo = $response->logo;
        $this->author = $response->author;
        $this->hacked = (bool)$response->hacked;
        $this->location = $response->location;
        $this->faction = $response->faction;
        $this->factionType = $response->factionType;
        $this->title = $response->title;
        $this->body = $response->body;
        $this->postdate = $response->postdate;
        $this->postdateUNIX = $response->postdateUNIX;
        $this->id = $response->id;
        $this->category = $response->category;
    }
}

?>
