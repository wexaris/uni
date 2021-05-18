<x-app-layout>
    <x-slot name="header">
        <h2 class="font-semibold text-xl text-gray-800 leading-tight">
            {{ __('Authors') }}
        </h2>
    </x-slot>

    <div class="py-12">
        <div class="max-w-7xl mx-auto sm:px-6 lg:px-8">
            <div class="bg-white overflow-hidden shadow-sm sm:rounded-lg">
                <div class="p-6 bg-white border-b border-gray-200">
                @foreach ( $authors as $author )
                    <p class='text-lg'>
                        <a href="{{ url('author', $author->id) }}">
                            {{ $author->first_name }} {{ $author->last_name }} @isset($author->country) ({{ $author->country }}) @endisset
                        </a>
                    </p>
                @endforeach
                                
                @can('is-admin')
                <x-nav-link :href="route('author.create')">
                    Create new
                </x-nav-link>
                @endcan
                
                </div>
            </div>
        </div>
    </div>
</x-app-layout>
