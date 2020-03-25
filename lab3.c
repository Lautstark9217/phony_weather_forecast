#include  "lab3.h"
void func_query_City(char* city2Query,struct CityQuery *cq)
{
    int cityNameLength=strlen(city2Query);
    if (cityNameLength>29) city2Query[29]='\0';
    memcpy(cq->cityQueryType,0x0100,2);
    memcpy(cq->cityName,city2Query,29);
}
void func_query_Date(int queryType,int date2Query,char* city2Query, struct DateQuery *dq)
{
    if(queryType==DQ_ASK_ONE_DAY)
    {
        memcpy(dq->dateQueryType,0x0201,2);
        memcpy(dq->cityName,city2Query,strlen(city2Query));
        memcpy(dq->dateNum,date2Query,1);
    }
    else
    {
        memcpy(dq->dateQueryType,0x0202,2);
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
    
    return 0;
}