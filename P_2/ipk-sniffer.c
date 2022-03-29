// Authors: Dominik Pop
// Login: xpopdo00, <xpopdo00@stud.fit.vutbr.cz>
// VUT FIT, 2 BIT, summer semestr
// Date: 29.3.2021
// Second project for IPK -> packet sniffer

#include "ipk-sniffer.h"

// GLOBAL VARIABLES
char interface[ARG_LEN] = "";
int port = -1;
bool tcp = false, udp = false, arp = false, icmp = false, do_all = false;
int number_packets = 1;

// FUCNTIONS
void help_function(){ // TODO 
    fprintf(stdout, "Description:\n");
    fprintf(stdout, "\tPacket sniffer in C.\n");
    fprintf(stdout, "Usage:\n");
    fprintf(stdout, "\tsudo ./ipk-sniffer [-i rozhraní | --interface rozhraní] {-p ­­port} {[--tcp|-t] [--udp|-u] [--arp] [--icmp] } {-n num}\n");
    fprintf(stdout, "Parametres\n");
    fprintf(stdout, "\tsomething\n"); 
    
    exit(0);   
}

void print_interfaces(){
    pcap_if_t *devices, *devices_list;
    char error_buffer[PCAP_ERRBUF_SIZE];
    bool find = pcap_findalldevs(&devices, error_buffer) == -1 ? false : true;
    if(!find){
        fprintf(stderr, "Error pcap_findalldevs! Output: %s\n", error_buffer);
        exit(-1);
    }

    for(devices_list = devices; devices_list; devices_list=devices_list->next){
        fprintf(stdout, "%s\n", devices_list->name);
    }
}

bool check_interface(char *name){
    pcap_if_t *devices, *devices_list;
    char error_buffer[PCAP_ERRBUF_SIZE];
    bool find = pcap_findalldevs(&devices, error_buffer) == -1 ? false : true;
    if(!find){
        fprintf(stderr, "Error pcap_findalldevs! Output: %s\n", error_buffer);
        exit(-1);
    }

    for(devices_list = devices; devices_list; devices_list=devices_list->next){
        if(strcmp(devices_list->name, name) == 0){
            return true;
        }
    }

    return false;
}

int parse_arguments(int argc, char **argv){ // TODO -> asi nejakej checking spatnych argumentu
    if(argc <= 2){ // TODO odstranit comment
        print_interfaces();
        exit(0);
    }

    int boolean_counter = 0;
    for(int i = 1; i < argc; i++){
        if(strcmp(argv[i], "-i") == 0 || strcmp(argv[i], "--interface") == 0){
            if(i + 1 == argc){
                fprintf(stderr, "Error! Not enough arguments!\n");
                exit(-1);
            }
            strcpy(interface, argv[i+1]); // TODO -> Odstranit comment
            if(!check_interface(interface)){
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
            port = atoi(argv[i+1]);
            i++;
        }
        else if(strcmp(argv[i], "-t") == 0 || strcmp(argv[i], "--tcp") == 0){
            tcp = true;
            boolean_counter++;
        }
        else if(strcmp(argv[i], "-u") == 0 || strcmp(argv[i], "--udp") == 0){
            udp = true;
            boolean_counter++;
        }
        else if(strcmp(argv[i], "--arp") == 0){
            arp = true;
            boolean_counter++;
        }
        else if(strcmp(argv[i], "--icmp") == 0){
            icmp = true;
            boolean_counter++;
        }
        else if(strcmp(argv[i], "-n") == 0){
            if(i + 1 == argc){
                fprintf(stderr, "Error! Not enough arguments!\n");
                exit(-1);
            }
            number_packets = atoi(argv[i+1]);
            i++;
        }
        else if(strcmp(argv[i], "-h") == 0 || strcmp(argv[i], "--help") == 0){
            help_function();
        }
        else{
            fprintf(stderr, "Error! Invalid argument!\n");
            exit(-1);
        }
    }

    if(boolean_counter == 0 || boolean_counter == 4){
        do_all = true;
    }
    // else if(boolean_counter != 1){ // TODO -> mozna blbe, mozna by to melo podporovat if kombinace 2,3...
    //     fprintf(stderr, "Error! Wrong use of tcp|udp|arp|icmp arguments\n");
    //     exit(-1);
    // }

    return boolean_counter;
}

// MAIN
int main(int argc, char **argv){
    
    bool_number = 0;
    int bool_counter = parse_arguments(argc, argv, &bool_number);
    
    char error_buffer[PCAP_ERRBUF_SIZE];
    bpf_u_int32 mask;
    bpf_u_int32 net;

    // Getting network mask and number
    if(pcap_lookupnet(interface, &net, &mask, error_buffer) == -1){
        fprintf(stderr, "Error! Could not find Netmask!\n");
        net = 0;
        mask = 0;
    }

    // Opening device for capturing packets
    pcat_t *sniffer = pcap_open_live(interface, SNAP_LEN, 1, 1000, error_buffer);
    if(!sniffer){
        fprintf(stderr, "Error! Could not open device!\n");
        exit(-1);
    }

    // Creating filter
    char filter[FILTER_LEN];
    if(!do_all){
        switch(bool_counter){
            case 2:
                if(tcp && udp){
                    
                }
                else if(tcp && arp){

                }
                else if(tcp && icmp){

                }
                else if(udp && arp){

                }
                else if(udp && icmp){

                }
                else if(arp && icmp){

                }
                break;
            case 3:
                if(tcp && udp && arp){

                }
                else if(tcp && udp && icmp){

                }
                else if(tcp && arp && icmp){

                }
                else if(udp && arp && icmp){

                }
                break;
        }
    }
    
    return 0;
}