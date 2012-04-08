<?php
/**
 * @author Hardolaf
 */
abstract class NewsGnsHandlerAbstract extends DataHandler {
    protected $name;
    protected $method;
    protected $posts;
    protected $postIDs;
    protected $requestName;
    protected $total;

    abstract function __construct(array $response);

    public function __constructData($response) {
        //Variable information provided the response
        $this->posts = array();
        $this->postIDs = array();
        foreach ($response->posts as $post) {
            $this->posts[] = $post->href;

            $post = rtrim($post->href, '/');
            $post = strrchr($post, '/');
            $this->postIDs[] = (int)ltrim($post, '/');;
        }
        $this->requestName = 'news-gns-item';
        $this->total = $response->total;

        $this->savePostIDs();
    }

    public function getPost($index, $refresh = false) {
        if(!is_numeric($index) || !array_key_exists($index, $this->postIDs)) {
            throw new Exception('Requested index does not exist');
        }

        return NewsGNSHelper::getPost($this->postIDs[$index], $refresh);
    }

    public function getAllPosts($refresh = false) {
        $posts = array();
        foreach($this->postIDs as $id) {
            $posts[] = NewsGNSHelper::getPost($id, $refresh);
        }
        return $posts;
    }

    public function savePost($index) {
        $DB = new DB();

        if(!array_key_exists($index, $this->postsIDs)) {
            throw new InvalidArgumentException('Requested index does not exist');
        }

        $DB->query('INSERT IGNORE INTO news_gns SET id ='.$this->postIDs[$index]);
    }

    public function savePostIDs() {
        $DB = new DB();

        foreach($this->postIDs as $postID) {
            $DB->query('INSERT IGNORE INTO news_gns SET id ='.$postID);
        }
    }
}

?>
