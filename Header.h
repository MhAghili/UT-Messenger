#pragma once
typedef struct Date Date;
typedef struct userMessage userMessage;
typedef struct user user;
typedef enum
{
	GREEN = 2, RED = 4, WHITE = 7

} ConsoleColors;
typedef HANDLE Handle;
typedef CONSOLE_SCREEN_BUFFER_INFO BufferInfo;
typedef WORD Word;
short setTextColor(const ConsoleColors foreground);
void signup(user*head, userMessage*headm);
void addtouserlist(user*head, user*new);
void checkformat(user*head, user*new, int*flag);
void checkformat2(user*head, user*new, int*flag);
void login(user*head, userMessage*headm);
void plogin(user*head, user*cur, userMessage*headm);
void Info(user*head);
void About(user*head);
void editun(user*head);
void editpass(user*head);
void sendmass(user*head, user*cur, userMessage*headm);
void addtomesslist(userMessage*headm, userMessage*new);
void showsent(user*cur, userMessage*headm);
void showreceive(user*cur, userMessage*headm);
void savedata(user*head, userMessage*headm);
void readdata(user*head, userMessage*headm);
void add_to_mess_list_from_file(userMessage*headm, userMessage*new);
void add_to_userlist_from_file(user*head, user*new);
struct userMessage
{
	char* content;
	char* sender;
	char* receiver;
	char*date;
	int status;
	userMessage* next;
};
struct user
{
	char* un;
	char* pass;
	char* num;
	char*date;
	user* next;
};
