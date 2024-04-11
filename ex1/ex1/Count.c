/*
 * Count.c
 *
 *  Created on: Oct 24, 2015
 *  Author: Rani
 *  user: rani.aboraya
 *  id: 316396787
 */
#include <stdio.h>

/**
* @brief The main function
* @param no parameters is taken
* @return return 0 if the code works
* @output to count the characters,words and lines
*/
int main()
{
	char ch, prev = ' ';
	int rows = 0, words = 0, characters = 0;
	while ((ch = fgetc(stdin)) != EOF)
	{
	    if (ch == ' ' && prev != ' ')
	    {
            words++;           
	    }
	    else if (ch == '\n' && prev != ' ')
	    {
            words++; 
        }     
        if (ch == '\n')
        {
            rows++;
        }
    characters++;
    prev = ch; 
    }
    rows++;
	printf("Num of rows:%d words:%d characters:%d\n", rows, words, characters);
	return 0;

}



