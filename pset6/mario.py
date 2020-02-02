# File:    mario.py
# 
# Author:  Calvin Che (github.com/CalvinChe)
# Date:    Jan 2020
# Purpose: Created for CS50 2020 EDX Problem Set 6
# 
# Summary of File:
# 
#     Recreation of the pyramids in Nintendo's Super Mario Brothers in text.
#     Hashes will be used to replace bricks.
#     Restrictions.
#          1. The height must be between, 1 and 8, inclusive
#          2. There should not be any spaces to the right of the pyramid
#          3. The "gap" between adjacent pyramids is equal to the width of two hashes.
#     Example of a 4 height pyramid:
#             #  #
#            ##  ##
#           ###  ###
#          ####  ####
from cs50 import get_int


def main():
    # prompt user for height
    while True:
        height = get_int("Height: ")
        # height must be between 1 and 8, inclusive
        if height > 0 and height < 9:
            break

    # Print out the pyramid
    for i in range(height - 1, -1, -1):
        # Print out the left side of the pyramid
        for j in range(height):
            if j >= i:
                print("#", end="")
            else:
                print(" ", end="")

        # Print out the gap between the pyramid
        print("  ", end="")

        # Print the right side of the pyramid
        for k in range(i, height, 1):
            if k >= i:
                print("#", end="")

        print()


main()