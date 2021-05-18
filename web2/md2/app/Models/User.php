<?php

namespace App\Models;

use Illuminate\Contracts\Auth\MustVerifyEmail;
use Illuminate\Database\Eloquent\Factories\HasFactory;
use Illuminate\Foundation\Auth\User as Authenticatable;
use Illuminate\Notifications\Notifiable;
use App\Models\BorrowedBook;
use App\Models\ReaderCard;

class User extends Authenticatable
{
    use HasFactory, Notifiable;

    /**
     * The attributes that are mass assignable.
     *
     * @var array
     */
    protected $fillable = [
        'name',
        'email',
        'password',
        'role'
    ];

    /**
     * The attributes that should be hidden for arrays.
     *
     * @var array
     */
    protected $hidden = [
        'password',
        'remember_token',
    ];

    /**
     * The attributes that should be cast to native types.
     *
     * @var array
     */
    protected $casts = [
        'email_verified_at' => 'datetime',
    ];

    // determine if User is admin by checking DB field role (1 is admin)
    public function isAdmin() {
        return ($this->role == 1);
    }

    public function borrowed_books() { // FK relationship
        return $this->hasMany(BorrowedBook::class, 'user_id', 'id');
    }

    public function reader_card() { // FK relationship
        return $this->hasOne(ReaderCard::class, 'user_id', 'id');
    }
}
