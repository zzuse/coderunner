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
        char    version; //1
        char    spi:4; //0
        char    encrypt:4; //0
        int16_t tranId; //16882
        int32_t sourceId; //16777261 

    // internal part
        int32_t destId; //0           12bytes
        char   meterId[24]; //10.0.2.15   24bytes
        short  port;  // for UDP only   2bytes
        char   empty[1]; //1byte
        char   msgType; //31   1byte
        int32_t msgLen;//before here is 40bytes
        char   content[0]; //""
    } STaosHeader;
    typedef struct _msg_node{
        struct _msg_node *next;
        int    msgLen;
    } SMsgNode;
    typedef struct {
        unsigned char code;
        char          more[];
    } STaosRsp, SMsgReply;
#pragma pack()

    char a[0];
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
}