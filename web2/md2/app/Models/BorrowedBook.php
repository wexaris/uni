<?php

namespace App\Models;

use Illuminate\Database\Eloquent\Factories\HasFactory;
use Illuminate\Database\Eloquent\Model;
use App\Models\Book;
use App\Models\User;

class BorrowedBook extends Model
{
    use HasFactory;

    protected $table = 'borrowed_books';

    public function book() { // FK relationship
        return $this->belongsTo(Book::class);
    }

    public function user() { // FK relationship
        return $this->belongsTo(User::class);
    }
}
