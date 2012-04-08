<?php
/**
 * @author Joseph 'Hardolaf' Warner <hardolaf@gmail.com>
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

        $this->savePost();
    }

    public function savePost() {
        $DB = new DB();

        $DB->prepare("REPLACE INTO news_gns SET id = ?, url = ?, logo = ?, author = ?, hacked = ?, location = ?, faction = ?, factionType = ?, title = ?, body = ?, postdate = ?,
                postdateUNIX = ?, category = ?, lastAccessTime = ?", $this->id, $this->url, $this->logo, $this->author, $this->hacked, $this->location, $this->faction, $this->factionType,
                $this->title, $this->body, $this->postdate, $this->postdateUNIX, $this->category, time());
    }
}

?>
