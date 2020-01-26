/**
 * File:    plurality.c
 *
 * Author:  Calvin Che (github.com/CalvinChe)
 * Date:    Jan 2020
 * Purpose: Created for CS50 EDX Problem Set 3
 *
 * Summary of File:
 *
 *     A program that runs a plurality election.
 *
 * Example
 *     $ ./plurality Alice Bob
 *     Number of voters: 3
 *     Vote: Alice
 *     Vote: Bob
 *     Vote: Alice
 *     Alice
 *
*/
#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max number of candidates
#define MAX 9

// Candidates have name and vote count
typedef struct
{
    string name;
    int votes;
}
candidate;

// Array of candidates
candidate candidates[MAX];

// Number of candidates
int candidate_count;

// Function prototypes
bool vote(string name);
void print_winner(void);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: plurality [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates
    candidate_count = argc - 1;
    if (candidate_count > MAX)
    {
        printf("Maximum number of candidates is %i\n", MAX);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i].name = argv[i + 1];
        candidates[i].votes = 0;
    }

    int voter_count = get_int("Number of voters: ");

    // Loop over all voters
    for (int i = 0; i < voter_count; i++)
    {
        string name = get_string("Vote: ");

        // Check for invalid vote
        if (!vote(name))
        {
            printf("Invalid vote.\n");
        }
    }

    // Display winner of election
    print_winner();
}

// Update vote totals given a new vote
bool vote(string name)
{
    // for each candidate check if the name matches
    for (int i = 0; i < candidate_count; i++)
    {
        // if the name matches increment the candidate's vote count by one.
        if (!strcmp(name, candidates[i].name))
        {
            candidates[i].votes++;
            return true;
        }
    }
    return false;
}

// Print the winner (or winners) of the election
void print_winner(void)
{
    // if there are no candidates
    if (!candidate_count)
    {
        return;
    }

    // make an array of winners set initial winner to first on the list
    int win[candidate_count];
    for (int i = 0; i < candidate_count; i++)
    {
        win[i] = 0;
    }
    int biggest = 0;
    win[0] = 1;

    // compare vote counts if greater reset winner array, if equal add a new winner.
    for (int i = 1; i < candidate_count; i++)
    {
        int curVal = candidates[i].votes;
        int bigVal = candidates[biggest].votes;
        if (curVal > bigVal)
        {
            for (int j = 0; j < candidate_count; j++)
            {
                win[j] = 0;
            }
            win[i] = 1;
            biggest = i;
        }
        else if (curVal == bigVal)
        {
            win[i] = 1;
        }
    }

    // print the winner (or winners) of the election
    for (int i = 0; i < candidate_count; i++)
    {
        if (win[i])
        {
            printf("%s\n", candidates[i].name);
        }
    }
    return;
}

