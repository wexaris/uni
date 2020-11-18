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

#pragma once

#ifndef STACK_SIZE
#define STACK_SIZE 5
#endif

/// Veselu skaitļu steks
/// Var saturēt tikai `STACK_SIZE` elementu skaitu, noklusēti 5
class IntStack {
public:
    IntStack();
    virtual ~IntStack();

    /// Pievieno stekam elementu
    void Push(int val);
    /// Izņem un atgriež virsējo steka elementu
    int Pop();
    /// Virsējais steka elements
    int Top() const;

    /// Steka elementu skaits
    unsigned Count() const;

    bool IsEmpty() const;
    bool IsFull() const;

private:
    int data[STACK_SIZE];
    unsigned idx;
};