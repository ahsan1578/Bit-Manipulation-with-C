#include <stdio.h>
int bitXor(int x, int y);
int main(){
	int x, y;
	scanf("%d",&x);
	scanf("%d",&y);
	printf("The xor: %x\n", bitXor(x,y));
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
