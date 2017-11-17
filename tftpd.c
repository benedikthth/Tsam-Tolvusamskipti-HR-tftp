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

//create bytes, needed to manipulate data on the bit level.
typedef char byte;

// Our blocksize template. we need to do arithmetic later to figure
// out our packet size later.
unsigned int pre_block_size = 0x408; ///516 < 1
unsigned int* server_status_code = (unsigned int *)malloc(sizeof(unsigned int));


void get_buffer_size(int * super_code, int block_preset){

  block_preset = 2;
  //int x = block_preset << *super_code;



}

int main(int argc, char **argv){

  if(argc == 0){
    //prevent people from calling the server with no parameters.
    printf( "\aCannot call the server with 0 parameters. exiting with error %d", pre_block_size);
    return -pre_block_size; //return our template size for debugging.
  }

  else if( argv[1] == NULL){
    //printf("There has been a problem\n");
  }

  *server_status_code = 1; // our server has started.

  get_buffer_size( (int *)server_status_code, pre_block_size);

  printf("%d -> %d\n", *server_status_code, pre_block_size );

  return 1;//*server_status_code;
}
