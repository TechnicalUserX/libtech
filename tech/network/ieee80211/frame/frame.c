#include <tech/network/ieee80211/frame/frame.h>
#include <tech/util/include/error.h>

tech_return_t tech_network_ieee80211_frame_find_tagged_parameter(int tagged_parameter, tech_byte_t* tagged_parameter_data, tech_size_t total_length,tech_size_t* found_tagged_paramter_size,tech_byte_t** found_tagged_paramter_data){


    if(tagged_parameter_data == NULL || found_tagged_paramter_data == NULL || found_tagged_paramter_size == NULL){
        tech_error_number = TECH_ERROR_NULL_POINTER;
        return TECH_RETURN_FAILURE;
    }

    // If length is zero, there is nothing to return
    if(total_length == 0){
        *found_tagged_paramter_size = 0;
        *found_tagged_paramter_data = NULL;
        tech_error_number = TECH_ERROR_SIZE_ZERO;
        return TECH_RETURN_FAILURE;
    }
    // This guarantees that at least one tagged parameter exists


    // Assuming the frame_data pointer points to the start of the tagged parameter

    size_t current_byte_offset = 0;


    tech_network_ieee80211_tagged_parameter_indicator_t* indicator = (tech_network_ieee80211_tagged_parameter_indicator_t*)tagged_parameter_data;


    do{

        indicator = indicator + current_byte_offset;
        if(tagged_parameter == indicator->tag_number){

            // return std::tuple<byte_t*,size_t>{tagged_parameter_data+current_byte_offset+sizeof(struct ieee80211_tagged_parameter_indicator), indicator->tag_length};

            *found_tagged_paramter_size = indicator->tag_length;
            *found_tagged_paramter_data = tagged_parameter_data+current_byte_offset+sizeof(tech_network_ieee80211_tagged_parameter_indicator_t);
            tech_error_number = TECH_SUCCESS;
            return TECH_RETURN_SUCCESS;

        }else{
            current_byte_offset += sizeof(tech_network_ieee80211_tagged_parameter_indicator_t) + indicator->tag_length;           
        }
    }while(current_byte_offset != (total_length-1));


        *found_tagged_paramter_size = 0;
        *found_tagged_paramter_data = NULL;
        tech_error_number = TECH_ERROR_VALUE_NOT_FOUND;
        return TECH_RETURN_FAILURE;
}


