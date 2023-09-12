#include<stdio.h>
#include<fcntl.h>
#include<stdlib.h>
#include<string.h>
#include <dirent.h>
#include <sys/wait.h>
#include <assert.h>
#include <netdb.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h> // read(), write(), close()
#define SA struct sockaddr
#include <arpa/inet.h>
#include <signal.h>
#include <sys/un.h>
#define MAX 1024 


int StartsWith(const char *a, const char *b)
{
   if(strncmp(a, b, strlen(b)) == 0) return 1;
   return 0;
}

int EndsWith(const char *str, const char *suffix)
{
    if (!str || !suffix)
        return 0;
    size_t lenstr = strlen(str);
    size_t lensuffix = strlen(suffix);
    if (lensuffix >  lenstr)
        return 0;
    return strncmp(str + lenstr - lensuffix, suffix, lensuffix) == 0;
}

char** str_split(char* a_str, const char a_delim)
{   
    if(EndsWith(a_str, "\n") != 0){
        a_str[strlen(a_str)-1] = '\0';
    }

    char** result    = 0;
    size_t count     = 0;
    char* tmp        = a_str;
    char* last_comma = 0;
    char delim[2];
    delim[0] = a_delim;
    delim[1] = 0;

    /* Count how many elements will be extracted. */
    while (*tmp)
    {
        if (a_delim == *tmp)
        {
            count++;
            last_comma = tmp;
        }
        tmp++;
    }

    /* Add space for trailing token. */
    count += last_comma < (a_str + strlen(a_str) - 1);

    /* Add space for terminating null string so caller
       knows where the list of returned strings ends. */
    count++;

    result = malloc(sizeof(char*) * count);

    if (result)
    {
        size_t idx  = 0;
        char* token = strtok(a_str, delim);

        while (token)
        {
            assert(idx < count);
            *(result + idx++) = strdup(token);
            token = strtok(0, delim);
        }
        assert(idx == count - 1);
        *(result + idx) = 0;
    }

    return result;
}

void parse(char *line, char **argv)
{   
    if(EndsWith(line, "\n") != 0){
        line[strlen(line)-1] = '\0';
    }
    
    // Extract the first token
    char * token = strtok(line, " ");
    // loop through the string to extract all other tokens
    int i=0;
    while( token != NULL ) {
        argv[i] = token;
        token = strtok(NULL, " ");
        i++;
    }
    argv[i] = NULL;
    for(int j = 0; j<i; j++){
    }
}

void parse_arrow1(char *line, char **argv)
{   
    if(EndsWith(line, "\n") != 0){
        line[strlen(line)-1] = '\0';
    }
    
    // Extract the first token
    char * token = strtok(line, ">");
    // loop through the string to extract all other tokens
    int i=0;
    while( token != NULL ) {
        argv[i] = token;
        token = strtok(NULL, ">");
        i++;
    }
    argv[i] = NULL;
    for(int j = 0; j<i; j++){
    }
}

void parse2(char *line, char **argv)
{   
    if(EndsWith(line, "\n") != 0){
        line[strlen(line)-1] = '\0';
    }
    
    // Extract the first token
    char * token = strtok(line, "|");
    int i=0;
    while( line != NULL ) {
        
        argv[i] = token;
        token = strtok(line, "|");
        i++;
    }
    argv[i] = NULL;
    for(int j = 0; j<i; j++){
    }
}

int check_arrow1(char *line){
    for(int i=0;i<strlen(line);i++){
        if(line[i] == '>'){
            return 1;
        }
    }
    return 0;
}

int check_arrow2(char *line){
    for(int i=0;i<strlen(line);i++){
        if(line[i] == '<'){
            printf("1\n");
            return 1;
        }
    }
    printf("0\n");
    return 0;
}

int run_linux_command(char **line){
    
    pid_t pid = fork();
    if (pid == 0){
        char* command = line[0];
        char command_path[100] = "/bin/";
        strcat(command_path, command);
        execv(command_path, line);                
        exit(0);
    }
    wait(NULL);
}

void command_to_file(char *line){
    char * commands[1000];
    parse_arrow1(line, commands);

    int commands_counter;
    int outfd = open(commands[1], O_CREAT | O_WRONLY | O_TRUNC, 0644);
    if (outfd == -1) {
    }

    char* p[1000][2];
    for(commands_counter=0; *(commands + commands_counter); commands_counter++){
        parse(*(commands + commands_counter), p[commands_counter]);
    }

    pid_t pid = fork();
    if (pid == 0){
        dup2(outfd, 1); // make stdout go to file
        close(outfd);
        run_linux_command(p[0]);
        exit(0);
    }
    wait(NULL);
}

int parse_by_pipe(char *line, char **commands)
{   
    if(EndsWith(line, "\n") != 0){
        line[strlen(line)-1] = '\0';
    }
    char * token = strtok(line, "|");
    // loop through the string to extract all other tokens
    int i=0;
    while( token != NULL ) {
        commands[i] = token;
        token = strtok(NULL, "|");
        i++;
    }
    for(int j = 0; j<i; j++){
    }
    return i;
}

void slice(const char *str, char *result, size_t start, size_t end)
{
    strncpy(result, str + start, end - start);
}

int check_my_server(char* buffer){
    if(StartsWith(buffer, "{")){return 1;}
    else{ return 0; }
}

void run_my_server(char* buffer){
    
    char port[4] = {0};
    slice(buffer, port, 2, strlen(buffer));
    int portNumber = atoi(port);
    int sockfd, connfd, len;
    struct sockaddr_in servaddr, cli;
    char buff[10000] = {0};
    // socket create and verification
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == -1) {
        exit(0);
    }
    else
    bzero(&servaddr, sizeof(servaddr));
   
    // assign IP, PORT
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(portNumber);
   
    // Binding newly created socket to given IP and verification
    if ((bind(sockfd, (SA*)&servaddr, sizeof(servaddr))) != 0) {
        exit(0);
    }   
    // Now server is ready to listen and verification
    if ((listen(sockfd, 5)) != 0) {
        exit(0);
    }
    else

    len = sizeof(cli);
   
    // Accept the data packet from client and verification
    connfd = accept(sockfd, (SA*)&cli, &len);
    if (connfd < 0) {
        exit(0);
    }

    read(connfd, buff, sizeof(buff));
    printf("%s",buff);

   
    // After chatting close the socket
    close(sockfd);
}


int check_my_client(char * buffer){

    // if }
    char* ch_loc = strchr(buffer, '}');
    if(ch_loc == NULL){

        return 0;
    }
    else{
        int index = (int)(ch_loc - buffer);
        return index;
    }
} 

void run_my_client(char * buffer, int index){

    // get command
    char command[1024] = {0};
    slice(buffer, command, 0, index-1);
    
    // get ip + port
    char ip_and_port[100] = {0};
    slice(buffer, ip_and_port, index+2, strlen(buffer)-1);
    char ip[100] = {0};
    char port[6] = {0};
    int end_ip_index = (int)(strchr(ip_and_port, ':') - ip_and_port);
    slice(ip_and_port, ip, 0, end_ip_index);
    slice(ip_and_port, port, end_ip_index+1, strlen(ip_and_port));

     // make command to file:
    size_t size = strlen(command);
    command[size] = ' ';
    command[size+1] = '>';
    command[size+2] = ' ';
    command[size+3] = 't';
    command[size+4] = 'm';
    command[size+5] = 'p';
    command[size+6] = 'p';
    command[size+7] = 'p';
    command[size+8] = '.';
    command[size+9] = 't';
    command[size+10] = 'x';
    command[size+11] = 't';
    
    if(StartsWith(command, "DIR")){
        struct dirent *pDirent;
        DIR *pDir;
        pDir = opendir("./");
        char str[10000] = {0};
        while ((pDirent = readdir(pDir)) != NULL) {
            strcat(str,pDirent->d_name);
            strcat(str,"\n");
        }
        // Close directory and exit.
        closedir (pDir);
        int fd_write_file = open("tmppp.txt", 'a',S_IRUSR | S_IWUSR);
        write(fd_write_file, str, strlen(str));
        close(fd_write_file);
    }
    else{
        system(command);
    }

    // send file data via socket:
    int port_number = atoi(port);
    char * buffer_to_send = 0;
    long length;
    FILE * f = fopen ("tmppp.txt", "rb");

    if (f)
    {
    fseek (f, 0, SEEK_END);
    length = ftell (f);
    fseek (f, 0, SEEK_SET);
    buffer_to_send = malloc (length);
    if (buffer_to_send)
    {
        fread (buffer_to_send, 1, length, f);
    }
        fclose (f);
    }
        // char buffer[MAX] = {0};
        int n = 0;
        int sockfd, connfd;
        struct sockaddr_in servaddr, cli;
 
        // socket create and verification
        sockfd = socket(AF_INET, SOCK_STREAM, 0);
        if (sockfd == -1) {
            exit(0);
        }
        else
            bzero(&servaddr, sizeof(servaddr));
    
        // assign IP, PORT
        servaddr.sin_family = AF_INET;
        servaddr.sin_addr.s_addr = inet_addr(ip);
        servaddr.sin_port = htons(port_number);
    
        // connect the client socket to server socket
        if (connect(sockfd, (SA*)&servaddr, sizeof(servaddr))
            != 0) {
            exit(0);
        }
        else
            write(sockfd, buffer_to_send, strlen(buffer_to_send));
            close(sockfd);
            system("rm -f tmppp.txt");

}




int main(int argc, char *argv[]){

    int nread = 0;
    int done = 0;
    while(done != 1) {
    
        printf(">");
        fflush(stdout);

        char buffer[1024] = {0};
        while (read(STDIN_FILENO, buffer, 1024) == 0)
        {
            
        }
        char original_buffer[1024] = {0};
        strcpy(original_buffer, buffer);

        char original_buffer2[1024] = {0};
        strcpy(original_buffer2, buffer);

        char * line[100];
        parse(buffer, line);
        
        char ** commands;       
        commands = str_split(original_buffer, '|');
        char ** commands_original = commands;       
        int commands_counter;
        char* p[1000][20];
        for(commands_counter=0; *(commands + commands_counter); commands_counter++){
            parse(*(commands + commands_counter), p[commands_counter]);
        }
        
        int index = check_my_client(original_buffer2);
        if(index != 0){
            run_my_client(original_buffer2, index);
        }
        else if(strcmp(line[0], "DIR") == 0){
            struct dirent *pDirent;
            DIR *pDir;
            pDir = opendir("./");
            while ((pDirent = readdir(pDir)) != NULL) {
                printf ("%s\n", pDirent->d_name);
            }
            closedir (pDir);
        }
        
        else if(strcmp(line[0], "COPY") == 0){

            char *copy_command = line[0];
            char *src = line[1];
            char *dst = line[2];

            int fd_read_file = open(src, 'r');
            int fd_write_file = open(dst, 'a',S_IRUSR | S_IWUSR);
            if (fd_read_file == -1 || fd_write_file == -1)
            {   
                printf("Usage : copy <file1> <file2>\n");
            }

            int size_read;
            char *data = (char *) calloc(1, sizeof(char));

            size_read = read(fd_read_file, data, 1);
            while( size_read != 0 ){
                write(fd_write_file, data, size_read);
                size_read = read(fd_read_file, data, 1);
            }
            
            int result1 = close(fd_read_file);
            int result2 = close(fd_write_file);

            if(result1 != 0 || result2 != 0){
                printf("Usage : copy <file1> <file2>\n");
            }else{
                printf("file is copied\n");
            }
        }
        else{
            
            if(check_my_server(original_buffer2)){
                while(1){
                    run_my_server(original_buffer2);
                }
                
            }
            else if(strchr(original_buffer2, '<') != NULL || strchr(original_buffer2, '>') != NULL || 1){
                system(original_buffer2);
            }
            else if(commands_counter == 1){
                pid_t pid = fork();
                if (pid == 0){
                    run_linux_command(p[0]);
                    exit(0);
                }
                wait(NULL);
            }
            else{                
                int fd[2];
                pid_t pid;
                pid_t pid2;
                if (pipe(fd) == -1) {
                    perror("pipe failed");
                    exit(1);
                }

                pid = fork();
                if (pid == -1) {
                    perror("fork failed");
                    exit(1);
                }
                if (pid == 0) {
                    // fflush(stdout);
                    close(fd[0]);
                    dup2(fd[1], STDOUT_FILENO);
                    close(fd[1]);
                    printf("here\n");
                    run_linux_command(p[0]);
                    exit(0);
                    perror("execlp failed");
                } else {
                    wait(NULL);
                    close(fd[1]);
                    dup2(fd[0], STDIN_FILENO);
                    close(fd[0]);
                    run_linux_command(p[1]); 
                    close(fd[0]);
                    close(fd[1]);
                    exit(0);
                }
                if(pid == 0){
                }
            }            
        }
    }
    
    return 1;
}