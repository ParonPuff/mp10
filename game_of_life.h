#ifndef GAME_OF_LIFE_H
#define GAME_OF_LIFE_H

#include <stdio.h>
#include <stdlib.h>

/* Constants, representation of states */
#define ALIVE 'X'
#define DEAD '.'

/* Declaration of data structure */
typedef struct {
	char current;
	char next;
} cell;

typedef struct { 
	int rows; 
	int cols; 
	cell **cells; 
} field; 

/* Declaration of functions */
field create_field(int rows,int cols);
void destroy_field(field thisField);

void init_field(field the_field);
void render_world(const field the_field);
void update_world(field the_field);
void calculate_next(field the_field);
int count_neighbours(const field the_field, const int x, const int y);
void print_menu();
char input_choice();

#endif