#include <stdio.h>
int bitXor(int x, int y);
int allEvenBits(int x);
int replaceByte(int x, int n, int c);
int tmax(void);
int isEqual(int x, int y);
int isPositive(int x);
int subOK(int x, int y);
int fitsBits(int x, int n);
int trueFiveEighths(int x);
unsigned float_abs(unsigned uf);
unsigned float_twice(unsigned uf);
int bitParity(int x);
int howManyBits(int x);

int main(){
	int x, y;
//	scanf("%d",&x);
//	scanf("%d",&y);
//	printf("The xor: %x\n", bitXor(x,y));
//	scanf("%x",&x);
//	printf("%d\n", allEvenBits(x));
//	int n,c;
//	scanf("%x %d %x", &x, &n, &c);
//	printf("%x\n", replaceByte(x,n,c));
//	printf("%x\n", tmax());
	scanf("%d",&x);
//	scanf("%x",&y);
//	printf("%d\n", isEqual(x,y));
//	printf("%d\n",isPositive(x));
	printf("%d\n", howManyBits(x));
//	printf("%x\n", float_twice(x) );
	return 0;
}

/* 
 * bitXor - x^y using only ~ and & 
 *   Example: bitXor(4, 5) = 1
 *   Legal ops: ~ &
 *   Max ops: 14
 *   Rating: 1
 */

int bitXor(int x, int y){
	//A xor B = (~A & B) | (A & ~B)
	//Use De Morgan's law ~(A and B) = ~A or ~B
	//which follows ~(~A and ~B) = ~(~A) or ~(~B) = A or B
	//our A = ~x & y, B = x & ~B
	//so (~x & y)|(x & ~y) = the following expression
	return ~(~(~x & y) & ~(~y & x));
}


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

