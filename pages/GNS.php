<?php
require_once 'path.php';

$NewsRequest = new RestRequest('news-gns', 'GET', WEB_API_VERSION_0_1, array('item_count'=>5));
$NewsRequest->execute();
$NewsResponse = new RequestHandler($NewsRequest);
$posts = $NewsResponse->handler->getAllPosts();

foreach($posts as $post) {
    if($post->hacked == true) {
        $hacked = 'true';
    } else {
        $hacked = 'false';
    }
    print <<<END
        <br />
        <div style="border-style:solid;border-width:1px" id="post{$post->id}">
            <strong style="font-size:16px"><a href="{$post->url}"><img src="{$post->logo}">{$post->title}</a></strong><br />
            <strong>Author</strong>: {$post->author}<br />
            <strong>Faction</strong>: {$post->faction}<br />
            <strong>Location</strong>: {$post->location}<br />
            <strong>Hacked</strong>: {$hacked}<br />
            <strong>Posted</strong>: {$post->postdate}<br />
            <strong>Category</strong>: {$post->category}<br />
            {$post->body}
        </div>

END;
}
?>
