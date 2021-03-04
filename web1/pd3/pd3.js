/*
 * Work in this file.
 *
 */

var words = [];
/* create a list of dictionary words for task #2 */
for (var i in my_dict) {
    words.push(i);
}

function add_content() {
    var ul = document.createElement("ul");
    for (i = 1; i <= 2; i++) {
        var p = document.createElement("p");
        p.innerHTML = "paragraph " + i;

        var li = document.createElement("li");
        li.appendChild(p);
        li.style.color = randomColor();
        li.style.fontWeight = "bold"
        li.style.textAlign = "center"

        ul.appendChild(li);
    }

    document.getElementById("task1-content").appendChild(ul);
}

window.onload = function () {
    /* this code gets executed when the page has loaded */
    console.log("On-load function started");

    document.title = "Rainers rv20039";

    /* Dictionary */
    var wordSelect = document.getElementById("word-select");
    for (var i = 0; i < words.length; i++) {
        var opt = document.createElement("option");
        opt.setAttribute("value", words[i]);
        opt.innerHTML = words[i];

        wordSelect.appendChild(opt);
    }
    wordSelect.onchange = translateDict;
    wordSelect.value = ""

    /* Translation app */
    var input = document.createElement("input");
    input.id = "input";
    input.type = "text";
    input.size = 80;

    var button = document.createElement("button");
    button.onclick = translateText;
    button.innerHTML = "Translate";

    var output = document.createElement("input");
    output.id = "output";
    output.type = "text";
    output.size = 80;
    output.readOnly = true;

    var translationApp = document.getElementById("translation-app");
    translationApp.firstElementChild.innerHTML = "Input text:";
    translationApp.appendChild(input);
    translationApp.appendChild(button);
    translationApp.appendChild(output);
    translationApp.insertBefore(document.createElement("br"), button);
    translationApp.insertBefore(document.createElement("br"), button);
    translationApp.insertBefore(document.createElement("br"), output);
    translationApp.insertBefore(document.createElement("br"), output);

    var example1 = document.createElement("p");
    example1.innerHTML = 'The text "Elephant is happy" translates to "zilonis ir laimīgs".';
    var example2 = document.createElement("p");
    example2.innerHTML = 'The text "Apple is black. Pear is blue" translates to "Ābols ir melns. Bumbieris ir blue".';

    var defaultExample = document.getElementsByTagName("h4")[0].nextElementSibling;
    defaultExample.parentElement.insertBefore(example1, defaultExample);
    defaultExample.parentElement.insertBefore(example2, defaultExample);
    defaultExample.parentElement.removeChild(defaultExample);
}

function translateDict() {
    var wordIn = document.getElementById("input");
    var wordOut = document.getElementById("word-output");
    wordOut.innerHTML = "Translation: " + my_dict[wordIn.value];
}

function translateText() {
    var input = document.getElementById("input");
    var output = document.getElementById("output");

    // Translate if word defined
    var text = input.value.replace(/(\w+)/g, function(w) {
        if (w.toLowerCase() in my_dict) { return my_dict[w.toLowerCase()]; }
        return w;
    })
    // Uppercase first
    text = text.charAt(0).toUpperCase() + text.slice(1);
    // Uppercase after a period
    text = text.replace(/(?<=\. )(\w+)/g, w => w.charAt(0).toUpperCase() + w.slice(1));

    output.value = text;
}

function randomColor() {
    var letters = '0123456789ABCDEF';
    var color = '#';
    for (var i = 0; i < 6; i++) {
        color += letters[Math.floor(Math.random() * 16)];
    }
    return color;
}

