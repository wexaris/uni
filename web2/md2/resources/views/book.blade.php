<x-app-layout>
    <x-slot name="header">
        <h2 class="font-semibold text-xl text-gray-800 leading-tight">
            {{ __('Book info') }}
        </h2>
    </x-slot>

    <div class="py-12">
        <div class="max-w-7xl mx-auto sm:px-6 lg:px-8">
            <div class="bg-white overflow-hidden shadow-sm sm:rounded-lg">
                <div class="p-6 bg-white border-b border-gray-200">
                <p class='font-semibold text-xl'>{{ $book->title }}</p>
                <p class='text-lg'><strong class='font-semibold'>Genre:</strong> <a href="{{ url('genre', $book->genre->id) }}">{{ $book->genre->name}}</a></p>
                <p class='text-lg'><strong class='font-semibold'>Year:</strong> {{ $book->year }}</p>
                @isset($book->abstract)
                <p class='text-lg'><strong class='font-semibold'>Abstract:</strong> {{ $book->abstract }}</p>
                @endisset
                @if (count($book->authors) > 1)
                <p class='text-lg'><strong class='font-semibold'>Authors:</strong> 
                @else    
                <p class='text-lg'><strong class='font-semibold'>Author:</strong> 
                @endif
                @foreach ($book->authors as $author)
                    <a href="{{ url('author', $author->id) }}">{{ $author->first_name }} {{ $author->last_name }} @isset($author->country) ({{ $author->country }}) @endisset</a>
                @endforeach
                </p>
                
                <x-button id="btn-reserve" book-id="{{ $book->id }}">
                    @if ($reserved == 0)
                    Reserve
                    @else
                    Unreserve
                    @endif
                </x-button>
            </div>
        </div>
    </div>
        
    <script>
$(document).ready(function () {
    $("#btn-reserve").on('click', function (e) {
        var url = "{{ route('books.reserve') }}";
        var CSRF_TOKEN = $('meta[name="csrf-token"]').attr('content');
        $.ajax({
            type: "POST",
            url: url,
            data: { id: $(e.target).attr('book-id'), _token: CSRF_TOKEN },
            success: function (data) {
                if ($("#btn-reserve").text().trim() == "Reserve")
                    $("#btn-reserve").text("Unreserve");
                else
                    $("#btn-reserve").text("Reserve");
            },
            error: function (data) {
                console.log('Error:', data);
            }
        });
    })
});        
    </script>        
</x-app-layout>
