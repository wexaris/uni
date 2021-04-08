#pragma once

#include <iostream>

// Dereference pointers
template<typename T> T& val(T* obj) { return *obj; } // pointer -> reference
template<typename T> T& val(T& obj) { return obj;  } // reference

// Print the elements of any iterable container
template<template<typename> class Cont, typename Type>
void print(const Cont<Type>& cont) {
    for (const auto& item : cont)
        std::cout << val(item) << " ";
    std::cout << std::endl;
}

// Print the elements of any iterable container
template<template<typename, class> class Cont, typename Type, class Alloc>
void print(const Cont<Type, Alloc>& cont) {
    for (const auto& item : cont)
        std::cout << val(item) << " ";
    std::cout << std::endl;
}
