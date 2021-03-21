<?php

/**
 * This is the main file which receives and analyzes data,
 * generates response data and finally calls the template.
 */

// show all warnings and errors on the screen
error_reporting(E_ALL);
ini_set('display_errors', 1);

$currencies = array ("USD"=>"US dollar",
"JPY"=>"Japanese yen",
"BGN"=>"Bulgarian lev",
"CZK"=>"Czech koruna",
"DKK"=>"Danish krone",
"GBP"=>"Pound sterling",
"HUF"=>"Hungarian forint",
"PLN"=>"Polish zloty",
"RON"=>"Romanian leu",
"SEK"=>"Swedish krona",
"CHF"=>"Swiss franc",
"ISK"=>"Icelandic krona",
"NOK"=>"Norwegian krone",
"HRK"=>"Croatian kuna",
"RUB"=>"Russian rouble",
"TRY"=>"Turkish lira",
"AUD"=>"Australian dollar",
"BRL"=>"Brazilian real",
"CAD"=>"Canadian dollar",
"CNY"=>"Chinese yuan renminbi",
"HKD"=>"Hong Kong dollar",
"IDR"=>"Indonesian rupiah",
"ILS"=>"Israeli shekel",
"INR"=>"Indian rupee",
"KRW"=>"South Korean won",
"MXN"=>"Mexican peso",
"MYR"=>"Malaysian ringgit",
"NZD"=>"New Zealand dollar",
"PHP"=>"Philippine peso",
"SGD"=>"Singapore dollar",
"THB"=>"Thai baht",
"ZAR"=>"South African rand");

// DO NOT EDIT BEFORE THIS LINE

/* Functions and classes You might want to use (you have to study function descriptions and examples)
 * Note: You can easily solve this task without using any regular expressions
file_get_contents() http://lv1.php.net/file_get_contents
file_put_contents() http://lv1.php.net/file_put_contents
file_exists() http://lv1.php.net/file_exists
round() http://lv1.php.net/round
SimpleXMLElement http://php.net/manual/en/simplexml.examples-basic.php http://php.net/manual/en/class.simplexmlelement.php
date() http://lv1.php.net/manual/en/function.date.php or Date http://lv1.php.net/manual/en/class.datetime.php
Multiple string functions (choose by studying descriptions) http://lv1.php.net/manual/en/ref.strings.php
Multiple variable handling functions (choose by studying descriptions) http://lv1.php.net/manual/en/ref.var.php
Optionally you can use some array functions (with $_GET, $target_currencies) http://lv1.php.net/manual/en/ref.array.php
*/

// Your code goes here

$result = ""; //valid values: empty string, "OK", "ERROR"
$result_message = "";
$date = "";

function error(string $msg) {
    global $result;
    global $result_message;
    $result = "ERROR";
    $result_message .= $msg . "\n";
}

function success(string $msg, string $time) {
    global $result;
    global $result_message;
    global $date;
    if (!is_error()) {
        $result = "OK";
        $result_message = $msg;
        $date = $time;
    }
}

function is_error() : bool {
    global $result;
    return $result == "ERROR";
}

function get_conversion_rate(string $currency, DateTime $datetime) : float {
    $xml_data = "";

    // Load stored conversion rate table
    $path = "xml/".$currency.".xml";
    if (file_exists($path)) {
        $xml_data = simplexml_load_file($path);
    }
    // Download new conversion rate table
    else {
        $str_data = @download_conversion_rates($currency);
        if ($str_data == FALSE) {
            error("Failed to retrieve conversion rates!");
            return "";
        }
        $xml_data = simplexml_load_string($str_data);
    }

    // Look for relevant rate
    $rates = $xml_data->DataSet->Series->Obs;
    $rate = find_rate($rates, $datetime);

    // Try download newest converion rates
    // Search for needed date again
    if (!$rate) {
        $str_data = @download_conversion_rates($currency);
        if ($str_data == FALSE) {
            error("Failed to retrieve conversion rates!");
            return "";
        }
        $xml_data = simplexml_load_string($str_data);

        $rates = $xml_data->DataSet->Series->Obs;
        $rate = find_rate($rates, $datetime);
    }

    return $rate;
}

function download_conversion_rates(string $currency) : string {
    $path = "xml/".$currency.".xml";
    $url = "https://www.ecb.europa.eu/stats/policy_and_exchange_rates/euro_reference_exchange_rates/html/".strtolower($currency).".xml";
    $data = file_get_contents($url);
    file_put_contents($path, $data);
    return $data;
}

function find_rate(SimpleXMLElement $rates, DateTime $datetime) : string {
    foreach ($rates as $r) {
        if ($r['TIME_PERIOD'] == $datetime->format("Y-m-d")) {
            return $r['OBS_VALUE'];
        }
    }
    return "";
}

if ($_GET) {
    $in_date = $_GET["date"];
    $in_amount = $_GET["amount"];
    $in_currency = $_GET["currency"];
    $datetime = new DateTime($in_date);

    // Verify date
    if (!$in_date)                      { error("Missing date!"); }
    elseif ($datetime > new DateTime()) { error("Date is in the future!"); }

    // Verify amount
    if (!$in_amount)                    { error("Missing amount!"); }
    elseif (!is_numeric($in_amount))    { error("Invalid amount!"); }
    elseif (floatval($in_amount) < 0)   { error("Invalid amount!"); }

    // Verify currency
    if (!$in_currency)                  { error("Missing currency!"); }

    // Avoid weekend dates
    if ($datetime->format('N') >= 6) {
        $datetime->modify("-".($datetime->format('N') % 5)." day");
    }

    if (!is_error()) {
        // Convert currency to Euro
        $rate = get_conversion_rate($in_currency, $datetime);
        $value = round(floatval($in_amount) / floatval($rate), 2);

        success($value, $datetime->format("Y-m-d"));
    }
}

// DO NOT EDIT AFTER THIS LINE

require("view.php");