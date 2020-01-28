/**
 * File:    tideman.c
 *
 * Author:  Calvin Che (github.com/CalvinChe), CS50
 * Date:    Jan 2020
 * Purpose: Created for CS50 EDX Problem Set 3
 *
 * Summary of File:
 *
 *     A program that runs a Tideman election.
 *
 * Specification
 *     1. There is a maximum number of 9 candidates.
 *     2. If multiple pairs have the same strength of victory, order does not matter.
 *     3. There is no more than one source for the winner.
 *
 * Example
 *     ./tideman Alice Bob Charlie
 *      Number of voters: 5
 *      Rank 1: Alice
 *      Rank 2: Charlie
 *      Rank 3: Bob
 *      
 *      Rank 1: Alice
 *      Rank 2: Charlie
 *      Rank 3: Bob
 *      
 *      Rank 1: Bob
 *      Rank 2: Charlie
 *      Rank 3: Alice
 *      
 *      Rank 1: Bob
 *      Rank 2: Charlie
 *      Rank 3: Alice
 *      
 *      Rank 1: Charlie
 *      Rank 2: Alice
 *      Rank 3: Bob
 *      
 *      Charlie
 *
*/
#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max number of candidates
#define MAX 9

// preferences[i][j] is number of voters who prefer i over j
int preferences[MAX][MAX];

// locked[i][j] means i is locked in over j
bool locked[MAX][MAX];

// Each pair has a winner, loser
typedef struct
{
    int winner;
    int loser;
}
pair;

// Array of candidates
string candidates[MAX];
pair pairs[MAX * (MAX - 1) / 2];

int pair_count;
int candidate_count;

// Function prototypes
bool vote(int rank, string name, int ranks[]);
void record_preferences(int ranks[]);
void add_pairs(void);
void sort_pairs(void);
void lock_pairs(void);
void print_winner(void);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: tideman [candidate ...]\n");
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
        candidates[i] = argv[i + 1];
    }

    // Clear graph of locked in pairs
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            locked[i][j] = false;
        }
    }

    pair_count = 0;
    int voter_count = get_int("Number of voters: ");

    // Query for votes
    for (int i = 0; i < voter_count; i++)
    {
        // ranks[i] is voter's ith preference
        int ranks[candidate_count];

        // Query for each rank
        for (int j = 0; j < candidate_count; j++)
        {
            string name = get_string("Rank %i: ", j + 1);

            if (!vote(j, name, ranks))
            {
                printf("Invalid vote.\n");
                return 3;
            }
        }

        record_preferences(ranks);

        printf("\n");
    }

    add_pairs();
    sort_pairs();
    lock_pairs();
    print_winner();
    return 0;
}

// Update ranks given a new vote
bool vote(int rank, string name, int ranks[])
{
    // for each candidate check if the name matches
    for (int i = 0; i < candidate_count; i++)
    {
        // if the name matches, record candidate's rank.
        if (!strcmp(name, candidates[i]))
        {
            ranks[rank] = i;
            return true;
        }
    }
    return false;
}

// Update preferences given one voter's ranks
void record_preferences(int ranks[])
{
    // increment corresponding spot in preferences array.
    for (int i = 0; i < candidate_count - 1; i++)
    {
        for (int j = i + 1; j < candidate_count; j++)
        {
            preferences[ranks[i]][ranks[j]]++;
        }
    }
    return;
}

// Record pairs of candidates where one is preferred over the other
void add_pairs(void)
{
    // iterate through the preferences array and check for pairs.
    for (int i = 0; i < candidate_count - 1; i++)
    {
        for (int j = i + 1; j < candidate_count; j++)
        {
            if (preferences[i][j] > preferences[j][i])
            {
                pairs[pair_count].winner = i;
                pairs[pair_count].loser = j;
                pair_count++;
            }
            else if (preferences[i][j] < preferences[j][i])
            {
                pairs[pair_count].winner = j;
                pairs[pair_count].loser = i;
                pair_count++;
            }
        }
    }
    return;
}

// Sort pairs in decreasing order by strength of victory
void sort_pairs(void)
{
    // bubble sort to sort the pairs.
    int swaps = 0;
    for (int i = 0, n = pair_count; i < n - 1; n--)
    {
        if (preferences[pairs[i].winner][pairs[i].loser] < preferences[pairs[i + 1].winner][pairs[i + 1].loser])
        {
            swaps++;
            pair temp;
            temp.winner = pairs[i].winner;
            temp.loser = pairs[i].loser;
            pairs[i].winner = pairs[i + 1].winner;
            pairs[i].loser = pairs[i + 1].loser;
            pairs[i + 1].winner = temp.winner;
            pairs[i + 1].loser = temp.loser;
        }
        if (swaps == 0)
        {
            break;
        }
        else
        {
            swaps = 0;
        }
    }
    return;
}

// helper method for lock_pairs to check if there is a path from winner to loser using the locked array.
bool pathTo(int winner, int loser)
{
    for (int i = 0; i < candidate_count; i++)
    {
        if (locked[i][winner])
        {
            if (i == loser)
            {
                return true;
            }
            if (pathTo(i, loser))
            {
                return true;
            }
        }
    }
    return false;
}

// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{
    for (int i = 0; i < pair_count; i++)
    {
        // if there is no path from winner to loser, lock the pair.
        if (!pathTo(pairs[i].winner, pairs[i].loser))
        {
            locked[pairs[i].winner][pairs[i].loser] = true;
        }
    }
    return;
}

// Print the winner of the election, There will not be more than one source of the graph.
void print_winner(void)
{
    bool winner = false;
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            // this candidate has a locked pair pointing at it.
            if (locked[j][i])
            {
                break;
            }
            if (j == candidate_count - 1)
            {
                printf("%s\n", candidates[i]);
                return;
            }
        }
    }
    return;
}

