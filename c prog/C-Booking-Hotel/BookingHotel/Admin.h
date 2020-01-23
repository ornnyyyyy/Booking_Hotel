#ifndef BOOKINGHOTEL_ADMIN_H
#define BOOKINGHOTEL_ADMIN_H


#include<stdio.h>
#include<string.h>
#include <stdlib.h>
#include <ctype.h>
#include "Hotel.h"


void seek_to_next_line( void )
{
    int c;
    while( (c = fgetc( stdin )) != EOF && c != '\n' );
}


void checkout(char room[10],char name[10]){
    FILE *cuFile,*file;
    int check_first = 1,check = 1;
    char buffer[255];
    char a[20] = "";
    strcat(a,name);
    cuFile = fopen("Customer.txt","r");
    file = fopen("buffer.txt","w");
    char bname[25],bphone[10],bdate[10],broom[10],btype[30],type[100],droom[10];
    while(fgets(buffer,255,cuFile)){
        fputs(buffer,file);
    }
    fclose(file);
    fclose(cuFile);
    cuFile = fopen("Customer.txt","w");
    file = fopen("buffer.txt","r");
    fseek(file,-1,SEEK_CUR);
    while(fgets(buffer,255,file)!= NULL){
        char nn[100];
        sscanf(buffer,"%s : %s : %s : %s : %[^\n]",nn,bphone,bdate,broom,btype);
        if(!strcmp(name,nn)&& !strcmp(broom,room)){
            check = 0;
            strcpy(droom,broom);
            strcpy(type,btype);
            continue;
        }
        else{
            char sub[255] = "";
            strcat(sub,nn);
            strcat(sub," : ");
            strcat(sub,bphone);
            strcat(sub," : ");
            strcat(sub,bdate);
            strcat(sub," : ");
            strcat(sub,broom);
            strcat(sub," : ");
            strcat(sub,btype);
            strcat(sub,"\n");
            fputs(sub,cuFile);
        }
    }

    fclose(cuFile);
    if(check){
        printf("Can not check out ,can not find your log");
        return;
    }

    cuFile = fopen(strcat(type,".txt"), "r");
    char n[25];
    char s[25];
    Room *r, *ar;
    int first = 1;

    while (fscanf(cuFile, "%s : %s", n,s) != EOF) {
        char *n_in = (char*)malloc(sizeof(n));
        strcpy(n_in,n);
        Room *in = (Room *) malloc(sizeof(Room));
        in->room_num = n_in;
        int st;
        if(strcmp(s,"Avalible") == 0)
            st = 1;
        else
            st = 0;
        in->status = st;
        in->next = NULL;
        if (first) {
            r = in;
            ar = r;
            first = 0;
        } else {
            r->next = in;
            r = r->next;
        }
    }

    fseek(cuFile, 0, SEEK_SET);
    fclose(cuFile);

    fopen(type, "w");
    while (ar != NULL) {
        char buffer[255] = "";
        strcat(buffer, ar->room_num);
        strcat(buffer, " : ");

        if (strcmp(ar->room_num, droom) == 0) {
            strcat(buffer, "Avalible");
        }
        else {
            if (ar->status == 1)
                strcat(buffer, "Avalible");
            else
                strcat(buffer, "Full");
        }
        ar = ar->next;
        strcat(buffer, "\n");
        fputs(buffer, cuFile);
    }
    fclose(cuFile);
    printf("Check Out Success\n");
}


int check_duplicate(char* filename){
    FILE *file;
    file = fopen("Hotelname.txt","r");
    char buffer[strlen(filename)+1];
    while (fgets(buffer, sizeof(buffer),file)){
        if(strcmp(filename,buffer) == 0)
            return 0;
    }
    return 1;
}

void addHotel(){
    int firstdes =1;
    FILE *hotelfile,*room,*hotel;
    hotelfile = fopen("Hotelname.txt","a");

    char hotelname[255];
    printf("Enter Hotelname :");
    scanf("%s", hotelname);
    seek_to_next_line();
    if(check_duplicate(hotelname)) {
        strcat(hotelname, "\n");
        fputs(hotelname, hotelfile);
        strtok(hotelname, "\n");
    }
    fclose(hotelfile);

    char *hotel_room = (char*)malloc(sizeof(hotelname));
    hotel_room = hotelname;
    strcat(hotel_room,"_room.txt");
    room = fopen(hotel_room,"a");
    strtok(hotel_room,"_");

    char moreRoom;

    do{
        char roomtype[] = "Room Type : ";
        char buffer[255];
        char rt[255] = "";
        printf("Enter Room Type : ");
        scanf("%s",buffer);
        seek_to_next_line();

        strcat(buffer,".txt\n");
        strcat(rt,buffer);
        fputs(buffer,room);
        strtok(buffer,".");
        fclose(room);

        strcat(hotelname,".txt");
        hotel = fopen(hotelname,"a");
        strcat(roomtype,buffer);
        strcat(roomtype,"\n");
        fputs(roomtype,hotel);

        int check = 0;
        do {
            char des[50];
            if(firstdes)
                strcpy(des,"     Description :  ");
            else
                strcpy(des,"                 :  ");
            printf("Enter Description(1 line per 1 option) : ");
            scanf("%[^\n]", buffer);
            seek_to_next_line();

            strcat(buffer, "\n");
            strcat(des, buffer);
            fputs(des, hotel);

            char more;
            printf("Do you want to add more description? (y to add more):");
            scanf("%c",&more);
            seek_to_next_line();
            printf("You entered %c\n",more);

            if(more == 'y') {
                firstdes = 0;
                check = 1;
            }
            else {
                firstdes = 1;
                check = 0;
            }
        }while (check == 1);

        char people[] = "     People suggest: ";
        char detail[255];
        printf("Enter people suggest: ");
        scanf("%s",detail);
        seek_to_next_line();
        strcat(detail,"\n");
        strcat(people,detail);
        fputs(people,room);

        char price[] = "     Price: ";
        char p[10];
        printf("Enter the price :");
        scanf("%s",p);
        seek_to_next_line();

        strcat(p,"\n");
        strcat(price,p);
        fputs(price,room);

        int check_digit = 1;
        do {
            char sroom[10], eroom[10];
            printf("Enter strating room number: ");
            scanf("%s", sroom);
            seek_to_next_line();

            for(int i =0;i < strlen(sroom);i++){
                if(!isdigit(sroom[i])){
                    printf("Invalid Starting room\n");
                    continue;
                }
            }

            printf("Enter ending room number: ");
            scanf("%s", eroom);
            seek_to_next_line();

            for(int i =0;i < strlen(eroom);i++){
                if(!isdigit(sroom[i])){
                    printf("Invalid Ending room\n");
                    continue;
                }
            }

            if (check_digit) {
                FILE *roomCheck;
                roomCheck = fopen(strtok(rt,"\n"), "w");
                int s = atoi(sroom),e = atoi(eroom);
                if(s < e){
                    while (s <= e){
                        char b[10];
                        itoa(s,b,10);
                        strcat(b," : Avalible\n");
                        fputs(b,roomCheck);
                        s++;
                    }
                }
                else{
                    check_digit = 0;
                    printf("starting room is less than ending room\n");
                }
            }
            else{
                printf("Invalid room\n");
            }
        }while (check_digit == 0);



        printf("Do you want to add more room type(y to add): ");
        scanf("%c",&moreRoom);
        seek_to_next_line();
        printf("You entered %c\n",moreRoom);
    }while (moreRoom == 'y');

    fclose(hotelfile);
    fclose(room);
    fclose(hotel);
}

void menuAdmin(){
    int command , check = 0;
    do {
        printf("1.Adding Hotel\n");
        printf("2.Check out\n");
        printf("3.Back\n");
        printf("Enter the number of command :");
        scanf("%d", &command);
        if(command == 1)
            addHotel();
        else if(command == 2) {
            char room[10],name[25];
            printf("Enter room to check out: ");
            scanf("%s",room);
            seek_to_next_line();

            printf("Enter customer name:");
            scanf("%s",name);
            seek_to_next_line();

            checkout(room,name);
        }
        else if(command == 3)
            check = 1;
        else
            printf("Invalid command!!!");
    }while(check == 0);

}

void login(){
    char user[10],pass[10];
    int check = 0;
    do {
        printf("Enter Username (b to back): ");
        scanf("%s", user);
        if (strcmp(user, "b") == 0)
            return;
        printf("Enter Password: ");
        scanf("%s", pass);
        int check_user = strcmp(user, "Admin"),
                check_pass = strcmp(pass, "rootAdmin");
        if (check_user && check_pass) {
            printf("Username or Password is invalid\n");

        } else {
            menuAdmin();
            check = 1;
        }
    }while(check == 0);
}

#endif //BOOKINGHOTEL_ADMIN_H
