#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include<string.h>
#include <math.h>

typedef struct Opt
{
    //dynamically allocated name
    char *name;
    double odds;
}opt;

typedef struct Node
{
    struct Node *next;
    struct Node *prev;
    struct Opt *data;
}node;

 struct 
{
    //is a linked list
    struct Node *head;
    int evenOdds;
    int remainingOdds; 
    int opts ; 
} wheel;

void setEvenOdds()
{
    double odds = 100 / wheel.opts;
    struct Node *cur = wheel.head;
    while (cur =! NULL)
    {
        cur->data->odds = odds;
    }   
}

void add(char name[100], double odds)
{
    wheel.opts++;
    struct Node *cur = wheel.head;
    struct Node *prev;
    if (cur != NULL)
    {
        printf("here");
        while (cur->next != NULL)
        {
            cur = cur->next;
        }
        prev = cur;
        cur->next = malloc(sizeof(node));
        cur = cur->next;
        cur->prev = prev;
    }   
    else 
        cur = malloc(sizeof(node));

    cur->data = malloc(sizeof(opt));
    cur->data->name = malloc(strlen(name)*sizeof(char));
    if (wheel.evenOdds)
        setEvenOdds();
    else 
        {
            cur->data->odds = odds;
            wheel.remainingOdds -= odds;
        }   
}

struct Opt * roll()
{
    double winNum = (rand() % 100);
    struct Node *cur = wheel.head;
    double sum = 0.0;
    while(cur != NULL)
    {
        if (winNum >= sum && winNum < (sum + cur->data->odds))
            return cur->data;
        else
            cur = cur->next;
    }
    return NULL;
}

int main()
{
    srand( (unsigned) clock());
    wheel.opts = 0;
    char even;
    char name[100];
    double odds;
    char more;

    printf("Welcome to ScroreSettler!\n");

    printf("Would you like to use even odds (y/n)\n");
    do 
    {
        scanf(" %c", &even);
        if (even == 'y')
        {
            wheel.evenOdds = 1;
            wheel.remainingOdds = 0;
        }
        else if (even == 'n')
        {
            wheel.evenOdds = 0;
            wheel.remainingOdds = 100;
        }
        else
            printf("Invalid input\n");
    } while ( even != 'y' && even != 'n');

    printf("Please enter the first option\n");
    do
    {
        printf("name: ");
        scanf(" %s", &name);
        if (wheel.evenOdds)
            add(name, 0.0);
        else
        {
            int valid = 1;
            printf("odds: ");
            do
            {
                scanf(" %f", &odds);
                if (odds > wheel.remainingOdds || odds <= 0)
                {
                    printf("Invalid odds");
                    valid = 0;
                }
            }while (!valid);
            add(name,odds);
        }
        printf("Would you like to add more options (y/n)\n");
        do 
        {
            scanf(" %c", &more);
            if (more != 'y' && more != 'n')
            {
                printf("Invalid option\n");
            }
        } while (more != 'n' && more != 'y');      
    } while (more == 'y');
    
    printf("Rolling...\n");
    struct Opt *winner = roll();
    if (winner == NULL)
        printf("No Winner!\n");
    else
        printf("%s was won with a chance of %f %%!", winner->name, winner->odds);
}