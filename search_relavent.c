#include <stdio.h>
#include <memory.h>
#include "gym.h"

//int main(){
//    Node * head_site = _private_init(FILE_SITE_PATH,_private_get_value_SiteInfo);
//    Node * head_rent = _private_init(FILE_RENT_PATH,_private_get_value_rental);
//    Node * head_cos  = _private_init(FILE_COS_PATH,_private_get_value_cos);
//    CostumerInfo cos = *((CostumerInfo*)(head_cos->Info));
//    search(head_site,head_rent,cos);
//    return 0;
//}

void search(Node* head_site,Node * head_rent,CostumerInfo cos)    //–ﬁ∏ƒ¡À£¨≤ª÷™µ¿ «∑Ò’˝»∑£ø  ‘Ÿ¥Œ–ﬁ∏ƒ¡À£¨”¶∏√’˝»∑¡À∞…
{
    int n=0;
    char str[ID_LEN];
    char choice;
    Node * node;
    SiteInfo * info;

    search_menu();		//œ‘ æÀ—À˜≤Àµ•
    while ((n=get_int())!=4)
    {
//        getchar();
        switch(n)
        {
            case 1:
                printf("Please enter the Site ID to search:\n");
                printf("Site ID = \n");
                gets(str);
                if((node = search_site(head_site,str))==NULL){
                    fprintf(stderr,"we don't have this site.");    //¥À¥¶Œ™ ≤√¥”√fprint£ø
                    break;
                }
                else{
                    info = (SiteInfo *)(node->Info);
                    printf("\n");
                    printf("Site Info:\n");
                    printf("ID\t venue name\t region\t sport\t enter age\t rent\t introduction\n");
                    printf("%s\t %s\t %s\t %s\t %d\t %.2lf\t %s\n", info->ID, info->venue_name, info->region, info->sport,
                           info->enter_age, info->rent, info->intro);
                    printf("Do you want to reserve? (y/n)\n"); //,yes‘§∂®£¨no∑µªÿ≤È—Ø∑Ω ΩΩÁ√Ê
                    if (get_choice()=='y'){
                        reserve(str,head_site,head_rent,&cos);
                    }
                    break;
                }

            case 2:
                category_menu();
                while ((n=get_int())!=4)
                {
                    switch(n) {
                        case 1:
                            _private_book_venue_menu();
                            while ((n = get_int()) != 4) {
                                switch (n) {
                                    case 1:
                                        search_venue(head_site, "CP_CENTER");
                                        printf("Do you want to reserve? (y/n)\n"); //,yes‘§∂®£¨no∑µªÿ≤È—Ø∑Ω ΩΩÁ√Ê
                                        if (get_choice() == 'y') {
                                            printf("Please enter the Site ID to reserve:\n");
                                            printf("Site ID= ");
                                            gets(str);
                                            reserve(str,head_site,head_rent,&cos);
                                        }
                                        break;
                                    case 2:
                                        search_venue(head_site, "HD_CENTER");
                                        printf("Do you want to reserve? (y/n)\n"); //,yes‘§∂®£¨no∑µªÿ≤È—Ø∑Ω ΩΩÁ√Ê
                                        if (get_choice() == 'y') {
                                            printf("Please enter the Site ID to reserve:\n");
                                            printf("Site ID= ");
                                            gets(str);
                                            reserve(str,head_site,head_rent,&cos);
                                        }
                                        break;
                                    case 3:
                                        search_venue(head_site, "CY_CENTER");
                                        printf("Do you want to reserve? (y/n)\n"); //,yes‘§∂®£¨no∑µªÿ≤È—Ø∑Ω ΩΩÁ√Ê
                                        if (get_choice() == 'y') {
                                            printf("Please enter the Site ID to reserve:\n");
                                            printf("Site ID= ");
                                            gets(str);
                                            reserve(str,head_site,head_rent,&cos);

                                        }
                                        break;
                                    default:
                                        fprintf(stderr, "Wrong Choice!");
                                        break;
                                }
                                _private_book_venue_menu();
                            }
                            break;
                        case 2:
                            _private_book_sport_menu();
                            while ((n = get_int()) != 4) {
                                switch (n) {
                                    case 1:
                                        search_sport(head_site, "soccer");
                                        printf("Do you want to reserve? (y/n)\n"); //,yes‘§∂®£¨no∑µªÿ≤È—Ø∑Ω ΩΩÁ√Ê
                                        if (get_choice() == 'y') {
                                            printf("Please enter the Site ID to reserve:\n");
                                            printf("Site ID= ");
                                            gets(str);
                                            reserve(str,head_site,head_rent,&cos);

                                        }
                                        break;
                                    case 2:
                                        search_sport(head_site, "basketball");
                                        printf("Do you want to reserve? (y/n)\n"); //,yes‘§∂®£¨no∑µªÿ≤È—Ø∑Ω ΩΩÁ√Ê
                                        if (get_choice() == 'y') {
                                            printf("Please enter the Site ID to reserve:\n");
                                            printf("Site ID= ");
                                            gets(str);
                                            reserve(str,head_site,head_rent,&cos);

                                        }
                                        break;
                                    case 3:
                                        search_sport(head_site, "badminton");
                                        printf("Do you want to reserve? (y/n)\n"); //,yes‘§∂®£¨no∑µªÿ≤È—Ø∑Ω ΩΩÁ√Ê
                                        if (get_choice() == 'y') {
                                            printf("Please enter the Site ID to reserve:\n");
                                            printf("Site ID= ");
                                            gets(str);
                                            reserve(str,head_site,head_rent,&cos);

                                        }
                                        break;
                                    default:
                                        fprintf(stderr, "Wrong Choice!");
                                        break;
                                }
                                _private_book_sport_menu();
                            }
                            break;
                        case 3:
                            _private_book_region_menu();
                            while ((n = get_int()) != 4) {
                                switch (n) {
                                    case 1:
                                        search_region(head_site, "BEI_CP");
                                        printf("Do you want to reserve? (y/n)\n"); //,yes‘§∂®£¨no∑µªÿ≤È—Ø∑Ω ΩΩÁ√Ê
                                        if (get_choice() == 'y') {
                                            printf("Please enter the Site ID to reserve:\n");
                                            printf("Site ID= ");
                                            gets(str);
                                            reserve(str,head_site,head_rent,&cos);
                                        }
                                        break;
                                    case 2:
                                        search_region(head_site, "BEI_HD");
                                        printf("Do you want to reserve? (y/n)\n"); //,yes‘§∂®£¨no∑µªÿ≤È—Ø∑Ω ΩΩÁ√Ê
                                        if (get_choice() == 'y') {
                                            printf("Please enter the Site ID to reserve:\n");
                                            printf("Site ID= ");
                                            gets(str);
                                            reserve(str,head_site,head_rent,&cos);
                                            break;
                                        } else
                                            break;
                                    case 3:
                                        search_region(head_site, "BEI_CY");
                                        printf("Do you want to reserve? (y/n)\n"); //,yes‘§∂®£¨no∑µªÿ≤È—Ø∑Ω ΩΩÁ√Ê
                                        if (get_choice() == 'y') {
                                            printf("Please enter the Site ID to reserve:\n");
                                            printf("Site ID= ");
                                            gets(str);
                                            reserve(str,head_site,head_rent,&cos);
                                            break;
                                        } else
                                            break;
                                    default:
                                        fprintf(stderr, "Wrong Choice!");
                                        break;
                                }
                            }
                            break;
                    }
            break;
            case 3:
                sort_menu();
            while ((n=get_int())!=5)
            {
                switch(n)
                {
                    case 1:
                        print_SiteInfo(sort(head_site,comp_site_rent_up));
                        break;

                    case 2:
                        print_SiteInfo(sort(head_site,comp_site_rent_down));
                        break;
                    case 3:
//                        print_SiteInfo(sort(head_site,comp_site_rent));
                        break;
                    case 4:
//                        print_SiteInfo(sort(head_site,comp_site_rent));
                        break;
                    default:
                        fprintf (stderr,"Wrong Choice!\n");
                        break;
                }
                sort_menu();
            }
            break;
            default:
                fprintf (stderr,"Wrong Choice!\n");
                break;
        }
        }
        search_menu();		//œ‘ æÀ—À˜≤Àµ•
    }
}











