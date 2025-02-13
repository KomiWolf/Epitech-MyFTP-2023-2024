/*
** EPITECH PROJECT, 2024
** ftp
** File description:
** struct
*/

#ifndef STRUCT_H_
    #define STRUCT_H_

    #include <arpa/inet.h>
    #include <sys/select.h>
    #include <stdbool.h>

// Server structure
typedef struct server_s {
    int server_fd;
    int client_fd;
    struct sockaddr_in server_addr;
    struct sockaddr_in client_addr;
    int port;
    char *initial_path;
    fd_set current_fd;
    fd_set ready_fd;
} server_t;

// Client structure
typedef struct client_s {
    int id;
    bool is_login;
    int connexion;
    char *server_path;
    int mode;
    int port;
    bool has_username;
} client_t;

#endif
