#pragma once
#include <iostream>
#include<string.h>
#include<fstream>
using namespace std;

int n=0;//车次的个数
class Train
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
    string pass_station[20];//途径站
    int stat_num;
};


void menu();//菜单
void chose(int);//功能的选择
void input(Train t[]);//录入车次信息,可随机地增加车次数据
void show(Train t[]);//浏览车次信息，途径站。
bool trainrule(Train tr[],char startplace[],char getplace[],int i)//区间是否有车



