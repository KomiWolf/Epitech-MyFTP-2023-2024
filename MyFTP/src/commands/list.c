/*
** EPITECH PROJECT, 2024
** ftp
** File description:
** list
*/

#include <unistd.h>
#include <string.h>
#include <malloc.h>
#include <dirent.h>
#include <sys/stat.h>

#include "my_ftp.h"
#include "constants.h"

static void send_folder_content(DIR *dir, client_t *cli, int got)
{
    struct dirent *content = NULL;
    char str[MAX_BUFFER_SIZE];
    struct stat info;

    while (true) {
        content = readdir(dir);
        if (content == NULL)
            break;
        if (content->d_name[0] == '.')
            continue;
        strcpy(str, "150 ");
        strcat(str, content->d_name);
        stat(content->d_name, &info);
        if (S_ISDIR(info.st_mode) == true) {
            strcat(str, " -> Folder\r\n");
        } else {
            strcat(str, " -> File\r\n");
        }
        send_message_to_client(cli, got, str);
    }
}

static void handle_list(client_t *cli, int got)
{
    DIR *directory = NULL;

    directory = opendir(cli->server_path);
    if (directory == NULL) {
        return send_message_to_client(cli, got, LIST_ERROR);
    }
    send_folder_content(directory, cli, got);
    closedir(directory);
}

void list(client_t *client, int got)
{
    if (client[got].is_login == false) {
        send_message_to_client(client, got, NOT_CONNECTED);
        return;
    }
    if (client[got].mode == UNKNOW) {
        send_message_to_client(client, got, MODE_ERROR);
        return;
    }
    handle_list(client, got);
}
