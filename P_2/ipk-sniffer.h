// Authors: Dominik Pop
// Login: xpopdo00, <xpopdo00@stud.fit.vutbr.cz>
// VUT FIT, 2 BIT, summer semestr
// Date: 29.3.2021
// Second project for IPK -> packet sniffer

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include <ctype.h>
#include <errno.h>

#include <pcap.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define ETHERNET_SIZE 14
#define ETHERNET_ADDRESS 6
#define SNAP_LEN 1518

#define ARG_LEN 20
#define FILTER_LEN 100

void help_function();

void print_interfaces();

bool check_interface(char *name);

int parse_arguments(int argc, char **argv);

void start_capture();

void process_ethernet();

void process_ip();

void process_tcp();

void process_udp();

void process_arp();

void process_icmp();

void print_info();