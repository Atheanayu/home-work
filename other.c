#include <stdio.h>
#include <memory.h>
#include "gym.h"

//int main(){
//    Node * head = _private_init(FILE_AMIN_PATH,_private_get_value_admin);
//    revise_administrator_info(((AdminInfo*)(head->Info)));
//    return 0;
//}

Node * Login_user(Node * head_cos){
    int i,choice;
    char cos_ID[ID_LEN],key[KEY_LEN];
    Node * cos;
    printf("please enter your ID:\n");
    scanf("%s",cos_ID);
    getchar();
    if((cos = search_user(head_cos,cos_ID))==NULL){
        printf("sorry,you have not registered\n");
        return NULL;
    }
    for(i = 0;i<3;i++) {
        printf("please enter your key:\n");
        scanf("%s", key);
        getchar();
        if(strcmp(key,((CostumerInfo*)(cos->Info))->key)==0)
            break;
        else {
            printf("sorry,your key is wrong,do you want to try again ?(yes-1 no-2)\n");
            scanf("%d",&choice);
            getchar();
            if(choice != 1)
                break;
        }
    }
    if(i==3){
        printf("you have enter your key wrongly for 3 times,you have to back compulsorily\n");
        return NULL;
    }else
        return cos;
}

Node * Login_adm(Node * head_adm){
    int i,choice;
    char adm_ID[ID_LEN],key[KEY_LEN];
    Node * adm;
    printf("please enter your ID:\n");
    scanf("%s",adm_ID);
    getchar();
    if((adm = search_user(head_adm,adm_ID))==NULL){
        printf("sorry,you have not registered\n");
        return NULL;
    }
    for(i = 0;i<3;i++) {
        printf("please enter your key:\n");
        scanf("%s", key);
        getchar();
        if(strcmp(key,((AdminInfo*)(adm->Info))->key)==0)
            break;
        else {
            printf("sorry,your key is wrong,do you want to try again ?(yes-1 no-2)\n");
            scanf("%d",&choice);
            getchar();
            if(choice != 1)
                break;
        }
    }
    if(i==3){
        printf("you have enter your key wrongly for 3 times,you have to back compulsorily\n");
        return NULL;
    }else
        return adm;
}

int revise_customer_info(CostumerInfo * cos){
    int choice,i;
    char s[40];
    while(choice != 5){
        cos_modify_menu();
        scanf("%d",&choice);
        getchar();
        switch(choice) {
            case 1:
                printf("please enter your phone number:\n");
                scanf("%s", s);
                getchar();
                while(Register_phone(s)!=0){
                    printf("sorry,your phone number can not exist, do you want to try again?(yes-1 no-2)\n");
                    scanf("%d",&choice);
                    getchar();
                    if(choice != 1)
                        break;
                    printf("please enter your phone number:\n");
                    scanf("%s", s);
                    getchar();
                }
                strcpy(cos->phone_num,s);
                break;
            case 2:
                printf("please enter your original key:\n");
                for (i = 0; i < 3; i++) {
                    scanf("%s", s);
                    getchar();
                    if (strcmp(s, cos->key) == 0) {
                        printf("please enter your new key:\n");
                        printf("(for security ,there has to be both number & alpha in new key"
                                       ",but no other word ,besides the key word can not less than 6)\n");
                        scanf("%s", s);
                        getchar();
                        while(Register_password(s)!=0){
                            printf("sorry,your new key is not compatible,do you want to try again?(yes-1 no-2)\n");
                            scanf("%d",&choice);
                            getchar();
                            if(choice != 1)
                                break;
                            printf("please enter your new key:\n");
                            printf("(for security ,there has to be both number & alpha in new key"
                                           ",but no other word ,besides the key word can not less than 6)\n");
                            scanf("%s", s);
                            getchar();
                        }
                    } else {
                        printf("sorry, your key is wrong,do you want to try again?(yes-1 no-2)\n");
                        scanf("%d", &choice);
                        getchar();
                        if (choice != 1)
                            break;
                    }
                }
                if (i == 3)
                    printf("you have enter your key wrongly for 3 times,you have to back compulsorily\n");
                break;
            case 3:
                printf("please enter your new e_mail\n");
                scanf("%s", s);
                getchar();
                while(Register_mail(s)!=0) {
                    printf("sorry,your e_mail can not exist,do you want to try again?(yes-1 no-2)\n");
                    scanf("%d",&choice);
                    getchar();
                    if(choice != 1)
                        break;
                    printf("please enter your new e_mail\n");
                    scanf("%s", s);
                    getchar();
                    strcpy(cos->e_mail, s);
                }
                break;
            case 4:
                printf("please enter your region\n");
                scanf("%s", cos->region);
                getchar();
                break;
            case 5:
                break;
            default:
                printf("wrong choice\n");

        }
    }
    return 0;
}

int revise_administrator_info(AdminInfo * adm){
    int choice,i;
    char s[40];
    while(choice != 4){
        adm_modify_menu();
        scanf("%d",&choice);
        getchar();
        switch(choice) {
            case 1:
                printf("please enter your phone number:\n");
                scanf("%s", s);
                getchar();
                while(Register_phone(s)!=0){
                    printf("sorry,your phone number can not exist, do you want to try again?(yes-1 no-2)\n");
                    scanf("%d",&choice);
                    getchar();
                    if(choice != 1)
                        break;
                    printf("please enter your phone number:\n");
                    scanf("%s", s);
                    getchar();
                }
                strcpy(adm->phone_num,s);
                break;
            case 2:
                printf("please enter your original key:\n");
                for (i = 0; i < 3; i++) {
                    scanf("%s", s);
                    getchar();
                    if (strcmp(s, adm->key) == 0) {
                        printf("please enter your new key:\n");
                        printf("(for security ,there has to be both number & alpha in new key"
                                       ",but no other word ,besides the key word can not less than 6)\n");
                        scanf("%s", s);
                        getchar();
                        while(Register_password(s)!=0){
                            printf("sorry,your new key is not compatible,do you want to try again?(yes-1 no-2)\n");
                            scanf("%d",&choice);
                            getchar();
                            if(choice != 1)
                                break;
                            printf("please enter your new key:\n");
                            printf("(for security ,there has to be both number & alpha in new key"
                                           ",but no other word ,besides the key word can not less than 6)\n");
                            scanf("%s", s);
                            getchar();
                        }
                    } else {
                        printf("sorry, your key is wrong,do you want to try again?(yes-1 no-2)\n");
                        scanf("%d", &choice);
                        getchar();
                        if (choice != 1)
                            break;
                    }
                }
                if (i == 3)
                    printf("you have enter your key wrongly for 3 times,you have to back compulsorily\n");
                break;
            case 3:
                printf("please enter your new e_mail\n");
                scanf("%s", s);
                getchar();
                while(Register_mail(s)!=0) {
                    printf("sorry,your e_mail can not exist,do you want to try again?(yes-1 no-2)\n");
                    scanf("%d",&choice);
                    getchar();
                    if(choice != 1)
                        break;
                    printf("please enter your new e_mail\n");
                    scanf("%s", s);
                    getchar();
                    strcpy(adm->e_mail, s);
                }
                break;
            case 4:
                break;
            default:
                printf("wrong choice\n");

        }
    }
    return 0;
}


//void cos_show_orders(Node *Rentalhead, char cosid[ID_LEN]) {
//    Node *Rentalcurrent;
//    Node *Rentalnewhead = sort(Rentalhead, comp_rent_start_time);//根据时间筛选生成一个订单新表格
//    RentalInfo *rentalinfo = NULL;
//    //Rentalcurrent = Rentalnewhead;
//    Rentalcurrent = Rentalnewhead;
//    while (Rentalcurrent != NULL) {
//        printf("\n");
//        printf("site_ID\t\tAppoint_ID\t\tstart_time\tend_time\tAppoint_time\tprice\tis_intime\n");
//        rentalinfo = (RentalInfo *) Rentalcurrent->Info;
//        if (strncmp(rentalinfo->Appoint_ID, cosid, strlen(cosid)) == 0) {
//            printf("%s\t\t%s\t%s\t%s\t%s\t%.2lf\t", rentalinfo->site_ID, rentalinfo->Appoint_ID,
//                   rentalinfo->start_time, rentalinfo->end_time, rentalinfo->Appoint_time, rentalinfo->price);
//            if (rentalinfo->is_intime == 1) {
//                printf("yes\n");
//            } else {
//                printf("no\n");
//            }
//            Rentalcurrent = Rentalcurrent->next;
//        }
//    }
//}