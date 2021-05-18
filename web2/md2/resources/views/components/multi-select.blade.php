@props(['list', 'id', 'selected', 'text', 'disabled' => false])
<select multiple id="{{ $id }}" {{ $disabled ? 'disabled' : '' }} {!! $attributes->merge(['class' => '']) !!}>
    @foreach ($list as $item) 
        @if(collect($selected)->contains($item->value))
        <option value='{{$item->value}}' selected>{{$item->name}}</option>
        @else
        <option value='{{$item->value}}'>{{$item->name}}</option>
        @endif
    @endforeach
</select>

<script>
    $(document).ready(function() {
        $('#{{ $id }}').multiselect({
                    nonSelectedText:"{{ $text }}",
                });
    });
</script>