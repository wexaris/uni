<?php

namespace App\Models;

use Illuminate\Database\Eloquent\Factories\HasFactory;
use Illuminate\Database\Eloquent\Model;
use App\Models\Book;

class Author extends Model
{
    use HasFactory;
    
    /**
     * Get the books authored by this author. Many-to-many relationship.
     */    
    public function books()
    {
        return $this->belongsToMany(Book::class, 'books_by_author');
    }      
}
