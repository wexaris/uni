<?php

namespace Database\Seeders;

use App\Models\Genre;
use Illuminate\Database\Seeder;

class GenreSeeder extends Seeder
{
    /**
     * Run the database seeds.
     *
     * @return void
     */
    public function run()
    {
        Genre::truncate();
        Genre::create(['id' => 1, 'name' => 'Novel']);
        Genre::create(['id' => 2, 'name' => 'Study book']);
        Genre::create(['id' => 3, 'name' => 'Cookbook']);
    }
}
