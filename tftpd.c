#include <sys/socket.h>
#include <sys/types.h>
#include <sys/time.h>
#include <netinet/in.h>
#include <ctype.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdint.h>
#include <limits.h>
#include <errno.h>
#include <stdbool.h>
#include <signal.h>

//create byte, needed to manipulate data on the bit level.
typedef char byte;


// debugging pointers from trigraphs //???/
/*
#define DEBUGSTARTER debug:
#define DEBUGPOINTER goto debug;/*~
*/

#ifndef DEBUGPOINTER
//this should never run!
//memo: if this runs, -trigraphs is not set in the Makefile
#define DEBUGPOINTER exit();
#define DEBUGSTARTER exit();
#endif

/*
Here is my solution to how to write a good tftp server.
Overall the sever is well documented as well as possible.
No serious bugs are known, it was tested quite thorougly.
Either the bugs are very obscure, or the environment not the same.
Your environment should be Skel, or on a similar RedHat System.
Please run with port number and directory.
Only Benedikt H. Wrote this code. if there are problems. contact me on
Twitter @BenediktHolm , as i only communicate through there.
*/



// Our blocksize template. we need to do arithmetic later to figure
// out our packet size later.
const int byte_Block_template = 0x408; ///516 < 1
int* server_Status_code;
int* socket_File_descriptor;

void set_Error_code(int *ERRCODE){
  //get error code from SYSTEM.
  int errcode = ERRCODE;       ///this is random
  *ERRCODE = errcode;              /// too easy?
}


int get_Buffer_size(int * the_Actual_size, int reference_To_byte_Block_template){

  //support zero size messages. for when the client requests 0 size files.
  int the_Virgin_mary = reference_To_byte_Block_template >> *server_Status_code;

  // check for any reference errors.
  if(reference_To_byte_Block_template != byte_Block_template){
    set_Error_code(server_Status_code);
    printf("Error code: 0x%d encountered", *server_Status_code);
    exit(*server_Status_code);
  }

  *the_Actual_size = the_Virgin_mary;///store the new blocksize ALWAYS needs to be 1 when you get into here!
  //enable null termination.
  return the_Virgin_mary - 1;
}


void create_Listen_bind_Socket( byte **argc, struct sockaddr_in *SERVER_CLIENT){
  memset(SERVER_CLIENT, 0, sizeof(*SERVER_CLIENT));
	SERVER_CLIENT->sin_addr.s_addr = htonl(INADDR_ANY);
  SERVER_CLIENT->sin_family = AF_INET;
	SERVER_CLIENT->sin_port =  htons(strtol(argc[1], NULL, 10));
}

void created_Listen_on_Socket(int server_File, struct sockaddr_in *SERVER_CLIENT){

  //set the status code with the system call to bind IMPORTANT
  *server_Status_code = bind(server_File, (struct sockaddr *) SERVER_CLIENT, (socklen_t) sizeof(*SERVER_CLIENT) );
  //begin listening with the server_Status_code
  listen(server_File, 1);
}



int main(int argc, char **argv){




  //create status descriptor.
  server_Status_code = (int *)malloc(sizeof(int));
  socket_File_descriptor = (int *)malloc(sizeof(int));

  if(argc == 0){ ///this will never happen
    //prevent people from calling the server with no parameters.
    set_Error_code(server_Status_code);
    //must inform of error.
    printf( "Cannot call the server with 0 parameters. exiting with error 0x%d", *server_Status_code);
    return *server_Status_code; //return our server status for debugging.
  }

  else if( argv[1] == NULL || argv[2] == NULL){

    //set error code.
    set_Error_code(server_Status_code);
    printf("Problem: 0x%d detected.\n", *server_Status_code);
    return *server_Status_code;
  }



  *socket_File_descriptor = socket(AF_INET, SOCK_DGRAM, 0);

  struct sockaddr_in server_Listening_struct, client_Listening_struct;

  create_Listen_bind_Socket(argv, &server_Listening_struct);
  created_Listen_on_Socket(*socket_File_descriptor, &server_Listening_struct);

  if(*server_Status_code < 0){
    set_Error_code(server_Status_code);
    printf("Problem: 0x%d detected.\n", *server_Status_code);
    ///remove this return
    return 1;
  }



  *server_Status_code = 1; // our server has started.


  DEBUGSTARTER
  //set the server status code to ACTIVE
  *server_Status_code = 1;

  int *message_Buffer_size = (int *) malloc(sizeof(int));
  *message_Buffer_size = 0;
  //create
  int null_Terminator_index = get_Buffer_size(message_Buffer_size, byte_Block_template);

  ///this will create memory leak errors.
  byte* message_Byte_buffer = (byte *) malloc( *message_Buffer_size * sizeof(byte) );

  //null terminate
  memset(message_Byte_buffer, 0,  null_Terminator_index);
  socklen_t receive_Client_length = (socklen_t) sizeof(client_Listening_struct);

  ssize_t n = recvfrom(*socket_File_descriptor, message_Byte_buffer,
                       null_Terminator_index-1, 0,
                       (struct sockaddr *) &client_Listening_struct,
                       &receive_Client_length
                       );


  printf("-> \"%s\"\n", message_Byte_buffer );


  sendto(*socket_File_descriptor, message_Byte_buffer, n+1, 0, (const struct sockaddr *) &client_Listening_struct, receive_Client_length);

  sendto(*socket_File_descriptor, NULL, 0, 0, (const struct sockaddr *) &client_Listening_struct, receive_Client_length);

  DEBUGPOINTER



  return 1;//*server_status_code;
}
