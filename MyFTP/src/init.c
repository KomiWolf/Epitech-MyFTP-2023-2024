/*
** EPITECH PROJECT, 2024
** ftp
** File description:
** init
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <string.h>

#include "struct.h"
#include "constants.h"

static int init_server_error(server_t *server, char *error_msg)
{
    fprintf(stderr, error_msg);
    if (server->server_fd != -1) {
        close(server->server_fd);
    }
    return ERROR;
}

static char *get_cwd(void)
{
    char cwd[MAX_BUFFER_SIZE];
    char *str = strdup(getcwd(cwd, sizeof(cwd)));

    return str;
}

static int set_up_server(server_t *serv, char **av)
{
    socklen_t len = 0;

    serv->server_addr.sin_family = AF_INET;
    serv->server_addr.sin_port = htons(serv->port);
    serv->server_addr.sin_addr.s_addr = INADDR_ANY;
    len = sizeof(serv->server_addr);
    if (bind(serv->server_fd, (struct sockaddr *)&serv->server_addr,
        len) == -1) {
        shutdown(serv->server_fd, SHUT_RDWR);
        return init_server_error(serv, BIND_ERR);
    }
    if (listen(serv->server_fd, MAX_CLIENT) == -1) {
        return init_server_error(serv, LISTEN_ERR);
    }
    chdir(av[2]);
    serv->initial_path = get_cwd();
    return SUCCESS;
}

int init_server(server_t *serv, char **av)
{
    serv->port = atoi(av[1]);
    serv->server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (serv->server_fd == -1) {
        return init_server_error(serv, SOCKET_ERR);
    }
    if (set_up_server(serv, av) == ERROR) {
        return ERROR;
    }
    return SUCCESS;
}

client_t *init_client_list(void)
{
    client_t *clients = malloc(sizeof(client_t) * MAX_CLIENT);

    for (int i = 0; i < MAX_CLIENT; i++) {
        clients[i].id = UNKNOW;
        clients[i].is_login = false;
        clients[i].connexion = UNKNOW;
        clients[i].mode = UNKNOW;
        clients[i].server_path = NULL;
        clients[i].port = UNKNOW;
        clients[i].has_username = false;
    }
    return clients;
}
