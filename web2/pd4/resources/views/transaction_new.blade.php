<!DOCTYPE html>
<html>
<head>
    <title>New transaction</title>
</head>
<body>
    <p>Add a transaction for <b>{{ $city->city_name }}</b>:</p>
    <form method="POST" action="{{ action([App\Http\Controllers\TransactionController::class, 'store']) }}">
        @csrf
        <input type="hidden" name="city_id" value="{{ $city->id }}">
        <label for="account1">Account 1: </label>
        <input type="text" name="account1" id="account1" required>
        <label for="account2">Account 2: </label>
        <input type="text" name="account2" id="account2" required>
        <label for="amount">Amount: </label>
        <input type="number" name="amount" id="amount" required>
        <input type="submit" value="add">
    </form>
</body>
</html>
