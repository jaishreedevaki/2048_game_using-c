#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<conio.h>
#define grid_size 4
#define multiplier 1103515245
#define increment 12345
#define modulo (1U << 31)
int game_grid[grid_size][grid_size]={0};
unsigned int seed;
int game_over;
int flag_2048=0;
int score=0;
int zero_present=1;
int same_neighbour=0;
void default_grid()
{
    game_grid[1][1]=8;
    game_grid[3][2]=32;
    game_grid[2][3]=2;
}
unsigned int random_generator()
{   
    seed=(multiplier*seed+increment)%modulo;
    return seed;		
}
int random_filling(int start,int end,int add_value)
{
    int row_index;
    int col_index;
    for(row_index=start;row_index<end;row_index++)
    {
		for(col_index=start;col_index<end;col_index++)
		{
			if(game_grid[row_index][col_index]==0)
			{
			   game_grid[row_index][col_index]=add_value;
			   return 1;	
			}
		}
    }
    return 0;
}
int  random_value()
{
	int add_value;
	unsigned int value=random_generator();
	if(value%2==0)
	{
	   add_value=2;	
	}
	else 
	{
	   add_value=4;
	}
	int random_index=value%grid_size;
        if(random_filling(0,random_index,add_value))
        {
    	   return 0;
	}
	else if(random_filling(random_index,grid_size,add_value))
	{
	   return 0;
	}
	else 
	{
	   random_value();
	}
	
}
void grid_display()
{
	int index_row;
	int index_col;
	int pat_index;
	printf("\n\n\n\n\n");
	for(index_row=0;index_row<grid_size;index_row++)
	{ 
	  printf("\t\t\t\t");
	  for(pat_index=0;pat_index<29;pat_index++)
	  {
	  	printf("_");
	  } 
	  printf("\n\n");
	  for(index_col=0;index_col<grid_size;index_col++)
	  { 
	      if(index_col==0)
	       {
	          printf("\t\t\t\t");
	       }
	       if(game_grid[index_row][index_col]!=0)
		{
		   printf("| %4d ",game_grid[index_row][index_col]);
	        }
	       else 
	        {
	           printf("|      ");	
		}
	  }	
	   printf("|\n");
	   if(index_row==grid_size-1)
           {  
              printf("\t\t\t\t");
	      for(pat_index=0;pat_index<29;pat_index++)
	       {
	  	   printf("_");
	       } 
	   }
	}
	printf("\n\n\t\t\t\t\t  SCORE: %d",score);
}
void alter_if_zerorow(int neighbour_row,int current_row,int col_index)
{
    game_grid[neighbour_row][col_index]=game_grid[current_row][col_index];
    game_grid[current_row][col_index]=0;		
}
void alter_if_zerocol(int neighbour_col,int current_col,int row_index)
{
    game_grid[row_index][neighbour_col]=game_grid[row_index][current_col];
    game_grid[row_index][current_col]=0;		
}
void alter_if_samerow(int neighbour_row,int current_row,int col_index)
{
    game_grid[neighbour_row][col_index]=2*game_grid[neighbour_row][col_index];
    score+=game_grid[neighbour_row][col_index];
    game_grid[current_row][col_index]=0;	
}
void alter_if_samecol(int neighbour_col,int current_col,int row_index)
{
    game_grid[row_index][neighbour_col]=2*game_grid[row_index][neighbour_col];
    score+=game_grid[row_index][neighbour_col];
    game_grid[row_index][current_col]=0;	
}
void up()
{
	int col_index;
	int row_index;
	int dum_index;
	for(col_index=0;col_index<grid_size;col_index++)
	{
		for(row_index=0;row_index<grid_size;row_index++)
		{
			if(game_grid[row_index][col_index]!=0)
			{
				dum_index=row_index;
				while(dum_index>0)
				{
					if(game_grid[dum_index-1][col_index]==0)
					{
					   alter_if_zerorow(dum_index-1,dum_index,col_index);
					   dum_index--;
					}
					else if(game_grid[dum_index-1][col_index]==game_grid[dum_index][col_index])
					{
					    alter_if_samerow(dum_index-1,dum_index,col_index);
					    dum_index--;
					}
					else
					{
					    break;
					}
				}
			}
		}
	}	
}
void down()
{ 
	int col_index;
	int row_index;
	int dum_index;
	for(col_index=grid_size-1;col_index>=0;col_index--)
	{
		for(row_index=grid_size-1;row_index>=0;row_index--)
		{
			if(game_grid[row_index][col_index]!=0)
			{
				dum_index=row_index;
				while(dum_index<grid_size-1)
				{
					if(game_grid[dum_index+1][col_index]==0)
					{
					   alter_if_zerorow(dum_index+1,dum_index,col_index);	
					   dum_index++;
					}
					else if(game_grid[dum_index+1][col_index]==game_grid[dum_index][col_index])
					{
					    alter_if_samerow(dum_index+1,dum_index,col_index);
					    dum_index++;
					}
					else
					{
					    break;
					}
				}
			}
		}
	}	
}
void left()
{
	int col_index;
	int row_index;
	int dum_index;
	for(row_index=0;row_index<grid_size;row_index++)
	{
		for(col_index=0;col_index<grid_size;col_index++)
		{
			if(game_grid[row_index][col_index]!=0)
			{
			   dum_index=col_index;
			   while(dum_index>0)
			   {
					if(game_grid[row_index][dum_index-1]==0)
					{
					   alter_if_zerocol(dum_index-1,dum_index,row_index);	
					   dum_index--;
					}
					else if(game_grid[row_index][dum_index-1]==game_grid[row_index][dum_index])
					{
					    alter_if_samecol(dum_index-1,dum_index,row_index);
					    dum_index--;
					}
					else
					{
					     break;
					}
			   }	
			}
		}
	}
}
void right()
{
	int col_index;
	int row_index;
	int dum_index;
	for(row_index=grid_size-1;row_index>=0;row_index--)
	{
		for(col_index=grid_size-1;col_index>=0;col_index--)
		{
			if(game_grid[row_index][col_index]!=0)
			{
			   dum_index=col_index;
			   while(dum_index<grid_size-1)
			   {
					if(game_grid[row_index][dum_index+1]==0)
					{
					   alter_if_zerocol(dum_index+1,dum_index,row_index);	
					   dum_index++;
					}
					else if(game_grid[row_index][dum_index+1]==game_grid[row_index][dum_index])
					{
					    alter_if_samecol(dum_index+1,dum_index,row_index);
					    dum_index++;
					}
					else
					{
					    break;
					}
			   }	
			}
		}
	}
}
void get_input(int * valid_key_ptr)
{
   int key=getch();
   if(key==224)
   { 
     int specific_key=getch();
     switch(specific_key)
       {
         case 72:
   	    	up();
   		break;
         case 77:
   	    	right();
   	    	break;
     	 case 80:
	        down();
	    	break;
	     case 75:
	        left();
		break;	
       }
   }
   else if(key=='0') 
   {
   	game_over=1;
   }
   else
   {
   	*valid_key_ptr=1;
   }
}
void check_zero()
{
	zero_present=0;
	int row_index;
	int col_index;
	for(row_index=0;row_index<grid_size;row_index++)
	{
		for(col_index=0;col_index<grid_size;col_index++)
		{
			if(game_grid[row_index][col_index]==0)
			{
				zero_present=1;
				break;
			}
		}
		if(zero_present==1)
		{
			break;
		}
	}		
}
void check_move()
{
	int row_index;
	int col_index;
	same_neighbour=0;
	for(row_index=0;row_index<grid_size;row_index++)
	{
		for(col_index=0;col_index<grid_size;col_index++)
		{
			if(col_index>0&&game_grid[row_index][col_index]==game_grid[row_index][col_index-1])
			{
				same_neighbour=1;
				break;
			}
			else if(col_index<grid_size-1&&game_grid[row_index][col_index]==game_grid[row_index][col_index+1])
			{
				same_neighbour=1;
				break;
			}
			else if(row_index>0&&game_grid[row_index][col_index]==game_grid[row_index+1][col_index])
			{
				same_neighbour=1;
				break;				
			}
			else if(row_index<grid_size-1&&game_grid[row_index][col_index]==game_grid[row_index+1][col_index])
			{
				same_neighbour=1;
				break;				
			}				
		}
	       if(same_neighbour==1)
        	{
		      break;
        	}	
	}
}
void check_2048()
{
	int row_index;
	int col_index;
	for(row_index=0;row_index<grid_size;row_index++)
	{
		for(col_index=0;col_index<grid_size;col_index++)
		{
			if(game_grid[row_index][col_index]==2048)
			{
				flag_2048=1;
				break;
			}
		}
		if(flag_2048==1)
		{
			break;
		}
	}	
}
int main()
{  
   printf("WELCOME!!!\n\nREAD BELOW FOR INSTRUCTIONS:\n\nPress PgUp Button To Move the blocks upward.\n\nPress PgDn Button To Move the blocks downward.\n\nPress End Button To Move the blocks right.\n\nPress Home Button To Move the blocks left.\n\nPress 0 to exit.\n\n");
   printf("PRESS ENTER KEY TO CONTINUE\n");
   if((int)getch()==13)
   {
      default_grid(); 
      seed=(unsigned int)time(NULL);
      int valid_key=0;
      system("cls");
      grid_display();
      while(!game_over)
      {
   	  get_input(&valid_key);
   	  if(!valid_key)
   	  {
   	     check_zero();
   	     if(zero_present)
   	     {
   	     	random_value();	
	     }
	     else
	     {
	        check_move();
	     }	
             system("cls");
             grid_display();	 
	     if(!zero_present&&!same_neighbour) 
	     {
		game_over=1;	
	     } 
	     if(!zero_present&&same_neighbour==1)
	     {
		printf("\n\nHINT:\nYou still have a chance to win.\n\n");
	     } 
         }
         else
         {  
            system("cls");
            grid_display(); 
            printf("\n\nWARNING:\n\nPlease enter a valid key");
            valid_key=0;
	}       
      }
      system("cls");      
      printf("GAME OVER!!\n\n");
      check_2048();
      if(flag_2048)
      {
      	printf("YOU WON!!!\n\nTOTAL SCORE : %d",score);
      }
      else
      {
	printf("YOU LOST!!!\n\nTOTAL SCORE : %d",score);
      }
   }
   return 0;
}
