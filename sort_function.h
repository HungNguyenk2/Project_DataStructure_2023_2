#ifndef extend_h
#define extend_h
#include "main_function.h"
//Sort list student
// -------- Ham in danh sach sau khi sap xep ---- //
void print_students(person* start,int *j) {
    while (start != NULL) {
        printf("%5d \t %-7s\t %-5s\t %-5s \t %-7d \t %-12s \t %-5.2f \n", 
               *j, start->student_name.ho,start->student_name.dem,start->student_name.ten, start->id, start->ngaysinh,start->diem);
        start = start->next_student;
        (*j)++;
    }
}
void print_sort(int number_bucket,person *bucket[],int dinhdang ){
        printf("What are the options?\n");
    char t;
    do{
        printf("\t1-Show student list sorted\n");
        printf("\t2-Printf to file\n");
        printf("\tx-Exit\n");
        scanf(" %c",&t);
        switch(t){
            case '1':{
                if(dinhdang==1){
                printf("%5s \t %-7s \t %-5s \t %-5s \t %-7s \t %-12s \t %-5s\n", 
                    "STT", "Ho", "Dem", "Ten", "ID", "Date of birth", "Point");
                int j = 1;
                for (int i=0 ; i <=number_bucket - 1; i++) {
                    print_students(bucket[i], &j);
                }
                break;
                }else{
                printf("%5s \t %-7s \t %-5s \t %-5s \t %-7s \t %-12s \t %-5s\n", 
                    "STT", "Ho", "Dem", "Ten", "ID", "Date of birth", "Point");
                int j = 1;
                for (int i=number_bucket - 1 ; i>=0; i--) {
                    print_students(bucket[i], &j);
                }
                break;
                }
            }
            case '2':{
                FILE *ptr = fopen("Sorted_Data.csv", "w");
                if (ptr == NULL) {
                    printf("Error opening file!\n");
                    return;
                }
                    fputs("Stt,Student ID,Student Name,Date of birth,Point\n", ptr);
                int j = 1;

                // Ghi dữ liệu từ các bucket đã sắp xếp vào file
                if(dinhdang==1){
                for (int i = 0; i <=number_bucket - 1; i++) {
                    struct student* current = bucket[i];
                    while (current != NULL) {
                        fprintf(ptr, "%d,%d,%s %s %s,%s,%.2f\n",
                                j++, current->id, current->student_name.ho, current->student_name.dem, 
                                current->student_name.ten, current->ngaysinh, current->diem);
                        current = current->next_student;
                    }
                }
                }else{
                for (int i=number_bucket - 1 ; i>=0; i--) {
                    struct student* current = bucket[i];
                    while (current != NULL) {
                        fprintf(ptr, "%d,%d,%s %s %s,%s,%.2f\n",
                                j++, current->id, current->student_name.ho, current->student_name.dem, 
                                current->student_name.ten, current->ngaysinh, current->diem);
                        current = current->next_student;
                    }
                }
                }
                printf("Write to file succeed\n");
                fclose(ptr);
                break;
            }
            default:{
                if(t!='x'){
                    printf("Invalid choice. Please select again.\n");
                }
            }
        }
    }while(t!='x');
}
// -------- Hàm chèn node theo thứ tự sắp xếp trong bucket ---
person* insert_linked(person *bucket, person *A) {
    if(A==NULL){
        return bucket;
    }else{
        person *node=(person*)malloc(sizeof(person));
        if(node==NULL){
            printf("Memory allocation Failed");
            return bucket;
        }
        strcpy(node->student_name.ho,A->student_name.ho);
        strcpy(node->student_name.dem,A->student_name.dem);
        strcpy(node->student_name.ten,A->student_name.ten);
        strcpy(node->ngaysinh,A->ngaysinh);
        node->diem=A->diem;
        node->id=A->id;
        node->next_student=NULL;
        //Neu bucket rong
        if(bucket==NULL){
            return node;
        }
        person *temp=bucket;
        person *pre=NULL;
        while(temp!=NULL&&(temp->diem>A->diem)){
            pre=temp;
            temp=temp->next_student;
        }
        if(pre==NULL){
            node->next_student=temp;
            bucket=node;
        }else{
            pre->next_student=node;
            node->next_student=temp;            
        }
        return bucket;
    }
}

// Hàm sắp xếp sinh viên theo điểm
void bucket_sort_by_grade() {
    const int number_bucket = 11; // Chia thành 11 khoảng điểm
    person *bucket[number_bucket]; // Khởi tạo
    for (int i = 0; i < number_bucket; i++) { 
        bucket[i] = NULL;
    }

    // chuyển sinh viên hashtable vào bucket
    for (int i = 0; i < TABLE_SIZE; i++) {
        person *tem = hash_table[i];
        while (tem != NULL) {
            int position = (int)(tem->diem);
            bucket[position]=insert_linked(bucket[position], tem); // chèn m?i sinh viên vào m?i bucket và s?p x?p
            tem=tem->next_student;
        }
    }
        int dinhdang=0;
        print_sort(number_bucket,bucket,dinhdang);
}

// Sắp xếp sinh viên theo tên
int sosanh(person *A,person *B){
    int temp=strcmp(A->student_name.ten,B->student_name.ten);
    if(temp==0){
        int temp2=strcmp(A->student_name.dem,B->student_name.dem);
        if(temp2==0){
            int temp3=strcmp(A->student_name.ho,B->student_name.ho);
            if(temp3==0){
                return 1;
            }else{
                if(temp3<0){
                    return 1;
                }else{
                    return 0;
                }
            }
        }else{
                if(temp2<0){
                    return 1;
                }else{
                    return 0;
                }
        }
    }else{
                if(temp<0){
                    return 1;
                }else{
                    return 0;
                }
    }
}
person* insert_linked2(person *bucket, person *A) {
    if(A==NULL){
        return bucket;
    }else{
        person *node=(person*)malloc(sizeof(person));
        if(node==NULL){
            printf("Memory allocation Failed");
            return bucket;
        }
        strcpy(node->student_name.ho,A->student_name.ho);
        strcpy(node->student_name.dem,A->student_name.dem);
        strcpy(node->student_name.ten,A->student_name.ten);
        strcpy(node->ngaysinh,A->ngaysinh);
        node->diem=A->diem;
        node->id=A->id;
        node->next_student=NULL;
        //Neu bucket rong
        if(bucket==NULL){
            return node;
        }
        person *temp=bucket;
        person *pre=NULL;
        while(temp!=NULL&&(sosanh(temp,A)==1)){
            pre=temp;
            temp=temp->next_student;
        }
        if(pre==NULL){
            node->next_student=temp;
            bucket=node;
        }else{
            pre->next_student=node;
            node->next_student=temp;            
        }
        return bucket;
    }
}

void bucket_sort_by_name() {
    const int number_bucket = 26;
    person *bucket[number_bucket];
    for (int i = 0; i < number_bucket; i++) { 
        bucket[i] = NULL;
    }

    // chuyển sinh viên hashtable vào bucket
    for (int i = 0; i < TABLE_SIZE; i++) {
        person *tem = hash_table[i];

        while (tem != NULL) {
            int position = (int)(tem->student_name.ten[0])%65;
            bucket[position]=insert_linked2(bucket[position], tem); // chèn m?i sinh viên vào m?i bucket và s?p x?p
            tem=tem->next_student;
        }
    }
    int dinhdang=1;
    print_sort(number_bucket,bucket,dinhdang);
}


#endif