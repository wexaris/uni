
function avgOfNumbers(array) {
    var count = 0;
    var sum = 0;

    for (var i = 0; i < array.length; i++) {
        if (Number.isInteger(array[i])) {
            sum += array[i];
            count++;
        }
    }

    return sum / count;
}