<?php

namespace Database\Seeders;

use Illuminate\Database\Seeder;
use Illuminate\Support\Facades\DB;
use App\Models\City;
use App\Models\Country;
use App\Models\Transaction;

class DatabaseSeeder extends Seeder
{
    /**
     * Seed the application's database.
     *
     * @return void
     */
    public function run()
    {
        DB::statement('SET FOREIGN_KEY_CHECKS=0;');
        City::truncate();
        Country::truncate();

        DB::table('countries')->insert([
            'country_name' => 'Latvia',
            'country_code' => 'LV',
        ]);

        $country = new Country();
        $country->country_name = 'Finland';
        $country->country_code = 'FI';
        $country->save();

        $country = Country::create(['country_name' => 'Germany', 'country_code' => 'DE']);

        $country = Country::where('country_name', 'Latvia')->first();
        $country->cities()->create(['city_name' => 'Riga']);

        $transaction = new Transaction();
        $transaction->account1_number = '1234567812345678';
        $transaction->account2_number = '8765432187654321';
        $transaction->amount = 10.20;
        $country->cities()->first()->transactions()->save($transaction);

        $city = new City();
        $city->city_name = 'Helsinki';
        $country = Country::where('country_name', 'Finland')->first();
        $country->cities()->save($city);

        $country = Country::where('country_name', 'Germany')->first();
        $city = new City();
        $city->city_name = 'Berlin';
        $city->country()->associate($country);
        $city->save();

        DB::statement('SET FOREIGN_KEY_CHECKS=1;');
    }
}
