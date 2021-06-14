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
    for (int i = 0; i < candidate_count; i++)
    {
        if (strcmp(candidates[i], name) == 0)
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
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = i + 1; j < candidate_count; j++)
        {
            preferences[ranks[i]][ranks[j]] = preferences[ranks[i]][ranks[j]] + 1;
        }
    }
    return;
}

// Record pairs of candidates where one is preferred over the other
void add_pairs(void)
{
    pair_count = 0;
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            // swap the i and j around. We are inverting the table to see if more people prefered alice over bob, compared with bob over alice. If yes, then we add the pair
            if (preferences[i][j] > preferences[j][i])
            {
                // This is telling us the INDEX value of the candidate that has won the pair. Therefore [2] would mean the THIRD candidate has won over say the first candidate (if j = 0), there is an EDGE between them
                pairs[pair_count].winner = i;
                pairs[pair_count].loser = j;
                pair_count = pair_count + 1;
            }
        }
    }
    return;
}

// Sort pairs in decreasing order by strength of victory
void sort_pairs(void)
{
    pair x[pair_count];
    pair y[pair_count];
    for (int i = 0; i < pair_count; i++)
    {
        for (int j = i + 1; j < pair_count; j++)
        {
            if (preferences[pairs[i].winner][pairs[i].loser] < preferences[pairs[j].winner][pairs[j].loser])
            {
                x[pair_count].winner = pairs[i].winner;
                x[pair_count].loser = pairs[i].loser;

                y[pair_count].winner = pairs[j].winner;
                y[pair_count].loser = pairs[j].loser;

                pairs[i].winner = y[pair_count].winner;
                pairs[i].loser = y[pair_count].loser;

                pairs[j].winner = x[pair_count].winner;
                pairs[j].loser = x[pair_count].loser;
            }
        }
    }
    /*
    for (int i = 0; i < pair_count; i++)
    {
        int a = pairs[i].winner;
        int b = pairs[i].loser;
        printf("Who beat who: %i %i\n", a, b);
    }
    for (int i = 0; i < pair_count; i++)
    {
        int a = preferences[pairs[i].winner][pairs[i].loser];
        int b = preferences[pairs[i].loser][pairs[i].winner];
        // we are looking for the MAGNITUDE of the victory. Did they win by 1/2 or three votes. remember this is only for PAIRS. I.e. they have an edge '0 1', where 0 beats 1.
        printf("Magnitude: %i %i\n", a, b);
    }
    */
    return;
}

// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{
    int cycle_check_i = 0;
    int cycle_check_j = 0;
    //printf("%i\n", pair_count);


    int total = 0;
    for (int i = 0; i < pair_count; i++)
    {
        for (int j = 0; j < pair_count; j++)
        {
            total = total + locked[i][j];
        }


        if (!(cycle_check_i + pairs[i].winner == candidate_count && cycle_check_j + pairs[i].loser == candidate_count))
        {
            locked[pairs[i].winner][pairs[i].loser] = true;
            cycle_check_i = cycle_check_i + pairs[i].winner;
            cycle_check_j = cycle_check_j + pairs[i].loser;
        }
    }

    /*

    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            printf("%i", locked[i][j]);
        }
        printf("\n");
    }
    */

    //printf("cycle check i: %i\n", cycle_check_i);
    //printf("cycle check j: %i\n", cycle_check_j);

    return;
}

// Print the winner of the election
void print_winner(void)
{
    for (int i = 0; i < candidate_count; i++)
    {
        int row_total = 0;
        for (int j = 0; j < candidate_count; j++)
        {
            row_total = row_total + locked[i][j];
            if (row_total >= candidate_count - 1)
            {
                printf("%s\n", candidates[i]);

            }
        }
    }
    return;
}

