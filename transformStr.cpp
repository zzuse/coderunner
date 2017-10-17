#include <iostream>
#include <stack>

int transformStr(const char* in,char* out);

using namespace std;
int main(int argc, char *argv[]) {
    std::string in="ab<c<d>e<f>g";
	char out[200];
	transformStr(in.c_str(),out);
	printf("%s\n",out);
	//expect "fdcabeg"
}

int transformStr(const char* in,char* out) {
	if(NULL==in) return -1;
	int i=0;
	std::stack<char> tmp;
	std::stack<char> final;
	while(in[i]!='\0')
	{
		if(in[i]!='<'&&in[i]!='>')
			tmp.push(in[i]);
		if((in[i]=='<')&&(in[i+1]!='\0'))
		{
			while(!tmp.empty())
			{
				final.push(tmp.top());
				tmp.pop();
			}
			final.push(in[i+1]);
		}
		if((in[i]=='>')&&(in[i+1]!='\0'))
		{
			tmp.push(in[i+1]);
		}
		while(!final.empty())
		{
			tmp.push(final.top());
			final.pop();
		}
		i++;
	}
	while(!tmp.empty()){
		final.push(tmp.top());
		tmp.pop();
	}
	int j=0;
	while(!final.empty()){
		out[j++]=final.top();
		final.pop();
	}
	return 0;
}
