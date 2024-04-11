
#ifndef COMPLEX_H
#define COMPLEX_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "Epsilon.h"


#define LEGAL_ATGUMENTS 3
#define I 'i'
#define POSITIVE 1
#define NEGATIVE -1
#define ZERO 0
//------------------------------------------------------------------------------------------------//

//********      types and functions types
/**
* A struct for Complex numbers. 
*/	
typedef struct Complex
{
    double _real;
    double _imaginary;
}Complex;
		
/**
* A pointer to Complex number. 
*/		
typedef struct Complex* ComplexP;

/**
* A struct of a Complex table.
*/
typedef const struct Complex* ConstComplexP;

//A pointer to a func tha takes two comlex number as arguments and compare between them

typedef int (*compareComplexP)(ConstComplexP, ConstComplexP);

		  
/**
 * @brief create a new complex number
 *   
 * @param s the string that contain the number. the syntax for Complex number is '<double number>,<double number>i'
 * for example : "0,0i","1.878,78i","-768,1i".
 * you can use atof for converting the <double_number>
 * @return ComplexP that is repesneted by the string. if the string do not match the syntax return NULL;
 */
 ComplexP fromCharFunc(char * s)
 {
    double real, imaginary;
    char i = 0, stringEnd = 0;
    ComplexP complex = (Complex*)malloc(sizeof(Complex));
    if(complex == NULL)
    {
        return NULL;
    }
    if(sscanf(s, "%lf,%lf%c%c", &real, &imaginary, &i, &stringEnd) == LEGAL_ATGUMENTS)
    {
        if(i != I || stringEnd != '\0')
        {
            return NULL;
        }
        else
        {
            complex->_real = real;
            complex->_imaginary = imaginary;
        }
        return complex;
    }
    return NULL;
 }
 
 /**
 * @brief a string repesnets the complex number
 *   
 * @param num is the number.
 * @ str - Pointer to a buffer where the resulting C-string is stored.
 *    The buffer should have a size of at least n characters
 * @ n - Maximum number of bytes to be used in the buffer.
 *     The generated string has a length of at most n-1, leaving space for the additional terminating null character.
 * the syntax of the string should be '<double number>,<double number>i'
 * for example : "0,0i","1.878,78i","-768,1i".
 * @return  The number of characters that would have been written if n had been sufficiently large, 
 *  not counting the terminating null character. If an encoding error occurs, a negative number is returned.
 */
int toChar(char * str, int n, ConstComplexP num)
{
    if(str == NULL)
    {
        return NEGATIVE;
    }
    if(sprintf(str, "%lf,%lfi", num->_real, num->_imaginary) < 0)
    {
        return NEGATIVE;
    }
    int strlength = strlen(str);
    if (strlength > n - 1)
    {
        return NEGATIVE;
    }
    return strlen(str);
}




/**
 * @brief free the complex object
 *   
 * @param num is the number. 
 */
void freeComplex(ComplexP num)
{
    free(num);
    num = NULL;
}

/**
 * @brief create a new complex number which is the result of addition num2 to num1.
 *   
 * @param num1 - the first Complex
 * @param num2 - the second Complex
 * @return ComplexP that = num1+num2 . if num1/num2 is NULL return NULL;
 */
 ComplexP add(ConstComplexP num1, ConstComplexP num2)
 {
    ComplexP complex = (Complex*)malloc(sizeof(Complex));
    if(complex == NULL)
    {
        return NULL;
    }   
    if((num1 == NULL) || (num2 == NULL))
    {
        return NULL;
    }
    else 
    {
        complex->_real = num1->_real + num2->_real;
        complex->_imaginary = num1->_imaginary + num2->_imaginary;
    }
    return complex;
 }

 /**
 * @brief create a new complex number which is the result of multiplication of scalar*num1
 *   
 * @param num1 - scalar double number
 * @param num1 - the  Complex
 * @return ComplexP that = scalar*num . if num is NULL return NULL;
 */
 ComplexP multScalar(double scalar, ConstComplexP num)
 {
    if(num == NULL)
    {
        return NULL;
    }
    ComplexP complex = (Complex*)malloc(sizeof(Complex));
    complex->_real = scalar * num->_real;
    complex->_imaginary = scalar * num->_imaginary;
    return complex;
 }

 /**
 * @brief create a new complex number which is the result of multiplication of num1*num2
 *   
 * @param num1 - the first Complex
 * @param num1 - the second Complex
 * @return ComplexP that = num1*num2 . if num1/num2 is NULL return NULL;
 */
ComplexP mult(ConstComplexP num1, ConstComplexP num2)
{
    ComplexP complex = (Complex*)malloc(sizeof(Complex));
    if(complex == NULL)
    {
        return NULL;
    }
    if(complex == NULL)
    {
        return NULL;
    }   
    if((num1 == NULL) || (num2 == NULL))
    {
        return NULL;
    }
    complex->_real = num1->_real * num2->_real - num1->_imaginary * num2->_imaginary;
    complex->_imaginary = num1->_real * num2->_imaginary + num2->_real * num1->_imaginary;

    return complex;
}

/**
 * @brief a function that compare between complex numbers and return a number based on that.
 * @param num1 - Pointer to the first group member
 * @param num2 - Pointer to the second group member
 * @return 0 if |num1 - num2| < EPSILON , 1 if num1 > num2 , -1 if num1 < num2
 */
static int compareComplex(ConstComplexP num1, ConstComplexP num2)
{
    ComplexP negativeNum2 = (Complex*)malloc(sizeof(Complex));
    negativeNum2->_real = NEGATIVE * num2->_real;
    negativeNum2->_imaginary = NEGATIVE * num2->_imaginary;
    ComplexP differenceComp = add(num1, negativeNum2);
    freeComplex(negativeNum2);
    if(differenceComp->_real < EPSILON && differenceComp->_imaginary < EPSILON)
    {
        
        freeComplex(differenceComp);
        return ZERO;
    }
    else
    {
        if(differenceComp->_real != 0)
        {
            if(num1->_real > num2->_real)
            {
                freeComplex(differenceComp);
                return POSITIVE;
            }
            else 
            {
                freeComplex(differenceComp);
                return NEGATIVE;
            }
        }
        else
        {
            if(num1->_imaginary > num2->_imaginary)
            {
                freeComplex(differenceComp);
                return POSITIVE;
            }
            else 
            {
                freeComplex(differenceComp);
                return NEGATIVE;
            }
        }
    }
}




 /**
 * @brief create a pointer to a function that compare complex numbers with EPSILON
 *  function name:getCompareFunc
 * use the lexicographic order, comparing the real parts and then comparing the imaginary ones if the real parts are equal
 * @return a pointer to a function that gets 2 Complex pointers (num1,num2) and return int as following:
 *        0 - iff |num1-num2| <EPSILON
 *        otherwize:
 *                >0 if num1>num2
 *                <0 if num2<num1
 */
 
compareComplexP getCompareFunc(ConstComplexP num1, ConstComplexP num2)
{
    if((num1 == NULL) || (num2 == NULL))
    {
        return NULL;                                                                                                                  
    }
    
    return compareComplex;
          
}

#endif // COMPLEX_H




