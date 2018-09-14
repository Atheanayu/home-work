#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>

/*
 * 修改:路径定义增加,Site_info 改成 SiteInfo,增加了Node结构体，增加通用性
 * 后期希望增加一个帮助系统
 * 如果可以第二个版本希望有web
 * 修改了TIME_LEN 的长度
 * */

/* 定义的常数 */
#define ID_LEN 30
#define NAME_LEN 20
#define PHONE_NUM_LEN 12
#define KEY_LEN 20
#define MAIL_ADDRESS_LEN 20
#define TIME_LEN 20
#define INTRO_LEN 300

#define VENUE_NAME_LEN 20
#define SEX_LEN 10
#define REGION_LEN 20
#define SPORT_LEN 10


/* 路径 */
#define FILE_COS_PATH "CostumerInfo.text"
#define FILE_AMIN_PATH "AdminInfo.text"
#define FILE_RENT_PATH "RentalInfo.text"
#define FILE_SITE_PATH "SiteInfo.text"

//enum sex_type{male,female};
//enum region_type{BEI_CP,BEI_HD,BEI_CY};
//enum sport_type{sccore,basketball,badminton};
//enum vanue{CP_CENTER,HD_CENTER,CY_CENTER};

typedef struct CostumerInfo{
    char ID[ID_LEN];
    char name[NAME_LEN];
    char phone_num[PHONE_NUM_LEN];
    char key[KEY_LEN];
    char e_mail[MAIL_ADDRESS_LEN];
//    enum sex_type sex;
//    enum region_type region;
    char sex[SEX_LEN];
    char region[REGION_LEN];
    double balance;
    int age;
    int default_num;/* 爽约次数 */
}CostumerInfo;

typedef struct AdminInfo{
    char ID[ID_LEN];
    char name[NAME_LEN];
//    enum vanue vanue_name;
    char venue_name[VENUE_NAME_LEN];
    char key[KEY_LEN];
    char e_mail[MAIL_ADDRESS_LEN];
//    enum sex_type sex;
    char sex[SEX_LEN];
    char phone_num[PHONE_NUM_LEN];
}AdminInfo;

typedef struct RentalInfo{
    char site_ID[ID_LEN];
    char Appoint_ID[ID_LEN];
    char start_time[TIME_LEN];
    char end_time[TIME_LEN];
    char Appoint_time[TIME_LEN];
    double price;/* 保留两位小数 */
    bool is_intime;/* true or false */
//    eunum sex_type sex;
    char sex[SEX_LEN];
    int age;
    int is_complete;/* 判断是否完成，0(未完成)，1（完成），-1（取消）,这个是新加的 */
}RentalInfo;


typedef struct SiteInfo{
    char ID[ID_LEN];
//    enum vanue vanue_name;/* （综合）场馆 */
    char venue_name[VENUE_NAME_LEN];
//    enum region_type region;
    char region[REGION_LEN];
//    enum sport_type sport;
    char sport[SPORT_LEN];
    char intro[INTRO_LEN];/*????????*/
    int enter_age;/* 准入年龄 */
    double rent;/* 租金 */

}SiteInfo;

typedef struct Node{
    void * Info;
    struct Node * next;
}Node;

char * time_cut(char * time);

int reserve(char * site_ID,Node * head_site,Node * head_rent,CostumerInfo* cos);/* cos 变成指针类型 */
//void _private_book_menu();

void search(Node* head_site,Node * head_rent,CostumerInfo cos);

int search_venue(Node* head,char str[ID_LEN]);
Node * search_site(Node* head,char str[ID_LEN]);
int search_sport(Node* head,char sport[SPORT_LEN]);
int search_region(Node* head,char region[REGION_LEN]);
Node * search_user(Node * head,char str[ID_LEN]);

/* 打印各个类别菜单 */
void search_menu(void);
void category_menu(void);
void _private_book_venue_menu();
void _private_book_sport_menu();
void _private_book_region_menu();
void sort_menu(void);
void cos_modify_menu();
void adm_modify_menu();
void main_menu(void);
void user_func_menu(void);
void adm_func_menu(void);
void reserve_management_menu(void);
void count_order_menu(void);
void site_management_menu();
void register_menu(void);

void print_SiteInfo(Node* head);

/*用户友好输入*/
char get_choice (void);
int get_int (void);
char get_first(void);


void _private_time_to_str(char * s);
int _private_time_minus(char * start_time,char * end_time);
//int is_right_time_mode(char * s);
int write_to_file(char * path,char * content);
Node * _create_RentalInfo(char * site_ID,Node * head_site,Node * head_rent,CostumerInfo cos);
int Data_Check(Node* head, char end_time[TIME_LEN],char start_time[TIME_LEN],char asite_ID[ID_LEN]);
Node * _private_init(char * path,int (*_private_get_value)(FILE*,Node*));
int _private_get_value_cos(FILE *fp,Node * c);
int _private_get_value_admin(FILE *fp,Node * c);
int _private_get_value_rental(FILE *fp,Node * c);
int _private_get_value_SiteInfo(FILE *fp,Node * c);

int change_file_Rent_content(char * path,Node * head);

int Read_time(char model[TIME_LEN]);/*把时间转换为数字 如 2017：12：15：14----》2017121514*/
int Current_Time();/*获取当前时间 精确到小时*/
int Order_Check_Compare(int year, int month, int day);/*用于订单检查计算，返回的是日 已测试*/
//int Appoint_Time_check(char time[TIME_LEN]);/*确认时间是否录入正确*/
int Time_Check(char start_time[TIME_LEN]);/*修改订单使用 已测试*/
int Expired_Order_Check(char Ordertime[TIME_LEN]);/*判定过期订单  已测试*/
int MyOrder_Check(Node *head, char MyID[ID_LEN]);/*我的订单是否以超过或等于三个 已测试*/
int Order_check(char Ordertime[TIME_LEN]);/*判定订单是否在一周之外使用时返回0则说明时间不合法；需要重新输入 已测试 */
int Data_Chack(Node* head, char end_time[TIME_LEN], char start_time[TIME_LEN], char asite_ID[ID_LEN]);/*查看预定时间是否被已使用 已测试*/

//void Test_Time_checkpart();/*订单时间查重比对测试*/
//void Test_Passed_order();/*过期订单判定测试*/
//void Test_Order_check();/*预定至少提早七天测试*/
//void Test_MyOrder_Check();/*我的未完成订单是否达到三比功能测试*/
//void Test_Time_Check();/*订单提前一天才能修改功能测试*/

Node * delete(Node * head,Node **deleteNode);
int comp_cos_name(Node * cos1,Node * cos2);
int comp_cos_ID(Node * cos1,Node * cos2);
int comp_cos_region(Node * cos1,Node * cos2);
int comp_cos_balance(Node * cos1,Node * cos2);
int comp_cos_age(Node * cos1,Node * cos2);
int comp_cos_default(Node * cos1,Node *cos2);
int comp_admin_ID(Node * cos1,Node * cos2);
int comp_admin_name(Node * cos1,Node * cos2);
int comp_rent_site_ID(Node * cos1,Node * cos2);
int comp_rent_Appoint_ID(Node * cos1,Node * cos2);
int comp_rent_start_time(Node * cos1,Node * cos2);
int comp_rent_Appoint_time(Node * cos1,Node * cos2);
int comp_rent_price(Node * cos1,Node * cos2);
int comp_rent_age(Node * cos1,Node * cos2);
int comp_site_ID(Node * cos1,Node * cos2);
int comp_site_vanue(Node * cos1,Node * cos2);
int comp_site_region(Node * cos1,Node * cos2);
int comp_site_sport(Node * cos1,Node * cos2);
int comp_site_enter_age(Node *cos1,Node * cos2);
int comp_site_rent_up(Node *cos1,Node * cos2);
int comp_site_rent_down(Node *cos1,Node * cos2);

Node * sort(Node * head,int (*comp_way)(Node *,Node *));
//Node * sort_down(Node *head,int (*comp_way)(Node *,Node *));
//Node * sort_up(Node *head,int (*comp_way)(Node *,Node *))
/* 检验时间模式是否正确 */
int CheckDay(char Day[],int *dayTure);

/* 取消订单 */
int cancel_order(Node * head_rent,char * Appoint_ID);
/* 向租赁信息的文件中修改信息 */
//int change_file_Rent_content(char * path,Node * head);

Node * Login_user(Node * head_cos);

int Register_mail(char e_mail[]);/* 正在检测 */
int revise_customer_info(CostumerInfo * cos);/* 正在检测 */
int Register_phone(char phone_num[]);/* 正在检测 */
int Register_password(char key[]);/* 正在检测 */
Node * Login_adm(Node * head_adm);/* 正在检测 */
int revise_administrator_info(AdminInfo * adm);/* 正在检测 */
int Register_ID(char ID[ID_LEN]);/* 正在检测 */
int Register_age(int age);/* 正在检测 */
void Register_Customer(Node * head_cos);/* 正在检测 */
void  Register_Admin(Node * head_admin);/* 正在检测 */

void cos_show_orders(Node *Rentalhead, char cosid[ID_LEN]); /* 用户看自己的订单 */
void Admin_show_orders(Node *Rentalhead, Node * Sithead, char venuename[NAME_LEN]);
void count_best_sport(Node *Rentalhead, Node * Sithead, char vanuename[VENUE_NAME_LEN]);
//void cos_show_orders(Node *Rentalhead, char cosid[ID_LEN]) ;
double Analyse_Revenue(Node *Rentalhead, Node * Sithead, char venuename[NAME_LEN]);
int AgeCode(int a) ;
void Analyse_Age(Node *Rentalhead, Node * Sithead, char venuename[NAME_LEN]);

int Calculate_TimeLen(char starttime[TIME_LEN], char finishtime[TIME_LEN],int intime);
int Calculate_Day();
int isPrime(int year);
void Analyse_UtilizeRate(Node* Rentalhead, Node* Sithead, char vanuename[NAME_LEN]);
void Register(Node * head_cos,Node * head_admin);

void Solid_line();
void Title();
int _private_free_list(Node * head);

int change_file_Site_content(char * path,Node * head);
int change_file_admin_content(char * path,Node * head);
int change_file_Rent_content(char * path,Node * head);
int change_file_cos_content(char * path,Node * head);


