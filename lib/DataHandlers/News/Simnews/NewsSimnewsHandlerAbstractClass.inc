<?php
require_once('path.php');

/**
 * @author Hardolaf
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

    public function getPost($index) {
        if(!is_numeric($index) || !array_key_exists($index, $this->posts)) {
            throw new Exception('Requested index does not exist');
        }

        $PostRequest = new RestRequest('news-simnews-item', 'GET', WEB_API_CONFIG_VERSION, array(), WEB_API_CONFIG_SERVER, $this->posts['index']);
        $PostRequest->execute();
        $PostResponse = new RequestHandler($PostRequest);

        return $PostResponse->handler;
    }

    public function getAllPosts() {
        $posts = array();
        foreach($this->posts as $href) {
            $PostRequest = new RestRequest('news-simnews-item', 'GET', WEB_API_CONFIG_VERSION, array(), WEB_API_CONFIG_SERVER, $href);
            $PostRequest->execute();
            $PostResponse = new RequestHandler($PostRequest);

            $posts[] = $PostResponse->handler;
        }
        return $posts;
    }
}

?>
