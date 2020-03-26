#include  "lab3.h"

int tcp_client(char *address, int port) {
    int socket_fd;
    socket_fd = socket(AF_INET, SOCK_STREAM, 0);

    struct sockaddr_in server_addr;
    bzero(&server_addr, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(port);
    inet_pton(AF_INET, address, &server_addr.sin_addr);

    socklen_t server_len = sizeof(server_addr);
    int connect_rt = connect(socket_fd, (struct sockaddr *) &server_addr, server_len);
    if (connect_rt < 0) {
        //error(1, errno, "connect failed ");
    }

    return socket_fd;
}
void func_query_City(char* city2Query,struct CityQuery *cq)
{
    int cityNameLength=strlen(city2Query);
    if (cityNameLength>29) cityNameLength=29;
    int t=0x0001;//small endian
    memset(cq,0,cqSize);
    memcpy(cq->cityQueryType,&t,2);
    memcpy(cq->cityName,city2Query,cityNameLength);
}
void func_query_Date(int queryType,int date2Query,char* city2Query, struct DateQuery *dq)
{
    if(queryType==DQ_ASK_ONE_DAY)
    {
        int t=0x0102;//small endian
        memcpy(dq->dateQueryType,&t,2);
        memcpy(dq->cityName,city2Query,strlen(city2Query));
        memcpy(&(dq->dateNum),&date2Query,1);
    }
    else
    {
        int t=0x0202;
        memcpy(dq->dateQueryType,&t,2);
        memcpy(dq->cityName,city2Query,strlen(city2Query));
    }
}
int parse_reply(struct Reply* rp,const char cityName[])
{
    if(rp->replyType==CQ_CITY_IN)  return CQ_CITY_IN;
    else if(rp->replyType==CQ_CITY_NOT_FOUND)
    {
        printf("Sorry, Server does not have weather information for city %s!",cityName);
        return CQ_CITY_NOT_FOUND;
    }
    else if(rp->replyType==RP_WEATHER_QUERY)
    {
        int repYear=0,repMonth=0,repDate=0;
        repYear+=*(unsigned short*)(rp->year);
        repMonth+=rp->month;
        repDate+=rp->day;
        printf("City: %s  Today is: %d/%d/%d  Weather information is as follows:\n",cityName,repYear,repMonth,repDate);
        if(rp->dateQueryType==RP_ONE_DAY)
        {
            if(rp->nTHDay==1)
                printf("Today's Weather is: %s;  Temp:%d",WEATHER_NAME[rp->daysAndWeathers[0]],rp->daysAndWeathers[1]);
            else
                printf("The %dth day's Weather is: %s;  Temp:%d",rp->nTHDay,WEATHER_NAME[rp->daysAndWeathers[0]],rp->daysAndWeathers[1]);
        }
        else if(rp->dateQueryType==RP_THREE_DAYS)
        {
            for(int i=1;i<4;++i)
                printf("The %dth day's Weather is: %s;  Temp:%d",i,WEATHER_NAME[rp->daysAndWeathers[i*2-2]],rp->daysAndWeathers[i*2-1]);
        }
        else return -1;
    }
    else return -1;
}
int main()
{
    int sockfd=tcp_client("47.105.85.28",4321);
    if(sockfd<0) return -1;
    struct CityQuery cq;
    struct Reply rp;
    struct DateQuery dq;

    //begin
    while(1)
    {
        printf("Welcome to NJUCS Weather Forecast Demo Program!\nPlease input City Name in Chinese pinyin(e.g. nanjing or beijing)\n(c)cls,(#)exit\n");
        char cityName[100];
        scanf("%s",cityName);
        if(strcmp(cityName,"#")==0) break;
        else if(strcmp(cityName,"c")==0) system("clear");
        else
        {
            func_query_City(cityName,&cq);
            send(sockfd,(void*)(&cq),cqSize,0);

            recv(sockfd,&rp,rpSize,0);
            
            parse_reply(&rp,cityName);
        }
        
    }
    sleep(5);
    close(sockfd);
    return 0;
}