<?php

namespace App\Http\Controllers;

use Illuminate\Http\Request;
use Illuminate\Support\Facades\Auth;
use Illuminate\Support\Facades\Validator;
use App\Models\ReaderCard;
use App\Models\User;

class ReaderCardController extends Controller
{
    public function __construct() {
        // only authenticated users have access to the methods of the controller
        $this->middleware('auth');
    }

    public function index()
    {
        $card = Auth::user()->reader_card;

        if (!$card)
            return redirect('card/create');

        return view('reader_card_show', compact('card'));
    }

    /**
     * Show the form for creating a new resource.
     *
     * @return \Illuminate\Http\Response
     */
    public function create()
    {
        if (Auth::user()->reader_card)
            return redirect('card');

        return view('reader_card_create');
    }

    /**
     * Store a newly created resource in storage.
     *
     * @param  \Illuminate\Http\Request  $request
     * @return \Illuminate\Http\Response
     */
    public function store(Request $request)
    {
        $rules = array(
            'name' => 'required|string|min:2|max:32',
            'surname' => 'required|string|min:2|max:32',
            'student_id' => 'required|string|min:6|max:10',
            'faculty' => 'required|string',
            'address' => 'required|string',
            'phone' => 'required|string|min:8|max:12'
        );
        $this->validate($request, $rules);

        $card = new ReaderCard();
        $card->name = $request->name;
        $card->surname = $request->surname;
        $card->student_id = $request->student_id;
        $card->faculty = $request->faculty;
        $card->address = $request->address;
        $card->phone_number = $request->phone;
        $card->user_id = Auth::id();
        $card->save();

        return redirect('card');
    }
}
