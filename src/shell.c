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

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <wait.h>
#include "file.h"
#include "str.h"

void exec(char **argv) {
    pid_t pid;
    int status;

    pid = fork();
    if (pid == 0) {
        if (execvp(argv[0], argv) != 0) {
            perror("Execution error");
        }
        exit(0);
    } else if (pid < 0) {
        perror("Fork error");
    } else {
        do {
            waitpid(pid, &status, WUNTRACED);
        } while (!WIFEXITED(status) && !WIFSIGNALED(status));
    }
}

int run_command(char *line) {
    if (line == NULL)
        return 0;
    char **words = split(line, " ");

    if (!strcmp(words[0], "exit")) {
        if (words[1] != NULL)
            return atoi(words[1]);
        return 1;
    } else
        exec(words);

    free(words);

    return 0;
}
int run_text(char *data) {
    char **lines = split(data, "\n");
    int status = 0;

    for (unsigned int i = 0; i < strlen((char*) lines); i++)
        if ((status = run_command(lines[i])))
            return status;

    free(lines);

    return 0;
}
int run_file(const char *filepath) {
    FILE *file = fopen(filepath, "r");

    char *data = readFile(file);
    int status = run_text(data);

    free(data);
    fclose(file);
    return status;
}