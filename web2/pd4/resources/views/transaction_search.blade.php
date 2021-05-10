<!DOCTYPE html>
<html>
<head>
    <title>Transactions</title>
</head>
<body>
    @if (count($transactions) == 0)
        <p color='red'> There are no transactions in the database!</p>
    @else
        <table border="1" style="text-align: center">
            <tr>
                <td>Transaction Id</td>
                <td>Country</td>
                <td>City</td>
                <td>Account 1</td>
                <td>Account 2</td>
                <td>Amount</td>
                <td></td>
                <td></td>
            </tr>
            @foreach ($transactions as $trans)
                <tr>
                    <td>{{ $trans->id }}</td>
                    <td>{{ $trans->city->country->country_name }}</td>
                    <td>{{ $trans->city->city_name }}</td>
                    <td>{{ $trans->account1_number }}</td>
                    <td>{{ $trans->account2_number }}</td>
                    <td>{{ $trans->amount }}</td>
                    <td>
                        <form method="GET" action="{{ action([App\Http\Controllers\TransactionController::class, 'edit'], $trans->id) }}">
                            @csrf
                            @method('EDIT')
                            <input type="submit" value="edit">
                        </form>
                    </td>
                    <td>
                        <form method="POST" action="{{ action([App\Http\Controllers\TransactionController::class, 'destroy'], $trans->id) }}">
                            @csrf
                            @method('DELETE')
                            <input type="submit" value="delete">
                        </form>
                    </td>
                </tr>
            @endforeach
        </table>
    @endif
</body>
</html>