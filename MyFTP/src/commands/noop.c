/*
** EPITECH PROJECT, 2024
** ftp
** File description:
** noop
*/

#include <unistd.h>
#include <string.h>

#include "my_ftp.h"
#include "constants.h"

void noop(client_t *client, int got)
{
    if (client[got].is_login == false) {
        send_message_to_client(client, got, NOT_CONNECTED);
        return;
    }
    return send_message_to_client(client, got, NOOP_OK);
}
