// MESSAGE MOUNT_STATUS PACKING

#define MAVLINK_MSG_ID_MOUNT_STATUS 158

typedef struct __mavlink_mount_status_t 
{
	uint8_t target_system; ///< System ID
	uint8_t target_component; ///< Component ID
	int32_t pointing_a; ///< pitch(deg*100) or lat, depending on mount mode
	int32_t pointing_b; ///< roll(deg*100) or lon depending on mount mode
	int32_t pointing_c; ///< yaw(deg*100) or alt (in cm) depending on mount mode

} mavlink_mount_status_t;



/**
 * @brief Pack a mount_status message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 *
 * @param target_system System ID
 * @param target_component Component ID
 * @param pointing_a pitch(deg*100) or lat, depending on mount mode
 * @param pointing_b roll(deg*100) or lon depending on mount mode
 * @param pointing_c yaw(deg*100) or alt (in cm) depending on mount mode
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_mount_status_pack(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg, uint8_t target_system, uint8_t target_component, int32_t pointing_a, int32_t pointing_b, int32_t pointing_c)
{
	uint16_t i = 0;
	msg->msgid = MAVLINK_MSG_ID_MOUNT_STATUS;

	i += put_uint8_t_by_index(target_system, i, msg->payload); // System ID
	i += put_uint8_t_by_index(target_component, i, msg->payload); // Component ID
	i += put_int32_t_by_index(pointing_a, i, msg->payload); // pitch(deg*100) or lat, depending on mount mode
	i += put_int32_t_by_index(pointing_b, i, msg->payload); // roll(deg*100) or lon depending on mount mode
	i += put_int32_t_by_index(pointing_c, i, msg->payload); // yaw(deg*100) or alt (in cm) depending on mount mode

	return mavlink_finalize_message(msg, system_id, component_id, i);
}

/**
 * @brief Pack a mount_status message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message was sent over
 * @param msg The MAVLink message to compress the data into
 * @param target_system System ID
 * @param target_component Component ID
 * @param pointing_a pitch(deg*100) or lat, depending on mount mode
 * @param pointing_b roll(deg*100) or lon depending on mount mode
 * @param pointing_c yaw(deg*100) or alt (in cm) depending on mount mode
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_mount_status_pack_chan(uint8_t system_id, uint8_t component_id, uint8_t chan, mavlink_message_t* msg, uint8_t target_system, uint8_t target_component, int32_t pointing_a, int32_t pointing_b, int32_t pointing_c)
{
	uint16_t i = 0;
	msg->msgid = MAVLINK_MSG_ID_MOUNT_STATUS;

	i += put_uint8_t_by_index(target_system, i, msg->payload); // System ID
	i += put_uint8_t_by_index(target_component, i, msg->payload); // Component ID
	i += put_int32_t_by_index(pointing_a, i, msg->payload); // pitch(deg*100) or lat, depending on mount mode
	i += put_int32_t_by_index(pointing_b, i, msg->payload); // roll(deg*100) or lon depending on mount mode
	i += put_int32_t_by_index(pointing_c, i, msg->payload); // yaw(deg*100) or alt (in cm) depending on mount mode

	return mavlink_finalize_message_chan(msg, system_id, component_id, chan, i);
}

/**
 * @brief Encode a mount_status struct into a message
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 * @param mount_status C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_mount_status_encode(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg, const mavlink_mount_status_t* mount_status)
{
	return mavlink_msg_mount_status_pack(system_id, component_id, msg, mount_status->target_system, mount_status->target_component, mount_status->pointing_a, mount_status->pointing_b, mount_status->pointing_c);
}

/**
 * @brief Send a mount_status message
 * @param chan MAVLink channel to send the message
 *
 * @param target_system System ID
 * @param target_component Component ID
 * @param pointing_a pitch(deg*100) or lat, depending on mount mode
 * @param pointing_b roll(deg*100) or lon depending on mount mode
 * @param pointing_c yaw(deg*100) or alt (in cm) depending on mount mode
 */
#ifdef MAVLINK_USE_CONVENIENCE_FUNCTIONS

static inline void mavlink_msg_mount_status_send(mavlink_channel_t chan, uint8_t target_system, uint8_t target_component, int32_t pointing_a, int32_t pointing_b, int32_t pointing_c)
{
	mavlink_message_t msg;
	mavlink_msg_mount_status_pack_chan(mavlink_system.sysid, mavlink_system.compid, chan, &msg, target_system, target_component, pointing_a, pointing_b, pointing_c);
	mavlink_send_uart(chan, &msg);
}

#endif
// MESSAGE MOUNT_STATUS UNPACKING

/**
 * @brief Get field target_system from mount_status message
 *
 * @return System ID
 */
static inline uint8_t mavlink_msg_mount_status_get_target_system(const mavlink_message_t* msg)
{
	return (uint8_t)(msg->payload)[0];
}

/**
 * @brief Get field target_component from mount_status message
 *
 * @return Component ID
 */
static inline uint8_t mavlink_msg_mount_status_get_target_component(const mavlink_message_t* msg)
{
	return (uint8_t)(msg->payload+sizeof(uint8_t))[0];
}

/**
 * @brief Get field pointing_a from mount_status message
 *
 * @return pitch(deg*100) or lat, depending on mount mode
 */
static inline int32_t mavlink_msg_mount_status_get_pointing_a(const mavlink_message_t* msg)
{
	generic_32bit r;
	r.b[3] = (msg->payload+sizeof(uint8_t)+sizeof(uint8_t))[0];
	r.b[2] = (msg->payload+sizeof(uint8_t)+sizeof(uint8_t))[1];
	r.b[1] = (msg->payload+sizeof(uint8_t)+sizeof(uint8_t))[2];
	r.b[0] = (msg->payload+sizeof(uint8_t)+sizeof(uint8_t))[3];
	return (int32_t)r.i;
}

/**
 * @brief Get field pointing_b from mount_status message
 *
 * @return roll(deg*100) or lon depending on mount mode
 */
static inline int32_t mavlink_msg_mount_status_get_pointing_b(const mavlink_message_t* msg)
{
	generic_32bit r;
	r.b[3] = (msg->payload+sizeof(uint8_t)+sizeof(uint8_t)+sizeof(int32_t))[0];
	r.b[2] = (msg->payload+sizeof(uint8_t)+sizeof(uint8_t)+sizeof(int32_t))[1];
	r.b[1] = (msg->payload+sizeof(uint8_t)+sizeof(uint8_t)+sizeof(int32_t))[2];
	r.b[0] = (msg->payload+sizeof(uint8_t)+sizeof(uint8_t)+sizeof(int32_t))[3];
	return (int32_t)r.i;
}

/**
 * @brief Get field pointing_c from mount_status message
 *
 * @return yaw(deg*100) or alt (in cm) depending on mount mode
 */
static inline int32_t mavlink_msg_mount_status_get_pointing_c(const mavlink_message_t* msg)
{
	generic_32bit r;
	r.b[3] = (msg->payload+sizeof(uint8_t)+sizeof(uint8_t)+sizeof(int32_t)+sizeof(int32_t))[0];
	r.b[2] = (msg->payload+sizeof(uint8_t)+sizeof(uint8_t)+sizeof(int32_t)+sizeof(int32_t))[1];
	r.b[1] = (msg->payload+sizeof(uint8_t)+sizeof(uint8_t)+sizeof(int32_t)+sizeof(int32_t))[2];
	r.b[0] = (msg->payload+sizeof(uint8_t)+sizeof(uint8_t)+sizeof(int32_t)+sizeof(int32_t))[3];
	return (int32_t)r.i;
}

/**
 * @brief Decode a mount_status message into a struct
 *
 * @param msg The message to decode
 * @param mount_status C-struct to decode the message contents into
 */
static inline void mavlink_msg_mount_status_decode(const mavlink_message_t* msg, mavlink_mount_status_t* mount_status)
{
	mount_status->target_system = mavlink_msg_mount_status_get_target_system(msg);
	mount_status->target_component = mavlink_msg_mount_status_get_target_component(msg);
	mount_status->pointing_a = mavlink_msg_mount_status_get_pointing_a(msg);
	mount_status->pointing_b = mavlink_msg_mount_status_get_pointing_b(msg);
	mount_status->pointing_c = mavlink_msg_mount_status_get_pointing_c(msg);
}
