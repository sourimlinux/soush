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
#include <stdio.h>
#include <stdlib.h>

inline static void *memalloc(size_t size) {
    void *out = malloc(size);
    if (!out) {
        perror("Memory allocation error:");
        exit(1);
    }
    return out;
}
inline static void *memrealloc(void *ptr, size_t size) {
    void *out = realloc(ptr, size);
    if (!out) {
        perror("Memory reallocation error:");
        exit(1);
    }
    return out;
}