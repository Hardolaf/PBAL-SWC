<?php
require_once 'path.php';

/**
 * @author Hardolaf
 */
class GUIDraw {

    public $title;
    public $authentication;

    public function drawHeader($title, $authentication = null) {
        if($authentication !== null) {
            //do something
        }

        //Record the information
        $this->title = $title;
        $this->authentication = $authentication;

        //Use for fallback for non-javascript enabled browsers.
        $TimeCGTRequest = new RestRequest('time-CGT');
        $TimeCGTRequest->execute();
        $TimeCGTResponse = new RequestHandler($TimeCGTRequest);

        print <<<END
<!DOCTYPE html>
<html>
    <head>
        <meta http-equiv="Content-Type" content="text/html; charset=UTF-8">
        <title>{$this->title}</title>
        <script type="text/javascript">
            function updateClock ( )
            {
                var offset = 17;
                var o = new Date();
                var utc = o.getTime() + (o.getTimezoneOffset() * 60000);
                var currentTime = new Date ( utc + (3600000*offset) );
                var opening=new Date(Date.UTC(1998, 11, 3, 16, 0 ,0)); //Month is 0-11 in JavaScript

                var currentHours = currentTime.getHours ( );
                var currentMinutes = currentTime.getMinutes ( );
                var currentSeconds = currentTime.getSeconds ( );

                //Set 1 day in milliseconds
                var one_day=1000*60*60*24
                
                //Calculate difference btw the two dates, and convert to days
                days = (Math.floor((currentTime.getTime()-opening.getTime())/(one_day))) - 1;
                
                years = Math.floor(days / 365);
                days -= years * 365;

                // Pad the minutes and seconds with leading zeros, if required
                currentMinutes = ( currentMinutes < 10 ? "0" : "" ) + currentMinutes;
                currentSeconds = ( currentSeconds < 10 ? "0" : "" ) + currentSeconds;

                // Compose the string for display
                var currentTimeString = currentHours + ":" + currentMinutes + ":" + currentSeconds;

                // Update the time display
                document.getElementById("years").firstChild.nodeValue = years;
                document.getElementById("days").firstChild.nodeValue = days;
                document.getElementById("time").firstChild.nodeValue = currentTimeString;
            }
        </script>
    </head>
    <body onload="updateClock(); setInterval('updateClock()', 1000 )">
        <div>
            <strong>NewsBine</strong>
        </div>
        <div>
            <table>
                <tr>
                    <td>
                        Year
                    </td>
                    <td>
                        Day
                    </td>
                    <td>
                        Time
                    </td>
                </tr>
                <tr>
                    <td id="years">
                        {$TimeCGTResponse->handler->years}
                    </td>
                    <td id="days">
                        {$TimeCGTResponse->handler->hours}
                    </td>
                    <td id="time">
                        {$TimeCGTResponse->handler->getTime()}
                    </td>
                </tr>
            </table>
        </div>
        
END;
    }

    public function drawFooter() {
        print <<<END
    </body>
</html>
END;
    }
}

?>
