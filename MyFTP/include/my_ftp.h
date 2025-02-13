/*
** EPITECH PROJECT, 2024
** ftp
** File description:
** my_ftp
*/

#ifndef MY_FTP_H_
    #define MY_FTP_H_

    #include "struct.h"

// Init
int init_server(server_t *serv, char **av);
client_t *init_client_list(void);

// Loop
void server_loop(server_t *server);

// Client management
void add_new_client(client_t *client, server_t *server, const int fd);
int get_client(client_t *client, int fd);
void delete_client(client_t *client, const int fd);

// Command handling
void command_handling(client_t *client, server_t *server, int i);
void do_command(client_t *cli, server_t *server, char **command, int got);

// Commands utils
void send_message_to_client(client_t *client, int got, char *msg);

// Commands
void user(client_t *client, char **command, int got);
void pass(client_t *client, char **command, int got);
void noop(client_t *client, int got);
void help(client_t *client, int got);
void quit(client_t *client, server_t *server, int got);
void pwd(client_t *client, int got);
void cwd(client_t *client, server_t *server, char **command, int got);
void cdup(client_t *client, server_t *server, int got);
void pasv(client_t *client, int got);
void port(client_t *client, char **command, int got);
void list(client_t *client, int got);
void retr(client_t *client, char **command, int got);
void dele(client_t *client, char **command, int got);
void stor(client_t *client, char **command, int got);

#endif
