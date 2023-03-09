#ifndef TECH_NETWORK_IEEE80211_RADIOTAP_H
#define TECH_NETWORK_IEEE80211_RADIOTAP_H

#define TECH_NETWORK_IEEE80211_RADIOTAP_VERSION 0

#include <tech/config/features.h>
#include <tech/shared/include.h>
#include <tech/shared/types.h>

#ifdef __cplusplus
	extern "C" {
#endif


typedef struct tech_network_ieee80211_radiotap_header_struct_t {

	uint8_t version;

	uint8_t padding;

	uint16_t length;

	uint32_t present_flags;

}network_ieee80211_radiotap_header_t;


typedef struct tech_network_ieee80211_radiotap_align_size_struct_t {
	uint8_t align:4, size:4;
}tech_network_ieee80211_radiotap_align_size_t;


extern const tech_network_ieee80211_radiotap_align_size_t tech_radiotap_namespace_sizes[23];


typedef enum tech_network_ieee80211_radiotap_presence_enum_t {
	TECH_NETWORK_IEEE80211_RADIOTAP_TSFT = 0,
	TECH_NETWORK_IEEE80211_RADIOTAP_FLAGS = 1,
	TECH_NETWORK_IEEE80211_RADIOTAP_RATE = 2,
	TECH_NETWORK_IEEE80211_RADIOTAP_CHANNEL = 3,
	TECH_NETWORK_IEEE80211_RADIOTAP_FHSS = 4,
	TECH_NETWORK_IEEE80211_RADIOTAP_DBM_ANTSIGNAL = 5,
	TECH_NETWORK_IEEE80211_RADIOTAP_DBM_ANTNOISE = 6,
	TECH_NETWORK_IEEE80211_RADIOTAP_LOCK_QUALITY = 7,
	TECH_NETWORK_IEEE80211_RADIOTAP_TX_ATTENUATION = 8,
	TECH_NETWORK_IEEE80211_RADIOTAP_DB_TX_ATTENUATION = 9,
	TECH_NETWORK_IEEE80211_RADIOTAP_DBM_TX_POWER = 10,
	TECH_NETWORK_IEEE80211_RADIOTAP_ANTENNA = 11,
	TECH_NETWORK_IEEE80211_RADIOTAP_DB_ANTSIGNAL = 12,
	TECH_NETWORK_IEEE80211_RADIOTAP_DB_ANTNOISE = 13,
	TECH_NETWORK_IEEE80211_RADIOTAP_RX_FLAGS = 14,
	TECH_NETWORK_IEEE80211_RADIOTAP_TX_FLAGS = 15,
	TECH_NETWORK_IEEE80211_RADIOTAP_RTS_RETRIES = 16,
	TECH_NETWORK_IEEE80211_RADIOTAP_DATA_RETRIES = 17,
	/* 18 is XChannel, but it's not defined yet */
	TECH_NETWORK_IEEE80211_RADIOTAP_MCS = 19,
	TECH_NETWORK_IEEE80211_RADIOTAP_AMPDU_STATUS = 20,
	TECH_NETWORK_IEEE80211_RADIOTAP_VHT = 21,
	TECH_NETWORK_IEEE80211_RADIOTAP_TIMESTAMP = 22,

	/* valid in every it_present bitmap, even vendor namespaces */
	TECH_NETWORK_IEEE80211_RADIOTAP_RADIOTAP_NAMESPACE = 29,
	TECH_NETWORK_IEEE80211_RADIOTAP_VENDOR_NAMESPACE = 30,
	TECH_NETWORK_IEEE80211_RADIOTAP_EXT = 31,
	TECH_NETWORK_IEEE80211_RADIOTAP_DUMMY = 32
}tech_network_ieee80211_radiotap_presence_t;


typedef enum tech_network_ieee80211_radiotap_flags_enum_t {
	TECH_NETWORK_IEEE80211_RADIOTAP_F_CFP = 0x01,
	TECH_NETWORK_IEEE80211_RADIOTAP_F_SHORTPRE = 0x02,
	TECH_NETWORK_IEEE80211_RADIOTAP_F_WEP = 0x04,
	TECH_NETWORK_IEEE80211_RADIOTAP_F_FRAG = 0x08,
	TECH_NETWORK_IEEE80211_RADIOTAP_F_FCS = 0x10,
	TECH_NETWORK_IEEE80211_RADIOTAP_F_DATAPAD = 0x20,
	TECH_NETWORK_IEEE80211_RADIOTAP_F_BADFCS = 0x40,
}tech_network_ieee80211_radiotap_flags_t;

/* for NETWORK_IEEE80211_RADIOTAP_CHANNEL */
typedef enum tech_network_ieee80211_radiotap_channel_flags_enum_t {
	TECH_NETWORK_IEEE80211_CHAN_CCK = 0x0020,
	TECH_NETWORK_IEEE80211_CHAN_OFDM = 0x0040,
	TECH_NETWORK_IEEE80211_CHAN_2GHZ = 0x0080,
	TECH_NETWORK_IEEE80211_CHAN_5GHZ = 0x0100,
	TECH_NETWORK_IEEE80211_CHAN_DYN = 0x0400,
	TECH_NETWORK_IEEE80211_CHAN_HALF = 0x4000,
	TECH_NETWORK_IEEE80211_CHAN_QUARTER = 0x8000,
}tech_network_ieee80211_radiotap_channel_flags_t;


/* for NETWORK_IEEE80211_RADIOTAP_RX_FLAGS */
typedef enum tech_network_ieee80211_radiotap_rx_flags_enum_t {
	TECH_NETWORK_IEEE80211_RADIOTAP_F_RX_BADPLCP = 0x0002,
}tech_network_ieee80211_radiotap_rx_flags_t;

/* for NETWORK_IEEE80211_RADIOTAP_TX_FLAGS */
typedef enum tech_network_ieee80211_radiotap_tx_flags_enum_t {
	TECH_NETWORK_IEEE80211_RADIOTAP_F_TX_FAIL = 0x0001,
	TECH_NETWORK_IEEE80211_RADIOTAP_F_TX_CTS = 0x0002,
	TECH_NETWORK_IEEE80211_RADIOTAP_F_TX_RTS = 0x0004,
	TECH_NETWORK_IEEE80211_RADIOTAP_F_TX_NOACK = 0x0008,
}tech_network_ieee80211_radiotap_tx_flags_t;

/* for NETWORK_IEEE80211_RADIOTAP_MCS "have" flags */
typedef enum tech_network_ieee80211_radiotap_mcs_have_enum_t {
	TECH_NETWORK_IEEE80211_RADIOTAP_MCS_HAVE_BW = 0x01,
	TECH_NETWORK_IEEE80211_RADIOTAP_MCS_HAVE_MCS = 0x02,
	TECH_NETWORK_IEEE80211_RADIOTAP_MCS_HAVE_GI = 0x04,
	TECH_NETWORK_IEEE80211_RADIOTAP_MCS_HAVE_FMT = 0x08,
	TECH_NETWORK_IEEE80211_RADIOTAP_MCS_HAVE_FEC = 0x10,
	TECH_NETWORK_IEEE80211_RADIOTAP_MCS_HAVE_STBC = 0x20,
}tech_network_ieee80211_radiotap_mcs_have_t;

typedef enum tech_network_ieee80211_radiotap_mcs_flags_enum_t {
	TECH_NETWORK_IEEE80211_RADIOTAP_MCS_BW_MASK = 0x03,
	TECH_NETWORK_IEEE80211_RADIOTAP_MCS_BW_20 = 0,
	TECH_NETWORK_IEEE80211_RADIOTAP_MCS_BW_40 = 1,
	TECH_NETWORK_IEEE80211_RADIOTAP_MCS_BW_20L = 2,
	TECH_NETWORK_IEEE80211_RADIOTAP_MCS_BW_20U = 3,

	TECH_NETWORK_IEEE80211_RADIOTAP_MCS_SGI = 0x04,
	TECH_NETWORK_IEEE80211_RADIOTAP_MCS_FMT_GF = 0x08,
	TECH_NETWORK_IEEE80211_RADIOTAP_MCS_FEC_LDPC = 0x10,
	TECH_NETWORK_IEEE80211_RADIOTAP_MCS_STBC_MASK = 0x60,
	TECH_NETWORK_IEEE80211_RADIOTAP_MCS_STBC_1 = 1,
	TECH_NETWORK_IEEE80211_RADIOTAP_MCS_STBC_2 = 2,
	TECH_NETWORK_IEEE80211_RADIOTAP_MCS_STBC_3 = 3,
	TECH_NETWORK_IEEE80211_RADIOTAP_MCS_STBC_SHIFT = 5,
}tech_network_ieee80211_radiotap_mcs_flags_t;

/* for NETWORK_IEEE80211_RADIOTAP_AMPDU_STATUS */
typedef enum tech_network_ieee80211_radiotap_ampdu_flags_enum_t {
	TECH_NETWORK_IEEE80211_RADIOTAP_AMPDU_REPORT_ZEROLEN = 0x0001,
	TECH_NETWORK_IEEE80211_RADIOTAP_AMPDU_IS_ZEROLEN = 0x0002,
	TECH_NETWORK_IEEE80211_RADIOTAP_AMPDU_LAST_KNOWN = 0x0004,
	TECH_NETWORK_IEEE80211_RADIOTAP_AMPDU_IS_LAST = 0x0008,
	TECH_NETWORK_IEEE80211_RADIOTAP_AMPDU_DELIM_CRC_ERR = 0x0010,
	TECH_NETWORK_IEEE80211_RADIOTAP_AMPDU_DELIM_CRC_KNOWN = 0x0020,
}tech_network_ieee80211_radiotap_ampdu_flags_t;

/* for NETWORK_IEEE80211_RADIOTAP_VHT */
typedef enum tech_network_ieee80211_radiotap_vht_known_enum_t {
	TECH_NETWORK_IEEE80211_RADIOTAP_VHT_KNOWN_STBC = 0x0001,
	TECH_NETWORK_IEEE80211_RADIOTAP_VHT_KNOWN_TXOP_PS_NA = 0x0002,
	TECH_NETWORK_IEEE80211_RADIOTAP_VHT_KNOWN_GI = 0x0004,
	TECH_NETWORK_IEEE80211_RADIOTAP_VHT_KNOWN_SGI_NSYM_DIS = 0x0008,
	TECH_NETWORK_IEEE80211_RADIOTAP_VHT_KNOWN_LDPC_EXTRA_OFDM_SYM = 0x0010,
	TECH_NETWORK_IEEE80211_RADIOTAP_VHT_KNOWN_BEAMFORMED = 0x0020,
	TECH_NETWORK_IEEE80211_RADIOTAP_VHT_KNOWN_BANDWIDTH = 0x0040,
	TECH_NETWORK_IEEE80211_RADIOTAP_VHT_KNOWN_GROUP_ID = 0x0080,
	TECH_NETWORK_IEEE80211_RADIOTAP_VHT_KNOWN_PARTIAL_AID = 0x0100,
}tech_network_ieee80211_radiotap_vht_known_t;

typedef enum tech_network_ieee80211_radiotap_vht_flags_enum_t {
	TECH_NETWORK_IEEE80211_RADIOTAP_VHT_FLAG_STBC = 0x01,
	TECH_NETWORK_IEEE80211_RADIOTAP_VHT_FLAG_TXOP_PS_NA = 0x02,
	TECH_NETWORK_IEEE80211_RADIOTAP_VHT_FLAG_SGI = 0x04,
	TECH_NETWORK_IEEE80211_RADIOTAP_VHT_FLAG_SGI_NSYM_M10_9 = 0x08,
	TECH_NETWORK_IEEE80211_RADIOTAP_VHT_FLAG_LDPC_EXTRA_OFDM_SYM = 0x10,
	TECH_NETWORK_IEEE80211_RADIOTAP_VHT_FLAG_BEAMFORMED = 0x20,
}tech_network_ieee80211_radiotap_vht_flags_t;

typedef enum tech_network_ieee80211_radiotap_vht_coding_enum_t {
	TECH_NETWORK_IEEE80211_RADIOTAP_CODING_LDPC_USER0 = 0x01,
	TECH_NETWORK_IEEE80211_RADIOTAP_CODING_LDPC_USER1 = 0x02,
	TECH_NETWORK_IEEE80211_RADIOTAP_CODING_LDPC_USER2 = 0x04,
	TECH_NETWORK_IEEE80211_RADIOTAP_CODING_LDPC_USER3 = 0x08,
}tech_network_ieee80211_radiotap_vht_coding_t;

/* for NETWORK_IEEE80211_RADIOTAP_TIMESTAMP */
typedef enum tech_network_ieee80211_radiotap_timestamp_unit_spos_enum_t {
	TECH_NETWORK_IEEE80211_RADIOTAP_TIMESTAMP_UNIT_MASK = 0x000F,
	TECH_NETWORK_IEEE80211_RADIOTAP_TIMESTAMP_UNIT_MS = 0x0000,
	TECH_NETWORK_IEEE80211_RADIOTAP_TIMESTAMP_UNIT_US = 0x0001,
	TECH_NETWORK_IEEE80211_RADIOTAP_TIMESTAMP_UNIT_NS = 0x0003,
	TECH_NETWORK_IEEE80211_RADIOTAP_TIMESTAMP_SPOS_MASK = 0x00F0,
	TECH_NETWORK_IEEE80211_RADIOTAP_TIMESTAMP_SPOS_BEGIN_MDPU = 0x0000,
	TECH_NETWORK_IEEE80211_RADIOTAP_TIMESTAMP_SPOS_PLCP_SIG_ACQ = 0x0010,
	TECH_NETWORK_IEEE80211_RADIOTAP_TIMESTAMP_SPOS_EO_PPDU = 0x0020,
	TECH_NETWORK_IEEE80211_RADIOTAP_TIMESTAMP_SPOS_EO_MPDU = 0x0030,
	TECH_NETWORK_IEEE80211_RADIOTAP_TIMESTAMP_SPOS_UNKNOWN = 0x00F0,
}tech_network_ieee80211_radiotap_timestamp_unit_spos_t;


typedef enum tech_network_ieee80211_radiotap_timestamp_flags_enum_t {
	TECH_NETWORK_IEEE80211_RADIOTAP_TIMESTAMP_FLAG_64BIT = 0x00,
	TECH_NETWORK_IEEE80211_RADIOTAP_TIMESTAMP_FLAG_32BIT = 0x01,
	TECH_NETWORK_IEEE80211_RADIOTAP_TIMESTAMP_FLAG_ACCURACY = 0x02,
}tech_network_ieee80211_radiotap_timestamp_flags_t;


void tech_network_ieee80211_radiotap_initialize_align_size(tech_network_ieee80211_radiotap_align_size_t radiotap_align_size[23]);

/**
 *  First usage of the function cannot include NULL pointer to a memory address
 *  After using the function with a proper frame byte address, following usages with the address being NULL tries to find next occurences in the field if PRESENT
 *  Each usage with non-NULL address just finds the first occurence of the specified field index
 */
tech_byte_t* tech_network_ieee80211_radiotap_header_find_field(tech_network_ieee80211_radiotap_presence_t field_index,tech_byte_t* frame_bytes);



#ifdef __cplusplus
	}
#endif

#endif