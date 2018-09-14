#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "gym.h"

/* 顾客的账户余额 */
//int reserve(Node * head_site,Node * head_rent,CostumerInfo cos);/* 预约函数 */
//void _private_book_menu();/* 打印预约 */
//int search_venue(Node* head,char str[ID_LEN]);/* 来源于k. 的代码合并时候删除 */
//Node * search_site(Node* head,char str[ID_LEN]);/* 来源于k. 代码合并时候删除 */
//void _private_time_to_str(char * s);/* 将当前时间写成字符串形式 */
//int _private_time_minus(char * start_time,char * end_time);/* 将时间相减，暂时认为都是整小时的，如果不是后期可更改 */
//int is_right_time_mode(char * s);/* 判断输入时间的格式是否正确，不是我完成 */
//int write_to_file(char * path,char * content);/* 向文件中写入信息 */
//Node * _create_RentalInfo(Node * head_site,Node * head_rent,CostumerInfo cos);/* 负责读取和创建RentalInfo的结构体 */
//int Data_Check(Node* head, char end_time[TIME_LEN],char start_time[TIME_LEN],char asite_ID[ID_LEN]);
//int Read_time (char model[TIME_LEN]);

/* 还需要加一个时间测试，就是那个一周的那个 */
//void _private_book_menu(){
//    printf("******************* VANUE ***************************\n");
//    printf("*                1.  CP_CENTER				        *\n");
//    printf("*                2.  HD_CENTER                      *\n");
//    printf("*                3.  CY_CENTER                      *\n");
//    printf("*                4.  BACK TO HOMEPAGE               *\n");
//    printf("*****************************************************\n");
//}
/* 创建租借信息的结构体
 * 并为其赋值
 * */
Node * _create_RentalInfo(char * site_ID,Node * head_site,Node * head_rent,CostumerInfo cos){
    int choice,is_sucess=0;
    char s[40],ss[40];
    Node * node = (Node *)malloc(sizeof(Node));/* 为该node分配地址空间 */
    Node * node_site = search_site(head_site,site_ID);
    node->Info = (RentalInfo*)malloc(sizeof(RentalInfo));/* 为node中的指针Info分配空间 */
//    printf("which vanue do you want to go to?\n");
//    while(scanf("%d",&choice)!=1){/* 选择场馆 */
//        fprintf(stderr,"scanf() err\n");
//        printf("please choose again:\n");
//    }
//    getchar();
//    switch(choice){/* 处理 */
//        case 1:
//            search_venue(head_site,"CP_CENTER");/* 这个地方后期可以做处理 */
//            break;
//        case 2:
//            search_venue(head_site,"HD_CENTER");
//            break;
//        case 3:
//            search_venue(head_site,"CY_CENTER");
//            break;
//        case 4:
//            printf("back to ");
//            return NULL;
//        default:
//            fprintf(stderr,"we don't have this choice");
//            return NULL;
//    }
//    printf("which site do you want to go to?(please enter the site id)\n");
//    scanf("%s",s);
//    getchar();
//    if(search_site(head_site,s)==NULL){
//        fprintf(stderr,"we don't have this site");
//        return NULL;
//    }
    if(MyOrder_Check(head_rent,cos.ID)==0){
        fprintf(stderr,"sorry,one ID can not reserve more than 3\n");
        return NULL;
    }
    strcpy(((RentalInfo*)(node->Info))->site_ID,site_ID);
    _private_time_to_str(s);
    strcpy(((RentalInfo*)(node->Info))->Appoint_time,s);
    while(!is_sucess) {
        printf("please enter the start time:(yyyy:mm:dd:hh:mm)\n");
        scanf("%s", s);
        getchar();
        CheckDay(s, &is_sucess);
    }
//    while(!is_right_time_mode(s)){
//        fprintf(stderr,"the time is not in the right mode\n");
//        scanf("%s",s);
//        getchar();
//    }
    strcpy(((RentalInfo*)(node->Info))->start_time,s);
    strcpy(ss,s);
    while(Expired_Order_Check(time_cut(s))==0){
        fprintf(stderr,"the appoint time is earlier than current time\n");
        printf("please enter the start time:(yyyy:mm:dd:hh:mm)\n");
        scanf("%s", s);
        getchar();
        CheckDay(s, &is_sucess);
        strcpy(((RentalInfo*)(node->Info))->start_time,s);
    }
    if(Order_check(time_cut(s))==1){
        fprintf(stderr,"you have to reserve before one week\n");
        printf("please enter again\n");
        scanf("%s",s);
        getchar();
    }
    printf("please enter the end time:(yyyy:mm:dd:hh:mm)\n");
    scanf("%s",s);
    getchar();
    CheckDay(s,&is_sucess);
    strcpy(((RentalInfo*)(node->Info))->end_time,s);
    if(Data_Check(head_rent,time_cut(ss),time_cut(s),((RentalInfo*)(node->Info))->site_ID)==0){
        fprintf(stderr,"the time has been reserved\n");
        return NULL;/* 此处的逻辑是，一旦发现这个时间被reserved，就跳出这个函数，此处后期可修改 */
    }

    ((RentalInfo*)(node->Info))->price =
            _private_time_minus(&((((RentalInfo*)(node->Info))->start_time)[11]),&((((RentalInfo*)(node->Info))->end_time))[11])
            *(((SiteInfo*)(node_site->Info))->rent);
    strcpy(((RentalInfo*)(node->Info))->sex,cos.sex);

    if(((SiteInfo*)(node_site))->enter_age > cos.age){/* 新增年龄检测 */
        fprintf(stderr,"your age is not enough for entering this site\n");
        return NULL;
    }

    ((RentalInfo*)(node->Info))->age = cos.age;
    ((RentalInfo*)(node->Info))->is_complete = 0;
    sprintf(((RentalInfo*)(node->Info))->Appoint_ID,"%s|%s",cos.ID,((RentalInfo*)(node->Info))->Appoint_time);
    return node;
}

void _private_time_to_str(char * s){
    time_t time1;
    struct tm * current_time;
    time(&time1);
    current_time = localtime(&time1);
    sprintf(s,"%d:%02d:%02d:%02d:%02d",current_time->tm_year+1900,current_time->tm_mon+1,
            current_time->tm_mday,current_time->tm_hour,current_time->tm_min);
}


int reserve(char * site_ID,Node * head_site,Node * head_rent,CostumerInfo* cos){
    char temp_content[40];
    Node * new_node,*p;
//    _private_book_menu();
//    _private_book_venue_menu()
    if((new_node =_create_RentalInfo(site_ID,head_site,head_rent,*cos))==NULL){
        return -1;/* 回到homepage上 */
    }
    new_node->next = NULL;
    for(p = head_rent;p->next!=NULL;p= p->next)
        ;
    p->next = new_node;
    if(cos->balance < ((RentalInfo*)(new_node->Info))->price){/* 新增余额检测 */
        printf("sorry,your balance is not enough\n");
        return -1;
    }
    write_to_file(FILE_RENT_PATH,"#\n");
    sprintf(temp_content,"site_ID:%s\n",((RentalInfo*)(new_node->Info))->site_ID);
    write_to_file(FILE_RENT_PATH,temp_content);
    sprintf(temp_content,"Appoint_ID:%s\n",((RentalInfo*)(new_node->Info))->Appoint_ID);
    write_to_file(FILE_RENT_PATH,temp_content);
    sprintf(temp_content,"start_time:%s\n",((RentalInfo*)(new_node->Info))->start_time);
    write_to_file(FILE_RENT_PATH,temp_content);
    sprintf(temp_content,"end_time:%s\n",((RentalInfo*)(new_node->Info))->end_time);
    write_to_file(FILE_RENT_PATH,temp_content);
    sprintf(temp_content,"Appoint_time:%s\n",((RentalInfo*)(new_node->Info))->Appoint_time);
    write_to_file(FILE_RENT_PATH,temp_content);
    if(((RentalInfo*)(new_node->Info))->is_intime == true)
        write_to_file(FILE_RENT_PATH,"is_intime:true\n");
    else
        write_to_file(FILE_RENT_PATH,"is_intime:false\n");
    sprintf(temp_content,"price:%.2f\n",((RentalInfo*)(new_node->Info))->price);
    write_to_file(FILE_RENT_PATH,temp_content);
    sprintf(temp_content,"sex:%s\n",((RentalInfo*)(new_node->Info))->sex);
    write_to_file(FILE_RENT_PATH,temp_content);
    sprintf(temp_content,"age:%d\n",((RentalInfo*)(new_node->Info))->age);
    write_to_file(FILE_RENT_PATH,temp_content);
    write_to_file(FILE_RENT_PATH,"is_complete:0\n");
    return 0;
}

int write_to_file(char * path,char * content){
    FILE * fp = fopen(path,"a");
    fprintf(fp,"%s",content);
    fclose(fp);
    return 0;/* 成功 */
}

int _private_time_minus(char * start_time,char * end_time){/* s1 s2 都是hh:mm 形式的 */
    int num1=0,num2=0;
    for(int i = 0;i<2;i++)
        num1 += (start_time[i]-'0');
    for(int i = 0;i<2;i++)
        num2 += (end_time[i]-'0');
    return num2 - num1;
}


int Data_Check(Node* head, char end_time[TIME_LEN],char start_time[TIME_LEN],char asite_ID[ID_LEN])
{
    Node *next;
    RentalInfo *rentalinfo;
    int endtime = Read_time(end_time);//将时间全部转换成2017121212
    int starttime = Read_time(start_time);
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

//int search_venue(Node* head,char str[ID_LEN]){
//    bool is_found=0;
//    Node *target;
//    SiteInfo *info;
//
//    for(target=head;target!=NULL;target=target->next)
//    {
//        info = (SiteInfo *)target->Info;
//        if (strcmp(str,info->venue_name)==0)	//判断场地字符串是否一致
//        {
//            printf("\n");
//            printf("Site Info:\n");
//            printf("ID\t venue name\t\t region\t\t sport\t enter age\t rent\t introduction\n");
//            printf("%s%12s%12s%12s%8d%10.2lf%s\n",info->ID,info->venue_name,
//                   info->region,info->sport,info->enter_age,info->rent,info->intro);
//            is_found = 1;
//        }
//    }
//    return is_found;
//}

//Node * search_site(Node* head,char str[ID_LEN]) {
//    Node *target;
//    SiteInfo *info;
//
//    for (target = head; target != NULL; target = target->next) {
//        info = (SiteInfo *)(target->Info);
//        if (strcmp(str, info->ID) == 0)    //判断场地字符串是否一致
//        {
//            printf("\n");
//            printf("Site Info:\n");
//            printf("ID\t venue name\t\t region\t\t sport\t enter age\t rent\t introduction\n");
//            printf("%s%12s%12s%12s%8d%10.2lf%s\n", info->ID, info->venue_name, info->region, info->sport,
//                   info->enter_age, info->rent, info->intro);
//            return target;
//        }
//    }
//    return NULL;
//}
