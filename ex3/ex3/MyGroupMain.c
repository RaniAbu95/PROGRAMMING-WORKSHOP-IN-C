
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Epsilon.h"
#include "Complex.h"
#include "GenGroup.h"
#include "AddMultComplex.c"
#include "AddMultIntegersZ6.c"

#define FOUR 4 
#define SIX 6
#define ZERO 0

typedef void *GroupMemberP;

/**
 * @brief free the GroupMember object
 *   
 * @param member is the member to free. 
 */
void freeMember(GroupMemberP member)
{
    free(member);
    member = NULL;
}

// My first group example
void exampleForGroup1()
{
    char * member1 =  "1,0i";
    char * member2 =  "0,1i";
    char * member3 =  "-1,0i";
    char * member4 =  "0,-1i";
    GroupMemberP members[FOUR] = {member1, member2, member3, member4};
    int n = sizeof(members) / sizeof(GroupMemberP);
    bool abelian = false;    
    if(isAbelianGroup(members[ZERO], members, n, multComplex, freeMember, compareMembers))
    {
        abelian = true;
    }
    printf("//////////////////\n");
    printf("Complex Group with regular Complex multiplication function:\n");
    printf("Identity member: %s\n", member1);
    printf("Group members: %s ; %s ; %s ; %s\n", member1, member2, member3, member4);
    if(abelian)
    {
        printf("This is an Abelian group\n");
    }
    else 
    {
        printf("This is not Abelian group\n");
    }
    printf("//////////////////\n");
}
// My second group example
void exampleForGroup2()
{
    char * first =  "1,5i";
    char * second =  "4,3i";
    char * third =  "-3,2i";
    char * forth =  "-1,100i";
    GroupMemberP groupMembers[FOUR] = {first, second, third, forth};
    int n = sizeof(groupMembers) / sizeof(GroupMemberP);
    bool abelian = false;
    if(isAbelianGroup(groupMembers[ZERO], groupMembers, n, addComplex, freeMember, compareMembers))
    {
        abelian = true;
    }
    printf("//////////////////\n");
    printf("Complex Group with regular Complex add function:\n");
    printf("Identity member: %s\n", first);
    printf("Group members: %s ; %s ; %s ; %s\n", first, second, third, forth);
    if(abelian)
    {
        printf("This is an Abelian group\n");
    }
    else
    {
        printf("This is not Abelian group\n");
    }
    printf("//////////////////\n"); 
}
// My third group example
void exampleForGroup3()
{
    int myMember1 = 0;
    int myMember2 = 1;
    int myMember3 = 2;
    int myMember4 = 3;
    int myMember5 = 4;
    int myMember6 = 5;
    GroupMemberP myMembers[SIX] = {&myMember1, &myMember2, &myMember3, &myMember4, &myMember5, &myMember6};
    int n = sizeof(myMembers) / sizeof(GroupMemberP);
    bool abelian = false;
    if(isAbelianGroup(myMembers[ZERO], myMembers, n, addIntegersZ6, freeMember, compareIntegersZ6))
    {
        abelian = true;
    }
    printf("//////////////////\n");
    printf("int Group with the add operation in Z6 :\n");
    printf("Identity member: %d\n", myMember1);
    printf("Group members: %d ; %d ; %d ; %d ; %d ; %d\n", myMember1, myMember2, myMember3, 
                                                                   myMember4, myMember5, myMember6);
    if(abelian)
    {
        printf("This is an Abelian group\n");
    }
    else
    {
        printf("This is not Abelian group\n");
    }
    printf("//////////////////\n");
   
}
// My forth group example
void exampleForGroup4()
{
    int myFirstMem = 0;
    int mySecondMem = 1;
    int myThirdMem = 2;
    int myForthMem = 3;
    GroupMemberP Members[FOUR] = {&myFirstMem, &mySecondMem, &myThirdMem, &myForthMem};
    int n = sizeof(Members) / sizeof(GroupMemberP);
    bool abelian = false;
    if(isAbelianGroup(Members[ZERO], Members, n, multIntegersZ6, freeMember, compareIntegersZ6))
    {
        abelian = true;
    }
    printf("//////////////////\n");
    printf("int Group with the mult operation in Z6 :\n");
    printf("Identity member: %d\n", myFirstMem);
    printf("Group members: %d ; %d ; %d ; %d\n", myFirstMem, mySecondMem, myThirdMem, myForthMem);
    if(abelian)
    {
        printf("This is an Abelian group\n");
    }
    else
    {
        printf("This is not Abelian group\n");
    }
    printf("//////////////////\n");
}

//the main function that runs all of my groups examples
int main()
{
    exampleForGroup1();
    exampleForGroup2();
    exampleForGroup3();
    exampleForGroup4();
    return 0; 
}
