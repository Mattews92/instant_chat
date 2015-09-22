char* getUserIp()
{
int n;
struct ifreq ifr;
char array[] = "eth0";
n = socket(AF_INET, SOCK_DGRAM, 0);
    //Type of address to retrieve - IPv4 IP address
ifr.ifr_addr.sa_family = AF_INET;
//Copy the interface name in the ifreq structure
strncpy(ifr.ifr_name , array , IFNAMSIZ - 1);
ioctl(n, SIOCGIFADDR, &ifr);
close(n);
    //display result
    //printf("IP Addr %s\n" ,inet_ntoa(( (struct sockaddr_in *)&ifr.ifr_addr )->sin_addr) );
return (inet_ntoa(( (struct sockaddr_in *)&ifr.ifr_addr )->sin_addr)) ;
}