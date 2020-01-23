#ifndef BOOKINGHOTEL_USER_H
#define BOOKINGHOTEL_USER_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void information(char room_number[10],char room_type[50]){
    char name[128],number[128],date[128];

    printf("Enter your name:");
    scanf("%s",name);

    printf("Enter your phone number:");
    scanf("%s",number);

    printf("Enter your booking date:");
    scanf("%s",date);


    char inf[255] =  "";
    strcat(inf,name);
    strcat(inf," : ");
    strcat(inf,number);
    strcat(inf," : ");
    strcat(inf,date);
    strcat(inf," : ");
    strcat(inf,room_number);
    strcat(inf," : ");
    strcat(inf,strtok(room_type,"."));
    strcat(inf,"\n");


    FILE *file;
    file  = fopen("Customer.txt","a");
    fputs(inf,file);
    fclose(file);
}

void search(int version){
    FILE *file;
    file  = fopen("Customer.txt","r");
    char name[128],number[128],date[128],input[128],room[128],type[128];
    char c;

    do {
        if (version == 0) {
            printf("Enter name to search:");
            scanf("%s", input);
        } else if (version == 1) {
            printf("Enter phone number to search:");
            scanf("%s", input);
        }

        int check = 0;
        while (fscanf(file, "%s : %s : %s : %s : %[^\n]", name, number, date, room, type) != EOF) {
            if (version == 0) {
                if (strcmp(name, input) == 0) {
                    printf("%s : %s : %s : %s : %s\n", name, number, date, room, type);
                    check = 1;
                }
            } else if (version == 1) {
                if (strcmp(number, input) == 0) {
                    printf("%s : %s : %s : %s : %s\n", name, number, date, room, type);
                    check = 1;
                }
            }
        }

        if (check == 0 && version == 0) {
            printf("Can not find this name !!!\n");
        }
        else if (check == 0 && version == 1){
            printf("Can not find this name !!!\n");
        }


        printf("Do you want to search again?(y to search or b to back)");
        getchar();
        scanf("%c", &c);
        if(c == 'b')
            return;
    }while(c == 'y');


}

#endif //BOOKINGHOTEL_USER_H
