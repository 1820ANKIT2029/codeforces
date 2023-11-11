def main():
    n1 = input()
    n2 = input()
    a = ""
    for i, j in zip(n1, n2):
        if (int(i)+int(j)) in [0,2]:
            print("0",end="")
        else:
            print("1",end="")
    print()

if __name__ == "__main__":
    main()