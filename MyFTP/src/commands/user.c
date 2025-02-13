/*
** EPITECH PROJECT, 2024
** ftp
** File description:
** user
*/

#include <unistd.h>
#include <string.h>

#include "my_ftp.h"
#include "constants.h"

void user(client_t *client, char **command, int got)
{
    if (command[1] == NULL || command[1][0] == '\0') {
        send_message_to_client(client, got, USER_ERROR);
        return;
    }
    if (client[got].has_username == true) {
        send_message_to_client(client, got, LOGGED_USER);
        return;
    }
    client[got].has_username = true;
    if (strcmp(command[1], "Anonymous") == 0) {
        return send_message_to_client(client, got, USER_OK);
    } else {
        return send_message_to_client(client, got, NEW_USER);
    }
}
