/*
** EPITECH PROJECT, 2024
** ftp
** File description:
** commands_utils
*/

#include <unistd.h>
#include <string.h>

#include "struct.h"

void send_message_to_client(client_t *client, int got, char *msg)
{
    write(client[got].id, msg, strlen(msg));
}
