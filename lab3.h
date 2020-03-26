#ifndef NPLAB3
#define NPLAB3
#include    <sys/types.h>    
#include    <sys/socket.h>   
#include    <netinet/in.h>   
#include    <arpa/inet.h>   
#include    <errno.h>
#include    <fcntl.h>
#include    <netdb.h>
#include    <signal.h>
#include    <stdio.h>
#include    <stdlib.h>
#include    <string.h>
#include    <sys/stat.h>   
#include    <sys/uio.h>   
#include    <unistd.h>
#include    <sys/wait.h>
#include    <sys/un.h>        
#include    <sys/sysctl.h>
#include    <strings.h>    
#include    <sys/ioctl.h>
typedef unsigned char lByte;

const int CQ_CITY_IN=1;
const int CQ_CITY_NOT_FOUND=2;

const int DQ_ASK_ONE_DAY=1;
const int DQ_ASK_THREE_DAYS=2;

const int RP_WEATHER_QUERY=3;
const char RP_ONE_DAY='A';
const char RP_THREE_DAYS='B';

const char* WEATHER_NAME[8] = {  
    "overcast","sunny","cloudy","rain"
    ,"fog","rainstorm","thunderstorm","breeze"
};

struct CityQuery
{
    lByte cityQueryType[2];
    lByte cityName[31];
};
struct DateQuery
{
    lByte dateQueryType[2];
    lByte cityName[30];
    lByte dateNum;
};
struct Reply
{
    lByte replyType;
    lByte dateQueryType;
    lByte cityName[30];
    lByte year[2];
    lByte month;
    lByte day;
    lByte nTHDay;
    lByte daysAndWeathers[6];
};
#endif