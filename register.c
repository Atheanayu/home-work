#include "gym.h"

void StarRegisterInface(Node * head_cos,Node * head_admin)
{
//    void Login();
//    void Register();
//    void Out();
    /* 声明函数，登录，注册，退出 */
//    printf("未登录\n");
//    Solid_line();
    int choice=-1;
    while(choice<1||choice>3)
    {
        Title();
        printf("请选择您接下来的操作\n");
        printf("1、登陆\n2、注册\n3、退出\n");
        scanf("%d",&choice);/* 读取选项 */
        switch(choice)
        {
            case 1:
            {
                printf("等待代码");
                break;
            }
            case 2:
            {
                Register(head_cos,head_admin);
                break;
            }
            case 3:
            {
                printf("欢迎您下次使用本服务系统");
                break;
            }
            default:
            {
                printf("对不起，您输入的选项不合法，请重新输入:"); /* 检测数据是否正确 */
                break;
            }
        }
    }
}

void Register(Node * head_cos,Node * head_admin)
{
//    void StarRegisterInface();
//    void Register_Admin(head_cos);
//    void Register_Customer(head_admin);      /* 声明调用函数 */
    int choice=-1;
    while(choice<0||choice>3)
    {
//        Title();
        printf("请选择注册用户类型:\n");
        printf("1、顾客；\n2、管理员;\n0、返回上级界面\n");
        printf("请输入选项：");
        scanf("%d",&choice);
        switch(choice)
        {
            case 0:
            {
                StarRegisterInface(head_cos,head_admin);
                break;
            }
            case 1:
            {
                Register_Customer(head_cos);
                break;
            }
            case 2:
            {
                Register_Admin(head_admin);
                break;
            }
            default:
            {
                printf("对不起，您输入的选项不合法，请重新输入:\n"); /* 检测数据是否正确 */
                break;
            }
        }
    }
};
void Register_Customer(Node * head_cos)                                            /* 注册顾客账号 */
{
    int choice = 0;
    Node * p;
//    void Register();
    Node * new_node = (Node *)malloc(sizeof(new_node));
    CostumerInfo* CurrentCustomer = (CostumerInfo *)malloc(sizeof(CurrentCustomer));
    for(p = head_cos;p->next!=NULL;p= p->next)
        ;
    p->next = new_node;
    new_node->next = NULL;
    new_node->Info = CurrentCustomer;
    char CheckKey[KEY_LEN];
    int i=0,Compare=100;
    printf("请按步骤开始注册您的账号：\n");
    while(1){
        printf("请设置您的ID号（6-10个字符与数字的组合）：\n");          /* 注册ID */
        scanf("%s",CurrentCustomer->ID);
        getchar();
        if(Register_ID(CurrentCustomer->ID)!=0){
            printf("your ID can not be registered,do you want to try again? (yes-1 no-2)\n");
            scanf("%d",&choice);
            getchar();
            if(choice != 1)
                break;
        } else
            break;/* 检测ID合法性 */
    }
    printf("请设置您的用户名：");                                      /* 注册用户名 */
    scanf("%s",CurrentCustomer->name);
    getchar();
    while(1){
        printf("请设置您的密码：(6位以上，字符与数字的组合)");
        scanf("%s",CurrentCustomer->key);                               /* 注册密码合法性 */
        if(Register_password(CurrentCustomer->key)!=0){
            printf("for your security ,your key can not be set,do you want to try again?(yes-1 no-2)\n");
            scanf("%d",&choice);
            getchar();
            if(choice != 1)
                break;
        }else
            break;/* 检测密码合法性 */
    }
    while(1){
        printf("请重新确认您的密码:");                                 /* 重新确认密码 */
        scanf("%s",CheckKey);
        getchar();
        Compare=strcmp(CurrentCustomer->key,CheckKey);
        if(Compare != 0){
            printf("sorry, key is not accordant,do you want to try again?(yes-1 no-2)\n");
            scanf("%d",&choice);
            getchar();
            if(choice != 1)
                break;
        }else
            break;
    }
    while(1)
    {
        printf("请输入您的性别：\n1、男\n2、女\n");                      /* 注册性别 */
        scanf("%s",CurrentCustomer->sex);
        if(Register_sex(CurrentCustomer->sex)!=0){
            printf("wrong choice ,do you want to try again?(yes-1 no-2)\n");
            scanf("%d",&choice);
            getchar();
            if(choice != 1)
                break;
        }else
            break;
    }
    while(1){
        printf("请输入您的电话号码：");                                /* 注册电话号码 */
        scanf("%s",CurrentCustomer->phone_num);
        if(Register_phone(CurrentCustomer->phone_num)!=0){
            printf("your phone number can not be true, do you want to enter again?(yes-1 no-2)\n");
            scanf("%d",&choice);
            getchar();
            if(choice != 1)
                break;
        } else
            break;/* 检测电话号码的合法性 */
    }
    while(1){
        printf("请输入您的邮箱地址：");                                /* 注册邮箱 */
        scanf("%s",CurrentCustomer->e_mail);
        if(Register_mail(CurrentCustomer->e_mail)!=0){
            printf("your mail can not be true, do you want to enter again?(yes-1 no-2)\n");
            scanf("%d",&choice);
            getchar();
            if(choice != 1)
                break;
        }else
            break;/* 检测邮箱的合法性 */
    }
    while(1){
        printf("请输入您的年龄：");                                    /* 注册年龄 */
        scanf("%d",&CurrentCustomer->age);
        getchar();
        if(Register_age(CurrentCustomer->age)!=0){
            printf("your age can not be true, do you want to enter again?(yes-1 no-2)\n");
            scanf("%d",&choice);
            getchar();
            if(choice != 1)
                break;
        }else
            break;/* 检测年龄的真实性 */
    }
    printf("请问您是否要充值余额？\n1、是\n2、否\n");                  /* 选择充值服务 */
    CurrentCustomer->balance=0;
    int newchoice;
    double money;
    scanf("%d",&newchoice);
    switch(newchoice)
    {
        case 1:
        {
            printf("请输入您要充值的金额：");                      /* 选择充值金额 */
            scanf("%lf",&money);
            getchar();
            CurrentCustomer->balance=money;
            printf("您的当前余额为：%.2lf\n",CurrentCustomer->balance);
            break;
        }
        case 2:
        {
            printf("您的当前余额为：0.00\n");
        }
        default:
        {
            printf("请输入正确选项");
        }
    }
    printf("恭喜您注册完成\n您的ID是：%s\n您的用户名是:%s\n",CurrentCustomer->ID,CurrentCustomer->name);
    printf("您的性别是：%s\n",CurrentCustomer->sex);
    printf("您的密码是：%s\n您的电话是：%s\n您的邮箱是：%s\n",CurrentCustomer->key,CurrentCustomer->phone_num,CurrentCustomer->e_mail);

//    /* 输出已注册界面 */
//    char Check;
//    scanf("%s",&Check);
//    Register();
}
void  Register_Admin(Node * head_admin)/* 注册管理员账号 */
{
    void Register();
    char CheckKey[KEY_LEN];
    int i=0,Compare=100;
    int choice;
    Node * p;
    Node * new_node = (Node *)malloc(sizeof(new_node));
    for(p = head_admin;p->next!=NULL;p= p->next)
        ;
    p->next = new_node;
    new_node->next = NULL;
    AdminInfo* CurrentAdmin = (AdminInfo *)malloc(sizeof(AdminInfo));
    new_node->Info = CurrentAdmin;
    printf("请按步骤开始注册您的账号：\n");
    while(1){
        printf("请设置您的ID号（6-10个字符与数字的组合）：\n");      /* 注册管理者ID */
        scanf("%s",CurrentAdmin->ID);
        if(Register_ID(CurrentAdmin->ID)!=0){
            printf("your ID can not be set, do you want to enter again ?(yes-1 no-2)\n");
            scanf("%d",&choice);
            getchar();
            if(choice != 1)
                break;
        }else
            break;/* 检测管理者ID合法性 */
    }
    printf("请设置您的用户名：");                                  /* 注册管理者用户名 */
    scanf("%s",CurrentAdmin->name);
    while(1){
        printf("请设置您的密码：(6位以上，字符和数字的组合)");                                /* 注册管理者密码 */
        scanf("%s",CurrentAdmin->key);
        if(Register_password(CurrentAdmin->key)!=0){
            printf("your key can not be set, do you want to enter again?(yes-1 no-2)\n");
            scanf("%d",&choice);
            getchar();
            if(choice !=1)
                break;
        }else
            break;/* 检测管理者密码合法性 */
    }
    while(1){
        printf("请重新确认您的密码:");                             /* 重新确认密码 */
        scanf("%s",CheckKey);
        Compare=strcmp(CurrentAdmin->key,CheckKey);
        if(Compare != 0){
            printf("your key is not right, do you want to try again?(yes-1 no-2)\n");
            scanf("%d",&choice);
            getchar();
            if(choice != 1)
                break;
        }else
            break;
    }
    printf("请输入您的性别：");                                    /* 注册管理者性别 */
    scanf("%s",CurrentAdmin->sex);
    while(1){
        printf("请输入您的电话号码：");                            /* 注册管理者电话号码 */
        scanf("%s",CurrentAdmin->phone_num);
        if(Register_phone(CurrentAdmin->phone_num)!=0){
            printf("your phone number can not be right, do you want to try again?(yes-1 no-2)\n");
            scanf("%d",&choice);
            getchar();
            if(choice != 1)
                break;
            /* 检测管理者邮箱合法性 */
        }else
            break;
    }
    while(1){
        printf("请输入您的邮箱地址：");                            /* 注册管理者邮箱 */
        scanf("%s",CurrentAdmin->e_mail);
        if(Register_mail(CurrentAdmin->e_mail)!=0){
            printf("your mail can not be right, do you want to enter again?(yes-1 no-2)\n");
            scanf("%d",&choice);
            if(choice != 1)
                break;
        }else
            break;/* 检测管理者邮箱合法性 */
    }
    printf("恭喜您注册完成\n您的ID是：%s\n您的用户名是:%s\n",
           CurrentAdmin->ID,CurrentAdmin->name);
    printf("您的性别是：%s\n",CurrentAdmin->sex);
    printf("您的密码是：%s\n您的电话是：%s\n您的邮箱是：%s\n",CurrentAdmin->key,CurrentAdmin->phone_num,CurrentAdmin->e_mail);
    printf("输入任意键返还上级：");
    /* 展示已成功注册界面 */
    char Check;
    scanf("%s",&Check);
//   Register();
}

int Register_sex(char sex[])                /* 检测年龄 */
{
    int number=0,i;
    int IfsexTure=1;
    int *Ture;
    Ture=&IfsexTure;
//    Ture=sexTure;
    number=(sex[0]-'0');
    if(number!=1&&number!=2||strlen(sex)!=1)
    {
        printf("请输入1或者2\n");
        return -1;
    }
    Ture=&IfsexTure;
//    *sexTure=*Ture;
    return 0;
}

int Register_age(int age)                /* 检测年龄 */
{
    int number=0;
    int IfageTure=1;
    int *Ture;
    Ture=&IfageTure;
//    Ture=ageTure;
    number=age;
    if(number<=0||number>=100)
    {
        printf("请输入合法年龄");
//        IfageTure=0;
        return -1;
    }
    Ture=&IfageTure;
//    *ageTure=*Ture;
    return 0;
}

void Solid_line()
{
    int i;
    for(i=0;i<26;i++)
    {
        printf("*");
    }
    printf("\n");
}
void Title()
{
    Solid_line();
    printf("欢迎来到北京体育馆预定系统\n");
    Solid_line();
}