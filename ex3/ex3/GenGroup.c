


#ifndef GENGROUP_H
#define GENGROUP_H


#include <stdbool.h>
#include  "Epsilon.h"
#include <stdio.h>
#include <string.h>

//********      types and functions types
/**
* A pointer to group number/member. 
*/

typedef void * GroupMemberP;
typedef const void * ConstGroupMemberP;
typedef GroupMemberP (*FuncP)(GroupMemberP); 
typedef GroupMemberP (*addP)(GroupMemberP, GroupMemberP);
typedef int (*CompareFuncP)(GroupMemberP, GroupMemberP);
typedef void (*freeMemberP)(GroupMemberP);
typedef GroupMemberP (*operFuncP)(GroupMemberP, GroupMemberP);

//**************************
// functions to implement.


/**
 * @brief return the result of add(f(n),g(n))
 *   function name:addFunctions  
 * @param add pointer to A function that gets 2 GroupMemberP objects and return a GroupMemberP that is the result of the an opreation  on them.
 * @param f pointer to A function that gets a GroupMemberP and return a GroupMemberP
 * @param g pointer to A function that gets a GroupMemberP and return a GroupMemberP
 * @param n A  GroupMemberP 
 * @param freeMember pointer to A function that get GroupMemberP and frees it from memory.
 * @return the result of add(f(n),g(n)).  In case of an error return NULL.
 * Complexity runtime : O(1)
 */

GroupMemberP addFunctions(addP add, FuncP f, FuncP g, GroupMemberP n, freeMemberP freeMember)
{
    if((add != NULL) && (f != NULL) && (g != NULL) && (n != NULL))
    {
        GroupMemberP funcSum = add(f(n), g(n));
        if(funcSum == NULL)
        {
            freeMember(f(n));
            freeMember(g(n));
            return NULL;
        }
        else
        {
            freeMember(f(n));
            freeMember(g(n));
            return funcSum;
        }
    }
    return NULL;
}



/**
 * @brief return the result of f(g(n))
 *   function name:composeFunctions
 * @param f pointer to A function that gets a GroupMemberP and return a GroupMemberP
 * @param g pointer to A function that gets a GroupMemberP and return a GroupMemberP
 * @param n A  GroupMemberP 
 * @param freeMember pointer to A function that get GroupMemberP and frees it from memory.
 * @return the result of f(g(n)).  In case of an error return NULL.
 * Complexity runtime : O(1)
 */

GroupMemberP composeFunctions(FuncP f, FuncP g, GroupMemberP n, freeMemberP freeMember)
{
    if((f != NULL) && (g != NULL) && (n != NULL))
    {
        GroupMemberP funcCompose = f(g(n));
        if(funcCompose != NULL)
        {
            freeMember(g(n));
            return funcCompose;
        }
        else 
        {
            freeMember(g(n));
            return NULL;
        }
    }
    else
    {
        return NULL;
    } 
}
/**
 * @brief a function that checks if A member belongs to the group
 * @param members[] Pointer to an array that contains all the group members
 * @param membersLen Number of members in the group
 * @param member Pointer to the member to check  
 * @param compare Pointer to A function that get two GroupMembers members and return the difference.
 * @return True if the member is within the group, false otherwise
 * Complexity runtime : O(N)
 */
static bool isInGroup(GroupMemberP members[], int membersLen, GroupMemberP member, CompareFuncP compare)
{
   for(int i = 0; i < membersLen; i++)
   {
        if(compare(members[i], member) == 0)
        {
            return true;
        }
   }
   return false;
     
}

/**
 * @brief check if the given arguments define a an Abelian Group 
 * you should follow the definition of Abelian group -  see https://en.wikipedia.org/wiki/Abelian_group.
 * if some arguments are NULL print the following error message to stderr : "Error : <argument_name> is NULL\n"
 *   
 * @param IdentityElement - The identity element.
 * @param members A struct of GroupMemberP which contain ALL the group members (including IdentityElement).
 * @param membersLen The length of members.
 * @param oper pointer to A function that gets 2 GroupMemberP objects and return a GroupMemberP that is the result of the opreation  on them.
 * @param freeMember pointer to A function that get GroupMemberP and frees it from memory.
 * @param compare pointer to A function that gets 2 GroupMemberP objects and return int >0 iff the first is bigger; 
            <0 if the second is bigger; and 0 iff they are equal(i.e. the diffrents beetween the diffrent between them is <EPSILON).
 * @return true iff the pramters an Abelian Group group.  In case of an error return false.
 * Complexity runtime : O(N^3)
 */
 
bool isAbelianGroup(GroupMemberP IdentityElement, GroupMemberP members[], int membersLen, operFuncP oper, freeMemberP freeMember, CompareFuncP compare)
{
        GroupMemberP EquationA, EquationB, EquationC, EquationD, EquationE, EquationF, EquationG, EquationH;
        if(IdentityElement == NULL || members == NULL || oper == NULL || freeMember == NULL || compare == NULL)
        {
            return false;
        }
        int i, j, k;
        bool flag = false;
        for(i = 0; i < membersLen; i++)
        {
           
           //check for the existence of the identity element
           EquationA = oper(members[i], IdentityElement);
           EquationB = oper(IdentityElement, members[i]);
           if(compare(EquationA, EquationB) != 0 || compare(EquationA, members[i]) !=0)
           {

                freeMember(EquationA);
                freeMember(EquationB);
                return false;
           }
           freeMember(EquationA);
           freeMember(EquationB);
           for(j = 0; j < membersLen; j++) 
           {
                
               //check for the existence of the inverse member 
               EquationC = oper(members[i], members[j]);
               EquationD = oper(members[j], members[i]);
               //check for multiplication closure
               if(!isInGroup(members, membersLen, EquationC, compare))
               {
                    freeMember(EquationC);
                    freeMember(EquationD);
                    
                    return false;
               }
               //check if for each group member there is an inverse member
               else if(compare(EquationC, EquationD) == 0 && compare(EquationC, IdentityElement) == 0)
               {
                   flag = true; 
               }
               //check for commutativity attribute
               else if(compare(EquationC, EquationD) != 0)
               {
                    freeMember(EquationC);
                    freeMember(EquationD);
                    return false;
               }
               freeMember(EquationC);
               freeMember(EquationD);
               for(k = 0; k < membersLen; k++)
               {
                    EquationE = oper(members[j], members[k]);
                    EquationF = oper(members[i], members[j]);
                    EquationG = oper(members[i], EquationE);
                    EquationH = oper(EquationF, members[k]);
                    //check for associativity attribute
                    if(compare(EquationG, EquationH) != 0)
                    {
                        freeMember(EquationF);
                        freeMember(EquationE);
                        freeMember(EquationG);
                        freeMember(EquationH);
                        return false;
                    }
                    freeMember(EquationF);
                    freeMember(EquationE);
                    freeMember(EquationG);
                    freeMember(EquationH); 
               }
               
           }
           
           
           if(!flag)
           {
                return false;
           }
        
        }
        return true;
} 


#endif // GENGROUP_H

