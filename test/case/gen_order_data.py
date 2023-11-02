import csv

def write(file_nm:str, data: list):
    with open(file_nm, "w") as csv_file:
        writer = csv.writer(csv_file, delimiter='|')

        writer.writerows(data)
    
    print("done "+file_nm)

def main():
    ord1 = list()
    for i in range(1, 25):
        ord1.append([i, (i+1)*1.0, 'a'+str(i+3)])

    ord2 = list()
    for i in range(1, 25):
        ord2.append([i, i*10+20])

    write('data/order1.csv', ord1)
    write('data/order2.csv', ord2)

if __name__ == '__main__':
    main()
