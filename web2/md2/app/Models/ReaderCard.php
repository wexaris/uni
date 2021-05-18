<?php

namespace App\Models;

use Illuminate\Database\Eloquent\Factories\HasFactory;
use Illuminate\Database\Eloquent\Model;
use App\Models\User;

class ReaderCard extends Model
{
    use HasFactory;

    protected $table = 'reader_cards';

    public function user() { // FK relationship
        return $this->belongsTo(User::class);
    }
}
