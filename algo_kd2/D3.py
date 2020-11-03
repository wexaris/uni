
n = input("N: ")
if n < 0:
    print("N jabut naturalam")
    exit()

count = 0
i = n
while count < 5:
    # Atrod pirmo ciparu
    first = i
    while first >= 10:
        first /= 10
    # Atrod pedejo ciparu
    last = i % 10

    if (first + last) % 2 == 1:
        print(i)
        count += 1
    i += 1