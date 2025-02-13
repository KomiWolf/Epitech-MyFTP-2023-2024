/*
** EPITECH PROJECT, 2024
** ftp
** File description:
** stor
*/

#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>

#include "my_ftp.h"
#include "constants.h"

static void get_file(client_t *client, int got, int file_fd)
{
    struct sockaddr_in connexion_addr;
    socklen_t len = sizeof(connexion_addr);
    int fd = accept(client[got].connexion, (struct sockaddr *)&connexion_addr,
    &len);
    char buffer[5000];
    ssize_t bytes = 0;

    while (true) {
        memset(buffer, '\0', sizeof(buffer) - 1);
        bytes = read(fd, buffer, sizeof(buffer) - 1);
        if (bytes < 0) {
            close(file_fd);
            exit(ERROR);
        }
        if (bytes == 0) {
            close(file_fd);
            return;
        }
        write(file_fd, buffer, bytes);
    }
}

static void handle_stor(client_t *cli, char **cmd, int got)
{
    int file_fd = open(cmd[1], O_CREAT | O_TRUNC | O_WRONLY, 0644);
    pid_t child = 0;

    if (file_fd < 0) {
        send_message_to_client(cli, got, STOR_FILE_ERROR);
        return;
    }
    send_message_to_client(cli, got, STOR_CONNEXION_OK);
    child = fork();
    if (child < 0) {
        send_message_to_client(cli, got, STOR_FILE_ERROR);
        return;
    } else if (child == 0) {
        get_file(cli, got, file_fd);
        exit(SUCCESS);
    }
    send_message_to_client(cli, got, STOR_UPLOAD_OK);
    close(file_fd);
}

void stor(client_t *client, char **command, int got)
{
    if (client[got].is_login == false) {
        send_message_to_client(client, got, NOT_CONNECTED);
        return;
    }
    if (client[got].mode == UNKNOW) {
        send_message_to_client(client, got, MODE_ERROR);
        return;
    }
    if (command[1] == NULL) {
        send_message_to_client(client, got, STOR_PARAMETER_ERROR);
        return;
    }
    handle_stor(client, command, got);
    return;
}
