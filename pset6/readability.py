# File:    readability.py
# 
# Author:  Calvin Che (github.com/CalvinChe)
# Date:    Jan 2020
# Purpose: Created for CS50 2020 EDX Problem Set 6
# 
#   Summary of file
#      A program that estimates the reading grade level of the user's input using the Coleman-Liau index.
#
#   Specification
#   1. Any letter is any, lowercase character a to z or any uppercase character from A to Z
#   2. Any sequence of characters is seperated by spaces should count as a word, a sentence will not have multiple spaces in a row
#   3. Any occurrence of a period, exclamation point, or question mark indicates the end of a sentence.
#
#   Usage
#   $ python readability.py
#   Text: Congratulations! Today is your day. You're off to Great Places! You're off and away!
#   Grade 3
import re
from sys import exit
from cs50 import get_string


def readability():
    # Prompt user for text.
    text = get_string("Text: ")
    # Exit if user gives no text
    if text == "":
        print("Before Grade 1")
        exit(1)
    letter = 0
    word = 1
    sentence = 0
    # Iterate through text
    for c in text:
        # regex to check if letter, space, or sentence end.
        if re.search("[a-z]", c, re.IGNORECASE):
            letter += 1
        elif c == " ":
            word += 1
        elif re.search("[.!?]", c):
            sentence += 1
    # Calculate Coleman-Liau index
    L = letter/word * 100
    S = sentence/word * 100
    index = 0.0588 * L - 0.296 * S - 15.8
    # Round index and print grade
    indexR = round(index)
    if indexR < 1:
        print("Before Grade 1")
    elif indexR > 15:
        print("Grade 16+")
    else:
        print(f"Grade {indexR}")


readability()