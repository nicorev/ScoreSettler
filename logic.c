#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int odds;
int times;
int wins = 0;
char over_under;

int main ()
{
 srand( (unsigned) clock());
 printf("Welcome to ScoreSetller\n");
 printf("====================================================================\n");
 printf("odds:");
 scanf(" %d", &odds);
 do
 {
    printf("over or under (o/u): ");
    scanf(" %c", &over_under);
 } while (over_under != 'o' && over_under != 'u');
 char check = 'n';
 do
{
    printf("How many times would you like to flip the coin\n");
    scanf(" %d", &times);
    if(times % 2 == 0)
    {
        printf("Are you sure you want to flip the coin an even number of times (y/n): ");
        scanf(" %c", &check);
    }
    else 
        check = 'y';
} while(check != 'y');
int i;
if(over_under == 'o')
{  
    for(i = 0; i < times; i++)
    {
                int num = rand() % 100;
        printf("%d\n", num);
        if(num >= odds)
        wins++;
    }
}
else
{  
    for(i = 0; i < times; i++)
    {
        int num = rand() % 100;
        printf("%d\n", num);
        if(num < odds)
        wins++;
    }
}
printf("You won %d out of %d flips!\n", wins, times);
}