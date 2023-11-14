text = input()
word = text.split("WUB")
x = []
for i in word:
    if i != "":
        x.append(i)

output = " ".join(x)
print(output)