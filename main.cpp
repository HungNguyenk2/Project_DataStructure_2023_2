#include <stdio.h>
#include "main_function.h"
#include "sort_function.h"
int main() {
    init_hash_table();
    char choice[3]; 
    int h;
    int a;
    
    do {
        printf("\n\t********************************************************\n");
        printf("\t ---------      Menu - Select the function       ---------\n");              
        printf("\t1 - Add student\n");
        printf("\t2 - Add list student from data file\n");
        printf("\t3 - Write list student to data file\n");
        printf("\t4 - Delete student\n");
        printf("\t5 - Update grade's students\n");
        printf("\t6 - Modify student details\n");
        printf("\t7 - Searching student\n");
        printf("\t8 - Sort students\n");
        printf("\t9 - Print list student\n");
        printf("\t10 - Print table hash\n");
        printf("\tx - Exit the interface\n");
        printf("\t  ********************************************************\n");
        printf("\tWhat are your options?: ");
        scanf("%2s", choice); 
        a = atoi(choice);
        
        switch (a) {
            case 1: {
                addSV();
                break;
            }
            case 2: {
                addSV_Data_File();
                break;
            }
            case 3: {
                write_data();
                break;
            }
            case 4: {
                deleteSV();
                break;
            }
            case 5: {
                update_grade();
                break;
            }
            case 6: {
                modify_student();
                break;
            }
            case 7: {
                search_student();
                break;
            }
            case 8: {
                printf("1-Sort by score\n");
                printf("2-Sort by name\n");
                scanf("%d",&h);
                switch(h){
                    case 1:{
                        bucket_sort_by_grade();
                        break;
                    }
                    case 2:{
                        bucket_sort_by_name();
                        break;
                    }
                    default: break;
                }
                
                break;
            }
            case 9: {
                Print_list_student();
                break;
            }
            case 10: {
                print_table();
                break;
            }
            default: {
                if (strcmp(choice, "x") != 0) {
                    printf("Invalid choice. Please select again.\n");
                }
            }
        }

        if (strcmp(choice, "x") == 0) {
            break; // Thoát khỏi vòng lặp nếu người dùng chọn "x"
        }

        printf("Do you want to continue y/n? ");
        char t;
        scanf(" %c", &t);
        if (t == 'n') {
            break; // Thoát khỏi vòng lặp nếu người dùng chọn 'n'
        }

    } while (1); 

    return 0;
}
