/*
** EPITECH PROJECT, 2024
** ftp
** File description:
** do_command
*/

#include <string.h>
#include <unistd.h>

#include "my_ftp.h"
#include "constants.h"

static char *to_lower(char *str)
{
    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] >= 65 && str[i] <= 90) {
            str[i] += 32;
        }
    }
    return str;
}

static bool do_command_4(client_t *cli, char **c, int got)
{
    if (strcmp(to_lower(c[0]), "dele") == 0) {
        dele(cli, c, got);
        return true;
    }
    if (strcmp(to_lower(c[0]), "stor") == 0) {
        stor(cli, c, got);
        return true;
    }
    return false;
}

static bool do_command_3(client_t *cli, char **c, int got)
{
    if (strcmp(to_lower(c[0]), "pasv") == 0) {
        pasv(cli, got);
        return true;
    }
    if (strcmp(to_lower(c[0]), "port") == 0) {
        port(cli, c, got);
        return true;
    }
    if (strcmp(to_lower(c[0]), "list") == 0) {
        list(cli, got);
        return true;
    }
    if (strcmp(to_lower(c[0]), "retr") == 0) {
        retr(cli, c, got);
        return true;
    }
    if (do_command_4(cli, c, got) == true) {
        return true;
    }
    return false;
}

static bool do_command_2(client_t *cli, server_t *server, char **c, int got)
{
    if (strcmp(to_lower(c[0]), "quit") == 0) {
        quit(cli, server, got);
        return true;
    }
    if (strcmp(to_lower(c[0]), "pwd") == 0) {
        pwd(cli, got);
        return true;
    }
    if (strcmp(to_lower(c[0]), "cwd") == 0) {
        cwd(cli, server, c, got);
        return true;
    }
    if (strcmp(to_lower(c[0]), "cdup") == 0) {
        cdup(cli, server, got);
        return true;
    }
    if (do_command_3(cli, c, got) == true) {
        return true;
    }
    return false;
}

void do_command(client_t *client, server_t *server, char **command, int got)
{
    if (strcmp(to_lower(command[0]), "user") == 0) {
        return user(client, command, got);
    }
    if (strcmp(to_lower(command[0]), "pass") == 0) {
        return pass(client, command, got);
    }
    if (strcmp(to_lower(command[0]), "noop") == 0) {
        return noop(client, got);
    }
    if (strcmp(to_lower(command[0]), "help") == 0) {
        return help(client, got);
    }
    if (do_command_2(client, server, command, got) == true) {
        return;
    }
    write(client[got].id, UNKNOWN_COMMAND, strlen(UNKNOWN_COMMAND));
}
