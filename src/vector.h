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

#pragma once
#include <string.h>
#include "memory.h"
#define PAGE_SIZE 16

#define vector_var(type, name) struct \
    {                             \
        char typeSize;            \
        type *data;               \
        unsigned int len;         \
        unsigned int size;        \
    } name;

#define vector_init(type, name)   \
    name.typeSize = sizeof(type); \
    name.data = (type*) memalloc(PAGE_SIZE * sizeof(type)); \
    name.len = 0;                 \
    name.size = PAGE_SIZE;        \
    name.data[0] = '\0';

#define vector(type, name)        \
    vector_var(type, name);       \
    vector_init(type, name);

#define vector_free(name)                    \
    {                                        \
        free(name.data);                     \
        memset(&name, 0, sizeof(name));      \
    }

#define vector_clear(type, name)  \
    vector_free(name);            \
    vector_init(type, name);



#define vector_push_back(vec, val)                                                   \
    {                                                                                \
        if (vec.len >= vec.size)                                                     \
            vec.data = memrealloc(vec.data, (vec.size += PAGE_SIZE) * vec.typeSize); \
        vec.data[vec.len++] = val;                                                   \
        vec.data[vec.len] =   0;                                                     \
    }

#define vector_push_back_word(vec, ptr)     \
    {                                       \
        for (int i = 0; ptr[i]; i++)        \
            vector_push_back(vec, ptr[i]);  \
    }

#define vector_size(vec, outvar)        \
    unsigned long outvar = 0;           \
    for (; vec[outvar]; outvar++);
