<?php

namespace App\Models;

use Illuminate\Database\Eloquent\Factories\HasFactory;
use Illuminate\Database\Eloquent\Model;
// City model usage
use App\Models\City;

class Transaction extends Model
{
    use HasFactory;

    public function city() { // FK relationship
        return $this->belongsTo(City::class);
    }
}
