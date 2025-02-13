/*
** EPITECH PROJECT, 2024
** ftp
** File description:
** constants
*/

#ifndef CONSTANTS_H_
    #define CONSTANTS_H_

    // Return value
    #define SUCCESS 0
    #define ERROR 84

    // Value to use in code
    #define MAX_CLIENT 1024
    #define INFINITE_LOOP 1
    #define UNKNOW -1
    #define PASSIVE 1
    #define ACTIVE 2
    #define MAX_BUFFER_SIZE 1024
    #define FUNC_ERROR -1

    // Error message
    #define ARGS_NB_ERR "Error: The program only takes 2 arguments.\n"
    #define STAT_ERR "Error: The file/folder is not recognised.\n"
    #define PORT_ERR "Error: The first argument must be a port.\n"
    #define FOLDER_ERR "Error: The second argument must be a folder.\n"
    #define SOCKET_ERR "Error: Server socket creation failed.\n"
    #define BIND_ERR "Error: Server bind to IP address failed.\n"
    #define LISTEN_ERR "Error: Server listen failed.\n"
    #define SELECT_ERR "Error: Select failed.\n"
    #define ACCEPT_ERR "Error: Accept failed.\n"
    #define READ_ERR "Error: Read command failed.\n"

    //!! Message to client !!//

    // General
    #define NEW_CONNECTION "220 New connection from a new client.\r\n"
    #define MODE_ERROR "425 Connexion mode not selected.\r\n"
    #define UNKNOWN_COMMAND "500 Unknown command.\r\n"
    #define NOT_CONNECTED "530 Need to be connected with USER and PASS.\r\n"

    // USER
    #define NEW_USER "220 New user logged.\r\n"
    #define LOGGED_USER "230 User already logged with USER command.\r\n"
    #define USER_OK "331 User logged with USER command, need password now.\r\n"
    #define USER_ERROR "530 Username is not valid.\r\n"

    // PASS
    #define PASS_OK "230 Password is correct. User logged in.\r\n"
    #define LOGGED_PASS "230 User already logged with PASS command.\r\n"
    #define NEED_USER "332 Need account to set password.\r\n"
    #define PASS_ERROR "530 Password is not correct.\r\n"

    // NOOP
    #define NOOP_OK "200 Noop ok.\r\n"

    // HELP
    #define HELP "214 List of every handled command: "

    // QUIT
    #define QUIT_OK "221 Connexion with server closed.\r\n"

    // PWD
    #define PRINT_PWD "257 Current work directory: "

    // CWD
    #define CWD_OK "250 Directory exists. Changed successfully.\r\n"
    #define CWD_ERROR "550 Directory does not exist.\r\n"

    // CDUP
    #define CDUP_OK "200 Changed to parent directory successfully.\r\n"
    #define CDUP_ERROR "550 Cannot change to parent directory.\r\n"

    // PASV
    #define PASV_OK "227 Passive mode activated.\r\n"
    #define PASV_ERROR "421 Passive mode connexion failed.\r\n"

    // PORT
    #define PORT_OK "200 Port command done successfully.\r\n"
    #define PORT_ERROR "421 Active mode connexion failed.\r\n"
    #define PORT_PARAMETER_ERROR "501 Syntax error in parameters.\r\n"

    // LIST
    #define LIST_OK "150 List of every file and folder: \r\n"
    #define LIST_ERROR "450 List command failed.\r\n"

    // RETR (Downloading a file from the server)
    #define RETR_CONNEXION_OK "150 Connected successfully.\r\n"
    #define RETR_DOWNLOAD_OK "226 File downloaded successfully.\r\n"
    #define RETR_PARAMETER_ERROR "501 Does not found the file parameter.\r\n"
    #define RETR_FILE_ERROR "550 Failed to retrieve file.\r\n"

    // DELE (Delete a file in the server)
    #define DELE_OK "250 File deleted successfully.\r\n"
    #define DELE_PARAMETER_ERROR "501 Does not found the file parameter.\r\n"
    #define DELE_FILE_ERROR "550 Failed to delete file.\r\n"

    // STOR (Upload a file to the server)
    #define STOR_CONNEXION_OK "150 Connected successfully.\r\n"
    #define STOR_UPLOAD_OK "226 File uploaded successfully.\r\n"
    #define STOR_PARAMETER_ERROR "501 Does not found the file parameter.\r\n"
    #define STOR_FILE_ERROR "550 Failed to upload file.\r\n"

#endif
