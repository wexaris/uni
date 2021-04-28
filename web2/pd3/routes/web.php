<?php

use Illuminate\Support\Facades\Route;

use App\Http\Controllers\CountryController;
use App\Http\Controllers\CityController;
use App\Http\Controllers\TransactionController;

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

//Route::get('/', function () {
//    return view('welcome');
//});

Route::redirect('/', 'country');

Route::get('city/country/{id}', [CityController::class, 'index']);
Route::get('city/country/{id}/create', [CityController::class, 'create']);

Route::get('transaction/city/{id}', [TransactionController::class, 'index']);
Route::get('transaction/city/{id}/create', [TransactionController::class, 'create']);

Route::resource('country', CountryController::class);
Route::resource('city', CityController::class, ['except' => ['index', 'create']]);
Route::resource('transaction', TransactionController::class, ['except' => ['index', 'create']]);