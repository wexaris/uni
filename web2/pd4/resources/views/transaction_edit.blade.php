<!DOCTYPE html>
<html>
<head>
    <title>Edit transaction</title>
</head>
<body>
    <p>Edit transaction:</p>
    <form method="PUT" action="{{ action([App\Http\Controllers\TransactionController::class, 'update'], $trans->id) }}">
        @csrf
        <input type="hidden" name="trans_id" value="{{ $trans->id }}">
        <label for="account1">Account 1: </label>
        <input type="text" name="account1" id="account1" value="{{ $trans->account1_number }}" required>
        <label for="account2">Account 2: </label>
        <input type="text" name="account2" id="account2" value="{{ $trans->account2_number }}" required>
        <label for="amount">Amount: </label>
        <input type="numeric" name="amount" id="amount" value="{{ $trans->amount }}" required>
        <input type="submit" value="update">
    </form>

    @if (count($errors) > 0)
    <div class = "alert alert-danger">
       <ul>
          @foreach ($errors->all() as $error)
             <li>{{ $error }}</li>
          @endforeach
       </ul>
    </div>
@endif
</body>
</html>
