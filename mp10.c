/*
 * Programmering i C
 * Fall 22
 * Mastery test 10
 *
 * File:         mp8.c
 * Description:  An implementation of conways game of life with functionality to save state.
 * Author:		 Simon Karlsen
 * CS username:	 dv22skn
 * Date:		 2022-10-10
 * Input:        Start condition and save location
 * Output:       Prints the game field in each step and saves the current state to save location on exit.
 */
#include <stdio.h>
#include <stdlib.h>

#include "game_of_life.h"
#include "game_of_life_file_handler.h"


int check_prog_params(int argc, const char *argv[], FILE **in_file_p, FILE **out_file_p);

int main(int argc, const char *argv[]){
	FILE *in_file_p, *out_file_p;
	char userChoice;
	field the_field;
	
	if(check_prog_params(argc,argv,&in_file_p,&out_file_p)){
		return 1;
	}

	if(load_config_from_file(&the_field, in_file_p)){
		return 1;
	}

	do{
		render_world(the_field);
		print_menu();
		if((userChoice = input_choice()) == '\n'){
			update_world(the_field);
		}
	}while(userChoice == '\n');

	if(save_config_to_file(the_field, out_file_p)){
		return 1;
	}	

	destroy_field(the_field);

	return 0;
}

/* Description: Checks the parameters to the program. Checks if the 
 *              call to the program has the right number of 
 *              parameters. Open the input and output files. 
 * Input:       The parameters to the program and two pointers to file 
 *              pointers. 
 * Output:      Returns 0 when the files are correctly opened. 
 *              Returns a non-zero value on failure. 
 */
  
int check_prog_params(int argc, const char *argv[], FILE **in_file_p, FILE **out_file_p){
	if(argc != 3){
		fprintf(stderr,"Usage: %s <input configuration file> <output configuration file>\n",argv[0]);
		return 1;
	}

	*in_file_p = fopen(argv[1],"r");
	if(*in_file_p == NULL){
		fprintf(stderr,"Could not open the file: %s\n",argv[1]);
		return 1;
	}

	*out_file_p = fopen(argv[2],"w");
	if(*out_file_p == NULL){
		fclose(*in_file_p);
		fprintf(stderr,"Could not open the file: %s\n",argv[2]);
		return 1;
	}

	return 0;
}