#include "train.h"
#include "ticket.h"

void  menu()//菜单
{
    cout<<"\n********---欢迎来到火车订票系统---********\n";
    cout<<"\t 1.录入车次信息\n";
    cout<<"\t 2.浏览车次信息\n";
    cout<<"\t 3.查询车票信息\n";//输入数据
    cout<<"\t 4.售票\n";// 按总分降序进行排序
    cout<<"\t 5.退出\n";
    cout<<"\t 请选择";
    cout<<"\n***************************************\n";
}

void show(Train t[])//展示车次信息 case2
{
    cout<<"车次数:"<<n<<endl;
    cout<<"***************************************"<<endl;
    for(int i=0; i<n; i++)
    {
        cout<<"车次号:"<<t[i].no<<endl;
        cout<<"发出时间:"<<t[i].start_time<<endl;
        cout<<"到达时间:"<<t[i].end_time<<endl;
        cout<<"始发站:"<<t[i].start_station<<endl;
        cout<<"终点站:"<<t[i].last_station<<endl;
        cout<<"行车时间:"<<t[i].time<<endl;
        cout<<"票价:"<<t[i].price<<endl;
        cout<<"剩余车票数:"<<t[i].last_ticket<<endl;
        cout<<"途径站:";
        for(int j=0; j<(sizeof(t[i].pass_station)/sizeof(string)); j++){
            cout<<t[i].pass_station[j]<<" ";
        }
        cout<<endl;
    }
}
 
void input(Train t[])//录入&保存车次信息 case1
{
    int k=0;//中停站数量
    n++;
    for(int i=n-1; i<n; i++)
    {
        cout<<"请输入车次号:"<<endl;
        cin>>t[i].no;

        cout<<"出发时间："<<endl;
        cin>>t[i].start_time;

        cout<<"到达时间："<<endl;
        cin>>t[i].end_time;

        cout<<"请输入始发站:"<<endl;
        cin>>t[i].start_station;

        cout<<"请输入终点站:"<<endl;
        cin>>t[i].last_station;

        cout<<"请输入行车时间:"<<endl;
        cin>>t[i].time;

        cout<<"请输入票价:"<<endl;
        cin>>t[i].price;

        cout<<"请输入剩余车票数"<<endl;
        cin>>t[i].last_ticket;

        cout<<"请输入途径站:"<<endl;
        cout<<"途径站数量:"<<endl;
        cin>>k;
        for(int j=0; j<k; j++){
            cout<<"请输入途径站"<<j+1<<":"<<endl;
            cin>>t[i].pass_station[j];
        }
        t[i].stat_num=k+2;
        // break;
    }

    char c;
    cout<<"你要保存到文本文件中吗(y/n)"<<endl;
    cin>>c;
    if(c=='y')
    { 
        ofstream ofs;//写到文本文件当中去
        ofs.open("train.txt",ios::out);
        for(int i=0; i<n; i++)
        {
            ofs<<"车次号:"<<t[i].no<<endl;
            ofs<<"发出时间:"<<t[i].start_time<<endl;
            ofs<<"到达时间:"<<t[i].end_time<<endl;
            ofs<<"始发站:"<<t[i].start_station<<endl;
            ofs<<"终点站:"<<t[i].last_station<<endl;
            ofs<<"行车时间:"<<t[i].time<<endl;
            ofs<<"票价:"<<t[i].price<<endl;
            ofs<<"剩余车票数:"<<t[i].last_ticket<<endl;
            ofs<<"途径站:";
            for(int j=0; j<(sizeof(t[i].pass_station)/sizeof(string)); j++){
                ofs<<t[i].pass_station[j]<<" ";
            }
            ofs<<endl;
        }
        cout<<"保存成功！"<<endl;
    }
}
// 判断对应区间是否有车
bool trainrule(Train tr[],char startplace[],char getplace[],int i)
{
    int sta_len=0;//所有站点长度
    string all_station[20];//保存所有站点信息
    all_station[0] = tr[i].start_station;
    for(int j=0; j<tr[i].stat_num; j++){
        all_station[j+1] = tr[i].pass_station[j];
        sta_len = j+3;
    }
    all_station[sta_len-1] = tr[i].last_station;

    //判断对应站点是否单向
    for(int a=0; a<sta_len; a++){
        for(int b=a+1;b<sta_len;b++){
            if(startplace==all_station[a]&&getplace==all_station[b]){
                return true;
            }
        }       
    }
    return false;       
}

int ticketrule(Ticket ti[],Train tr[],char startplace[],char getplace[],int i)
{
    int sta_len=0;//所有站点长度
    string all_station[20];//保存所有站点信息
    all_station[0] = tr[i].start_station;
    for(int j=0; j<tr[i].stat_num-2; j++){
        all_station[j+1] = tr[i].pass_station[j];
        sta_len = j+3;
    }
    all_station[sta_len-1] = tr[i].last_station;

    //判断对应区间余票
    int tmp = tr[i].last_ticket;
    int conflict = 0;//和选票区间冲突的票数

    int first2=99999;//目标站点的站台编号
    int last2=0;
    for(int b=0;b<tr[i].stat_num;b++){
        if(all_station[b]==startplace&&b<first2){
            first2 = b;
        }
        if(all_station[b]==getplace&&b>first2){
            last2 = b;
        }
    }
    pricenum = last2-first2;

    for(int a=0; a<x; a++){       
        if(strcmp(ti[a].no,tr[i].no)==0){
            int first1=99999;
            int last1=0;
            for(int b=0;b<tr[i].stat_num;b++){
                if(all_station[b]==ti[a].start_station&&b<first1){
                    first1 = b;
                }
                if(all_station[b]==ti[a].last_station&&b>first1){
                    last1 = b;
                }
            }
            if(last1==0){
                cerr<<"乘车区间输入不对";
                return 0;
            }

            if(last2<=first1||first2>=last1){
                cout<<"不冲突";
            }else{
                cout<<"冲突";
                conflict++;
            }
        }
    }
    return tmp-conflict;    
}


void findtic(Ticket ti[],Train tr[])//查询车票功能：
{
    char startplace[20];
    char getplace[20];
    cout<<"请输入出发站:"<<endl;
    getchar();
    cin>>startplace;
    cout<<"请输入到达站:"<<endl;;
    cin>>getplace;
    for(int i=0; i<n; i++)
    {
        if(trainrule(tr,startplace,getplace,i))
        {
            cout<<"车次号:"<<tr[i].no<<endl;
            cout<<"发出时间:"<<tr[i].start_time<<endl;
            cout<<"到达时间:"<<tr[i].end_time<<endl;
            cout<<"始发站:"<<tr[i].start_station<<endl;
            cout<<"终点站:"<<tr[i].last_station<<endl;
            cout<<"行车时间:"<<tr[i].time<<endl;
            cout<<"途径站:";
            for(int j=0; j<tr[i].stat_num; j++){
                cout<<tr[i].pass_station[j]<<" ";
            }
            cout<<endl;
        }

        int num=ticketrule(ti,tr,startplace,getplace,i);
        if(num){
            cout<<"票价:"<<(pricenum+1.0)/tr[i].stat_num*tr[i].price<<endl;
            cout<<"剩余车票数:"<<num<<endl;
        }else{
            cout<<"没票了";
        }      
    }
}

void selltic(Ticket ti[],Train tr[])//售票功能
{
    string cc;
    int k;
    char startplace[20];
    char getplace[20];
    cout<<"请输入出发站:"<<endl;
    getchar();
    cin>>startplace;
    cout<<"请输入到达站:"<<endl;;
    cin>>getplace;
    cout<<"请输入你要买的车次号："<<endl;
    cin>>cc;
    cout<<"你要买几张："<<endl;
    cin>>k;   
    for(int i=0; i<n; i++){//n个列车
        if(cc==tr[i].no){           
            for(int j=0; j<k; j++){//k张票
                int num=ticketrule(ti,tr,startplace,getplace,i);
                if(num){
                    cout<<"购买成功!"<<endl;
                    // ti[x].no = tr[i].no;
                    strcpy(ti[x].no, tr[i].no);
                    // ti[x].start_station=startplace;
                    strcpy(ti[x].start_station,startplace);
                    // ti[x].last_station=getplace;
                    strcpy(ti[x].last_station,getplace);
                    ti[x].price = (pricenum+1.0)/tr[i].stat_num*tr[i].price;
                    ti[x].last_ticket = num-1;
                    x++;
                }else{
                    cout<<"没票了";
                }    
            }
            break;
        }      
    }
    
}

int main(){
    Ticket ticket[1000];
    Train train[1000];
    int m;//菜单选择标签2
    
    while(1)
    {
        menu();
        cin>>m;
        switch(m){
            case 1:
                input(train);// 录入车次信息
                break;
            case 2:
                show(train);//车次查询展示
                break;
            case 3:
                findtic(ticket,train);//查询车票信息
                break;
            case 4:
                selltic(ticket,train);//售票功能
                break;
            case 5:
                exit(0);//退出
                break;
            default:
                continue;
        }
    }
    return 0;
}
 


