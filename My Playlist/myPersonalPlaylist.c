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
		printf("%s : %s : %s \n",temp->song.songName,temp->song.singer,temp->song.genre);
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
	printf("\n%s : %s : %s \n",current->song.songName,current->song.singer,current->song.genre);

}
void shuffleSong(struct myPlaylist *head,int pos1,int pos2)
{
	struct myPlaylist *temp=head,*ptr;
	int count=0;
	char Name[50],singer[50],genre[50];
	if(pos1==0 || pos2==0)
	{
		return;
	}
	if(head!=NULL)
	{
		while(temp!=NULL)
		{
			count++;
			if(pos1<pos2)
			{
				if(pos1==count)
				{
					ptr=temp;
				}
				if(pos2==count)
				{
					strcpy(Name,ptr->song.songName);
					strcpy(singer,ptr->song.singer);
					strcpy(genre,ptr->song.genre);
					strcpy(ptr->song.songName,temp->song.songName);
					strcpy(ptr->song.singer,temp->song.singer);
					strcpy(ptr->song.genre,temp->song.genre);
					strcpy(temp->song.songName,Name);
					strcpy(temp->song.singer,singer);
					strcpy(temp->song.genre,genre);
					break;
				}
			}
			else
			{
				if(pos2==count)
				{
					ptr=temp;
				}
				if(pos1==count)
				{
					strcpy(Name,ptr->song.songName);
					strcpy(singer,ptr->song.singer);
					strcpy(genre,ptr->song.genre);
					strcpy(ptr->song.songName,temp->song.songName);
					strcpy(ptr->song.singer,temp->song.singer);
					strcpy(ptr->song.genre,temp->song.genre);
					strcpy(temp->song.songName,Name);
					strcpy(temp->song.singer,singer);
					strcpy(temp->song.genre,genre);
					break;
				}
			}
			temp=temp->next;
		}
	}
}
int main()
{
	int ch,pos1,pos2;
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
				fflush(stdin);
				printf("Enter Song: ");
				fgets(Name,sizeof(Name),stdin);
				fflush(stdin);
				printf("Enter Singer: ");
				fgets(singer,sizeof(singer),stdin);
				fflush(stdin);
				printf("Enter Genre: ");
				fgets(genre,sizeof(genre),stdin);
				insertSong(&head,Name,singer,genre);
				if(flag==0)
				{
					current=head;
					flag=1;
				}
				break;
			}
			case 2:{
				if(head!=NULL)
				{
					fflush(stdin);
					printf("Enter Song: ");
					fgets(Name,sizeof(Name),stdin);
					deleteSong(&head,Name);
				}
				break;
			}
			case 3:{
				display(head);
				break;
			}
			case 4:{
				if(head!=NULL)
				{
					playNext(&current,head);
					displayCurrent(current);
				}
				break;
			}
			case 5:{
				if(head!=NULL)
				{
					playPrev(&current);
					displayCurrent(current);
				}
				break;
			}
			case 6:{
				if(head!=NULL)
				{
					fflush(stdin);
					printf("Enter Song: ");
					fgets(Name,sizeof(Name),stdin);
					playParticular(head,&current,Name);
					displayCurrent(current);
				}
				break;
			}
			case 7:{
				if(head!=NULL)
				{
					playFirst(&current,head);
					displayCurrent(current);
				}				
				break;
			}
			case 8:{
				printf("Enter Positions: ");
				scanf("%d %d",&pos1,&pos2);
				shuffleSong(head,pos1,pos2);
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
