<x-app-layout>
    <x-slot name="header">
        <h2 class="font-semibold text-xl text-gray-800 leading-tight">
            Borrowed Books
        </h2>
    </x-slot>

    <div class="py-12">
        <div class="max-w-7xl mx-auto sm:px-6 lg:px-8">
            <div class="bg-white overflow-hidden shadow-sm sm:rounded-lg">
                <div class="p-6 bg-white border-b border-gray-200">
                @foreach ($books as $book)
                    <div class="mb-5">
                        <a href="{{ url('book', $book->id) }}" class='text-lg'>
                            {{ $book->book->title }}
                            {{ $book->book->year }}
                        </a>
                        <div>
                            <p>Borrow: {{ $book->borrow_date }}</p>
                            <p>Return: {{ $book->return_date }}</p>
                        </div>
                    </div>
                @endforeach
                </div>
            </div>
        </div>
    </div>
</x-app-layout>
