<?php

namespace Database\Seeders;

use App\Models\User;
use Illuminate\Database\Seeder;
use Illuminate\Support\Facades\Schema;

class DatabaseSeeder extends Seeder
{
    /**
     * Seed the application's database.
     *
     * @return void
     */
    public function run()
    {
        Schema::disableForeignKeyConstraints();
        $this->call(GenreSeeder::class);
        $this->call(AuthorSeeder::class);
        $this->call(BookSeeder::class);
        Schema::enableForeignKeyConstraints();

        // create an admin user with email admin@library.test and password secret
        User::truncate();
        User::create(array('name' => 'Administrator',
                           'email' => 'admin@library.test',
                           'password' => bcrypt('secret'),
                           'role' => 1));
    }
}
