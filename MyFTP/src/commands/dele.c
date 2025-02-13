/*
** EPITECH PROJECT, 2024
** ftp
** File description:
** dele
*/

#include <unistd.h>
#include <string.h>
#include <sys/stat.h>
#include <stdio.h>

#include "my_ftp.h"
#include "constants.h"

static bool is_file(char **c)
{
    struct stat info;

    if (stat(c[1], &info) == -1) {
        return false;
    }
    if (S_ISDIR(info.st_mode) == true) {
        return false;
    }
    return true;
}

void dele(client_t *client, char **command, int got)
{
    if (client[got].is_login == false) {
        send_message_to_client(client, got, NOT_CONNECTED);
        return;
    }
    if (command[1] == NULL) {
        send_message_to_client(client, got, DELE_PARAMETER_ERROR);
        return;
    }
    if (is_file(command) == true) {
        remove(command[1]);
        send_message_to_client(client, got, DELE_OK);
    } else {
        send_message_to_client(client, got, DELE_FILE_ERROR);
    }
    return;
}
