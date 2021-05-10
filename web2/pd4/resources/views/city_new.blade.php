<!DOCTYPE html>
<html>
<head>
    <title>New city</title>
</head>
<body>
    <p>Add a city for <b>{{ $country->country_name }}</b>:</p>
    <form method="POST" action="{{action([App\Http\Controllers\CityController::class, 'store']) }}">
        @csrf
        <input type="hidden" name="country_id" value="{{ $country->id }}">
        <label for="city_name">City Name: </label>
        <input type="text" name="city_name" id="city_name">
        <input type="submit" value="add">
    </form>
</body>
</html>
