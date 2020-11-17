// 10. Uzdevums (III) – vidējais svars
// Ievada no klaviatūras svaru vairākās mēneša dienās. Ievads sastāv no
// skaitļu pāru virknes – datums (vesels skaitlis robežās no 1 līdz 31 un svars –
// reāls pozitīvs skaitlis). Ievada vairākus šādus pārus (jauktā secībā) un ievadu beidz,
// kad tiek ievadīts nekorekts datums (ārpus robežām).
// Dienās, kurās svars nav ievadīts, tas tiek modelēts no tuvāk esošajiem
// ievadītajiem svariem kā parādīts zemāk. Aprēķināt vidējo svaru mēneša laikā,
// ņemot vērā modelēto svaru tajās dienās, par kurām svars nav ievadīts.
//
// Rainers Vorza
// rv20039

#include <iostream>

// Piepilda noradito skaitu masiva elementu ar lineari
// interpoletam vertibam (beg; end).
void interp_array(double* arr, double beg, double end, unsigned count) {
    // Katras nakamas vertibas inkrementacija
    double incr = (end - beg) / (count + 1);
    // Ievietojam inkrementetu vertibu katram nakosajam masiva elementam
    for (double val = beg + incr; count > 0; count--, val += incr) {
        *arr++ = val;
    }
}

// Iegust videjo aritmetisko vertibu no noradita masiva.
float get_average(double* arr, unsigned size) {
    double sum = 0;
    for (unsigned i = 0; i < size; i++)
        sum += arr[i];
    return sum / size;
}

int main() {
    // Inicializejam masivu, kas satur katrai menesa dienai atbilstoso svaru
    double weight[31];
    for (int n = 0 ; n < 31 ; n++)
        weight[n] = 0.0;

    // Atkatroti prasam no lietotaja dienu un svaru
    // lidz tiek iedots datums, kas nepieder [1; 31]
    while (true) {
        unsigned day;
        double val;
        std::cout << "Ievadiet dienu un svaru: ";
        std::cin >> day >> val;

        // Parbaudam vai datums ir derigs
        if (day < 1 || 31 < day)
            break;

        // Parbaudam vai svars ir derigs
        if (val > 0)
            weight[day - 1] = val;
        else
            std::cerr << "Nepienemams svars, meginiet velreiz!" << std::endl;
    }

    // Aizpildam tuksas dienas ar interpoletam vertibam
    for (unsigned i = 0; i < 31; i++) {
        if (weight[i] == 0.0) {
            // Saglabajam pirmo dienu, no kuras interolet
            unsigned beg_idx = i;

            // Atrodam nakamo dienu, kurai ir vertiba, vai menesa beigas
            for (; weight[i] == 0 && i < 31; i++);

            // Ja pirma tuksa vertiba nebija pirma menesa diena,
            // lietojam ieprieksejas dienas vertibu, citadi - nulli
            double last_weight = beg_idx ? weight[beg_idx - 1] : 0;
            // Ja pedeja tuksa vertiba nebija pedeja menesa diena,
            // lietojam nakamas dienas vertibu, citadi - pirmas dienas
            double next_weight = i < 31 ? weight[i] : last_weight;

            // Veicam interpolaciju sakot no pirmas tuksas dienas
            interp_array(
                &weight[beg_idx],
                last_weight ? last_weight : next_weight,
                next_weight,
                i - beg_idx);
        }
    }

    // Izprintejam visa menesa veribas
    std::cout << "Menesa vertibas: ";
    for (int i = 0; i < 31; i++)
        std::cout << weight[i] << " ";
    std::cout << std::endl;

    // Izprintejam videjo
    std::cout << std::fixed << "Videjais svars: " << get_average(weight, 31) << std::endl;
}