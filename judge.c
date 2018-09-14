#include "gym.h"
#include <stdio.h>
#include<string.h>
#include <stdlib.h>
#include <math.h>
#include<time.h>
#include <ctype.h>

#define TRUE 1
#define FALSE 0
#define ERROR -1
/*
时间数据处理部分
池晓威
默认时间格式：yyyy:mm:dd:hh
*/

//int Read_time(char model[TIME_LEN]);/*把时间转换为数字 如 2017：12：15：14----》2017121514*/
//int Current_Time();/*获取当前时间 精确到小时*/
//int Order_Check_Compare(int year, int month, int day);/*用于订单检查计算，返回的是日 已测试*/
//int Appoint_Time_check(char time[TIME_LEN]);/*确认时间是否录入正确*/
//int Time_Check(char start_time[TIME_LEN]);/*修改订单使用判定是否在24h以外 已测试*/
//int Expired_Order_Check(char Ordertime[TIME_LEN]);/*判定过期订单  已测试*/
//int MyOrder_Check(Node *head, char MyID[ID_LEN]);/*我的订单是否以超过或等于三个 已测试*/
//int Order_check(char Ordertime[TIME_LEN]);/*判定订单是否在一周之外使用时返回0则说明时间不合法；需要重新输入 已测试 */
//int Data_Chack(Node* head, char end_time[TIME_LEN], char start_time[TIME_LEN], char asite_ID[ID_LEN]);/*查看预定时间是否被已使用 已测试*/


/*把时间转换为数字 如 2017：12：15：14----》2017121514*/
int Read_time (char model[TIME_LEN])
{
    int count = 0;
    int time[4],returntime;
    for (int i = 0;model[i]!='\0'; i++)
    {
        while (model[i] == ':')
        {
            count++;
            if (count == 1)
            {
                time[0] = ((int)model[i - 4] - 48) * 1000+((int)model[i - 3] - 48) * 100+((int)model[i - 2] - 48) * 10 + ((int)model[i - 1] - 48);
            }
            else if (count == 2)
            {
                time[1] = ((int)model[i - 2] - 48) * 10 + ((int)model[i - 1] - 48);
            }
            else if (count == 3)
            {
                time[2] = ((int)model[i - 2] - 48) * 10 + ((int)model[i - 1] - 48);
                time[3] = ((int)model[i + 1] - 48) * 10 + ((int)model[i + 2] - 48);
            }
            i++;
        }
    }
    returntime = time[0] * 1000000 + time[1] * 10000 + time[2] * 100 + time[3];
    return returntime;
}//读取年月日

/*获取当前时间 精确到小时*/
int Current_Time()
{
    time_t timep;//引用了 <time.h>
    struct tm *p;
    time(&timep);
    p = gmtime(&timep);
    return (p->tm_year+1900) * 1000000 + (p->tm_mon + 1) * 10000 + p->tm_mday * 100 + (p->tm_hour + 8);
}

/*修改订单使用 一天以外才可修改*/
int Time_Check(char model[TIME_LEN])
{
    if (Expired_Order_Check(model)==0)
    {
        printf("\nOrder has expired");
        return 0;
    }
    int tim[4];//先读取时间
    int count = 0;
    for (int i = 0; model[i]!='\0'; i++)
    {
        while (model[i] == ':')
        {
            count++;
            if (count == 1)
            {
                tim[0] = ((int)model[i - 4] - 48) * 1000 + ((int)model[i - 3] - 48) * 100 + ((int)model[i - 2] - 48) * 10 + ((int)model[i - 1] - 48);
            }
            else if (count == 2)
            {
                tim[1] = ((int)model[i - 2] - 48) * 10 + ((int)model[i - 1] - 48);
            }
            else if (count == 3)
            {
                tim[2] = ((int)model[i - 2] - 48) * 10 + ((int)model[i - 1] - 48);
                tim[3] = ((int)model[i + 1] - 48) * 10 + ((int)model[i + 2] - 48);
            }
            i++;
        }
    }
    time_t timep;//获取当前时间
    struct tm *p;
    time(&timep);
    p = gmtime(&timep);
    double appointtime = (Order_Check_Compare(tim[0], tim[1], tim[2]) * 24 + tim[3]);
    double nowtime = (Order_Check_Compare(p->tm_year + 1900,  p->tm_mon + 1, p->tm_mday) * 24 + p->tm_hour +8);
    if (appointtime-nowtime<24)//至少提前一天修改订单
    {
        return 0;//不可修改，返回FALSE
    }
    return 1;//可修改
}

/*判定过期订单  已测试*/
int Expired_Order_Check(char Ordertime[TIME_LEN])//导入订单上的日期
{
    if (Read_time(Ordertime) <= Current_Time())
    {
        return 0;//订单已经过期
    }
    return 1;//订单未过期
}

/*我的订单是否以超过或等于三个*/
int MyOrder_Check(Node *head,char MyID[ID_LEN])
{
    Node *Next;
    RentalInfo *appointid;
    Next = head;
    int count = 0;
    while (Next!=NULL)
    {
        appointid = (RentalInfo *)(Next->Info);
        if (strncmp(appointid->Appoint_ID, MyID, strlen(MyID))==0)//如果是我的订单
        {
            if (appointid->is_complete == 0)//若日期未过期
            {
                count++;
            }
        }
        Next = Next->next;
    }
    if (count>=3)//超过或等于三比订单的话
    {
        return 0;//不可添加
    }
    return 1;//可以添加
}

/*用于订单检查计算 返回天数*/
int Order_Check_Compare(int year, int month, int day)
{
    year -= 2000;
    char Standard_month[13] = { 0,31,28,31,30,31,30,31,31,30,31,30,31 };
    int i, sum = 0;
    for (i = 1; i < year; i++)//计算闰年与平年
    {
        if ((i % 4 == 0 && i % 100 != 0 )|| i % 400 == 0)//若为闰年
        {
            sum += 366;
        }
        else//若为平年
        {
            sum += 365;
        }
    }
    if ((year % 4 == 0 && year % 100 != 0 )|| year % 400 == 0)//闰月判定

    {
        Standard_month[2] = 29;
    }
    for (i = 1; i < month; i++)
    {
        sum += Standard_month[i];//整月的天数
    }

    sum += day;//日的天数
    return sum;
}

/*判定订单是否在一周之外*/
int Order_check(char Ordertime[TIME_LEN])
{
    /*引用了 <time.h>,抓取现在时间*/
    time_t timep;
    struct tm *p;
    time(&timep);
    p = gmtime(&timep);
    if (Expired_Order_Check(Ordertime)==0)
    {
        printf("\nInpput ERROR.");//
        return 0;
    }

    /*抓取订单时间，以数组time 按照年月日时的顺序储存*/
    int count = 0;
    int time[4];
    for (int i = 0; Ordertime[i] != '\0'; i++)
    {
        while (Ordertime[i] == ':')
        {
            count++;
            if (count == 1)
            {
                time[0] = ((int)Ordertime[i - 4] - 48) * 1000 + ((int)Ordertime[i - 3] - 48) * 100 + ((int)Ordertime[i - 2] - 48) * 10 + ((int)Ordertime[i - 1] - 48);
            }
            else if (count == 2)
            {
                time[1] = ((int)Ordertime[i - 2] - 48) * 10 + ((int)Ordertime[i - 1] - 48);
            }
            else if (count == 3)
            {
                time[2] = ((int)Ordertime[i - 2] - 48) * 10 + ((int)Ordertime[i - 1] - 48);
                time[3] = ((int)Ordertime[i + 1] - 48) * 10 + ((int)Ordertime[i + 2] - 48);
            }
            i++;
        }
    }

    if (Order_Check_Compare((p->tm_year+1900), (p->tm_mon+1),( p->tm_mday+1)) - Order_Check_Compare(time[0], time[1], time[2]) < 7)/*修改*/
    {
        return 0; //错误，距离预定日期小于七天
    }
    return 1;
}

/*查看预定时间是否被已使用 已测试*/
int Data_Chack(Node* head, char end_time[TIME_LEN],char start_time[TIME_LEN],char asite_ID[ID_LEN])
{
    Node *next;
    RentalInfo *rentalinfo;
    int endtime = Read_time(end_time);//将时间全部转换成2017121212
    int starttime = Read_time(start_time);
    if (endtime-starttime>16)//订单时间超过一天
    {
        printf("一次只可预定一天的订单");
        return 0;
    }
    int time;
    next = head;
    while (next != NULL)//循环开始，检索链表
    {
        rentalinfo = (RentalInfo *)(next->Info);
        time = Read_time(rentalinfo->start_time);//第一轮判定
        if (strcmp(rentalinfo->site_ID, asite_ID) == 0)//同一场地（相同场馆ID）
        {
            if (time >= starttime && time <endtime)//该订单的开始时间在已有区间之内
            {
                return 0;
            }
            else if (starttime >= time && starttime < Read_time(rentalinfo->end_time))//已有区间的开始时间在订单之内
            {
                return 0;
            }
        }
        next = next->next;
    }
    return 1;
}

/*确认时间是否录入正确 待优化(过久远或早于现在时间)*/
//int Appoint_Time_check(char model[TIME_LEN])
//{
//    int i;
//    int count = 0;
//    for (i = 0; i < strlen(model); i++)//先检测非法字符
//    {
//        if ((model[i] >= '0'&&model[i] <= '9') || model[i] == ':')
//        {
//            continue;
//        }
//        else
//        {
//            return 0;//按需加printf
//        }
//    }
//
//    if (model[4]!=':'||model[7] != ':' ||model[10] != ':')//检测输入位数
//    {
//        return 0;//按需加printf
//    }
//
//    if (Read_time(model)<Current_Time())//当预定的时间早于当前时间时报错
//    {
//        return 0;//按需加printf
//    }
//    return 1;
//}

char * time_cut(char * time){
    int count = 0,i = 0;
    for(i = 0;count != 4;i++){
        if(time[i]==':')
            count++;
    }
    time[i-1]='\0';
    return time;
}

int CheckDay(char Day[],int *dayTure)          /* 检测日期是否合法 */
{
    int number=0,dot=0,i=0,j=0,ati=0,doti[10];
    int year,Two[4];
    int str;
    int IfdayTure=1;
    int *Ture;
    Ture=&IfdayTure;
    Ture=dayTure;
    for(i=0;i<strlen(Day);i++)
    {
        if(isdigit(Day[i]))
        {
            number++;
        }
        if(Day[i]==':')
        {
            dot++;
            doti[dot]=i;
        }
    }
    if(number!=strlen(Day)-4||dot!=4||doti[1]!=4)
    {
        IfdayTure=0;
    }
    for(i=1;i<4;i++)
    {
        if((doti[i+1]-doti[i])<2||(doti[i+1]-doti[i])>3)
        {
            IfdayTure=0;
        }
    }
    if(IfdayTure==1){
        year=(Day[0]-'0');
        for(i=0;i<4;i++)
        {
            Two[i]=0;
        }
        for(i=1;i<doti[1];i++)
        {
            year=year*10+(Day[i]-'0');
        }
        for(i=1;i<4;i++)
        {
            for(j=doti[i]+1;j<doti[i+1];j++)
            {
                Two[i-1]=Two[i-1]*10+(Day[j]-'0');
            }
        }
        for(i=doti[4]+1;i<strlen(Day);i++)
        {
            Two[3]=Two[3]*10+(Day[i]-'0');
        }
        if(year<2018||year>2050)
        {
            printf("对不起，请输入（2018-2050）内的年份\n");
            IfdayTure=0;
        }
        if(Two[0]<1||Two[0]>12)
        {
            printf("对不起，请输入（1-12）内的月份\n");
            IfdayTure=0;
        }
        if(Two[0]==2)
        {
            if(year%400==0||(year%4==0&&year%100!=0))
            {
                if(Two[1]<1||Two[1]>29)
                {
                    printf("对不起，请输入正确日期");
                    IfdayTure=0;
                }
            }
            else
            {
                if(Two[1]<1||Two[1]>28)
                {
                    printf("对不起，请输入正确日期");
                    IfdayTure=0;
                }
            }
        }
        else if(Two[0]>0&&Two[0]<8&&Two[0]!=2)
        {
            if(Two[0]%2==0)
            {
                if(Two[1]<1||Two[1]>30)
                {
                    printf("对不起，请输入正确日期");
                    IfdayTure=0;
                }
            }
            else
            {
                if(Two[1]<1||Two[1]>31)
                {
                    printf("对不起，请输入正确日期");
                    IfdayTure=0;
                }
            }
        }
        else
        {
            if(Two[0]%2==0)
            {
                if(Two[1]<1||Two[1]>31)
                {
                    printf("对不起，请输入正确日期");
                    IfdayTure=0;
                }
            }
            else
            {
                if(Two[1]<1||Two[1]>30)
                {
                    printf("对不起，请输入正确日期");
                    IfdayTure=0;
                }
            }
        }
        if(Two[2]<6||Two[2]>22)
        {
            printf("对不起，请输入（6-22）内的小时\n");
            IfdayTure=0;
        }
        if(Two[3]<0||Two[3]>59)
        {
            printf("对不起，请输入（0-60）内的分钟\n");
            IfdayTure=0;
        }
    }
    Ture=&IfdayTure;
    *dayTure=*Ture;
    return 0;
}

int Register_mail(char e_mail[])           /* 检测邮箱是否合法 */
{
    int at=0,dot=0,i=0,ati=0,doti=0,number=0;
    int IfemTure=1;
    int *Ture;
    Ture=&IfemTure;
    if(strlen(e_mail)<1)
    {
        return -1;
    }
    for(i=0;i<strlen(e_mail);i++)
    {
        if(e_mail[i]=='@')
        {
            at=i;
            ati++;
        }
        if(e_mail[i]=='.')
        {
            dot=i;
            doti++;
        }
    }
    if(at==0||dot==strlen(e_mail)-1||at>=dot-1||ati!=1||doti!=1)
    {
        return -1;
    }
    i=0;
    for (i=0;i<at;i++)
    {
        if(isalpha(e_mail[i])||isdigit(e_mail[i]))
            number++;
    }
    for (i=at+1;i<dot;i++)
    {
        if(isdigit(e_mail[i])||isalpha(e_mail[i]))
            number++;
    }
    for(i=dot+1;i<strlen(e_mail);i++)
    {
        if (isalpha(e_mail[i])||isdigit(e_mail[i]))
            number++;
    }
    if(number!=strlen(e_mail)-2)
    {
        return -1;
    }
//    if(IfemTure==0)
//    {
//        printf("对不起，您的邮箱不合法，请重新选择操作\n");
//        return -1;
//    }
//    Ture=&IfemTure;
//    *emTure=*Ture;
    return 0;
}

int Register_phone(char phone_num[])       /* 检测电话号码 */
{
    int number=0,i=0;
    int IfPhTure=1;
    int *Ture;
    Ture=&IfPhTure;
    for(i=0;i<strlen(phone_num);i++)
    {
        if(isdigit(phone_num[i]))
        {
            number++;
        }
    }
    if(number!=11||strlen(phone_num)!=11)
    {
//        printf("对不起，您的电话号码不合法，请重新选择操作\n");
        return -1;
    }
    return 0;
}

int Register_password(char key[])         /* 检测密码是否合法 */
{
    int letter=0,number=0,i=0;
    int IfPwTure=1;
    int *Ture;
    Ture=&IfPwTure;
    if(strlen(key)<1)
    {
        return -1;
    }
    for(i=0;i<strlen(key);i++)
    {
        if(isalpha(key[i]))
        {
            letter++;
        }else if(isdigit(key[i]))
        {
            number++;
        }
    }
    if(letter==0||number==0||letter+number!=strlen(key)||strlen(key)<6)  /* 暂定密码只有最少限制6 */
    {
//        printf("对不起，您的密码不合法");
        return -1;
    }
    return 0;
}

int Register_ID(char ID[ID_LEN]){
    int letter=0,number=0,i=0;
    int IfIDTure=1;
    int *Ture;
    Ture=&IfIDTure;
    if(strlen(ID)<1)
    {
        return -1;
    }
    for(i=0;i<strlen(ID);i++)
    {
        if(isalpha(ID[i]))     /* 检测字母数量 */
        {
            letter++;
        }
        if(isdigit(ID[i]))     /* 检测数字数量 */
        {
            number++;
        }
    }
    if(letter==0||number==0||letter+number!=strlen(ID)||strlen(ID)>10||strlen(ID)<6)
    {
        printf("对不起，您的用户名不合法，请重新选择操作\n");
        return -1;
    }
    return 0;
}