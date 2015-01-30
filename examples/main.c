#include <stdio.h>
#include <stdlib.h>
#include <iface.h>

//TODO Analisar alterações para ifreq e socket de toda a estrutura

int main(int argc, char *argv[]){
    struct iface ifa;
    
    char **list;
    int i;
    list = get_list_interfaces();
    for(i=0; i < MAX_IFACE; i++){
        if(list[i] == NULL){
            continue;
        }
        get_info_interface(&ifa, list[i]);
    
        printf("Interface: %s\n", ifa.name);
        printf("IPv4: %s\n", ifa.inet_addr);
        printf("IPv6: %s\n", ifa.inet6_addr);
        printf("MAC: %s\n", ifa.hw_addr);
        printf("TX Bytes: %u\n", ifa.tx_bytes);
        printf("RX Bytes: %u\n", ifa.rx_bytes);
        printf("TX Packets: %u\n", ifa.tx_packets);
        printf("RX Packets: %u\n", ifa.rx_packets);
        
        free_iface(&ifa);
        
        printf("--------------------------------\n");
    }
    
    return 0;
}
