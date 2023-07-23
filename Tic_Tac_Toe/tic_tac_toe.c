#include<stdio.h>
#include<stdlib.h>
char a[3][3];
int cp=0;
struct Player{
	char name[50];
	char mark;
};
struct Player player1,player2;
int tossF()
{
	srand(time(0));
	return rand()%2;
}
void createPlayer()
{
	printf("\nPlayer 1 Details\n");	
	printf("\nMark \'O\' | \'X\' : ");
	fflush(stdin);
	scanf("%c",&player1.mark);
	if(player1.mark=='X' || player1.mark=='O')
	{
		printf("Name: ");
		fflush(stdin);
		fgets(player1.name,50,stdin);
		printf("\nPlayer 2 Details\n");
		printf("Name: ");
		fflush(stdin);
		fgets(player2.name,50,stdin);
		if(player1.mark=='X')
		{
			player2.mark='O';
		}
		else
		{
			player2.mark='X';
		}
	}
	else
	{
		createPlayer();
	}
}
void welcome()
{
	printf("\n\t\t Game	  : TIC TAC TOE\n\n");
	printf("\t\t Player 1 : \'%c\' : %s\n",player1.mark,player1.name);
	printf("\t\t Player 2 : \'%c\' : %s\n",player2.mark,player2.name);
}

void cells()
{	
	printf("\n\t<-- TIC TAC TOE Cell Positions -->\n\n\n");
	printf("\t1\t|\t2\t|\t3\t\n");
	printf(" ---------------+---------------+---------------\n");
	printf("\t4\t|\t5\t|\t6\t\n");
	printf(" ---------------+---------------+---------------\n");
	printf("\t7\t|\t8\t|\t9\t\n");
}

void player_Input(char pl)
{
	int in,flag=0;
	fflush(stdin);
	scanf("%d",&in);
	if(in>=1 && in<=9)
	{
		if(in==1 && (a[0][0]!='X' && a[0][0]!='O'))
		{
			a[0][0]=pl;
			flag=1;
		}
		if(in==2 && (a[0][1]!='X' && a[0][1]!='O'))
		{
			a[0][1]=pl;
			flag=1;
		}
		if(in==3 && (a[0][2]!='X' && a[0][2]!='O'))
		{
			a[0][2]=pl;
			flag=1;
		}
		if(in==4 && (a[1][0]!='X' && a[1][0]!='O'))
		{
			a[1][0]=pl;
			flag=1;
		}
		if(in==5 && (a[1][1]!='X' && a[1][1]!='O'))
		{
			a[1][1]=pl;
			flag=1;
		}
		if(in==6 && (a[1][2]!='X' && a[1][2]!='O'))
		{
			a[1][2]=pl;
			flag=1;
		}
		if(in==7 && (a[2][0]!='X' && a[2][0]!='O'))
		{
			a[2][0]=pl;
			flag=1;
		}
		if(in==8 && (a[2][1]!='X' && a[2][1]!='O'))
		{
			a[2][1]=pl;
			flag=1;
		}
		if(in==9 && (a[2][2]!='X' && a[2][2]!='O'))
		{
			a[2][2]=pl;
			flag=1;
		}
		if(flag)
			return;
		else
		{
			printf("\nEnter a valid cell number\n");
			player_Input(pl);
		}
	}
	else
	{
		printf("\nEnter a valid cell number\n");
		player_Input(pl);
	}
	
}

void initializeGame()
{
	int i,j;
	for(i=0;i<3;i++)
	{
		for(j=0;j<3;j++)
		{
			a[i][j]=' ';
		}
	}
}

void updateCells()
{
	printf("\n\n\t%c\t|\t%c\t|\t%c\t\n",a[0][0],a[0][1],a[0][2]);
	printf(" ---------------+---------------+---------------\n");
	printf("\t%c\t|\t%c\t|\t%c\t\n",a[1][0],a[1][1],a[1][2]);
	printf(" ---------------+---------------+---------------\n");
	printf("\t%c\t|\t%c\t|\t%c\t\n\n\n",a[2][0],a[2][1],a[2][2]);
}

int winner_Selection(char up)
{
	printf("%c",up);
	int f=0;
	
	if((a[0][0]==up && a[1][1]==up && a[2][2]==up) || (a[2][0]==up && a[1][1]==up && a[0][2]==up))
	{
		f=1;
	}
	if((a[0][0]==up && a[0][1]==up && a[0][2]==up) || (a[1][0]==up && a[1][1]==up && a[1][2]==up) || (a[2][0]==up && a[2][1]==up && a[2][2]==up))
	{
		f=1;
	}
	if((a[0][0]==up && a[1][0]==up && a[2][0]==up) || (a[0][1]==up && a[1][1]==up && a[2][1]==up) || (a[0][2]==up && a[1][2]==up && a[2][2]==up))
	{
		f=1;
	}
	if(f)
	{
		if(up==player1.mark)
		{
			printf("\n\nPlayer 1 is the winner\n\n");
		}
		if(up==player2.mark)
		{
			printf("\n\nPlayer 2 is the winner\n\n");
		}
		return 1;
	}
	else
	{
		return 0;
	}
}

int main()
{
	int toss,turn=0,p1=0,p2=0,win=0;
	char up;
	if(cp==0)
	{
		createPlayer();
		cp=1;
	}
	welcome();
	cells();
	initializeGame();
	updateCells();
	printf("\n\nPress 1 to toss : ");
	fflush(stdin);
	scanf("%d",&toss);
	if(toss==1)
	{
		if(tossF())
		{
			p1=1;
		}
		else
		{
			p2=1;
		}
		while(turn!=9)
		{
			if(turn>4)
			{
				win=winner_Selection(up);
				if(win==1)
				{
					break;
				}
			}
			if(p1)
			{
                printf("\n\nPlayer 1: [\'%c\'] : %s \n\n",player1.mark,player1.name);
				player_Input(player1.mark);
				system("cls");
				welcome();
				cells();
				updateCells();
				turn++;
				p1=0;
				p2=1;
				up=player1.mark;
				continue;				
			}
			if(p2)
			{
				printf("\n\nPlayer 2: [\'%c\'] : %s \n\n",player2.mark,player2.name);
				player_Input(player2.mark);
				system("cls");
				welcome();
				cells();
				updateCells();
				turn++;
				p2=0;
				p1=1;
				up=player2.mark;
				continue;
			}
		}
		if(turn==9)
		{
			win=winner_Selection(up);
		}
		if(win==0)
		{
			printf("\n\nDRAW\n\n");
		}
	}
	else
	{
		system("cls");
		main();
	}
	return 0;
}
