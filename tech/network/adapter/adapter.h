#ifndef TECH_NETWORK_ADAPTER_H
#define TECH_NETWORK_ADAPTER_H

#include <tech/config/features.h>
#include <tech/shared/include.h>
#include <tech/shared/types.h>

#include <tech/util/include/error.h>

// For 6 bytes
#define TECH_NETWORK_ADAPTER_MAC_SIZE 6 

// 00:00:00:00:00:00 17 + 1(for the string terminator)
#define TECH_NETWORK_ADAPTER_MAC_STRING_SIZE 18 

#define TECH_NETWORK_ADAPTER_NAME_SIZE IFNAMSIZ


#ifdef __cplusplus
	extern "C" {
#endif


typedef tech_byte_t tech_network_adapter_mac_t[TECH_NETWORK_ADAPTER_MAC_SIZE];

typedef char tech_network_adapter_mac_string_t[TECH_NETWORK_ADAPTER_MAC_STRING_SIZE];

typedef char tech_network_adapter_name_t[TECH_NETWORK_ADAPTER_NAME_SIZE]; // This is the standard

typedef struct tech_network_adapter_info_struct_t{
	tech_network_adapter_name_t adapter;
	tech_network_adapter_mac_t current_mac;
	tech_network_adapter_mac_t permanent_mac;
	struct tech_network_adapter_info_struct_t* next;
}tech_network_adapter_info_t;

tech_return_t tech_network_adapter_convert_mac_to_string(tech_network_adapter_mac_string_t destination, tech_network_adapter_mac_t source);

tech_return_t tech_network_adapter_convert_mac_from_string(tech_network_adapter_mac_t destination, tech_network_adapter_mac_string_t source);

// call srand()
tech_return_t tech_network_adapter_generate_random_mac_global(tech_network_adapter_mac_t mac);

tech_return_t tech_network_adapter_get_info_list(tech_network_adapter_info_t** info_list);

tech_return_t tech_network_adapter_free_info_list(tech_network_adapter_info_t** info_list);

tech_return_t tech_network_adapter_find_name_from_mac(tech_network_adapter_name_t name, tech_network_adapter_mac_t permanent_mac);


#ifdef __cplusplus
	}
#endif

#endif