#include <stdio.h>

#include <stdlib.h>

#include <string.h>

#include <time.h>

#include "gym.h"

//Node * _create_RentalInfo(Node * head_site,Node * head_rent,CostumerInfo cos);
//int reserve(Node * head_site,Node * head_rent,CostumerInfo cos);/* 预约函数 */
//
//Node * search_site(Node* head,char str[ID_LEN]);/* 来源于k. 代码合并时候删除 */
//
//void _private_time_to_str(char * s);/* 将当前时间写成字符串形式 */
//
//int _private_time_minus(char * start_time,char * end_time);/* 将时间相减，暂时认为都是整小时的，如果不是后期可更改 */
//
//int is_right_time_mode(char * s);/* 判断输入时间的格式是否正确，不是我完成 */
//
//int write_to_file(char * path,char * content);/*向文件中写入信息 */
//
//Node * _create_RentalInfo(char s[ID_LEN],Node * head_rent,CostumerInfo cos);/* 负责读取和创建RentalInfo的结构体 */
//int Data_Check(Node* head, char end_time[TIME_LEN],char start_time[TIME_LEN],char asite_ID[ID_LEN]);
//int Read_time (char model[TIME_LEN]);
//
/*分类别查询*/
//void search_venue(Node* head,char venue[VENUE_NAME_LEN]);
//void search_sport(Node* head,char sport[SPORT_LEN]);
//void search_region(Node* head,char region[REGION_LEN]);

/*用户友好输入*/
//char get_choice (void);
//int get_int (void);


/* 打印各个类别菜单 */
//void search_menu(void);
//void category_menu(void);
//void _private_book_venue_menu();
//void _private_book_sport_menu();
//void _private_book_region_menu();
//
//void sort_menu(void);
//void print(Node* head);


/* 创建租借信息的结构体
 * 并为其赋值
 * */




//void _private_time_to_str(char * s){
//    time_t time1;
//    struct tm * current_time;
//    time(&time1);
//    current_time = localtime(&time1);
//    sprintf(s,"%d:%02d:%02d:%02d:%02d",current_time->tm_year+1900,current_time->tm_mon+1,
//            current_time->tm_mday,current_time->tm_hour,current_time->tm_min);
//}


//int reserve(Node * head_site,Node * head_rent,CostumerInfo cos){
//    char temp_content[40];
//    Node * new_node,*p;
//    _private_book_menu();
//    if((new_node =_create_RentalInfo(head_site,head_rent,cos))==NULL){
//        return -1;/* 回到homepage上 */
//    }
//    new_node->next = NULL;
//    for(p = head_rent;p->next!=NULL;p= p->next)
//        ;
//    p->next = new_node;
//    write_to_file(FILE_RENT_PATH,"#\n");
//    sprintf(temp_content,"site_ID:%s\n",((RentalInfo*)(new_node->Info))->site_ID);
//    write_to_file(FILE_RENT_PATH,temp_content);
//    sprintf(temp_content,"Appoint_ID:%s\n",((RentalInfo*)(new_node->Info))->Appoint_ID);
//    write_to_file(FILE_RENT_PATH,temp_content);
//    sprintf(temp_content,"start_time:%s\n",((RentalInfo*)(new_node->Info))->start_time);
//    write_to_file(FILE_RENT_PATH,temp_content);
//    sprintf(temp_content,"end_time:%s\n",((RentalInfo*)(new_node->Info))->end_time);
//    write_to_file(FILE_RENT_PATH,temp_content);
//    sprintf(temp_content,"Appoint_time:%s\n",((RentalInfo*)(new_node->Info))->Appoint_time);
//    write_to_file(FILE_RENT_PATH,temp_content);
//    sprintf(temp_content,"price:%.2f\n",((RentalInfo*)(new_node->Info))->price);
//    write_to_file(FILE_RENT_PATH,temp_content);
//    if(((RentalInfo*)(new_node->Info))->is_intime == true)
//        write_to_file(FILE_RENT_PATH,"is_intime:true\n");
//    else
//        write_to_file(FILE_RENT_PATH,"is_intime:false\n");
//    sprintf(temp_content,"sex:%s\n",((RentalInfo*)(new_node->Info))->sex);
//    write_to_file(FILE_RENT_PATH,temp_content);
//    sprintf(temp_content,"age:%d\n",((RentalInfo*)(new_node->Info))->age);
//    write_to_file(FILE_RENT_PATH,temp_content);
//    return 0;
//}

//int write_to_file(char * path,char * content){
//    FILE * fp = fopen(path,"a");
//    fprintf(fp,"%s",content);
//    fclose(fp);
//}

//int _private_time_minus(char * start_time,char * end_time){/* s1 s2 都是hh:mm 形式的 */
//    int num1=0,num2=0;
//    for(int i = 0;i<2;i++)
//        num1 += (start_time[i]-'0');
//    for(int i = 0;i<2;i++)
//        num2 += (end_time[i]-'0');
//    return num2 - num1;
//}

//int Read_time (char model[TIME_LEN])
//{
//    int count = 0;
//    int time[4],returntime;
//    for (int i = 0; model[i] != '\0'; i++)
//    {
//        while (model[i] == ':')
//        {
//            count++;
//            if (count == 1)
//            {
//                time[0] = ((int)model[i - 4] - 48) * 1000+((int)model[i - 3] - 48) * 100+((int)model[i - 2] - 48) * 10 + ((int)model[i - 1] - 48);
//            }
//            else if (count == 2)
//            {
//                time[1] = ((int)model[i - 2] - 48) * 10 + ((int)model[i - 1] - 48);
//            }
//            else if (count == 3)
//            {
//                time[2] = ((int)model[i - 2] - 48) * 10 + ((int)model[i - 1] - 48);
//                time[3] = ((int)model[i + 1] - 48) * 10 + ((int)model[i + 2] - 48);
//            }
//            i++;
//        }
//    }
//    returntime = time[0] * 1000000 + time[1] * 10000 + time[2] * 100 + time[3];
//    return returntime;
//}

//int Data_Check(Node* head, char end_time[TIME_LEN],char start_time[TIME_LEN],char asite_ID[ID_LEN])
//{
//    Node *next;
//    RentalInfo *rentalinfo;
//    int endtime = Read_time(end_time);//将时间全部转换成2017121212
//    int starttime = Read_time(start_time);
//    int time;
//    next = head;
//    while (next != NULL)//循环开始，检索链表
//    {
//        rentalinfo = (RentalInfo *)(next->Info);
//        time = Read_time(rentalinfo->start_time);//第一轮判定
//        if (strcmp(rentalinfo->site_ID, asite_ID) == 0)//同一场地（相同场馆ID）
//        {
//            if (time >= starttime && time <endtime)//该订单的开始时间在已有区间之内
//            {
//                return 0;
//            }
//            else if (starttime >= time && starttime < Read_time(rentalinfo->end_time))//已有区间的开始时间在订单之内
//            {
//                return 0;
//            }
//        }
//        next = next->next;
//    }
//    return 1;
//}
//
//

int search_sport(Node* head,char sport[SPORT_LEN])
{
    Node *target;
    SiteInfo *info;
    int is_found = 0;

    printf("\n");
    printf("ID\t venue name\t region\t sport\t enter age\t rent\t introduction");
    for (target = head; target != NULL; target = target->next) {
        info = (SiteInfo *)(target->Info);
        if (strcmp(sport, info->sport) == 0)
        {
            printf("%20s%12s%10s%12s%10d%.2lf%s\n", info->ID, info->venue_name, info->region, info->sport,
                   info->enter_age, info->rent, info->intro);
            is_found = 1;
        }
    }
    return is_found;
}

int search_region(Node* head,char region[REGION_LEN])
{
    Node *target;
    SiteInfo *info;
    int is_found = 0;

    printf("\n");
    printf("ID\t venue name\t \tregion\t sport\t enter age\t rent\t introduction\n");
    for (target = head; target != NULL; target = target->next) {
        info = (SiteInfo *)(target->Info);
        if (strcmp(region, info->region) == 0)
        {
            printf("%s\t %s\t %s\t %s\t %d\t %.2lf\t %s\n", info->ID, info->venue_name, info->region, info->sport,
                   info->enter_age, info->rent, info->intro);
            is_found = 1;
        }
    }
    return is_found;
}


Node * search_site(Node* head,char str[ID_LEN]) {
    Node *target;
    SiteInfo *info;

    for (target = head; target != NULL; target = target->next) {
        info = (SiteInfo *)(target->Info);
        if (strcmp(str, info->ID) == 0)    //判断场地字符串是否一致
        {
//            printf("\n");
//            printf("Site Info:\n");
//            printf("ID\t venue name\t region\t sport\t enter age\t rent\t introduction");
//            printf("%20s%12s%10s%12s%10d%.2lf%s\n", info->ID, info->venue_name, info->region, info->sport,
//                   info->enter_age, info->rent, info->intro);
            return target;
        }
    }
    return NULL;
}

//防止选择预定或返回时错误的输入
char get_choice(void)
{
    char ch;

    ch = get_first();
    while (ch != 'y' && ch != 'n')
    {
        printf ("Please respond with y or n.\n");
        ch = get_first();
    }
    return ch;
}

//获取输入字符串的首字母  倘若输入yes或no同样可以达成目的
char get_first (void)
{
    char ch;
    char * s;
    ch = (char)getchar();
    fgets(s,100,stdin);
//    getchar();
    return ch;
}

//防止查询菜单中错乱字符的输入
int get_int (void)
{
    int input;
    char ch;

    while (scanf ("%d", &input) != 1)
    {
        while ((ch = (char)getchar()) != '\n')
        {
            putchar(ch);
        }
        printf (" is not an integer.\nPlease enter an integer:");
    }
    getchar();
    return input;
}

void search_menu(void){
    printf("******************* SEARCH MODE *********************\n");
    printf("*                1.  BY Site ID				        *\n");
    printf("*                2.  BY CATEGORY                    *\n");
    printf("*                3.  SORT                           *\n");
    printf("*                4.  BACK TO HOMEPAGE               *\n");
    printf("*****************************************************\n");
    printf("Please enter your choice: \n");
}

void category_menu(void){
    printf("******************** CATEGORY ***********************\n");
    printf("*                1.  VENUE					        *\n");
    printf("*                2.  SPORT			                *\n");
    printf("*                3.  REGION                         *\n");
    printf("*                4.  BACK TO SEARCH MODE            *\n");
    printf("*****************************************************\n");
    printf("Please choose the category: \n");
}

void _private_book_venue_menu(){

    printf("********************* VENUE *************************\n");
    printf("*                1.  CP_CENTER				        *\n");
    printf("*                2.  HD_CENTER                      *\n");
    printf("*                3.  CY_CENTER                      *\n");
    printf("*                4.  BACK TO CATEGORY               *\n");
    printf("*****************************************************\n");
    printf("Please enter your choice: \n");
}

void _private_book_sport_menu(){

    printf("********************* SPORT *************************\n");
    printf("*                1.  SOCCER				            *\n");
    printf("*                2.  BASKETBALL                     *\n");
    printf("*                3.  BADMINTON                      *\n");
    printf("*                4.  BACK TO CATEGORY               *\n");
    printf("*****************************************************\n");
    printf("Please enter your choice: \n");
}

void _private_book_region_menu(){

    printf("********************* REGION ************************\n");
    printf("*                1.  BEI_CP				            *\n");
    printf("*                2.  BEI_HD		                    *\n");
    printf("*                3.  BEI_CY                         *\n");
    printf("*                4.  BACK TO CATEGORY               *\n");
    printf("*****************************************************\n");
    printf("Please enter your choice: \n");
}

void sort_menu(void){
    printf("********************** SORT *************************\n");
    printf("*                1.  RENT ↑				            *\n");
    printf("*                2.  RENT ↓                         *\n");
    printf("*                3.  QUANTITY↑                      *\n");
    printf("*                4.  QUANTITY↓                      *\n");
    printf("*                5.  BACK TO SEARCH MODE            *\n");
    printf("*****************************************************\n");
    printf("Please enter your choice: \n");
}

void print_SiteInfo(Node* head)
{
    Node *target;
    SiteInfo *info;

    printf("\n");
    printf("ID\t venue name\t region\t sport\t enter age\t rent\t introduction\n");
    for (target = head; target != NULL; target = target->next) {
        info = (SiteInfo *)(target->Info);
        printf("%s\t %s\t %s\t %s\t %d\t %.2lf\t %s\n", info->ID, info->venue_name, info->region, info->sport,
               info->enter_age, info->rent, info->intro);
    }
}

int search_venue(Node* head,char str[ID_LEN]){
    bool is_found=0;
    Node *target;
    SiteInfo *info;

    for(target=head;target!=NULL;target=target->next)
    {
        info = (SiteInfo *)target->Info;
        if (strcmp(str,info->venue_name)==0)	//判断场地字符串是否一致
        {
            printf("\n");
            printf("Site Info:\n");
            printf("ID\t venue name\t\t region\t\t sport\t enter age\t rent\t introduction\n");
            printf("%s%12s%12s%12s%8d%10.2lf%s\n",info->ID,info->venue_name,
                   info->region,info->sport,info->enter_age,info->rent,info->intro);
            is_found = 1;
        }
    }
    return is_found;
}

Node * search_user(Node * head,char user_ID[ID_LEN]){
    Node * p;
    CostumerInfo * info;
    for(p = head;p!=NULL;p = p->next){
        info = ((CostumerInfo*)(p->Info));
        if(strcmp(info->ID,user_ID)==0)
            return p;
    }
    return NULL;
}
