//
// Created by Athena on 2018/9/11.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "gym.h"

/* 需要一个销毁链表的操作,代码风格最后需要修改 */

//Node * _private_init(char * path,int (*_private_get_value)(FILE*,Node*));
//int _private_get_value_cos(FILE *fp,Node * c);
//int _private_get_value_admin(FILE *fp,Node * c);
//int _private_get_value_rental(FILE *fp,Node * c);
//int _private_get_value_SiteInfo(FILE *fp,Node * c);


//int main(){
//    Node * head;
//    head = _private_init(FILE_AMIN_PATH,_private_get_value_admin);
//
//    return 0;
//}


/* 用于从文件中读取数据，创建链表，函数指针是为了一个函数为多个链表服务 */
Node * _private_init(char * path,int (*_private_get_value)(FILE*,Node*))
{
    char s[40];
    char c;
    FILE * fp = fopen(path,"r");
    fscanf(fp,"%s\n",s);
    Node * head = NULL;
    if(strcmp(s,"#")!=0) {
        fprintf(stderr,"sorry,there is not information");
        return head;
    }
    Node * current = malloc(sizeof(Node));
    Node * previous=NULL;
    while(1)//创建链表
    {
        if(head == NULL)
            head = current;
        else
            previous->next = current;
        current->next = NULL;
        if(_private_get_value(fp,current)==-1){
            fprintf(stderr, "the information is wrong");/* 考虑将这个放到外面 */
            return NULL;
        }
        previous = current;
        c = (char)fgetc(fp);
        if(c==EOF)
            break;
        else if(c == '#')
            fgetc(fp);
        else
            return NULL;
        current = (Node *)malloc(sizeof(Node));
    }
    fclose(fp);
    return head;
}

/* 用于赋值 */
int _private_get_value_cos(FILE *fp,Node * c){
    c->Info = (CostumerInfo *)malloc(sizeof(CostumerInfo));
    CostumerInfo * current = (CostumerInfo *)(c->Info);
    char s[40];
    fscanf(fp,"ID:%s\n",current->ID);
    fscanf(fp,"name:%s\n",current->name);
    fscanf(fp,"phone_num:%s\n",current->phone_num);
    fscanf(fp,"key:%s\n",current->key);
    fscanf(fp,"e_mail:%s\n",current->e_mail);
    fscanf(fp,"sex_type:%s\n",current->sex);
//    current->sex = (enum sex_type)_private_find_enum(s,"sex");
    fscanf(fp,"region_type:%s\n",current->region);
//    current->region = (enum region_type)_private_find_enum(s,"region");
    if(fscanf(fp,"balance:%lf\n",&(current->balance))==-1){
        return -1;
    }
    if(fscanf(fp,"age:%d\n",&(current->age))==-1){
        return -1;
    }
    if(fscanf(fp,"default_num:%d\n",&(current->default_num))==-1){
        return -1;
    }
    return 0;
}
int _private_get_value_admin(FILE *fp,Node * c){
    c->Info = (AdminInfo *)malloc(sizeof(AdminInfo));
    AdminInfo * current = (AdminInfo *)(c->Info);
    char s[40];
    fscanf(fp,"ID:%s\n",current->ID);
    fscanf(fp,"name:%s\n",current->name);
    fscanf(fp,"venue_name:%s\n",current->venue_name);
    fscanf(fp,"key:%s\n",current->key);
    fscanf(fp,"e_mail:%s\n",current->e_mail);
    fscanf(fp,"sex:%s\n",current->sex);
    fscanf(fp,"phone_num:%s\n",current->phone_num);
    return 0;
}
int _private_get_value_rental(FILE *fp,Node * c){
    c->Info = (RentalInfo *)malloc(sizeof(RentalInfo));
    RentalInfo * current = (RentalInfo *)(c->Info);
    char s[40];
    fscanf(fp,"site_ID:%s\n",current->site_ID);
    fscanf(fp,"Appoint_ID:%s\n",current->Appoint_ID);
    fscanf(fp,"start_time:%s\n",current->start_time);
    fscanf(fp,"end_time:%s\n",current->end_time);
    fscanf(fp,"Appoint_time:%s\n",current->Appoint_time);
    fscanf(fp,"is_intime:%s\n",s);
    if(strcmp(s,"true")==0)
        current->is_intime = true;
    else if(strcmp(s,"false")==0)
        current->is_intime = false;
    else
        return -1;
    fscanf(fp,"price:%lf\n",&(current->price));
    fscanf(fp,"sex:%s\n",current->sex);
    if((fscanf(fp,"age:%d\n",&(current->age)))==-1)
        return -1;
    fscanf(fp,"is_complete:%d\n",&(current->is_complete));
    return 0;
}
int _private_get_value_SiteInfo(FILE *fp,Node * c){
    c->Info = (SiteInfo*)malloc(sizeof(SiteInfo));
    SiteInfo * current = (SiteInfo *)(c->Info);
    char s[40];
    fscanf(fp,"ID:%s\n",current->ID);
    fscanf(fp,"venue_name:%s\n",current->venue_name);
    fscanf(fp,"region:%s\n",current->region);
    fscanf(fp,"sport:%s\n",current->sport);
    fscanf(fp,"enter_age:%d\n",&(current->enter_age));
    fscanf(fp,"rent:%lf\n",&(current->rent));
    return 0;
}

int _private_free_list(Node * head){
    Node * pr = head;
    for(Node * p = head;p!=NULL;p = pr){
        pr = p->next;
        free(p->Info);
        free(p);
    }
    return 0;
}