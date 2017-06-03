    #include "trabalho3_SO.h"

int main(){		
    socket_t *p;
    int n_bytes;
    
    p=socket_init_client(LOCALHOST, DEFAULT_PORT);
    printf("Insert (city,county acronym)!!\n");
    
    while ( fgets(p->buffer, sizeof(p->buffer), stdin) != NULL ) {
      
        if ( strcmp(p->buffer, ".\n") == 0 ) break;
        
        if ( socket_write(p, p->buffer, strlen(p->buffer)) < 0 )
            FatalErrorSystem("Error on write");
        printf("\n");
        printf("\n");
       
        if ( (n_bytes = socket_read(p,p->buffer, DIM_BUFFER)) < 0 )
            FatalErrorSystem("Error on read");
        p->buffer[n_bytes] = '\0';
        
        printf("%s", p->buffer);
        
        
        printf("\n");
        printf("\n");
        fflush(stdout);
    } 
   
    socket_close(p);
    return EXIT_SUCCESS;
}
