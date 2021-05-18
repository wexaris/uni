@props(['errors', 'title'])

@error($title)
<div {{ $attributes }}>
    <span class="text-red-600" role="alert">
    <strong>{{ $message }}</strong>
    </span>
</div>
@enderror
