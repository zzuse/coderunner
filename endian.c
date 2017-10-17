#include <stdio.h>  
  
int main()  
{  
	  
	union w  
	{  
		int a;  
		char b;  
	}c;  
  
	c.a = 1;  
  
	if(c.b == 1)  
	{  
		printf("litte!\n");  
	}  
	else  
	{  
		printf("big!\n");  
	}  
  
	return 0;  
}  
