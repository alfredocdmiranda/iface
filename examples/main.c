#include <stdio.h>
#include <stdlib.h>
#include "iface.h"

//TODO Analisar alterações para ifreq e socket de toda a estrutura

int main(int argc, char *argv[]){
    struct iface ifa;
    
    char **list = NULL;
    int list_len;
    int i;
    
    list_len = get_list_interfaces(&list);
    for(i=0; i<list_len; i++){
        get_info_interface(&ifa, list[i]);
    
        printf("Interface: %s\n", ifa.name);
        printf("IPv4: %s\n", ifa.inet_addr);
        printf("Netmask v4: %s\n", ifa.inet_mask);
        printf("Broadcast: %s\n", ifa.broad_addr);
        printf("IPv6: %s\n", ifa.inet6_addr);
        printf("Netmask v6: %s\n", ifa.inet6_mask);
        printf("MAC: %s\n", ifa.hw_addr);
        printf("TX Bytes: %u\n", ifa.tx_bytes);
        printf("RX Bytes: %u\n", ifa.rx_bytes);
        printf("TX Packets: %u\n", ifa.tx_packets);
        printf("RX Packets: %u\n", ifa.rx_packets);
        printf("Running: %d\n", ifa.running);
        printf("UP: %d\n", ifa.updown);
        
        free_iface(&ifa);
        
        printf("--------------------------------\n");
    }
    
    return 0;
}
