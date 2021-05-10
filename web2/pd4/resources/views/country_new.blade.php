<!DOCTYPE html>
<html>
<head>
    <title>New country</title>
</head>
<body>
    <p>Add a country:</p>
    <form method="POST" action="{{ action([App\Http\Controllers\CountryController::class, 'store']) }}">
        @csrf
        <label for="country_name">Country Name: </label>
        <input type="text" name="country_name" id="country_name">
        <label for="country_code">Country Code: </label>
        <input type="text" name="country_code" id="country_code">
        <input type="submit" value="add">
    </form>
</body>
</html>
