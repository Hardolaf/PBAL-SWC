<?php
/**
 * @author Joseph 'Hardolaf' Warner <hardolaf@gmail.com>
 */
class NewsSimnewsHelper {
    static function getPost($postID, $refresh = false) {
        $DB = new DB();

        if($refresh) {
            $href = WEB_API_CONFIG_SERVER.'ws/v'.WEB_API_CONFIG_VERSION.'/news/simnews/'.$postID.'/';
            $PostRequest = new RestRequest('news-simnews-item', 'GET', WEB_API_CONFIG_VERSION, array(), WEB_API_CONFIG_SERVER, $href);
            $PostRequest->execute();
            $PostResponse = new RequestHandler($PostRequest);
            $post = $PostResponse->handler;
        } else {
            $postReturn = $DB->query("SELECT * FROM news_simnews WHERE id = $postID AND lastAccessTime != 0");
            if($DB->num_rows($postReturn) == 1 ) {
                $post = $DB->fetch_object($postReturn);
            } else {
                return self::getPost($postID, true);
            }
        }
        return $post;
    }
}

?>
