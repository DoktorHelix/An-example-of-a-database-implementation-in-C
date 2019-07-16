#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#define MAX 50

//======================================================================================================//
//--------------------------------------------------- Первыя сложность --------------------------------//
typedef struct Node                       //элемент базы данных, содержащий информацию о студенте
{
    char *number;                         //номер зачетки
    char *Name;
    char *Surname;
    char *Fname;
    char *facultet;
    char *speciality;
    struct Node *next;

} Node;

int Comparison(char str1[], char str2[])
{
    for(int i = 0; str1[i] != '\0' || str2[i] != '\0'; i++)
    {
        if (str1[i] != str2[i])
            return 0;
    }
    return 1;
}

Node * FindNum(Node **head, char number[] )
{
    Node *help;
    help = *head;
    while (help != NULL)
    {
        //printf("start next \n");
        //printf("%p\n%p\n", help, help->next);
        if (!strcmp(help->number, number))
        {
            printf("got it ");
            return help;
        }
        help = help->next;
    }

    return NULL;
}

Node * FindNumDb(Node **head, char *number){
    Node *help;
    help = *head;
    while (help != NULL){
        if (Comparison(help->number, number)){
            printf(" Got it  %s\n", number);
            return help;
        }
        help = help -> next;
    }
    printf("There is no student's with this number %s\n", number);
    return NULL;
}

int AddStudent(Node **head, char number[], char Name[], char Surname[], char Fname[], char facultet[], char speciality[]) //функия добавляет
{

    Node *pNewHead = malloc(sizeof(Node));
    Node *pOldHead;
    pOldHead = *head;

    pNewHead->number = malloc(strlen(number)* sizeof(char));
    strcpy(pNewHead->number, number);
    pNewHead->Name = malloc(strlen(Name)* sizeof(char));
    strcpy(pNewHead->Name, Name);
    pNewHead->Surname = malloc(strlen(Surname)* sizeof(char));
    strcpy(pNewHead->Surname, Surname);
    pNewHead->Fname = malloc(strlen(Fname)* sizeof(char));
    strcpy(pNewHead->Fname, Fname);
    pNewHead->facultet = malloc(strlen(facultet)* sizeof(char));
    strcpy(pNewHead->facultet,facultet);
    pNewHead->speciality = malloc(strlen(speciality)* sizeof(char));
    strcpy(pNewHead->speciality, speciality);
    pNewHead->next = malloc(8);
    pNewHead->next = NULL;

    printf(" student added \n");

    if (*head != NULL)

    {
        while ((pOldHead->next) != NULL)
        {
            pOldHead = pOldHead->next;
            printf(" step2 ");
        }
        pOldHead->next = pNewHead;
        printf(" step3 ");

    }
    else
        *head = pNewHead;
    printf(" final\n ");
    return 1;

}

int RemoveStudent(Node **head,char number[])                     //удаление по номеру зачетки
{
    Node *pOldHead;
    pOldHead = (*head);
    printf(" step one ");
    if (Comparison(pOldHead->number, number))
    {
        (*head) = pOldHead -> next;
        printf(" condition:one ");
        free(pOldHead);
        return 1;
    }
    while (!Comparison(pOldHead->next->number, number))
    {
        printf(" condition:two ");
        pOldHead = pOldHead ->next;
        if (pOldHead->next == NULL)
        {
            return 0;
        }

    }
    printf(" step two ");
    Node *help;
    help = pOldHead->next;
    pOldHead->next = (pOldHead->next->next);
    free(help);

    printf(" final step\n ");
    return 1;

}

int Edit(Node **head,char number[], char Name[], char Surname[], char Fname[], char facultet[], char speciality[])
{
    Node *pOldHead;
    pOldHead = (*head);
    printf(" step one ");
    if (Comparison(pOldHead->number, number))
    {
        strcpy( pOldHead->Name , Name);
        strcpy( pOldHead->Surname , Surname);
        strcpy( pOldHead->Fname , Fname);
        strcpy( pOldHead->facultet , facultet);
        strcpy( pOldHead->speciality , speciality);
        printf(" edditing... \n");
        return 1;
    }
    while (!Comparison(pOldHead->next->number, number))
    {
        printf(" condition:two ");
        pOldHead = pOldHead ->next;
        if (pOldHead->next == NULL)
        {
            return 0;
        }

    }
    printf(" step two ");
    Node *help;
    help = pOldHead->next;

    strcpy( help->Name , Name);
    strcpy( help->Surname , Surname);
    strcpy( help->Fname , Fname);
    strcpy( help->facultet , facultet);
    strcpy( help->speciality , speciality);

    printf(" final step\n ");
    return 1;
}

int SaveData(Node **head, char *filename)
{
    FILE *fp;
    fp = fopen("C:\\Users\\b\\Documents\\LibHw\\students.csv", "w");
    Node *help;
    help = (*head);
    printf("first step->");
    if (fp == NULL)
    {
        printf("Error opening file...\n");
        return -1;
    }
    while (help != NULL)
    {
        fprintf(fp,"%s;%s;%s;%s;%s;%s", help->number, help->Name, help->Surname, help->Fname, help->facultet,help->speciality);
        help = help->next;
        printf("step two->");
    }
    if (fclose(fp) != 0)
    {
        printf("Error closing file...");
        return 0;
    }
    fclose(fp);
    printf("final step.");
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
    fprintf(fp, " data- %s  action -  %s\n", timing, logstr1);
    fclose(fp);
}
//----------------------------------------------------------------------------------------------------------------------//
int main()
{
    Node *head = NULL;
    FILE *fp;
    fp = fopen("C:\\Users\\b\\Documents\\LibHw\\students.csv", "r");

    char inpStr[150];
    char StudData[6][66];

    if (fp == NULL)
        printf("kg");

    while(fgets(inpStr, 150, fp))
    {
        puts(inpStr);
        char *token;
        token = strtok(inpStr, ";");
        int i = 0;
        while (token != NULL)
        {
            strcpy(StudData[i] , token);

            token = strtok (NULL, ";");
            i++;
        }
        AddStudent(&head, StudData[0], StudData[1], StudData[2], StudData[3], StudData[4], StudData[5] );
    }

    fclose(fp);
    //---------------------------------------------------------------------------------------//
    printf("Menu: \n1-Add student\n2-Remove Student\n3-edit student info\n4-check student info\n0-save and exit\n");
    //-------------------------------------//
    char number[20];
    char Name[20];
    char Fname[20];
    char Surname[20];
    char facultet[6];
    char speciality[MAX];
    //======================================================================================================================//


    //=====================================================================================================================//
    //-------------MENU-----MENU-------------------------------------------------------------------------------------------//
    //=====================================================================================================================//



    int menu;
    int flag = 1;
    while (flag)
    {
        scanf("%i", &menu);
        switch (menu)
        {
            case 1:
                printf("Enter student's data to add: \n");
                printf("Enter Number: ");
                scanf("%s", number);

                Node *studentAdd;
                studentAdd = FindNum(&head, number);
                if (studentAdd)
                {
                    printf("Such a student already exists in the database.\n");
                    LibraryLog("trying do add existing student ");
                }
                else
                {
                    printf("Enter Name: ");
                    scanf("%s", Name);
                    printf("Enter Surname: ");
                    scanf("%s", Surname);
                    printf("Enter Fname: ");
                    scanf("%s", Fname);
                    printf("Enter facultet: ");
                    scanf("%s", facultet);
                    printf("Enter speciality: ");
                    scanf("%s", speciality);
                    AddStudent(&head, number, Name, Surname, Fname, facultet, speciality);
                    LibraryLog("Student added");
                }

                //  printf(" case 1 ");
                break;

            case 2:

                printf("Enter Student's number to remove: ");

                scanf("%s", number);
                Node *studentX;
                studentX = FindNumDb(&head, number);
                if(studentX)
                {

                    RemoveStudent(&head, number);
                }
                else {
                    printf("There is no student with such number!Returning to menu...\n");
                    LibraryLog("Trying to remove nonexistent student: ");
                     }
                //  PrintNode(&head);
                //  printf(" case 2 ");
                break;

            case 3:
                printf("Enter Student's data to edit:\n ");
                printf("Enter Number: ");
                scanf("%s", number);
                Node *studentE;
                studentE = FindNum(&head, number);
                if(studentE)
                {

                    printf("Enter Name: ");
                    scanf("%s", Name);
                    printf("Enter Surname: ");
                    scanf("%s", Surname);
                    printf("Enter Fname: ");
                    scanf("%s", Fname);
                    printf("Enter facultet: ");
                    scanf("%s", facultet);
                    printf("Enter speciality: ");
                    scanf("%s", speciality);
                    Edit(&head, number, Name, Fname, Surname, facultet, speciality);
                    LibraryLog("Editing student:");
                    printf("Editing done.\n");
                }
                else {
                    printf("Wrong number!Returning to menu...\n");
                    LibraryLog("Trying to edit nonexistent student:");

                }
                //    printf(" case 3 ");
                break;

            case 4:
                printf("Enter student's number to check: ");
                Node *student;
                char *number1 = malloc(32 * sizeof(char));
                scanf("%s", number1);
                student = FindNum(&head, number1);
                if (student)
                {
                    printf("Number: %s\n", student->number);
                    printf("Name: %s\n ", student->Name);
                    printf("Surname: %s\n", student->Surname);
                    printf("Fname: %s \n", student->Fname);
                    printf("facultet: %s \n", student->facultet);
                    printf("speciality: %s \n", student->speciality);
                    LibraryLog("Checking student's info:");
                    //       printf(" case 4 ");
                }
                else {
                    LibraryLog("Trying to check nonexistent student:");
                    printf("There is no student with such number!! Returning to menu...\n");
                }
                break;

            case 0:

                SaveData(&head, "C:\\Users\\b\\Documents\\LibHw\\students.csv");
                //    printf(" case 0 ");
                flag = 0;

                break;

        }
    }
    return 0;
}



