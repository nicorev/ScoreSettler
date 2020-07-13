#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include<string.h>
#include <math.h>

typedef struct Opt
{
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
    struct Node *head;
    int evenOdds;
    int remainingOdds; 
    int opts ; 
} wheel;

void set_even_odds()
{
    double odds = 100 / wheel.opts;
    struct Node *cur = wheel.head;
    while (cur != NULL)
    {
        cur->data->odds = odds;
        cur = cur->next;
    }   
}

void add_opt(char name[100], double odds)
{
    struct Node *cur = wheel.head;
    struct Node *prev;
    wheel.opts++;
    if (cur == NULL)
    {
        cur = malloc(sizeof(node));
        cur->data = malloc(sizeof(opt));
        cur->data->name = malloc(strlen(name) * sizeof(char) + 1);
        strcpy(cur->data->name, name);
        wheel.head = cur;
        if (wheel.evenOdds)
         {
             set_even_odds();
         }
         else
         {
             cur->data->odds = odds;
             wheel.remainingOdds -= odds;
         } 
         
    }
    else
    {
        while(cur->next != NULL)
        {
            cur = cur->next;
        }
        cur->next = malloc(sizeof(node));
        prev = cur;
        cur = cur->next;
        cur->prev = prev;
        cur->data = malloc(sizeof(opt));
        cur->data->name = malloc(strlen(name) * sizeof(char) + 1);
        strcpy(cur->data->name, name);
        if (wheel.evenOdds)
         {
             set_even_odds();
         }
         else
         {
             cur->data->odds = odds;
             wheel.remainingOdds -= odds;
         } 
    }
    
}

struct Opt * roll()
{
    double winNum = (rand() % 100);
    struct Node *cur = wheel.head;
    double sum = 0.0;
    printf("winning number: %f\n", winNum);
    while(cur != NULL)
    {
        if (winNum >= sum && winNum < (sum + cur->data->odds))
            return cur->data;
        else
        {
            sum += cur->data->odds;
            cur = cur->next;
        }
    }
    return NULL;
}

void print_wheel()
{
    struct Node *cur = wheel.head;
    while(cur != NULL)
    {
        printf("name: %s\todds: %f\n", cur->data->name, cur->data->odds);
        cur = cur->next;
    }
}

void clear_mem(struct Node *head)
{
    if (head != NULL)
    {
       clear_mem(head->next);

        free(head->data->name);
        free(head->data);
        free(head);  
    }
}

int main()
{
    struct Opt *winner;
    char even;
    char name[100];
    double odds;
    char more;
    char rep;

    srand( (unsigned) clock());
    wheel.opts = 0;

    printf("Welcome to ScroreSettler!\n");

    printf("Would you like to use even odds? (y/n)\n");
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
        scanf(" %s", name);
        if (wheel.evenOdds)
           {
               add_opt(name, 0.0);
           }
        else
        {
            int valid = 1;
            do
            {
                printf("odds: ");
                scanf(" %lf", &odds);
                if (odds > wheel.remainingOdds || odds <= 0)
                {
                    printf("Invalid odds\n");
                    valid = 0;
                }
                else
                {
                    valid = 1;
                }
                
            }while (!valid);
            add_opt(name,odds);
        }
        printf("Would you like to add more options? (y/n)\n");
        do 
        {
            scanf(" %c", &more);
            if (more != 'y' && more != 'n')
            {
                printf("Invalid input\n");
            }
        } while (more != 'n' && more != 'y');      
    } while (more == 'y');
    
    do {
        printf("\nRolling...\n");
        print_wheel();
        winner = roll();

        if (winner == NULL)
            printf("No Winner!\n");
        else
            printf("%s was won with a chance of %f %%!\n", winner->name , winner->odds);
        printf("\nWould you like to roll again? (y/n)\n");
        do
        {
            scanf(" %c", &rep);
            if (rep != 'y' && rep != 'n')
            {
                printf("Invalid Input\n");
            }
        } while (rep != 'y' && rep !='n');
    
    }while(rep == 'y');

    clear_mem(wheel.head);
    return 0;
}