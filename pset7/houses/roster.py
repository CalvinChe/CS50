from sys import argv, exit
from cs50 import SQL


def roster():
    # must have the name of a csv file as a command-line argument
    if len(argv) != 2:
        print("Usage: python roster.py house")
        exit(1)

    # access database with cs50
    db = SQL("sqlite:///students.db")

    house = db.execute("SELECT first, middle, last, birth FROM 'students' WHERE house = ? ORDER BY last, first", argv[1])

    # Print out full name and birth year
    for person in house:
        print(f"{person['first']} ", end='')

        if person['middle'] is not None:
            print(f"{person['middle']} ", end='')

        print(f"{person['last']}, born {person['birth']}")


roster()