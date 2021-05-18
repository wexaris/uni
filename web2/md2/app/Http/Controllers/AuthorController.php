<?php

namespace App\Http\Controllers;

use App\Models\Author;
use Illuminate\Validation\Rule;
use Illuminate\Http\Request;
use function view;

class AuthorController extends Controller
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
        $authors = Author::orderBy('last_name')->get();
        return view('authors',  compact('authors'));
    }

    /**
     * Show the form for creating a new author.
     *
     * @return \Illuminate\Http\Response
     */
    public function create()
    {
        return view('author_create');
    }

    /**
     * Store a newly created author in the database.
     *
     * @param  \Illuminate\Http\Request  $request
     * @return \Illuminate\Http\Response
     */
    public function store(Request $request)
    {
        $last_name = $request->last_name;
        $rules = array(
            'first_name' => [
                'required', 
                'string', 
                'min:2', 
                'max:50',
                Rule::unique('authors', 'first_name')->where(function ($query) use ($last_name) {
                    return $query->where('last_name', $last_name);
                })],
            'last_name' => 'required|string|min:2|max:50',
            'country' => 'nullable|string',
        );        
        $this->validate($request, $rules); 

        $author = new Author();
        $author->first_name = $request->first_name;
        $author->last_name = $request->last_name;
        $author->country = $request->country;
        $author->save();        
        return redirect()->route('author.index');
    }

    /**
     * Display the specified resource.
     *
     * @param  int  $id
     * @return \Illuminate\Http\Response
     */
    public function show($id)
    {
        $author = Author::findOrFail($id);
        $books = $author->books;
        return view('books', compact('books', 'author'));
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
}
