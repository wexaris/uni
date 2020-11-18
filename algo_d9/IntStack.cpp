/*******************************************
Rainers Vorza, rv20039
D9. Izveidot klasi "Skaitļu steks", kurā glabājas masīvs ar skaitliskām
vērtībām (int) garumā 5 un steka elementu skaits. Klasei izveidot šādas metodes:
(1) konstruktors,
(2) destruktors, kurš paziņo par objekta likvidēšanu un likvidēto elementu skaitu (ja likvidēšanas brīdī steks nav tukšs),
(3) metode ""Push"", kas pievieno stekam elementu, ja tas nav pilns,
(4) metode ""Pop"", kas izņem no steka augšējo elementu un atgriež tā vērtību,
(5) metode ""Count"", kas atgriež elementu skaitu stekā,
(6) metode ""Top"", kas atgriež augšējā elementa vērtību,
(7) metode ""IsEmpty"", kas noskaidro, vai steks ir tukšs,
(8) metode ""IsFull"", kas noskaidro, vai steks ir pilns.
Pirms uzdevuma veikšanas precīzi noskaidrot, ko nozīmē jēdziens steks (stack).
Programma izveidota: 18/11/2020
*******************************************/

#include "IntStack.h"
#include <iostream>

IntStack::IntStack() :
    data{0}, idx(0)
{}

IntStack::~IntStack() {
    std::cout << "Likvidejam Steku" << std::endl;
    if (idx == 1)     std::cout << "Atbrivots " << idx << " elements" << std::endl;
    else if (idx > 1) std::cout << "Atbrivoti " << idx << " elementi" << std::endl;
}

void IntStack::Push(int val) {
    if (!IsFull())
        data[idx++] = val;
}

int IntStack::Pop() {
    if (!IsEmpty())
        return data[--idx];
    return 0;
}

int IntStack::Top() const {
    if (!IsEmpty())
        return data[idx - 1];
    return 0;
}

unsigned IntStack::Count() const { return idx; }

bool IntStack::IsEmpty() const   { return idx == 0; }
bool IntStack::IsFull() const    { return idx == STACK_SIZE; }