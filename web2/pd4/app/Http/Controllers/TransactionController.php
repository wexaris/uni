<?php

namespace App\Http\Controllers;

use Illuminate\Http\Request;
use App\Models\Country;
use App\Models\City;
use App\Models\Transaction;

use Illuminate\Support\Facades\DB;

class TransactionController extends Controller
{
    public function search(Request $request) {
        $query = $request->get('query');
        $transactions = Transaction::query()
            ->join('cities', 'cities.id', '=', 'transactions.city_id')
            ->join('countries', 'countries.id', '=', 'cities.country_id')
            ->where('transactions.account1_number', '=', $query)
            ->orWhere('transactions.account2_number', '=', $query)
            ->orWhere('transactions.amount', '=', $query)
            ->orWhere('cities.city_name', 'LIKE', $query)
            ->orWhere('countries.country_name', 'LIKE', $query)
            ->orWhere('countries.country_code', '=', $query)
            ->get();

        // Return the search view with the resluts compacted
        return view('transaction_search', compact('transactions'));
    }

    /**
     * Display a listing of the resource.
     *
     * @return \Illuminate\Http\Response
     */
    public function index($id)
    {
        $transactions = Transaction::where('city_id', '=', $id)->get();
        return view('transactions', ['city_id' => $id, 'transactions' => $transactions]);
    }

    /**
     * Show the form for creating a new resource.
     *
     * @return \Illuminate\Http\Response
     */
    public function create($id)
    {
        $city = City::findOrFail($id);
        return view('transaction_new', compact('city'));
    }

    /**
     * Store a newly created resource in storage.
     *
     * @param  \Illuminate\Http\Request  $request
     * @return \Illuminate\Http\Response
     */
    public function store(Request $request)
    {
        $validated = $request->validate([
            'account1' => 'required|max:16|regex:/[a-zA-Z0-9]/',
            'account2' => 'required|max:16|regex:/[a-zA-Z0-9]/',
            'amount' => 'required|numeric|min:0.01'
        ]);

        $trans = new Transaction();
        $trans->account1_number = $request->account1;
        $trans->account2_number = $request->account2;
        $trans->amount = $request->amount;
        $trans->city_id = $request->city_id;
        $trans->save();
        return redirect('transaction/city/' . $trans->city_id);
    }

    /**
     * Display the specified resource.
     *
     * @param  int  $id
     * @return \Illuminate\Http\Response
     */
    public function show($id)
    {
        //
    }

    /**
     * Show the form for editing the specified resource.
     *
     * @param  int  $cityID
     * @param  int  $transID
     * @return \Illuminate\Http\Response
     */
    public function edit($id)
    {
        $trans = Transaction::findOrFail($id);
        return view('transaction_edit', compact('trans'));
    }

    /**
     * Update the specified resource in storage.
     *
     * @param  \Illuminate\Http\Request  $request
     * @param  int  $id
     * @return \Illuminate\Http\Response
     */
    public function update(Request $request, $id)
    {
        $validated = $request->validate([
            'account1' => 'required|max:16|regex:/^[a-zA-Z0-9]*$/',
            'account2' => 'required|max:16|regex:/^[a-zA-Z0-9]*$/',
            'amount' => 'required|numeric|min:0.01'
        ]);

        $trans = Transaction::findOrFail($request->trans_id);
        $trans->account1_number = $request->account1;
        $trans->account2_number = $request->account2;
        $trans->amount = $request->amount;
        $trans->save();
        return redirect('transaction/city/' . $trans->city_id);
    }

    /**
     * Remove the specified resource from storage.
     *
     * @param  int  $id
     * @return \Illuminate\Http\Response
     */
    public function destroy($id)
    {
        $city_id = Transaction::findOrFail($id)->city_id;
        Transaction::findOrFail($id)->delete();
        return redirect('transaction/city/'.$city_id);
    }
}
