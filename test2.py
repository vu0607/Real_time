a = [0,0,0,0,0]
b =[]
n = len(a)
def find_number(arr):
    for i in range(0,n):
        for j in range(n-1, -1, -1):
            if a[i] == a[j]:
                if a[i+1] == a[j-1]:
                    return a[i], a[i+1]
            return -1
print(find_number(a))
