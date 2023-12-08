#include<stdio.h>
#include<mysql.h>
#include<windows.h>
#include<time.h>
#include<stdlib.h>
#include<conio.h>
#include <string.h>
#include <io.h>
#ifdef _WIN32
#include <conio.h>
#else
#include <unistd.h>
#include <termios.h>
#endif
int get_user_input(char *input, int maxLength) {
#ifdef _WIN32
    if (_kbhit()) {
        fgets(input, maxLength, stdin);
        return 1;
    }
#else
    struct termios old_attr, new_attr;
    tcgetattr(fileno(stdin), &old_attr);
    new_attr = old_attr;
    new_attr.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(fileno(stdin), TCSANOW, &new_attr);

    fd_set fdset;
    struct timeval tv;
    FD_ZERO(&fdset);
    FD_SET(fileno(stdin), &fdset);
    tv.tv_sec = 0;
    tv.tv_usec = 0;
    select(fileno(stdin) + 1, &fdset, NULL, NULL, &tv);

    if (FD_ISSET(fileno(stdin), &fdset)) {
        fgets(input, maxLength, stdin);
        return 1;
    }

    tcsetattr(fileno(stdin), TCSANOW, &old_attr);
#endif

    return 0;
}
 
typedef struct chat
{
    char time[30];
    char name[20];
    char message[100];
    int status;
}chat;
typedef struct users
{
	char  name[10];
	char  account[10];
	char  password[10];
	char  question[20];
	char  answer[10];
    int status;
    int pass;
}user;

int function1=1;
int function2=1;
int function3=1;
int function4=1;

int check_admi(MYSQL *mysql);
void create_admi(MYSQL *mysql);
void admi_start();
void admi_menu();
int select(int a,int b);
int check_select(int select,int a,int b);
int check_password(user user);
void switch_select(int select,MYSQL *mysql);
void check_user_information(MYSQL *mysql);
void check_user_information_screen();
void check_user_switch_select(int select,MYSQL *mysql);
MYSQL *log_in_mysql();
void exit_mysql(MYSQL *mysql);
void admi_list(MYSQL_RES *result);
void admi_view(MYSQL *mysql);
void admi_find(MYSQL *mysql);
void admi_clear(MYSQL *mysql);
void admi_delete(MYSQL *mysql);
void delete_rollback(MYSQL *mysql);
void admi_modify(MYSQL *mysql);
void modify_administrator_account(MYSQL *mysql);
int check_user(MYSQL *mysql,char *m,char *find_key);
void enter(char*m);
int secure(char *password);
void user_register(MYSQL *mysql);
void user_log_in(MYSQL *mysql);
void user_change_password(MYSQL *mysql);
void user_retrieve_password(MYSQL *mysql);
void user_start();
void user_menu();
void user_select_switch();
void user_switch_select(int select,MYSQL *mysql);
void user_exit();
void admi_load(MYSQL *mysql);
user information_return(MYSQL *mysql,char *record,int i);
void remove_spaces(char *m);
void exit_the_system();
void admi(MYSQL *mysql);
void a_b();void b_a();
void b_c();void c_b();
void game(user user,MYSQL *mysql);
void board();
void switch_game(int select,user user,MYSQL *mysql);
void enter_alien();
void enter_snake();
void enter_table();
void enter_sweep();
void enter_pg(user user);
void upload_message(MYSQL *mysql,chat chat,int *i);
void show_chatting(MYSQL *mysql,int *i);
void engine_chat(MYSQL *mysql,user user);
void two(MYSQL *mysql);

void a_b()
{
    function2=1;    
}
void b_a()
{
    function2=0;
}
void b_c()
{
    function3=1;
}
void c_b()
{
    function3=0;
}
void c_d()
{
    function4=1;
}
void d_c()
{
    function4=0;
}
MYSQL *log_in_mysql()
{
    
    MYSQL *mysql=mysql_init(0);
    if(!mysql_real_connect(mysql, "mytry.e3.luyouxia.net", "remote_user", "remote", "Try_users", 10670, NULL, 0))
    {
        printf("Fail to connect,%s",mysql_error(mysql));
        mysql_close(mysql);
    }
    if(mysql_query(mysql,"set names gbk"))
    {
        printf("Fail to change code,%s",mysql_error(mysql));
        mysql_close(mysql);
    }
    return mysql;
}
int check_admi(MYSQL *mysql)
{
    char query[100];
    sprintf(query,"select * from B");
    mysql_query(mysql,query);
    MYSQL_RES *result=mysql_store_result(mysql);
    if (result!=NULL)
    {
        int num_rows = mysql_num_rows(result);
        mysql_free_result(result);
        return (num_rows > 0);
    }
    else return 0;
}

void create_admi(MYSQL *mysql)
{
    user user;
    printf("��ע�����Ա�˻�");
    printf("\n�û���:");
    scanf("%s",&user.name);
    printf("\n����:");
    scanf("%s",&user.password);
    char query[100];
    sprintf(query,"INSERT INTO b (administrator, password) VALUES ('%s', '%s')",user.name, user.password);
    mysql_query(mysql,query);
}

user information_return(MYSQL *mysql,char *record,int i)
{
    char query[100];
    user user;
    if(i=1) sprintf(query,"select * from A where name='%s'",record);
    else if(i=2) sprintf(query,"select * from A where name='%s'or account='%s'",record,record);
    mysql_query(mysql,query);
    MYSQL_RES *result=mysql_store_result(mysql);
    MYSQL_ROW row;
    while(row=mysql_fetch_row(result))
    {
        strcpy(user.account, row[1]);
        strcpy(user.name, row[0]);
        strcpy(user.password, row[2]);
        strcpy(user.question, row[3]);
        strcpy(user.answer, row[4]);
        user.status=atoi(row[5]);
    }
    return user;
}

void user_start()
{
    system("cls");
    printf("\n\n\t\t��\t\t                                \t\t��");
    printf("\n\n\t\tʹ\t\t                                \t\t��");
    printf("\n\n\t\t��\t\tWelcome to join the user system!\t\t��");
    printf("\n\n\t\t��\t\t                                \t\t��");
    printf("\n\n\t\t��\t\t                                \t\t��");

    Sleep(2000);
    system("cls");
}

void user_menu()
{
    system("cls");
	printf("\n		***************************  �û��˵�  **************************\n");
    printf("\t\t*\t                                                       *\n");         
	printf("\t\t*\t      1.��¼�˺�                                       *\n");         
    printf("\t\t*\t      2.ע���˺�                                       *\n");             
    printf("\t\t*\t      3.�޸�����                                       *\n");         
    printf("\t\t*\t      4.�һ�����                                       *\n");         
	printf("\t\t*\t      5.�˳�����                                       *\n");
    printf("\t\t*\t      6.����Աϵͳ                                     *\n");          
    printf("\t\t*\t                                                       *\n");              
	printf("		****************************************************************\n");
	printf("\n");
}

void user_switch_select(int select,MYSQL *mysql)
{

    switch (select)
    {
    case 1:user_log_in(mysql); break;
    case 2:user_register(mysql); break;
    case 3:user_change_password(mysql);break;
    case 4:user_retrieve_password(mysql);break;
    case 5:user_exit();break;
    case 6:admi(mysql);break;
    }

}

void user_register(MYSQL *mysql)
{
    user user;
    char name[]="name";
    char temp_password[10];
    while(1)
    {
        system("cls");
        printf("\n�������û���:");
        scanf("%s",&user.name);
        if(check_user(mysql,name,user.name))
        {
            MessageBox(NULL,"�û����Ѵ���.","Tip",MB_OK);
            continue;
        }
        break;
    }
    
    
    while(1)
    {
        do
        {
            printf("\n����������:");
            enter(user.password);
        } while (!secure(user.password));
        printf("\n��ȷ������:");
        enter(temp_password);
        if (strcmp(user.password,temp_password))
        {
            MessageBox(NULL,"�������벻һ��","Tip",MB_OK);
            continue;
        }
        break;
    }
    
    printf("\nϵͳ����Ϊ�������˺�");
    Sleep(500);
    int temp[10];char account[]="account";
    srand((unsigned int)time(NULL));
    do
    {
        for(int h=0;h<6;h++){temp[h]=rand()%6;user.account[h]='0'+temp[h];user.account[h+1]='\0';}
    } while (check_user(mysql,account,user.account));
    printf("\n����˺��� %s",user.account);
    printf("\n�����������һ����������.");
    scanf("%s",&user.question);
    printf("\n�������:");
    scanf("%s",&user.answer);
    char query[100];
    sprintf(query,"INSERT INTO A (name, account, password, question, answer, status) VALUES ('%s', '%s', '%s', '%s', '%s', %d)",user.name, user.account, user.password, user.question, user.answer, 0);
    mysql_query(mysql,query);
    printf("ע��ɹ���");
}

void user_log_in(MYSQL *mysql)
{
    char record[10];char name[]="name";char account[]="account";
    system("cls");
    printf("\n�����������û������˺�:");
    scanf("%s",&record);
    if((!check_user(mysql,name,record))&&(!check_user(mysql,account,record)))
        {
            MessageBox(NULL,"�û�������","Tip",MB_OK);
            return;
        }
    user user=information_return(mysql,record,2);
    if(check_password(user)) 
    {
        system("cls");
        printf("\n\n\t%s,��ӭ����¼ϵͳ",user.name);
        Sleep(500);
        game(user,mysql);
    }
    else 
    {
        MessageBox(NULL,"���ѳ�������Դ���","Tip",MB_OK);
    }
}

int check_password(user user)
{
    char password[10];int time=0;
    while(1)
    {
        printf("\n��������������:");
        enter(password);
        time++;
        if(time<5&&strcmp(password,user.password))
        {
            char tip[30];
            sprintf(tip,"�������.�������Գ���%d��.",5-time);
            MessageBox(NULL,tip,"Tip",MB_OK);
            continue;
        }
        break;
    }
    if(time==5) 
    {
        return 0;
    }
    return 1;
}

void user_change_password(MYSQL *mysql)
{
   char record[10];char name[]="name";
   char query[100];
   
   while(1)
    {
        system("cls");
        printf("\n����������˺ŵ��û���:");
        scanf("%s",&record);
        if(!check_user(mysql,name,record))
        { 
            MessageBox(NULL,"�û���������.","Tip",MB_OK);
            return;
        }
        break;
    }
    user temp1,temp2;
    user user=information_return(mysql,record,1);
    if(check_password(user)) 
    {
        while(1)
        {
            
            
            while(1)
            {   
            printf("\n������������:");
            enter(temp1.password);
            if(!strcmp(temp1.password,user.password))
            {
                MessageBox(NULL,"��������ԭ��������ͬ.","Tip",MB_OK);
                continue;
            }
            if(!secure(temp1.password))
            {
                continue;
            }
            break;
            }
            printf("\n��ȷ������:");
            enter(temp2.password);
            if(strcmp(temp1.password,temp2.password)) 
            {
                MessageBox(NULL,"�������벻һ��.","Tip",MB_OK);
                continue;
            }
            break;
        }
        sprintf(query,"\nUPDATE a SET password='%s' WHERE name='%s'",temp1.password,record);
        mysql_query(mysql,query);
    }
    else
    {
        MessageBox(NULL,"���Ѵﵽ����Դ���.","Tip",MB_OK);
    } 
}

void user_retrieve_password(MYSQL *mysql)
{
    user temp;char name[]="name";
    user user;
    while(1)
    {
        system("cls");
        printf("\n�����������˺ŵ��û���:");
        scanf("%s",&temp.name);
        if(!check_user(mysql,name,temp.name))
        { 
            MessageBox(NULL,"�û���������.","Tip",MB_OK);
            return;
        }
        break;
    }
    user=information_return(mysql,temp.name,1);
    printf("����:%s\n�������:",user.question);
    scanf("%s",&temp.answer);
    remove_spaces(user.answer);
    remove_spaces(temp.answer);
    if(strcmp(user.answer,temp.answer))
    {
        MessageBox(NULL,"�𰸴���.","Tip",MB_OK);
        return;
    }
    else
    {
        printf("��������� %s .",user.password);
        while(getchar()!='\n');
        getchar();
    }
    
}

void user_exit()
{
    printf("��л����֧��!");
    exit(0);
}

void admi_start()
{
    system("cls");
    printf("\n\n\t\t\tWelcome to join the administrator system!");
    Sleep(2000);
}

void admi_menu()
{
    system("cls");
	printf("\n		*********************      ����Ա�˵�     **********************\n");  
    printf("\t\t*\t                                                       *\n");
	printf("\t\t*\t      1.�鿴�û���Ϣ                                   *\n");
    printf("\t\t*\t                                                       *\n");
    printf("\t\t*\t      2.�޸Ĺ���Ա�˺�                                 *\n");
    printf("\t\t*\t                                                       *\n");
	printf("\t\t*\t      3.�˳�����Աϵͳ                                 *\n");
    printf("\t\t*\t                                                       *\n");
	printf("		***************************************************************\n");
	printf("\n");
}

int select(int a,int b)
{
    int select;
    printf("\t\t\t\t����ѡ��: [\t].\b\b\b\b");
    
        while(scanf("%d",&select)!=1||!check_select(select,a,b))
        {
            MessageBox(NULL,"��������Ч����.","Tip",MB_OK);
            printf("\x1b[1A\x1b[2K");
            while(getchar()!='\n');
            printf("\t\t\t\t����ѡ��: [\t].\b\b\b\b");
        }
    return select;
    
}

int check_select(int select,int a,int b)
{
    if(select<a||select>b) return 0;
    else return 1;
}

void switch_select(int select,MYSQL *mysql)
{
    switch (select)
    {
    case 1:check_user_information(mysql);break;
    case 2:modify_administrator_account(mysql);break;
    case 3:exit_the_system();break;
    }
}

void exit_the_system()
{
    b_a();
}

void check_user_information(MYSQL *mysql)
{
    b_c();
    while(function3)
    {
        check_user_information_screen();
        int admi_select=select(1,6);
        check_user_switch_select(admi_select,mysql);
    }
}

void check_user_information_screen()
{
    system("cls");
    printf("\n		*************************** Menu ******************************\n");
    printf("\t\t*\t                                                       *\n");         
	printf("\t\t*\t      1.�鿴�û���Ϣ                                   *\n");         
    printf("\t\t*\t      2.�����û���Ϣ                                   *\n");         
    printf("\t\t*\t      3.ɾ���û���Ϣ                                   *\n");         
	printf("\t\t*\t      4.�޸��û�Ȩ��                                   *\n");
    printf("\t\t*\t      5.����û���Ϣ                                   *\n");
    printf("\t\t*\t      6.������һҳ                                     *\n");         
    printf("\t\t*\t                                                       *\n");         
	printf("		***************************************************************\n");
	printf("\n");
}

void check_user_switch_select(int select,MYSQL *mysql)
{
    switch (select)
    {
    case 1:admi_view(mysql);break;
    case 2:admi_find(mysql);break;
    case 3:admi_delete(mysql);break;
    case 4:admi_modify(mysql);break;
    case 5:admi_clear(mysql);break;
    case 6:c_b();
    }
}



void exit_mysql(MYSQL *mysql)
{
    mysql_close(mysql);
}

void admi_view(MYSQL *mysql)
{
    char choice;
    while(getchar()!='\n');
    mysql_query(mysql,"select * from A");
    MYSQL_RES *result=mysql_store_result(mysql);
    admi_list(result);
    printf("\n����y�������, ����n������һҳ:[  ]\b\b\b");
    scanf("%c",&choice);
    system("cls");
    if(choice=='y') admi_load(mysql);
}

void admi_find(MYSQL *mysql)
{
    system("cls");
    char query[100];char name[]="name";
    char find_key[20];
    printf("\n��������Ҫ���ҵ��û���:");
    printf("ģ����ѯʾ����%��%");
    scanf("%s",&find_key);
    sprintf(query,"select * from A where name like '%s'",find_key);
    mysql_query(mysql,query);
    MYSQL_RES *result=mysql_store_result(mysql);
    admi_list(result);
    while(getchar()!='\n');
    printf("\n����س�������һҳ��");
    getchar();
}

void admi_list(MYSQL_RES *result)
{
    user User;int i=1;
    MYSQL_ROW row;
    system("cls");
    printf("\n\t\t+----------------------------+");
    while(row=mysql_fetch_row(result))                                  
    {                                                       
        strcpy(User.account,row[1]);                            
        strcpy(User.name,row[0]);                                   
        User.status=atoi(row[5]);                               
        printf("\n\t\t|%-2d|%-10s|%-10s|%-4d|\n",i++,User.account,User.name,User.status);
    }                                                                   
    printf("\n\t\t+----------------------------+");
    mysql_free_result(result);    
}

void admi_load(MYSQL *mysql)
{
    #define STDOUT 1
    int oldstdout = dup(STDOUT); 
    mysql_query(mysql,"select * from A");
    MYSQL_RES *result=mysql_store_result(mysql);
    FILE *p=fopen("../result.txt","w");
    freopen("../result.txt", "w", stdout);
    admi_list(result);
    fflush(stdout);
    fclose(p);
    freopen("CONOUT$", "w", stdout);
    dup2(oldstdout,STDOUT); 
}

void admi_delete(MYSQL *mysql)
{
    char query[100];char i[]="name";
    char name[20];
    char choice;
    system("cls");
    printf("��������Ҫɾ�����˺ŵ��û���:");
    scanf("%s",&name);
    if(!check_user(mysql,i,name)) {MessageBox(NULL,"���û���������.","Tip",MB_OK);return;return;};
    mysql_query(mysql,"START TRANSACTION");
    sprintf(query,"delete from A where name='%s'",name);
    mysql_query(mysql,query);
    printf("\n����yȷ��ɾ��,����n����ɾ��.");
    printf("�������뿼��ʱ��.");
    Sleep(3000);
    do
    {
        printf("����ѡ��('y'or'n'):");
        while (getchar() != '\n');
        choice=getchar();
    } while (choice!='y'&&choice!='n');
    if(choice=='y') {printf("�ɹ�ɾ��.");mysql_query(mysql,"commit");}
    else delete_rollback(mysql);
}

void delete_rollback(MYSQL *mysql)
{
    mysql_query(mysql,"rollback");
    printf("�ɹ�����ɾ��.");
    Sleep(500);
}

void modify_administrator_account(MYSQL *mysql)
{
    create_admi(mysql);
}

void admi_clear(MYSQL *mysql)
{
    int a = MessageBox(NULL, "��������,�޷��ָ�.", "Tip", MB_OKCANCEL | MB_ICONASTERISK);
    if (a == IDYES) {
        mysql_query(mysql, "truncate a");
    }
}

void admi_modify(MYSQL *mysql)
{
    char username[20];
    int status;char name[]="name";
    char query[100];
    system("cls");
    printf("����������Ҫ�޸ĵ��û���:");
    scanf("%s",&username);
    if(!check_user(mysql,name,username)) printf("The user does not exist.");
    printf("������Ȩ��ѡ��(0 ����ɷ���, 1 �������)");
    scanf("%d",&status);
    sprintf(query,"UPDATE a SET status=%d WHERE name='%s'",status,username);
    mysql_query(mysql,query);
}

int check_user(MYSQL *mysql,char *m,char *find_key)
{
    char query[100];
    sprintf(query,"select * from A where %s = '%s'",m,find_key);
    mysql_query(mysql,query);
    MYSQL_RES *result=mysql_store_result(mysql);
    if (result!=NULL)
    {
        int num_rows = mysql_num_rows(result);
        mysql_free_result(result);
        return (num_rows > 0);
    }
    else return 0;
}

int secure(char *password)
{
    int length=strlen(password);
    int up=0,low=0,spe=0,dig=0;
    for(int i=0;i<length;i++)
    {
        if (password[i] >= 'A' && password[i] <= 'Z') {
            up=1;
        } else if (password[i] >= 'a' && password[i] <= 'z') {
            low=1;
        } else if (password[i] >= '0' && password[i] <= '9') {
            dig=1;
        } else {
            spe=1;
        }
    }
    if(up+low+spe+dig>=2&&length>=6) return 1;
    else 
    {
    MessageBox(NULL,"���밲ȫϵ����!","Tip",MB_OK|MB_ICONEXCLAMATION);
    return 0;
    }
}

void enter(char *m)
{
    int i = 0;
    while (i < 20) {
        char c = getch();

        if (c == '\r') {
            break;
        } else if (c == '\b') {
            if (i > 0) {
                i--;
                printf("\b \b"); // ���˸������֮ǰ������
            }
        } else if (i < 19) {
            m[i++] = c;
            printf("*");
        }
    }
    m[i] = '\0';
}

void remove_spaces(char* str) 
{
    int count = 0;
    for (int i = 0; str[i]; i++) 
    {
        if (str[i] != ' ') str[count++] = str[i];
    }
    str[count] = '\0';
}

void admi(MYSQL *mysql)
{    
    admi_start();
    a_b();
    while(function2)
    {  
        admi_menu();
        switch_select(select(1,3),mysql);
    }
}

void game(user user,MYSQL *mysql)
{
    c_d();
    while(function4)
    {  
        board();
        switch_game(select(1,8),user,mysql);
    }
    
}
void board()
{
    system("cls");
    printf("\n		*************************** Menu ******************************\n");
    printf("\t\t*\t                                                       *\n");         
	printf("\t\t*\t      1.��������                                       *\n");         
    printf("\t\t*\t      2.̰����                                         *\n");         
    printf("\t\t*\t      3.�ɻ���ս                                       *\n");
    printf("\t\t*\t      4.������                                         *\n");
    printf("\t\t*\t      5.������(˫��)                                   *\n");         
	printf("\t\t*\t      6.ɨ��                                           *\n");
    printf("\t\t*\t      7.������                                         *\n");
    printf("\t\t*\t      8.������һҳ��                                   *\n");         
    printf("\t\t*\t                                                       *\n");         
	printf("		***************************************************************\n");
	printf("\n");
}
void switch_game(int select,user user,MYSQL *mysql)
{
    switch (select)
    {
    case 1:enter_alien();break;
    case 2:enter_snake();break;
    case 4:enter_table();break;
    case 6:enter_sweep();break;
    case 3:enter_pg(user);break;
    case 7:engine_chat(mysql,user);break;
    case 8:d_c();
    case 5:two(mysql);
    }
}
void enter_alien()
{
    char path[] = "bin\\dist\\alien_invasion.exe"; 
    system(path);
}
void enter_snake()
{
    char path[100];
    sprintf(path, "powershell -Command \"Start-Process 'bin\\Project4.exe' -Verb RunAs\"");
    system(path);
}
void enter_table()
{
    system("cls");
    char path[] = "bin\\main.exe"; 
    system(path);
}
void enter_sweep()
{
    system("cls");
    char path[] = "bin\\minesweeping.exe"; 
    int result = system(path);
}
void enter_pg(user user)
{
    char path[100];
    sprintf(path,"bin\\pg.exe %s",user.name);
    system(path);
}




void engine_chat(MYSQL *mysql,user user)
{
    chat temp;
    temp.status=user.status;
    strcpy(temp.name,user.name);
    MessageBox(NULL,"����س����ɿ�ʼ������Ϣ.","Tip",MB_OK);
    while(getchar()!='\n');
    int status=1;int i=0;
    system("cls");
    while(status)
    {
        show_chatting(mysql,&i);
        printf("\x1b[1A\x1b[2K");
        printf("������Ϣ(����q�˳�):\n");
        fgets(temp.message,sizeof(temp.message),stdin);
        if (strcmp(temp.message, "q\n") == 0) break;
        upload_message(mysql, temp,&i);

    }
}
void show_chatting(MYSQL *mysql,int *i)
{
    chat chat;
    user user;    
    char user_input[100];
    mysql_query(mysql,"select * from chatting");
        MYSQL_RES *result=mysql_store_result(mysql);
        MYSQL_ROW row;

        while(row=mysql_fetch_row(result))
        {
        strcpy(chat.time, row[0]);
        strcpy(chat.name, row[1]);
        strcpy(chat.message, row[2]);
        (*i)++;
        printf("\n\t\t\t\t\t\t%-10s\n%-10s:%s",chat.time,chat.name,chat.message);
        }
    while (1) 
    {
        if (get_user_input(user_input, sizeof(user_input))) {
            if (strcmp(user_input, "\n") == 0 || strcmp(user_input, "Q\n") == 0) {
                break;  
            }
        }
        char query[100];
        sprintf(query,"select * from chatting LIMIT 999999 OFFSET %d",*i);
        mysql_query(mysql,query);
        MYSQL_RES *result=mysql_store_result(mysql);
        MYSQL_ROW row;
        while(row=mysql_fetch_row(result))
        {
        strcpy(chat.time, row[0]);
        strcpy(chat.name, row[1]);
        strcpy(chat.message, row[2]);
        (*i)++;
        printf("\n\t\t\t\t\t\t%-10s\n%-10s:%s",chat.time,chat.name,chat.message);



    char path[] = "5.mp3";
    system(path);
    Sleep(1000);
    // ��ȡ��ǰ����ھ��
    HWND hwnd = GetForegroundWindow();

    // ��С������
    ShowWindow(hwnd, SW_MINIMIZE);

        
        }
        Sleep(1000);
    }
}

void upload_message(MYSQL *mysql,chat chat,int *i)
{
    char query[100];
    if(chat.message[0]=='\n') return;
    time_t current_time;
    time(&current_time);
    if(chat.status!=1)
    {
    strcpy(chat.time, ctime(&current_time));
    sprintf(query,"INSERT INTO chatting (time, name , message) VALUES ('%s', '%s', '%s')",chat.time,chat.name,chat.message);
    mysql_query(mysql,query);
    char query1[100];
        sprintf(query1,"select * from chatting LIMIT 999999 OFFSET %d",*i);
        mysql_query(mysql,query1);
        MYSQL_RES *result=mysql_store_result(mysql);
        MYSQL_ROW row;
        while(row=mysql_fetch_row(result))
        {
        strcpy(chat.time, row[0]);
        strcpy(chat.name, row[1]);
        strcpy(chat.message, row[2]);
        (*i)++;
        printf("\n\t\t\t\t\t\t%-10s\n%-10s:%s",chat.time,chat.name,chat.message);
        }
    }
    if(chat.status==1)
    {
    MessageBox(NULL,"���ѱ�����.","Tip",MB_OK);
    }
}

#define ROW 3
#define COL 3

char ret = 0;
void nenu();
void game_(MYSQL *mysql);
void innitiaboard(char board[ROW][COL], int row, int col);
void displayboard(char board[ROW][COL], int row, int col);
void computermove1(char board[ROW][COL], int row, int col,MYSQL *mysql);
void computermove2(char board[ROW][COL], int row, int col,MYSQL *mysql);
void playmove1(char board[ROW][COL], int row, int col,MYSQL *mysql);
void playmove2(char board[ROW][COL], int row, int col,MYSQL *mysql);
int iswin(char board[ROW][COL], int row, int col);
int isfull(char board[ROW][COL], int row, int col);

void nenu()
{
system("cls");
printf("|----------------------|\n");
printf("| 1.play |\n");
printf("| 0.exit |\n");
printf("|----------------------|\n");
printf("������:>\n");
}
void innitiaboard(char board[ROW][COL],int row, int col)
{
	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < col; j++)
		{
			board[i][j] = ' ';
		}
	}
}
void displayboard(char board[ROW][COL], int  row, int col)
{
	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < col; j++)
		{
			printf(" %c ", board[i][j]);
			if (j < row - 1)
				printf("|");
		}
		printf("\n");
		for (int j = 0; j < col; j++)
		{
			printf("---");
			if (j < col - 1)
				printf("|");
		}
		printf("\n");
	}
}

void playmove1(char board[ROW][COL], int row, int col,MYSQL* mysql)
{
int x,y;
while (1)
{
    printf("\n������x����");
    scanf("%d",&x);
    printf("\n������y����");
    scanf("%d",&y);
    if (x >= 1 && x <= row && y >= 1 && y <= col)
		{
			if (board[x - 1][y - 1] ==' ')
				{board[x - 1][y - 1] = '*';
				break;}
		}

	printf("\n������Ч");
}
char query[100];
sprintf(query,"INSERT INTO chess_a (x,y) VALUES ('%d', '%d')",x,y);
mysql_query(mysql,query);
}
void playmove2(char board[ROW][COL], int row, int col,MYSQL* mysql)
{
int x,y;

while (1)
{
    printf("\n������x����");
    scanf("%d",&x);
    printf("\n������y����");
    scanf("%d",&y);
    if (x >= 1 && x <= row && y >= 1 && y <= col)
		{
			if (board[x - 1][y - 1] == ' ')
				{board[x - 1][y - 1] = '*';
				break;}
		}
			printf("\n������Ч");
}
char query[100];
sprintf(query,"INSERT INTO chess_b (x,y) VALUES ('%d', '%d')",x,y);
mysql_query(mysql,query);
}
void computermove1(char board[ROW][COL], int row, int col,MYSQL *mysql)
{
int x, y;
while (1)
{
	char query[100];    
    while(1)
    {
    mysql_query(mysql,"select * from chess_b");
    MYSQL_RES *result=mysql_store_result(mysql);
    if (result!=NULL)
        {
            int num_rows = mysql_num_rows(result);
            mysql_free_result(result);
            if (num_rows > 0) break;
        }
    } 
       
	mysql_query(mysql,"select * from chess_b");
	MYSQL_RES *result=mysql_store_result(mysql);
	MYSQL_ROW row;    
    while(row=mysql_fetch_row(result))
	{
    x=atoi(row[1]);
	y=atoi(row[2]);
	}
	mysql_query(mysql,"TRUNCATE TABLE chess_b");
	if (board[x-1][y-1] == ' ')
	{
		board[x-1][y-1] = '#';
		break;
	}
}
}

void computermove2(char board[ROW][COL], int row, int col,MYSQL *mysql)
{
int x, y;
while (1)
{
	char query[100];    
    while(1)
    {
    mysql_query(mysql,"select * from chess_a");
    MYSQL_RES *result=mysql_store_result(mysql);
    if (result!=NULL)
        {
            int num_rows = mysql_num_rows(result);
            mysql_free_result(result);
            if (num_rows > 0) break;
        }
    } 
       
	mysql_query(mysql,"select * from chess_a");
	MYSQL_RES *result=mysql_store_result(mysql);
	MYSQL_ROW row;    
    while(row=mysql_fetch_row(result))
	{
    x=atoi(row[1]);
	y=atoi(row[2]);
	}
	mysql_query(mysql,"TRUNCATE TABLE chess_a");
	if (board[x-1][y-1] == ' ')
	{
		board[x-1][y-1] = '#';
		break;
	}
}
}
int isfull(char board[ROW][COL], int row, int col)
{
	for (int i = 0; i < ROW; i++)
	{
		for (int j = 0; j < COL; j++)
		{
			if (board[ROW][COL] == ' ');
			return 0;
		}
	}
	return 1;
}
 
int iswin(char board[ROW][COL], int row, int col)
{
	for (int i = 0; i < ROW; i++)
	{
		//����
		if (board[i][0] == board[i][1]&& board[i][1]== board[i][2] && board[i][0] =='*')
			return '*';
	}
	//��
	for (int j = 0; j < COL; j++)
	{
		if (board[0][j] == board[1][j]&& board[1][j]== board[2][j] && board[0][j] =='#')
			return '#';
	}
	//�Խ���
	if (board[0][0] == board[1][1] && board[1][1] == board[2][2] && board[0][0] != ' ')
		return board[0][0];
	if (board[0][2] == board[1][1] && board[1][1] == board[2][0] && board[0][2] != ' ')
		return board[0][2];
	//�ж���
	if (isfull(board, row, col))
	{
		return 'Q';
	}
	return 'C';
}

int check(MYSQL* mysql)
{
mysql_query(mysql,"select * from chess_a");
while(1)
{
MYSQL_RES *result=mysql_store_result(mysql);
if (result!=NULL)
{
int num_rows = mysql_num_rows(result);
mysql_free_result(result);
return (num_rows > 1);
}
}
}

void game_(MYSQL* mysql)
{

char board[ROW][COL];
mysql_query(mysql,"INSERT INTO chess_a (x, y) VALUES (9,9) ");
printf("ƥ����");
while(!check(mysql));
system("cls");
printf("��Ϸ������ʼ");
Sleep(1000);
mysql_query(mysql,"TRUNCATE TABLE chess_a");
system("cls");
innitiaboard(board, ROW, COL);//��ʼ������
displayboard(board, ROW, COL);//��ӡ��ʼ����
int module;
printf("������ѡ��(1����,2����)");
scanf("%d",&module);
if(module==1)
{
    while(1)
{
	playmove1(board, ROW, COL,mysql);//�����?
	displayboard(board, ROW, COL);
	ret = iswin(board, ROW, COL);
	if (ret != 'C')//�г����?
		break;
    if(isfull)
    break;
	computermove1(board, ROW, COL,mysql);
	displayboard(board, ROW, COL);
	ret = iswin(board, ROW, COL);
	if (ret != 'C')
		break;
    if(isfull)
    break;
}
	if (ret == '*')
		printf("���Ӯn");
	else if (ret == '#')
		printf("����Ӯ\n");
	else
		printf("ƽ��\n");
	Sleep(1000);
	mysql_query(mysql,"truncate table chess_a");
	mysql_query(mysql,"truncate table chess_b");
}

if(module==2)
{
while(1)
{
	computermove2(board, ROW, COL,mysql);
	displayboard(board, ROW, COL);
	ret = iswin(board, ROW, COL);
	if (ret != 'C')//�г����?
		break;
    if(isfull)
    break;
	playmove2(board, ROW, COL,mysql);//�����?
	displayboard(board, ROW, COL);
	ret = iswin(board, ROW, COL);
	if (ret != 'C')
		break;
    if(isfull)
    break;
}
	if (ret == '*')
		printf("���Ӯn");
	else if (ret == '#')
		printf("����Ӯ\n");
	else
		printf("ƽ��\n");
	Sleep(1000);
	mysql_query(mysql,"truncate table chess_a");
	mysql_query(mysql,"truncate table chess_b");
}


}

void two(MYSQL *mysql)
{
system("cls");
int input = 0;
srand((unsigned int)time(NULL));

do
{
	system("cls");
	nenu();
	scanf("%d",&input);
	switch (input)
	{
	case 1:
		system("cls");
		game_(mysql);
		break;
	case 0:
		break;
	default:
		printf("ѡ����Ч");
		break;
	}
} while (input);
return ;
}
int main()
{
MYSQL *mysql=log_in_mysql();
user_start();    
while(!check_admi(mysql)) create_admi(mysql);
while(function1)
{
    user_menu();
    user_switch_select(select(1,6),mysql);
}
exit_mysql(mysql);

}