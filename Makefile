CC= gcc
CFLAGS = -std=c11 -trigraphs -D_XOPEN_SOURCE=700 -O2 -Wall -Wextra -Wformat=2 -Wno-trigraphs -Wno-int-conversion
WARN = -Wno-comment


all:
	$(CC) $(CFLAGS) $(WARN) tftpd.c -o tftpd

tftpd:
	all

default:
	tftpd
