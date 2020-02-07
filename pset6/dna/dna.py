# File:    dna.py
# 
# Author:  Calvin Che (github.com/CalvinChe)
# Date:    Feb 2020
# Purpose: Created for CS50 2020 EDX Problem Set 6
# 
#   Summary of file
#      A program that identifies a person based on their DNA sequence.
#
#   Specification
#   1. Must have 2 arguments, the name of the CSV file containing the STR counts for a list of individuals,
#      the name of the text file containing the DNA sequence to identify.
#   2. For each of the STRs, the program should compute the longest run of consecutive repeats of the STR in the DNA sequence.
#   3. if the STR counts match exactly with any of the individuals in the CSV file, the program will print the name of the individual.
#      (assuming the STR counts will not match more than one individual)
#
#   Usage
#   $ python dna.py databases/large.csv sequences/5.txt
#   Lavender
import csv
from sys import argv, exit


def dna():
    # must have 2 arguments
    if len(argv) != 3:
        print("Usage: python dna.py data.csv sequence.txt")
        exit(1)

    # store the csv's rows in an array
    database = []
    with open(argv[1]) as file:
        csvfile = csv.reader(file)
        for row in csvfile:
            database.append(row)

    # store the sequence text file in a string
    with open(argv[2]) as file:
        sequence = file.read()

    # check for STR repeats
    strCount = len(database[0])
    sequenceCrt = [0]
    for i in range(1, strCount):
        STR = database[0][i]
        strL = len(database[0][i])
        repeat = 0
        largest = 0
        count = 0
        while count < (len(sequence) - strL):
            if sequence[count:count+strL] == STR:
                repeat += 1
                count += strL
            else:
                if repeat > largest:
                    largest = repeat
                repeat = 0
                count += 1
        sequenceCrt.append(largest)

    # find a match for STR repeats from database
    for i in range(1, len(database)):
        for j in range(1, strCount):
            if sequenceCrt[j] == int(database[i][j]):
                if j == strCount - 1:
                    # all STR repeats match perfectly.
                    print(database[i][0])
                    exit(0)
            else:
                break

    # no matches were found.
    print("No match")
    exit(0)


dna()