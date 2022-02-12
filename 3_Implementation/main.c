/**
 * @file main.c
 * @author Sambangi Bogiraju (bogirajusambangi@gmail.com)
 * @brief Project in C Language for Module 1
 * @version 0.1
 * @date 2022-02-12
 * 
 * @copyright Copyright (c) 2022
 * 
 */


#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
#include<string.h>
#include<windows.h>

 void input_fun();
 void writefile_fun();
 void search_fun();
 void showoutput ();

 struct date{
       int month;
       int day;
       int year;
       };

  struct account {
    int num;
    char name[50];
    int acno;
    float ph_no;
    char street[22];
    char city[33];
    char acc_type;
    float oldbal;
    float newbal;
    float payment;
    struct date last_payment;
  }customer;
  int tl,sl,ts;
 void main()
    {
      int i,n;
      char ch;
      system("cls");

      printf("\e[?25l");
      printf(" \n  COUNTER BILLING SYSTEM:\n\n");
      printf("------------------------------\n");
      printf("\n   1:To add New account on list\n");
      printf("   2:To Find customer account\n");
      printf("   3:Exit\n");
      printf("\n------------------------------\n");
      do{
           printf("\nSelect one option to go Further ?");
           ch=getche();
      }while(ch<='0' || ch>'3');
      switch(ch){
        case '1':
            system("cls");
            printf("\nHow many customer accounts?");
            scanf("%d",&n);
            for(i=0;i<n;i++){
                input_fun();
                if(customer.payment>0)
                    customer.acc_type=(customer.payment<0.1*customer.oldbal)? 'O': 'D';
                else
                    customer.acc_type=(customer.oldbal>0)?'D' : 'C';
                customer.newbal=customer.oldbal - customer.payment;
                writefile_fun();
            }
            main();
        case '2':
            system("cls");
            printf("Search by what?\n");
            printf("\n1 --- Search by customer number\n");
            printf("2 --- Search by customer name\n");
            search_fun();
            ch=getche();
            main();
        case '3':
            system("cls");
            printf("\n\t ***Our Valuable Customer***");
            void gotoxy(int x, int y)
{
            COORD c = { 25, 25};  
            SetConsoleCursorPosition(  GetStdHandle(STD_OUTPUT_HANDLE) , c);
}
            _cprintf("\n\t    *Thank you & Vist Again*");
            exit(1);
      }
 }

   void input_fun()
    {
      FILE *fp=fopen("bidur.dat","rb");
      fseek (fp,0,SEEK_END);
      tl=ftell(fp);
      sl=sizeof(customer);
      ts=tl/sl;
      fseek(fp,(ts-1)*sl,SEEK_SET);
      fread(&customer,sizeof(customer),1,fp);
      printf("\nCustomer no:%d\n",++customer.num);
      fclose(fp);
      printf("       Account num             :");
      scanf("%d",&customer.acno);
      printf("\n       Name                    :");
      scanf("%s",customer.name);
      printf("\n       Mobile no               :");
      scanf("%f",&customer.ph_no);
      printf("\n       Street                  :");
      scanf("%s",customer.street);
      printf("\n       City                    :");
      scanf("%s",customer.city);
      printf("\n       Previous balance        :");
      scanf("%f",&customer.oldbal);
      printf("\n       Current payment         :");
      scanf("%f",&customer.payment);
      printf("\n       Payment date(mm/dd/yyyy):");
      scanf("%d/%d/%d",&customer.last_payment.month,&customer.last_payment.day,&customer.last_payment.year);
      return;
   }

   void writefile_fun()
   {
      FILE *fp;
      fp=fopen("bidur.dat","ab");
      fwrite(&customer,sizeof(customer),1,fp);
      fclose(fp);
      return;
   }

   void search_fun()
   {
     char ch;
     char nam[100];
     int n,i,m=1;
     FILE *fp;
     fp=fopen("bidur.dat","rb");
     do{
        printf("\nEnter your choice:");
        ch=getche();
     }while(ch!='1' && ch!='2');
     switch(ch){
          case '1':
            fseek(fp,0,SEEK_END);
            tl=ftell(fp);
            sl=sizeof(customer);
            ts=tl/sl;
            do{
            printf("\nchoose customer num:");
            scanf("%d",&n);
            if(n<=0 || n>ts)
            printf("\nenter correct\n");
            else{
                fseek(fp,(n-1)*sl,SEEK_SET);
                fread(&customer,sl,1,fp);
               showoutput();
            }
            printf("\n\nagain?(y/n)");
            ch=getche();
            }while(ch=='y');
            fclose(fp);
            break;
          case '2':
            fseek(fp,0,SEEK_END);
            tl=ftell(fp);
            sl=sizeof(customer);
            ts=tl/sl;
            fseek(fp,(ts-1)*sl,SEEK_SET);
            fread(&customer,sizeof(customer),1,fp);
            n=customer.num;

            do{
            printf("\nEnter the name:");
            scanf("%s",nam);
            fseek(fp,0,SEEK_SET);
            for(i=1;i<=n;i++)
            {
                 fread(&customer,sizeof(customer),1,fp);
                 if(strcmp(customer.name,nam)==0)
                 {
                showoutput();
                m=0;
                break;
                 }
            }
            if(m!=0)
            printf("\n\nDoesn't exist\n");
            printf("\nAnother?(y/n)");
            ch=getche();
            }while(ch=='y');
            fclose(fp);
          }
          return;
     }


   void showoutput()
     {
       printf("\n\n    Customer no    :%d\n",customer.num);
       printf("    Name        :%s\n",customer.name);
       printf("    Mobile no      :%.f\n",customer.ph_no);
       printf("    Account num :%d\n",customer.acno);
       printf("    Street         :%s\n",customer.street);
       printf("    City           :%s\n",customer.city);
       printf("    Old balance    :%.2f\n",customer.oldbal);
       printf("    Current payment:%.2f\n",customer.payment);
       printf("    New balance    :%.2f\n",customer.newbal);
       printf("    Payment date   :%d/%d/%d\n\n",customer.last_payment.month,customer.last_payment.day,customer.last_payment.year);
       printf("    Account status :");
       switch(customer.acc_type)
          {
          case 'C':
         _cprintf("CURRENT\n\n");
         break;
          case 'O':
         _cprintf("OVERDUE\n\n");
         break;
          case 'D':
         _cprintf("DELINQUENT\n\n");
         break;
          default:
         _cprintf(" Invalid\\n\n");
          }
          printf("\033[0;37m");
          return;
       }
