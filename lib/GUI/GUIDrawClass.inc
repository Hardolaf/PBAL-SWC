<?php
/**
 * @author Joseph 'Hardolaf' Warner <hardolaf@gmail.com>
 */
class GUIDraw {

    public $title;
    public $authentication = null;

    public function __construct($page) {
        if($page != 'default') {
            $page = explode('-', $page);
            $this->title = 'NewsBine - '.implode(' ', $page);
        } else {
            $page = array($page);
            $this->title = 'NewsBine - Home';
        }

        $this->drawHeader();

        $page = 'pages/'.implode('/', $page).'.php';
        if(file_exists($page)) {
            require_once($page);
        } else {
            $this->throw404();
        }

        $this->drawFooter();
    }

    private function drawHeader() {
        if($this->authentication !== null) {
            //do something
        }

        //Use for fallback for non-javascript enabled browsers.
        $TimeCGTRequest = new RestRequest('time-CGT');
        $TimeCGTRequest->execute();
        $TimeCGTResponse = new RequestHandler($TimeCGTRequest);

?><!DOCTYPE html>
<html>
    <head>
        <meta http-equiv="Content-Type" content="text/html; charset=UTF-8">
        <title><?php print $this->title; ?></title>
        <link rel="stylesheet" type="text/css" href="CSS/main.css">
        <link rel="stylesheet" type="text/css" href="CSS/testStyles.css">
        <script type="text/javascript" src="JS/main.js"></script>
        <script type="text/javascript" src="JS/livevalidation.js"></script>
    </head>
    <body onload="updateClock(); setInterval('updateClock()', 1000 )">
        <div class="title">
            <h1>NewsBine</h1>
        </div>
        <div class="header">
            <div class="navigation">
                <strong>Navigation:</strong>&nbsp;&nbsp;<a href="?page=default">Home</a>&nbsp;&nbsp;&nbsp;<a href="?page=GNS">GNS</a>
            </div>
        </div>
        <div class ="clock">
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
                        <?php print $TimeCGTResponse->handler->years; ?>
                    </td>
                    <td id="days">
                        <?php print $TimeCGTResponse->handler->hours; ?>
                    </td>
                    <td id="time">
                        <?php print $TimeCGTResponse->handler->getTime(); ?>
                    </td>
                </tr>
            </table>
        </div>
        <div class="body">
<?php
    }

    private function drawFooter() {
?>
        </div>
        <div class="footer_menu"> 
            <a href="?page=About">About</a>&nbsp;&nbsp;&nbsp;<a href="?page=Legal">Legal</a>&nbsp;&nbsp;&nbsp;<a href="<?php echo SERVICE_CONFIG_BUGTRACKER; ?>">Bugs</a>
        </div>
        <div class="powered_by">
            Powered by <a href="<?php echo SERVICE_CONFIG_NEWSBINE_LIBRARY_URL; ?>">PBAL-SWC v<?php echo SERVICE_CONFIG_NEWSBINE_VERSION; ?></a>
        </div>
        <div class="copyright">
            &copy; Joseph 'Hardolaf' Warner 2012 Licensed under a MIT license
        </div>
        <?php  if(SERVICE_CONFIG_PIWIK) {
            $this->piwik();
        } ?>
    </body>
</html>
<?php
    }

    private function piwik() {
        ?><!-- Piwik -->
        <script type="text/javascript">
            var pkBaseURL = (("https:" == document.location.protocol) ? "<?php echo SERVICE_CONFIG_PIWIK_URL_SECURE; ?>" : "<?php echo SERVICE_CONFIG_PIWIK_URL; ?>");
            document.write(unescape("%3Cscript src=\'" + pkBaseURL + "piwik.js\' type=\'text/javascript\'%3E%3C/script%3E"));
        </script>
        <script type="text/javascript">
            try {
                var piwikTracker = Piwik.getTracker(pkBaseURL + "piwik.php", <?php echo SERVICE_CONFIG_PIWIK_SITE_ID; ?>);
                piwikTracker.trackPageView();
                piwikTracker.enableLinkTracking();
            } catch( err ) {}
        </script>
        <noscript><p><img src="<?php echo SERVICE_CONFIG_PIWIK_URL; ?>piwik.php?idsite=<?php echo SERVICE_CONFIG_PIWIK_SITE_ID; ?>&amp;rec=1" style="border:0" alt="" /></p></noscript>
        <!-- End Piwik Tracking Code --><?php
    }

    private function throw404() {
        ?> The page you have requested does not exist. <?php
    }
}

?>
