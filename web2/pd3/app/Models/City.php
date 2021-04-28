<?php

namespace App\Models;

use Illuminate\Database\Eloquent\Factories\HasFactory;
use Illuminate\Database\Eloquent\Model;
// Country model usage
use App\Models\Country;
// Transaction model usage
use App\Models\Transaction;

class City extends Model
{
    use HasFactory;

    public function country() { // FK relationship
        return $this->belongsTo(Country::class);
    }

    public function transactions() { // FK relationship
        return $this->hasMany(Transaction::class);
    }
}

