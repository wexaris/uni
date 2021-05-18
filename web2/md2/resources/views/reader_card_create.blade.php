<x-app-layout>
    <x-slot name="header">
        <h2 class="font-semibold text-xl text-gray-800 leading-tight">
            {{ __('ReaderCard') }}
        </h2>
    </x-slot>

    <x-form>
    <form method="POST" action="{{ action([App\Http\Controllers\ReaderCardController::class, 'store']) }}">
        @csrf

        <!-- Name -->
        <div>
            <x-label for="name" value="Name" />
            <x-input id="name" class="block mt-1 w-full" type="text" name="name" required autofocus :value="old('name')"/>
            <x-validation-error class="mb-4" :errors="$errors" title="name"/>
        </div>

        <!-- Surname -->
        <div>
            <x-label for="surname" value="Surname" />
            <x-input id="surname" class="block mt-1 w-full" type="text" name="surname" required :value="old('surname')"/>
            <x-validation-error class="mb-4" :errors="$errors" title="surname"/>
        </div>

        <!-- Student ID -->
        <div>
            <x-label for="student_id" value="Student ID" />
            <x-input id="student_id" class="block mt-1 w-full" type="text" name="student_id" required :value="old('student_id')"/>
            <x-validation-error class="mb-4" :errors="$errors" title="student_id"/>
        </div>

        <!-- Faculty -->
        <div>
            <x-label for="faculty" value="Faculty" />
            <x-input id="faculty" class="block mt-1 w-full" type="text" name="faculty" required :value="old('faculty')"/>
            <x-validation-error class="mb-4" :errors="$errors" title="faculty"/>
        </div>

        <!-- Address -->
        <div>
            <x-label for="address" value="Address" />
            <x-input id="address" class="block mt-1 w-full" type="text" name="address" required :value="old('address')"/>
            <x-validation-error class="mb-4" :errors="$errors" title="address"/>
        </div>

        <!-- Phone number -->
        <div>
            <x-label for="phone" value="Phone" />
            <x-input id="phone" class="block mt-1 w-full" type="number" name="phone" required :value="old('phone')"/>
            <x-validation-error class="mb-4" :errors="$errors" title="phone"/>
        </div>

        <div class="flex items-center justify-end mt-4">
            <x-button class="ml-4">
                Create
            </x-button>
        </div>
    </form>
    </x-form>
</x-app-layout>