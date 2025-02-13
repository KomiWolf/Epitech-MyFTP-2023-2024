/*
** EPITECH PROJECT, 2024
** ftp
** File description:
** port
*/

#include <unistd.h>
#include <string.h>
#include <stdio.h>

#include "my_ftp.h"
#include "constants.h"

static int set_nb(char *str, size_t *i)
{
    int nb = 0;
    int tmp = 0;

    for (; *i < strlen(str); (*i)++) {
        if (str[*i] == ',') {
            (*i)++;
            return nb;
        }
        if (*i == 0 || (*i > 0 && str[*i - 1] == ',')) {
            tmp = str[*i] - 48;
            nb += tmp;
            continue;
        }
        tmp = str[*i] - 48;
        nb *= 10;
        nb += tmp;
    }
    return nb;
}

static struct sockaddr_in fill_addr(char *str)
{
    struct sockaddr_in client_addr;
    size_t i = 0;
    int ip1 = set_nb(str, &i);
    int ip2 = set_nb(str, &i);
    int ip3 = set_nb(str, &i);
    int ip4 = set_nb(str, &i);
    int port1 = set_nb(str, &i);
    int port2 = set_nb(str, &i);
    int port = (port1 * 256 + port2);
    char ip[30] = "";

    sprintf(ip, "%d.%d.%d.%d", ip1, ip2, ip3, ip4);
    client_addr.sin_family = AF_INET;
    client_addr.sin_port = htons(port);
    client_addr.sin_addr.s_addr = inet_addr(ip);
    return client_addr;
}

static bool set_addr(client_t *client, char *str, int got)
{
    struct sockaddr_in client_addr = fill_addr(str);
    socklen_t len = sizeof(client_addr);

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

static bool set_connexion_to_client(client_t *client, char *str, int got)
{
    if (client[got].connexion != UNKNOW) {
        close(client[got].connexion);
    }
    client[got].connexion = socket(AF_INET, SOCK_STREAM, 0);
    if (client[got].connexion == UNKNOW) {
        return false;
    }
    if (set_addr(client, str, got) == false) {
        return false;
    }
    return true;
}

static bool check_format(char *str)
{
    int count_comma = 0;

    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] < 0 && str[i] > 9 && str[i] != ',') {
            return false;
        }
        if (str[i] == ',') {
            count_comma++;
        }
    }
    if (count_comma != 5) {
        return false;
    }
    return true;
}

void port(client_t *client, char **command, int got)
{
    if (client[got].is_login == false) {
        send_message_to_client(client, got, NOT_CONNECTED);
        return;
    }
    if (command[1] == NULL) {
        send_message_to_client(client, got, PORT_PARAMETER_ERROR);
        return;
    }
    if (check_format(command[1]) == false) {
        send_message_to_client(client, got, PORT_PARAMETER_ERROR);
        return;
    }
    if (set_connexion_to_client(client, command[1], got) == false) {
        if (client[got].connexion != UNKNOW)
            close(client[got].connexion);
        send_message_to_client(client, got, PORT_ERROR);
        return;
    }
    client[got].mode = ACTIVE;
    send_message_to_client(client, got, PORT_OK);
}
