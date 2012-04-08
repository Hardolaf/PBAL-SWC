<?php
/**
 * @author Joseph 'Hardolaf' Warner <hardolaf@gmail.com>
 */
abstract class NewsSimnewsHandlerAbstract extends DataHandler {
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
        $this->requestName = 'news-simnews-item';
        $this->total = $response->total;
    }

    public function getPost($index, $refresh = false) {
        if(!array_key_exists($index, $this->posts)) {
            throw new Exception('Requested index does not exist');
        }

        return NewsSimnewsHelper::getPost($index, $refresh);
    }

    public function getAllPosts($refresh = false) {
        $posts = array();
        foreach($this->postIDs as $id) {
            $posts[] = NewsSimnewsHelper::getPost($id, $refresh);
        }
        return $posts;
    }

    public function savePost($index) {
        global $DB;

        if(!array_key_exists($index, $this->postsIDs)) {
            throw new InvalidArgumentException('Requested index does not exist');
        }

        $DB->query('INSERT IGNORE INTO news_simnews SET id ='.$this->postIDs[$index]);
    }

    public function savePostsAll() {
        global $DB;

        foreach($this->postIDs as $postID) {
            $DB->query('INSERT IGNORE INTO news_simnews SET id ='.$postID);
        }
    }
}

?>
