/*******************************************
Rainers Vorza, rv20039
D9. Izveidot klasi "Skaitļu steks", kurā glabājas masīvs ar skaitliskām
vērtībām (int) garumā 5 un steka elementu skaits. Klasei izveidot šādas metodes:
(1) konstruktors,
(2) destruktors, kurš paziņo par objekta likvidēšanu un likvidēto elementu skaitu (ja likvidēšanas brīdī steks nav tukšs),
(3) metode "Push", kas pievieno stekam elementu, ja tas nav pilns,
(4) metode "Pop", kas izņem no steka augšējo elementu un atgriež tā vērtību,
(5) metode "Count", kas atgriež elementu skaitu stekā,
(6) metode "Top", kas atgriež augšējā elementa vērtību,
(7) metode "IsEmpty", kas noskaidro, vai steks ir tukšs,
(8) metode "IsFull", kas noskaidro, vai steks ir pilns.
Pirms uzdevuma veikšanas precīzi noskaidrot, ko nozīmē jēdziens steks (stack).
Programma izveidota: 18/11/2020
*******************************************/

#include <iostream>
#include <assert.h>
#include "IntStack.h"

// Pateicoties tam, ka no lietotaja nekas nav jāprasa,
// `main` funkcija pati veic nepieciešamos testus.
// Rezultātā, ja viss strāda pareizi, programmai vajadzētu izprintēt
// tikai steka iznēcināšanas ziņu, kad tā beidz darbu.
int main() {
    IntStack stack;

    assert(stack.IsEmpty());
    assert(!stack.IsFull());

    stack.Push(5);
    assert(stack.Top() == 5);
    stack.Push(10);
    stack.Push(15);
    stack.Push(20);
    stack.Push(25);
    assert(!stack.IsEmpty());
    assert(stack.IsFull());

    assert(stack.Top() == 25);
    assert(stack.Pop() == 25);
    assert(stack.Top() == 20);
    assert(!stack.IsEmpty());
    assert(!stack.IsFull());

    stack.Pop();
    stack.Pop();
    stack.Pop();
    stack.Pop();
    assert(stack.IsEmpty());
    assert(!stack.IsFull());


    // Notiks steka iznīcināšana
}