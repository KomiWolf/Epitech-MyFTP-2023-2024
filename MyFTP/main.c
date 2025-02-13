/*
** EPITECH PROJECT, 2024
** ftp
** File description:
** main
*/

#include <stdbool.h>
#include <sys/stat.h>
#include <stdio.h>
#include <malloc.h>
#include <unistd.h>
#include <string.h>

#include "my_ftp.h"
#include "constants.h"

static bool is_folder(char **av)
{
    struct stat info;

    if (stat(av[2], &info) == -1) {
        fprintf(stderr, STAT_ERR);
        return false;
    }
    if (S_ISDIR(info.st_mode) == false) {
        fprintf(stderr, FOLDER_ERR);
        return false;
    }
    return true;
}

static bool is_argument_correct(int ac, char **av)
{
    if (ac != 3) {
        fprintf(stderr, ARGS_NB_ERR);
        return false;
    }
    for (int i = 0; av[1][i] != '\0'; i++) {
        if (av[1][i] < '0' || av[1][i] > '9') {
            fprintf(stderr, PORT_ERR);
            return false;
        }
    }
    if (is_folder(av) == false) {
        return false;
    }
    chdir(av[2]);
    return true;
}

static void free_all(server_t *server)
{
    free(server->initial_path);
    shutdown(server->server_fd, SHUT_RDWR);
    close(server->server_fd);
}

static int display_helper(void)
{
    puts("USAGE: ./myftp port path");
    puts("\tport\tis the port number on which the server socket listens");
    puts("\tpath\tis the path to the home directory for the Anonymous user");
    return SUCCESS;
}

int main(int ac, char **av)
{
    server_t server;

    if (ac == 2) {
        if (strcmp(av[1], "-h") == 0 || strcmp(av[1], "-help") == 0 ||
            strcmp(av[1], "--h") == 0 || strcmp(av[1], "--help") == 0) {
            return display_helper();
        }
    }
    if (is_argument_correct(ac, av) == false) {
        return ERROR;
    }
    if (init_server(&server, av) == ERROR) {
        return ERROR;
    }
    printf("Serveur address: %s\n", inet_ntoa(server.server_addr.sin_addr));
    server_loop(&server);
    free_all(&server);
    return SUCCESS;
}
