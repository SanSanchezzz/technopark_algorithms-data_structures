def main():
    num = 1000

    for i in range (num):
        file = open(str(i) + '.txt', 'w')
        file.write(str(i) + '\n')
        file.write(str(num) + '\n')
        for j in range (i):
            file.write(str(j + 1) + '\n')
        for k in range (num - 1, -1, -1):
            file.write(str(k + 1) + '\n')
        file.close()

if __name__ == '__main__':
    main()
