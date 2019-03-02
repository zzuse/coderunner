#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[])
{
	char *src = "abcdefghi\\$aagg";
	char dst[100];
	char *var, *token, *value;
	int dstLen, srcLen, tokenLen;

	dst[0] = 0, dstLen = 0;
	while (1)
	{
		var = strchr(src, '$');
		if (var == NULL)
			break;
		if (*(var - 1) == '\\')
		{
			srcLen = var - src - 1;
			memcpy(dst + dstLen, src, srcLen);
			dstLen += srcLen;
			src = var;
			break;
		}
		srcLen = var - src;
		memcpy(dst + dstLen, src, srcLen);
		dstLen += srcLen;
		src = var + 1;
	}

	strcpy(dst + dstLen, src);
	printf(dst);
	return 0;
}
