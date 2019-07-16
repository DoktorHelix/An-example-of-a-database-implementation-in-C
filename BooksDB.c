#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#define MAX 50

typedef struct Book
{
    char *isbn;
    char *Authors;
    char *totb;                     //title of the book
    int countOfBooks;              //COB
    int countOfAvalibleBooks;     //COAB
    struct Book *next;
} Book;

int Comparison(char *str1, char *str2){
    for(int i = 0; *(str1+i) != '\0' || *(str2+i) != '\0'; i++){

        if (*(str1+i) != *(str2+i))
            return 0;
    }
    return 1;
}

Book * FindBook(Book **head, char *isbn){
    Book *help;
    help = *head;
    while (help != NULL){
        if (Comparison(help->isbn, isbn)){
            return help;
        }
        help = help -> next;
    }
    printf("There is no book with this isbn %s\n", isbn);
    return NULL;
}

void AddBookToList(Book **Bhead, char isbn[], char Authors[], char totb[], int COB, int COAB)
{
    Book *tmp = malloc(sizeof(Book));

    tmp -> isbn = malloc(strlen(isbn)* sizeof(char)+1);
    strcpy(tmp->isbn, isbn);

    tmp -> Authors = malloc(strlen(Authors)* sizeof(char)+1);
    strcpy(tmp->Authors, Authors);

    tmp -> totb = malloc(strlen(totb)* sizeof(char)+1);
    strcpy(tmp->totb, totb);

    tmp -> countOfBooks = COB;

    tmp ->countOfAvalibleBooks = COAB;

    tmp->next = NULL;
    printf("book added to list\n");

    Book *help;
    help = (*Bhead);
    if ((*Bhead) != NULL){
        while(help->next != NULL){
            help = help->next;
        }
        help->next = tmp;
    }
    else
        (*Bhead) = tmp;


}

int RemoveBook(Book **Bhead,char isbn[])                     //удаление по номеру зачетки
{
    Book *pOldHead;
    pOldHead = (*Bhead);
    printf(" step one ");
    if (Comparison(pOldHead->isbn, isbn))
    {
        (*Bhead) = pOldHead -> next;
        printf(" condition:one ");
        free(pOldHead);
        return 1;
    }
    while (!Comparison(pOldHead->next->isbn, isbn))
    {
        printf(" condition:two ");
        pOldHead = pOldHead ->next;
        if (pOldHead->next == NULL)
        {
            return 0;
        }

    }
    printf(" step two ");
    Book *help;
    help = pOldHead->next;
    pOldHead->next = (pOldHead->next->next);
    free(help);
    printf(" final step\n ");
    return 1;

}

int IssueTheBook(Book **Bhead, char isbn[])
{
    Book *help;
    help = FindBook(Bhead, isbn);

    if (help->countOfAvalibleBooks <= 0) {
        printf("There is no avalible books");
        return -1;
    } else
        {
        help->countOfAvalibleBooks -= 1;
        }
    return 0;
}

int TakeTheBook(Book **Bhead, char isbn[])
{
    Book *help;
    help = FindBook(Bhead, isbn);

    if (help->countOfAvalibleBooks >= help->countOfBooks) {
        printf("There is not our book,lol\n");
        return -1;
    } else
    {
        help->countOfAvalibleBooks += 1;
    }
    return 0;

}

int SaveData(Book **head, char *filename)
{
    FILE *fp;
    fp = fopen("E:\\booksDB\\books.csv", "w");
    Book *help;
    help = (*head);
   // printf("first step->");
    if (fp == NULL)
    {
        printf("Error opening file...\n");
        return -1;
    }
    while (help != NULL)
    {
        fprintf(fp,"%s;%s;%s;%i;%i\n", help->isbn, help->Authors, help->totb, help->countOfBooks, help->countOfAvalibleBooks);
        help = help->next;
     //   printf("step two->");
    }
    if (fclose(fp) != 0)
    {
        printf("Error closing file...");
        return 0;
    }
    fclose(fp);
 //   printf("final step.");
    free(*head);
    return 1;
}

char *TimeSet(struct tm *t)
{
    char time[40];
    char *new;

    for (int i = 0; i < 40; i++)
        time[i]=0;

    int len = strftime(time, 40, "%d.%m.%Y   %H:%M:%S - ", t);
    new = (char*)malloc(sizeof(time));
    strcpy(new, time);
    return (new);
}

void LibraryLog(char logstr1[])
{
FILE *fp;
fp = fopen("E:\\HWDifDebugg\\library.log","a");
char *timing;
const time_t timer = time (NULL);
struct tm *t;
t = localtime(&timer);
timing = TimeSet(t);
fprintf(fp, " data- %s  actoin -  %s\n", timing, logstr1);
fclose(fp);
}

int main() {
    FILE *fp;
    Book *Bhead;
    Bhead = NULL;
    fp = fopen("E:\\booksDB\\books.csv", "r");

    char inpBook[150];
    char BookData[5][66];

    if (fp == NULL)
        printf(" return ");

    while (fgets(inpBook, 150, fp))
    {
        puts(inpBook);
        char *token;
        token = strtok(inpBook, ";");
        int i = 0;
        while (token != NULL)
        {
            strcpy(BookData[i], token);
            token = strtok(NULL, ";");
            i++;
        }
        AddBookToList(&Bhead, BookData[0], BookData[1], BookData[2], atoi(BookData[3]), atoi(BookData[4]));
    }
    fclose(fp);

    Book *knigga;
    int flag = 1;
    int button;

    char isbn[10];
    char Authors[20];
    char totb[MAX];
    int COB;
    int COAB;

    printf("Book menu:\n1-Add book\n2-Delete book\n3-Issue the book\n4-Take the book\n0-Save and exit\n");
    while (flag)
    {
        scanf("%i", &button);
        switch (button)
        {
            case 1:
                printf("Enter book's data to add:\n");
                printf ("Enter isbn: ");
                scanf("%s", isbn);
                knigga = FindBook(&Bhead, isbn);
                if (knigga) {
                    printf("This is CopyPasta \n");
                    LibraryLog("Trying to add existing book");
                }
                else
                {
                    printf("Enter book's authors:");
                    scanf("%s", Authors);
                    printf("Enter book's title: ");
                    scanf("%s", totb);
                    printf("Enter number of book's: ");
                    scanf("%i", &COB);
                    printf("Enter number of avalible books: ");
                    scanf("%i", &COAB);

                    AddBookToList(&Bhead, isbn, Authors, totb, COB, COAB);
                    printf("Book added to list");
                    LibraryLog("Added book to the lib");

                }
                break;

            case 2:
                printf("Enter book's isbn do delete: ");
                scanf("%s", isbn);
                knigga = FindBook(&Bhead, isbn);
                if (knigga)
                {
                    RemoveBook(&Bhead, isbn);
                    printf("Book successfully deleted from the list");
                    LibraryLog("Book successfully deleted");
                }
                else {
                    LibraryLog("Trying to delete an existing book");
                    printf("There is no book with such isbn");
                }
                break;

            case 3:
                printf("Enter book's isbn do issue: ");
                scanf("%s", isbn);
                knigga = FindBook(&Bhead, isbn);
                if (knigga)
                {
                    IssueTheBook(&Bhead, isbn);
                    LibraryLog("book   issued to the student");
                    printf("Book issued\n");
                }
                else {
                    LibraryLog("user tried to issue nonexistent book ");
                    printf("There is no book with such isbn\n");
                }
                break;

            case 4:
                printf("Enter book's isbn do take: ");
                scanf("%s", isbn);
                knigga = FindBook(&Bhead, isbn);
                if (knigga)
                {
                    TakeTheBook(&Bhead, isbn);
                    printf("Book taked\n");
                    LibraryLog("User took a book from the lib");
                }
                else {
                    LibraryLog("User tried to take book, that doesn't exist in the list");
                    printf("There is no book with such isbn\n");
                }
                break;

            case 0:
                SaveData(&Bhead, "E:\\booksDB\\books.csv");
                LibraryLog("Book session ended, User: ");
                printf("Closing book menu...");
                flag = 0;
                break;

        }
    }

    return 0;
}