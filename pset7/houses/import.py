import csv
from sys import argv, exit
from cs50 import SQL


def main():
    # must have the name of a csv file as a command-line argument
    if len(argv) != 2:
        print("Usage: python import.py characters.csv")
        exit(1)
    if not argv[1].endswith('.csv'):
        print("Usage: python import.py characters.csv")
        exit(1)

    # access database with cs50
    db = SQL("sqlite:///students.db")

    # parse csv file.
    with open(argv[1]) as file:
        csvfile = csv.DictReader(file)
        # insert into students table each student
        for row in csvfile:
            names = row["name"].split()
            if len(names) == 2:
                db.execute("INSERT INTO students (first, middle, last, house, birth) VALUES(?, ?, ?, ?, ?)",
                           names[0], None, names[1], row['house'], row['birth'])
            else:
                db.execute("INSERT INTO students (first, middle, last, house, birth) VALUES(?, ?, ?, ?, ?)",
                           names[0], names[1], names[2], row['house'], row['birth'])


main()