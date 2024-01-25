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

#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include "soush.h"
#include "shell.h"
#include "file.h"
#include "vector.h"
#include "cwd.h"

static const char *PS1 = "\\W # ";
vector_var(char, prompt);

inline static void update_prompt() {
    vector_clear(char, prompt);
    for (unsigned int i = 0; PS1[i]; i++) {
        char ch = PS1[i];
        if (ch == '\\') {
            switch (PS1[++i]) {
                case 'W': vector_push_back_word(prompt, getCWD()); break;
                default:
                    fprintf(stderr, "unknown backslash symbol in $PS1: '\\%c'\n", PS1[i]);
                    exit(1);
            }
        } else
            vector_push_back(prompt, ch);
    }
}

char *getinput(char *prompt) {
    printf("%s", prompt);
    char *data = readFile(stdin);
    return data;
}

int main(int argc, char **argv) {
    vector_init(char, prompt);
    signal(SIGINT, SIG_IGN);

    if (argc > 1) {
        int op;
        while ((op = getopt(argc, argv, "c:hv")) != -1) {
            switch (op) {
                case 'c':
                    run_command(optarg);
                    return 0;
                case '?':
                    printf("Try '%s -h' for more information", argv[0]);
                    return 1;
                case 'h':
                    PRINT_HELP(argv[0], "[OPTION] [FILE]", "SOUrim SHell",
                               "  -c COMMAND\tRun COMMAND and exit\n" \
                               "  -h\tShow this message\n" \
                               "  -v\tShow version");
                    return 0;
                case 'v':
                    PRINT_VERSION();
                    return 0;
            }
        }

        if (optind < argc)
            return run_file(argv[optind]);
    }

    while (1) {
        update_prompt();
        char *input = getinput(prompt.data);
        int status = 0;

        if (*input == '\0')
            continue;
        
        if ((status = run_text(input)))
            return status;

        free(input);
    }
    return 0;
}