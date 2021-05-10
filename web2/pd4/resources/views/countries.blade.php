<!DOCTYPE html>
<html>
<head>
    <title>Countries</title>
</head>
<body>
    @if (count($countries) == 0)
        <p color='red'> There are no records in the database!</p>
    @else
        <form method="GET" action="transaction/search">
            @csrf
            <label for="query">Search for transactions</label><br>
            <input type="text" name="query" id="query" placeholder="Search...">
            <input type="submit" value="Search">
        </form>
        <br>

        <table border="1" style="text-align: center">
            <tr>
                <td>Country Id</td>
                <td>Country Name</td>
                <td>Country Code</td>
                <td>Cities</td>
                <td></td>
            </tr>
            @foreach ($countries as $country)
                <tr>
                    <td>{{ $country->id }}</td>
                    <td>{{ $country->country_name }}</td>
                    <td>{{ $country->country_code }}</td>
                    <td><input type="button" value="show" onclick="showCities({{ $country->id }})"></td>
                    <td>
                        <form method="POST" action="{{ action([App\Http\Controllers\CountryController::class, 'destroy'], $country->id) }}">
                            @csrf
                            @method('DELETE')
                            <input type="submit" value="delete">
                        </form>
                    </td>
                </tr>
            @endforeach
        </table>
    @endif
    <p><input type="button" value="New Country" onclick="newCountry()"></p>
    <script>
        function showCities(countryID) {
            window.location.href = "/city/country/" + countryID;
        }
        function newCountry() {
            window.location.href = "/country/create";
        }
    </script>
</body>
</html>
