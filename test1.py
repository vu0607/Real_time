a = [1,-1,-2,3]
arrayMax =[]
array2 =[]
array3 =[]
for i in range(1,len(a)):
    if i == 1:
        arrayMax.append(max(a))
        
    if i == 2:
        for j1 in range(len(a)-1):
            arrayMax.append(sum(a[j1:j1+2]))
        
    if i == 3:
        for j2 in range(len(a)-2):
            arrayMax.append(sum(a[j2:j2+3]))
        
    if i == 4:
        for j3 in range(len(a)-3):
            arrayMax.append(sum(a[j3:j3+4]))
maxSum = max(arrayMax)
print(maxSum)