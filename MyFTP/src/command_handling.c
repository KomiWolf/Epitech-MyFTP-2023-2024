/*
** EPITECH PROJECT, 2024
** ftp
** File description:
** command_handling
*/

#include <unistd.h>
#include <stdio.h>
#include <malloc.h>
#include <string.h>

#include "my_ftp.h"
#include "constants.h"

static int count_space(const char *user_input)
{
    int counter = 0;

    for (int i = 0; i < MAX_BUFFER_SIZE; i++) {
        if (user_input[i] == '\0') {
            return counter;
        }
        if (user_input[i] == ' ') {
            counter++;
        }
    }
    return counter;
}

static void fill_str(char *str, const char *user_input, int *a)
{
    int k = 0;

    while (user_input[*a] != ' ') {
        if (user_input[*a] == '\0' || user_input[*a] == '\n' ||
            user_input[*a] == '\r') {
            break;
        }
        str[k] = user_input[*a];
        (*a)++;
        k++;
    }
    str[k] = '\0';
}

static char **parse_command(const char *user_input)
{
    int nb_space = count_space(user_input);
    char **parsed_command = malloc(sizeof(char *) * (nb_space + 2));
    int a = 0;
    int i = 0;

    for (; i < nb_space + 1; i++) {
        parsed_command[i] = malloc(sizeof(char) * MAX_BUFFER_SIZE);
        fill_str(parsed_command[i], user_input, &a);
        a++;
    }
    parsed_command[i] = NULL;
    return parsed_command;
}

static void replace_char(const int size, char *user_input)
{
    for (int i = 0; i < size; i++) {
        if (user_input[i] == '\0' || user_input[i] == '\n' ||
            user_input[i] == '\r') {
            break;
        }
        if (user_input[i] == '\t') {
            user_input[i] = ' ';
        }
    }
}

static void read_error(ssize_t read_bytes, client_t *client, int *i, int got)
{
    if (read_bytes == 0) {
        printf("Client %d disconnected\n", client[got].id);
    } else {
        fprintf(stderr, READ_ERR);
    }
    close(*i);
}

static void free_all(char *command, char **parsed_command)
{
    int nb_space = count_space(command);

    for (int i = 0; i < nb_space + 1; i++) {
        free(parsed_command[i]);
    }
    free(parsed_command);
    free(command);
}

static char *setup_command(char buffer[], char ***parsed_command)
{
    char *str = strdup(buffer);

    printf("Received command: %s\n", buffer);
    memset(buffer, '\0', MAX_BUFFER_SIZE);
    replace_char(MAX_BUFFER_SIZE, str);
    *parsed_command = parse_command(str);
    return str;
}

void command_handling(client_t *client, server_t *server, int i)
{
    char buffer[MAX_BUFFER_SIZE];
    ssize_t read_bytes = 0;
    int got = get_client(client, i);
    char **parsed_command = NULL;
    char *command = NULL;

    memset(buffer, '\0', MAX_BUFFER_SIZE);
    read_bytes = read(i, buffer, sizeof(buffer));
    if (read_bytes <= 0) {
        read_error(read_bytes, client, &i, got);
        FD_CLR(i, &server->current_fd);
        delete_client(client, i);
    } else if (read_bytes >= MAX_BUFFER_SIZE) {
        return;
    } else {
        command = setup_command(buffer, &parsed_command);
        do_command(client, server, parsed_command, got);
        free_all(command, parsed_command);
    }
}
