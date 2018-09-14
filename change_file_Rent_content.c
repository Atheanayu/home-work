#include <stdio.h>
#include <memory.h>
#include "gym.h"

//int main(){
//    Node * head_rent = _private_init(FILE_RENT_PATH,_private_get_value_rental);
//    cancel_order(head_rent,((RentalInfo*)(head_rent->Info))->Appoint_ID);
//    return 0;
//}

int change_file_Site_content(char * path,Node * head){
    FILE * fp = fopen(path,"w");
    SiteInfo * info;
    for(Node * p = head;p!=NULL;p=p->next){
       info = (SiteInfo *)(p->Info);
       fprintf(fp,"#\n");
       fprintf(fp,"ID:%s\n",info->ID);
       fprintf(fp,"venue_name:%s\n",info->venue_name);
       fprintf(fp,"region:%s\n",info->region);
       fprintf(fp,"sport:%s\n",info->sport);
       fprintf(fp,"enter_age:%d\n",info->enter_age);
       fprintf(fp,"rent:%.2f\n",info->rent);
    }
    fclose(fp);
    return 0;
}

int change_file_admin_content(char * path,Node * head){
    FILE *fp = fopen(path,"w");
    AdminInfo * info;
    for(Node * p = head;p!=NULL;p=p->next){
        info = (AdminInfo *)(p->Info);
        fprintf(fp,"#\n");
        fprintf(fp,"ID:%s\n",info->ID);
        fprintf(fp,"name:%s\n",info->name);
        fprintf(fp,"venue_name:%s\n",info->venue_name);
        fprintf(fp,"key:%s\n",info->key);
        fprintf(fp,"e_mail:%s\n",info->e_mail);
        fprintf(fp,"sex:%s\n",info->sex);
        fprintf(fp,"phone_num:%s\n",info->phone_num);
    }
    return 0;
}

int change_file_Rent_content(char * path,Node * head){
    FILE * fp = fopen(path,"w");
    RentalInfo * info;
    for(Node * p = head;p!=NULL;p=p->next){
        info = (RentalInfo*)(p->Info);
        fprintf(fp,"#\n");
        fprintf(fp,"site_ID:%s\n",info->site_ID);
        fprintf(fp,"Appoint_ID:%s\n",info->Appoint_time);
        fprintf(fp,"start_time:%s\n",info->start_time);
        fprintf(fp,"end_time:%s\n",info->end_time);
        fprintf(fp,"Appoint_time:%s\n",info->Appoint_time);
        if(info->is_intime==true){
            fprintf(fp,"is_intime:true\n");
        }else{
            fprintf(fp,"is_intime:false\n");
        }
        fprintf(fp,"price:%.2f\n",info->price);
        fprintf(fp,"sex:%s\n",info->sex);
        fprintf(fp,"age:%d\n",info->age);
        fprintf(fp,"is_complete:%d\n",info->is_complete);
    }
    fclose(fp);
    return 0;
}

int change_file_cos_content(char * path,Node * head){
    FILE * fp = fopen(path,"w");
    CostumerInfo * info;
    for(Node * p = head;p!=NULL;p=p->next){
        info = (CostumerInfo*)(p->Info);
        fprintf(fp,"#\n");
        fprintf(fp,"ID:%s\n",info->ID);
        fprintf(fp,"name:%s\n",info->name);
        fprintf(fp,"phone_num:%s\n",info->phone_num);
        fprintf(fp,"key:%s\n",info->key);
        fprintf(fp,"e_mail:%s\n",info->e_mail);
        fprintf(fp,"sex_type:%s\n",info->sex);
        fprintf(fp,"region_type:%s\n",info->region);
        fprintf(fp,"balance:%.2f\n",info->balance);
        fprintf(fp,"age:%d\n",info->age);
        fprintf(fp,"default_num:%s\n",info->region);
    }
    fclose(fp);
    return 0;
}

int cancel_order(Node * head_rent,char * Appoint_ID){/* 取消订单 */
    RentalInfo * info;
    char s[40];
    for(Node * p = head_rent;p != NULL;p = p->next){
        strcpy(s,((RentalInfo*)(p->Info))->start_time);
        info = ((RentalInfo*)(p->Info));
        if(strcmp(Appoint_ID,info->Appoint_ID)==0){
            if(Time_Check(time_cut(s))==0){
                fprintf(stderr,"sorry,you can just cancel your order before 24h\n");
                return -1;
            }
            info->is_complete = 1;
            return 0;/* 成功取消订单 */
        }
    }
    return -1;/* 未能找到订单 */
}
