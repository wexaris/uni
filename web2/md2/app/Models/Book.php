<?php

namespace App\Models;

use Illuminate\Database\Eloquent\Factories\HasFactory;
use Illuminate\Database\Eloquent\Model;
use App\Models\Genre;
use App\Models\Author;

class Book extends Model
{
    use HasFactory;
    
    /**
     * Get the genre that this book corresponds to.
     */
    public function genre()
    {
        return $this->belongsTo(Genre::class);
    }      

    /**
     * Get the authors that wrote the book. Many-to-many relationship.
     */    
    public function authors()
    {
        return $this->belongsToMany(Author::class, 'books_by_author');
    }     
}
