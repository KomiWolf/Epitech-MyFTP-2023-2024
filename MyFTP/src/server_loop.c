/*
** EPITECH PROJECT, 2024
** ftp
** File description:
** server_loop
*/

#include <stddef.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>

#include "my_ftp.h"
#include "constants.h"

static int connection_handling(client_t *client, server_t *server, int i)
{
    socklen_t fd_size = sizeof(server->server_fd);

    if (i == server->server_fd) {
        server->client_fd = accept(server->server_fd,
        (struct sockaddr *)&server->client_addr,
        &fd_size);
        if (server->client_fd == -1) {
            fprintf(stderr, ACCEPT_ERR);
            return ERROR;
        }
        FD_SET(server->client_fd, &server->current_fd);
        add_new_client(client, server, server->client_fd);
        write(server->client_fd, NEW_CONNECTION, strlen(NEW_CONNECTION));
        printf("Connexion from %s:%d\n",
        inet_ntoa(server->client_addr.sin_addr),
        ntohs(server->client_addr.sin_port));
    } else {
        command_handling(client, server, i);
    }
    return SUCCESS;
}

static int fd_loop_statement(client_t *client, server_t *server, int i)
{
    if (FD_ISSET(i, &server->ready_fd)) {
        if (connection_handling(client, server, i) == ERROR) {
            return ERROR;
        }
    }
    return SUCCESS;
}

static int loop_in_fd(client_t *client, server_t *server)
{
    for (int i = 0; i < FD_SETSIZE; i++) {
        if (fd_loop_statement(client, server, i) == ERROR) {
            return ERROR;
        }
    }
    return SUCCESS;
}

void server_loop(server_t *server)
{
    client_t *client;

    client = init_client_list();
    FD_ZERO(&server->current_fd);
    FD_SET(server->server_fd, &server->current_fd);
    while (INFINITE_LOOP) {
        server->ready_fd = server->current_fd;
        if (select(FD_SETSIZE, &server->ready_fd, NULL, NULL, NULL) < 0) {
            fprintf(stderr, SELECT_ERR);
            break;
        }
        if (loop_in_fd(client, server) == ERROR) {
            return;
        }
    }
}
