<?php

namespace Database\Seeders;

use App\Models\Book;
use Illuminate\Database\Seeder;
use Illuminate\Support\Facades\DB;

class BookSeeder extends Seeder
{
    /**
     * Run the database seeds.
     *
     * @return void
     */
    public function run()
    {
        Book::truncate();
        Book::create(['id' => 1, 'genre_id' => 1, 'title' => 'Don Quixote', 'year' => 1605, 'abstract' => 'The story of the gentle knight and his servant Sancho Panza has entranced readers for centuries.']);
        Book::create(['id' => 2, 'genre_id' => 1, 'title' => 'Robinson Crusoe', 'year' => 1719, 'abstract' => 'The book is presented as an autobiography of the title character (whose birth name is Robinson Kreutznaer) – a castaway who spends 28 years on a remote tropical desert island near the coasts of Venezuela and Trinidad.']);
        Book::create(['id' => 3, 'genre_id' => 1, 'title' => 'Emma', 'year' => 1815, 'abstract' => 'Near impossible choice between this and Pride and Prejudice. But Emma never fails to fascinate and annoy.']);
        Book::create(['id' => 4, 'genre_id' => 1, 'title' => 'Pride and Prejudice', 'year' => 1813, 'abstract' => 'The novel follows the character development of Elizabeth Bennet, the dynamic protagonist of the book who learns about the repercussions of hasty judgments and comes to appreciate the difference between superficial goodness and actual goodness.']);
        Book::create(['id' => 5, 'genre_id' => 1, 'title' => "Harry Potter and the Philosopher's Stone", 'year' => 1997, 'abstract' => 'The book follows Harry Potter, a young wizard who discovers his magical heritage on his eleventh birthday, when he receives a letter of acceptance to Hogwarts School of Witchcraft and Wizardry.']);
        Book::create(['id' => 6, 'genre_id' => 1, 'title' => 'Harry Potter and the Chamber of Secrets', 'year' => 1998, 'abstract' => "The plot follows Harry's second year at Hogwarts School of Witchcraft and Wizardry."]);
        Book::create(['id' => 7, 'genre_id' => 2, 'title' => 'Learning Angular 3rd edition', 'year' => 2020, 'abstract' => "Uncover Angular's potential for creating enterprise web applications―from setting up the environment to deployment―with the help of expert guidance, step-by-step explanations, and hands-on exercises"]);
        Book::create(['id' => 8, 'genre_id' => 2, 'title' => "Laravel: The Ultimate Beginner's Guide to Learn Laravel Step by Step , 2nd Edition", 'year' => 2020, 'abstract' => 'If you’re looking for a book that can help you to build amazing web applications, this is the book for you! Aimed at people who have some experience with Laravel, this cookbook has your back!']);
        Book::create(['id' => 9, 'genre_id' => 3, 'title' => 'The Ultimate Slow Cooker Cookbook: No-Fuss Recipes for Classic Dishes & New Favorites', 'year' => 2019, 'abstract' => 'There’s a reason slow cookers have been a staple in American homes for more than half a century: with just a few minutes of prep in the morning, you can have a delicious dinner waiting for you when you get home.']);
        Book::create(['id' => 10, 'genre_id' => 3, 'title' => 'The River Cottage Cookbook', 'year' => 2001, 'abstract' => 'First published in the United Kingdom in 2001, THE RIVER COTTAGE COOKBOOK quickly became a hit among food cognoscenti around the world.']);
        
        DB::table('books_by_author')->truncate();
        DB::table('books_by_author')->insert(['book_id' => 1, 'author_id' => 1]);
        DB::table('books_by_author')->insert(['book_id' => 2, 'author_id' => 2]);
        DB::table('books_by_author')->insert(['book_id' => 3, 'author_id' => 3]);
        DB::table('books_by_author')->insert(['book_id' => 4, 'author_id' => 3]);
        DB::table('books_by_author')->insert(['book_id' => 5, 'author_id' => 4]);
        DB::table('books_by_author')->insert(['book_id' => 6, 'author_id' => 4]);
        DB::table('books_by_author')->insert(['book_id' => 7, 'author_id' => 5]);
        DB::table('books_by_author')->insert(['book_id' => 7, 'author_id' => 6]);
        DB::table('books_by_author')->insert(['book_id' => 8, 'author_id' => 7]);
        DB::table('books_by_author')->insert(['book_id' => 9, 'author_id' => 8]);
        DB::table('books_by_author')->insert(['book_id' => 10, 'author_id' => 9]);
    }
}
