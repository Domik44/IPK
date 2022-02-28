// Authors: Dominik Pop
// VUT FIT, 2 BIT, summer semestr
// Date: 11.2.2021
// First project for IPK -> creating server communicating with HTTP

// For basic operations
#include <stdlib.h>
#include <stdio.h>

// For operations with strings, loop conditions, ..
#include <unistd.h>
#include <ctype.h>
#include <string.h>

// For creating server
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>

#define NAME_MAX 253 // Max len of hostname in linux
#define BUFFER_MAX 3000 // Should be enough for testing purposes
// Technically we need only the first line of HTTP request

/**
 * @brief Structure for storing cpu computing times
 *  
*/
typedef struct{
    unsigned long user;
    unsigned long nice;
    unsigned long sys;
    unsigned long idle;
    unsigned long iowait;
    unsigned long irq;
    unsigned long softirq;
    unsigned long steal;
    unsigned long guest;
    unsigned long guest_n;
}t_CPU;

/**
 * @brief Hostname detection function
 * 
 */
void get_hostname();

/**
 * @brief CPU name detection function
 * 
 */
void get_cpu_name();

/**
 * @brief Function for loading cpu computing times
 * 
 */
void load_params(t_CPU *cpu);

/**
 * @brief Function computes cpu usage from 2 reads
 * @return CPU usage in %
 */
double compute_usage(t_CPU *read_1, t_CPU *read_2);

/**
 * @brief CPU usage computing function
 * @return Returns CPU usage in %
 */
double cpu_usage();