/*
** EPITECH PROJECT, 2024
** ftp
** File description:
** help
*/

#include <unistd.h>
#include <string.h>

#include "my_ftp.h"
#include "constants.h"

void help(client_t *client, int got)
{
    char all_command[MAX_BUFFER_SIZE] = "USER, PASS, CWD, CDUP, QUIT, DELE";
    char end_display[] = "\r\n";

    strcat(all_command, ", PWD, PASV, PORT, HELP, NOOP, RETR, STOR, LIST.");
    if (client[got].is_login == false) {
        send_message_to_client(client, got, NOT_CONNECTED);
        return;
    }
    send_message_to_client(client, got, HELP);
    send_message_to_client(client, got, all_command);
    send_message_to_client(client, got, end_display);
}
