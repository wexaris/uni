/*******************************************
Rainers Vorza, rv20039

Programma izveidota: 2021/04/08
*******************************************/

#pragma once
#include <iostream>
#include "forward_list.hpp"

// Dereference templated pointer types
template<typename T> T& val(T* obj) { return *obj; } // pointer -> reference
template<typename T> T& val(T& obj) { return obj;  } // reference

// Create a new list from the given one, but without any duplicate values
template<typename Type>
ForwardList<Type> copy_without_duplicates(const ForwardList<Type>& list) {
    ForwardList<Type> new_list;
    auto iter = new_list.cbefore_begin();

    for (const auto& item : list) {
        // Check if already exists
        for (const auto& added : new_list)
            if (val(item) == val(added))
                goto next;

        // Insert value into new list
        iter = new_list.insert_after(iter, Type(item));
next:;
    }

    return new_list;
}

// Print the elements of any ForwardList
template<typename Type>
void print(const ForwardList<Type>& cont) {
    for (const auto& item : cont)
        std::cout << val(item) << " ";
    std::cout << std::endl;
}
