#include <tech/network/adapter/wifi/adapter.h>



static inline tech_return_t tech_network_adapter_wifi_float_to_frequency(double float_frequency, struct iw_freq *frequency){


    if(frequency == NULL){
        tech_error_number = TECH_ERROR_NULL_POINTER;
        return TECH_RETURN_FAILURE;
    }

	frequency->e = (short) floor(log10(float_frequency));

	if (frequency->e > 8)
	{
        frequency->e -= 8;
		frequency->m = ((long) (floor(float_frequency / pow(10,frequency->e - 6)))) * 100;
	}
	else
	{
		frequency->e = 0;
		frequency->m = (long) float_frequency;
	}
    tech_error_number = TECH_SUCCESS;
    return TECH_RETURN_SUCCESS;
}

static inline tech_return_t tech_network_adapter_wifi_frequency_to_float(const struct iw_freq *freq, double* float_frequency){

    if(float_frequency == NULL){
        tech_error_number = TECH_ERROR_NULL_POINTER;
        return TECH_RETURN_FAILURE;
    }

    *float_frequency =  ((double) freq->m) * pow(10, freq->e);

    tech_error_number = TECH_SUCCESS;
	return TECH_RETURN_SUCCESS;
}

static inline tech_return_t tech_network_adapter_wifi_frequency_to_channel(tech_network_adapter_name_t adapter,double frequency, tech_network_adapter_wifi_channel_t* channel){


    if(adapter == NULL || channel == NULL){
        tech_error_number = TECH_ERROR_NULL_POINTER;
        return TECH_RETURN_FAILURE;
    }

    static bool internal_socket_initialized = false;
    static int internal_socket = 0;
    if(!internal_socket_initialized){
        internal_socket = socket(AF_INET, SOCK_DGRAM, 0);

        if(internal_socket == -1){
            tech_error_number = TECH_ERROR_NETWORK_CANNOT_CREATE_SOCKET;
            return TECH_RETURN_FAILURE;
        }else{
            // Initialization successfull
            internal_socket_initialized = true;
        }

    }


	struct iwreq wrq;
	char buffer[sizeof(struct iw_range) * 2];

	bzero(buffer, sizeof(buffer));
	wrq.u.data.pointer = buffer;
	wrq.u.data.length = sizeof(buffer);
	wrq.u.data.flags = 0;

	strncpy(wrq.ifr_name, adapter, IFNAMSIZ);

    if(ioctl(internal_socket, SIOCGIWRANGE, &wrq) < 0){
        tech_error_number = TECH_ERROR_BAD_SYSTEM_CALL;
        return TECH_RETURN_FAILURE;
    }else{

		struct iw_range *range = (struct iw_range *) buffer;

		for (int k = 0; k < range->num_frequency; k++){
            double temp_frequency = 0.0;
            if(tech_network_adapter_wifi_frequency_to_float(&(range->freq[k]),&temp_frequency)){
                // error number is set by above function
                return TECH_RETURN_FAILURE;
            }else{
                if (frequency == temp_frequency)
                {
                    *channel = range->freq[k].i;
                    tech_error_number = TECH_SUCCESS;
                    return TECH_RETURN_SUCCESS;
                }
            }


        }
        tech_error_number = TECH_ERROR_NETWORK_ADAPTER_WIFI_NO_CHANNEL_FOR_FREQUENCY;
        return TECH_RETURN_FAILURE;

    }


}


tech_return_t tech_network_adapter_wifi_parse_mode(int iw_mode,tech_network_adapter_wifi_mode_t* adapter_mode ){
	
    if(adapter_mode == NULL){
        tech_error_number = TECH_ERROR_NULL_POINTER;
        return TECH_RETURN_FAILURE;
    }
    
    switch (iw_mode)
	{
	case TECH_NETWORK_ADAPTER_WIFI_MODE_AUTO:
	case TECH_NETWORK_ADAPTER_WIFI_MODE_ADHOC:
	case TECH_NETWORK_ADAPTER_WIFI_MODE_MANAGED:
	case TECH_NETWORK_ADAPTER_WIFI_MODE_MASTER:
	case TECH_NETWORK_ADAPTER_WIFI_MODE_REPEAT:
	case TECH_NETWORK_ADAPTER_WIFI_MODE_SECOND:
	case TECH_NETWORK_ADAPTER_WIFI_MODE_MONITOR:
        *adapter_mode = (tech_network_adapter_wifi_mode_t)iw_mode;
        tech_error_number = TECH_SUCCESS;
        return TECH_RETURN_SUCCESS;
    default:
        tech_error_number = TECH_ERROR_NETWORK_ADAPTER_WIFI_MODE_UNKNOWN;
        return TECH_RETURN_FAILURE;
    }

}


tech_return_t tech_network_adapter_wifi_get_mode(tech_network_adapter_name_t adapter, tech_network_adapter_wifi_mode_t* mode){

    if(adapter == NULL || mode == NULL){
        tech_error_number = TECH_ERROR_NULL_POINTER;
        return TECH_RETURN_FAILURE;
    }

    static bool internal_socket_initialized = false;
    static int internal_socket = 0;
    if(!internal_socket_initialized){
        internal_socket = socket(AF_INET, SOCK_DGRAM, 0);

        if(internal_socket == -1){
            tech_error_number = TECH_ERROR_NETWORK_CANNOT_CREATE_SOCKET;
            return TECH_RETURN_FAILURE;
        }else{
            // Initialization successfull
            internal_socket_initialized = true;
        }

    }

	struct iwreq wrq;
	strncpy(wrq.ifr_name, adapter, IFNAMSIZ);
    
    if(ioctl(internal_socket, SIOCGIWMODE, &wrq) < 0){
        // Below function sets the error number already
        tech_error_number = TECH_ERROR_BAD_SYSTEM_CALL;
        return TECH_RETURN_FAILURE;
    }else{
        return tech_network_adapter_wifi_parse_mode(wrq.u.mode,mode);
    }

}


tech_return_t tech_network_adapter_wifi_get_operstate(tech_network_adapter_name_t adapter, tech_network_adapter_wifi_operstate_t* operstate){

    if(adapter == NULL && operstate == NULL){
        tech_error_number = TECH_ERROR_NULL_POINTER;
        return TECH_RETURN_FAILURE;
    }

    static bool internal_socket_initialized = false;
    static int internal_socket = 0;
    if(!internal_socket_initialized){
        internal_socket = socket(AF_INET, SOCK_DGRAM, 0);

        if(internal_socket == -1){
            tech_error_number = TECH_ERROR_NETWORK_CANNOT_CREATE_SOCKET;
            return TECH_RETURN_FAILURE;
        }else{
            // Initialization successfull
            internal_socket_initialized = true;
        }

    }

	struct ifreq ifr;

	strncpy(ifr.ifr_name, adapter, IFNAMSIZ);

    if( ioctl(internal_socket, SIOCGIFFLAGS, &ifr) < 0 ){
        tech_error_number = TECH_ERROR_BAD_SYSTEM_CALL;
        return TECH_RETURN_FAILURE;
    }else{

        if((ifr.ifr_flags & IFF_UP) == IFF_UP){
            // Up
            *operstate = TECH_NETWORK_ADAPTER_WIFI_OPERSTATE_UP;
        }else{
            // Down
            *operstate = TECH_NETWORK_ADAPTER_WIFI_OPERSTATE_DOWN;
        }

        tech_error_number = TECH_SUCCESS;
        return TECH_RETURN_SUCCESS;
    }

}


tech_return_t tech_network_adapter_wifi_get_frequency(tech_network_adapter_name_t adapter,double* frequency, tech_network_adapter_wifi_frequency_flag_t* flag){


    if(adapter == NULL || frequency == NULL || flag == NULL){
        tech_error_number = TECH_ERROR_NULL_POINTER;
        return TECH_RETURN_FAILURE;
    }

    static bool internal_socket_initialized = false;
    static int internal_socket = 0;
    if(!internal_socket_initialized){
        internal_socket = socket(AF_INET, SOCK_DGRAM, 0);

        if(internal_socket == -1){
            tech_error_number = TECH_ERROR_NETWORK_CANNOT_CREATE_SOCKET;
            return TECH_RETURN_FAILURE;
        }else{
            // Initialization successfull
            internal_socket_initialized = true;
        }

    }


    struct iwreq wrq;
	strncpy(wrq.ifr_name, adapter, IFNAMSIZ);

    if(ioctl(internal_socket, SIOCGIWFREQ, &wrq) < 0){
            tech_error_number = TECH_ERROR_BAD_SYSTEM_CALL;
            return TECH_RETURN_FAILURE;
    }else{
        if (IW_FREQ_AUTO == (wrq.u.freq.flags & IW_FREQ_AUTO)){
            *flag = TECH_NETWORK_ADAPTER_WIFI_FREQ_AUTO;
        }else if (IW_FREQ_FIXED == (wrq.u.freq.flags & IW_FREQ_FIXED)){
            *flag = TECH_NETWORK_ADAPTER_WIFI_FREQ_FIXED;
        }else{
            tech_error_number = TECH_ERROR_NETWORK_ADAPTER_WIFI_FREQUENCY_FLAG_UNKNOWN;
            return TECH_RETURN_FAILURE;
        }

        // This last function will determine the return value
        return tech_network_adapter_wifi_frequency_to_float(&(wrq.u.freq),frequency);
    }

}


tech_return_t tech_network_adapter_wifi_get_channel(tech_network_adapter_name_t adapter, tech_network_adapter_wifi_channel_t* channel){

    if(adapter == NULL || channel == NULL){
        tech_error_number = TECH_ERROR_NULL_POINTER;
        return TECH_RETURN_FAILURE;
    }


    tech_network_adapter_wifi_channel_t temp_channel;
    double temp_frequency;
    tech_network_adapter_wifi_frequency_flag_t temp_flag;

    if(tech_network_adapter_wifi_get_frequency(adapter,&temp_frequency,&temp_flag)){
        // error number is set by above function
        return TECH_RETURN_FAILURE;
    }else{

        if(tech_network_adapter_wifi_frequency_to_channel(adapter,temp_frequency,&temp_channel)){
            // error number is set by above function
            return TECH_RETURN_FAILURE;
        }else{

            *channel = temp_channel;
            tech_error_number = TECH_SUCCESS;
            return TECH_RETURN_SUCCESS;
        }

    }

}


tech_return_t tech_network_adapter_wifi_set_mode(tech_network_adapter_name_t adapter, tech_network_adapter_wifi_mode_t mode){
    char command[1024] = {0};
        strcat(command,"iw dev ");
        strcat(command,adapter);
        strcat(command," set type ");
    switch(mode){
        case TECH_NETWORK_ADAPTER_WIFI_MODE_MANAGED:
            strcat(command,"managed");
            break;
        case TECH_NETWORK_ADAPTER_WIFI_MODE_MONITOR:
            strcat(command,"monitor");
            break;
        case TECH_NETWORK_ADAPTER_WIFI_MODE_MASTER:
        case TECH_NETWORK_ADAPTER_WIFI_MODE_ADHOC:
        case TECH_NETWORK_ADAPTER_WIFI_MODE_REPEAT:
        case TECH_NETWORK_ADAPTER_WIFI_MODE_AUTO:
        case TECH_NETWORK_ADAPTER_WIFI_MODE_SECOND:
            tech_error_number = TECH_ERROR_NETWORK_ADAPTER_CANNOT_SET_MODE;
            return TECH_RETURN_FAILURE;

    }
    
    int ret = system(command);

    if(ret == 0){
        tech_error_number = TECH_SUCCESS;
        return TECH_RETURN_SUCCESS;
    }else{
        tech_error_number = TECH_ERROR_NETWORK_ADAPTER_CANNOT_SET_MODE;
        return TECH_RETURN_FAILURE;
    }

}


tech_return_t tech_network_adapter_wifi_set_operstate(tech_network_adapter_name_t adapter, tech_network_adapter_wifi_operstate_t operstate){

    char command[1024] = {0};
    strcat(command,"ip link set ");
    strcat(command,adapter);
    switch(operstate){
        case TECH_NETWORK_ADAPTER_WIFI_OPERSTATE_UP:
            strcat(command," up");
            break;
        case TECH_NETWORK_ADAPTER_WIFI_OPERSTATE_DOWN:
            strcat(command," down");
            break;
        default:
            tech_error_number = TECH_ERROR_NETWORK_ADAPTER_CANNOT_SET_OPERSTATE;
            return TECH_RETURN_FAILURE;
    }

    int ret = system(command);

    if(ret == 0){
        tech_error_number = TECH_SUCCESS;
        return TECH_RETURN_SUCCESS;
    }else{
        tech_error_number = TECH_ERROR_NETWORK_ADAPTER_CANNOT_SET_OPERSTATE;
        return TECH_RETURN_FAILURE;
    }

}


tech_return_t tech_network_adapter_wifi_set_channel(tech_network_adapter_name_t adapter, tech_network_adapter_wifi_channel_t channel){

    char command[1024] = {0};
    strcat(command,"iw dev ");
    strcat(command,adapter);
    strcat(command, " set channel ");
    char channel_number[16] = {0};
    sprintf(channel_number,"%d",channel);
    strcat(command, channel_number);

    int ret = system(command);

    if(ret == 0){
        tech_error_number = TECH_SUCCESS;
        return TECH_RETURN_SUCCESS;
    }else{
        tech_error_number = TECH_ERROR_NETWORK_ADAPTER_CANNOT_SET_OPERSTATE;
        return TECH_RETURN_FAILURE;
    }

}
