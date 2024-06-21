#ifndef function_h
#define function_h
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_NAME 256
#define TABLE_SIZE 15

struct hoten{
    char ho[10];
    char dem[10];
    char ten[10];
};
struct student {
    int id;
    struct hoten student_name;
    char ngaysinh[15];
    float diem;
    struct student* next_student;
};
typedef struct hoten name;
typedef struct student person;
person* hash_table[TABLE_SIZE];

/////------------- Hash Function---------------------//////
unsigned int Hash(int id) {
    unsigned int hash_value = id;
    hash_value = hash_value % TABLE_SIZE;
    return hash_value;
}

// Initialize hash table
void init_hash_table() {
    for (int i = 0; i < TABLE_SIZE; i++) {
        hash_table[i] = NULL;
    }
}
//Check Hash table
bool check_hashtable() {
    for (int i = 0; i < TABLE_SIZE; i++) {
        if (hash_table[i] != NULL) {
            return true;
        }
    }
    return false;
}
// Print the hash table
void print_table() {
    printf("Start\n");
    for (int i = 0; i < TABLE_SIZE; i++) {
        if (hash_table[i] == NULL) {
            printf("\t%i\t---\n", i);
        } else {
            printf("\t%i\t", i);
            person* tmp = hash_table[i];
            while (tmp != NULL) {
                printf("%d - ", tmp->id);
                tmp = tmp->next_student;
            }
            printf("\n");
        }
    }
    printf("End\n");
}

// Insert a person into the hash table
bool hash_table_insert(person* p) {
    if (p == NULL)return false;
    int index = Hash(p->id);
    p->next_student = hash_table[index];
    hash_table[index] = p;
    return true;
}

///////------------ Feature Function--------------- //////

// Add student
void addSV() {
    int id;
    float grade;
    name name_student;
    char ngaysinh[15];

    printf("\nNhap Id sinh vien: ");
    scanf("%d", &id);
    getchar(); // Consume the newline character left by scanf

    printf("\nNhap Ho Ten sinh vien: ");
    printf("\nHo: ");
    fgets(name_student.ho, sizeof(name_student.ho), stdin);
    name_student.ho[strcspn(name_student.ho, "\n")] = '\0';
    printf("Dem: ");
    fgets(name_student.dem, sizeof(name_student.dem), stdin);
    name_student.dem[strcspn(name_student.dem, "\n")] = '\0';
    printf("Ten: ");
    fgets(name_student.ten, sizeof(name_student.ten), stdin);
    name_student.ten[strcspn(name_student.ten, "\n")] = '\0';

    printf("\nNhap Ngay thang nam sinh (dd mm yyyy): ");
    fgets(ngaysinh, sizeof(ngaysinh), stdin);
    ngaysinh[strcspn(ngaysinh, "\n")] = '\0';

    printf("\nNhap Diem so: ");
    scanf("%f", &grade);

    // Insert into hash table based on name (hoten)
    person *p1=(person*)malloc(sizeof(person));
    p1->id = id;
    strcpy(p1->student_name.ho,name_student.ho);
    strcpy(p1->student_name.dem,name_student.dem);
    strcpy(p1->student_name.ten,name_student.ten);
    strcpy(p1->ngaysinh, ngaysinh);
    p1->diem = grade;
    p1->next_student = NULL;
    hash_table_insert(p1);
    printf("Add student succeed!");
}

//Doc file 
void addSV_Data_File() {
    char buffer[100];
    FILE *data_file = fopen("Data_Test_Ver2_Full.csv", "r");

    if (data_file == NULL) {
        perror("Error opening file");
        return;
    }else{
        printf("\n%30s\n","Add data file success");
    }

    // Read data from the file line by line
    while (fgets(buffer, sizeof(buffer), data_file)) {
        // Remove newline character at the end if it exists
        buffer[strcspn(buffer, "\n")] = '\0';

        // Tokenize the line using strtok
        char *id_str = strtok(buffer, ",");
        char *ho = strtok(NULL, ",");
        char *dem = strtok(NULL, ",");
        char *ten = strtok(NULL, ",");
        char *ngaysinh_str = strtok(NULL, ",");
        char *diem_str = strtok(NULL, ",");

        // Allocate memory for a new student node
        struct student *new_student = (struct student *)malloc(sizeof(struct student));
        if (new_student == NULL) {
            perror("Memory allocation failed");
            break; // Exit the loop if memory allocation fails
        }

        // Convert strings to appropriate types and assign to struct fields
        new_student->id = atoi(id_str);
        strncpy(new_student->student_name.ho, ho, sizeof(new_student->student_name.ho));
        strncpy(new_student->student_name.dem,dem, sizeof(new_student->student_name.dem));
        strncpy(new_student->student_name.ten, ten, sizeof(new_student->student_name.ten));
        strncpy(new_student->ngaysinh, ngaysinh_str, sizeof(new_student->ngaysinh));
        new_student->diem = atof(diem_str);
        new_student->next_student = NULL;
        // Add the new student node to the end of the list
        hash_table_insert(new_student);
    }
        fclose(data_file);
}
//Ghi file
void write_data() {
    FILE *ptr = fopen("Newfile_csv.csv", "w");
    if (ptr == NULL) {
        printf("Error opening file!\n");
        return;
    }
    int j=1;
        fputs("Stt",ptr);fputc(',', ptr);fputs("Student ID",ptr);fputc(',', ptr);
        fputs("Student Name",ptr);fputc(',', ptr);fputs("Date of birth",ptr);fputc(',', ptr);
        fputs("Point",ptr);fputc(',', ptr);
        fputc('\n', ptr);
    for (int i = 0; i < TABLE_SIZE; i++) {
        person *tem = hash_table[i];
        while (tem != NULL) {
            char a0[10]; // stt
            char a1[10]; // diem
            char a2[10]; // id
            sprintf(a0, "%d", j);
            sprintf(a1, "%.2f", tem->diem);
            sprintf(a2, "%d", tem->id);

            fputs(a0,ptr);fputc(',', ptr);
            fputs(a2, ptr);fputc(',', ptr);  
            fputs(tem->student_name.ho, ptr);fputc(',', ptr);
            fputs(tem->student_name.dem, ptr);fputc(',', ptr);
            fputs(tem->student_name.ten, ptr);fputc(',', ptr);
            fputs(tem->ngaysinh, ptr);fputc(',', ptr);   
            fputs(a1, ptr);
            fputc('\n', ptr);
            j++;
            tem = tem->next_student;
        }
    }

    fclose(ptr);
}
// Delete Student
void deleteSV() {
    if (check_hashtable==false) {
        printf("The list student is empty\n");
    } else {
        int mssv;
        printf("\nEnter the student ID to be deleted: ");
        scanf("%d", &mssv);
        // hash mssv
        unsigned int position=Hash(mssv);
        person *p=hash_table[position];
        person *prev=NULL;
        while(p!=NULL&&(p->id!=mssv)){
            prev=p;
            p=p->next_student;
        }
        if (p == NULL) {
            printf("Not found student ID = %d\n", mssv);
        } else {
            if (prev == NULL) {
                hash_table[position] = p->next_student;
                } else {
                    prev->next_student = p->next_student;
                }
            free(p); 
            printf("Student ID = %d deleted successfully\n", mssv);
        }
    }
}

// Update Grade
void update_grade() {
    if (check_hashtable() == false) {
        printf("The list is empty\n");
    } else {
        int count = 1,mssv;
        float new_grade;
        printf("\nUpdate the grade's student  || Enter '11' to stop updating");
        printf("\nEnter the student id you want to start updating: ");
        scanf("%d",&mssv);

        // Tim kiem mssv bang ham bam
        unsigned int position = Hash(mssv);
        printf("%5s \t %-7s \t %-5s \t %-5s \t %-7s\t %-5s\n", 
                        "STT", "Ho", "Dem", "Ten", "ID", "Point");
    
        for(int i=position;i<TABLE_SIZE;i++){
            if(hash_table[i]== NULL){
                continue;
            }else{
                person* tmp = hash_table[i];
                while(tmp!=NULL){
                    printf("%5d \t %-7s \t %-5s \t %-5s \t %-7d \t %-5.2f -> ", 
                            count, tmp->student_name.ho,tmp->student_name.dem,
                                tmp->student_name.ten, tmp->id, tmp->diem);
                    scanf("%f",&new_grade);
                    if(new_grade==11){
                        return;
                    }
                    tmp->diem=new_grade;
                    tmp=tmp->next_student;
                    count++;
                }
            }
        }
    }
}

//Search Student
void search_student(){
    if(check_hashtable()==false){
        printf("The list is empty");
    }else{
        int mssv;
        printf("Enter the Student ID you want to find: ");scanf("%d",&mssv);
        //Hash mssv
        unsigned int position = Hash(mssv);
        person *tmp=hash_table[position];
        while (tmp!=NULL&&(tmp->id!=mssv)) {
            tmp=tmp->next_student;
        }
        if(tmp==NULL){
            printf("Not found student ID : %d",mssv);
        }else {
            printf("\t %-7s \t %-5s \t %-5s \t %-7s \t %-12s \t %-5s\n", 
                "Ho", "Dem", "Ten", "ID", "Date of birth", "Point");
            printf("\t %-7s \t %-5s \t %-5s \t %-7d \t %-12s \t %-5.2f \n", tmp->student_name.ho,tmp->student_name.dem,
                                            tmp->student_name.ten, tmp->id, tmp->ngaysinh, tmp->diem);
        }
    }
}

//Modify
void modify_student() {
    if (check_hashtable() == false) {
        printf("The list student is empty\n");
    } else {
        int id;
        char t;
        printf("Enter Student ID that you want to modify: ");
        scanf("%d", &id);

        // hash id
        unsigned int position = Hash(id);
        person *p=hash_table[position];
        while (p!=NULL&&(p->id!=id)) {
            p=p->next_student;
        }
        if(p==NULL){
            printf("Not found student ID : %d",id);
        }else {
            
            do{ 
                char data;
                printf("Select the student id %d you want to modify: ",id);
                printf("\n1 - Student name");
                printf("\n2 - Date of birth");
                printf("\n3 - Student ID");
                printf("\n4 - Point");
                printf("\nData : ");
                scanf(" %c", &data); // Space before %c to consume any newline left in input buffer
                switch(data){
                    case '1': {
                        char new_ho[10];
                        char new_dem[10];
                        char new_ten[10];
                        printf("\nHo: %s", p->student_name.ho);
                        printf("\nDem: %s", p->student_name.dem);
                        printf("\nTen: %s", p->student_name.ten);
                        printf("\nEnter new student name: ");
                        printf("\nNew Họ?: ");
                        fgets(new_ho, sizeof(new_ho), stdin);
                        new_ho[strcspn(new_ho, "\n")] = '\0';
                        strcpy(p->student_name.ho, new_ho);
                        printf("\nNew Ðệm: ");
                        fgets(new_dem, sizeof(new_dem), stdin);
                        new_dem[strcspn(new_dem, "\n")] = '\0';
                        strcpy(p->student_name.dem, new_dem);
                        printf("\nNew Tên: ");
                        fgets(new_ten, sizeof(new_ten), stdin);
                        new_ten[strcspn(new_ten, "\n")] = '\0';
                        strcpy(p->student_name.ten, new_ten);
                        

                        printf("Student details updated successfully!\n");
                        break;
                    }
                    case '2': {
                        char new_ngaysinh[15];
                        printf("\nNgay Sinh: %s", p->ngaysinh);
                        getchar();
                        printf("\nEnter new date of birth (dd mm yyyy): ");
                        fgets(new_ngaysinh, sizeof(new_ngaysinh), stdin);
                        new_ngaysinh[strcspn(new_ngaysinh, "\n")] = '\0';
                        strcpy(p->ngaysinh, new_ngaysinh);
                        printf("Student details updated successfully!\n");
                        break;
                    }
                    case '3': {
                        int  new_mssv;
                        printf("\nMSSV: %d", p->id);
                        printf("\nEnter new student id: ");
                        scanf("%d", &new_mssv);
                        struct student *new_student = (struct student *)malloc(sizeof(struct student));
                        if (new_student == NULL) {
                            perror("Memory allocation failed");
                            break; // Exit the loop if memory allocation fails
                        }

                        new_student->id = new_mssv;
                        strncpy(new_student->student_name.ho, p->student_name.ho, sizeof(new_student->student_name.ho));
                        strncpy(new_student->student_name.dem, p->student_name.dem, sizeof(new_student->student_name.dem));
                        strncpy(new_student->student_name.ten, p->student_name.ten, sizeof(new_student->student_name.ten));
                        strncpy(new_student->ngaysinh, p->ngaysinh, sizeof(new_student->ngaysinh));
                        new_student->diem = p->diem;
                        new_student->next_student = NULL;
                        //xoa mssv cu
                        deleteSV();
                        hash_table_insert(new_student);
                        printf("Student details updated successfully!\n");
                        break;
                    }
                    case '4': {
                        float new_diem;
                        printf("\nOld point: %.2f", p->diem);
                        printf("\nEnter new point: ");
                        scanf("%f", &new_diem);
                        p->diem = new_diem;
                        printf("Student details updated successfully!\n");
                        break;
                    }
                    default: {
                        printf("Invalid option selected. Please select a valid option (1-4).\n");
                    }
                }
                
                printf("Do you want to continue y/n? ");
                scanf(" %c", &t);
            }while(t=='y');
            
        } 
    }
}
//Print list students
void Print_list_student() {
    printf("%5s \t %-7s \t %-5s \t %-5s \t %-7s \t %-12s \t %-5s\n", 
           "STT", "Ho", "Dem", "Ten", "ID", "Date of birth", "Point");
    int count = 1;

    for (int i = 0; i < TABLE_SIZE; i++) {
        if (hash_table[i] != NULL) {
            person* tmp = hash_table[i];
            while (tmp != NULL) {
                printf("%5d \t %-7s \t %-5s \t %-5s \t %-7d \t %-12s \t %-5.2f \n", 
                       count, tmp->student_name.ho, tmp->student_name.dem, tmp->student_name.ten, 
                       tmp->id, tmp->ngaysinh, tmp->diem);
                count++;
                tmp = tmp->next_student;
            }
        }
    }
}

#endif
