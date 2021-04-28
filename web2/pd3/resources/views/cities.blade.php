<!DOCTYPE html>
<html>
<head>
    <title>Cities</title>
</head>
<body>
    @if (count($cities) == 0)
        <p color='red'> There is no city in the database!</p>
    @else
        <table border="1">
            <tr>
                <td>City Id</td>
                <td>City Name</td>
                <td>Country Id</td>
                <td></td>
            </tr>
            @foreach ($cities as $city)
                <tr>
                    <td>{{ $city->id }}</td>
                    <td>{{ $city->city_name }}</td>
                    <td>{{ $city->country_id }}</td>
                    <td>
                        <input type="button" value="transactions" onclick="showTransactions({{ $city->id }})">
                        <form method="POST" action="{{ action([App\Http\Controllers\CityController::class, 'destroy'], $city->id) }}">
                            @csrf
                            @method('DELETE')
                            <input type="submit" value="delete">
                        </form>
                    </td>
                </tr>
            @endforeach
        </table>
    @endif
    <p><input type="button" value="New City" onclick="newCity({{ $country_id }})"></p>
    <script>
        function showTransactions(cityID) {
            window.location.href = "/transaction/city/" + cityID;
        }
        function newCity(countryID) {
            window.location.href = "/city/country/" + countryID + "/create";
        }
    </script>
</body>
</html>