<?php
/**
 * This class is a wrapper class that will send requests to the Star Wars Combine Server.
 * It is meant to serve any request you need.
 * 
 * To properly process data retrieved, helper classes will be included. 
 * 
 * @author Joseph 'Hardolaf' Warner
 */
class RestRequest
{
    //The name of the Web Service you are providing. Provide by path.php
    protected $WebAPIName;

    //The ID of your Web Service. Provide by path.php
    private $client_id;

    //The secret of your Web Service. Provide by path.php
    private $client_secret;

    //The name of the service being called
    protected $name;

    //The URL we'll request.
    protected $url;

    //The type of request we are to make ('GET', 'PUT', or 'POST' usually)
    protected $verb;

    //The request body we'll send with PUT and POST requests.
    protected $requestBody;

    //An internally used variable for PUT requests.
    protected $requestLength;

    //What kind of content we'll accept as a response
    protected $acceptType;

    //The body of the response
    protected $responseBody;

    //All other information from the response (status code, etc.)
    protected $responseInfo;

    /**
     * The construct function sets up the Rest Request.
     * 
     * @param string $url
     * @param string $verb
     * @param array $requestBody
     */
    public function __construct ($name, $verb = 'GET', $version=WEB_API_CONFIG_VERSION, array $requestBody = array(), $server=WEB_API_CONFIG_SERVER, $url = null)
    {
        $this->WebAPIName        = WEB_API_CONFIG_NAME;
        $this->client_id         = WEB_API_CONFIG_ID;
        $this->client_secret     = WEB_API_CONFIG_SECRET;
        $this->name              = $name;
        if($url === null && !in_array($name, array('ratelimits'))) {
            $this->url           = $server.'ws/v'.$version.'/'.str_replace('-', '/', $name).'/';
        } elseif($url === null && in_array($name, array('ratelimits'))) {
            $this->url           = $server.'ws/v'.$version.'/'.str_replace('-', '/', $name);
        } else {
            $this->url           = $url;
        }
        $this->verb              = $verb;
        $this->requestBody       = array_merge($requestBody, array('client_id' => $this->client_id, 'client_secret' => $this->client_secret));
        $this->requestLength     = 0;
        $this->acceptType        = 'application/json';
        $this->responseBody      = null;
        $this->responseInfo      = null;

        if (is_array($this->requestBody))
        {
            $this->buildBody();
        }
    }

    public function __get($name) {
        switch($name) {
            case 'ID':
            case 'secret':
                return null;
            default:
                return $this->$name;
        }
    }

    public function __isset ($name) {
        $val = $this->__get($name);
        return isset($val);
    }

    /**
     * Reset the response data from the server for another request.
     */
    public function flush ()
    {
        $this->requestBody       = null;
        $this->requestLength     = 0;
        $this->verb              = 'GET';
        $this->responseBody      = null;
        $this->responseInfo      = null;
    }

    /**
     * Executes the request that has been programmed in.
     * 
     * @throws InvalidArgumentException 
     */
    public function execute ()
    {
        $ch = curl_init();
        $this->setAuth($ch);

        try
        {
            switch (strtoupper($this->verb))
            {
                case 'GET':
                    $this->executeGet($ch);
                    break;
                case 'POST':
                    $this->executePost($ch);
                    break;
                case 'PUT':
                    $this->executePut($ch);
                    break;
                case 'DELETE':
                    $this->executeDelete($ch);
                    break;
                default:
                    throw new InvalidArgumentException('Current verb (' . $this->verb . ') is an invalid REST verb.');
            }
        }
        catch (InvalidArgumentException $e)
        {
            curl_close($ch);
            throw $e;
        }
        catch (Exception $e)
        {
            curl_close($ch);
            throw $e;
        }
    }

    /**
     * Builds the body of a request.
     * 
     * @param array $data
     * @throws InvalidArgumentException 
     */
    public function buildBody ($data = null)
    {
        $data = ($data !== null) ? $data : $this->requestBody;
        $data = array_merge($data, array('client_id' => $this->client_id, 'client_secret' => $this->client_secret));

        if (!is_array($data))
        {
            throw new InvalidArgumentException('Invalid data input for postBody.  Array expected');
        }

        $data = http_build_query($data, '', '&');
        $this->requestBody = $data;
    }

    /**
     * Executes a get request.
     *
     * @param type $ch - curl handle variable
     */
    protected function executeGet ($ch)
    {
        if (is_array($this->requestBody))
        {
            $this->buildBody();
        }
        if (is_string($this->requestBody)) {
            $this->url .= '?'.$this->requestBody;
        }

        $this->doExecute($ch);
    }

    /**
     * Executes a post request, make sure that the post body exists.
     *
     * @param type $ch  - curl handle variable
     */
    protected function executePost ($ch)
    {
        if (!is_string($this->requestBody))
        {
            $this->buildBody();
        }

        curl_setopt($ch, CURLOPT_POSTFIELDS, $this->requestBody);
        curl_setopt($ch, CURLOPT_POST, 1);

        $this->doExecute($ch);
    }

    /**
     * Executes a put request, builds post body and sets up the put request.
     *
     * @param type $ch - curl handle variable
     */
    protected function executePut ($ch)
    {
        if (!is_string($this->requestBody))
        {
            $this->buildBody();
        }

        $this->requestLength = strlen($this->requestBody);

        $fh = fopen('php://memory', 'rw');
        fwrite($fh, $this->requestBody);
        rewind($fh);

        curl_setopt($ch, CURLOPT_INFILE, $fh);
        curl_setopt($ch, CURLOPT_INFILESIZE, $this->requestLength);
        curl_setopt($ch, CURLOPT_PUT, true);

        $this->doExecute($ch);

        fclose($fh);
    }

    /**
     * Executes a delete request, may not be needed for the Combine.
     *
     * @param type $ch - curl handle variable
     * @deprecated - possibly
     */
    protected function executeDelete ($ch)
    {
        curl_setopt($ch, CURLOPT_CUSTOMREQUEST, 'DELETE');

        $this->doExecute($ch);
    }

    /**
     * Handles whatever request was sent to the object.
     *
     * @param type $curlHandle - curl handle variable
     */
    protected function doExecute (&$curlHandle)
    {
        $this->setCurlOpts($curlHandle);
        $this->responseBody = curl_exec($curlHandle);
        $this->responseInfo  = curl_getinfo($curlHandle);

        curl_close($curlHandle);
    }

    /**
     * Sets up the common options for every request.
     *
     * @param type $curlHandle - curl handle variable
     */
    protected function setCurlOpts (&$curlHandle)
    {
        curl_setopt($curlHandle, CURLOPT_TIMEOUT, 10);
        curl_setopt($curlHandle, CURLOPT_URL, $this->url);
        curl_setopt($curlHandle, CURLOPT_RETURNTRANSFER, true);
        curl_setopt($curlHandle, CURLOPT_HTTPHEADER, array ('Accept: ' . $this->acceptType));
    }

    /**
     * Establishs authorization for the request.
     *
     * @param type $curlHandle - curl handle variable
     */
    protected function setAuth (&$curlHandle)
    {
        /*if ($this->username !== null && $this->password !== null)
        {
            curl_setopt($curlHandle, CURLOPT_HTTPAUTH, CURLAUTH_DIGEST);
            curl_setopt($curlHandle, CURLOPT_USERPWD, $this->username . ':' . $this->password);
        }*/
    }

    public function setAcceptType ($acceptType)
    {
        $this->acceptType = $acceptType;
    }

    public function setUrl ($url)
    {
        $this->url = $url;
    }

    public function setVerb ($verb)
    {
        $this->verb = $verb;
    } 
}

?>
