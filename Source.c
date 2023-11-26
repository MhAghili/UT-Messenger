#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h> 
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include"header.h"
#define true 1
#define MIN_PASS_LEN 5
#define NUMBER_LEN 11
int main() {
	user*head = (user*)malloc(sizeof(user));
    head->next = NULL;
	userMessage*headm = (userMessage*)malloc(sizeof(userMessage));
	headm->next = NULL;
	char* Login = (char*)malloc(sizeof(char));
	char* Signup = (char*)malloc(sizeof(char));
	char* Close = (char*)malloc(sizeof(char));
	char* logout = (char*)malloc(sizeof(char));
	Signup = "signup";
	Login = "login";
	Close = "close";
	logout = "logout";
    readdata(head, headm);
	printf("welcome to utmessenger\n");
	while (true) {
		char*command = (char*)malloc(sizeof(char));
		scanf("%s",command);
		getchar();
		if (strcmp(command, Signup) == 0) {
			signup(head,headm);		
		}
		else if (strcmp(command,Login) == 0) {
			login(head,headm);
		}
		else if (strcmp(command, Close) == 0) {
			savedata(head, headm);
			break;
		}
		else if (strcmp(command, logout) == 0) {
			printf("you must first login\n");
		}
		else  {
			printf("You entered an incorrect command.Please try again\n");
			fseek(stdin, 0, SEEK_END);
		}
	}
	return 0;
}
void signup(user*head, userMessage*headm) {
	while (true)
	{
		int flag = 0;
		user*new = malloc(sizeof(user));
		new->un = (char*)malloc(sizeof(char));
		new->pass = (char*)malloc(sizeof(char));
		new->num = (char*)malloc(sizeof(char));
		int i = 0, j = 0, k = 0;
		while ((new->un[i] = getchar()) != ' ') 
		{
			i++;
			new->un = realloc(new->un, (i + 1) * sizeof(char));
		}
		new->un[i] = '\0';
		while ((new->pass[j] = getchar()) != ' ')
		{
			j++;
			new->pass = realloc(new->pass, (j + 1) * sizeof(char));
		}
		new->pass[j] = '\0';
		while ((new->num[k] = getchar()) != '\n')
		{
			k++;
			new->num = realloc(new->num, (k + 1) * sizeof(char));
		}
		new->num[k] = '\0';
		checkformat(head,new,&flag);
		if (flag == 1) {
			break;
		}
		checkformat2(head, new,&flag);
		if (flag == 1) {
			break;
		}
		time_t curtime = time(NULL);
		localtime(&curtime);
	    new->date = malloc(sizeof(char)*(strlen(ctime(&curtime) + 1)));
	    strcpy(new->date, ctime(&curtime));
		addtouserlist(head, new);
		plogin(head, new,headm);
		break;
	}
}
void addtouserlist(user*head, user*new) {
	user* curr = head->next;
	user* pre = head;
	while (curr != NULL)
	{
			pre = curr;
			curr = curr->next;
	}
	pre->next = new;
	new->next = NULL;
	printf("         successfully registered\n");
	return;
}
void checkformat(user*head,user*new,int*flag){
	user*now = head->next;
	while (now != NULL) {
		if (strcmp((new->num), (now->num)) == 0) {
			printf("dupplicate number\n");
			free(new);
			*flag = 1;
			break;
		}
		if (strcmp((new->un), (now->un)) == 0) {
			printf("dupplicate username\n");
			free(new);
			*flag = 1;
			break;
		}
		now = now->next;
	}
}
void checkformat2(user*head, user*new, int*flag) {
	while (true) {
		if (strlen(new->num) != NUMBER_LEN) {
			printf("wrong number\n");
			free(new);
			*flag = 1;
			break;
		}
		if (new->num[0]!= '0') {
			printf("wrong number\n");
			free(new);
			*flag = 1;
			break;
		}
		if (strlen(new->pass) <= MIN_PASS_LEN) {
			printf("false password\n");
			free(new);
			*flag = 1;
			break;
		}
		break;
	}
}
void login(user*head, userMessage*headm) {
	user*cur = head->next;
	int i=0,j=0;
	char*logun = malloc(sizeof(char));
	char*logpass = malloc(sizeof(char));
	while ((logun[i] = getchar()) != ' ')
	{
		i++;
		logun = realloc(logun, (i + 1) * sizeof(char));
	}
	logun[i] = '\0';
	while ((logpass[j] = getchar()) != '\n')
	{
		j++;
		logpass = realloc(logpass, (j + 1) * sizeof(char));
	}
	logpass[j] = '\0';
	while (cur != NULL) {
		if (strcmp(logun, (cur->un)) == 0 && strcmp(logpass, (cur->pass)) == 0) {
			printf("         successfully login\n");
			plogin(head,cur,headm);
			break;
		}
		cur = cur->next;
	}
	if(cur==NULL)
	printf("  incorrect username or password.pleas check and try again!\n");
}
void plogin(user*head,user*cur,userMessage*headm) {
	userMessage*now = headm->next;
	char* info = (char*)malloc(sizeof(char));
	char* about = (char*)malloc(sizeof(char));
	char* edit_username = (char*)malloc(sizeof(char));
	char* eidt_pass = (char*)malloc(sizeof(char));
	char* logout = (char*)malloc(sizeof(char));
	char* send = (char*)malloc(sizeof(char));
	char* show_received = (char*)malloc(sizeof(char));
	char* show_sent = (char*)malloc(sizeof(char));
	char* signup = (char*)malloc(sizeof(char));
	info = "info";
	about = "about";
	edit_username = "edit_username";
	eidt_pass = "edit_pass";
	logout = "logout";
	send = "send";
	show_sent = "show_sent";
	show_received = "show_received";
	signup = "signup";
	while(true)
	{
		while (now != NULL) {
			if (strcmp(now->receiver, cur->un) == 0) {
				if (now->status == 0) {
					setTextColor(GREEN);
					printf("          unread mesaage:\n");
					setTextColor(RED);
					printf("          message from: %s  at: %s\n", now->sender, now->date);
					setTextColor(WHITE);
					now->status = 1;
				}
			}
			now = now->next;
		}
		char*command2 = (char*)malloc(sizeof(char));
		scanf("%s", command2);
		getchar();
		if (strcmp(command2, info) == 0) {
			Info(head);
			continue;
		}
		else if (strcmp(command2, about) == 0) {
			About(head);
			continue;
		}
		else if (strcmp(command2, eidt_pass) == 0) {
			editpass(cur);
			continue;
		}
		else if (strcmp(command2, edit_username) == 0) {
			editun(cur);
			continue;
		}
		else if (strcmp(command2, logout) == 0) {
			printf("         successfully logout\n");
			break;
		}
		else if (strcmp(command2, send) == 0) {
			sendmass(head,cur,headm); 
			continue;
		}
		else if (strcmp(command2, show_sent) == 0) {
			showsent(cur, headm);
			continue;
		}
		else if (strcmp(command2, show_received) == 0) {
			showreceive(cur, headm);
			continue;
		}
		else if (strcmp(command2, signup) == 0) {
			printf("you can not sign up right now!\n");
			fseek(stdin, 0, SEEK_END);
			continue;
		}
		else {
			printf("You entered an incorrect command.Please try again\n");
			fseek(stdin, 0, SEEK_END);
		}
	}
}
void Info(user*head) {
	user*now = head->next;
	while (now != NULL)
	{
		printf("      %s\n", now->un);
		now = now->next;
	}
}
void About(user*head) {
	int i = 0;
	char*username = malloc(sizeof(char));
	user*now = head->next;
	while ((username[i] = getchar()) != '\n')
	{
		i++;
		username = realloc(username, (i + 1) * sizeof(char));
	}
	username[i] = '\0';
	while (now != NULL) {
		if (strcmp(username, (now->un)) == 0) {
			printf("      %s\n",now->un);
			printf("      registerd at: %s", now->date);
			printf("      Number: %s\n", now->num);
			break;
		}
		now = now->next;
	}
	if (now = NULL)
	printf("      user does not exist\n");
}
void editun(user*cur) {
	int i=0;
	char*newun = malloc(sizeof(char));
	while ((newun[i] = getchar()) != '\n')
	{
		i++;
		newun = realloc(newun, (i + 1) * sizeof(char));
	}
	newun[i] = '\0';
	if (strcmp(newun, cur->un) != 0) {
		cur->un = newun;
		printf("         successfully changed\n");
	}
	else
		printf("      The new username must be different from the previous one!\n");
}
void editpass(user*cur) {
	int i = 0;
	char*newpass = malloc(sizeof(char));
	while ((newpass[i] = getchar()) != '\n')
	{
		i++;
		newpass = realloc(newpass, (i + 1) * sizeof(char));
	}
	newpass[i] = '\0';
	if (strcmp(newpass, cur->pass) != 0) {
		cur->pass = newpass;
		printf("         successfully changed\n");
	}
	else
		printf("         The new password must be different from the previous one!\n");
}
void sendmass(user*head, user*cur, userMessage*headm) {
	while (true) {
		user*now = head->next;
		userMessage*new = malloc(sizeof(userMessage));
		int j = 0, k = 0;
		new->receiver = (char*)malloc(sizeof(char));
		new->content = (char*)malloc(sizeof(char));
		new->sender = (char*)malloc(sizeof(char));
		new->date = (char*)malloc(sizeof(char));
		new->sender = cur->un;
		char*username = (char*)malloc(sizeof(char));
		while ((username[j] = getchar()) != ' ')
		{
			j++;
			username = realloc(username, (j + 1) * sizeof(char));
		}
		username[j] = '\0';
		while ((new->content[k] = getchar()) != '\n')
		{
			k++;
			new->content = realloc(new->content, (k + 1) * sizeof(char));
		}
		new->content[k] = '\0';
		while (now != NULL) {
			if (strcmp((username), (now->un)) == 0) {
				new->receiver = username;
				break;
			}
			now = now->next;
		}
		if (strcmp(new->receiver, new->sender) == 0) {
			printf("       You can't send message to yourself !\n");
			free(new);
			break;
		}
		if (now == NULL) {
			printf("       user not found\n");
			free(new);
			break;
		}
		new->status = 0;
		time_t curtime=time(NULL);
		localtime(&curtime);
		new->date = malloc(sizeof(char)*(strlen(ctime(&curtime) + 1)));
		strcpy(new->date, ctime(&curtime));
		addtomesslist(headm, new);
		break;
	}
}
void addtomesslist(userMessage*headm, userMessage*new) {
	userMessage* curr = headm->next;
	userMessage* pre = headm;
	while (curr != NULL)
	{
		pre = curr;
		curr = curr->next;
	}
	pre->next = new; //nafare akhare
	new->next = NULL;
	printf("          sent\n");
	return;
}
void showsent(user*cur, userMessage*headm) {
	while (true) {
		int i = 0;
		int flag = 0;
		char*username = (char*)malloc(sizeof(char));
		while ((username[i] = getchar()) != '\n')
		{
			i++;
			username = realloc(username, (i + 1) * sizeof(char));
		}
		username[i] = '\0';
		userMessage*now = headm->next;
		while (now != NULL) {
			if (strcmp(now->sender, cur->un)==0) {
				if (strcmp(now->receiver, username) == 0) {
					printf("     Message to:%s\n      at:%s      %s\n",username, now->date, now->content);
					flag = 1;
				}
			}
			now = now->next;
		}
		if (flag == 0) {
			printf("     No Message\n");
		}
		break;
	}
}
void showreceive(user*cur, userMessage*headm) {
	while (true) {
		int i = 0;
		int flag = 0;
		char*username = (char*)malloc(sizeof(char));
		while ((username[i] = getchar()) != '\n')
		{
			i++;
			username = realloc(username, (i + 1) * sizeof(char));
		}
		username[i] = '\0';
		userMessage*now = headm->next;
		while (now != NULL) {
			if (strcmp(now->receiver, cur->un) == 0) {
				if (strcmp(now->sender, username) == 0) {
					printf("     Message from:%s\n       at:%s       %s\n", username,now->date,now->content);
					now->status = 1;
					flag = 1;
				}
			}
			now = now->next;
		}
		if (flag == 0) {
			printf("     No Message\n");
		}
		break;
	}
}
void savedata(user*head, userMessage*headm) {
	user*now = head->next;
	userMessage*cur = headm->next;
	FILE* writeuserdata = fopen("input1.txt", "w");
	while (now != NULL)
	{
		fprintf(writeuserdata, "%s ", now->un);
		fprintf(writeuserdata, "%s ", now->pass);
		fprintf(writeuserdata, "%s\n", now->num);
		//fprintf(writeuserdata, "%s", now->date);
		now = now->next;
	}
	fclose(writeuserdata);
	FILE* writemessagedata = fopen("input2.txt", "w");
	while (cur != NULL)
	{
		fprintf(writemessagedata, "%s ", cur->sender);
		fprintf(writemessagedata, "%s ", cur->receiver);
		fprintf(writemessagedata, "%s ", cur->content);
        fprintf(writemessagedata, "%d\n", cur->status);
		//fprintf(writemessagedata, "%s", cur->date);
		cur = cur->next;
	}
	fclose(writemessagedata);
}
void readdata(user*head, userMessage*headm) {
	FILE* readuserdata;
	if ((readuserdata = (FILE*)fopen("input1.txt", "r")) != NULL) {
		while (true)
		{
			user*new = malloc(sizeof(user));
			new->un = (char*)malloc(sizeof(char));
			new->pass = (char*)malloc(sizeof(char));
			new->num = (char*)malloc(sizeof(char));
			new->date = (char*)malloc(sizeof(char));
			new->date = "Unknown";
			fscanf(readuserdata, "\n%s ", new->un);
			fscanf(readuserdata, "%s", new->pass);
			fscanf(readuserdata, "%s", new->num);
			//fscanf(readuserdata, "%s\n", new->date);
            if (feof(readuserdata))
				break;
			add_to_userlist_from_file(head, new);
		}
     fclose(readuserdata);
	}
	FILE* readmessagedata;
	if ((readmessagedata = (FILE*)fopen("input2.txt", "r")) != NULL) {
		while (true)
		{
			userMessage*new = malloc(sizeof(userMessage));
			new->receiver = (char*)malloc(sizeof(char));
			new->sender = (char*)malloc(sizeof(char));
			new->content = (char*)malloc(sizeof(char));
			new->date = (char*)malloc(sizeof(char));
			new->date = "Unknown";
			fscanf(readmessagedata, "\n%s ", new->sender);
			fscanf(readmessagedata, "%s ", new->receiver);
			fscanf(readmessagedata, "%s ", new->content);
			fscanf(readmessagedata, "%d", &new->status);
			//fscanf(readmessagedata, "%s/n", new->date);
			if (feof(readmessagedata))
				break;
			add_to_mess_list_from_file(headm, new);
		}
		fclose(readmessagedata);
	}
}
void add_to_mess_list_from_file(userMessage*headm, userMessage*new) {
	userMessage* curr = headm->next;
	userMessage* pre = headm;
	while (curr != NULL)
	{
		pre = curr;
		curr = curr->next;
	}
	pre->next = new; 
	new->next = NULL;
	return;
}
void add_to_userlist_from_file(user*head, user*new) {
	user* curr = head->next;
	user* pre = head;
	while (curr != NULL)
	{
		pre = curr;
		curr = curr->next;
	}
	pre->next = new;
	new->next = NULL;
	return;
}
short setTextColor(const ConsoleColors foreground)
{
	Handle consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	BufferInfo bufferInfo;
	if (!GetConsoleScreenBufferInfo(consoleHandle, &bufferInfo))
		return 0;
	Word color = (bufferInfo.wAttributes & 0xF0) + (foreground & 0x0F);
	SetConsoleTextAttribute(consoleHandle, color);
	return 1;
}