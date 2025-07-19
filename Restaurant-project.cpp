#include<stdio.h>
#include<time.h>
#include<stdlib.h>
#include<string.h>
#define FILENAME "itemsprice.csv"
struct Item{
   int itemNo;
   char itemName[20];   //camcelCase Notation
   int price;
};
struct Order{
   int itemNo;
   char itemName[20];   //camcelCase Notation  
   int price, qty,amount;
};
int main(){
  FILE *f, *g;
  char buffer[1024] , line[100] , billname[20];
  time_t secs;
  struct tm *local;
  f=fopen(FILENAME, "r");
  if(f==0){   //OR  if(!f)
    printf("\nSorry. ItemsPrice.csv Not Found in Project Folder");
    return 1;
  }
  //Otherwise
  int n,i,choice,sum=0, index=-1;
  fscanf(f,"%d",&n);
  printf("Total Items=%d", n); //For Debugging - Bhupendra Khilrani
  if(n<=0){
    printf("\nSorry. No Sufficient Items Found in ItemsPrice.csv");
    return 2;
  }
  //Otherwise, Read all data into array of struct
  Item *s=(Item*)calloc(n, sizeof(Item));
  Order *r=(Order*)calloc(n, sizeof(Order));
  for(i=0; i<n; i++){
    fscanf(f,"%d,%20[^,],%d", &s[i].itemNo, &s[i].itemName, &s[i].price );
  }
  menu:   //Label for goto
  printf("\nRestaurant Menu. Rate List\n");
  printf("\n%-7s %-22s %-10s", "ItemNo.", "Item Name", "Price (Rs)");
  for(i=0; i<n; i++){
    //fscanf(f,"%d,%20[^,],%d", &s[i].itemNo, &s[i].itemName, &s[i].price );
    printf("\n%7d. %-20s %10d/-", s[i].itemNo, s[i].itemName, s[i].price);
  }
  options:  //Label for goto
  printf("\nEnter Your Choice. (Max %d Orders)", n);
  printf("\nPress 0:Checkout   -1: Cancel Order  -2: Menu Again");
  printf("\n-3 Show Order -4:Exit App:");
  scanf("%d", &choice);
  if(choice==-4){   //Exit App
    printf("\nSoftware Designed by MANAS");
    goto end;
  }
  if(choice==-3)  //Show order
  {
      if (index ==-1){
        printf("\nNo Order Found");
        goto options;
      }
      //Otherwise
      printf("\nOrder Details :");
      for(i=0; i<=index;i++){
        printf("\n%d-%s-Rs %d/-  %d  %d" , r[i].itemNo, r[i].itemName, r[i].price, r[i].qty,r[i].amount);
      }
      goto options;
  }
  else if(choice==-2){
    goto menu;
  }
  else if(choice==-1){   //Cancel Order
    sum=0; index=0;
    printf("\nOrder Canceled. Showing Menu Again.");
    goto menu;
  }
  else if(choice==0){   //Checkout
    printf("\nOrder Total: Rs %d /-", sum);
    secs = time(0);
     /* convert to localtime */
    local = localtime(&secs);
    sprintf(billname, "bill-%02d%02d%02d.txt", local->tm_hour, local->tm_min, local->tm_sec);
    printf("%s", billname);

    g=fopen(billname ,"w");
    fprintf(g,"%s" , buffer);
    fclose(g);
    printf("\nBill Saved Successfully as bill.txt");
    sum=0,index=-1;   //Re-initialize sum
    strcpy(buffer,""); //Make it Empty
    goto menu;
  }
  else if(choice<-2 || choice>n){
    printf("\nSorry. Invalid Choice. Try Again");
  }
  //Otherwise, Store Item into order and compute sum
    //index starts with 0, choice with 1

  if(index<n)
        index++;
  else{
    printf("Max Orders cannot exceed %d" , n);
    goto options;
  }

  printf("\nEnter Qty for Item %d:" , choice);
  scanf("%d" , &r[index].qty);
  r[index].itemNo=s[choice-1].itemNo;
  strcpy(r[index].itemName, s[choice-1].itemName);
  r[index].price=s[choice-1].price;
  r[index].amount=r[index].qty*r[index].price;
  sum=sum + r[index].amount;
  sprintf(line, "%d. %-20s %10d/- %5d %10d\n",r[index].itemNo,
           r[index].itemName, r[index].price, r[index].qty, r[index].amount);
  strcat(buffer,line);
  //index++;   //Increase Index
  goto options;
end:
  fclose(f);
  printf("\nThanks. Visit Again");
}