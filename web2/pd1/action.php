<?php
switch($_GET['action']) {
    case 'part2': part2(); break;
    case 'part3': part3(); break;
    case 'part4': part4(); break;
    default: break;
}

function fibonacci($n) {
    if ($n < 1)      { return "invalid"; }
    elseif ($n == 1) { return "0"; }
    elseif ($n == 2) { return "1"; }
    else {
        $sum = fibonacci($n - 1) + fibonacci($n - 2);
        return $sum;
    }
}

function part2() {
    for ($i = 1; $i <= 9; $i++) {
        for ($j = 1; $j <= $i; $j++) {
            echo $i * $j . " ";
        }
        echo "<br>";
    }

    $i = (int)$_POST['fib'];
    echo "<br>The $i Fibonacci number is " . fibonacci($i) . "<br><br>";

    for ($i = 1; $i <= 12; $i++) {
        echo "The $i Fibonacci number is " . fibonacci($i) . "<br>";
    }
}

function part3() {
    $n = (int)$_POST['fibTo'];

    if ($n < 1) { echo "No values"; }

    for ($i = 1; $i <= $n; $i++) {
        echo fibonacci($i);
        if ($i != $n) {
            echo ", ";
        }
    }
}

function part4() {
    $n = (int)$_POST['isFib'];

    $isFib = FALSE;
    for ($i = 1; TRUE; $i++) {
        $fib = fibonacci($i);

        if ($n == $fib) {
            $isFib = TRUE;
            break;
        }
        elseif ($n < $fib) {
            break;
        }
    }

    if ($isFib) { echo "$n is a Fibonacci number."; }
    else        { echo "$n is not a Fibonacci number."; }
}
?>
