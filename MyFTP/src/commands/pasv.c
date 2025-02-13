/*
** EPITECH PROJECT, 2024
** ftp
** File description:
** pasv
*/

#include <unistd.h>
#include <string.h>
#include <stdio.h>

#include "my_ftp.h"
#include "constants.h"

static void send_ip_and_port(client_t *client, int got)
{
    int fd = client[got].id;
    struct sockaddr_in addr;
    socklen_t len = sizeof(addr);
    char *ip = NULL;
    int port1 = 0;
    int port2 = 0;
    char msg[100] = "227 Connexion ip and port: ";

    getsockname(client[got].connexion, (struct sockaddr *)&addr,
    &len);
    ip = inet_ntoa(addr.sin_addr);
    port1 = client[got].port / 256;
    port2 = client[got].port % 256;
    strcat(msg, ip);
    send_message_to_client(client, got, msg);
    dprintf(fd, ":%d.\r\n", (port1 + port2));
}

static bool set_addr(client_t *client, int got)
{
    struct sockaddr_in client_addr;
    socklen_t len = 0;

    client_addr.sin_family = AF_INET;
    client_addr.sin_port = htons(0);
    client_addr.sin_addr.s_addr = INADDR_ANY;
    len = sizeof(client_addr);
    if (bind(client[got].connexion, (struct sockaddr *)&client_addr,
    len) == FUNC_ERROR) {
        return false;
    }
    if (listen(client[got].connexion, 1) == FUNC_ERROR) {
        return false;
    }
    client[got].port = ntohs(client_addr.sin_port);
    return true;
}

static bool set_connexion_to_client(client_t *client, int got)
{
    if (client[got].connexion != UNKNOW) {
        close(client[got].connexion);
    }
    client[got].connexion = socket(AF_INET, SOCK_STREAM, 0);
    if (client[got].connexion == UNKNOW) {
        return false;
    }
    if (set_addr(client, got) == false) {
        return false;
    }
    return true;
}

void pasv(client_t *client, int got)
{
    if (client[got].is_login == false) {
        send_message_to_client(client, got, NOT_CONNECTED);
        return;
    }
    if (set_connexion_to_client(client, got) == false) {
        if (client[got].connexion != UNKNOW) {
            close(client[got].connexion);
        }
        send_message_to_client(client, got, PASV_ERROR);
        return;
    }
    client[got].mode = PASSIVE;
    send_ip_and_port(client, got);
    send_message_to_client(client, got, PASV_OK);
}
