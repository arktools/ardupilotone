// MESSAGE AP_ADC PACKING

#define MAVLINK_MSG_ID_AP_ADC 153

typedef struct __mavlink_ap_adc_t 
{
	uint16_t adc1; ///< ADC output 1
	uint16_t adc2; ///< ADC output 2
	uint16_t adc3; ///< ADC output 3
	uint16_t adc4; ///< ADC output 4
	uint16_t adc5; ///< ADC output 5
	uint16_t adc6; ///< ADC output 6

} mavlink_ap_adc_t;



/**
 * @brief Pack a ap_adc message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 *
 * @param adc1 ADC output 1
 * @param adc2 ADC output 2
 * @param adc3 ADC output 3
 * @param adc4 ADC output 4
 * @param adc5 ADC output 5
 * @param adc6 ADC output 6
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_ap_adc_pack(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg, uint16_t adc1, uint16_t adc2, uint16_t adc3, uint16_t adc4, uint16_t adc5, uint16_t adc6)
{
	uint16_t i = 0;
	msg->msgid = MAVLINK_MSG_ID_AP_ADC;

	i += put_uint16_t_by_index(adc1, i, msg->payload); // ADC output 1
	i += put_uint16_t_by_index(adc2, i, msg->payload); // ADC output 2
	i += put_uint16_t_by_index(adc3, i, msg->payload); // ADC output 3
	i += put_uint16_t_by_index(adc4, i, msg->payload); // ADC output 4
	i += put_uint16_t_by_index(adc5, i, msg->payload); // ADC output 5
	i += put_uint16_t_by_index(adc6, i, msg->payload); // ADC output 6

	return mavlink_finalize_message(msg, system_id, component_id, i);
}

/**
 * @brief Pack a ap_adc message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message was sent over
 * @param msg The MAVLink message to compress the data into
 * @param adc1 ADC output 1
 * @param adc2 ADC output 2
 * @param adc3 ADC output 3
 * @param adc4 ADC output 4
 * @param adc5 ADC output 5
 * @param adc6 ADC output 6
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_ap_adc_pack_chan(uint8_t system_id, uint8_t component_id, uint8_t chan, mavlink_message_t* msg, uint16_t adc1, uint16_t adc2, uint16_t adc3, uint16_t adc4, uint16_t adc5, uint16_t adc6)
{
	uint16_t i = 0;
	msg->msgid = MAVLINK_MSG_ID_AP_ADC;

	i += put_uint16_t_by_index(adc1, i, msg->payload); // ADC output 1
	i += put_uint16_t_by_index(adc2, i, msg->payload); // ADC output 2
	i += put_uint16_t_by_index(adc3, i, msg->payload); // ADC output 3
	i += put_uint16_t_by_index(adc4, i, msg->payload); // ADC output 4
	i += put_uint16_t_by_index(adc5, i, msg->payload); // ADC output 5
	i += put_uint16_t_by_index(adc6, i, msg->payload); // ADC output 6

	return mavlink_finalize_message_chan(msg, system_id, component_id, chan, i);
}

/**
 * @brief Encode a ap_adc struct into a message
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 * @param ap_adc C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_ap_adc_encode(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg, const mavlink_ap_adc_t* ap_adc)
{
	return mavlink_msg_ap_adc_pack(system_id, component_id, msg, ap_adc->adc1, ap_adc->adc2, ap_adc->adc3, ap_adc->adc4, ap_adc->adc5, ap_adc->adc6);
}

/**
 * @brief Send a ap_adc message
 * @param chan MAVLink channel to send the message
 *
 * @param adc1 ADC output 1
 * @param adc2 ADC output 2
 * @param adc3 ADC output 3
 * @param adc4 ADC output 4
 * @param adc5 ADC output 5
 * @param adc6 ADC output 6
 */
#ifdef MAVLINK_USE_CONVENIENCE_FUNCTIONS

static inline void mavlink_msg_ap_adc_send(mavlink_channel_t chan, uint16_t adc1, uint16_t adc2, uint16_t adc3, uint16_t adc4, uint16_t adc5, uint16_t adc6)
{
	mavlink_message_t msg;
	mavlink_msg_ap_adc_pack_chan(mavlink_system.sysid, mavlink_system.compid, chan, &msg, adc1, adc2, adc3, adc4, adc5, adc6);
	mavlink_send_uart(chan, &msg);
}

#endif
// MESSAGE AP_ADC UNPACKING

/**
 * @brief Get field adc1 from ap_adc message
 *
 * @return ADC output 1
 */
static inline uint16_t mavlink_msg_ap_adc_get_adc1(const mavlink_message_t* msg)
{
	generic_16bit r;
	r.b[1] = (msg->payload)[0];
	r.b[0] = (msg->payload)[1];
	return (uint16_t)r.s;
}

/**
 * @brief Get field adc2 from ap_adc message
 *
 * @return ADC output 2
 */
static inline uint16_t mavlink_msg_ap_adc_get_adc2(const mavlink_message_t* msg)
{
	generic_16bit r;
	r.b[1] = (msg->payload+sizeof(uint16_t))[0];
	r.b[0] = (msg->payload+sizeof(uint16_t))[1];
	return (uint16_t)r.s;
}

/**
 * @brief Get field adc3 from ap_adc message
 *
 * @return ADC output 3
 */
static inline uint16_t mavlink_msg_ap_adc_get_adc3(const mavlink_message_t* msg)
{
	generic_16bit r;
	r.b[1] = (msg->payload+sizeof(uint16_t)+sizeof(uint16_t))[0];
	r.b[0] = (msg->payload+sizeof(uint16_t)+sizeof(uint16_t))[1];
	return (uint16_t)r.s;
}

/**
 * @brief Get field adc4 from ap_adc message
 *
 * @return ADC output 4
 */
static inline uint16_t mavlink_msg_ap_adc_get_adc4(const mavlink_message_t* msg)
{
	generic_16bit r;
	r.b[1] = (msg->payload+sizeof(uint16_t)+sizeof(uint16_t)+sizeof(uint16_t))[0];
	r.b[0] = (msg->payload+sizeof(uint16_t)+sizeof(uint16_t)+sizeof(uint16_t))[1];
	return (uint16_t)r.s;
}

/**
 * @brief Get field adc5 from ap_adc message
 *
 * @return ADC output 5
 */
static inline uint16_t mavlink_msg_ap_adc_get_adc5(const mavlink_message_t* msg)
{
	generic_16bit r;
	r.b[1] = (msg->payload+sizeof(uint16_t)+sizeof(uint16_t)+sizeof(uint16_t)+sizeof(uint16_t))[0];
	r.b[0] = (msg->payload+sizeof(uint16_t)+sizeof(uint16_t)+sizeof(uint16_t)+sizeof(uint16_t))[1];
	return (uint16_t)r.s;
}

/**
 * @brief Get field adc6 from ap_adc message
 *
 * @return ADC output 6
 */
static inline uint16_t mavlink_msg_ap_adc_get_adc6(const mavlink_message_t* msg)
{
	generic_16bit r;
	r.b[1] = (msg->payload+sizeof(uint16_t)+sizeof(uint16_t)+sizeof(uint16_t)+sizeof(uint16_t)+sizeof(uint16_t))[0];
	r.b[0] = (msg->payload+sizeof(uint16_t)+sizeof(uint16_t)+sizeof(uint16_t)+sizeof(uint16_t)+sizeof(uint16_t))[1];
	return (uint16_t)r.s;
}

/**
 * @brief Decode a ap_adc message into a struct
 *
 * @param msg The message to decode
 * @param ap_adc C-struct to decode the message contents into
 */
static inline void mavlink_msg_ap_adc_decode(const mavlink_message_t* msg, mavlink_ap_adc_t* ap_adc)
{
	ap_adc->adc1 = mavlink_msg_ap_adc_get_adc1(msg);
	ap_adc->adc2 = mavlink_msg_ap_adc_get_adc2(msg);
	ap_adc->adc3 = mavlink_msg_ap_adc_get_adc3(msg);
	ap_adc->adc4 = mavlink_msg_ap_adc_get_adc4(msg);
	ap_adc->adc5 = mavlink_msg_ap_adc_get_adc5(msg);
	ap_adc->adc6 = mavlink_msg_ap_adc_get_adc6(msg);
}
