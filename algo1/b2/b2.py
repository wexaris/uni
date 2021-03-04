#*******************************************
# Rainers Vorza, rv20039
# B2. Dots naturāls skaitlis n < 1000. Izdrukāt doto skaitli romiešu pierakstā.
# Programma izveidota: 05/10/2020
#*******************************************

# Rezultātu tabula:
#    n   |   CPPRezultāts   |   PyRezultāts    |    Paredzēts     | Sakrīt
# -------|------------------|------------------|------------------|--------
#    420 |             CDXX |             CDXX |             CDXX |   X
#   1000 |                M |                M |                M |   X
#      0 | nepieņemami dati | nepieņemami dati | nepieņemami dati |   X
#     -1 | nepieņemami dati | nepieņemami dati | nepieņemami dati |   X
#    txt | nepieņemami dati | nepieņemami dati | nepieņemami dati |   X

# Romiešu cipars - tā simbols un vērtība
class RomanNumeral():
    "Stores name and place pairs"
    def __init__(self, symbol, value):
        self.Symbol = symbol
        self.Value = value


print("Ievadiet ENTER lai beigtu")

while (True):
    # Saņemam naturālo un izņemamo skaitli no lietotāja.
    # Ja ir tukšums, apturam programmu.
    inputStr = input("Ievadiet naturalu skaitli: ")
    if (inputStr == ""):
        break

    try:
        inputNum = int(inputStr)
        # Pārliecinamies, ka ievadītais skaitlis ir 1 - 1000
        if 0 >= inputNum or inputNum > 1000:
            raise ValueError("skaitlim jabut 1 - 1000")

        # Saraksts ar romiešu cipariem un to vērtībām.
        roman = []
        roman.append(RomanNumeral("M", 1000))
        roman.append(RomanNumeral("CM", 900))
        roman.append(RomanNumeral("D",  500))
        roman.append(RomanNumeral("CD", 400))
        roman.append(RomanNumeral("C",  100))
        roman.append(RomanNumeral("XC",  90))
        roman.append(RomanNumeral("L",   50))
        roman.append(RomanNumeral("XL",  40))
        roman.append(RomanNumeral("X",   10))
        roman.append(RomanNumeral("IX",   9))
        roman.append(RomanNumeral("V",    5))
        roman.append(RomanNumeral("IV",   4))
        roman.append(RomanNumeral("I",    1))

        # Atkārtoti pievienojam lielākos iespējamos romiešu ciparus
        # līdz ievadītais cipars ticis konvertēts.
        res = ""
        for r in roman:
            while (inputNum - r.Value) >= 0:
                res += r.Symbol
                inputNum -= r.Value

        # Paziņojam rezultātu
        print(res, end='\n\n')

    except ValueError as e:
        print("nepienemami dati;", e, end="\n\n")
