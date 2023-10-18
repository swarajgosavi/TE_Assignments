message = '1001101'

m = len(message)

r = 0

while r < m:
    if 2**r >= m + r + 1:
        break
    r += 1

print(m, r)
n = m + r

hamming = []

for i in message:
    hamming.append(int(i))

hamming.reverse()

for i in range(r):
    hamming.insert(2**i - 1, -1)

hamming.reverse()

r1 = []

for i in range(r):
    p = 2**i
    j = n - p -1
    while j > 0:
        if j % 2 == 0:
            r1.append(hamming[j])
        else:
            pass
        j -= p
    print(r1)
    r1 = []
        

print(hamming)