<?php

namespace Database\Seeders;

use App\Models\Author;
use Illuminate\Database\Seeder;

class AuthorSeeder extends Seeder
{
    /**
     * Run the database seeds.
     *
     * @return void
     */
    public function run()
    {
        Author::truncate();
        Author::create(['id' => 1, 'first_name' => 'Miguel', 'last_name' => 'De Cervantes', 'country' => 'Spain']);
        Author::create(['id' => 2, 'first_name' => 'Daniel', 'last_name' => 'Defoe', 'country' => 'England']);
        Author::create(['id' => 3, 'first_name' => 'Jane', 'last_name' => 'Austen', 'country' => 'England']);
        Author::create(['id' => 4, 'first_name' => 'J. K.', 'last_name' => 'Rowling', 'country' => 'England']);
        Author::create(['id' => 5, 'first_name' => 'Aristeidis', 'last_name' => 'Bampakos']);
        Author::create(['id' => 6, 'first_name' => 'Pablo', 'last_name' => 'Deeleman']);
        Author::create(['id' => 7, 'first_name' => 'Rufus', 'last_name' => 'Steward']);
        Author::create(['id' => 8, 'first_name' => 'Linda', 'last_name' => 'Larsen', 'country' => 'USA']);
        Author::create(['id' => 9, 'first_name' => 'Hugh', 'last_name' => 'Fearnley-Whittingstall', 'country' => 'England']);
    }
}
