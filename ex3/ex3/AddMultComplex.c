#include <stdio.h>
#include "Complex.h"
#include <stdlib.h>
#define N 25

typedef void * GroupMemberP;
typedef int (*compareComplexP)(ConstComplexP, ConstComplexP);


/**
 * @brief create a new complex number which is the result of addition member1 to member2.
 * @param member1 - the first group member
 * @param member2 - the second group member
 * @return GroupMemberP that = member1 + member2 . if member1/member2 is NULL return NULL;
 */
GroupMemberP addComplex(GroupMemberP member1, GroupMemberP member2)
{
    ComplexP complex1 = fromCharFunc(member1);
    ComplexP complex2 = fromCharFunc(member2);
    ComplexP newMember = add(complex1, complex2);
    char *ComplexString = (char*) malloc(sizeof(char) * N);
    if(toChar(ComplexString, N, newMember) < 0)
    {
        return NULL;
    }
    freeComplex(complex1);
    freeComplex(complex2);
    freeComplex(newMember);
    return ComplexString;
}

/**
 * @brief create a new complex number which is the result of multiplication member1 with member2.
 * @param member1 - the first group member
 * @param member2 - the second group member
 * @return GroupMemberP that = member1 * member2 . if member1/member2 is NULL return NULL;
 */
GroupMemberP multComplex(GroupMemberP member1, GroupMemberP member2)
{
    ComplexP complex1 = fromCharFunc(member1);
    ComplexP complex2 = fromCharFunc(member2);
    ComplexP newMember = mult(complex1, complex2);
       
    char *ComplexString = (char*) malloc(sizeof(char) * N);
    if(toChar(ComplexString, N, newMember) < 0)
    {
        return NULL;
    }
    freeComplex(complex1);
    freeComplex(complex2);
    freeComplex(newMember);
    return ComplexString;
    
}
/**
 * @brief a function that compare between complex numbers and return a number based on that.
 * @param member1 - the first group member
 * @param member2 - the second group member
 * @return 0 if |member1 - member2| < EPSILON , 1 if member1 > member2 , -1 if member1 < member2
 */
int compareMembers(GroupMemberP member1, GroupMemberP member2)
{
    ComplexP complex1 = fromCharFunc(member1);
    ComplexP complex2 = fromCharFunc(member2);
    compareComplexP getComplexDiff = getCompareFunc(complex1, complex2);
    int result = getComplexDiff(complex1 , complex2);
    freeComplex(complex1);
    freeComplex(complex2);
    return result;
}


