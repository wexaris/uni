<?php

namespace App\Http\Controllers;

use App\Models\Book;
use Illuminate\Http\Request;

class CartController extends Controller
{
    public function addOrRemoveFromCart(Request $request) 
    {
        if (session()->has('books') && in_array($request->id, session()->get('books'))) { // if book is already in the cart, remove book from cart
            $books = session()->pull('books');
            unset($books[array_search($request->id, $books)]);
            session()->put('books', $books);
        }        
        else // add a book to cart
            session()->push('books', $request->id);

        return response()->json(session()->get('books'), 200);
    }   
    
    public function showCart() 
    {
        if (session()->has('books')) {
            $books = Book::whereIn('id', session()->get('books'))->get();
            return view('cart', compact('books'));
        }
        else
            return view('cart');            
    }    
}
