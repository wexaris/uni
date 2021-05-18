<x-app-layout>
    <x-slot name="header">
        <h2 class="font-semibold text-xl text-gray-800 leading-tight">
            Create a new genre
        </h2>
    </x-slot>
    
    <x-form>
    <form method="POST" action="{{ action([App\Http\Controllers\GenreController::class, 'store']) }}">
        @csrf

        <!-- Name -->
        <div>
            <x-label for="name" value="Name" />

            <x-input id="name" class="block mt-1 w-full" type="text" name="name" required autofocus :value="old('name')"/>
            
            <x-validation-error class="mb-4" :errors="$errors" title="name"/>          
        </div>

        <div class="flex items-center justify-end mt-4">
            <x-button class="ml-4">
                Create
            </x-button>
        </div>
    </form>
    </x-form>
</x-app-layout>
