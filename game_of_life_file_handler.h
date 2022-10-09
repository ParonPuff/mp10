#ifndef GAME_OF_LIFE_FILE_HANDLER_H
#define GAME_OF_LIFE_FILE_HANDLER_H

#define BUFF_SIZE 300

#include <string.h>
#include <stdio.h>
#include "game_of_life.h"

int load_config_from_file(field *the_field, FILE *fp);
int save_config_to_file(const field the_field, FILE *fp); 

#endif