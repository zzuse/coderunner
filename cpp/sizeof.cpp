#include <iostream>

using namespace std;
int main(int argc, char *argv[]) {
#pragma pack(1)
    typedef struct {
        int32_t destId; //4bytes
        char    meterId[24]; //24bytes
        char    empty[3]; //3bytes
        char    msgType; //1bytes
        int32_t  msgLen;//4bytes
        char    content[0];//4bytes
    } SIntMsg;
    typedef struct 
    {
        char    version; //1 1byte
        char    spi:4; //0 4bit
        char    encrypt:4; //0 4bit
        int16_t tranId; //16882 2bytes
        int32_t sourceId; //16777261 4bytes

    // internal part
        int32_t destId; //0           4bytes
        char   meterId[24]; //10.0.2.15   24bytes
        short  port;  // for UDP only   2bytes
        char   empty[1]; //1byte
        char   msgType; //31   1byte
        int32_t msgLen;//before here is 40bytes
        char   content[0]; //"" 0bytes
    } STaosHeader;
    typedef struct _msg_node{
        struct _msg_node *next;
        int    msgLen;
    } SMsgNode;
    typedef struct {
        unsigned char code;
        char          more[];
    } STaosRsp, SMsgReply;
    
    struct pid_tag {
      unsigned int inactive:1;
      unsigned int :0; /*padding last field*/
      short pid;
    } Spid;
#pragma pack()

class A1 {
  public:
    int a;
    unsigned long b;
    int c;
};
class A2 {
  public:
    int a;
    char c;
    bool d;
};
class A3:private A2 {
  public:
    char k[3];
    char* str;
    virtual void f(){};
};
class A4:private A3 {
  public:
    char e[5];
    double* d;
    void h(){int a;int b;int c;};
};
    cout<<sizeof(unsigned long int)<<endl;
    cout<<sizeof(unsigned char)<<endl;
    cout<<sizeof(short)<<endl;
    cout<<__SIZEOF_LONG__<<endl;
    cout<<sizeof(long int)<<endl;
    cout<<sizeof(SIntMsg)<<endl;
    cout<<sizeof(STaosHeader)<<endl;
    cout<<sizeof(SMsgNode)<<endl;
    cout<<sizeof(STaosRsp)<<endl;
    cout<<sizeof(SMsgReply)<<endl;
    cout<<sizeof(Spid)<<endl;
    cout << "sizeof A1 "<<sizeof(A1) <<endl;
    cout << "sizeof A2 "<<sizeof(A2) <<endl;
    cout << "sizeof A3 "<<sizeof(A3) <<endl;
    cout << "sizeof A4 "<<sizeof(A4) <<endl;
    cout << "sizeof char A "<< sizeof 'A' <<endl;
    char p = 10;
    int apple = sizeof (int) * p;
    cout << "sizeof int*p "<<apple <<endl;

}