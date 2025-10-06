#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max voters and candidates
#define MAX_VOTERS 100
#define MAX_CANDIDATES 9

// preferences[i][j] is jth preference for voter i
int preferences[MAX_VOTERS][MAX_CANDIDATES];

// Candidates have name, vote count, eliminated status
typedef struct
{
    string name;
    int votes;
    bool eliminated;
}
candidate;

// Array of candidates
candidate candidates[MAX_CANDIDATES];

// Numbers of voters and candidates
int voter_count;
int candidate_count;

// Function prototypes
bool vote(int voter, int rank, string name);
void tabulate(void);
bool print_winner(void);
int find_min(void);
bool is_tie(int min);
void eliminate(int min);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: runoff [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates
    candidate_count = argc - 1;
    if (candidate_count > MAX_CANDIDATES)
    {
        printf("Maximum number of candidates is %i\n", MAX_CANDIDATES);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i].name = argv[i + 1];
        candidates[i].votes = 0;
        candidates[i].eliminated = false;
    }

    voter_count = get_int("Number of voters: ");
    if (voter_count > MAX_VOTERS)
    {
        printf("Maximum number of voters is %i\n", MAX_VOTERS);
        return 3;
    }

    // Keep querying for votes
    for (int i = 0; i < voter_count; i++)
    {

        // Query for each rank
        for (int j = 0; j < candidate_count; j++)
        {
            string name = get_string("Rank %i: ", j + 1);

            // Record vote, unless it's invalid
            if (!vote(i, j, name))
            {
                printf("Invalid vote.\n");
                return 4;
            }
        }

        printf("\n");
    }

    // Keep holding runoffs until winner exists
    while (true)
    {
        // Calculate votes given remaining candidates
        tabulate();

        // Check if election has been won
        bool won = print_winner();
        if (won)
        {
            break;
        }

        // Eliminate last-place candidates
        int min = find_min();
        bool tie = is_tie(min);

        // If tie, everyone wins
        if (tie)
        {
            for (int i = 0; i < candidate_count; i++)
            {
                if (!candidates[i].eliminated)
                {
                    printf("%s\n", candidates[i].name);
                }
            }
            break;
        }

        // Eliminate anyone with minimum number of votes
        eliminate(min);

        // Reset vote counts back to zero
        for (int i = 0; i < candidate_count; i++)
        {
            candidates[i].votes = 0;
        }
    }
    return 0;
}

// Record preference if vote is valid
bool vote(int voter, int rank, string name)
{
    //Loops through the number of candidates
    for (int a = 0; a < candidate_count; a++)
    {
        //Checks if the user entered a valid candidate
        if (strcmp(name, candidates[a].name) == 0)
        {
            //Updates the preferences array from each user and the ranking they chose for the candidates
            preferences[voter][rank] = a;
            return true;
        }
    }
    return false;
}

// Tabulate votes for non-eliminated candidates
void tabulate(void)
{
    //Loops through the number of voters
    for (int b = 0; b < voter_count; b++)
    {
        //Loops through the number of candidates
        for (int c = 0; c < candidate_count; c++)
        {
            //Checks if a candidate is still in the election
            if (candidates[preferences[b][c]].eliminated == false)
            {
                //Adds a vote if the candidate is in the election
                candidates[preferences[b][c]].votes++;
                break;
            }
        }
    }
    return;
}

// Print the winner of the election, if there is one
bool print_winner(void)
{
    //Loops through the candidate count
    for (int d = 0; d < candidate_count; d++)
    {
        //Checks to see if the a candidate has more than half of the votes
        if (candidates[d].votes > voter_count / 2)
        {
            //prints the winner
            printf("%s\n", candidates[d].name);
            return true;
        }
    }
    return false;
}

// Return the minimum number of votes any remaining candidate has
int find_min(void)
{
    int minimum = 0;
    //Loops through the number of candidates
    for (int e = 0; e < candidate_count; e++)
    {
        //Checkts to see if a candidate is still in the election and has the fewest votes
        if (candidates[e].votes < voter_count && candidates[e].eliminated == false)
        {
            minimum = candidates[e].votes;
        }
    }
    return minimum;
}

// Return true if the election is tied between all candidates, false otherwise
bool is_tie(int min)
{
    int candidate_min_votes = 0;
    int approved_candidates = 0;
    //Loops through the number of candidates
    for (int h = 0; h < candidate_count; h++)
    {
        //Checks to see the number of candidates and compares it with a candidate with the fewest votes that is still in the election
        if (candidates[h].votes == min)
        {
            candidate_min_votes++;
        }
        //Checks to see which candidates are still in the election
        if (candidates[h].eliminated == false)
        {
            approved_candidates++;
        }
    }
    //Checks to see if it is a tie
    if (candidate_min_votes == approved_candidates)
    {
        return true;
    }
    return false;
}

// Eliminate the candidate (or candidates) in last place
void eliminate(int min)
{
    //Loops through the number of candidates
    for (int f = 0; f < candidate_count; f++)
    {
        //Checks to see if candidate has the fewest number of votes
        if (candidates[f].votes == min)
        {
            //Removes the candidate with the fewest number of votes
            candidates[f].eliminated = true;
        }
    }
    return;
}