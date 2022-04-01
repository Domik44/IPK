// Authors: Dominik Pop
// Login: xpopdo00, <xpopdo00@stud.fit.vutbr.cz>
// VUT FIT, 2 BIT, summer semestr
// Date: 29.3.2021
// File explaining arguments processing

#include "ipk-sniffer.h"


// FUNCTIONS

// Constructor

t_Args ctor_Args(){
   t_Args args;
   args.tcp = false;
   args.udp = false;
   args.arp = false;
   args.icmp = false;
   args.number_packets = 1;
   strcpy(args.interface, "");
   strcpy(args.port, "");
   
   return args;
}

// Help

void help_function(){
    fprintf(stdout, "Description:\n");
    fprintf(stdout, "\tPacket sniffer in C.\n");
    fprintf(stdout, "Usage:\n");
    fprintf(stdout, "\tsudo ./ipk-sniffer [-i rozhraní | --interface rozhraní] {-p ­­port} {[--tcp|-t] [--udp|-u] [--arp] [--icmp] } {-n num}\n");
    fprintf(stdout, "Parametres:\n");
    fprintf(stdout, "\t -i/--interface \n\t\t -> Interface on which we want to catch packets\n"); 
    fprintf(stdout, "\t -p \n\t\t -> port number for filtering packets\n"); 
    fprintf(stdout, "\t [--tcp|-t]/[--udp|-u]/[--arp]/[--icmp] \n\t\t -> protocols for filtering packets \n"); 
    fprintf(stdout, "\t\t -> u can combine them, when none is given all are applied \n"); 
    fprintf(stdout, "\t -n \n\t\t -> number of packets that are supposed to be catched\n"); 
    fprintf(stdout, "\t\t -> if you don't pass this argument it means '-n 1' \n"); 
    
    exit(0);   
}
