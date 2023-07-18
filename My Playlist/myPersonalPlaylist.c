#include<stdio.h>
#include<stdlib.h>
#include<string.h>
int flag=0;
struct Song{
	char songName[50];
	char singer[50];
	char genre[50];
};
struct myPlaylist{
	struct Song song;
	struct myPlayist *next;
	struct myPlayist *prev;
};
void insertSong(struct myPlaylist **head,char Name[50],char singer[50],char genre[50])
{
	struct myPlaylist *temp=*head;
	struct myPlaylist *node=(struct myPlaylist*)malloc(sizeof(struct myPlaylist));
	strcpy(node->song.songName,Name);
	strcpy(node->song.singer,singer);
	strcpy(node->song.genre,genre);
	
	node->next=NULL;
	node->prev=NULL;
	if(*head==NULL)
	{
		*head=node;
	}
	else
	{
		while(temp->next!=NULL)
		{
			temp=temp->next;
		}
		temp->next=node;
		node->prev=temp;
	}
}
void display(struct myPlaylist *head)
{
	struct myPlaylist *temp=head;
	while(temp!=NULL)
	{
		printf("%s { %s, %s }\n",temp->song.songName,temp->song.singer,temp->song.genre);
		temp=temp->next;
	}
}
void playPrev(struct myPlaylist **current)
{
	struct myPlaylist *temp=*current;
	if(temp->prev!=NULL)
	{
		temp=temp->prev;
	}
	else
	{
		while(temp->next!=NULL)
		temp=temp->next;
	}
	*current=temp;
}
void playNext(struct myPlaylist **current,struct myPlaylist *head)
{
	struct myPlaylist *temp=*current;
	if(temp->next==NULL)
	{
		*current=head;
	}
	else
	{
		temp=temp->next;
		*current=temp;
	}
}
void playFirst(struct myPlaylist **current,struct myPlaylist *head)
{
	*current=head;
}
void deleteSong(struct myPlaylist **head,char *Name)
{
	struct myPlaylist *temp=*head,*ptr1,*ptr2;		
	if(head!=NULL)
	{
		if(temp->next==NULL && strcmp(temp->song.songName,Name)==0)
		{
			*head=NULL;
			flag=0;
			return;
		}
		while(temp!=NULL)
		{
			if(strcmp(temp->song.songName,Name)==0)
			{
				if(temp->next==NULL)
				{
					ptr1=temp->prev;
					ptr1->next=NULL;
					temp->prev=NULL;
					free(temp);
				}
				else if(temp->prev==NULL)
				{
					ptr2=temp->next;
					ptr2->prev=NULL;
					*head=ptr2;
					temp->next=NULL;
					free(temp);
				}
				else
				{
					ptr1=temp->prev;
					ptr2=temp->next;
					ptr1->next=temp->next;
					ptr2->prev=temp->prev;
					temp->next=NULL;
					temp->prev=NULL;
					free(temp);
				}
			}
			temp=temp->next;
		}
	}
}
void playParticular(struct myPlaylist *head,struct myPlaylist **current,char *Name)
{
	struct myPlaylist *temp=head;
	if(head!=NULL)
	{
		while(temp!=NULL)
		{
			if(strcmp(temp->song.songName,Name)==0)
			{
				*current=temp;
			}
			temp=temp->next;
		}
	}
}
void displayCurrent(struct myPlaylist *current)
{
	printf("\n%s { %s, %s }\n",current->song.songName,current->song.singer,current->song.genre);
}
void shuffleSong(struct myPlaylist *head,struct myPlaylist *current,int pos)
{
	struct myPlaylist *temp=head;
	int count=0;
	char Name[50],singer[50],genre[50];
	if(head!=NULL)
	{
		while(temp!=NULL)
		{
			count++;
			if(pos==count)
			{
				strcpy(Name,current->song.songName);
				strcpy(singer,current->song.singer);
				strcpy(genre,current->song.genre);
				strcpy(current->song.songName,temp->song.songName);
				strcpy(current->song.singer,temp->song.singer);
				strcpy(current->song.genre,temp->song.genre);
				strcpy(temp->song.songName,Name);
				strcpy(temp->song.singer,singer);
				strcpy(temp->song.genre,genre);
				break;
			}
			temp=temp->next;
		}
	}
}
int main()
{
	int ch,pos;
	char Name[50],singer[50],genre[50];
	struct myPlaylist *head=NULL,*current;
	while(1)
	{
		printf("\n1) Insert a New Song.\n");
		printf("2) Delete a Song.\n");
		printf("3) Display all Songs.\n");
		printf("4) Play Next Song.\n");
		printf("5) Play Previous Song.\n");
		printf("6) Play Particular Song.\n");
		printf("7) Play First Song.\n");
		printf("8) Shuffle Any Song.\n");
		printf("9) Quit.\n\n");
		printf("Enter your choice: ");
		scanf("%d",&ch);
		printf("\n");
		switch(ch)
		{
			case 1:{
				printf("Enter Song: ");
				scanf("%s",&Name);
				printf("Enter Singer: ");
				scanf("%s",&singer);
				printf("Enter Genre: ");
				scanf("%s",&genre);
				insertSong(&head,Name,singer,genre);
				if(flag==0)
				{
					current=head;
					flag=1;
				}
				break;
			}
			case 2:{
				printf("Enter Song: ");
				scanf("%s",&Name);
				deleteSong(&head,Name);
				break;
			}
			case 3:{
				display(head);
				break;
			}
			case 4:{
				playNext(&current,head);
				displayCurrent(current);
				break;
			}
			case 5:{
				playPrev(&current);
				displayCurrent(current);
				break;
			}
			case 6:{
				printf("Enter Song: ");
				scanf("%s",&Name);
				playParticular(head,&current,Name);
				displayCurrent(current);
				break;
			}
			case 7:{
				playFirst(&current,head);
				displayCurrent(current);
				break;
			}
			case 8:{
				printf("Enter Position: ");
				scanf("%d",&pos);
				shuffleSong(head,current,pos);
				break;
			}
			case 9:{
				exit(0);
				break;
			}
		}
	}
	return 0;
}
