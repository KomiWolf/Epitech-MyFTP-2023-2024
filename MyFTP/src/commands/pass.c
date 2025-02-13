/*
** EPITECH PROJECT, 2024
** ftp
** File description:
** pass
*/

#include <unistd.h>
#include <string.h>

#include "my_ftp.h"
#include "constants.h"

void pass(client_t *client, char **command, int got)
{
    if (client[got].has_username == false) {
        send_message_to_client(client, got, NEED_USER);
        return;
    }
    if (client[got].is_login == true) {
        send_message_to_client(client, got, LOGGED_PASS);
        return;
    }
    if (command[1] == NULL || strcmp(command[1], "\0") != 0) {
        send_message_to_client(client, got, PASS_ERROR);
        return;
    }
    client[got].is_login = true;
    send_message_to_client(client, got, PASS_OK);
}
