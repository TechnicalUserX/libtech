#include <tech/network/adapter/adapter.h>


tech_return_t tech_network_adapter_convert_mac_to_string(tech_network_adapter_mac_string_t destination, tech_network_adapter_mac_t source){
        
    if(destination == NULL || source == NULL){
        tech_error_number = TECH_ERROR_NULL_POINTER;
        return TECH_RETURN_FAILURE;
    }
    snprintf(destination,TECH_NETWORK_ADAPTER_MAC_STRING_SIZE,"%02hhX:%02hhX:%02hhX:%02hhX:%02hhX:%02hhX",source[0],source[1],source[2],source[3],source[4],source[5]);
    tech_error_number = TECH_SUCCESS;
    return TECH_RETURN_SUCCESS;
}

tech_return_t tech_network_adapter_convert_mac_from_string(tech_network_adapter_mac_t destination, tech_network_adapter_mac_string_t source){
    if(destination == NULL || source == NULL){
        tech_error_number = TECH_ERROR_NULL_POINTER;
        return TECH_RETURN_FAILURE;
    }

    // Assuming the format AA:BB:CC:DD:EE:FF
    sscanf(source,"%02hhX:%02hhX:%02hhX:%02hhX:%02hhX:%02hhX",&destination[0],&destination[1],&destination[2],&destination[3],&destination[4],&destination[5]);

    tech_error_number = TECH_SUCCESS;
    return TECH_RETURN_SUCCESS;
}

tech_return_t tech_network_adapter_generate_random_mac_global(tech_network_adapter_mac_t mac){
    
    if(mac == NULL){
        tech_error_number = TECH_ERROR_NULL_POINTER;
        return TECH_RETURN_FAILURE;
    }
    
    mac[0] = rand() % 256; mac[0] &= 0b11111100; // Set the local address bit and multicast bit to zero
    mac[1] = rand() % 256;
    mac[2] = rand() % 256;
    mac[3] = rand() % 256;
    mac[4] = rand() % 256;
    mac[5] = rand() % 256;




    tech_error_number = TECH_SUCCESS;
    return TECH_RETURN_SUCCESS;
}

tech_return_t tech_network_adapter_get_info_list(tech_network_adapter_info_t** info_list){
    

	if(info_list == NULL){
		tech_error_number = TECH_ERROR_NULL_POINTER;
		return TECH_RETURN_FAILURE;
	}

    // Send
    typedef struct {
        struct nlmsghdr nh;
        struct ifinfomsg ifi;
    } Req_getlink;


	if(NLMSG_LENGTH(sizeof(struct ifinfomsg)) != sizeof(Req_getlink)){
		tech_error_number = TECH_ERROR_GENERIC_FAIL_ASSERTION;
		return TECH_RETURN_FAILURE;
	}

    int fd=-1;
    fd=socket(AF_NETLINK,SOCK_RAW,NETLINK_ROUTE);

    struct sockaddr_nl addr_nl;
    addr_nl.nl_family = AF_NETLINK;
    addr_nl.nl_pad = 0;
    addr_nl.nl_pid = getpid();
    addr_nl.nl_groups = 0;

    //assert(0==bind(fd,(struct sockaddr*)(&addr_nl),sizeof(struct sockaddr_nl)));
	if(0 != bind(fd,(struct sockaddr*)(&addr_nl),sizeof(struct sockaddr_nl))){
		tech_error_number = TECH_ERROR_GENERIC_FAIL_ASSERTION;
		return TECH_RETURN_FAILURE;
	}

    Req_getlink getlink = {0};
    getlink.nh.nlmsg_len = NLMSG_LENGTH(sizeof(struct ifinfomsg));
    getlink.nh.nlmsg_type = RTM_GETLINK;
    getlink.nh.nlmsg_flags = NLM_F_REQUEST|NLM_F_ROOT;
    getlink.nh.nlmsg_seq = 0;
    getlink.nh.nlmsg_pid = 0;
    getlink.ifi.ifi_family = AF_UNSPEC;
    getlink.ifi.ifi_type = 0;
    getlink.ifi.ifi_index = 0;
    getlink.ifi.ifi_flags = 0;
    getlink.ifi.ifi_change = 0;


    if(sizeof(Req_getlink) != send(fd,&(getlink),sizeof(Req_getlink),0)){
		tech_error_number = TECH_ERROR_GENERIC_FAIL_ASSERTION;
		return TECH_RETURN_FAILURE;
	}

  	// Receive
    char recvbuf[8192]={};

    uint32_t len=0;
    for(char *p=recvbuf;;){
		const int seglen=recv(fd,p,sizeof(recvbuf)-len,0);

		if((seglen < 1)){
			tech_error_number = TECH_ERROR_GENERIC_FAIL_ASSERTION;
			return TECH_RETURN_FAILURE;	
		}

		len += seglen;
		if(((struct nlmsghdr*)p)->nlmsg_type==NLMSG_DONE||((struct nlmsghdr*)p)->nlmsg_type==NLMSG_ERROR)
			break;
		p += seglen;
    }

    struct nlmsghdr *nh=(struct nlmsghdr*)recvbuf;

	// Create a new list
	tech_network_adapter_info_t* new_info_list = NULL;


	tech_network_adapter_info_t* iterator = new_info_list;

    for(;NLMSG_OK(nh,len);nh=NLMSG_NEXT(nh,len)){

        if(nh->nlmsg_type==NLMSG_DONE)
            break;

        struct ifinfomsg *ifm=(struct ifinfomsg*)NLMSG_DATA(nh);

        #ifdef _NET_IF_H
        	#pragma GCC error "include <linux/if.h> instead of <net/if.h>"
        #endif

        // Part 3 rtattr
        struct rtattr *rta=IFLA_RTA(ifm); // /usr/include/linux/if_link.h

        int rtl=RTM_PAYLOAD(nh);

		tech_network_adapter_info_t* new_info = (tech_network_adapter_info_t*)malloc(sizeof(tech_network_adapter_info_t));
	

		if(new_info == NULL){
			tech_error_number = TECH_ERROR_CANNOT_ALLOC_MEMORY;
			return TECH_RETURN_FAILURE;
		}

		bzero(new_info,sizeof(tech_network_adapter_info_t));

		new_info->next = NULL; // Explicit :)

        for(;RTA_OK(rta,rtl); rta=RTA_NEXT(rta,rtl))
            switch(rta->rta_type ){
            

            case IFLA_IFNAME:
				memcpy(new_info->adapter,(const char*)RTA_DATA(rta),TECH_NETWORK_ADAPTER_NAME_SIZE-1);
                new_info->adapter[TECH_NETWORK_ADAPTER_NAME_SIZE-1] = '\0';
            break;

            case IFLA_ADDRESS:
				memcpy(new_info->current_mac,(tech_byte_t*)RTA_DATA(rta),TECH_NETWORK_ADAPTER_MAC_SIZE);
            break;


            case IFLA_PERM_ADDRESS:
				memcpy(new_info->permanent_mac,(tech_byte_t*)RTA_DATA(rta),TECH_NETWORK_ADAPTER_MAC_SIZE);
            break;

        }

        if(iterator == NULL){
            new_info_list = new_info;
            iterator = new_info;
        }else{
            iterator->next = new_info;
            iterator = iterator->next;
        }

    }

	close(fd);
	fd=-1;

	*info_list = new_info_list;
	tech_error_number = TECH_SUCCESS;
	return TECH_RETURN_SUCCESS;
}

tech_return_t tech_network_adapter_free_info_list(tech_network_adapter_info_t** info_list){

	if(info_list == NULL){
		tech_error_number = TECH_ERROR_NULL_POINTER;
		return TECH_RETURN_FAILURE;
	}

	tech_network_adapter_info_t* iterator = *info_list;

	while(iterator != NULL  ){

		tech_network_adapter_info_t* next = iterator->next;
		free(iterator);
		iterator = next;

	}

	*info_list = NULL;
	tech_error_number = TECH_SUCCESS;
	return TECH_RETURN_SUCCESS;
}

tech_return_t tech_network_adapter_find_name_from_mac(tech_network_adapter_name_t name, tech_network_adapter_mac_t permanent_mac){


	if(name == NULL || permanent_mac == NULL){
		tech_error_number = TECH_ERROR_NULL_POINTER;
		return TECH_RETURN_FAILURE;
	}


	tech_network_adapter_info_t* search_list;

	if(tech_network_adapter_get_info_list(&search_list) == TECH_RETURN_SUCCESS){

		tech_network_adapter_info_t* iterator;

		for(iterator = search_list; iterator != NULL; iterator = iterator->next){

			if(memcmp(iterator->permanent_mac,permanent_mac,TECH_NETWORK_ADAPTER_MAC_SIZE) == 0){
				memcpy(name,iterator->adapter,TECH_NETWORK_ADAPTER_NAME_SIZE-1);
				name[TECH_NETWORK_ADAPTER_NAME_SIZE-1] = '\0';
				tech_error_number = TECH_SUCCESS;
				tech_network_adapter_free_info_list(&search_list);
				return TECH_RETURN_SUCCESS;
			}

		}
		tech_network_adapter_free_info_list(&search_list);

		tech_error_number = TECH_ERROR_NETWORK_ADAPTER_NOT_FOUND;
		return TECH_RETURN_FAILURE;

	}else{
		return TECH_RETURN_FAILURE;
	}


}
