# File:    credit.c
# 
# Author:  Calvin Che (github.com/CalvinChe)
# Date:    Jan 2020
# Purpose: Created for CS50 2020 EDX Problem Set 6
# 
# Summary of File:
# 
#     A program that prompts the user for a credit card number and reports
#     whether it is a valid American Express, MasterCard, or Visa card number
#     using Luhn's algorithm.
#     Luhn's algorithm:
#      1. Multiply every other digit by 2, starting with the number’s second-to-last digit,
#         and then add those products’ digits together.
#      2. Add the sum to the sum of the digits that weren’t multiplied by 2.
#      3. If the total’s last digit is 0
#         (or, put more formally, if the total modulo 10 is congruent to 0),
#         the number is valid!
#     Differentiating between credit card companies:
#      * American Express: 15-digit numbers, start with: 34 or 37
#      * MasterCard:       16-digit numbers, start with: 51, 52, 53, 54, or 55
#      * Visa :    13- and 16-digit numbers, start with: 4
#      Note: Mastercard also have other potential starting numbers but we 
#            won't concern ourselves with this problem.
#            
#     Example:
#      $ ./credit
#      Number: 4003600000000014
#      VISA
import re
from sys import exit
from cs50 import get_int


def main():
    ccNum = get_int("Number: ")
    sumOdd = 0
    sumEven = 0
    length = 0

    # Check if CC number is valid, start from the end
    for i in reversed(str(ccNum)):
        # divide every other digit
        if length % 2:
            tmp = int(i) * 2
            # add the products' digits together
            if len(str(tmp)) > 1:
                for j in str(tmp):
                    sumOdd += int(j)
            else:
                sumOdd += tmp
        else:
            # add the sum of the digits that were not multiplied
            sumEven += int(i)
        length += 1

    # Check if number is valid
    if (sumEven + sumOdd) % 10 != 0:
        print("INVALID")
        exit(1)

    # Regex to determine company
    if re.search("^3[47]", str(ccNum)):
        if length == 15:
            print("AMEX")
            exit(0)
    if re.search("^4", str(ccNum)):
        if length == 13 or length == 16:
            print("VISA")
            exit(0)
    if re.search("^5[12345]", str(ccNum)):
        if length == 16:
            print("MASTERCARD")
            exit(0)
    print("INVALID")
    exit(1)


main()