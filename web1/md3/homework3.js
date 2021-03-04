/*
 * Rainers Vorza rv20039
 */

const MIN_DATE = new Date('2020-10-01');

var timerId;

var continentDom;
var countryDom;
var dateFromDom;
var dateUntilDom;
var searchDom;
var showListDom;

var lookup = {};
var continents = [];
var countries = [];
var continentVal = 'all';
var countryVal = 'all';
var searchVal = '';

window.addEventListener('DOMContentLoaded', (event) => {
    // Save DOM elements
    continentDom = document.getElementById("continent-select");
    countryDom = document.getElementById('country-select');
    dateFromDom = document.getElementById('date-from');
    dateUntilDom = document.getElementById('date-until');
    searchDom = document.getElementById('search');
    showListDom = document.getElementById('show-list');

    // Build continent and country lookup table
    for (let i in data) {
        let continent = data[i].continentExp;
        let country = data[i].countriesAndTerritories;
        if (continent && !(continent in lookup)) {
            lookup[continent] = {};
        }
        lookup[continent][country] = 1;
    }

    // Get all of the continents
    continents = Object.keys(lookup).sort();

    // Add continents to selection
    for (let i in continents) {
        continentDom.appendChild(createOption(continents[i]));
    }

    // Get all of the countries
    for (let i = 0; i < continents.length; i++) {
        countries.push(...Object.keys(lookup[continents[i]]));
    }
    countries = countries.sort();

    // Add countries to selection
    for (let i in countries) {
        countryDom.appendChild(createOption(countries[i]));
    }

    // Add callbacks
    continentDom.onchange = onContinentSelect;
    countryDom.onchange = onCountrySelect;
    searchDom.oninput = onSearch;
    showListDom.onclick = debouncedUpdateList;

    // Populate initial list
    debouncedUpdateList();
});

function onContinentSelect() {
    continentVal = continentDom.value;

    // Remove all countries from country selection
    for (let i = countryDom.length - 1; i > 0; i--) {
        countryDom.remove(i);
    }
    // Add needed countries to selection
    for (let i in countries) {
        if (continentVal == 'all' || countries[i] in lookup[continentVal]) {
            countryDom.appendChild(createOption(countries[i]));
        }
    }

    // Preserve correct display of currently selected country, if still available
    if (continentVal == 'all' || countryVal in lookup[continentVal]) {
        countryDom.value = countryVal;
    }
    else {
        countryVal = 'all';
    }
};

function onCountrySelect() {
    countryVal = countryDom.value;
};

function onSearch() {
    searchVal = searchDom.value;
    if (searchVal && searchVal.length < 2) {
        return;
    }
    debouncedUpdateList();
};

// Prevent multiple calls when entering search string
function debouncedUpdateList() {
    clearTimeout(timerId);
    timerId = setTimeout(updateList, 750);
}

function updateList() {
    // Date filters
    let dateBeg = MIN_DATE;
    let dateEnd = new Date();

    // Reset bad date messages
    dateFromDom.style.borderColor = 'inherit';
    dateUntilDom.style.borderColor = 'inherit';
    document.getElementById('date-from-invalid').style.display = 'none';
    document.getElementById('date-until-invalid').style.display = 'none';

    // Verify selected date range
    let bad_date = false;
    if (dateFromDom.value) { // Start date
        dateBeg = new Date(dateFromDom.value);
        if (isNaN(dateBeg.valueOf()) || dateBeg < MIN_DATE) {
            dateFromDom.style.borderColor = 'red';
            document.getElementById('date-from-invalid').style.display = 'inline';
            bad_date = true;
        }
    }
    if (dateUntilDom.value) { // End date
        dateEnd = new Date(dateUntilDom.value);
        if (isNaN(dateEnd.valueOf()) || dateEnd > new Date()) {
            dateUntilDom.style.borderColor = 'red';
            document.getElementById('date-until-invalid').style.display = 'inline';
            bad_date = true;
        }
    }
    if (bad_date) { // Don't populate the list, if the date was invalid
        return;
    }

    // Replace old statistics table
    let oldStats = document.getElementById("statistics");
    let newStats = document.createElement("table");
    newStats.id = oldStats.id;
    newStats.appendChild(oldStats.firstElementChild);
    oldStats.parentElement.replaceChild(newStats, oldStats);

    // Add filtered entries
    for (let i in data) {
        let entryDate = new Date(data[i].year, data[i].month - 1, data[i].day);
        if ((continentVal == 'all' || continentVal == data[i].continentExp) &&
            (countryVal == 'all' || countryVal == data[i].countriesAndTerritories) &&
            (dateBeg <= entryDate) && (entryDate <= dateEnd))
        {
            if (searchVal) {
                if (data[i].countriesAndTerritories.search(new RegExp(searchVal, "i")) != -1) {
                    newStats.appendChild(createRow(data[i]));
                }
            }
            else {
                newStats.appendChild(createRow(data[i]));
            }
        }
    }

};

function createOption(txt) {
    let opt = document.createElement('option');
    opt.innerHTML = txt.replace(/\_/g, ' ');
    opt.value = txt;

    return opt;
}

function createRow(info) {
    // Generate fields
    let date = document.createElement('td');
    let country = document.createElement('td');
    let cases = document.createElement('td');
    let deaths = document.createElement('td');
    let cumulative = document.createElement('td');
    date.innerHTML = info.day + '/' + info.month + '/' + info.year;
    country.innerHTML = info.countriesAndTerritories.replace(/\_/g, ' ');
    cases.innerHTML = info.cases;
    deaths.innerHTML = info.deaths;
    cumulative.innerHTML = info['Cumulative_number_for_14_days_of_COVID-19_cases_per_100000'];

    // Create row
    let row = document.createElement('tr');
    row.appendChild(date);
    row.appendChild(country);
    row.appendChild(cases);
    row.appendChild(deaths);
    row.appendChild(cumulative);

    return row;
}