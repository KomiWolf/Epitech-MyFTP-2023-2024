/*
** EPITECH PROJECT, 2024
** ftp
** File description:
** pwd
*/

#include <unistd.h>
#include <string.h>

#include "my_ftp.h"
#include "constants.h"

void pwd(client_t *client, int got)
{
    char end_display[] = ".\r\n";

    if (client[got].is_login == false) {
        send_message_to_client(client, got, NOT_CONNECTED);
        return;
    }
    send_message_to_client(client, got, PRINT_PWD);
    send_message_to_client(client, got, client[got].server_path);
    send_message_to_client(client, got, end_display);
}
