/*
** EPITECH PROJECT, 2024
** ftp
** File description:
** cdup
*/

#include <unistd.h>
#include <string.h>
#include <malloc.h>
#include <stdlib.h>

#include "my_ftp.h"
#include "constants.h"

static bool check_parent_path(client_t *client, server_t *server, int got)
{
    char cwd[MAX_BUFFER_SIZE];

    chdir("../");
    getcwd(cwd, sizeof(cwd));
    if (strstr(cwd, server->initial_path) == NULL) {
        chdir("../");
        getcwd(cwd, sizeof(cwd));
        if (strstr(cwd, server->initial_path) == NULL) {
            chdir(client[got].server_path);
        }
        return false;
    }
    return true;
}

void cdup(client_t *client, server_t *server, int got)
{
    char cwd[MAX_BUFFER_SIZE];

    if (client[got].is_login == false) {
        send_message_to_client(client, got, NOT_CONNECTED);
        return;
    }
    if (check_parent_path(client, server, got) == true) {
        free(client[got].server_path);
        client[got].server_path = strdup(getcwd(cwd, sizeof(cwd)));
        send_message_to_client(client, got, CDUP_OK);
        return;
    }
    send_message_to_client(client, got, CDUP_ERROR);
}
