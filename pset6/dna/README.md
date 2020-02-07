 # [dna](https://github.com/CalvinChe/CS50/blob/master/pset6/dna/dna.py)
  
   A program that identifies a person based on their DNA sequence.

   ## Usage
   ```bash
   Usage
   $ python dna.py databases/large.csv sequences/5.txt
   Lavender
   ```
   ## Specification
   1. Must have 2 arguments, the name of the CSV file containing the STR counts for a list of individuals,
      the name of the text file containing the DNA sequence to identify.
   2. For each of the STRs, the program should compute the longest run of consecutive repeats of the STR in the DNA sequence.
   3. if the STR counts match exactly with any of the individuals in the CSV file, the program will print the name of the individual.
      (assuming the STR counts will not match more than one individual)