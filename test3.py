from numpy import number


numberInput = 20
arrayOutput =[]
s = 0
while(1):
    quotient = numberInput //2
    arrayOutput.append(quotient)
    numberLeft = numberInput - quotient
    numberInput = numberLeft
    if numberInput < 2:
        break
print(arrayOutput)
for i  in range(0,len(arrayOutput)):
    s += arrayOutput[i]
print("Tong s = " + str(s) )
