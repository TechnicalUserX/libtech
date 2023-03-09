#include <tech/network/ieee80211/radiotap/radiotap.h>


const tech_network_ieee80211_radiotap_align_size_t tech_radiotap_namespace_sizes[23] = {

	[TECH_NETWORK_IEEE80211_RADIOTAP_TSFT] = { .align = 8, .size = 8, },
	[TECH_NETWORK_IEEE80211_RADIOTAP_FLAGS] = { .align = 1, .size = 1, },
	[TECH_NETWORK_IEEE80211_RADIOTAP_RATE] = { .align = 1, .size = 1, },
	[TECH_NETWORK_IEEE80211_RADIOTAP_CHANNEL] = { .align = 2, .size = 4, },
	[TECH_NETWORK_IEEE80211_RADIOTAP_FHSS] = { .align = 2, .size = 2, },
	[TECH_NETWORK_IEEE80211_RADIOTAP_DBM_ANTSIGNAL] = { .align = 1, .size = 1, },
	[TECH_NETWORK_IEEE80211_RADIOTAP_DBM_ANTNOISE] = { .align = 1, .size = 1, },
	[TECH_NETWORK_IEEE80211_RADIOTAP_LOCK_QUALITY] = { .align = 2, .size = 2, },
	[TECH_NETWORK_IEEE80211_RADIOTAP_TX_ATTENUATION] = { .align = 2, .size = 2, },
	[TECH_NETWORK_IEEE80211_RADIOTAP_DB_TX_ATTENUATION] = { .align = 2, .size = 2, },
	[TECH_NETWORK_IEEE80211_RADIOTAP_DBM_TX_POWER] = { .align = 1, .size = 1, },
	[TECH_NETWORK_IEEE80211_RADIOTAP_ANTENNA] = { .align = 1, .size = 1, },
	[TECH_NETWORK_IEEE80211_RADIOTAP_DB_ANTSIGNAL] = { .align = 1, .size = 1, },
	[TECH_NETWORK_IEEE80211_RADIOTAP_DB_ANTNOISE] = { .align = 1, .size = 1, },
	[TECH_NETWORK_IEEE80211_RADIOTAP_RX_FLAGS] = { .align = 2, .size = 2, },
	[TECH_NETWORK_IEEE80211_RADIOTAP_TX_FLAGS] = { .align = 2, .size = 2, },
	[TECH_NETWORK_IEEE80211_RADIOTAP_RTS_RETRIES] = { .align = 1, .size = 1, },
	[TECH_NETWORK_IEEE80211_RADIOTAP_DATA_RETRIES] = { .align = 1, .size = 1, },
	[TECH_NETWORK_IEEE80211_RADIOTAP_MCS] = { .align = 1, .size = 3, },
	[TECH_NETWORK_IEEE80211_RADIOTAP_AMPDU_STATUS] = { .align = 4, .size = 8, },
	[TECH_NETWORK_IEEE80211_RADIOTAP_VHT] = { .align = 2, .size = 12, },
	[TECH_NETWORK_IEEE80211_RADIOTAP_TIMESTAMP] = { .align = 8, .size = 12, }

};


tech_byte_t* tech_network_ieee80211_radiotap_header_find_field(tech_network_ieee80211_radiotap_presence_t field_index, tech_byte_t* frame_bytes){


    static tech_byte_t* bytes = NULL;
        // If first usage of this function includes a NULL pointer to frame bytes, there is no point to proceed.
        
        if(bytes == frame_bytes && frame_bytes == NULL){
            return NULL;
        }

    static tech_network_ieee80211_radiotap_presence_t wanted_field = TECH_NETWORK_IEEE80211_RADIOTAP_DUMMY;
    static tech_size_t wanted_occurence = 1;
    static tech_size_t seen_occurence = 0;


    if(frame_bytes != NULL && bytes != frame_bytes){
        bytes = frame_bytes;
        wanted_occurence = 1;
        wanted_field = field_index;
    }
    else if(frame_bytes == bytes){
        wanted_occurence = 1;
        wanted_field = field_index;
    }
    else if(frame_bytes == NULL && wanted_field == field_index){
        wanted_occurence++;
    }
    else if(frame_bytes == NULL && wanted_field != field_index){
        wanted_occurence = 1;
        wanted_field = field_index;
    }



    tech_size_t present_flags_field_count = 1;
    uint32_t temporary_present_flags = *((uint32_t*)((bytes+4)+( 4*(present_flags_field_count-1) )));

    while(1){

        if(temporary_present_flags & 1<<TECH_NETWORK_IEEE80211_RADIOTAP_EXT){
            present_flags_field_count++;
            temporary_present_flags = *((uint32_t*)((bytes+4)+( 4*(present_flags_field_count-1) )));
        }else{
            break;
        }

    }


    seen_occurence = 0;
    size_t present_flags_index = 0;
    uint32_t present_flags = *(   (uint32_t*)(    (bytes+4) + (4*present_flags_index)  )   );
    // Location detection of wanted field...
    int index_counter = 0;
    int bit_mask = 0b1;        
    int total_byte_jump = 0;

    int search_field = 1<<wanted_field;

    //int previous_byte_jump = 0;

    while(1){
        if((bit_mask & present_flags)){

            if(bit_mask & search_field)
                seen_occurence++;


            if(( (bit_mask & search_field) && (seen_occurence == wanted_occurence) ))
                break;



            total_byte_jump += tech_radiotap_namespace_sizes[index_counter].size;
            if((total_byte_jump % 2 == 1) && (tech_radiotap_namespace_sizes[index_counter].size % 2 == 0)){
                total_byte_jump += 1;
            }

            // previous_byte_jump = tech_radiotap_namespace_sizes[index_counter].size;

        }


        index_counter++;
        bit_mask <<= 1;

        if( (index_counter == 31 ) && (bit_mask & present_flags) && (bit_mask & 1<<TECH_NETWORK_IEEE80211_RADIOTAP_EXT)){
            // This means there are STILL flags and there are STILL data!
            present_flags_index++;
            present_flags = *((uint32_t*)((bytes+4)+(4*present_flags_index)));
            bit_mask = 0b1;
            index_counter = 0;
            // Going into another loop with new present_flags...
            continue;
        }
        
        if(index_counter == 31 && !(bit_mask & present_flags) ){
            // Couldn't find!
            return TECH_RETURN_NULL;
        }
        


    } 

    //printf("Total byte jump: %d + %d + %d\n",total_byte_jump,4, 4*(present_flags_field_count));

    //printf("Stop index: %d\n\n",index_counter);

    return bytes + total_byte_jump + 4 + present_flags_field_count*4;
}
