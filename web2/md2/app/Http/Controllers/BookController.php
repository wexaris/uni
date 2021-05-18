<?php

namespace App\Http\Controllers;

use App\Models\Author;
use App\Models\Book;
use App\Models\Genre;
use Illuminate\Http\Request;
use Illuminate\Support\Facades\DB;

class BookController extends Controller
{
    public function __construct() {
        // only Admins have access to the following methods
        $this->middleware('auth.admin')->only(['create', 'store']);
        // only authenticated users have access to the methods of the controller
        $this->middleware('auth');
    }

    /**
     * Display a listing of the resource.
     *
     * @return \Illuminate\Http\Response
     */
    public function index()
    {
        $books = Book::orderBy('title')->get();
        return view('books',  compact('books'));
    }

    /**
     * Show the form for creating a new book.
     *
     * @return \Illuminate\Http\Response
     */
    public function create()
    {
        $list = Author::all()->map(function ($author) {
            $author->name = $author->first_name.' '.$author->last_name;
            $author->value = $author->id;
            return $author;
	   });
        $genres = Genre::all()->map(function ($genre) {
            $genre->value = $genre->id;
            return $genre;
	   });
        return view('book_create', compact('list','genres'));
    }

    /**
     * Store a newly created book in the database.
     *
     * @param  \Illuminate\Http\Request  $request
     * @return \Illuminate\Http\Response
     */
    public function store(Request $request)
    {
        $rules = array(
            'title' => 'required|string|min:2|max:191',
            'year' => 'required|digits:4|integer|max:'.(date('Y')),
            'abstract' => 'nullable|string',
            'genre' => 'required|exists:genres,id',
            'author' => 'required|exists:authors,id',
        );
        $this->validate($request, $rules);

        $book = new Book();
        $book->title = $request->title;
        $book->year = $request->year;
        $book->abstract = $request->abstract;
        $book->genre()->associate(Genre::findOrFail($request->genre));
        $book->save();
        foreach($request->author as $id) {
            $author = Author::findOrFail($id);
            $book->authors()->attach($author);
        }
        return redirect()->route('book.index');
    }

    /**
     * Display the specified resource.
     *
     * @param  int  $id
     * @return \Illuminate\Http\Response
     */
    public function show($id)
    {
        $book = Book::findOrFail($id);
        $reserved = 0;
        if (session()->has('books') && in_array($id, session()->get('books'))) {
            $reserved = 1;
        }
        return view('book', compact('book','reserved'));
    }

    /**
     * Show the form for editing the specified resource.
     *
     * @param  int  $id
     * @return \Illuminate\Http\Response
     */
    public function edit($id)
    {
        //
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
        //
    }

    /**
     * Remove the specified resource from storage.
     *
     * @param  int  $id
     * @return \Illuminate\Http\Response
     */
    public function destroy($id)
    {
        //
    }

    public function showFilter()
    {
        $authors = Author::all()->map(function ($author) {
            $author->name = $author->first_name.' '.$author->last_name;
            $author->value = $author->id;
            return $author;
	   });
        $genres = Genre::all()->map(function ($genre) {
            $genre->value = $genre->id;
            return $genre;
	   });
        return view('books_filter', compact('authors','genres'));
    }

    public function filter(Request $request)
    {
        $rules;

        if ($request->year_from != null) {
            $year_from = $request->year_from;
            $rules = array(
                'title' => 'nullable|string|min:2|max:191',
                'year_from' => 'nullable|digits:4|integer|max:'.(date('Y')),
                'year_until' => 'nullable|digits:4|integer|max:'.date('Y').'|gte:'.$year_from,
                'genre' => 'nullable|exists:genres,id',
                'author' => 'nullable|exists:authors,id',
            );
        }
        else {
            $rules = array(
                'title' => 'nullable|string|min:2|max:191',
                'year_from' => 'nullable|digits:4|integer|max:'.(date('Y')),
                'year_until' => 'nullable|digits:4|integer|max:'.date('Y'),
                'genre' => 'nullable|exists:genres,id',
                'author' => 'nullable|exists:authors,id',
            );
        }

        $this->validate($request, $rules);

        $query = Book::join('books_by_author', 'books_by_author.book_id', '=', 'books.id');
        if ($request->genre != null) {
            $query = $query->whereIn('books.genre_id',$request->genre);
        }

        if ($request->author != null) {
            $query = $query->whereIn('books_by_author.author_id',$request->author);
        }

        if ($request->title != null) {
            $query = $query->where('books.title', 'LIKE', '%'.$request->title.'%');
        }

        if ($request->year_from != null) {
            $query = $query->where('books.year', '>=', $request->year_from);
        }

        if ($request->year_until != null) {
            $query = $query->where('books.year', '<=', $request->year_until);
        }

        if ($request->abstract != null) {
            $query = $query->where('books.abstract', 'LIKE', '%'.$request->abstract.'%');
        }

        $query = $query->select(DB::raw('distinct books.*'));

        return view('books', array('books' => $query->orderBy('title')->get()));
    }
}
