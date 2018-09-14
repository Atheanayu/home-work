#include "gym.h"

//int comp_rent_start_time(Node * cos1, Node * cos2);
//Node * sort_down(Node * head, int(*comp_way)(Node *, Node *));
//void main_menu(void);
//void user_func_menu(void);
//void adm_func_menu(void);
//void reserve_management_menu(void);
//void count_order_menu(void);
//void site_management_menu(void);
//
//void Statistics(int *man,int *woman,char sex);
//void count_best_sport(Node *Rentalhead, Node * Sithead, char vanuename[VENUE_NAME_LEN]);
//
//Node * Login_user(Node * head_cos);
//Node * Login_adm(Node * head_adm);
//
//double Analyse_Revenue(Node *Rentalhead, Node * Sithead, char venuename[NAME_LEN]);// 输出营业额 已测试
//void Analyse_Age(Node *Rentalhead, Node * Sithead, char venuename[NAME_LEN]);//输出年龄层 分布 已测试
//int is_Qualified(Node* sitehead, CostumerInfo* ptr, char siteID[ID_LEN], double rentalprice);//已测试  判定下单人是否符合条件
//void Admin_show_orders(Node *Rentalhead, Node * Sithead, char venuename[NAME_LEN]);//展示管理员定单 已测试
//void Analyse_UtilizeRate(Node* Rentalhead, Node * Sithead, char vanuename[NAME_LEN]);
//
//int revise_customer_info(CostumerInfo * cos);
//int revise_administrator_info(AdminInfo * adm);
//判断id是否合法函数需要修改，也需要增加写入文件的函数
//修改完成，只需写入文件

Node * _create_Site(Node * head_site,AdminInfo adm){
    char s[INTRO_LEN];
    int age;
    double rent_money;
//    int IfIDTure=0;
//    int *IDTure;
//    IDTure=&IfIDTure;
    char ID[ID_LEN];

    Node * node = (Node *)malloc(sizeof(Node));/* 为该node分配地址空间 */
    node->Info = (AdminInfo*)malloc(sizeof(AdminInfo));/* 为node中的指针Info分配空间 */

    printf("please enter the site id:\n");
    scanf("%s",s);
    getchar();
    while(!Register_ID(s)){
        fprintf(stderr,"the site ID in the right mode\n");
        scanf("%s",s);
        getchar();
    }
    strcpy(((AdminInfo*)(node->Info))->ID,s);

    printf("please enter the region:\n");
    scanf("%s",s);
    getchar();
    strcpy(((SiteInfo*)(node->Info))->region,s);

    printf("please enter the venue name:\n");
    scanf("%s",s);
    getchar();
    strcpy(((SiteInfo*)(node->Info))->venue_name,s);

    printf("please enter the sport:\n");
    scanf("%s",s);
    getchar();
    strcpy(((SiteInfo*)(node->Info))->sport,s);

    printf("please enter the introduction:\n");
    scanf("%s",s);
    getchar();
    strcpy(((SiteInfo*)(node->Info))->intro,s);

    printf("please enter the enter age:\n");
    scanf("%d",&age);
    getchar();
//    strcpy(((SiteInfo*)(node->Info))->enter_age,age);
    ((SiteInfo*)(node->Info))->enter_age = age;
    printf("please enter the rent:\n");
    scanf("%lf",&rent_money);
    getchar();
//    strcpy(((SiteInfo*)(node->Info))->rent,rent_money);
    ((SiteInfo*)(node->Info))->rent = rent_money;
    return node;
}

int main()
{

    int n;
    Node * head_cos = _private_init(FILE_COS_PATH,_private_get_value_cos);
    Node * head_admin = _private_init(FILE_AMIN_PATH,_private_get_value_admin);
    Node * head_rent = _private_init(FILE_RENT_PATH,_private_get_value_rental);
    Node * head_site = _private_init(FILE_SITE_PATH,_private_get_value_SiteInfo);
    CostumerInfo * costumerInfo;
    AdminInfo * adminInfo;
    Node * p;
    main_menu();
    while ((n=get_int())!=4)
    {
        switch(n)
        {
            case 1:
                costumerInfo = (CostumerInfo *)Login_user(head_cos)->Info;
                if (costumerInfo==NULL){
                    fprintf(stderr,"Login failed!\n");
                    break;
                }
                else{
                    user_func_menu();
                    while ((n=get_int())!=4)
                    {
                        switch(n)
                        {
                            case 1:
                                search(head_site,head_rent,*costumerInfo);
                                break;
                            case 2:
                                revise_customer_info(costumerInfo);
                                break;
                            case 3:
                                cos_show_orders(head_rent,costumerInfo->ID);         //需要填充函数！ //注意此处更改过函数名称了！
                                break;
                            default:
                                fprintf (stderr,"Wrong Choice!");
                                break;
                        }
                        user_func_menu();
                    }
                }
                break;
            case 2:
                adminInfo = (AdminInfo *)Login_adm(head_admin)->Info;
                if (adminInfo==NULL){									//管理员登录函数   返回结构体
                    fprintf(stderr,"Login failed!\n");
                    break;
                }
                else{
                    adm_func_menu();
                    while ((n=get_int())!=4)
                    {
                        switch(n)
                        {
                            case 1:
                                reserve_management_menu();
                                while ((n=get_int())!=3)
                                {
                                    switch(n)
                                    {
                                        case 1:
                                            Admin_show_orders(head_rent, head_site, adminInfo->venue_name);   //最后一个为char*是不是这么调用？
                                            break;
                                        case 2:
                                            count_order_menu();
                                            while ((n=get_int())!=7)
                                            {
                                                switch(n)
                                                {
                                                    /* 三处统计函数没写*/
                                                    case 1:
                                                        printf("sorry, we have not finished the function.\n");
                                                        break;
                                                    case 2:
                                                        printf("sorry, we have not finished the function.\n");
                                                        break;
                                                    case 3:
                                                        Analyse_UtilizeRate(head_rent, head_site, adminInfo->venue_name);
                                                        break;
                                                    case 4:
                                                        printf("The total turnover is %.2lf.\n",Analyse_Revenue(head_rent,head_site,adminInfo->venue_name));
                                                        break;
                                                    case 5:
                                                        count_best_sport(head_rent,head_site,adminInfo->venue_name);
                                                        break;
                                                    case 6:
                                                        Analyse_Age(head_rent, head_site, adminInfo->venue_name);
                                                        break;
                                                    default:
                                                        fprintf (stderr,"Wrong Choice!");
                                                        break;
                                                }
                                                count_order_menu();
                                            }
                                            break;
                                        default:
                                            fprintf (stderr,"Wrong Choice!");
                                            break;
                                    }
                                    reserve_management_menu();
                                }
                                break;
                            case 2:
                                site_management_menu();
                                while ((n=get_int())!=3)
                                {
                                    switch(n)
                                    {
                                        case 1:
                                            search_venue(head_site, adminInfo->venue_name);
                                            break;
                                        case 2:
                                            //此处类似于预定，我不会调用！ 需要更改
                                            for(p = head_site;p->next != NULL;p = p->next)
                                                ;
                                            p->next = _create_Site(head_site,*adminInfo);
                                            break;
                                        default:
                                            fprintf (stderr,"Wrong Choice!");
                                            break;
                                    }
                                    site_management_menu();
                                }
                                break;
                            case 3:
                                revise_administrator_info(adminInfo);
                                break;
                            default:
                                fprintf (stderr,"Wrong Choice!");
                                break;
                        }
                        adm_func_menu();
                    }
                    break;
                }
            case 3:
                printf("Please fill in your registration information.\n");
                register_menu();
                while ((n=get_int())!=3)
                {
                    switch(n)
                    {
                        case 1:
                            Register_Customer(head_site);
                            break;
                        case 2:
                            Register_Admin(head_admin);
                            break;
                        default:
                            fprintf (stderr,"Wrong Choice!");
                            break;
                    }
                    register_menu();
                }
                break;
        }
        main_menu();
    }
    change_file_Rent_content(FILE_RENT_PATH,head_rent);
    change_file_admin_content(FILE_AMIN_PATH,head_admin);
    change_file_cos_content(FILE_COS_PATH,head_cos);
    change_file_Site_content(FILE_SITE_PATH,head_site);
    _private_free_list(head_admin);
    _private_free_list(head_cos);
    _private_free_list(head_rent);
    _private_free_list(head_site);
    return 0;
}

void main_menu(void){	   					//1
    printf("****** Integrated Gymnasium Management System *******\n");
    printf("*                1.  User login				        *\n");
    printf("*                2.  Administrator login            *\n");
    printf("*                3.  Register                       *\n");
    printf("*                4.  Exit                           *\n");
    printf("*****************************************************\n");
    printf("Please enter your choice: \n");
}



void user_func_menu(void){					//1.1
    printf("******************* User Function *******************\n");
    printf("*                1.  Query and Reserve		        *\n");
    printf("*                2.  Modify personal information    *\n");
    printf("*                3.  View my order                  *\n");
    printf("*                4.  Log off                        *\n");
    printf("*****************************************************\n");
    printf("Please enter your choice: \n");
}

void adm_func_menu(void){					//1.2
    printf("************** Administrator Function ***************\n");
    printf("*                1.  Reserving management 		    *\n");
    printf("*                2.  Site management                *\n");
    printf("*                3.  Modify personal information    *\n");
    printf("*                4.  Log off                        *\n");
    printf("*****************************************************\n");
    printf("Please enter your choice: \n");
}

void reserve_management_menu(void){                   //1.2.1
    printf("*************** Reserving Management ****************\n");
    printf("*                1.  Query historical order		    *\n");
    printf("*                2.  Count order                    *\n");
    printf("*                3.  Back to administrator function  *\n");
    printf("*****************************************************\n");
    printf("Please enter your choice: \n");
}


void count_order_menu(void){	 					//1.2.1.2
    printf("******************* Count Order *********************\n");
    printf("*                1. Sort by quantity 				*\n");
    printf("*                2. Sort by turnover 				*\n");
    printf("*                3. Sort by utilize rate            *\n");
    printf("*                4. Count turnover   				*\n");
    printf("*                5. Count best liked sport			*\n");
    printf("*                6. Count distribution of user's age*\n");
    printf("*                7. Back to reserving management	*\n");
    printf("*****************************************************\n");
    printf("Please enter your choice: \n");
}

void site_management_menu(){						//1.2.2
    printf("***************** Site Management *******************\n");
    printf("*                1. Query all the sites 			*\n");
    printf("*                2. Add a new site 					*\n");
    printf("*                3. Back to reserving management	*\n");
    printf("*****************************************************\n");
    printf("Please enter your choice: \n");
}

void cos_modify_menu(){
    printf("***************** cos_modify ************************\n");
    printf("*                1. phone number        			*\n");
    printf("*                2. key         					*\n");
    printf("*                3. e_mail                       	*\n");
    printf("*                4. region                      	*\n");
    printf("*                5. back to main menu               *\n");
    printf("*****************************************************\n");
    printf("Please enter your choice: \n");
}

void adm_modify_menu(){
    printf("***************** adm_modify ************************\n");
    printf("*                1. phone number        			*\n");
    printf("*                2. key         					*\n");
    printf("*                3. e_mail                       	*\n");
    printf("*                4. back to main menu               *\n");
    printf("*****************************************************\n");
    printf("Please enter your choice: \n");
}

void register_menu(){						//1.3
    printf("********************* Register **********************\n");
    printf("*                1. User                 			*\n");
    printf("*                2. Administrator 					*\n");
    printf("*                3. Back to homepage             	*\n");
    printf("*****************************************************\n");
    printf("Please enter your choice: \n");
}



