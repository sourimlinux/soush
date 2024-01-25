/*
 * soush -- SOUrim SHell
 * Copyright (C) 2024 r2u2team
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

#include <string.h>
#include "vector.h"

char **split(char *data, const char *delim) {
    vector(char*, out);
    char *word = strtok(data, delim);
    
    while (word != NULL) {
        vector_push_back(out, word);
        word = strtok(NULL, delim);
    }

    return out.data;
}