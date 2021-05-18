<?php

namespace App\Http\Controllers;

use Illuminate\Http\Request;
use Illuminate\Support\Facades\Auth;
use App\Models\BorrowedBook;

class BorrowedBookController extends Controller
{
    public function __construct() {
        // only authenticated users have access to the methods of the controller
        $this->middleware('auth');
    }

    public function index()
    {
        $books = Auth::user()->borrowed_books;
        return view('borrowed_books', compact('books'));
    }

    /**
     * Store a newly created resource in storage.
     *
     * @param  \Illuminate\Http\Request  $request
     * @return \Illuminate\Http\Response
     */
    public function store(Request $request)
    {
        if (!Auth::user()->reader_card)
            return redirect('card');

        $rules = array(
            'borrow_date' => 'required|date|date_format:Y-m-d',
            'return_date' => 'required|date|date_format:Y-m-d|after:borrow_date',
        );
        $this->validate($request, $rules);

        $book = new BorrowedBook();
        $book->borrow_date = $request->borrow_date;
        $book->return_date = $request->return_date;
        $book->book_id = $request->book_id;
        $book->user_id = Auth::id();
        $book->save();

        return redirect('borrowed');
    }
}
