#ifndef TECH_TECH_NETWORK_IEEE80211_FRAME_H
#define TECH_TECH_NETWORK_IEEE80211_FRAME_H

#include <tech/config/features.h>
#include <tech/shared/include.h>
#include <tech/shared/types.h>

//=================================================================//

// MANAGEMENT FRAMES 14
#define TECH_NETWORK_IEEE80211_FRAME_MANAGEMENT_ASSOCIATION_REQUEST 0b00000000
#define TECH_NETWORK_IEEE80211_FRAME_MANAGEMENT_ASSOCIATION_RESPONSE 0b00010000
#define TECH_NETWORK_IEEE80211_FRAME_MANAGEMENT_REASSOCIATION_REQUEST 0b00100000
#define TECH_NETWORK_IEEE80211_FRAME_MANAGEMENT_REASSOCIATION_RESPONSE 0b00110000
#define TECH_NETWORK_IEEE80211_FRAME_MANAGEMENT_PROBE_REQUEST 0b01000000 // Come get me
#define TECH_NETWORK_IEEE80211_FRAME_MANAGEMENT_PROBE_RESPONSE 0b01010000
#define TECH_NETWORK_IEEE80211_FRAME_MANAGEMENT_TIMING_ADVERTISEMENT 0b01100000
#define TECH_NETWORK_IEEE80211_FRAME_MANAGEMENT_BEACON 0b10000000
#define TECH_NETWORK_IEEE80211_FRAME_MANAGEMENT_ATIM 0b10010000
#define TECH_NETWORK_IEEE80211_FRAME_MANAGEMENT_DISASSOCIATION 0b10100000
#define TECH_NETWORK_IEEE80211_FRAME_MANAGEMENT_AUTHENTICATION 0b10110000
#define TECH_NETWORK_IEEE80211_FRAME_MANAGEMENT_DEAUTHENTICATION 0x11000000
#define TECH_NETWORK_IEEE80211_FRAME_MANAGEMENT_ACTION 0b11010000
#define TECH_NETWORK_IEEE80211_FRAME_MANAGEMENT_ACTION_NO_ACK 0b11100000


// CONTROL FRAMES 14
#define TECH_NETWORK_IEEE80211_FRAME_CONTROL_TRIGGER 0b00100100
#define TECH_NETWORK_IEEE80211_FRAME_CONTROL_TACK 0b00110100
#define TECH_NETWORK_IEEE80211_FRAME_CONTROL_BEAMFORMING_REPORT_POLL 0b01000100
#define TECH_NETWORK_IEEE80211_FRAME_CONTROL_VHT_HE_NDP_ANNOUNCEMENT 0b01010100
#define TECH_NETWORK_IEEE80211_FRAME_CONTROL_CONTROL_FRAME_EXTENSION 0b01100100
#define TECH_NETWORK_IEEE80211_FRAME_CONTROL_CONTROL_WRAPPER 0b01110100
#define TECH_NETWORK_IEEE80211_FRAME_CONTROL_BLOCK_ACK_REQUEST 0b10000100
#define TECH_NETWORK_IEEE80211_FRAME_CONTROL_BLOCK_ACK 0b10010100
#define TECH_NETWORK_IEEE80211_FRAME_CONTROL_PS_POLL 0b10100100
#define TECH_NETWORK_IEEE80211_FRAME_CONTROL_RTS 0b10110100
#define TECH_NETWORK_IEEE80211_FRAME_CONTROL_CTS 0b11000100
#define TECH_NETWORK_IEEE80211_FRAME_CONTROL_ACK 0b11010100
#define TECH_NETWORK_IEEE80211_FRAME_CONTROL_CF_END 0b11100100
#define TECH_NETWORK_IEEE80211_FRAME_CONTROL_CF_END_CF_ACK 0b11110100


// DATA FRAMES 9
#define TECH_NETWORK_IEEE80211_FRAME_DATA_DATA 0b00001000
#define TECH_NETWORK_IEEE80211_FRAME_DATA_NULL 0b01001000
#define TECH_NETWORK_IEEE80211_FRAME_DATA_QOS_DATA 0b10001000
#define TECH_NETWORK_IEEE80211_FRAME_DATA_QOS_DATA_CF_ACK 0b10011000
#define TECH_NETWORK_IEEE80211_FRAME_DATA_QOS_DATA_CF_POLL 0b10101000
#define TECH_NETWORK_IEEE80211_FRAME_DATA_QOS_DATA_CF_ACK_CF_POLL 0b10111000
#define TECH_NETWORK_IEEE80211_FRAME_DATA_QOS_NULL 0b11001000
#define TECH_NETWORK_IEEE80211_FRAME_DATA_QOS_CF_POLL 0b11101000
#define TECH_NETWORK_IEEE80211_FRAME_DATA_QOS_CF_ACK_CF_POLL 0b11111000

//=================================================================//


// TAGGED PARAMETERS TAG NUMBERS
#define TECH_NETWORK_IEEE80211_TAGGED_PARAMETER_SSID 0
#define TECH_NETWORK_IEEE80211_TAGGED_PARAMETER_SUPPORTED_RATES 1
#define TECH_NETWORK_IEEE80211_TAGGED_PARAMETER_DS 3
#define TECH_NETWORK_IEEE80211_TAGGED_PARAMETER_TRAFFIC_INDICATION_MAP 5
#define TECH_NETWORK_IEEE80211_TAGGED_PARAMETER_ERP_INFO 42
#define TECH_NETWORK_IEEE80211_TAGGED_PARAMETER_ERP_INFO_2 47
#define TECH_NETWORK_IEEE80211_TAGGED_PARAMETER_RSN_INFO 48
#define TECH_NETWORK_IEEE80211_TAGGED_PARAMETER_EXTENDED_SUPPORTED_RATES 50
#define TECH_NETWORK_IEEE80211_TAGGED_PARAMETER_HT_CAPABILITIES 45
#define TECH_NETWORK_IEEE80211_TAGGED_PARAMETER_HT_INFO 61
#define TECH_NETWORK_IEEE80211_TAGGED_PARAMETER_OVERLAPPINT_BSS_SCAN_PARAMETERS 74
#define TECH_NETWORK_IEEE80211_TAGGED_PARAMETER_EXTENDEDN_CAPABILITIES 127
#define TECH_NETWORK_IEEE80211_TAGGED_PARAMETER_VENDOR_SPECIFIC 221
#define TECH_NETWORK_IEEE80211_TAGGED_PARAMETER_RM_ENABLED_CAPABILITIES 70


//=================================================================//


// MANAGEMENT FRAME FIXED_PARAM SIZES
#define TECH_NETWORK_IEEE80211_FRAME_MANAGEMENT_ASSOCIATION_REQUEST_FIXED_PARAM_SIZE 4
#define TECH_NETWORK_IEEE80211_FRAME_MANAGEMENT_ASSOCIATION_RESPONSE_FIXED_PARAM_SIZE 6
#define TECH_NETWORK_IEEE80211_FRAME_MANAGEMENT_REASSOCIATION_REQUEST_FIXED_PARAM_SIZE 10
#define TECH_NETWORK_IEEE80211_FRAME_MANAGEMENT_REASSOCIATION_RESPONSE_FIXED_PARAM_SIZE 6
#define TECH_NETWORK_IEEE80211_FRAME_MANAGEMENT_PROBE_REQUEST_FIXED_PARAM_SIZE 0
#define TECH_NETWORK_IEEE80211_FRAME_MANAGEMENT_PROBE_RESPONSE_FIXED_PARAM_SIZE 12
#define TECH_NETWORK_IEEE80211_FRAME_MANAGEMENT_BEACON_FIXED_PARAM_SIZE 12
#define TECH_NETWORK_IEEE80211_FRAME_MANAGEMENT_DISASSOCIATION_FIXED_PARAM_SIZE 2
#define TECH_NETWORK_IEEE80211_FRAME_MANAGEMENT_AUTHENTICATION_FIXED_PARAM_SIZE 6
#define TECH_NETWORK_IEEE80211_FRAME_MANAGEMENT_DEAUTHENTICATION_FIXED_PARAM_SIZE 2

//=================================================================//

#ifdef __cplusplus
	extern "C" {
#endif

typedef uint32_t tech_network_ieee80211_tagged_parameter_t;

typedef struct tech_network_ieee80211_frame_control_struct_t{
    tech_byte_t version:2;
    tech_byte_t type:2;
    tech_byte_t subtype:4;
    tech_byte_t flags;
}tech_network_ieee80211_frame_control_t;


typedef struct tech_network_ieee80211_tagged_parameter_indicator_struct_t{
    uint8_t tag_number;
    uint8_t tag_length;
}tech_network_ieee80211_tagged_parameter_indicator_t;



// Management Frames

typedef struct tech_network_ieee80211_association_request_struct_t{
    struct{ // Frame Control
        tech_byte_t version:2;
        tech_byte_t type:2;
        tech_byte_t subtype:4;
        tech_byte_t flags;
    };
    uint16_t duration;
    tech_byte_t receiver_destination_address[6];
    tech_byte_t transmitter_source_address[6];
    tech_byte_t bssid[6];
    struct{
        uint16_t fragment_number:4;
        uint16_t sequence_number:12;
    };
    struct { // Fixed parameters
        uint16_t capabilities_information;
        uint16_t listen_interval;
    }fixed_parameters;
}tech_network_ieee80211_association_request_t;


typedef struct tech_network_ieee80211_association_response_struct_t{
    struct{ // Frame Control
        tech_byte_t version:2;
        tech_byte_t type:2;
        tech_byte_t subtype:4;
        tech_byte_t flags;
    };
    uint16_t duration;
    tech_byte_t receiver_destination_address[6];
    tech_byte_t transmitter_source_address[6];
    tech_byte_t bssid[6];
    struct{
        uint16_t fragment_number:4;
        uint16_t sequence_number:12;
    };    
    struct{ // Fixed parameters
        uint16_t capabilities_information;
        uint16_t status_code;
        uint16_t association_id;
    }fixed_parameters;

}tech_network_ieee80211_association_response_t;


typedef struct tech_network_ieee80211_reassociation_request_struct_t{
    struct{ // Frame Control
        tech_byte_t version:2;
        tech_byte_t type:2;
        tech_byte_t subtype:4;
        tech_byte_t flags;
    };
    uint16_t duration;
    tech_byte_t receiver_destination_address[6];
    tech_byte_t transmitter_source_address[6];
    tech_byte_t bssid[6];
    struct{
        uint16_t fragment_number:4;
        uint16_t sequence_number:12;
    };  
    struct{ // Fixed parameters
        uint16_t capabilities_information;
        uint16_t listen_interval;
        tech_byte_t current_ap[6];
    }fixed_parameters;
}tech_network_ieee80211_reassociation_request_t;


typedef struct tech_network_ieee80211_reassociation_response_struct_t{
    struct{ // Frame Control
        tech_byte_t version:2;
        tech_byte_t type:2;
        tech_byte_t subtype:4;
        tech_byte_t flags;
    };
    uint16_t duration;
    tech_byte_t receiver_destination_address[6];
    tech_byte_t transmitter_source_address[6];
    tech_byte_t bssid[6];
    struct{
        uint16_t fragment_number:4;
        uint16_t sequence_number:12;
    };    
    struct{ // Fixed parameters
        uint16_t capabilities_information;
        uint16_t status_code;
        uint16_t association_id;
    }fixed_parameters;


}tech_network_ieee80211_reassociation_response_t;


typedef struct tech_network_ieee80211_probe_request_struct_t{
    struct{ // Frame Control
        tech_byte_t version:2;
        tech_byte_t type:2;
        tech_byte_t subtype:4;
        tech_byte_t flags;
    };
    uint16_t duration;
    tech_byte_t receiver_destination_address[6];
    tech_byte_t transmitter_source_address[6];
    tech_byte_t bssid[6];
    struct{
        uint16_t fragment_number:4;
        uint16_t sequence_number:12;
    };    

}tech_network_ieee80211_probe_request_t;


typedef struct tech_network_ieee80211_probe_response_struct_t{
    struct{ // Frame Control
        tech_byte_t version:2;
        tech_byte_t type:2;
        tech_byte_t subtype:4;
        tech_byte_t flags;
    };
    uint16_t duration;
    tech_byte_t receiver_destination_address[6];
    tech_byte_t transmitter_source_address[6];
    tech_byte_t bssid[6];
    struct{
        uint16_t fragment_number:4;
        uint16_t sequence_number:12;
    };
    struct{ // Fixed parameters
        tech_byte_t timestamp[8];
        uint16_t beacon_interval;
        int16_t capabilities_information;
    }fixed_parameters;

}tech_network_ieee80211_probe_response_t;


typedef struct tech_network_ieee80211_beacon_frame_struct_t{

    struct{ // Frame Control
        tech_byte_t version:2;
        tech_byte_t type:2;
        tech_byte_t subtype:4;
        tech_byte_t flags;
    };
    uint16_t duration;
    tech_byte_t receiver_destination_address[6];
    tech_byte_t transmitter_source_address[6];
    tech_byte_t bssid[6];
    struct{
        uint16_t fragment_number:4;
        uint16_t sequence_number:12;
    };
    // Fixed parameters
    struct{
        tech_byte_t timestamp[8];
        uint16_t beacon_interval;
        uint16_t capabilities_information;    
    }fixed_parameters;

}tech_network_ieee80211_beacon_frame_t;


typedef struct tech_network_ieee80211_disassociation_struct_t{
    struct{ // Frame Control
        tech_byte_t version:2;
        tech_byte_t type:2;
        tech_byte_t subtype:4;
        tech_byte_t flags;
    };
    uint16_t duration;
    tech_byte_t receiver_destination_address[6];
    tech_byte_t transmitter_source_address[6];
    tech_byte_t bssid[6];
    struct{
        uint16_t fragment_number:4;
        uint16_t sequence_number:12;
    };
    struct{ // Fixed parameters
        tech_byte_t timestamp[8];
        uint16_t beacon_interval;
        uint16_t capabilities_information;
    }fixed_parameters;

}tech_network_ieee80211_disassociation_t;


typedef struct tech_network_ieee80211_authentication_struct_t{
    struct{ // Frame Control
        tech_byte_t version:2;
        tech_byte_t type:2;
        tech_byte_t subtype:4;
        tech_byte_t flags;
    };
    uint16_t duration;
    tech_byte_t receiver_destination_address[6];
    tech_byte_t transmitter_source_address[6];
    tech_byte_t bssid[6];
    struct{
        uint16_t fragment_number:4;
        uint16_t sequence_number:12;
    };
    struct{ // Fixed parameters
        uint16_t authentication_algorithm;
        uint16_t authentication_seq;
        uint16_t status_code;
    }fixed_parameters;
}tech_network_ieee80211_authentication_t;


typedef struct tech_network_ieee80211_deauthentication_struct_t{
    struct{ // Frame Control
        tech_byte_t version:2;
        tech_byte_t type:2;
        tech_byte_t subtype:4;
        tech_byte_t flags;
    };
    uint16_t duration;
    tech_byte_t receiver_destination_address[6];
    tech_byte_t transmitter_source_address[6];
    tech_byte_t bssid[6];
    struct{
        uint16_t fragment_number:4;
        uint16_t sequence_number:12;
    };
    struct{ // Fixed parameters
        uint16_t reason_code;
    }fixed_parameters;
}tech_network_ieee80211_deauthentication_t;


typedef struct tech_network_ieee80211_action_struct_t{
    struct{ // Frame Control
        tech_byte_t version:2;
        tech_byte_t type:2;
        tech_byte_t subtype:4;
        tech_byte_t flags;
    };
    uint16_t duration;
    tech_byte_t receiver_destination_address[6];
    tech_byte_t transmitter_source_address[6];
    tech_byte_t bssid[6];
    struct{
        uint16_t fragment_number:4;
        uint16_t sequence_number:12;
    };
    struct{ // Fixed parameters
        uint8_t category_code;
        uint8_t action_code;
        struct{
            uint16_t reserved:11;
            uint16_t initiator:1;
            uint16_t TID:4;
        }delete_block_ack;

    }fixed_parameters;
}tech_network_ieee80211_action_t;


typedef struct tech_network_ieee80211_generic_management_frame_struct_t{
    struct{ // Frame Control
        tech_byte_t version:2;
        tech_byte_t type:2;
        tech_byte_t subtype:4;
        tech_byte_t flags;
    };
    uint16_t duration;
    tech_byte_t receiver_destination_address[6];
    tech_byte_t transmitter_source_address[6];
    tech_byte_t bssid[6];
    struct{
        uint16_t fragment_number:4;
        uint16_t sequence_number:12;
    };    
}tech_network_ieee80211_generic_management_frame_t;



// Control Frames

typedef struct tech_network_ieee80211_block_ack_request_struct_t{
    struct{ // Frame Control
        tech_byte_t version:2;
        tech_byte_t type:2;
        tech_byte_t subtype:4;
        tech_byte_t flags;
    };
    uint16_t duration;
    tech_byte_t receiver_address[6];
    tech_byte_t transmitter_address[6];
    struct{ // Compressed Block Ack

        struct{
            uint16_t ba_ack_policy:1;
            uint16_t ba_type:4;
            uint16_t reserved:7;
            uint16_t TID:4;

        }control;

        struct{
            uint16_t fragment:4;
            uint16_t starting_sequence_number:12;
        }starting_sequence_conrol;

    }compressed_block_ack;
}tech_network_ieee80211_block_ack_request_t;


typedef struct tech_network_ieee80211_block_ack_struct_t{
    struct{ // Frame Control
        tech_byte_t version:2;
        tech_byte_t type:2;
        tech_byte_t subtype:4;
        tech_byte_t flags;
    };
    uint16_t duration;
    tech_byte_t receiver_address[6];
    tech_byte_t transmitter_address[6];
    
    struct{ // Compressed Block Ack

        struct{
            uint16_t ba_ack_policy:1;
            uint16_t ba_type:4;
            uint16_t reserved:7;
            uint16_t TID:4;

        }control;

        struct{
            uint16_t fragment:4;
            uint16_t starting_sequence_number:12;
        }starting_sequence_conrol;

        struct{
            tech_byte_t map[8];
        }bitmap;
        
    }compressed_block_ack;
}tech_network_ieee80211_block_ack_t;


typedef struct tech_network_ieee80211_request_to_send_struct_t{
    struct{ // Frame Control
        tech_byte_t version:2;
        tech_byte_t type:2;
        tech_byte_t subtype:4;
        tech_byte_t flags;
    };
    uint16_t duration;
    tech_byte_t receiver_address[6];
    tech_byte_t transmitter_address[6];
    
}tech_network_ieee80211_request_to_send_t;


typedef struct tech_network_ieee80211_clear_to_send_struct_t{
    struct{ // Frame Control
        tech_byte_t version:2;
        tech_byte_t type:2;
        tech_byte_t subtype:4;
        tech_byte_t flags;
    };
    uint16_t duration;
    tech_byte_t receiver_address[6];
    

}tech_network_ieee80211_clear_to_send_t;


typedef struct tech_network_ieee80211_acknowledgement_struct_t{
    struct{ // Frame Control
        tech_byte_t version:2;
        tech_byte_t type:2;
        tech_byte_t subtype:4;
        tech_byte_t flags;
    };
    uint16_t duration;
    tech_byte_t receiver_address[6];
        
}tech_network_ieee80211_acknowledgement_t;


typedef struct tech_network_ieee80211_cf_end_struct_t{
    struct{ // Frame Control
        tech_byte_t version:2;
        tech_byte_t type:2;
        tech_byte_t subtype:4;
        tech_byte_t flags;
    };
    uint16_t duration;
    tech_byte_t receiver_address[6];
    tech_byte_t bssid[6];

}tech_network_ieee80211_cf_end_t;



// Data Frames

typedef struct tech_network_ieee80211_data_struct_t{
    struct{ // Frame Control
        tech_byte_t version:2;
        tech_byte_t type:2;
        tech_byte_t subtype:4;
        tech_byte_t flags;
    };
    uint16_t duration;
    tech_byte_t receiver_destination_address[6];
    tech_byte_t transmitter_bssid_address[6];
    tech_byte_t source_address[6];
    struct{
        uint16_t fragment_number:4;
        uint16_t sequence_number:12;
    };
    struct{
        uint64_t TKIP_Ext;
    }TKIP_parameters;
    // Data part starts from here

}tech_network_ieee80211_data_t;


typedef struct tech_network_ieee80211_null_data_struct_t{
    struct{ // Frame Control
        tech_byte_t version:2;
        tech_byte_t type:2;
        tech_byte_t subtype:4;
        tech_byte_t flags;
    };
    uint16_t duration;
    tech_byte_t receiver_bssid_address[6];
    tech_byte_t transmitter_source_sta_address[6];
    tech_byte_t destination_address[6];
    struct{
        uint16_t fragment_number:4;
        uint16_t sequence_number:12;
    };    

}tech_network_ieee80211_null_data_t;


typedef struct tech_network_ieee80211_qos_data_struct_t{
    struct{ // Frame Control
        tech_byte_t version:2;
        tech_byte_t type:2;
        tech_byte_t subtype:4;
        tech_byte_t flags;
    };
    uint16_t duration;
    tech_byte_t receiver_bssid_address[6];
    tech_byte_t transmitter_source_sta_address[6];
    tech_byte_t destination_address[6];
    struct{
        uint16_t fragment_number:4;
        uint16_t sequence_number:12;
    };
    uint16_t qos_control;
    tech_byte_t CCMP_Ext[8];
    // Data part starts from here
}tech_network_ieee80211_qos_data_t;


typedef struct tech_network_ieee80211_qos_null_struct_t{
    struct{ // Frame Control
        tech_byte_t version:2;
        tech_byte_t type:2;
        tech_byte_t subtype:4;
        tech_byte_t flags;
    };
    uint16_t duration;
    tech_byte_t receiver_bssid_address[6];
    tech_byte_t transmitter_source_sta_address[6];
    tech_byte_t destination_address[6];
    struct{
        uint16_t fragment_number:4;
        uint16_t sequence_number:12;
    };
    uint16_t qos_control;
}tech_network_ieee80211_qos_null_t;


//tech_return_t tech_network_ieee80211_frame_find_tagged_parameter(tech_network_ieee80211_tagged_parameter_t tagged_parameter, tech_byte_t* tagged_parameter_data, tech_size_t total_length, tech_byte_t** data_bytes, tech_size_t* data_size);



#ifdef __cplusplus
	}
#endif

#endif