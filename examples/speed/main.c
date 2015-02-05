/*
 * Author: Alfredo Miranda
 * E-mail: alfredocdmiranda@gmail.com
 * Description: It is just a simple example of how to use update_tx_rx()
 *              function. For example, to calculate internet speed, or just
 *              to keep tracking NIC's use of your bandwidth.
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "iface.h"

int main(int argc, char *argv[]){
    struct iface ifa;
    
    char **list = NULL;
    int list_len;
    int i;
    
    int interface = 2; //This value should be modified to your own value.
    int delay = 10; //seconds
    
    unsigned int last_tx_bytes;
    unsigned int last_rx_bytes;
    
    list_len = get_list_interfaces(&list);
    get_info_interface(&ifa, list[interface]);
    
    last_tx_bytes = ifa.tx_bytes;
    last_rx_bytes = ifa.rx_bytes;
    
    sleep(delay);
    update_tx_rx(&ifa);
    
    printf("Upload: %u bytes/sec\n", (ifa.tx_bytes - last_tx_bytes)/delay);
    printf("Download: %u bytes/sec\n", (ifa.rx_bytes - last_rx_bytes)/delay);
    
    free_iface(&ifa);
    
    return 0;
}
