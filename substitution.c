# include <stdio.h>
# include <cs50.h>
# include <string.h>
# include <ctype.h>
# include <stdlib.h>

// argc is an integer value for the number of arguments in the command line
// argv is a string array with with the string values of the command line stored in each element.

int main(int argc, string argv[])
{

    //------------------------------------------------------------------------     PART 1 - Command Line Prompt Conditions for the Encription Key ---------------------------------------------------------------------------------------------//




    // Command Line prompt for the 26 alphabetically letter cypher key will be in the command line. i) it must be entered ii) be 26 characters long iii) print every character in the alphabet only once

    if (argc != 2)
    {
        (printf("Error: Cipher Key Not Entered\n"));
        exit(1);
    }

    // for loop running through the entire content of the 2nd element ('the cypher key'). If it contains a numerical value the the key is invalid, and program exits.
    for (int i = 0; i < strlen(argv[1]); i++)
    {
        if (isdigit(argv[1][i]))
        {
            printf("Error: Key Contains Numerical Digits\n");
            exit(1);
        }
    }

    // the program exits if the key is not 26 characters in length.
    if (strlen(argv[1]) != 26)
    {
        // 'printf(": %lu \n", strlen(argv[1]));' will return the length of the second element in string array argv[]. This will only work when %lu is used (lu is an UNSIGNED INTEGER). Within the programming manual it states that...
        //  ... size_t strlen (const char *s); where size_t denotes the unsigned integer value.
        printf(": %lu \n", strlen(argv[1]));

        printf("Error: Key Must Contain 26 Characters.\n");
        exit(1);
    }

    else
    // Testing for duplicates. Must also be aware of duplicates which occur which appear but are upper and lower case, i.e Y and y. Declare the 2nd command line string to variable string cyphertext, 'string cyphertext = argv[1];'...
    // ... define the first character of argv[i]. Then define the jth char value for argv[j], which is simply the first/second nth character after character after i. Compare them to see if they are duplicates. Note the toupper   ...
    // ... function works on char values and not strings. Therefore toupper could apply to the char value of string array argv[1][2] but not to the STRING value returned from argv[1].
    {
        for (int i = 0; i < 26; i++)
        {
            for (int j = i + 1; j < 26; j++)
            {
                //printf("i:%i  j: %i\n",i, j);
                //printf("i: %c ", toupper(argv[1][i]));
                //printf("j: %c\n ", toupper(argv[1][j]));
                if (toupper(argv[1][i]) == toupper(argv[1][j]))
                {
                    printf("Error: Key Must Not Contain Duplicates\n");
                    exit(1);
                }
            }
        }
        //printf("Valid Key\n");
    }


    //------------------------------------------------------------------------     PART 2 - Assigning Cypher Key to a CypherText Array ---------------------------------------------------------------------------------------------//




    // create a char array. For ease the system follows the ASCII. 65 relates to A and so on. Therefore an array of 91 is required (26 char + 65 = 91). Unfornately elements 0 to 64 are wasted, I wasn't able to find a way to get around this.
    char cyphertext[91];
    for (int i = 65; i < 91; i++)
    {
        // 'toupper(argv[1][i - 65]);' - The UPPER case cypher key value is required,
        cyphertext[i] = toupper(argv[1][i - 65]);
    }

    // User prompt for text which is to be encripted.
    string usertext = get_string("plaintext: ");


    // Create an array for the users input text to be inserted into the first element, i.e. element 0.
    string plaintext[1];
    plaintext[0] = usertext;

    printf("ciphertext: ");
    for (int i =0; i < strlen(plaintext[0]); i++)
    {
        // if the string input 'hello world' is lower case, then capitalise it with the toupper function as our array linked to the cypher key is all in capitals...
        // We can then print the character after '%c' having returned it back to lower case using tolower.
        if (islower(plaintext[0][i]))
        {
            int ascii_no = toupper(plaintext[0][i]);

            printf("%c", tolower(cyphertext[ascii_no]));
        }

        // for user inputted text which is upper case, we can simply find the integer value of the character in question (the ASCII value), and since the cyphertext[] array is set to receive ASCII values, we can insert it in.
        else if (isupper(plaintext[0][i]))
        {
            int ascii_no = plaintext[0][i];
            printf("%c", cyphertext[ascii_no]);
        }

        // for all other characters, simply print without amending.
        else
        {
            printf("%c", plaintext[0][i]);
        }


    }
printf("\n");
exit(0);


}
