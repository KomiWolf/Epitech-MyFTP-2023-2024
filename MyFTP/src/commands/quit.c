/*
** EPITECH PROJECT, 2024
** ftp
** File description:
** quit
*/

#include <unistd.h>
#include <string.h>
#include <stdio.h>

#include "my_ftp.h"
#include "constants.h"

void quit(client_t *client, server_t *server, int got)
{
    int fd = client[got].id;

    if (client[got].is_login == false) {
        send_message_to_client(client, got, NOT_CONNECTED);
        return;
    }
    send_message_to_client(client, got, QUIT_OK);
    close(fd);
    FD_CLR(fd, &server->current_fd);
    delete_client(client, fd);
    printf("Client %d disconnected\n", fd);
}
