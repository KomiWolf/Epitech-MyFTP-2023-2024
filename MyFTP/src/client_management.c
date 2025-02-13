/*
** EPITECH PROJECT, 2024
** ftp
** File description:
** client_management
*/

#include <stddef.h>
#include <string.h>
#include <malloc.h>
#include <unistd.h>

#include "my_ftp.h"
#include "constants.h"

static bool check_client_existence(client_t *client, int fd)
{
    for (int i = 0; i < MAX_CLIENT; i++) {
        if (client[i].id == fd) {
            return true;
        }
    }
    return false;
}

static void add_client_value(client_t *client, server_t *server, int fd, int i)
{
    client[i].id = fd;
    client[i].connexion = UNKNOW;
    client[i].is_login = false;
    client[i].mode = UNKNOW;
    client[i].server_path = strdup(server->initial_path);
    client[i].port = UNKNOW;
    client[i].has_username = false;
}

int get_client(client_t *client, int fd)
{
    for (int i = 0; i < MAX_CLIENT; i++) {
        if (client[i].id == fd) {
            return i;
        }
    }
    return UNKNOW;
}

void add_new_client(client_t *client, server_t *server, const int fd)
{
    if (check_client_existence(client, fd) == true) {
        return;
    }
    for (int i = 0; i < MAX_CLIENT; i++) {
        if (client[i].id == UNKNOW) {
            add_client_value(client, server, fd, i);
            return;
        }
    }
}

static void close_connexion(client_t *client, int i)
{
    if (client[i].connexion != UNKNOW) {
        shutdown(client[i].connexion, SHUT_RDWR);
        close(client[i].connexion);
    }
}

void delete_client(client_t *client, const int fd)
{
    for (int i = 0; i < MAX_CLIENT; i++) {
        if (client[i].id == fd) {
            client[i].id = UNKNOW;
            close_connexion(client, i);
            client[i].connexion = UNKNOW;
            client[i].is_login = false;
            client[i].mode = UNKNOW;
            free(client[i].server_path);
            client[i].server_path = NULL;
            client[i].port = UNKNOW;
            client[i].has_username = false;
        }
    }
}
