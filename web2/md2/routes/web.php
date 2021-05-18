<?php

use App\Http\Controllers\AuthorController;
use App\Http\Controllers\BookController;
use App\Http\Controllers\BorrowedBookController;
use App\Http\Controllers\CartController;
use App\Http\Controllers\GenreController;
use App\Http\Controllers\ReaderCardController;
use Illuminate\Support\Facades\Route;

/*
|--------------------------------------------------------------------------
| Web Routes
|--------------------------------------------------------------------------
|
| Here is where you can register web routes for your application. These
| routes are loaded by the RouteServiceProvider within a group which
| contains the "web" middleware group. Now create something great!
|
*/

Route::get('/', function () {
    return view('dashboard');
})->middleware(['auth'])->name('dashboard');

require __DIR__.'/auth.php';

Route::get('/dashboard', function () {
    return view('dashboard');
})->middleware(['auth'])->name('dashboard');

Route::resource('genre', GenreController::class);
Route::resource('author', AuthorController::class);
Route::resource('book', BookController::class);
Route::resource('borrowed', BorrowedBookController::class);
Route::resource('card', ReaderCardController::class);

Route::get('books/filter', [BookController::class, 'showFilter'])->name('books.filter');
Route::post('books/filter', [BookController::class, 'filter']);

Route::post('books/reserve', [CartController::class, 'addOrRemoveFromCart'])->name('books.reserve');
Route::get('books/reserve', [CartController::class, 'showCart'])->name('cart.show');
