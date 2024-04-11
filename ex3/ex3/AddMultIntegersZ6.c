#include <stdio.h>
#include "Complex.h"
#include <stdlib.h>
#include "Epsilon.h"

#define SIX 6
#define ZERO 0
#define POSITIVE 1
#define NEGATIVE -1

typedef void * GroupMemberP;
typedef int (*intP);

/**
 * @brief create a new int GroupMember number which the result of the add operation in Z6
 * @param member1 - the first group member
 * @param member2 - the second group member
 * @return GroupMemberP that = (member1 + member2) % 6 . if member1/member2 is NULL return NULL;
 */
GroupMemberP addIntegersZ6(GroupMemberP member1, GroupMemberP member2)
{
    if(member1 == NULL || member2 == NULL)
    {
        return NULL;
    }
    int num1 = *((int*)member1);
    int num2 = *((int*)member2);
    int result = (num1 + num2) % SIX;
    int* newNum = (int*) malloc(sizeof(int));
    *newNum = result;
    return newNum;
}
/**
 * @brief create a new int GroupMember number which the result of the multiplication operation in Z6
 * @param member1 - the first group member
 * @param member2 - the second group member
 * @return GroupMemberP that = (member1 * member2) % 6 . if member1/member2 is NULL return NULL;
 */
 
GroupMemberP multIntegersZ6(GroupMemberP member1, GroupMemberP member2)
{
    if(member1 == NULL || member2 == NULL)
    {
        return NULL;
    }
    int num1 = *((int*)member1);
    int num2 = *((int*)member2);
    int result = (num1 * num2) % SIX;
    int* newNum = (int*) malloc(sizeof(int));
    *newNum = result;
    return newNum;
}

/**
 * @brief a function that comparesbetween two ints numbers and return a number based on that.
 * @param member1 - the first group member
 * @param member2 - the second group member
 * @return 0 if member1 = member2 , 1 if member1 > member2 , -1 if member1 < member2
 */
 
int compareIntegersZ6(GroupMemberP member1, GroupMemberP member2)
{
    int num1 = *((int*)member1);
    int num2 = *((int*)member2);
    if(num1 == num2)
    {
        return ZERO;
    }
    else if(num1 > num2)
    {
        return POSITIVE; 
    }
    else 
    {
        return NEGATIVE;
    }
    
}

