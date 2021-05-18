<x-app-layout>
    <x-slot name="header">
        <h2 class="font-semibold text-xl text-gray-800 leading-tight">
            Cart
        </h2>
    </x-slot>

    <div class="py-12">
        <div class="max-w-7xl mx-auto sm:px-6 lg:px-8">
            <div class="bg-white overflow-hidden shadow-sm sm:rounded-lg">
                <div id="booklist" class="p-6 bg-white border-b border-gray-200">
                @isset($books)
                @foreach ($books as $book)
                    <p class='text-lg' book-id="{{$book->id}}">
                        <a href="{{ url('book', $book->id) }}">{{ $book->title }} {{ $book->year }}</a>
                        <x-button class="btn-reserve my-2" book-id="{{ $book->id }}">
                            Unreserve
                        </x-button>
                    </p>

                    <form class="mb-5" method="POST" action="{{ action([App\Http\Controllers\BorrowedBookController::class, 'store']) }}">
                        @csrf

                        <div class="flex items-center">
                            <!-- Borrow Date -->
                            <div class="inline">
                                <x-label class="inline" for="borrow_date" value="Borrow Date"/>
                                <x-input id="borrow_date" class="mt-1" type="date" name="borrow_date" required autofocus :value="old('borrow_date')"/>
                            </div>

                            <!-- Return Date -->
                            <div class="inline ml-4">
                                <x-label class="inline" for="return_date" value="Return Date"/>
                                <x-input id="return_date" class="mt-1" type="date" name="return_date" required autofocus :value="old('return_date')"/>
                            </div>

                            <!-- Book ID -->
                            <x-input type="hidden" id="book_id" name="book_id" value="{{ $book->id }}"/>

                            <x-button class="ml-4">
                                Borrow
                            </x-button>
                        </div>

                        <x-validation-error class="mb-4" :errors="$errors" title="borrow_date"/>
                        <x-validation-error class="mb-4" :errors="$errors" title="return_date"/>
                    </form>
                @endforeach
                @endisset
                </div>
            </div>
        </div>
    </div>
    <script>
$(document).ready(function () {
    checkBookCount();

    function checkBookCount() {
        if (!$('p[book-id]').length) {
            $('#booklist').text('There are no books reserved!');
        }
    }

    $(".btn-reserve").on('click', function (e) {
        var url = "{{ route('books.reserve') }}";
        var CSRF_TOKEN = $('meta[name="csrf-token"]').attr('content');
        var btn = $(this);
        $.ajax({
            type: "POST",
            url: url,
            data: { id: btn.attr('book-id'), _token: CSRF_TOKEN },
            success: function (data) {
               btn.closest('p').remove();
               checkBookCount();
            },
            error: function (data) {
                console.log('Error:', data);
            }
        });
    })
});
    </script>
</x-app-layout>
