// Authors: Dominik Pop
// Login: xpopdo00, <xpopdo00@stud.fit.vutbr.cz>
// VUT FIT, 2 BIT, summer semestr
// Date: 29.3.2021
// Second project for IPK -> packet sniffer - ZETA

#include "ipk-sniffer.h"

// FUCNTIONS

// Interfaces

void get_interfaces(pcap_if_t **devices){
    char error_buffer[PCAP_ERRBUF_SIZE];
    bool find = pcap_findalldevs(devices, error_buffer) == -1 ? false : true;
    if(!find){
        fprintf(stderr, "Error pcap_findalldevs! Output: %s\n", error_buffer);
        exit(-1);
    }
}

void print_interfaces(){
    pcap_if_t *devices, *devices_list;
    get_interfaces(&devices);

    for(devices_list = devices; devices_list; devices_list=devices_list->next)
        fprintf(stdout, "%s\n", devices_list->name);
}

bool check_interface(char *name){
    pcap_if_t *devices, *devices_list;
    get_interfaces(&devices);

    for(devices_list = devices; devices_list; devices_list=devices_list->next)
        if(strcmp(devices_list->name, name) == 0)
            return true;

    return false;
}

// Parsing

int parse_arguments(int argc, char **argv, t_Args *args){
    if(argc <= 2){
        if(strcmp(argv[1], "-h") == 0 || strcmp(argv[1], "--help") == 0){
            help_function();
        }
        else{
            print_interfaces();
            exit(0);
        }
    }

    int boolean_counter = 0;
    for(int i = 1; i < argc; i++){
        if(strcmp(argv[i], "-i") == 0 || strcmp(argv[i], "--interface") == 0){
            if(i + 1 == argc){
                fprintf(stderr, "Error! Not enough arguments!\n");
                exit(-1);
            }
            strcpy(args->interface, argv[i+1]);
            if(!check_interface(args->interface)){
                fprintf(stderr, "Error! Interface not found!\n");
                exit(-1);
            }
            i++;
        }
        else if(strcmp(argv[i], "-p") == 0){
            if(i + 1 == argc){
                fprintf(stderr, "Error! Not enough arguments!\n");
                exit(-1);
            }
            strcpy(args->port, argv[i+1]);
            i++;

            // When port number is given we have to look for transtort layer protocols
            boolean_counter += 2;
            args->tcp = true;
            args->udp = true;
        }
        else if(strcmp(argv[i], "-t") == 0 || strcmp(argv[i], "--tcp") == 0){
            if(args->tcp != true)
                boolean_counter++;
            args->tcp = true;
        }
        else if(strcmp(argv[i], "-u") == 0 || strcmp(argv[i], "--udp") == 0){
            if(args->udp != true)
                boolean_counter++;
            args->udp = true;
        }
        else if(strcmp(argv[i], "--arp") == 0){
            if(args->arp != true)
                boolean_counter++;
            args->arp = true;
        }
        else if(strcmp(argv[i], "--icmp") == 0){
            if(args->icmp != true)
                boolean_counter++;
            args->icmp = true;
        }
        else if(strcmp(argv[i], "-n") == 0){
            if(i + 1 == argc){
                fprintf(stderr, "Error! Not enough arguments!\n");
                exit(-1);
            }
            args->number_packets = atoi(argv[i+1]);
            if(args->number_packets < 1){
                fprintf(stderr, "Error! Packet number cannot be lower than 1!\n");
                exit(-1);
            }
            i++;
        }
        else{
            fprintf(stderr, "Error! Invalid argument!\n");
            exit(-1);
        }
    }
    
    return boolean_counter;
}

// Filter

void create_filter(char *filter, int bool_counter, t_Args *args){
    if(strcmp(args->port, "") != 0){
        strcpy(filter, "port ");
        strcat(filter, args->port);
        strcat(filter, " and ");
    }

    switch(bool_counter){
        case 1:
            if(args->tcp){
               strcat(filter, "tcp\n"); 
            }
            else if(args->udp){
                strcat(filter, "udp\n"); 
            }
            else if(args->arp){
                strcat(filter, "arp\n"); 
            }
            else if(args->icmp){
                strcat(filter, "icmp\n"); 
            }
            break;
        case 2:
            if(args->tcp && args->udp){
                strcat(filter, "tcp or udp\n");
            }
            else if(args->tcp && args->arp){
                strcat(filter, "tcp or arp\n");
            }
            else if(args->tcp && args->icmp){
                strcat(filter, "tcp or icmp\n");
            }
            else if(args->udp && args->arp){
                strcat(filter, "udp or arp\n");
            }
            else if(args->udp && args->icmp){
                strcat(filter, "udp or icmp\n");
            }
            else if(args->arp && args->icmp){
                strcat(filter, "arp or icmp\n");
            }
            break;
        case 3:
            if(args->tcp && args->udp && args->arp){
                strcat(filter, "tcp or udp or arp\n");
            }
            else if(args->tcp && args->udp && args->icmp){
                strcat(filter, "tcp or udp or icmp\n");
            }
            else if(args->tcp && args->arp && args->icmp){
                strcat(filter, "tcp or icmp or arp\n");
            }
            else if(args->udp && args->arp && args->icmp){
                strcat(filter, "udp or arp or icmp\n");
            }
            break;
        case 0:
        case 4:
            strcat(filter, "tcp or udp or arp or icmp\n");
            break;
    }

}

// Printing

void print_basic_info(char *time, char *source, char *dest, int len, int protocol_type){
    switch (protocol_type){
        case 0:
        case 84:
            printf("***ARP*** \n");
            break;
        case 1:
            printf("***ICMP*** \n");
            break;
        case 6:
            printf("***TCP*** \n");
            break;
        case 17:
            printf("***UDP*** \n");
            break;
        default:
            break;
    }
    printf("timestamp: %s\n", time);
    printf("src MAC: %s\n", source);
    printf("dst MAC: %s\n", dest);
    printf("frame length: %d bytes\n", len);
}

void print_hex_ascii(const u_char *payload, int len, int offset){

    int i;
    int gap;
    const u_char *ch;

    // Offset
    printf("0x%04X   ", offset);
    
    // Hexa values
    ch = payload;
    for(i = 0; i < len; i++) {
        printf("%02x ", *ch);
        ch++;
    }

    if (len < 8)
        printf(" ");
    
    if (len < 16) {
        gap = 16 - len;
        for (i = 0; i < gap; i++) {
            printf("   ");
        }
    }
    printf("   ");
    
    // Ascii
    ch = payload;
    for(i = 0; i < len; i++) {
        if (isprint(*ch))
            printf("%c", *ch);
        else
            printf(".");
        ch++;
    }

    printf("\n");
}

void print_payload(const u_char *payload, int len){

    int len_rem = len;
    int line_width = 16;
    int line_len;
    int offset = 0;
    const u_char *ch = payload;

    if (len <= 0)
        return;

    // Data on one line
    if (len <= line_width) {
        print_hex_ascii(ch, len, offset);
        return;
    }

    // Data on multiple lines
    for ( ;; ) {
        line_len = line_width % len_rem;
        print_hex_ascii(ch, line_len, offset);
        len_rem = len_rem - line_len;
        ch = ch + line_len;

        offset = offset + line_width;
        if (len_rem <= line_width) {
            print_hex_ascii(ch, len_rem, offset);
            break;
        }
    }
}

// Other

char *ether_ntoa_override(char *buffer, struct ether_addr *address){
    sprintf(buffer, "%02x:%02x:%02x:%02x:%02x:%02x",
            address->ether_addr_octet[0], address->ether_addr_octet[1],
            address->ether_addr_octet[2], address->ether_addr_octet[3],
            address->ether_addr_octet[4], address->ether_addr_octet[5]);
    return buffer;
}

// Packet handling

void process_tcp(const u_char *data, int ip_header_len){
    struct tcphdr *tcp_header = (struct tcphdr *)(data + ip_header_len + sizeof(struct ether_header));
    unsigned src_port = ntohs(tcp_header->source);
    unsigned dst_port = ntohs(tcp_header->dest);

    printf("src port: %d\n", src_port);
    printf("dst port: %d\n", dst_port);

}

void process_udp(const u_char *data, int ip_header_len){
    struct udphdr *udp_header = (struct udphdr *)(data + ip_header_len + sizeof(struct ether_header));
    unsigned src_port = ntohs(udp_header->source);
    unsigned dst_port = ntohs(udp_header->dest);

    printf("src port: %d\n", src_port);
    printf("dst port: %d\n", dst_port);
}

void process_arp(){
    //printf("ARP DATA\n");
}

void process_icmp(){
    //printf("ICMP DATA\n");
}

void sniffer_callback(u_char *arguments, const struct pcap_pkthdr *packet_header, const u_char *data){
    // Ethernet header
    const struct ether_header *ethernet = (struct ether_header *)data;

    // Strings for storing MAC addresses
    char *ethernet_shost = malloc(sizeof(MAC_LEN));
    char *ethernet_dhost = malloc(sizeof(MAC_LEN));
    if(!ethernet_shost || !ethernet_dhost){
        fprintf(stderr, "Error! Bad malloc!s\n");
        exit(-1);
    }
    
    // Getting MAC addresses
    ethernet_shost = ether_ntoa_override(ethernet_shost, (struct ether_addr *)ethernet->ether_shost);
    ethernet_dhost = ether_ntoa_override(ethernet_dhost, (struct ether_addr *)ethernet->ether_dhost);
    
    // Getting packet length
    int len = packet_header->len;

    // Getting timestamp
    char miliseconds[7]; // TODO -> mozna predelat aby to byl jen milsekundy a ne mikro
    char date_format[20] = "%FT%T.";
    char time_zone[3] = "%z";
    
    snprintf(miliseconds, 6, "%ld", packet_header->ts.tv_usec);
    strcat(date_format, miliseconds);
    strcat(date_format, time_zone);

    char time[TIME_LEN];
	size_t zone = strftime(time, sizeof(time), date_format, localtime(&packet_header->ts.tv_sec));
    if (zone > 1) {
        char minute[] = { time[zone-2], time[zone-1], '\0' };
        sprintf(time + zone - 2, ":%s", minute);
    }

    // Determining whether we have IPv4 or IPv6
    uint16_t ipv6 = ntohs(ethernet->ether_type);
    int protocol_type;
    int ip_header_len;
    char ip_src[IP_LEN];
    char ip_dst[IP_LEN];
    char type_ip[10];

    // Chosing which IP protocol we have and printing src and dest IP addresses
    if(ipv6 == ETHERTYPE_IPV6){
        struct ip6_hdr *ipv6_header = (struct ip6_hdr *)(data + sizeof(struct ether_header));
        protocol_type = ipv6_header->ip6_nxt;
        ip_header_len = IP_LEN;
        strcpy(type_ip, "IPv6");
        // Using ntop, because it doesnt delete leading zeros
        inet_ntop(AF_INET6, &ipv6_header->ip6_src, ip_src, NI_MAXHOST); 
        inet_ntop(AF_INET6, &ipv6_header->ip6_dst, ip_dst, NI_MAXHOST);
    }
    else{
        // Using ip not iphdr for better unix compability (iphdr is only for Linux)
         struct ip* ipv4_header = (struct ip *)(data + sizeof(struct ether_header));
         protocol_type = ipv4_header->ip_p;
         ip_header_len = ipv4_header->ip_hl*4;
         strcpy(type_ip, "IP");
         strcpy(ip_src, inet_ntoa((struct in_addr)ipv4_header->ip_src));
         strcpy(ip_dst, inet_ntoa((struct in_addr)ipv4_header->ip_dst));
    }

    // Printing head info of packet
    print_basic_info(time, ethernet_shost, ethernet_dhost, len, protocol_type);
    // Printing IP addresses
    if(protocol_type != 0 && protocol_type != 84){
        printf("src %s: %s\n", type_ip, ip_src);
        printf("dst %s: %s\n", type_ip, ip_dst);
    }


    // Determining which protocol we have and printing his info
    switch (protocol_type){
        case 1: // ICMP
            process_icmp();
            break;

        case 6: // TCP
            process_tcp(data, ip_header_len);
            break;
    
        case 17: // UDP
            process_udp(data, ip_header_len);
            break;
    
        case 0: // ARP
        case 84:
            process_arp();
            break;
    
        default:
            break;
    }

    // Printing packet data
    printf("\n");
    print_payload(data, len);
    printf("\n\n");

    // Freeing strings
    free(ethernet_shost);
    free(ethernet_dhost);
}

// MAIN

int main(int argc, char **argv){
    
    t_Args args = ctor_Args();
    int bool_counter = parse_arguments(argc, argv, &args);
    
    char error_buffer[PCAP_ERRBUF_SIZE];
    bpf_u_int32 network_mask;
    bpf_u_int32 network_num;

    // Getting network mask and number
    if(pcap_lookupnet(args.interface, &network_num, &network_mask, error_buffer) == -1){
        fprintf(stderr, "Error! Could not find network mask! \n Error: \n\t%s \n", error_buffer);
        network_num = 0;
        network_mask = 0;
    }

    // Opening device for capturing packets
    pcap_t *sniffer = pcap_open_live(args.interface, SNAP_LEN, 1, 1000, error_buffer);
    if(!sniffer){
        fprintf(stderr, "Error! Could not open device! \n Error: \n\t%s \n", error_buffer);
        exit(-1);
    }

    // Creating filter
    char filter[FILTER_LEN] = "";
    create_filter(filter, bool_counter, &args);

    // Compiling and parsing filter
    struct bpf_program fp;
    if (pcap_compile(sniffer, &fp, filter, 0, network_num) == -1) {
        fprintf(stderr, "Error! Could not compile filter! \nFilter: \n\t %s \nError: \n\t%s \n", filter, pcap_geterr(sniffer));
        exit(-1);
    }
    
    // Applying filter
    if (pcap_setfilter(sniffer, &fp) == -1) {
        fprintf(stderr, "Error! Could not set filter! \nFilter: \n\t %s \nError: \n\t%s \n", filter, pcap_geterr(sniffer));
        exit(-1);
    }

    // Waiting for packets in loop
    pcap_loop(sniffer, args.number_packets, sniffer_callback, NULL);
    
    return 0;
}
