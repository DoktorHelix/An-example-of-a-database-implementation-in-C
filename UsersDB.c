#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
typedef struct User{
    char *login;
    char *password;
    char stud;
    char books;
    struct User *next;
} User;

int Comparison(char *str1, char *str2){
    for(int i = 0; *(str1+i) != '\0' || *(str2+i) != '\0'; i++)
    {
        if (*(str1+i) != *(str2+i))
            return 0;
    }
    return 1;
}

User * FindUser(User **Uhead, char *LogIn){
    User *help;
    help = *Uhead;
    while (help != NULL){
        if (Comparison(help->login, LogIn)){
            return help;
        }
        help = help -> next;
    }
    printf("There is no user with this login %s\n", LogIn);
    return NULL;
}

void Add(User **head, char *login, char *password, char stud, char books)
{
    User *tmp = malloc(sizeof(User));
    tmp->login = malloc(strlen(login)*sizeof(char)+1);

    strcpy(tmp->login, login);
    tmp->password = malloc(strlen(password)*sizeof(char)+1);

    strcpy(tmp->password, password);

    tmp->stud = stud;

    tmp->books = books;

    tmp->next = NULL;

    User *help;
    help = (*head);
    if ((*head) != NULL){
        while(help->next != NULL){
            help = help->next;
        }
        help->next = tmp;
    }
    else
        (*head) = tmp;
}

int FindLog(User **head, char *login, char *password){
    User *help;
    help = (*head);
    while (help != NULL){
        if (Comparison(help->login, login) && Comparison(help->password, password))
            return 1;
        help = help->next;
    }
    return 0;
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

void LibraryLog(char logstr1[], char login[])
{
    FILE *fp;
    fp = fopen("E:\\HWDifDebugg\\library.log","a");
    char *timing;
    const time_t timer = time (NULL);
    struct tm *t;
    t = localtime(&timer);
    timing = TimeSet(t);
    fprintf(fp, " data- %s  actoin -  %s, user - %s", timing, logstr1, login);
    fclose(fp);
}

int main()
{

    User *head;
    head = NULL;
    FILE *fp;
    fp = fopen("E:\\HWDifDebugg\\users.csv", "r");

    if (fp)
        printf("opening file\n");
    else
        printf("Err opening file...!\n");
    char InpStr[150];
    char UserData[4][50];
    while(fgets(InpStr, sizeof(InpStr), fp))
    {
        char *token;
        token = strtok(InpStr, ";");
        int i = 0;
        while(token != 0){
            strcpy(UserData[i], token);
            token = strtok(NULL, ";");

            i++;
        }
        Add(&head, UserData[0], UserData[1], *UserData[2], *UserData[3]);
    }

    char *str1 = malloc(sizeof(char) * 50);
    char *str2 = malloc(sizeof(char) * 50);

    int flag = 0;
    do{
        if (flag) {
            printf("Not valid Login or Password\n\n");
        LibraryLog("Unsuccessful login-", str1);
        }

        printf("Login: ");
        gets(str1);
        printf("Password: ");
        gets(str2);
        printf("\n");
        flag = 1;
    }while(!FindLog(&head, str1, str2));

    printf("Login successful, hello %s\n!", str1);
    LibraryLog("Login successful -", str1);
    User *user;
    user = FindUser(&head, str1);
    if(user->books == '1' && user->stud == '1')
    {
        printf("\nChoose menu you need:\n1-Students menu\n2-Books menu\n0-Exit\n");
        int button;
        int flag1 = 1;
        while (flag1){

            scanf("%i",&button);
            switch(button){
                case 1:
                    LibraryLog("User entered sudents menu\n:", str1);
                printf("Entering students menu...\n");
                system("C:\\Users\\b\\Documents\\LibHw\\bin\\Debug\\LibHw.exe");
                break;

                case 2:
                    LibraryLog("User entered books menu:\n",str1);
                printf("Entering books menu... \n");
                system("C:\\Users\\b\\Documents\\LibHwDif2\\bin\\Debug\\LibHwDif2.exe");
                break;
                case 0:
                    LibraryLog("User ends the work", str1);
                    printf("Closing program");
                    flag1 = 0;



         }
        }
    }else if(user->books == '1')
    {
        printf("You entered book menu, press to :\n1-Book menu\n 0-exit \n");
        LibraryLog("User entered students menu:",str1);
        int button;
        int flag2;
        while (flag2)
        {
            scanf("%i", &button);
            switch (button)
            {
                case 1:
                    system("C:\\Users\\b\\Documents\\LibHwDif2\\bin\\Debug\\LibHwDif2.exe");
                    printf("s");
                    break;

                case 0:
                    printf("Exit");
                    flag2 = 0;
                    break;

            }

        }
    }
    else if(user->stud == '1')
    {
        printf("You entered students menu:\n1-Students func\n0-exit\n");
        LibraryLog("User entered books menu:", str1);
        int button;
        int flag3 = 1;
        while (flag3) {
            scanf("%i", &button);
            switch (button) {
                case 1:
                system("C:\\Users\\b\\Documents\\LibHw\\bin\\Debug\\LibHw.exe");
                    break;

                case 0:
                    printf("exit");
                    flag3 = 0;
                    break;
            }
        }
    }else
        printf(" You have no power here! \n");
        LibraryLog("User with no rules tried to enter menu:", str1);
    return 0;
}
