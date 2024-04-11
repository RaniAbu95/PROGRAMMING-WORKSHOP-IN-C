/*
 * Count.c
 *
 *  Created on: Oct 24, 2015
 *  Author: Rani
 *  user: rani.aboraya
 *  id: 316396787
 */

#include <stdio.h>
#define LATERS_NUM 26
#define NUMBERS_AMOUNT 10
#define A_SAMLL 97
#define A_CAPITAL 65
#define Z_SMALL 122
#define Z_CAPITAL 90
#define ZERO 48
#define NINE 57
#define MAXIMAL_SHIFT 50
#define MINIMAL_SHIFT 0
#define MAX_INPUT_LENGTH 100
#define DECRYPT 'd'
#define ENCRYPT 'e'

/**
*@brief Decrypt the given char
* @param shift the offset for decrypt
* @param c the char to decrypt
* @return the decrypted char
*/
 char decrypt(int shift, char c)
 {
    int difference = c - shift, shifted_Char;
    if ((c >= A_SAMLL) && (c <= Z_SMALL))
    {
        shift = shift % LATERS_NUM; 
        if (difference < A_SAMLL)
        {
            shifted_Char = Z_SMALL - (A_SAMLL - difference) + 1;
        }
        else
        {
            shifted_Char = c - shift;
        }
    }
    else if ((c >= A_CAPITAL) && (c <= Z_CAPITAL))
    {
        shift = shift % LATERS_NUM;
        if (difference < A_CAPITAL)
        {
            shifted_Char = Z_CAPITAL - (A_CAPITAL - difference) + 1;
        }
        else
        {
            shifted_Char = c - shift;
        }
    }
    else if ((c >= ZERO) && (c <= NINE))
    {
        shift = shift % NUMBERS_AMOUNT;
        if (difference < ZERO)
        {
            shifted_Char = NINE - (ZERO - difference) + 1;
        }
        else
        {
            shifted_Char = c - shift;
        }
    }
    else
    {
        shifted_Char = c;
    }

    return shifted_Char;

 }
 
/**
* @brief Encrypt the given char
* @param c the char to encrypt
* @param shift the offset for encrypt
* @return encrypted char
*/
 char encrypt(int shift, char c)
 {
    int shifted_Char;
    if ((c >= A_SAMLL) && (c <= Z_SMALL))
    {
        shift = shift % LATERS_NUM;
        if (c + shift > Z_SMALL)
        {
            shifted_Char = A_SAMLL + ((c + shift) - Z_SMALL) - 1;
        }
        else
        {
            shifted_Char = c + shift;
        }
    }

    else if ((c >= A_CAPITAL) && (c <= Z_CAPITAL))
    {
        shift = shift % LATERS_NUM;
        if (c + shift > Z_CAPITAL)
        {
            shifted_Char = A_CAPITAL + ((c + shift) - Z_CAPITAL) - 1;
        }
        else
        {
            shifted_Char = c + shift;
        }
    }

    else if ((c >= ZERO) && (c <= NINE))
    {
        shift = shift % NUMBERS_AMOUNT;
        if (c + shift > NINE)
        {
            shifted_Char = ZERO + ((c + shift) - NINE) - 1;
        }
        else
        {
            shifted_Char = c + shift;
        }
    }

    else
    {
        shifted_Char = c;
    }

    return shifted_Char;
 }

/**
* @brief the main function
* @param no parameters is taken
* @return return 0 if the code works
* @output decrypt/encrypt all the chars of the string based on the user choose
*/
int main()
{
 int move, i;
 char decoding_Type, str[100], output[100];

 printf("Please enter the shift amount:\n");
 scanf("%d", &move);

 while ((move < MINIMAL_SHIFT) || (move > MAXIMAL_SHIFT))
 {
    printf("ERROR: Shift amount should be number between 0 to 50 please enter the shift amount\n");
    scanf("%d", &move);
 }
 
 printf("Would you like to encrypt (e) or decrypt (d)?\n");
 getchar();
 decoding_Type = getc(stdin);
 getchar();
 
 while ((decoding_Type != ENCRYPT) && (decoding_Type != DECRYPT))
 {
    printf("ERROR: You should type e or d Would you like to encrypt (e) or decrypt (d)?\n");
    decoding_Type = getc(stdin);
 }

 fgets(str, MAX_INPUT_LENGTH + 1, stdin);
 
 for (i = 0; i < MAX_INPUT_LENGTH; i++)
 {
    if (str[i] == '\n')
    {
        str[i] = '\0';
        output[i] = '\0';
        break;
    }
    if(str[0] == 'd')
    {
        output[i] = decrypt(move, str[i]);
    }
    else
    {
        output[i] = encrypt(move, str[i]);
    }
 }
 printf("\"%s\" -> \"%s\"\n", str, output);

 return 0;
}


