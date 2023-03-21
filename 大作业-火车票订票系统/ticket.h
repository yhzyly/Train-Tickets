#pragma once
#include <iostream>
#include<string.h>
#include<fstream>

;using namespace std;

int x=0;//车票数
int pricenum = 0;//所选站数-1
//可买同一列车不同区间的票
class Ticket
{
public:
    char no[10];//车次号
    string start_time;//出发时间
    string end_time;//到达时间
    char start_station[20];//出发地
    char last_station[20];//到达地
    float time;//行车时间
    int price;//票价
    int last_ticket;//剩余车票数
};


