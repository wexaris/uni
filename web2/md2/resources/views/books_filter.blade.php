<x-app-layout>
    <x-slot name="header">
        <h2 class="font-semibold text-xl text-gray-800 leading-tight">
            Filter books
        </h2>
    </x-slot>

    <x-form>
    <form method="POST" action="{{ action([App\Http\Controllers\BookController::class, 'filter']) }}">
        @csrf

        <!-- Title -->
        <div>
            <x-label for="title" value="Title or portion of it" />

            <x-input id="title" class="block mt-1 w-full" type="text" name="title" :value="old('title')" autofocus />

            <x-validation-error class="mb-4" :errors="$errors" title="title"/>            
        </div>

        <!-- Year from -->
        <div>
            <x-label for="year_from" value="Year from" />

            <x-input id="year_from" class="block mt-1 w-full" type="number" name="year_from" :value="old('year_from')" />

            <x-validation-error class="mb-4" :errors="$errors" title="year_from"/>            
        </div>

        <!-- Year till -->
        <div>
            <x-label for="year_until" value="Year until" />

            <x-input id="year_until" class="block mt-1 w-full" type="number" name="year_until" :value="old('year_until')" />

            <x-validation-error class="mb-4" :errors="$errors" title="year_until"/>            
        </div>

        <!-- Abstract -->
        <div>
            <x-label for="abstract" value="Abstract or portion of it" />

            <x-textarea id="abstract" class="block mt-1 w-full" type="text" name="abstract" :value="old('abstract')" />

            <x-validation-error class="mb-4" :errors="$errors" title="abstract"/>            
        </div>

        <!-- Author -->
        <div>
            <x-label for="author" value="Author" />
            
            <x-multi-select id="author" class="block mt-1 w-full" name="author[]" :list='$authors' :selected="old('author')" text="Any author"/>

            <x-validation-error class="mb-4" :errors="$errors" title="author"/>            
        </div>
        
        <!-- Genre -->
        <div>
            <x-label for="genre" value="Genre" />
            
            <x-multi-select id="genre" class="block mt-1 w-full" name="genre[]" :list='$genres' :selected="old('genre')" text="Any genre"/>

            <x-validation-error class="mb-4" :errors="$errors" title="genre"/>            
        </div>
        
        <div class="flex items-center justify-end mt-4">
            <x-button class="ml-4">
                Filter
            </x-button>
        </div>
    </form>
    </x-form>
</x-app-layout>
