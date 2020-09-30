#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>
typedef struct
{
    int DD;
    int MM;
    int YYYY;
}date;
typedef struct
{
    int car_ID;
    char car_name[50];
    int car_rate;
    int car_n;
}car_t;
typedef struct
{
    int renter_id;
    char renter_name[100];
    date rent_date;
    int rent_days;
    int carID;
    float tot_rent;
}renter_t;
void car_data(car_t c[], int x);
void rent_data(renter_t rent[], int x);
void new_rent();
void settings();
int main()
{
    car_t cars[50];
    renter_t renters[50];
    char pass1[100], pass2[100], d='n';
    FILE *fp;int x,i,j;
    for(i=0;i<50;i++)
    {
        cars[i].car_ID=0;
        strcpy(cars[i].car_name,"");
        cars[i].car_rate=0;
        cars[i].car_n=0;
    }
    for(i=0;i<50;i++)
    {
        renters[i].renter_id=0;
        strcpy(renters[i].renter_name,"");
        renters[i].rent_days=0;
        renters[i].tot_rent=0.0;
    }
    fp=fopen("pass.txt", "r");
    if(fp==NULL)
    {
        printf("\nError Opening pass.txt file!\n");
        return 0;
    }
    else fgets(pass1,100,fp);
    fclose(fp);
    printf("\n\n\n\n\n\t\t\t\t\tWELCOME!");
    printf("\n\n\t\t\t\tEnter Password to proceed:\n");
    printf("\n\t\t\t\t\t");
    fflush(stdin);
    gets(pass2);
    while((strcmp(pass1, pass2))!=0)
    {
        system("cls");
        printf("\n\n\n\n\n\t\t\t\t   Wrong Password!");
        printf("\n\n\t\t\t\tEnter Password Again:\n");
        printf("\n\t\t\t\t\t");
        fflush(stdin);
        gets(pass2);
    }
    system("cls");
    while (d=='N'||d=='n')
    {
        printf("\n\tSYETEM MENU\n");
        printf("--------------------------------");
        printf("\n 1 = Car Data\n");
        printf("\n 2 = Renter Data\n");
        printf("\n 3 = New Rental\n");
        printf("\n 4 = Settings\n");
        printf("\n 5 = Exit System\n");
        printf("--------------------------------");
        printf("\nEnter your selection:  ");
        scanf("%d", &x);

        if(x==1)
            car_data(cars,50);
        else if(x==2)
            rent_data(renters,50);
        else if(x==3)
            new_rent();
        else if(x==4)
            settings();
        else if (x==5)
            return 0;
        else printf("\nInvalid Input!\n");
        printf("\n\nExit System? (y/n)  ");
        fflush(stdin);
        scanf("%c", &d);
        system("cls");
    }
}
void car_data(car_t c[], int x)
{
    system("cls");
    printf("\n\n\n");
    FILE *fp; int i;
    fp=fopen("cars data.txt", "r");
    if(fp==NULL)
    {
        printf("\nError opening cars data.txt file\n");
        fclose(fp);
    }
    else
    {

    for(i=0;i<x;i++)
    {
        fseek(fp,i*sizeof(car_t),SEEK_SET);
        fread(&c[i],sizeof(car_t),1,fp);
    }
    printf("\nID\tCar Name\t\tRent per day(Rs.)\tAvailable\n");
    for(i=0;i<x;i++)
    {
        if(c[i].car_ID!=0)
            printf("\n%-8d%-20s\t%-10d\t\t%-10d",c[i].car_ID,c[i].car_name,c[i].car_rate,c[i].car_n);
    }
    }
    fclose(fp);
}
void rent_data(renter_t rent[], int x)
{
    system("cls");
    printf("\n\n");
    FILE *fp; int i;
    fp=fopen("renter data.txt","rb");
    if(fp==NULL)
    {
        printf("\nError oprning renter data.txt file\n");
        fclose(fp);
    }
    else
    {

    for(i=0;i<x;i++)
    {
        fseek(fp,i*sizeof(renter_t),SEEK_SET);
        fread(&rent[i],sizeof(renter_t),1,fp);
    }
    printf("\nID\tRenter Name\t\tRent Date\t\tRent Days\tCar ID\tTotal Rent\n");
    for(i=0;i<x;i++)
    {
        if(rent[i].renter_id!=0)
            printf("\n%d\t%-15s\t\t%d/%d/%d\t\t%d\t\t%d\t%.2f",rent[i].renter_id,rent[i].renter_name,rent[i].rent_date,rent[i].rent_days,rent[i].carID,rent[i].tot_rent);
    }
    }
    fclose(fp);
}
void new_rent()
{
    system("cls");
    printf("\n\n\n");
    renter_t renter;
    car_t car;
    char d;
    FILE *fp,*ft;
    fp=fopen("renter data.txt","r+");
    if(fp==NULL)
    {
        printf("\nError Opening renter data.txt File\n");
        fclose(fp);
    }
    else
    {
        do
        {
        do
        {
            printf("\nEnter renter ID(1-50):  ");
            scanf("%d",&renter.renter_id);
        }while(renter.renter_id<=0||renter.renter_id>50);
       /* fseek(fp,(renter.renter_id-1)*sizeof(renter),SEEK_SET);
        fread(&renter, sizeof(renter),1,fp);
        if(renter.renter_id!=0)
        {
            printf("\nRenter ID already exists!\n");
        }
        else*/
        {
            printf("\nEnter renter name:  ");
            fflush(stdin);
            gets(renter.renter_name);
            do{
            printf("\nEnter renting date(DD/MM/YYYY):  ");
            fflush(stdin);
            scanf("%d%d%d",&renter.rent_date.DD,&renter.rent_date.MM,&renter.rent_date.YYYY);
            }while(renter.rent_date.DD>31||renter.rent_date.DD<1||renter.rent_date.MM>12||renter.rent_date.MM<1||renter.rent_date.YYYY<2018||renter.rent_date.YYYY>2019);
            do{
            printf("\nEnter renting days(1-15):  ");
            scanf("%d",&renter.rent_days);}while(renter.rent_days<=0||renter.rent_days>15);
            ft=fopen("cars data.txt","r+");
            if(ft==NULL)
            {
                printf("\nError Opening cars data.txt File\n");
                fclose(ft);
            }
            else
            {
                printf("\nEnter car ID to rent:  ");
                scanf("%d",&renter.carID);
                fseek(ft,(renter.carID-1)*sizeof(car),SEEK_SET);
                fread(&car, sizeof(car),1,ft);
            }
            if(renter.carID==car.car_ID)
            {
                if(car.car_n<1)
                {
                    printf("\n\n The car (ID = %d) is unavailable right now. Sorry for inconvenience.\n", renter.carID);
                    return 0;
                }
                car.car_n=car.car_n-1;
                fseek(ft,(car.car_ID-1)*sizeof(car),SEEK_SET);
                fwrite(&car,sizeof(car),1,ft);
                fclose(ft);
            }
            else
            {
                printf("\n\nInvalid Car ID\n");
                return 0;
            }
            if(renter.carID==car.car_ID)
            {
                renter.tot_rent=(renter.rent_days)*(car.car_rate);
            }
            fseek(fp,(renter.renter_id-1)*sizeof(renter),SEEK_SET);
            fwrite(&renter,sizeof(renter_t),1,fp);
            printf("\nAdd another renter?(y/n)  ");
            fflush(stdin);
            scanf("%c", &d);
        }
        }while(d=='y'||d=='Y');
    }
    fclose(fp);
}
void settings()
{
    system("cls");
    car_t car;
    renter_t renter, blank_rent={0,"",0,0,0,0,0,0.0};
    FILE *fp,*ft; int x,y;
    char pass1[100], pass2[100], d;
    printf("\nSettings Menu\n");
    printf("--------------------------------");
    printf("\n1 = Edit/Update Car Data\n");
    printf("\n2 = Edit/Update Renter Data\n");
    printf("\n3 = Change Password\n");
    printf("--------------------------------");
    printf("\nEnter your selection:  ");
    scanf("%d", &x);
    system("cls");
    if (x==1)
    {
        system("cls");
        printf("\n\n");
        printf("--------------------------------");
        printf("\n1 = Add new car\n");
        printf("\n2 = Edit existing car data\n");
        printf("--------------------------------");
        printf("\nEnter your choice:  ");
        scanf("%d", &y);
        if (y==1)
        {
            system("cls");
            printf("\n\n");
            fp=fopen("cars data.txt", "r+");
            if (fp==NULL)
            {
                printf("\Error Opening cars data.txt File\n");
                fclose(fp);
            }
            else
            {
                do
                {
                    do
                    {
                    printf("\nEnter car ID(1-50):  ");
                    fflush(stdin);
                    scanf("%d",&car.car_ID);
                    }while(car.car_ID<=0||car.car_ID>50);
                   /* fseek(fp,(car.car_ID-1)*sizeof(car),SEEK_SET);
                    fread(&car,sizeof(car),1,fp);
                    if(car.car_ID!=0)
                    {
                        printf("\nCar ID already exists!\n");
                    }
                    else*/
                    {   printf("\nEnter car name:  ");
                        fflush(stdin);
                        gets(car.car_name);
                        printf("\nEnter car rate:  ");
                        fflush(stdin);
                        scanf("%d",&car.car_rate);
                        printf("\nEnter car availability no.:  ");
                        fflush(stdin);
                        scanf("%d",&car.car_n);
                        fseek(fp,(car.car_ID-1)*sizeof(car),SEEK_SET);
                        fwrite(&car,sizeof(car_t),1,fp);
                        printf("\n\nAction Successful!\n");
                        printf("\nAdd another car?(y/n)  ");
                        fflush(stdin);
                        scanf("%c", &d);
                    }
                }while (d=='y'||d=='Y');
                fclose(fp);
            }
        }
        else if(y==2)
        {
            system("cls");
            printf("\n\n");
            int id;
            printf("\nEnter car ID to edit :  ");
            fflush(stdin);
            scanf("%d",&id);
            fp=fopen("cars data.txt","r+");
            if(fp==NULL)
            {
                printf("\nCannot open cars data.txt file\n");
                fclose(fp);
            }
            else
            {
                fseek(fp,(id-1)*sizeof(car),SEEK_SET);
                fread(&car,sizeof(car),1,fp);
                if(car.car_ID==id)
                {
                    printf("\nEnter new car name:  ");
                    fflush(stdin);
                    gets(car.car_name);
                    printf("\nEnter new car rate:  ");
                    fflush(stdin);
                    scanf("%d", &car.car_rate);
                    printf("\nEnter new car availability no.:  ");
                    fflush(stdin);
                    scanf("%d", &car.car_n);
                    fseek(fp,(id-1)*sizeof(car),SEEK_SET);
                    fwrite(&car,sizeof(car),1,fp);
                    fclose(fp);
                    printf("\n\nAction Successful!\n");
                }
                else{printf("\nCar ID does not exist\n");}
            }
        }
        else
        {
            printf("\n\nInvalid Input!\n");
        }

    }
    else if(x==2)
    {
        system("cls");
        printf("\n\n");
        printf("--------------------------------");
        printf("\n1 = Edit existing renter data\n");
        printf("\n2 = Delete renter data\n");
        printf("--------------------------------");
        printf("\nEnter your choice:  ");
        scanf("%d", &y);
        if(y==1)
        {
            system("cls");
            printf("\n\n");
            int id;
            printf("\nEnter renter ID to edit:  ");
            fflush(stdin);
            scanf("%d", &id);
            fp=fopen("renter data.txt","r+");
            if(fp==NULL)
            {
                printf("\nCannot open renter data.txt file\n");
                fclose(fp);
            }
            else
            {
                fseek(fp,(id-1)*sizeof(renter),SEEK_SET);
                fread(&renter,sizeof(renter),1,fp);
                if(renter.renter_id==id)
                {
                    printf("\nEnter new name:   ");
                    fflush(stdin);
                    gets(renter.renter_name);
                    printf("\nEnter new rent date:   ");
                    fflush(stdin);
                    scanf("%d%d%d",&renter.rent_date.DD,&renter.rent_date.MM,&renter.rent_date.YYYY);
                    printf("\nEnter new rent days:   ");
                    fflush(stdin);
                    scanf("%d", &renter.rent_days);
                    printf("\nEnter new car ID:   ");
                    fflush(stdin);
                    scanf("%d",&renter.carID);
                    ft=fopen("cars data.txt","r+");
                    if(ft==NULL)
                    {
                        printf("\nCannot open cars data.txt file\n");
                        fclose(ft);
                    }
                    else
                    {
                        fseek(ft,(renter.carID-1)*sizeof(car),SEEK_SET);
                        fread(&car,sizeof(car),1,ft);
                        if(renter.carID==car.car_ID)
                        {
                            renter.tot_rent=(renter.rent_days)*(car.car_rate);
                            car.car_n=car.car_n-1;
                            fseek(ft,(renter.carID-1)*sizeof(car),SEEK_SET);
                            fwrite(&car,sizeof(car),1,ft);
                            fclose(ft);
                        }
                        else
                        {
                            printf("\nInvalid car ID\n");fclose(ft);
                        }
                    }
                }
                else
                {
                    printf("\nInvalid renter ID\n");
                }
                fseek(fp,(id-1)*sizeof(renter),SEEK_SET);
                fwrite(&renter,sizeof(renter),1,fp);
                fclose(fp);
                printf("\n\nAction Successful!\n");
            }
        }
        else if(y==2)
        {
            system("cls");
            printf("\n\n");
            int id;
            printf("\nEnter renter ID to delete:  ");
            fflush(stdin);
            scanf("%d",&id);
            fp=fopen("renter data.txt","r+");
            if(fp==NULL)
            {
                printf("\nCannot open renter data.txt file\n");
                fclose(fp);
            }
            else
            {
                fseek(fp,(id-1)*sizeof(renter),SEEK_SET);
                fread(&renter,sizeof(renter),1,fp);
                ft=fopen("cars data.txt","r+");
                if(ft==NULL)
                {
                    printf("\nCannot open cars data.txt file\n");
                    fclose(ft);
                }
                else
                {
                    fseek(ft,(renter.carID-1)*sizeof(car),SEEK_SET);
                    fread(&car,sizeof(car),1,ft);
                    car.car_n=car.car_n+1;
                    fseek(ft,(renter.carID-1)*sizeof(car),SEEK_SET);
                    fwrite(&car,sizeof(car),1,ft);
                    fclose(ft);
                    renter=blank_rent;
                    fseek(fp,(id-1)*sizeof(renter),SEEK_SET);
                    fwrite(&renter,sizeof(renter),1,fp);
                    fclose(fp);
                    printf("\n\nAction Successful!\n");
                }
            }
        }
        else printf("\nInvalid Input\n");
    }
    else if(x==3)
    {
        system("cls");
        printf("\n\n");
        fp=fopen("pass.txt", "r");
        if(fp==NULL)
           {
                printf("\nError Opening pass.txt File!\n");
                fclose(fp);
           }
        else
        {
            fscanf(fp,"%s", pass1);
            fclose(fp);
            printf("\nEnter Current Password:  ");
            fflush(stdin);
            gets(pass2);
            if((strcmp(pass1,pass2))==0)
            {
                printf("\nEnter new password:  ");
                fflush(stdin);
                gets(pass1);
                fp=fopen("pass.txt","w");
                if(fp==NULL)
                    printf("\nError Opening pass.txt File!\n");
                else
                {
                    fprintf(fp,"%s",pass1);
                    fclose(fp);
                    printf("\nPassword change successful!\n");
                }
            }
            else printf("\nIncorrect Password!\n");
        }
    }
    else printf("\nInvalid Input!\n");
}
