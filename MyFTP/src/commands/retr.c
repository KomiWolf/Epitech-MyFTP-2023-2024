/*
** EPITECH PROJECT, 2024
** ftp
** File description:
** retr
*/

#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <stdlib.h>

#include "my_ftp.h"
#include "constants.h"

static void send_file(client_t *cli, int got, int file_fd)
{
    char buffer[5000];
    ssize_t bytes = 0;

    while (true) {
        memset(buffer, '\0', sizeof(buffer) - 1);
        bytes = read(file_fd, buffer, sizeof(buffer) - 1);
        if (bytes < 0) {
            send_message_to_client(cli, got, RETR_FILE_ERROR);
            close(file_fd);
            exit(ERROR);
        }
        if (bytes == 0) {
            close(file_fd);
            return;
        }
        send_message_to_client(cli, got, buffer);
    }
}

static void handle_retr(client_t *cli, char **cmd, int got)
{
    int file_fd = open(cmd[1], O_RDONLY);
    pid_t child = 0;

    if (file_fd < 0) {
        send_message_to_client(cli, got, RETR_FILE_ERROR);
        return;
    }
    send_message_to_client(cli, got, RETR_CONNEXION_OK);
    child = fork();
    if (child < 0) {
        send_message_to_client(cli, got, RETR_FILE_ERROR);
        return;
    } else if (child == 0) {
        send_file(cli, got, file_fd);
        exit(EXIT_SUCCESS);
    }
    send_message_to_client(cli, got, RETR_DOWNLOAD_OK);
    close(file_fd);
    return;
}

void retr(client_t *client, char **command, int got)
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
        send_message_to_client(client, got, RETR_PARAMETER_ERROR);
        return;
    }
    handle_retr(client, command, got);
}
