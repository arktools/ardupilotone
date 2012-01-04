// MESSAGE MEMINFO PACKING

#define MAVLINK_MSG_ID_MEMINFO 152

typedef struct __mavlink_meminfo_t 
{
	uint16_t brkval; ///< heap top
	uint16_t freemem; ///< free memory

} mavlink_meminfo_t;



/**
 * @brief Pack a meminfo message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 *
 * @param brkval heap top
 * @param freemem free memory
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_meminfo_pack(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg, uint16_t brkval, uint16_t freemem)
{
	uint16_t i = 0;
	msg->msgid = MAVLINK_MSG_ID_MEMINFO;

	i += put_uint16_t_by_index(brkval, i, msg->payload); // heap top
	i += put_uint16_t_by_index(freemem, i, msg->payload); // free memory

	return mavlink_finalize_message(msg, system_id, component_id, i);
}

/**
 * @brief Pack a meminfo message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message was sent over
 * @param msg The MAVLink message to compress the data into
 * @param brkval heap top
 * @param freemem free memory
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_meminfo_pack_chan(uint8_t system_id, uint8_t component_id, uint8_t chan, mavlink_message_t* msg, uint16_t brkval, uint16_t freemem)
{
	uint16_t i = 0;
	msg->msgid = MAVLINK_MSG_ID_MEMINFO;

	i += put_uint16_t_by_index(brkval, i, msg->payload); // heap top
	i += put_uint16_t_by_index(freemem, i, msg->payload); // free memory

	return mavlink_finalize_message_chan(msg, system_id, component_id, chan, i);
}

/**
 * @brief Encode a meminfo struct into a message
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 * @param meminfo C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_meminfo_encode(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg, const mavlink_meminfo_t* meminfo)
{
	return mavlink_msg_meminfo_pack(system_id, component_id, msg, meminfo->brkval, meminfo->freemem);
}

/**
 * @brief Send a meminfo message
 * @param chan MAVLink channel to send the message
 *
 * @param brkval heap top
 * @param freemem free memory
 */
#ifdef MAVLINK_USE_CONVENIENCE_FUNCTIONS

static inline void mavlink_msg_meminfo_send(mavlink_channel_t chan, uint16_t brkval, uint16_t freemem)
{
	mavlink_message_t msg;
	mavlink_msg_meminfo_pack_chan(mavlink_system.sysid, mavlink_system.compid, chan, &msg, brkval, freemem);
	mavlink_send_uart(chan, &msg);
}

#endif
// MESSAGE MEMINFO UNPACKING

/**
 * @brief Get field brkval from meminfo message
 *
 * @return heap top
 */
static inline uint16_t mavlink_msg_meminfo_get_brkval(const mavlink_message_t* msg)
{
	generic_16bit r;
	r.b[1] = (msg->payload)[0];
	r.b[0] = (msg->payload)[1];
	return (uint16_t)r.s;
}

/**
 * @brief Get field freemem from meminfo message
 *
 * @return free memory
 */
static inline uint16_t mavlink_msg_meminfo_get_freemem(const mavlink_message_t* msg)
{
	generic_16bit r;
	r.b[1] = (msg->payload+sizeof(uint16_t))[0];
	r.b[0] = (msg->payload+sizeof(uint16_t))[1];
	return (uint16_t)r.s;
}

/**
 * @brief Decode a meminfo message into a struct
 *
 * @param msg The message to decode
 * @param meminfo C-struct to decode the message contents into
 */
static inline void mavlink_msg_meminfo_decode(const mavlink_message_t* msg, mavlink_meminfo_t* meminfo)
{
	meminfo->brkval = mavlink_msg_meminfo_get_brkval(msg);
	meminfo->freemem = mavlink_msg_meminfo_get_freemem(msg);
}
