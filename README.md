# iface

It is a interface to get information about Network Interfaces in your computer.
This library uses some Linux libraries to get informations about available 
Network Interfaces, so it makes easier to get these information.

## Installation
    
    $ make
    # make install

## Usage

You may use this library just copying the files to your project's folder or 
you can install in your system.

You can see an example of usage in examples folder or you can compile:

    $ gcc main.c -o main -liface

## Structure

You can check all attributes are available in the structure to use.

    char name               -   Interface's name
    char *inet_addr         -   IPv4 address
    char *inet6_addr        -   IPv6 address
    char *hw_addr           -   MAC address
    char *broad_addr        -   Broadcast address
    char *inet_mask         -   Network mask IPv4
    char *inet6_mask        -   Network mask IPv6
    unsigned char running   -   Variable to check if interface is running(1) or not(0)
    unsigned char updown    -   Variable to check if interface is up(1) or down(0)
    unsigned int flags      -   Variable with all flags from structure ifaddr
    unsigned int mtu        -   Interface's MTU (Not used yet)
    unsigned int metric     -   Interface's metric (Not used yet)
    unsigned int tx_bytes   -   Amount of bytes sent out from the interface
    unsigned int rx_bytes   -   Amount of bytes received on the interface
    unsigned int tx_packets -   Amount of packets sent out from the interface
    unsigned int rx_packets -   Amount of packet received on the interface

## Flags

You can check the flags which you can use together flags attribute to 
check some interface's status.

All flags are described on that page:
    
    http://man7.org/linux/man-pages/man7/netdevice.7.html

You can use in this way:

    if(ifa->flags & IFF_RUNNING){
        
    }

## Functions

These are some functions to initialize the structure, get information and 
etc.

    void free_iface(struct iface *ifa)
        - This function release the memory allocated for this structure.
    void init_iface(struct iface *ifa)
        - This function initialize the structure, allocating memory and 
          other necessary steps.
    int get_info_interface(struct iface* ifa, const char *name_iface)
        - This function gather all information about the interface, and 
          fill the structure with these information.
    int get_list_interfaces(char *** list_ifaces)
        - This function receive a pointer-to-pointer-to-pointer char
          (you call get_list_interfaces(&list_ifaces)) and fill it with 
          a list of all available NIC. It returns the length of list or 
          -1 if happens something wrong.
    char * get_mac(const char *name_iface)
        - This function returns MAC address of a available NIC. It should 
          be used just by get_info_interface(), but you can use too.
