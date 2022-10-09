#include "game_of_life.h"

/* Description: Creates an instance of the data structure field
 * Input:       desired collumns and rows for the field.
 * Output:      an instance of the field structure.
 */

field create_field(int rows,int cols){
	cell **cellMatrix = malloc(rows * sizeof(cell *));
	
	for(int i = 0; i < rows; i++){
		cellMatrix[i] = calloc(cols, sizeof(cell));
	}

	field newField = {rows,cols,cellMatrix};

	return newField;
}

/* Description: Dealocate the memory allocated by create field 
 * Input:       the field that needs to be deallocated
 * Output:      nothing
 */

void destroy_field(field thisField){
	for(int i = 0; i < thisField.rows; i++){
		free(thisField.cells[i]); 
	}
	free(thisField.cells);
}
/* Description: Initialize all the cells to dead, then asks the user
 *              about which structure to load, and finally load the
 *              structure.
 * Input:       The field array and its size.
 * Output:      The field array is updated.
 *
 * Note:		The function is never needed and thusly is never called however i am not allowed to remove it
 */

void init_field(field the_field)
{
	for (int r = 0 ; r < the_field.rows ; r++) {
		for (int c = 0 ; c < the_field.cols ; c++) {
			the_field.cells[r][c].current = DEAD;
		}
	}
}


/* Description: Displays the current state in terminal
 * Input: The field array and its size
 * Output: Prints the field
 */

void render_world(const field the_field)
{
	for(int x = 0; x < the_field.rows; x++)
	{
		for(int y = 0; y<the_field.cols; y++)
		{
			printf("%c ", the_field.cells[x][y].current);
		}
		printf("\n");
	}
}

/* Description: Updates the field to the next step
 * Input: The field array and its size
 * Output: The field array is updated.
 */

void update_world(field the_field)
{
	calculate_next(the_field);
	for(int y = 0; y < the_field.cols; y++)
	{
		for(int x = 0; x < the_field.rows; x++)
		{
			the_field.cells[x][y].current = the_field.cells[x][y].next;
		}
	}
}

/* Description: Calculates the value of all cells in next step
 * Input: field array and its size
 * Output: The field array is updated.  
 */

void calculate_next(field the_field)
{
	for(int y = 0; y < the_field.cols; y++)
	{
		for(int x = 0; x < the_field.rows; x++)
		{
			the_field.cells[x][y].next = DEAD;

			int numberOfNeighbours = count_neighbours(the_field,x,y);
			
			if(the_field.cells[x][y].current == ALIVE)
			{
				if(numberOfNeighbours <= 1)
				{
					the_field.cells[x][y].next = DEAD;
				}
				else if(numberOfNeighbours <= 3)
				{	
					the_field.cells[x][y].next = ALIVE;
				}
				else
				{	
					the_field.cells[x][y].next = DEAD;
				}
			}
			else if(the_field.cells[x][y].current == DEAD && numberOfNeighbours == 3)
			{
				the_field.cells[x][y].next = ALIVE;
			}
		}
	}
}

/* Description: Looks at 8 cells surrounding one cell and determines how many are alive
 * Input: the field array, its size and a x and y coordinate for the current cell being evaluated
 * Output: number of alive neighbours to current cell
 */

int count_neighbours(const field the_field, const int x, const int y)
{
	int count = 0;
	for(int xoff = -1; xoff<2; xoff++) // offset x
	{
		for(int yoff = -1; yoff<2; yoff++) // offset y
		{
			if(//is false if there is no offset or the offset is out of bounds
			!((xoff == 0 && yoff == 0) 
			|| (x+xoff >= the_field.rows) 
			|| (y+yoff >= the_field.cols) 
			|| (x+xoff <= -1) 
			|| (y+yoff <= -1))) 
			{
				count += the_field.cells[x+xoff][y+yoff].current == ALIVE; 
			}
		}
	}
	return count;
}

/* Description: prints a menu choice to the user
 * Input: nothing
 * Output: prints menu to terminal
 */

void print_menu()
{
	printf("Select one of the following options:\n\t(enter)\tStep\n\t(any)\tSave and exit\n");
}

/* Description: takes input from user
 * Input: nothing
 * Output: user input from scanf (char)
 */

char input_choice()
{
	char input;
	scanf("%c",&input);
	return input;
}
