n = int(input())
x = 0
for i in range(n):
    a = input()
    if a[0]=="+" or a[1]=="+" or a[2]=="+":
        x += 1
    else:
        x -= 1
print(x)