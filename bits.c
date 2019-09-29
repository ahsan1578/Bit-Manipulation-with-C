/* 
 * CS:APP Data Lab 
 * 
 * <Please put your name and userid here>
 * 
 * bits.c - Source file with your solutions to the Lab.
 *          This is the file you will hand in to your instructor.
 *
 * WARNING: Do not include the <stdio.h> header; it confuses the dlc
 * compiler. You can still use printf for debugging without including
 * <stdio.h>, although you might get a compiler warning. In general,
 * it's not good practice to ignore compiler warnings, but in this
 * case it's OK.  
 */

#if 0
/*
 * Instructions to Students:
 *
 * STEP 1: Read the following instructions carefully.
 */

You will provide your solution to the Data Lab by
editing the collection of functions in this source file.

INTEGER CODING RULES:
 
  Replace the "return" statement in each function with one
  or more lines of C code that implements the function. Your code 
  must conform to the following style:
 
  int Funct(arg1, arg2, ...) {
      /* brief description of how your implementation works */
      int var1 = Expr1;
      ...
      int varM = ExprM;

      varJ = ExprJ;
      ...
      varN = ExprN;
      return ExprR;
  }

  Each "Expr" is an expression using ONLY the following:
  1. Integer constants 0 through 255 (0xFF), inclusive. You are
      not allowed to use big constants such as 0xffffffff.
  2. Function arguments and local variables (no global variables).
  3. Unary integer operations ! ~
  4. Binary integer operations & ^ | + << >>
    
  Some of the problems restrict the set of allowed operators even further.
  Each "Expr" may consist of multiple operators. You are not restricted to
  one operator per line.

  You are expressly forbidden to:
  1. Use any control constructs such as if, do, while, for, switch, etc.
  2. Define or use any macros.
  3. Define any additional functions in this file.
  4. Call any functions.
  5. Use any other operations, such as &&, ||, -, or ?:
  6. Use any form of casting.
  7. Use any data type other than int.  This implies that you
     cannot use arrays, structs, or unions.

 
  You may assume that your machine:
  1. Uses 2s complement, 32-bit representations of integers.
  2. Performs right shifts arithmetically.
  3. Has unpredictable behavior when shifting an integer by more
     than the word size.

EXAMPLES OF ACCEPTABLE CODING STYLE:
  /*
   * pow2plus1 - returns 2^x + 1, where 0 <= x <= 31
   */
  int pow2plus1(int x) {
     /* exploit ability of shifts to compute powers of 2 */
     return (1 << x) + 1;
  }

  /*
   * pow2plus4 - returns 2^x + 4, where 0 <= x <= 31
   */
  int pow2plus4(int x) {
     /* exploit ability of shifts to compute powers of 2 */
     int result = (1 << x);
     result += 4;
     return result;
  }

FLOATING POINT CODING RULES

For the problems that require you to implent floating-point operations,
the coding rules are less strict.  You are allowed to use looping and
conditional control.  You are allowed to use both ints and unsigneds.
You can use arbitrary integer and unsigned constants.

You are expressly forbidden to:
  1. Define or use any macros.
  2. Define any additional functions in this file.
  3. Call any functions.
  4. Use any form of casting.
  5. Use any data type other than int or unsigned.  This means that you
     cannot use arrays, structs, or unions.
  6. Use any floating point data types, operations, or constants.


NOTES:
  1. Use the dlc (data lab checker) compiler (described in the handout) to 
     check the legality of your solutions.
  2. Each function has a maximum number of operators (! ~ & ^ | + << >>)
     that you are allowed to use for your implementation of the function. 
     The max operator count is checked by dlc. Note that '=' is not 
     counted; you may use as many of these as you want without penalty.
  3. Use the btest test harness to check your functions for correctness.
  4. Use the BDD checker to formally verify your functions
  5. The maximum number of ops for each function is given in the
     header comment for each function. If there are any inconsistencies 
     between the maximum ops in the writeup and in this file, consider
     this file the authoritative source.

/*
 * STEP 2: Modify the following functions according the coding rules.
 * 
 *   IMPORTANT. TO AVOID GRADING SURPRISES:
 *   1. Use the dlc compiler to check that your solutions conform
 *      to the coding rules.
 *   2. Use the BDD checker to formally verify that your solutions produce 
 *      the correct answers.
 */


#endif
/* Copyright (C) 1991-2016 Free Software Foundation, Inc.
   This file is part of the GNU C Library.

   The GNU C Library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Lesser General Public
   License as published by the Free Software Foundation; either
   version 2.1 of the License, or (at your option) any later version.

   The GNU C Library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Lesser General Public License for more details.

   You should have received a copy of the GNU Lesser General Public
   License along with the GNU C Library; if not, see
   <http://www.gnu.org/licenses/>.  */
/* This header is separate from features.h so that the compiler can
   include it implicitly at the start of every compilation.  It must
   not itself include <features.h> or any other header that includes
   <features.h> because the implicit include comes before any feature
   test macros that may be defined in a source file before it first
   explicitly includes a system header.  GCC knows the name of this
   header in order to preinclude it.  */
/* glibc's intent is to support the IEC 559 math functionality, real
   and complex.  If the GCC (4.9 and later) predefined macros
   specifying compiler intent are available, use them to determine
   whether the overall intent is to support these features; otherwise,
   presume an older compiler has intent to support these features and
   define these macros by default.  */
/* wchar_t uses Unicode 8.0.0.  Version 8.0 of the Unicode Standard is
   synchronized with ISO/IEC 10646:2014, plus Amendment 1 (published
   2015-05-15).  */
/* We do not support C11 <threads.h>.  */
/* 
 * allEvenBits - return 1 if all even-numbered bits in word set to 1
 *   Examples allEvenBits(0xFFFFFFFE) = 0, allEvenBits(0x55555555) = 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 2
 */
int allEvenBits(int x) {
   //Principle behind the solution is:
        //If we do x|y where all odd bits in y are 1, we should get all bits 1 integer given all even bits in x are 1
        //That is, we should have 0xFFFFFFFF
        //not (~) of that should be all zeroes and not (!) of the all zeroes should be one
        //If all even bits in x were not 1 to start with, the ~(x|y) will not be all zeroes
        //so !(~(x|y) will be 0


        //As we are not allowed to have constants more than 8 bits let's create a variable 0xAA
        //0xAA = 10101010 in banary
        //Left shift and add the same 0xAA 4 times to get all odd bits 1

        int eightBitAllOddOne = 0xAA;
        int allOddBitOne =((((((eightBitAllOddOne<<8)+eightBitAllOddOne)<<8)+eightBitAllOddOne)<<8)+eightBitAllOddOne);
        return !(~(x|allOddBitOne));

}
/*
 * bitParity - returns 1 if x contains an odd number of 0's
 *   Examples: bitParity(5) = 0, bitParity(7) = 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 20
 *   Rating: 4
 */
int bitParity(int x) {
  //Principles used to solve the problem
  //odd number or 0s means odd number of 1s
  //xor-ing with partitioning the bits in the middle will always give odd number of 1s
  //if there were odd number of ones to start with
  int leftZeroes = (0xFF<<8)+0xFF;
  int sixteenBit1 = x & leftZeroes;
  int sixteenBit2 = (leftZeroes)&(x>>16);

  int sixteenBit = sixteenBit1 ^ sixteenBit2;

  int eightBit1 = sixteenBit & 0xFF;
  int eightBit2 = sixteenBit>>8;

  int eightBit = eightBit1 ^ eightBit2;

  int fourBit1 = eightBit & 0xF;
  int fourBit2 = eightBit>>4;

  int fourBit = fourBit1 ^ fourBit2;

  int twoBit1 = fourBit & 0x3;
  int twoBit2 = fourBit >> 2;

  int twoBit = twoBit1^twoBit2;

  int bit1 = twoBit & 1;
  int bit2 = twoBit>>1;

  return bit1^bit2;

}
/* 
 * bitXor - x^y using only ~ and & 
 *   Example: bitXor(4, 5) = 1
 *   Legal ops: ~ &
 *   Max ops: 14
 *   Rating: 1
 */
int bitXor(int x, int y) {
  	//A xor B = (~A & B) | (A & ~B)
        //Use De Morgan's law ~(A and B) = ~A or ~B
        //which follows ~(~A and ~B) = ~(~A) or ~(~B) = A or B
        //our A = ~x & y, B = x & ~B
        //so (~x & y)|(x & ~y) = the following expression
        return ~(~(~x & y) & ~(~y & x));
}
/* 
 * replaceByte(x,n,c) - Replace byte n in x with c
 *   Bytes numbered from 0 (LSB) to 3 (MSB)
 *   Examples: replaceByte(0x12345678,1,0xab) = 0x1234ab78
 *   You can assume 0 <= n <= 3 and 0 <= c <= 255
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 10
 *   Rating: 3
 */
int replaceByte(int x, int n, int c) {
  	//We take the byte that we are going to replace with in nth byte position in an int
        int byteToPut = c<<(8*n);

        //We will make all the bits at the current n-th byte to zero
        //To do this first we are taking help of an int with all zeroes in nth byte
        //and the other bits will be ones
        //First take FF to the nth position and xor with all ones(~0)
        int helperInt = (~0)^((0xFF)<<8*n);

        //Anding the helper int will make all bits in nth byte zeroes
        int xWithZeroesInN_thByte = x & helperInt;

        //or-ing with the new byte in right position will give us the final int
        return xWithZeroesInN_thByte|byteToPut;
}
/* 
 * TMax - return maximum two's complement integer 
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 4
 *   Rating: 1
 */
int tmax(void) {
 	//We know max two's compliment will have zero as sign bit and rest bits ones
        //We take all ones (~0) and xor with an int that has sign bit one and rest of the bits zeroes
        return (~0 ^(1<<31));
}
/* 
 * fitsBits - return 1 if x can be represented as an 
 *  n-bit, two's complement integer.
 *   1 <= n <= 32
 *   Examples: fitsBits(5,3) = 0, fitsBits(-4,3) = 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 15
 *   Rating: 2
 */
int fitsBits(int x, int n) {
  	//Principle: We have to keep only one sign bit and
        //we can strip all the other sign bits
        //That will give us the minimun number of bits we need
        //So if we can show that from nth position all the bits to left is same as sign bit
        //that means x fits in n bits
        //So we show nth bit same as sign bit
        //All the bits to left is same and sign bit
        int signBit = (x>>31)&1;
        int nthBit = ((x<<1)>>n)&1;
        int striped_n_bits = x>>n;
        int allSignBit = x>>31;
        return !(signBit ^ nthBit) & !(striped_n_bits ^ allSignBit);

}
/* 
 * isEqual - return 1 if x == y, and 0 otherwise 
 *   Examples: isEqual(5,5) = 1, isEqual(4,5) = 0
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 5
 *   Rating: 2
 */
int isEqual(int x, int y) {
  	//If x and y have same bit pattern, their xor will be 0
        return !(x^y);
}
/* 
 * isPositive - return 1 if x > 0, return 0 otherwise 
 *   Example: isPositive(-1) = 0.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 8
 *   Rating: 3
 */
int isPositive(int x) {
  	//We just need to check sign bit
        //And-ng with int that has all 0s except the sign bit(which is 1) will give us the sign bit
        //Positive when sign bit is zero, that is return not of sign bit
        return !(x&(1<<31));
}
/* 
 * subOK - Determine if can compute x-y without overflow
 *   Example: subOK(0x80000000,0x80000000) = 1,
 *            subOK(0x80000000,0x70000000) = 0, 
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 20
 *   Rating: 3
 */
int subOK(int x, int y) {
  	int negY = (~y)+1;

        //Special case: if x and y both are 0x80000000, their sign doesn't change for negation
        //overflow doesn't occure either

        int specialNum = 1<<31;
        int isSpecialCase = (!(x^specialNum))&(!(y^specialNum));


        int signNegY = (negY>>31)&1;
        int signX = (x>>31)&1;
        int signXnegY = ((x+negY)>>31)&1;

        //If sign bits are different, that means no overflow
        int isDiffSign = signX ^ signNegY;

        //If sign bits are same x-y must have same sign bit to not overflow
        return isSpecialCase | isDiffSign | !(signX ^ signXnegY);

}
/* howManyBits - return the minimum number of bits required to represent x in
 *             two's complement
 *  Examples: howManyBits(12) = 5
 *            howManyBits(298) = 10
 *            howManyBits(-5) = 4
 *            howManyBits(0)  = 1
 *            howManyBits(-1) = 1
 *            howManyBits(0x80000000) = 32
 *  Legal ops: ! ~ & ^ | + << >>
 *  Max ops: 90
 *  Rating: 4
 */
int howManyBits(int x) {
  int allSignBit = x>>31;
  int withLeftZeroes = allSignBit ^ x;


  //Now we need to find the position of first occurence of 1 from left
  //Then we shall add to that position number which is the sign bit


  //We use divide and conquer process
  //First we check the left most 16 bits
  //If there is a 1 in left most 16 bit we don't need to check the right 16 bits
  //We check the left the left most 8 bit in that case
  //If there is no one in the left most 16 bits, we check the right 16 bits (left most 8 bits of right 16 bits which if bit index 8 to 15)
  //We continue the process until we get down to 1 bit


  int left16 =(!(!(withLeftZeroes>>16)))<<4;
  //if there was a 1 in left 16 bits, the left16 should give us value 16, otherwise 0
  //Now we right shift the integer according to the value of left16
  withLeftZeroes = withLeftZeroes>>left16;


  //We continue the process
  int left8 = (!(!(withLeftZeroes>>8)))<<3;
  withLeftZeroes = withLeftZeroes>>left8;

  int left4 = (!(!(withLeftZeroes>>4)))<<2;
  withLeftZeroes = withLeftZeroes>>left4;

  int left2 = (!(!(withLeftZeroes>>2)))<<1;
  withLeftZeroes = withLeftZeroes>>left2;

  int left1 = !(!(withLeftZeroes>>1));
  withLeftZeroes = withLeftZeroes>>left1;

  int leftMost = withLeftZeroes;

  //Now we add the 1 sign bit 
  int numBits = left16 + left8 + left4 + left2 + left1 + leftMost + 1;

  return numBits;

}
/* 
 * float_abs - Return bit-level equivalent of absolute value of f for
 *   floating point argument f.
 *   Both the argument and result are passed as unsigned int's, but
 *   they are to be interpreted as the bit-level representations of
 *   single-precision floating point values.
 *   When argument is NaN, return argument..
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 10
 *   Rating: 2
 */
unsigned float_abs(unsigned uf) {
  //First let's set the sign bit to zero
  unsigned signChanger = 0x7FFFFFFF;
  unsigned changedUf = uf & signChanger;

  //Now let's find lowest NAN
  unsigned smallestNAN = 0x7F800001;

  //changed uf must be greater than smallestNAN as an unsgned to be a NAN

  if(changedUf>smallestNAN)
          return uf;
  else
          return changedUf;
}
/* 
 * float_twice - Return bit-level equivalent of expression 2*f for
 *   floating point argument f.
 *   Both the argument and result are passed as unsigned int's, but
 *   they are to be interpreted as the bit-level representation of
 *   single-precision floating point values.
 *   When argument is NaN, return argument
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 30
 *   Rating: 4
 */
unsigned float_twice(unsigned uf) {
  //Multiplying a float by two is just adding 1 to the exponent
  //Multiplying 0 by 2 will give zero
  //Multiplying infinity of NAN values by 2 doesn't make sense
  //So we return the number when uf is 0 or all ones in exponent
  if(((uf<<1)==0) || ((uf & 0x7F800000)== 0x7F800000))
          return uf;

  //For values less than one, we keep the sign bit unchanged and left shift rest 31 bits by 1

  unsigned signBit = uf & 0x80000000;

  if(((uf>>23) & 0xFF) == 0)
         return (uf<<1) | signBit; //We or the sign bit so that if the sign bit was 1, it stays 1

  //All the special cases are done. Now just add 1 to exponent

  return uf + (1<<23);

}
/*
 * trueFiveEighths - multiplies by 5/8 rounding toward 0,
 *  avoiding errors due to overflow
 *  Examples: trueFiveEighths(11) = 6
 *            trueFiveEighths(-9) = -5
 *            trueFiveEighths(0x30000000) = 0x1E000000 (no overflow)
 *  Legal ops: ! ~ & ^ | + << >>
 *  Max ops: 25
 *  Rating: 4
 */
int trueFiveEighths(int x)
{
    //Divide by 8 first to avoid overflow
    int divEight = x>>3;
    printf("%d %d\n", x, divEight);

    int remUnchecked = x&7;
    int multFive =divEight +  (divEight << 2);
    printf("a: %d\n", multFive);
    int remMultFive = remUnchecked + (remUnchecked << 2);

    //Add 7 to remMultFive is x is negative, 0 if positive
    int toAdd = (x>>31)&7;
    return multFive + ((remMultFive+toAdd)>>3);
}
