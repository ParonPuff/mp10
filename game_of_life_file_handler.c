#include "game_of_life_file_handler.h"
/* Description: Loads a configuration to the field structure from a 
§ *              file. It is the responsiblity of the caller to 
 *              deallocate the dynamically allocated memory in the field 
 *              structure through a call to the function destroy_field. 
 *              The file pointed to by fp is closed. 
 * Input:       A pointer to where the created field structure should be 
 *              assigned and a file pointer to the file with the initial 
 *              configuration. 
 * Output:      Returns 0 on success, the field structure is created 
 *              with the configuration from the file. 
 *              Returns a non-zero value on failure. 
 */ 
int load_config_from_file(field *the_field, FILE *fp){
	int rows, cols;
	char current_line[BUFF_SIZE];

	if(fgets(current_line,BUFF_SIZE,fp) == NULL){
		fclose(fp);
		return 1;
	}

	if(sscanf(current_line, "%d,%d", &rows, &cols) != 2){
		fprintf(stderr,"Incorrect configuration file format\n");
		fclose(fp);
		return 1;
	}

	*the_field = create_field(rows, cols);

	int x = 0, y = 0;		

	while(fgets(current_line,BUFF_SIZE,fp) != NULL){
		while(current_line[y] != '\n'){
			if(current_line[y] == '*'){
				the_field -> cells[x][y].current = ALIVE;
			}
			else{
				the_field -> cells[x][y].current = DEAD;
			}
			y++;
		}
		y = 0;
		x++;
	}

	fclose(fp);

	return 0;
}
/* Description: Saves the current configuration of the field to a 
 *              specified file. The file pointed to by fp is closed. 
 * Input:       The field structure and a file pointer to the file 
 *              where the final configuration should be saved. 
 * Output:      Returns 0 on success, the current configuration in the 
 *              field is written to the file. 
 *              Returns a non-zero value on failure. 
 */ 
int save_config_to_file(const field the_field, FILE *fp){
	
	fprintf(fp, "%d,%d\n", the_field.rows, the_field.cols);

	for(int x = 0; x < the_field.rows; x++){
		for(int y = 0; y < the_field.cols; y++){
			if(the_field.cells[x][y].current == ALIVE){
				fprintf(fp, "%c", '*');		
			}
			else{
				fprintf(fp,"%c", '0');
			}
		}
		fprintf(fp, "\n");
	}

	fclose(fp);

	return 0;
}

