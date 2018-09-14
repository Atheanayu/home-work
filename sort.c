#include "gym.h"
#include <string.h>

/* 返回的是链表的头 */
Node * delete(Node * head,Node ** deleteNode){
    Node * p = NULL;
    if(head->next == NULL)
        return NULL;
    if((*deleteNode)==head)
        return (head->next);
    for(p = head;(p->next)!=(*deleteNode);p = p->next)
        ;
    p->next = (*deleteNode)->next;
    (*deleteNode)->next = NULL;
    return head;
}

/* 以下皆是排序的比较方法 */
int comp_cos_name(Node * cos1,Node * cos2){
    return strcmp(((CostumerInfo*)(cos1->Info))->name,((CostumerInfo*)(cos2->Info))->name);
}
int comp_cos_ID(Node * cos1,Node * cos2){
    return strcmp(((CostumerInfo*)(cos1->Info))->ID,((CostumerInfo*)(cos2->Info))->ID);
}
int comp_cos_region(Node * cos1,Node * cos2){/* 如果enum类型改成char * ，这里需要修改 */
//    return ((CostumerInfo*)(cos1->Info))->region-((CostumerInfo*)(cos2->Info))->region;
    return strcmp(((CostumerInfo*)(cos1->Info))->region,((CostumerInfo*)(cos2->Info))->region);
}
int comp_cos_balance(Node * cos1,Node * cos2){
    if((((CostumerInfo*)(cos1->Info))->balance-((CostumerInfo*)(cos2->Info))->balance)>0){
        return 1;
    }else{
        return -1;
    }
}
int comp_cos_age(Node * cos1,Node * cos2){
    return ((CostumerInfo*)(cos1->Info))->age-((CostumerInfo*)(cos2->Info))->age;
}
int comp_cos_default(Node * cos1,Node *cos2){
    return ((CostumerInfo*)(cos1->Info))->default_num-((CostumerInfo*)(cos2->Info))->default_num;
}

int comp_admin_ID(Node * cos1,Node * cos2){
    return strcmp(((AdminInfo*)(cos1->Info))->ID,((AdminInfo*)(cos2->Info))->ID);
}
int comp_admin_name(Node * cos1,Node * cos2){
    return strcmp(((AdminInfo*)(cos1->Info))->name,((AdminInfo*)(cos2->Info))->name);
}

int comp_rent_site_ID(Node * cos1,Node * cos2){
    return strcmp(((RentalInfo*)(cos1->Info))->site_ID,((RentalInfo*)(cos2->Info))->site_ID);
}
//int comp_rent_Appoint_ID(Node * cos1,Node * cos2){
//    return strcmp(((RentalInfo*)(cos1->Info))->Appoint_ID,((RentalInfo*)(cos2->Info))->Appoint_ID);
//}
//int comp_rent_start_time(Node * cos1,Node * cos2){
//    return strcmp(((RentalInfo*)(cos1->Info))->start_time,((RentalInfo*)(cos2->Info))->start_time);
//}
//int comp_rent_Appoint_time(Node * cos1,Node * cos2){
//    return strcmp(((RentalInfo*)(cos1->Info))->Appoint_time,((RentalInfo*)(cos2->Info))->Appoint_time);
//}


int comp_rent_start_time(Node * cos1, Node * cos2) {
    RentalInfo *rental1=(RentalInfo *)cos1->Info;
    RentalInfo *rental2= (RentalInfo *)cos2->Info;
    if (Read_time(rental1->start_time)>Read_time(rental2->start_time))
    {
        return 1;
    }
    return 0;
}

int comp_rent_price(Node * cos1,Node * cos2){
    if((((RentalInfo*)(cos1->Info))->price-((RentalInfo*)(cos2->Info))->price)>0){
        return 1;
    }else{
        return -1;
    }
}
int comp_rent_age(Node * cos1,Node * cos2){
    return ((RentalInfo*)(cos1->Info))->age-((RentalInfo*)(cos2->Info))->age;
}

int comp_site_ID(Node * cos1,Node * cos2){
    return strcmp(((SiteInfo*)(cos1->Info))->ID,((SiteInfo*)(cos2->Info))->ID);
}
int comp_site_vanue(Node * cos1,Node * cos2){
    return strcmp(((SiteInfo*)(cos1->Info))->venue_name,((SiteInfo*)(cos2->Info))->venue_name);
}
int comp_site_region(Node * cos1,Node * cos2){
    return strcmp(((SiteInfo*)(cos1->Info))->region,((SiteInfo*)(cos2->Info))->region);
}
int comp_site_sport(Node * cos1,Node * cos2){
    return strcmp(((SiteInfo*)(cos1->Info))->sport,((SiteInfo*)(cos2->Info))->sport);
}
int comp_site_enter_age(Node *cos1,Node * cos2){
    return ((SiteInfo*)(cos1->Info))->enter_age-((SiteInfo*)(cos2->Info))->enter_age;
}
int comp_site_rent_up(Node *cos1,Node * cos2){
    if((((SiteInfo*)(cos1->Info))->rent-((SiteInfo*)(cos2->Info))->rent)>0){
        return 1;
    }else{
        return -1;
    }
}
int comp_site_rent_down(Node *cos1,Node * cos2){
    if((((SiteInfo*)(cos1->Info))->rent-((SiteInfo*)(cos2->Info))->rent)>0){
        return -1;
    }else{
        return 1;
    }
}
/* 为链表做排序，需要传入链表的头，和比较的方法 */
Node * sort(Node * head,int (*comp_way)(Node *,Node *)){/* 返回的是新生成的链表头 */
    Node * p = NULL;
    Node * max = head;
    Node * new_head = NULL,* previous = NULL;
    while(head != NULL) {
        for (p = head; p->next != NULL; p = p->next) {
            if (comp_way(p, max) > 0)
                max = p;
        }
        head = delete(head,&max);
        if(new_head==NULL)
            new_head = max;
        else
            previous ->next = max;
        previous = max;
        max->next = NULL;
        max = head;
    }
    return new_head;

}
