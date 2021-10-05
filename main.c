#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>
#include <ctype.h>
void clrscr()
{
    printf("Press any key to proceed ");
    char z;
    scanf(" %c",&z);
    system("@cls||clear");
}
void stationList()
{
    char *a[31];
    a[1]="Gombak";
    a[2]="Taman Melati";
    a[3]="Wangsa Maju";
    a[4]="Sri Rampi";
    a[5]="Setiawangsa";
    a[6]="Jelatek";
    a[7]="Dato'Keramat";
    a[8]="Damai";
    a[9]="Ampang Pard";
    a[10]="KLCC";
    a[11]="Kampung Baru";
    a[12]="Dang Wangi";
    a[13]="Masjid Jamed";
    a[14]="Pasar Seni";
    a[15]="KL Sentral";
    a[16]="Bank Rakyat";
    a[17]="Abdullah Hukum";
    a[18]="Kerinchi";
    a[19]="KL GATEWAY";
    a[20]="Taman Jaya";
    a[21]="Asia Jaya";
    a[22]="Taman Paramount";
    a[23]="Taman Bahagia";
    a[24]="Kelana Jaya";
    a[25]="Lembah Subang";
    a[26]="Ara Damansara";
    a[27]="Glenmarie";
    a[28]="Subang Jaya";
    a[29]="SS 15";
    a[30]="SS 18";
    printf("\n\t\tKiwiExpress\t\t\n");
    printf("____________________________________________\n");
    printf("--------------------------------------------\n");
    printf("Kindly select the departure station");
    printf(" and the arrival station number.\n");
    printf("Following is the station list:\n\n");
    int i;
    for(i=1;i<31;i++)
    {
        if(i%2==0)
        {
            printf("%.2d. %-15s\n",i,a[i]);
        }
        else
        {
            printf("%.2d. %-15s\t",i,a[i]);
        }
    }
    printf("____________________________________________\n");
    printf("--------------------------------------------\n");
}
struct ticketInfo
{
    char code[6];
    int departure;
    int arrival;
    int hour,min;
    int noOfAdults;
    int noOfChildren;
}ti;
int KiwiExpressCounter()
{
    int menuNo;
    printf("\n\t\tKiwiExpress\t\t\n");
    printf("____________________________________________\n");
    printf("--------------------------------------------\n");
    printf("Press 1 for Registration\n");
    printf("Press 2 for Reward Module\n");
    printf("Press 3 for Ticketing Module\n");
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    printf("\n\nDate : %d-%d-%d %d:%d:%d\n", tm.tm_mday, tm.tm_mon + 1, tm.tm_year + 1900, tm.tm_hour, tm.tm_min, tm.tm_sec);
    printf("____________________________________________\n");
    printf("--------------------------------------------\n");

    scanf("%d",&menuNo);
    system("@cls||clear");
    return menuNo;
}
int main(){
    int menuNo;
    stateMenu:
    menuNo=KiwiExpressCounter();
    if(menuNo==1)
    {
        FILE *pFile,*duplicateFile;
        char name[20];
        char idCardNo[10];
        char key[7]="100000";
        char rm[10]="0";
        int idFlag=0;       //check if id exist. 0=not exist 1=exist
        char code[6];

        pFile=fopen("Registration Info.txt", "a+");
        duplicateFile=fopen("Points Info.txt", "a+");
        if(pFile!=NULL && duplicateFile!=NULL)
        {
            stateRegistration:
            system("@cls||clear");
            printf("\n\t\tKiwiExpress\t\t\n");
            printf("____________________________________________\n");
            printf("--------------------------------------------\n");
            printf("Enter Name: ");
            scanf(" %[^\n]%*c", &name);
            printf("Id card no: ");
            scanf("%s",&idCardNo);
            if(strlen(idCardNo)>10)
            {
                printf("Identity Number not longer than 10 digit\n");
                clrscr();
                goto stateMenu;
            }
            /******Checking if id already exist?******/
            /***And Retriving key****/
            char temp[70];
            while(fgets(temp, 70, pFile) != NULL)
            {
                char *token1,*token2,*token3,*token4;
                token1 = strtok(temp, ":");
                token2 = strtok(NULL, ":RM");
                token3 = strtok(NULL, ":");
                token4 = strtok(NULL, ":");
                if((strstr(token4, idCardNo)) != NULL)
                {     // Id exist already
                        printf("Identity Number already exist !!!\n");
                        //goto stateRegistration;
                        clrscr();
                        goto stateMenu;
                }
                int a=atoi(token1);
                int b=atoi(key);
                if(a>=b)b=a+1;
                char str[15];
                sprintf(key, "%d", b);
            }

            /****Writing to File*****/
            fprintf(pFile, "%6s :RM%10s : %20s : %10s\n", key,rm,name,idCardNo);
            fprintf(duplicateFile, "%6s  :RM%10s :  %20s  :  %10s\n", key,rm,name,idCardNo);

            printf("\n\t\tKiwiExpress\t\t\n");
            printf("\n\t Registration Page\t\t\n");
            printf("____________________________________________\n");
            printf("--------------------------------------------\n");
            printf("Name                : %s\n",name);
            printf("Identity Number     : %s\n",idCardNo);
            printf("6 digit code        : %s\n",key);

            printf("\nRegistration successfull !!!\n\n");
            printf("____________________________________________\n");
            printf("--------------------------------------------\n");
            fclose(pFile);
            fclose(duplicateFile);
        }
        /*******If file doesn't open********/
        else
        {
            printf("No file found\n\n");
        }
        clrscr();
        goto stateMenu;
    }
    else if(menuNo==2)
    {
        printf("\n\t\tKiwiExpress\t\t\n");
        printf("____________________________________________\n");
        printf("--------------------------------------------\n");
        printf(" For every RM 1.00 spent, a customer \n");
        printf(" shall accumulate one point\n");
        printf(" which will credited to the\n");
        printf(" account of the customer's 6digit code\n");
        printf("____________________________________________\n");
        printf("--------------------------------------------\n\n");

        clrscr();
        goto stateMenu;
    }
    else if(menuNo==3)
    {
        /***************taking input***********/
        stateTicketPurchase:
        stationList();
        printf("Departure Station: ");
        scanf("%d",&ti.departure);
        printf("Arrival Station: ");
        scanf("%d",&ti.arrival);
        if(ti.departure<0 || ti.departure>ti.arrival)
        {
            printf("Departure station must be greater than zero and less than arrival station\n");
            clrscr();
            goto stateTicketPurchase;
        }
        else if(ti.arrival<ti.departure || ti.arrival>31)
        {
            printf("Arrival station must be greater than departure station and less than 31\n");
            clrscr();
            goto stateTicketPurchase;
        }
        printf("Travel time(hh mm): ");
        scanf("%d%d",&ti.hour,&ti.min);
        if(ti.hour>24 || ti.hour<0 || ti.min>59 || ti.min<0)
        {
            printf("Hour between 0 to 24 and Minute between 0 to 59\n");
            clrscr();
            goto stateTicketPurchase;
        }
        printf("Number of Adults: ");
        scanf("%d",&ti.noOfAdults);
        printf("Number of Childrens: ");
        scanf("%d",&ti.noOfChildren);

        stateGetCode:
        printf("Do you have 6digit code? Press Y or N  ");
        char haveCode;
        int codeFlag=0;     //checking code exist or not. 0=not exist. 1=exist
        scanf(" %c",&haveCode);
        if(haveCode=='y'||haveCode=='Y')
        {
            printf("Enter 6 digit code: ");
            scanf(" %s",&ti.code);
            FILE *pFile;
            char temp[70];
            pFile=fopen("Registration Info.txt", "r");
            if(pFile!=NULL)
            {
                while(fgets(temp, 70, pFile) != NULL)
                {
                    char *token1,*token2,*token3,*token4;
                    token1 = strtok(temp, ":");
                    token2 = strtok(NULL, ":RM");
                    token3 = strtok(NULL, ":");
                    token4 = strtok(NULL, ":");
                    if((strstr(token1, ti.code)) != NULL)
                    {
                        codeFlag=1;
                        break;
                    }
                }
                if(codeFlag==0)
                {
                    printf("Invalid code\n");
                    goto stateGetCode;
                }
                else printf("Valid code\n");
            }
            fclose(pFile);
        }
        else if(haveCode=='n'||haveCode=='N')
        {
            printf("Being Registered passeneger, purchasing ticket you get points.\n");
        }
        else
        {
            printf("Wrong pressed !!! Please press Y or N.\n");
            goto stateGetCode;
        }

        /*********Calculating discounts***********/
        int stationDiff=ti.arrival-ti.departure;    //as imediate station needs 1RM
        float ticketCost=stationDiff;               //as imediate station needs 1RM
        float adultCost=stationDiff*ti.noOfAdults;    //adult cost calculation
        float discount=0;
        if(ti.hour>=19 && ti.hour<=23)
        {               //7pm-11pm 25% discount
            discount=.25;
            adultCost=adultCost-(adultCost*discount);
        }
        else if(ti.hour>=6&&ti.hour<=7)
        {              //6am-7am 50% discount
            if(ti.min<=15 && ti.min>=0)
            {
                discount=.50;
                adultCost=adultCost-(adultCost*discount);
            }
        }
        float childCost=(stationDiff*(.50))*ti.noOfChildren;  //always child have 50% discount
        ticketCost=adultCost+childCost;                         //total cost
        if(ti.noOfAdults+ti.noOfChildren>5)
        {                        //people 5+ have 10% discount
            discount=.10;
            ticketCost=ticketCost-(ticketCost*discount);
        }

                /********Code search and update********/
        int point=0;
        if(codeFlag==1)
        {                    //checking 500 points
            FILE *pFile,*pFile2,*pf;
            char temp[70],temp2[70];
            pFile=fopen("Registration Info.txt", "r");
            pFile2=fopen("Points Info.txt", "a+");
            pf=fopen("Points.txt", "w");
            if(pFile!=NULL && pFile2!=NULL)
            {
                while(fgets(temp, 70, pFile) != NULL && fgets(temp2, 70, pFile2) != NULL)
                {
                    char *temptoken1,*temptoken2,*temptoken3,*temptoken4;
                    temptoken1 = strtok(temp, ":");
                    temptoken2 = strtok(NULL, ":RM");
                    temptoken3 = strtok(NULL, ":");
                    temptoken4 = strtok(NULL, ":");
                    char *temp2token1,*temp2token2,*temp2token3,*temp2token4;
                    temp2token1 = strtok(temp2, ":");
                    temp2token2 = strtok(NULL, ":RM");
                    temp2token3 = strtok(NULL, ":");
                    temp2token4 = strtok(NULL, ":");
                    if((strstr(temptoken1, ti.code)) != NULL)
                    {
                        int a=atoi(temp2token2);
                        if(a>=500)
                        {             //checking if points>500
                            a=a-500;
                            discount=5;
                            ticketCost=ticketCost-5;            //discount RM 5.00
                            a=a+ticketCost;
                        }
                        else
                        {
                            a=a+ticketCost;
                        }
                        sprintf(temptoken2, "%d", a);
                        fprintf(pf, "%6s :RM%10s : %20s : %10s", temptoken1,temptoken2,temptoken3,temptoken4);
                        point=atoi(temptoken2);
                    }
                    else
                    {
                        /***Writing in 2nd file without edit***/
                        int a=atoi(temp2token2);
                        char str[15];
                        sprintf(temptoken2, "%d", a);
                        fprintf(pf, "%6s :RM%10s : %20s : %10s", temptoken1,temptoken2,temptoken3,temptoken4);
                    }
                }
            }
            fclose(pFile);
            fclose(pFile2);
            fclose(pf);
            remove("Points Info.txt");
            rename("Points.txt","Points Info.txt");
        }

        /********Generating Ticket********/
        system("@cls||clear");
        printf("\n\t\tKiwiExpress\t\t\n");
        printf("\n\t\t   Ticket  \t\t\n");
        printf("____________________________________________\n");
        printf("--------------------------------------------\n");
        printf("No of Passenger   : %d\n",(ti.noOfAdults+ti.noOfChildren));
        printf("Travel time       : %d:%d\n",ti.hour,ti.min);
        printf("Departure Station : %d\n",ti.departure);
        printf("Arrival Station   : %d\n",ti.arrival);
        printf("Ticket Price      : %f\n",ticketCost);
        if(point>0)
        {
            printf("Your point        : %d\n",point);
        }
        else
        {
            printf("Your point        : %d (You are not registered.)\n",point);
        }

        time_t t = time(NULL);
        struct tm tm = *localtime(&t);
        printf("\n\nDate              : %d-%d-%d %d:%d:%d\n", tm.tm_mday, tm.tm_mon + 1, tm.tm_year + 1900, tm.tm_hour, tm.tm_min, tm.tm_sec);
        printf("____________________________________________\n");
        printf("--------------------------------------------\n");

        stateGetPayment:
        printf("\nPlease pay the Ticket cost ");
        float payment;
        scanf("%f",&payment);
        if(payment>ticketCost)
        {
            printf("Amount Exceed the ticket cost !!!\n");
            goto stateGetPayment;
        }
        else if(payment<ticketCost)
        {
            printf("Please pay the full ticket cost !!!\n");
            goto stateGetPayment;
        }
        else
        {
            printf("Sucessfully paid!!!\n");
        }
        clrscr();
        goto stateMenu;
    }
    else if(menuNo==12345)
    {
        char ans;
        printf("Program is going to shutdown.");
        printf("\nDo you really want to shutdown?");
        printf("\nEnter Y or N ");
        scanf(" %c",&ans);
        if(ans=='Y'||ans=='y'){
            return 0;
        }
        else
        {
            system("@cls||clear");
            goto stateMenu;
        }
    }
    else
    {
        printf("Wrong Pressed!!!\n");
        clrscr();
        goto stateMenu;
    }
    return 0;
}
