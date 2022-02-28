// Authors: Dominik Pop
// Login: xpopdo00, <xpopdo00@stud.fit.vutbr.cz>
// VUT FIT, 2 BIT, summer semestr
// Date: 11.2.2021
// Functions definitions

#include "server.h"

#define CPU_NUM 25

// CPU NAME
//////////////////////////////////////////////////////////////////////////////////////

void get_cpu_name(char* cpu_name){

    FILE *fp = popen("cat /proc/cpuinfo | grep \"model name\" | head -n 1 | awk '{print}'", "r");
    if(!fp){ 
        perror("Error_cpu_name, couldnt read file!");
        exit(1);
    }

    int c;
    // Skiping unwanted information
    while((c = fgetc(fp)) != ':'){
    }
    c = fgetc(fp);

    // Storing name
    int i = 0;
    while((c = fgetc(fp)) != '\n'){
        cpu_name[i] = c;
        i++;
    }

    fclose(fp);
}

// HOSTNAME
///////////////////////////////////////////////////////////////////////////////////////

void get_hostname(char *result){

    FILE *fp = fopen("/proc/sys/kernel/hostname", "r");
    if(!fp){
        perror("Error_hostname, couldnt read file!");
        exit(1);
    }

    char name[NAME_MAX];
    int c;
    int i = 0;
    while((c=fgetc(fp)) != '\n'){ // Parsing hostname out of the file
        name[i] = c;
        i++;
    }
    name[i] = '\0';

    strcpy(result, name);
    fclose(fp);
}

// CPU USAGE
///////////////////////////////////////////////////////////////////////////////////////
void load_params(t_CPU *cpu){

    FILE *fp = fopen("/proc/stat", "r");
    if(!fp){
        perror("Error_cpu_usage, couldnt read file!");
        exit(1);
    }

    // Skip unwanted information
    int c;
    while(!isdigit(c = getc(fp))){
    }
    ungetc(c,fp);

    // Scan cpu times
    char number[100] = "";
    int i = 0;
    int count_asign = 0;
    do{
        c = getc(fp);
        if(c == ' ' || c == '\n'){
            number[i] = '\0';
            unsigned long num = atoi(number);
            if(count_asign == 0)
                cpu->user = num;
            else if(count_asign == 1)
                cpu->nice = num;
            else if(count_asign == 2)
                cpu->sys = num;
            else if(count_asign == 3)
                cpu->idle = num;
            else if(count_asign == 4)
                cpu->iowait = num;
            else if(count_asign == 5)
                cpu->irq = num;
            else if(count_asign == 6)
                cpu->softirq = num;
            else if(count_asign == 7)
                cpu->steal = num;
            else if(count_asign == 8)
                cpu->guest = num;
            else if(count_asign == 9)
                cpu->guest_n = num;
            i = 0;
            count_asign++;
            strcpy(number, "");
        }

        number[i] = c;
        i++;
    }while(( c != '\n'));

    fclose(fp);
}

double compute_usage(t_CPU *prev, t_CPU *actual){

    unsigned long long prev_idle = prev->idle + prev->iowait;
    unsigned long long idle = actual->idle + actual->iowait;

    unsigned long long prev_non_idle = prev->user + prev->nice + prev->sys + prev->irq + prev->softirq + prev->steal;
    unsigned long long non_idle = actual->user + actual->nice + actual->sys + actual->irq + actual->softirq + actual->steal;

    unsigned long long prev_total = prev_idle + prev_non_idle;
    unsigned long long total = idle + non_idle;

    unsigned long long result_total = total - prev_total;
    unsigned long long result_idle = idle - prev_idle;

    double result = (((double)result_total - (double)result_idle)/(double)result_total)*100;

    return result;
}

double cpu_usage(){

    // Reading parameters from /proc/stat
    t_CPU prev, actual;
    load_params(&prev);
    sleep(1);
    load_params(&actual);

    double result = compute_usage(&prev, &actual);

    return result;
}
