<?php
/**
 * @author Joseph 'Hardolaf' Warner
 */
class RequestHandler {

    //The $response that is pulled from the request.
    protected $responseInfo;

    //The handler that is called to handle the data.
    protected $handler;

    public function __construct(RestRequest $request) {
        $this->isValidRequest($request);

        $response = get_object_vars(json_decode($request->responseBody));
        if(count(array_keys($response)) > 1) {
            throw new Exception('Only one return per request is permitted.');
        }

        $parts = explode('-', $request->name);
        $name = '';
        $includePath = 'DataHandlers/';
        foreach($parts as $part) {
            $name .= ucfirst($part);
            $includePath .= ucfirst($part).'/';
        }
        $handlerName = $name.$request->verb.'Handler';
        $include = $includePath.$handlerName.'Class.inc';
        
        require_once($include);

        $this->responseInfo = $request->responseInfo;
        $this->handler = new $handlerName($response);
        return $this->handler;
    }

    private function isValidRequest(RestRequest $request) {
        switch ($request->responseInfo['http_code']):
            case 200:
            case 201:
                return;
            case 403:
                $RateRequest = new RestRequest('ratelimits');
                $RateRequest->execute();
                $RateResponse = new RequestHandler($RateRequest);
                $messages = array();
                foreach($RateResponse->handler->services as $key => $value) {
                    if($value['remaining'] <= 0) {
                        $messages[] = $key.'\'s rate limit has been reached, it will reset at '.$value['reset_time'];
                    }
                }
                $messages = implode($messages, '; ');
                throw new Exception('One or more rate limit has been exceeded: '.$messages);
            case 400:
            case 401:
            case 404:
            case 500:
                throw new Exception($request->responseBody);
            case 405:
                throw new Exception('Internal error at the Web API server.');
            default:
                throw new Exception('Unknown status code: '.$request->responseInfo['http_code']);
        endswitch;
    }

    public function __get($name) {
        return $this->$name;
    }
}

?>
