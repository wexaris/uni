#*******************************************
# Rainers Vorza, rv20039
# A5. Dots naturāls skaitlis n. Izdrukāt skaitli, kurš iegūts no dotā skaitļa, izmetot ciparu k.
# (Piemēram, ja n=12025 un k=2, jāiegūst 105). Skaitļa dalīšana ciparos jāveic skaitliski.
# Programma izveidota: 17/09/2020
#*******************************************

# Rezultātu tabula:
#    n   |  k  |   CPPRezultāts   |   PyRezultāts    |    Paredzēts     | Sakrīt
# -------|-----|------------------|------------------|------------------|--------
#  12025 | 2   |              105 |              105 |              105 |   X
#    420 | 5   |              420 |              420 |              420 |   X
#   2020 | 2   |                0 |                0 |                0 |   X
#    555 | 5   |                0 |                0 |                0 |   X
#      0 | 0   |                0 |                0 |                0 |   X
#      5 |     | nepieņemami dati | nepieņemami dati | nepieņemami dati |   X
#        | 5   | nepieņemami dati | nepieņemami dati | nepieņemami dati |   X
#     -5 |     | nepieņemami dati | nepieņemami dati | nepieņemami dati |   X
#     -5 | 5   | nepieņemami dati | nepieņemami dati | nepieņemami dati |   X
#      5 | -5  | nepieņemami dati | nepieņemami dati | nepieņemami dati |   X
#    txt | 5   | nepieņemami dati | nepieņemami dati | nepieņemami dati |   X
#      5 | txt | nepieņemami dati | nepieņemami dati | nepieņemami dati |   X
#    txt | txt | nepieņemami dati | nepieņemami dati | nepieņemami dati |   X
#    txt |     | nepieņemami dati | nepieņemami dati | nepieņemami dati |   X
#        | txt | nepieņemami dati | nepieņemami dati | nepieņemami dati |   X

print("Ievadiet ENTER lai beigtu")

while (True):
    # Saņemam naturālo un izņemamo skaitli no lietotāja.
    # Ja ir tukšums, apturam programmu.
    inputStr = input("Ievadiet naturālu skaitli un izņemamo ciparu: ")
    if (inputStr == ""):
        break;

    try:
        # Pārliecinamies, ka ievadīti divi skaitļi
        if (len(inputStr.split()) != 2):
            raise ValueError()

        # Pārvēršam un saglabājam abus kā skaitļus.
        inputNum = int(inputStr.split()[0])
        removeNum = int(inputStr.split()[1])
        # Pārliecinamies, ka ievadītais skaitlis ir naturāls.
        if inputNum < 0:
            raise ValueError()
        # Pārliecinamies, ka izņemamais skaitlis ir tikai viens cipars.
        if removeNum < 0 or removeNum > 9:
            raise ValueError()

        # Pārbaudam visus naturālā skaitļa ciparus no labās puses uz kreiso,
        # pievienojot tos rezultāta skaitlim kreisajā pusē, ja tie nesakrīt
        # ar izņemamo ciparu.
        res = 0
        loop = 0
        while inputNum:
            digit = int(inputNum % 10)
            inputNum = int(inputNum / 10)

            if digit != removeNum:
                res += digit * pow(10, loop)
                loop += 1

        # Paziņojam rezultātu
        print(res, end="\n\n")

    except ValueError:
        print("Nepieņemami dati\n")
