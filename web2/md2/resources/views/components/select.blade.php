@props(['list', 'disabled' => false])
<select {{ $disabled ? 'disabled' : '' }} {!! $attributes->merge(['class' => '']) !!}>
    @foreach ($list as $item) 
       <option value='{{$item->value}}'>{{$item->name}}</option>
    @endforeach
</select>
