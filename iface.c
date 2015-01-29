#include "iface.h"

void free_iface(struct iface *ifa){
    free(ifa->name);
    free(ifa->inet_addr);
    free(ifa->inet6_addr);
    free(ifa->hw_addr);
}

void init_iface(struct iface *ifa){
    ifa->name = malloc(sizeof(char)*IFACE_NAME_LENGTH);
    (ifa->name)[0] = '\0'; 
    ifa->inet_addr = malloc(sizeof(char)*16);
    (ifa->inet_addr)[0] = '\0';
    ifa->inet6_addr = malloc(sizeof(char)*NI_MAXHOST);
    (ifa->inet6_addr)[0] = '\0';
    ifa->hw_addr = malloc(sizeof(char)*HW_ADDR_LENGTH);
    (ifa->hw_addr)[0] = '\0';
    ifa->tx_bytes = 0;
    ifa->rx_bytes = 0;
    ifa->tx_packets = 0;
    ifa->rx_packets = 0;
}

int get_info_interface(struct iface* ifa,const char *name_iface){
    struct ifaddrs *ifaddr, *aux;
    struct rtnl_link_stats *stats;
    
    init_iface(ifa);
    
    if (getifaddrs(&ifaddr) == -1) {
        return -1;
    }
    
    for(aux=ifaddr; aux!=NULL; aux=aux->ifa_next){
        if (aux->ifa_addr == NULL){
            continue;
        }
        
        if(strcmp(aux->ifa_name, name_iface) == 0){
            strcpy(ifa->name, aux->ifa_name);
            
            if(aux->ifa_addr->sa_family == AF_PACKET){
                stats = aux->ifa_data;

                ifa->tx_bytes =  stats->tx_bytes;
                ifa->rx_bytes =  stats->rx_bytes;
                ifa->tx_packets =  stats->tx_packets;
                ifa->rx_packets =  stats->rx_packets;
            }else if(aux->ifa_addr->sa_family == AF_INET){
                getnameinfo(aux->ifa_addr, sizeof(struct sockaddr_in), 
                            ifa->inet_addr, NI_MAXHOST, NULL, 0, NI_NUMERICHOST);
            }else if(aux->ifa_addr->sa_family == AF_INET6){
                getnameinfo(aux->ifa_addr, sizeof(struct sockaddr_in6), 
                            ifa->inet6_addr, NI_MAXHOST, NULL, 0, NI_NUMERICHOST);
            }
            ifa->hw_addr = get_mac(name_iface);
        }
    }
    freeifaddrs(ifaddr);
    
    return 0;
}

char ** get_list_interfaces(){
    char **list_ifaces;
    struct ifaddrs *ifaddr, *ifa;
    int i = 0, j;

    list_ifaces = malloc(sizeof(char*)*MAX_IFACE);

    if (getifaddrs(&ifaddr) == -1) {
        return NULL;
    }
   
    for(ifa=ifaddr; ifa!=NULL; ifa=ifa->ifa_next){
        if (ifa->ifa_addr == NULL){
            continue;
        }
        
        for(j=0; j<i; j++){
            //Check if it already exists the interface inside the list
            if(strcmp(ifa->ifa_name, list_ifaces[j]) == 0){
                break;
            }
        }
        
        if(j < i){
            //If j < i, it means that last loop was broken before it finishes
            //Then, it means that was found a equal string inside the list
            continue;
        }
        
        list_ifaces[i] = malloc(sizeof(char)*IFACE_NAME_LENGTH);
        strcpy(list_ifaces[i], ifa->ifa_name);
        i++;
    }
    
    freeifaddrs(ifaddr);
    
    return list_ifaces;
}

char * get_mac(const char *name_iface){
    char *ret = malloc(HW_ADDR_LENGTH);
    struct ifreq s;
    int fd = socket(PF_INET, SOCK_DGRAM, IPPROTO_IP);

    strcpy(s.ifr_name, name_iface);
    if (fd >= 0 && ret && 0 == ioctl(fd, SIOCGIFHWADDR, &s)){
        int i;
        for (i = 0; i < 6; ++i){
            snprintf(ret+i*2,HW_ADDR_LENGTH-i*2,"%02x",(unsigned char) s.ifr_addr.sa_data[i]);
        }
    }else{
        return NULL;
    }
    return ret;
}
