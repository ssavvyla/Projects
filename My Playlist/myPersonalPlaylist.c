#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
int flag=0;
int loop;
struct Song{
	char songName[50];
	char singer[50];
	char genre[50];
};
struct myPlaylist{
	struct Song song;
	struct myPlaylist *next;
	struct myPlaylist *prev;
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
	if(head==NULL)
	{
		printf("\nEmpty Playlist\n");
	}
	while(temp!=NULL)
	{
		printf("\n%s : %s : %s \n",temp->song.songName,temp->song.singer,temp->song.genre);
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
		if(loop==1)
		{
			while(temp->next!=NULL)
			temp=temp->next;
		}
		else
		{
			printf("\nEnd of Playlist\n");
		}
	}
	*current=temp;
}
void playNext(struct myPlaylist **current,struct myPlaylist *head)
{
	struct myPlaylist *temp=*current;
	if(loop==1 && temp->next==NULL)
	{
		*current=head;
	}
	else if(loop==0 && temp->next==NULL)
	{
		printf("\nEnd of Playlist\n");
		return;
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
void displayCurrent(struct myPlaylist *current)
{
	printf("\n%s : %s : %s \n",current->song.songName,current->song.singer,current->song.genre);

}
void deleteSong(struct myPlaylist **head,char *Name)
{
	struct myPlaylist *temp=*head,*ptr1,*ptr2;		
	if(head!=NULL)
	{
		if(temp->next==NULL && strcmp(temp->song.songName,Name)==0)
		{
			printf("\nSong Deleted:-\n\n");
			printf("%s : %s : %s \n",temp->song.songName,temp->song.singer,temp->song.genre);
			*head=NULL;
			flag=0;
			return;
		}
		while(temp!=NULL)
		{
			if(strcmp(temp->song.songName,Name)==0)
			{
				printf("\nSong Deleted:-\n\n");
				printf("%s : %s : %s \n",temp->song.songName,temp->song.singer,temp->song.genre);
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
		if(temp==NULL)
		{
			printf("\nSong Not Found\n");
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
				printf("\n%s : %s : %s \n",temp->song.songName,temp->song.singer,temp->song.genre);
				break;
			}
			temp=temp->next;
		}
		if(temp==NULL)
		{
			printf("\nSong Not Found\n");
		}
	}
}
void shuffleSong(struct myPlaylist *head,int pos1,int pos2)
{
	struct myPlaylist *temp=head,*ptr;
	int count=0;
	char Name[50],singer[50],genre[50];
	if(pos1==0 || pos2==0)
	{
		printf("\nEnter valid positions\n");
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

					printf("\nShuffled Successfully\n");
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
					printf("\nShuffled Successfully\n");
					break;
				}
			}
			temp=temp->next;
		}
		if(temp==NULL)
		{
			printf("\nEnter valid Positions\n");
		}
	}
	else
	{
		printf("\nEmpty Playlist\n");
	}
}
int main()
{
	int ch,pos1,pos2;
	char Name[50],singer[50],genre[50];
	struct myPlaylist *head=NULL,*current;
	fflush(stdin);
	printf("\nPress 1 to loop and 0 otherwise: ");
	scanf("%d",&loop);
	if(loop!=0 || loop!=1 || isalpha(loop))
	{
		system("cls");
		main();
	}
	while(1)
	{
		system("cls");
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
		fflush(stdin);
		scanf("%d",&ch);		
		if(ch>0 && ch<10)
		{
			switch(ch)
			{
				case 1:{
					fflush(stdin);
					printf("\nEnter Song: ");
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
						printf("\nEnter Song: ");
						fgets(Name,sizeof(Name),stdin);
						deleteSong(&head,Name);
					}
					else
					{
						printf("\nEmpty Playlist\n");						
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
						if(current->next!=NULL || loop==1)
						{
							displayCurrent(current);
						}
					}
					else
					{
						printf("\nEmpty Playlist\n");
					}
					break;
				}
				case 5:{
					if(head!=NULL)
					{
						playPrev(&current);
						if(current->prev!=NULL || loop==1)
						{
							displayCurrent(current);
						}
					}
					else
					{
						printf("\nEmpty Playlist\n");
					}
					break;
				}
				case 6:{
					if(head!=NULL)
					{
						fflush(stdin);
						printf("\nEnter Song: ");
						fgets(Name,sizeof(Name),stdin);
						playParticular(head,&current,Name);
					}
					else
					{
						printf("\nEmpty Playlist\n");
					}
					break;
				}
				case 7:{
					if(head!=NULL)
					{
						playFirst(&current,head);
						displayCurrent(current);
					}
					else
					{
						printf("\nEmpty Playlist\n");
					}			
					break;
				}
				case 8:{
					if(head!=NULL)
					{
						printf("\nEnter Positions: ");
						scanf("%d %d",&pos1,&pos2);
						shuffleSong(head,pos1,pos2);
					}
					else
					{
						printf("\nEmpty Playlist\n");
					}	
					break;
				}
				case 9:{
					exit(0);
					break;
				}
			}
		}
		else
		{
			printf("\nEnter a Number between 1-9\n");
		}
		getch();
	}
	return 0;
}
