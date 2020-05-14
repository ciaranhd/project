# include <stdio.h>
# include <cs50.h>
# include <string.h>
# include <ctype.h>
#include <math.h>

int letters_count(int len, string array[]);
int sentences(int len, string array[]);
int wordcount(int len, string array[]);

int main(void)

{

    //------------------------------------------------------------------------------------------------   PART ONE - RETRIEVING WORD/SENTENCE/LETTER COUNT ----------------------------------------------------------------------------------------


    //len provides the total characters in the string.
    string string_text = get_string("Text: ");
    int len = strlen(string_text);
    //printf("%i\n", len);

    // create the string array str with 1 element and place the text into the 0th element
    string str[1];
    str[0] = string_text;

    // letters_count is a function (see below) which retrieves the total letters within the text.
    float y = letters_count(len, str);

    // letters_count is a function (see below) which retrieves the total sentences within the text.
    int s = sentences(len, str);

    // letters_count is a function (see below) which retrieves the total word count within the text.
    float z = wordcount(len, str);


    //------------------------------------------------------------------------------------------------   PART TWO - IMPLEMENTING ALGORITHM FOR GRADE LEVEL OF A TEXT ----------------------------------------------------------------------------------------

    // The Algorithm is = 0.0588 * average number of words per 100 words - 0.296 * average number of sentences per 100 words - 15.8

    float avg_l = (y/z)*100;

    float avg_s = (s/z)*100;

    // Apply the above to the algorithm below and round to the nearest whole number
    int index = round(0.0588 * avg_l - 0.296 * avg_s - 15.8);


    //------------------------------------------------------------------------------------------------   PART THREE - IF FUNCTIONS FOR PRINT STATEMENTS FOR GRADE LEVELS ----------------------------------------------------------------------------------------

    if (index >= 1 && index <= 15)
    {
        printf("Grade %i\n", index);
    }

    else if (index < 0)
    {
        printf("Before Grade 1\n");
    }
    else
    {
        printf("Grade 16+\n");
    }
}

    //------------------------------------------------------------------------------------------------   END OF MAIN() ----------------------------------------------------------------------------------------

    //------------------------------------------------------------------------------------------------   PART FOUR - FUNCTIONS OUTWITH MAIN() ----------------------------------------------------------------------------------------


    //------------------------------------------------------------------------------------------------   FUNCTION ONE - Letters Count----------------------------------------------------------------------------------------


int count = 0;
int letters_count(int len, string array[])
{
    // returns the char value which is tested for being an aphabetical letter. If yes, then the word count is increased incrementally.
    for (int i = 0; i < len; i ++)
    {
        char x = array[0][i];
        if (isalpha(x))
        {
            count = count + 1;
            //printf("%c", x);
        }
    }

    return count;
}


    //------------------------------------------------------------------------------------------------   FUNCTION TWO - Sentence Count----------------------------------------------------------------------------------------

int sentence_count = 0;
int sentences(int len, string array[])
{
    // we are looking for full stops, exclamations marks and question marks only as proxy's for when a sentence ends...
    // converting the char to its integer ASCII value and then querying it using the if statement. i.e. 46, 33 and  ...
    // 63 relate to full stops, question marks etc.
    for (int i = 0; i < len; i ++)
    {
        int x = array[0][i];
        //printf("%i\n", x);
        if (x == 46 || x == 33 || x == 63)
        {
            sentence_count = sentence_count + 1;
        }
    }

    return sentence_count;
}

    //------------------------------------------------------------------------------------------------   FUNCTION Three - Word Count----------------------------------------------------------------------------------------

int word_count = 1;
int wordcount(int len, string array[])
{
    // we must begin from 1 as we assume the first word in the sentence will always be word or number. There are some ...
    // sentences which have double spaces, therefore I have used the logic that every word starts when there is a     ...
    // a space followed by an aphabetical/numerical/punctuation character. e.g (I said   "yes") ...has, starting      ...
    // ... from one, two instances of a space followed by the criteria above. 1 + 2 = 3 words.

    for (int i = 0; i < len; i ++)
    {
        char x = array[0][i];
        if (isspace(x))
        {
            char y = array[0][i + 1];
            if (isalnum(y) || ispunct(y))
            {
                //printf("new word");
                word_count = word_count + 1;
            }
        }
    }

    return word_count;
}

//------------------------------------------------------------------------------------------------   END ----------------------------------------------------------------------------------------



