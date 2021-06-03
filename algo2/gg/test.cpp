/*******************************************
Rainers Vorza, rv20039

GG – STL list un saistītais saraksts ar izņēmumsituāciju apstrādi un vienībtestēšanu**.

* atrisināt uzdevumu G divos veidos:
  a) izmantojot dinamiskas datu struktūras (saistīto sarakstu vtml.),
  b) izmantojot STL::list konteineru.

** tas pats uzdevums, kas G, bet tā risinājums (a) jāpapildina ar divām lietām:
  1) vismaz viena no datu pārbaudēm jārealizē, izmantojot izņēmumsituāciju apstrādes
     (exception handling) mehānismu,
  2) vismaz viena funkcija (vēlams, galvenā) ir jānotestē, izmantojot vienībtestēšanu,
     kur attiecīgā funkcija būtu jāpārbauda uz vismaz trīs dažādiem nosacījumiem;
     šim nolūkam, kā minimums, ir nepieciešams:
        (1) šo funkciju iznest ārā citā failā (nekā funkcija main),
        (2) izveidot otru projektu speciāli šīs funkcijās testēšanai
            (tātad, kopā būs divi projekti, parastais, kas izmantos funkciju, otrais, kas testēs).

Papildus norāde: šādam vienībtestēšanas projektam daļēji atbilst iepriekšējā
semestra pēdējais laboratorijas darbs (ar klasēm) ar cieti iekodētu main funkciju.

Programma izveidota: 2021/06/01
*******************************************/

#include <iostream>
#include "forward_list.hpp"

static size_t error_count = 0;

#define ASSERT(x, msg) { if ((x)) {} else { ++error_count; throw std::runtime_error(msg); } }
#define SHOULD_THROW(x, msg) { try { x; throw std::runtime_error(msg); } catch (const std::exception&) {} }

void test_iter() {
    ForwardList<int> list;
    auto root1 = list.cbefore_begin();
    auto root2 = list.cbefore_begin();
    auto iter = list.cbefore_begin();

    ASSERT(list.cbegin() == list.cend(), "Iterator not at end of empty list!");

    ASSERT(root1.node(), "Iterator node missing!");
    ASSERT(++root1 == list.cend(), "Iterator not at end of empty list!");

    iter = list.insert_after(iter, 1);

    ASSERT(*iter == 1, "Iterator doesn't point to new element!");

    ASSERT(root2.node(), "Iterator node missing!");
    ASSERT(++root2 != list.cend(), "Iterator can't reach new element!");
    ASSERT(iter.node(), "Iterator node missing!");
    ASSERT(++iter == list.cend(), "Iterator can't reach end of list!");

    SHOULD_THROW(*iter, "Accessed out-of-bounds element!");
    SHOULD_THROW(iter++, "Accessed out-of-bounds element!");
}

void test_insert() {
    ForwardList<int> list;
    auto iter = list.cbefore_begin();

    SHOULD_THROW(list.front(), "Accessed first element of empty list!");

    iter = list.insert_after(iter, 1);
    iter = list.insert_after(iter, 2);

    ASSERT(list.front() == 1, "First element of list incorrect!");
    ASSERT(*iter == 2, "Iterator doesn't point to new element");

    list.push_front(3);
    ASSERT(list.front() == 3, "Pushed element isn't at the front!");
}

void test_erase() {
    ForwardList<int> list;
    auto iter = list.cbefore_begin();

    iter = list.insert_after(iter, 1);
    iter = list.insert_after(iter, 2);

    list.erase_after(list.cbegin());

    ASSERT(list.before_begin() != list.end(), "Root missing after everything after first erased!")
    ASSERT(*list.begin() == 1, "Incorrect first value after everything after first erased!")
    ASSERT(list.front() == 1, "Incorrect first value after everything after first erased!")

    list.erase_after(list.cbefore_begin());

    ASSERT(list.before_begin() != list.end(), "Root missing after everything erased!")
    ASSERT(list.begin() == list.end(), "First element exists after everything erased!")
    SHOULD_THROW(list.front(), "Accessed first element after everything erased!");
}

void test_swap() {
    ForwardList<int> list1;
    auto iter1 = list1.cbefore_begin();
    iter1 = list1.insert_after(iter1, 1);
    iter1 = list1.insert_after(iter1, 2);
    iter1 = list1.insert_after(iter1, 3);

    ForwardList<int> list2;
    auto iter2 = list2.cbefore_begin();
    iter2 = list2.insert_after(iter2, 7);
    iter2 = list2.insert_after(iter2, 8);
    iter2 = list2.insert_after(iter2, 9);

    list1.swap(list2);

    iter1 = list1.cbegin();
    ASSERT(*iter1++ ==  7, "Incorrect swap!")
    ASSERT(*iter1++ ==  8, "Incorrect swap!")
    ASSERT(*iter1++ ==  9, "Incorrect swap!")
    ASSERT(iter1 == list1.cend(), "Last iterator value isn't end!")
    SHOULD_THROW(*iter1, "Accessed out-of-bounds element!");

    iter2 = list2.cbegin();
    ASSERT(*iter2++ ==  1, "Incorrect swap!")
    ASSERT(*iter2++ ==  2, "Incorrect swap!")
    ASSERT(*iter2++ ==  3, "Incorrect swap!")
    ASSERT(iter2 == list2.cend(), "Last iterator value isn't end!")
    SHOULD_THROW(*iter1, "Accessed out-of-bounds element!");
}

void test_size() {
    ForwardList<int> list;

    ASSERT(list.size() == 0, "Incorrect initial size!")

    auto iter = list.cbefore_begin();
    iter = list.insert_after(iter, 1);
    iter = list.insert_after(iter, 2);

    ASSERT(list.size() == 2, "Incorrect size after insertion!")

    list.erase_after(list.cbegin());

    ASSERT(list.size() == 1, "Incorrect size after everything after first erased!")

    list.erase_after(list.cbefore_begin());

    ASSERT(list.size() == 0, "Incorrect size after everything erased!")
}

void test_clear() {
    ForwardList<int> list;
    auto iter = list.cbefore_begin();
    iter = list.insert_after(iter, 1);
    iter = list.insert_after(iter, 2);

    list.clear();

    ASSERT(list.before_begin() != list.end(), "Root missing after clear!")
    ASSERT(list.begin() == list.end(), "First element not empty after clear!")
    ASSERT(list.size() == 0, "Incorrect size after clear!")
    SHOULD_THROW(list.front(), "Accessed first element after everything erased!");
}


#define RUN_TEST(testname) try { testname(); } catch(const std::exception& e) \
    { std::cerr << "TEST " << #testname << " FAILED: " << e.what() << std::endl; }

int main() {
    error_count = 0;

    RUN_TEST(test_iter);
    RUN_TEST(test_insert);
    RUN_TEST(test_erase);
    RUN_TEST(test_swap);
    RUN_TEST(test_size);
    RUN_TEST(test_clear);

    if (error_count > 0)
        std::cout << "\nTests failed because of " << error_count << " errors!" << std::endl;
    else
        std::cout << "Tests complete!" << std::endl;
}
