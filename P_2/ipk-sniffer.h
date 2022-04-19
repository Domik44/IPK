/**
 * @author Dominik Pop, xpopdo00
 * @date 29.3.2021
 * 
 * @brief Header file for ipk-sniffer.c describing functions, structures, defines, ... 
 * 
 * VUT FIT, 2 BIT
 * <xpopdo00@stud.fit.vutbr.cz>
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include <time.h>
#include <ctype.h>
#include <errno.h>

#include <pcap.h>
#include <netinet/ether.h>
#include <netinet/if_ether.h>
#include <netinet/ip.h>
#include <netinet/ip6.h>
#include <netinet/tcp.h>
#include <netinet/udp.h>


// DEFINES

#define ARG_LEN 20

#define ETHERNET_SIZE 14
#define ETHERNET_ADDRESS 6
#define SNAP_LEN 1518

#define FILTER_LEN 100

#define MAC_LEN 20
#define IP_LEN 40
#define TIME_LEN 50

#define DATE_FORMAT 20
#define MILISECONDS 6
#define TIME_ZONE 3

#define ARP 84
#define ICMP 1
#define TCP 6
#define UDP 17

#define TYPE_IP 10

// STRUCTURES

/**
 * @brief Structure for storing user input arguments
 * 
 */
typedef struct Args{
    char interface[ARG_LEN];
    char port[ARG_LEN];
    bool tcp;
    bool udp;
    bool arp;
    bool icmp;
    int number_packets;
}t_Args;


// FUNCTIONS

/**
 * @brief Constructor for argument structure
 * 
 * @return t_Args Rerturns allocated argument
 */
t_Args ctor_Args();

/**
 * @brief Function prints help instruction on stdout
 * 
 */
void help_function();

/**
 * @brief Function for parsing and storing arguments
 * 
 * @param argc Number of input arguments
 * @param argv String array of input arguments
 * @return int Returns number of boolean arguments from input
 */
int parse_arguments(int argc, char **argv, t_Args *args);

/**
 * @brief Function finds all interfaces and stores them into devices variable
 * 
 * @param devices List that strores all interfaces
 */
void get_interfaces(pcap_if_t **devices);

/**
 * @brief Function prints all interfaces to stdout
 * 
 */
void print_interfaces();

/**
 * @brief Function checks if given interface is available
 * 
 * @param name Interface we are looking for
 * @return true If interface was found
 * @return false If interface wasnt found
 */
bool check_interface(char *name);

/**
 * @brief Function for creating filter
 * 
 * @param filter Stores created filter
 */
void create_filter(char *filter, int bool_counter, t_Args *args);

/**
 * @brief Callback function used for handling recieved packets
 * 
 * @param arguments User arguments -> NULL for our project
 * @param packet_header Packet header storing packet information
 * @param data String containing packet data
 */
void sniffer_callback(u_char *arguments, const struct pcap_pkthdr *packet_header, const u_char *data);

/**
 * @brief Function prints basic packet info on stdout
 * 
 * @param time   Timestamp
 * @param source String containing source MAC address
 * @param dest   String containing destination MAC address
 * @param len    Number containing length of packet in bytes
 * @param protocol_type Number representing protocol type
 */
void print_basic_info(char *time, char *source, char *dest, int len, int protocol_type);

/**
 * @brief Override for ntoa function, it doesnt delete first 0
 * 
 * @param buffer String used for formating MAC address
 * @param address Contains MAC address
 * @return Returns string containing formated MAC address
 */
char *ether_ntoa_override(char* buffer, struct ether_addr* address);

/**
 * @brief Fucntion gets important information about TCP packet
 * 
 * @param data String containing packet data
 * @param ip_header_len Length of ip header
 */
void process_tcp(const u_char *data ,int ip_header_len);

/**
 * @brief Fucntion gets important information about UDP packet
 * 
 * @param data String containing packet data
 * @param ip_header_len Length of ip header
 */
void process_udp(const u_char *data, int ip_header_len);

/**
 * @brief 
 * 
 */
void process_arp();

/**
 * @brief 
 * 
 */
void process_icmp();
