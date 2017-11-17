CC= gcc
CFLAGS = -std=c11 -D_XOPEN_SOURCE=700 -O2 -Wall -Wextra -Wformat=2 -Wno-int-conversion
CPPFLAGS =
SIGSEV = `echo`

# <COMMAND>: ~;
default: all
all: tftpd


# ;~ </COMMAND>
