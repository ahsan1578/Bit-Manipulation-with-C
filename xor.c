#include <stdio.h>
int bitXor(int x, int y);
int allEvenBits(int x);
int replaceByte(int x, int n, int c);


int main(){
	int x, y;
	scanf("%d",&x);
	scanf("%d",&y);
	printf("The xor: %x\n", bitXor(x,y));
	scanf("%x",&x);
	printf("%d\n", allEvenBits(x));
	int n,c;
	scanf("%x %d %x", &x, &n, &c);
	printf("%x", replaceByte(x,n,c));
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
 * replaceByte(x,n,c) - Replace byte n in x with c
 *   Bytes numbered from 0 (LSB) to 3 (MSB)
 *   Examples: replaceByte(0x12345678,1,0xab) = 0x1234ab78
 *   You can assume 0 <= n <= 3 and 0 <= c <= 255
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 10
 *   Rating: 3
 */
int replaceByte(int x, int n, int c) {
	int byteToPut = c<<(8*n);
	int helperInt = (~0)^((0xFF)<<8*n);
	int xWithZeroesInN_thByte = x & helperInt;
	return xWithZeroesInN_thByte|byteToPut;
}


