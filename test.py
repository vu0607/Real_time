a = [1,2,3,-1,0]
arrayMax =[]
for i in range(1,len(a)+1):      #Su dung bien i de nhom i phan tu voi nhau
        for j0 in range(len(a)-(i-1)):    
            arrayMax.append(sum(a[j0:j0+i]))   # Tinh tong cua cac phan tu va gan no vao mang arrayMax
Sum = max(arrayMax)
print("Gia tri lon nhat cua mang con la ", Sum)