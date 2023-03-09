#ifndef TECH_NETWORK_ADAPTER_WIFI_H
#define TECH_NETWORK_ADAPTER_WIFI_H

#include <tech/config/features.h>
#include <tech/shared/include.h>
#include <tech/shared/types.h>

#include <tech/network/adapter/adapter.h>
#include <tech/util/include/error.h>

#ifdef __cplusplus
    extern "C" {
#endif

typedef enum tech_network_adapter_wifi_mode_enum_t{
	TECH_NETWORK_ADAPTER_WIFI_MODE_AUTO		= IW_MODE_AUTO,		/**< Driver decides. */
	TECH_NETWORK_ADAPTER_WIFI_MODE_ADHOC	= IW_MODE_ADHOC,	/**< Single cell network. */
	TECH_NETWORK_ADAPTER_WIFI_MODE_MANAGED	= IW_MODE_INFRA,	/**< Multi cell network, roaming, ... */
	TECH_NETWORK_ADAPTER_WIFI_MODE_MASTER	= IW_MODE_MASTER,	/**< Synchronisation master or access point. */
	TECH_NETWORK_ADAPTER_WIFI_MODE_REPEAT	= IW_MODE_REPEAT,	/**< Wireless repeater, forwarder. */
	TECH_NETWORK_ADAPTER_WIFI_MODE_SECOND	= IW_MODE_SECOND,	/**< Secondary master/repeater, backup. */
	TECH_NETWORK_ADAPTER_WIFI_MODE_MONITOR	= IW_MODE_MONITOR	/**< Passive monitor, listen only. */
} tech_network_adapter_wifi_mode_t;


typedef enum tech_network_adapter_wifi_frequency_flag_enum_t{
	TECH_NETWORK_ADAPTER_WIFI_FREQ_AUTO	= IW_FREQ_AUTO,
	TECH_NETWORK_ADAPTER_WIFI_FREQ_FIXED	= IW_FREQ_FIXED
} tech_network_adapter_wifi_frequency_flag_t;


typedef enum tech_network_adapter_wifi_operstate_enum_t{
    TECH_NETWORK_ADAPTER_WIFI_OPERSTATE_UNKNOWN = 0,
    TECH_NETWORK_ADAPTER_WIFI_OPERSTATE_DOWN = 1,
    TECH_NETWORK_ADAPTER_WIFI_OPERSTATE_UP = 2
}tech_network_adapter_wifi_operstate_t;


typedef uint8_t tech_network_adapter_wifi_channel_t;

tech_return_t tech_network_adapter_wifi_parse_mode(int iw_mode,tech_network_adapter_wifi_mode_t* adapter_mode );


tech_return_t tech_network_adapter_wifi_get_mode(tech_network_adapter_t adapter, tech_network_adapter_wifi_mode_t* mode);


tech_return_t tech_network_adapter_wifi_get_operstate(tech_network_adapter_t adapter, tech_network_adapter_wifi_operstate_t* operstate);


tech_return_t tech_network_adapter_wifi_get_frequency(tech_network_adapter_t adapter,double* frequency, tech_network_adapter_wifi_frequency_flag_t* flag);


tech_return_t tech_network_adapter_wifi_get_channel(tech_network_adapter_t adapter, tech_network_adapter_wifi_channel_t* channel);

#ifdef __cplusplus
    }
#endif

#endif