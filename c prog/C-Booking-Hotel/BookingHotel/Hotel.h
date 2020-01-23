#ifndef BOOKINGHOTEL_HOTEL_H
#define BOOKINGHOTEL_HOTEL_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "User.h"

void roomDetail(char* hotelname);
void hotel();

typedef struct hotel {
    char* name;
    struct hotel * next;
}Hotel;

typedef  struct roomtype{
    char *name;
    int status;
    struct roomtype *next;
}Roomtype;

typedef  struct room{
    char *room_num;
    int status;
    struct room *next;
}Room;


void makeHotelList(Hotel **lst, char *hotelname){
    Hotel* newHotel = (Hotel*)malloc(sizeof(Hotel)); ;
    newHotel->name = hotelname;
    newHotel->next = NULL;
    if(*lst == NULL) {
        *lst = newHotel;
    }
    else{
        Hotel* buffer = *lst;
        Hotel* head = buffer;
        while(buffer->next != NULL) {
            buffer = buffer->next;
        }
        buffer->next = newHotel;
        *lst = head;
    }
}

void makeRoomTypeList(Roomtype **lst, char *roomname, int s){
    Roomtype* newRoom = (Roomtype*)malloc(sizeof(Roomtype)); ;
    newRoom->name = roomname;
    newRoom->next = NULL;
    newRoom->status = s;

    if(*lst == NULL) {
        *lst = newRoom;
    }
    else{
        Roomtype* buffer = *lst;
        Roomtype* head = buffer;
        while(buffer->next != NULL) {
            buffer = buffer->next;
        }
        buffer->next = newRoom;
        *lst = head;
    }
}

void makeRoomList(Room **lst, char *room_num, int s){
    Room* newRoom = (Room*)malloc(sizeof(Room)); ;
    newRoom->room_num = room_num;
    newRoom->next = NULL;
    newRoom->status = s;

    if(*lst == NULL) {
        *lst = newRoom;
    }
    else{
        Room* buffer = *lst;
        Room* head = buffer;
        while(buffer->next != NULL) {
            buffer = buffer->next;
        }
        buffer->next = newRoom;
        *lst = head;
    }
}

void write_file(Room* room,char* filename){
    Room* sub = room;
    FILE *f;
    f = fopen(strcat(filename,".txt"),"w");

    while (sub != NULL) {
        char* new_room = (char*)malloc(sizeof(sub->room_num));
        new_room = sub->room_num;
        strcat(new_room," : ");
        if(sub->status == 1){
            strcat(new_room,"Avalible\n");
            fputs(new_room,f);
        }
        else if(sub->status == 0){
            strcat(new_room,"Full\n");
            fputs(new_room,f);
        }
        sub = sub->next;
    }
    fclose(f);
}

void booking(char* all_room, char* hotelname){
    FILE * all;
    all  = fopen(all_room,"r+");
    Room *room = NULL;
    char room_number[10],room_status[10];

    while (fscanf(all,"%s : %s",room_number,room_status)!= EOF){
        printf("%s : %s\n",room_number,room_status);
        int status;
        if(strcmp(room_status,"Avalible") == 0)
            status = 1;
        else
            status = 0;

        char *sub_room = (char*)malloc(sizeof(room_number));
        strcpy(sub_room,room_number);
        makeRoomList(&room,sub_room,status);
    }

    char n[10];
    int check = 0, invalid = 0;


    do {
        printf("Enter the room number that avalible( b to back):");
        scanf("%s", n);
        Room *sub = room;
        if(strcmp(n,"b")== 0){
            char* hotel = hotelname;
            strtok(hotel,"_");
            strcat(hotel,".txt");
            roomDetail(hotel);
            return;
        }
        while (sub != NULL) {
            if (strcmp(sub->room_num, n) == 0 && sub->status == 1) {
                char cf;
                printf("Are you sure to booking this room?(y to confirm)");
                getchar();
                scanf("%c",&cf);
                if(cf == 'y'){
                    information(n,all_room);
                    sub->status = 0;
                }
                check = 1;
                break;
            }
            else if (strcmp(sub->room_num, n) == 0 && sub->status == 0){
                printf("This room is already booking\n");
                invalid = 0;
                break;
            }
            else
                invalid = 1;

            sub = sub->next;
        }
        if(invalid == 1)
            printf("Your select is invalid or not avalible\n");

        invalid = 0;

    }while (check == 0);

    if(check == 1){
        write_file(room,all_room);
        printf("Success!!!\n");
    }
}

void checkStatus(char* room_name,int choice,Roomtype **r){
    FILE *room,*type;
    int status;
    char room_number[10],room_status[10];

    room = fopen(room_name,"r");
    char type_name[255];
    for(int i =0;i< choice;i++){
        fgets(type_name, sizeof(type_name),room);
    }
    strtok(type_name,"\n");

    type = fopen(type_name,"r");
    while (fscanf(type,"%s : %s",room_number,room_status)!= EOF){
        if(strcmp(room_status,"Full")!= 0){
            printf("\nStatus : Avalible\n");
            status = 1;
            char* sub = malloc(sizeof(type_name));
            strcpy(sub,type_name);
            sub = strtok(sub,"\n");
            makeRoomTypeList(r, sub, status);
            fclose(room);
            fclose(type);
            return;
        }
    }
    printf("\nStatus : Full\n");
    status = 0;
    makeRoomTypeList(r, type_name, status);
    fclose(room);
    fclose(type);
}


void roomDetail(char* hotelname){
    FILE *roomlst;
    roomlst = fopen(hotelname,"r");
    if(roomlst == 0){
        return;
    }
    Roomtype *roomLink = NULL;

    char buffer[255];
    char* n = strtok(hotelname,".");
    n = strcat(n,"_room.txt");

    int order = 1;
    int number = 0;

    printf("-------Room Detail---------\n");
    while (fgets(buffer, sizeof(buffer),roomlst)){
        if(strcmp(buffer,"\n") == 0){
            checkStatus(n,order,&roomLink);
            order++;
        }
        printf("%s",buffer);
        number++;
    }
    checkStatus(n,order,&roomLink);

    fclose(roomlst);

    char* room_name;
    char c[2];
    int room_status,command,check = 1;

    do {
        Roomtype *select_room = roomLink;
        printf("\nEnter the selected room type (or b to back): ");
        scanf("%s", c);
        if(strcmp(c,"b")== 0){
            hotel();
            return;
        }
        command = atoi(c);
        if(command < 0 || command > number || strlen(c)> 1){
            printf("Enter invalid room type\n");
            continue;
        }

        for (int i = 0; i < command; i++) {
            room_name = select_room->name;
            room_status = select_room->status;
            select_room = select_room->next;
        }
        if (!room_status)
            printf("Enter invalid type or type with Full status!!!\n");
        else
            check = 0;

    }while(check);

    booking(room_name,hotelname);

}

void hotel() {
    FILE *hotelst;
    char buffer[255];
    Hotel *hotel = NULL;
    int len_hotel = 0;

    printf("\n---------Hotel name---------\n");
    hotelst = fopen("Hotelname.txt","r");
    while (fgets(buffer, sizeof(buffer),hotelst)){
        printf("%d.%s",len_hotel+1,buffer);
        char* sub = malloc(sizeof(buffer));
        strcpy(sub,buffer);
        sub = strtok(sub,"\n");
        makeHotelList(&hotel, sub);
        len_hotel++;
    }

    fclose(hotelst);

    int command;
    char c[1];
    Hotel* selecthotel = hotel;
    char* hotelname;
    int check = 1;

    do{
    printf("\nSelect Hotel(or b to back): ");
    scanf("%s",c);
    if(strcmp(c,"b")== 0) {
        return;
    }
    command = atoi(c);
    if(command != 0 && command > len_hotel) printf("Invalid Select Hotel!!!");
    else check = 0;
    }while (check);

    for(int i = 0;i<command ;i++){
        hotelname = selecthotel->name;
        selecthotel = selecthotel->next;
    }

    hotelname = strcat(hotelname,".txt");
    roomDetail(hotelname);

}
#endif //BOOKINGHOTEL_HOTEL_H
