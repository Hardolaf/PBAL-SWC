/** Donated by Noba Argetlam**/
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