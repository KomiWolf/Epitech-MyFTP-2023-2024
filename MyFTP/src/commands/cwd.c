/*
** EPITECH PROJECT, 2024
** ftp
** File description:
** cwd
*/

#include <unistd.h>
#include <string.h>
#include <malloc.h>
#include <sys/stat.h>

#include "my_ftp.h"
#include "constants.h"

static bool check_new_path(client_t *cli, server_t *server, char **c, int got)
{
    struct stat info;
    char cwd[MAX_BUFFER_SIZE];

    if (stat(c[1], &info) == -1) {
        return false;
    }
    if (S_ISDIR(info.st_mode) == false) {
        return false;
    }
    chdir(c[1]);
    getcwd(cwd, sizeof(cwd));
    if (strstr(cwd, server->initial_path) == NULL) {
        chdir("../");
        getcwd(cwd, sizeof(cwd));
        if (strstr(cwd, server->initial_path) == NULL) {
            chdir(cli[got].server_path);
        }
        return false;
    }
    return true;
}

void cwd(client_t *client, server_t *server, char **command, int got)
{
    char cwd[MAX_BUFFER_SIZE];

    if (client[got].is_login == false) {
        send_message_to_client(client, got, NOT_CONNECTED);
        return;
    }
    if (command[1] == NULL) {
        send_message_to_client(client, got, CWD_ERROR);
        return;
    }
    if (check_new_path(client, server, command, got) == true) {
        free(client[got].server_path);
        client[got].server_path = strdup(getcwd(cwd, sizeof(cwd)));
        send_message_to_client(client, got, CWD_OK);
        return;
    }
    send_message_to_client(client, got, CWD_ERROR);
}
