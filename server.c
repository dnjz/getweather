#include "trabalho3_SO.h"

int get_weather(char *c, char *d){

    char *cmd[]={"./getweather","-l",c,"-p",d,NULL};
    so_popen_t*sp=so_popen(cmd, "r");
    if (sp<0){ 
        perror("so_popen"); exit(-2);
    }
    int fdout = open("newweather.txt", O_CREAT | O_WRONLY | O_TRUNC, 0644);
    if (fdout < 0) { perror("Open File"); exit(-1); }
    char buf[512];
    ssize_t nBytes;
    int retval = 0;
    while ((nBytes =so_pread(sp,buf,sizeof(buf)))>0){
        if (write(fdout,buf,nBytes)<0) {
            perror("write");
            retval = -3;
            break;
        }
        if (nBytes < 0) {perror("so_pread"); retval = -4;}
    }
    close(fdout);
    return retval;
}

char* break_city(char *c){
    char *p;
    p=strtok(c,",");
    return p;
}
char* break_ACR(char*c){
	 char *w;
	 w=strtok(c,",");
	 char p = w[0];
	 w=strtok(NULL,"\n");
	 return w;
}

char* read_fileweather(){
    char *source = NULL;
    FILE *fp = fopen("newweather.txt", "r");
    if (fp != NULL) {
        if (fseek(fp, 0L, SEEK_END) == 0) {

            long bufsize = ftell(fp);
    if (bufsize == -1) { /* Erro */ }

            source = malloc(sizeof(char) * (bufsize + 1));

    if (fseek(fp, 0L, SEEK_SET) != 0) { /* Error */ }

            size_t newLen = fread(source, sizeof(char), bufsize, fp);
            if ( ferror( fp ) != 0 ) {
                fputs("Error reading file", stderr);
            } 
            else {
                source[newLen++] = '\0';
            }
        }
        fclose(fp);

    }
    return source;
}

void * threadRotine (void *args){
    int n_bytes;
    socket_t *p2=(socket_t*)args;

    while ( (n_bytes = socket_read(p2, p2->buffer, DIM_BUFFER)) != 0 ) {
        if ( n_bytes < 0 )
            FatalErrorSystem("Error on read");

        p2->buffer[n_bytes] = '\0';
        char *str1,*str2,*aux;
        aux=p2->buffer;
        
        str1=break_city(p2->buffer);
        str2=break_ACR(aux);
      
        get_weather(str1,str2);
        char *read;
        read=read_fileweather();

        if ( socket_write(p2, read, strlen(read)) < 0 )
            
        if (strcmp(p2->buffer, "..\n") == 0) 
            break;

    } 
        socket_close(p2);
        pthread_exit(NULL);
     return NULL;
}


int main(){	

    socket_t *p,*p2;
    pthread_t threads;
    
    p=socket_init_server(DEFAULT_PORT);
    for(;;){
        printf("Waiting for conection...\n");
        p2=socket_accept(p);
        pthread_create( &threads, NULL, threadRotine, (void*)p2);
    }   
    socket_close(p);
return 0;
}