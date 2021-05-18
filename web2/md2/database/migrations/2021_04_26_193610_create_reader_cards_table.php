<?php

use Illuminate\Database\Migrations\Migration;
use Illuminate\Database\Schema\Blueprint;
use Illuminate\Support\Facades\Schema;

class CreateReaderCardsTable extends Migration
{
    /**
     * Run the migrations.
     *
     * @return void
     */
    public function up()
    {
        Schema::create('reader_cards', function (Blueprint $table) {
            $table->id();
            $table->timestamps();
            $table->string('name', 32);
            $table->string('surname', 32);
            $table->string('student_id', 10);
            $table->string('faculty');
            $table->string('address');
            $table->string('phone_number', 12);
            $table->foreignId('user_id')->constrained();
        });
    }

    /**
     * Reverse the migrations.
     *
     * @return void
     */
    public function down()
    {
        Schema::dropIfExists('reader_cards');
    }
}
