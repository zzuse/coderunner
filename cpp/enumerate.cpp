#include <iostream>
#include <string>
#include <vector>

using namespace std;
typedef unsigned char uint1b;
int splitFields(char *p_pchRecord, char p_chSplit, std::vector<int> &intFields);
string complexNumberMultiply(string a, string b);
int ENUMERATED(char *p, int iLen, void *po);
int main(int argc, char *argv[])
{
    FILE *file = fopen("./bin", "rb");
    fseek(file, 132, 0);
    char tmp[100];
    fread(tmp, 3, 1, file);
    int out;
    ENUMERATED(tmp, 1, &out);
    printf("%d", out);
    cout << complexNumberMultiply("1+1i", "2+2i");
    cout << complexNumberMultiply("1+-1i", "2+-2i");
}
int ENUMERATED(char *p, int iLen, void *po)
{
    *((int *)po) = ((uint1b *)p)[0];
    return 0;
}

int splitFields(char *p_pchRecord, char p_chSplit, std::vector<int> &intFields)
{
    char *p_left;
    char *p_right;
    char temp[10];
    int i;
    long len;

    len = strlen(p_pchRecord);

    p_left = &p_pchRecord[0];
    i = 0;
    while ((p_right = strchr(p_left, p_chSplit)) != NULL)
    {
        i++;
        memset(temp, 0, sizeof(temp));
        len = p_right - p_left;
        strncpy(temp, p_left, len);
        intFields.push_back(atoi(temp));
        p_left = p_right + 1;
    }
    if (strlen(p_left) > 0)
    {
        i++;
        intFields.push_back(atoi(p_left));
    }
    return i;
}

string itoa(int i)
{
    char buf[11];
    sprintf(buf, "%d", i);
    return buf;
}

string complexNumberMultiply(string a, string b)
{
    size_t pos;
    if ((pos = a.find("i")) != string::npos)
    {
        a = a.substr(0, pos);
    }
    std::vector<int> intFields;
    splitFields(const_cast<char *>(a.c_str()), '+', intFields);
    if ((pos = b.find("i")) != string::npos)
    {
        b = b.substr(0, pos);
    }
    std::vector<int> intFields2;
    splitFields(const_cast<char *>(b.c_str()), '+', intFields2);
    //(1 - i) * (1 - i)  1 + i2 + 2 * i
    int sum = intFields[0] * intFields2[0] - (intFields[1] * intFields2[1]);
    int sum_comp = intFields[0] * intFields2[1] + intFields[1] * intFields2[0];
    return string(itoa(sum) + "+" + itoa(sum_comp) + "i");
}
//testing this on a 32bit machine
