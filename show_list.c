
#include "gym.h"

/*管理员查看所有订单*/

//展示出我的订单
void Admin_show_orders(Node *Rentalhead, Node * Sithead, char venuename[NAME_LEN])
{
    Node * Rentalcurrent, *Sitecurrent;
    //Node * Rentalnewhead = sort_down(Rentalhead, comp_rent_start_time);//根据时间筛选生成一个订单新表格
    Node * Rentalnewhead = sort(Rentalhead, comp_rent_start_time);
    SiteInfo *siteinfo = NULL;
    RentalInfo *rentalinfo = NULL;
    //Rentalcurrent = Rentalnewhead;
    Rentalcurrent = Rentalnewhead;
    Sitecurrent = Sithead;
    while (Sitecurrent != NULL)//查找相应的场地ID
    {
        siteinfo = (SiteInfo *)Sitecurrent->Info;
        if (strcmp(venuename, siteinfo->venue_name) == 0)//找到对应的场地ID
        {
            printf("\n");
            printf("site_ID\t\tAppoint_ID\t\tstart_time\tend_time\tAppoint_time\tprice\tis_intime\n");
            Rentalcurrent = Rentalnewhead;
            while (Rentalcurrent != NULL)
            {
                rentalinfo = (RentalInfo *)Rentalcurrent->Info;
                if (strcmp(rentalinfo->site_ID, siteinfo->ID) == 0)
                {
                    printf("%s\t\t%s\t%s\t%s\t%s\t%.2lf\t", rentalinfo->site_ID, rentalinfo->Appoint_ID,
                           rentalinfo->start_time, rentalinfo->end_time,rentalinfo->Appoint_time, rentalinfo->price);
                    if (rentalinfo->is_intime==1) {
                        printf("yes\n");
                    }
                    else{
                        printf("no\n");
                    }
                }
                Rentalcurrent = Rentalcurrent->next;
            }
        }
        Sitecurrent = Sitecurrent->next;
    }
}

/*最受男女喜爱的运动*/

void count_best_sport(Node *Rentalhead, Node * Sithead, char vanuename[VENUE_NAME_LEN])
{
    Node * Rentalcurrent, *Sitecurrent;
    SiteInfo *siteinfo;
    RentalInfo *rentalinfo;
    Rentalcurrent = Rentalhead;
    Sitecurrent = Sithead;
    int boynum, girlnum;
    while (Sitecurrent != NULL)//查找相应的场地ID
    {
        siteinfo = (SiteInfo *)Sitecurrent->Info;
        if (strcmp(vanuename, siteinfo->venue_name) == 0)//找到对应的场地ID
        {
            boynum = 0, girlnum = 0;
            Rentalcurrent = Rentalhead;
            while (Rentalcurrent != NULL)
            {
                rentalinfo = (RentalInfo *)Rentalcurrent->Info;
                if (strcmp(rentalinfo->site_ID, siteinfo->ID) == 0)
                {
                    if (strcmp(rentalinfo->sex, "male"))
                    {
                        girlnum++;
                    }
                    else
                    {
                        boynum++;
                    }
                }
                Rentalcurrent = Rentalcurrent->next;
            }
            printf("\nID为%s的场地，男生预定量为%d，女生预定量%d\n", siteinfo->ID, boynum, girlnum);
        }
        Sitecurrent = Sitecurrent->next;
    }

}

/*顾客看自己订单*/

void cos_show_orders(Node *Rentalhead, char cosid[ID_LEN]) {
    Node *Rentalcurrent;
//    Node *Rentalnewhead = sort_down(Rentalhead, comp_rent_start_time);//根据时间筛选生成一个订单新表格
//    Node *Rentalnewhead = sort(Rentalhead, comp_rent_start_time);
//    RentalInfo *rentalinfo = NULL;
    //Rentalcurrent = Rentalnewhead;
//    Rentalcurrent = Rentalnewhead;
    /* 新加，直接打印，不根据时间进行 */
    Rentalcurrent = Rentalhead;
    RentalInfo * rentalinfo;
    while (Rentalcurrent != NULL) {
        printf("\n");
        printf("site_ID\tAppoint_ID\tstart_time\tend_time\tAppoint_time\tprice\tis_intime\n");
        rentalinfo = (RentalInfo *) Rentalcurrent->Info;
        if (strncmp(rentalinfo->Appoint_ID, cosid, strlen(cosid)) == 0) {
            printf("%s\t %s\t %s\t %s\t %s\t %.2lf\t", rentalinfo->site_ID, rentalinfo->Appoint_ID,
                   rentalinfo->start_time, rentalinfo->end_time, rentalinfo->Appoint_time, rentalinfo->price);
            if (rentalinfo->is_intime == 1) {
                printf("yes\n");
            } else {
                printf("no\n");
            }
        }
        Rentalcurrent = Rentalcurrent->next;
    }
}

//统计一个场馆的营业额；
/*
1.场地名字查找相应的场地ID
2.场地ID--->订单信息
3.count 订单营业额
*/


double Analyse_Revenue(Node *Rentalhead, Node * Sithead, char venuename[NAME_LEN])//输入 订单表头，场地信息表头，场地名字，返回总营业额
{
    Node *Sitcurrent, *Rentalcurrent;
    SiteInfo *siteinfo;
    RentalInfo *rentalinfo;
    Sitcurrent = Sithead;
    Rentalcurrent = Rentalhead;
    double revenue = 0;
    while (Sitcurrent != NULL)//查找相应的场地ID
    {
        siteinfo = (SiteInfo *)Sitcurrent->Info;
        if (strcmp(venuename, siteinfo->venue_name) == 0)
        {
            while (Rentalcurrent != NULL)//根据ID查找相应的订单
            {
                rentalinfo = (RentalInfo *)Rentalcurrent->Info;
                if (strcmp(siteinfo->ID, rentalinfo->site_ID) == 0)
                {
                    revenue = revenue + rentalinfo->price;
                }
                Rentalcurrent = Rentalcurrent->next;
            }
            Rentalcurrent = Rentalhead;
        }
        Sitcurrent = Sitcurrent->next;
    }
    return revenue;
}

//统计不同场地的用户年龄层次分布
/*
1.场地名来找订单
2.订单的年龄信息
3.统计年龄信息
*/
//输入 订单表头，场地信息表头，场地名字
//直接打印出关于年龄的统计信息


//0-19岁->0 20-40岁->1  41以上->2
int AgeCode(int a) {
    if (a >= 0 && a < 20) {
        return 1;
    }
    if (a >= 20 && a <= 40) {
        return 2;
    }
    if (a > 40) {
        return 3;
    }
    return 0;//年龄不合法
}

void Analyse_Age(Node *Rentalhead, Node * Sithead, char venuename[NAME_LEN])
{

    Node *Sitcurrent, *Rentalcurrent;
    SiteInfo *siteinfo;
    RentalInfo *rentalinfo;
    Sitcurrent = Sithead;
    Rentalcurrent = Rentalhead;
    int Age[3] = { 0,0,0 };
    double total = 0;
    double revenue = 0;
    while (Sitcurrent != NULL)//查找相应的场地ID
    {
        siteinfo = (SiteInfo *)Sitcurrent->Info;
        if (strcmp(venuename, siteinfo->venue_name) == 0)
        {
            while (Rentalcurrent != NULL)//根据ID查找相应的订单
            {
                rentalinfo = (RentalInfo *)Rentalcurrent->Info;
                if (strcmp(siteinfo->ID, rentalinfo->site_ID) == 0)
                {
                    switch (AgeCode(rentalinfo->age))//统计信息
                    {
                        case 1:
                            Age[0]++;
                            total++;
                            break;
                        case 2:
                            Age[1]++;
                            total++;
                            break;
                        case 3:
                            Age[2]++;
                            total++;
                            break;
                    }//待增加百分比计算
                }
                Rentalcurrent = Rentalcurrent->next;
            }
            printf("\n%s\t%s运动场地\t%s年龄层分布0`20有：%d,20~40有%d,40+有%d", siteinfo->venue_name, siteinfo->sport, siteinfo->ID, Age[0], Age[1], Age[2]);
            Rentalcurrent = Rentalhead;
        }
        Age[1] = 0;
        Age[2] = 0;
        Age[0] = 0;
        total = 0.0;
        Sitcurrent = Sitcurrent->next;
    }
}


//Read standardized time
int Calculate_TimeLen(char starttime[TIME_LEN], char finishtime[TIME_LEN],int intime) {
    int i;
    if (Read_time(starttime) <= Current_Time()&&intime==1)
    {
        int starthour = (starttime[11] - '0') * 10 + (starttime[12] - '0'), finishhour = (finishtime[11] - '0') * 10 + (finishtime[12] - '0');
        return finishhour - starthour;
    }
    return 0;
}
// Return the accumulated time of one site.
int Calculate_Day()
{
    //int Order_Check_Compare(int year, int month, int day)
    time_t timep;//引用了 <time.h>
    struct tm *p;
    time(&timep);
    p = gmtime(&timep);
    int now = Order_Check_Compare(p->tm_year + 1900, p->tm_mon + 1, p->tm_mday);
    int startday = Order_Check_Compare(2018, 9, 1);
    return now - startday;
}
int isPrime(int year) {
    if ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0)) {
        return 1;
    }
    else {
        return 0;
    }
}

void Analyse_UtilizeRate(Node* Rentalhead, Node* Sithead, char vanuename[NAME_LEN]) {
    Node *Sitcurrent, *Rentalcurrent;
    SiteInfo *siteinfo;
    RentalInfo *rentalinfo;
    Sitcurrent = Sithead;
    Rentalcurrent = Rentalhead;
    int i;
    int Time_Sum = 0;
    double utilize;
    while (Sitcurrent != NULL)
    {
        siteinfo = (SiteInfo *)Sitcurrent->Info;
        if (strcmp(vanuename, siteinfo->venue_name) == 0)//查找相应的场地ID
        {
            while (Rentalcurrent != NULL)//根据ID查找相应的订单
            {
                rentalinfo = (RentalInfo *)Rentalcurrent->Info;
                if (strcmp(siteinfo->ID, rentalinfo->site_ID) == 0)
                {
                    Time_Sum += Calculate_TimeLen(rentalinfo->start_time, rentalinfo->end_time,rentalinfo->is_complete);
                }
                Rentalcurrent = Rentalcurrent->next;
            }
            Rentalcurrent = Rentalhead;
            utilize = (double)Time_Sum / (16 * (double)(Calculate_Day()));
            printf("Utilize Rate of %s: %.2lf%%\n", siteinfo->ID, utilize);
        }
        Time_Sum = 0;
        Sitcurrent = Sitcurrent->next;
    }
}