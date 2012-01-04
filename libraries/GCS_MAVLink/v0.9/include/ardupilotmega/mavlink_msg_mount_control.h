// MESSAGE MOUNT_CONTROL PACKING

#define MAVLINK_MSG_ID_MOUNT_CONTROL 157

typedef struct __mavlink_mount_control_t 
{
	uint8_t target_system; ///< System ID
	uint8_t target_component; ///< Component ID
	int32_t input_a; ///< pitch(deg*100) or lat, depending on mount mode
	int32_t input_b; ///< roll(deg*100) or lon depending on mount mode
	int32_t input_c; ///< yaw(deg*100) or alt (in cm) depending on mount mode
	uint8_t save_position; ///< if "1" it will save current trimmed position on EEPROM (just valid for NEUTRAL and LANDING)

} mavlink_mount_control_t;



/**
 * @brief Pack a mount_control message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 *
 * @param target_system System ID
 * @param target_component Component ID
 * @param input_a pitch(deg*100) or lat, depending on mount mode
 * @param input_b roll(deg*100) or lon depending on mount mode
 * @param input_c yaw(deg*100) or alt (in cm) depending on mount mode
 * @param save_position if "1" it will save current trimmed position on EEPROM (just valid for NEUTRAL and LANDING)
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_mount_control_pack(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg, uint8_t target_system, uint8_t target_component, int32_t input_a, int32_t input_b, int32_t input_c, uint8_t save_position)
{
	uint16_t i = 0;
	msg->msgid = MAVLINK_MSG_ID_MOUNT_CONTROL;

	i += put_uint8_t_by_index(target_system, i, msg->payload); // System ID
	i += put_uint8_t_by_index(target_component, i, msg->payload); // Component ID
	i += put_int32_t_by_index(input_a, i, msg->payload); // pitch(deg*100) or lat, depending on mount mode
	i += put_int32_t_by_index(input_b, i, msg->payload); // roll(deg*100) or lon depending on mount mode
	i += put_int32_t_by_index(input_c, i, msg->payload); // yaw(deg*100) or alt (in cm) depending on mount mode
	i += put_uint8_t_by_index(save_position, i, msg->payload); // if "1" it will save current trimmed position on EEPROM (just valid for NEUTRAL and LANDING)

	return mavlink_finalize_message(msg, system_id, component_id, i);
}

/**
 * @brief Pack a mount_control message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message was sent over
 * @param msg The MAVLink message to compress the data into
 * @param target_system System ID
 * @param target_component Component ID
 * @param input_a pitch(deg*100) or lat, depending on mount mode
 * @param input_b roll(deg*100) or lon depending on mount mode
 * @param input_c yaw(deg*100) or alt (in cm) depending on mount mode
 * @param save_position if "1" it will save current trimmed position on EEPROM (just valid for NEUTRAL and LANDING)
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_mount_control_pack_chan(uint8_t system_id, uint8_t component_id, uint8_t chan, mavlink_message_t* msg, uint8_t target_system, uint8_t target_component, int32_t input_a, int32_t input_b, int32_t input_c, uint8_t save_position)
{
	uint16_t i = 0;
	msg->msgid = MAVLINK_MSG_ID_MOUNT_CONTROL;

	i += put_uint8_t_by_index(target_system, i, msg->payload); // System ID
	i += put_uint8_t_by_index(target_component, i, msg->payload); // Component ID
	i += put_int32_t_by_index(input_a, i, msg->payload); // pitch(deg*100) or lat, depending on mount mode
	i += put_int32_t_by_index(input_b, i, msg->payload); // roll(deg*100) or lon depending on mount mode
	i += put_int32_t_by_index(input_c, i, msg->payload); // yaw(deg*100) or alt (in cm) depending on mount mode
	i += put_uint8_t_by_index(save_position, i, msg->payload); // if "1" it will save current trimmed position on EEPROM (just valid for NEUTRAL and LANDING)

	return mavlink_finalize_message_chan(msg, system_id, component_id, chan, i);
}

/**
 * @brief Encode a mount_control struct into a message
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 * @param mount_control C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_mount_control_encode(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg, const mavlink_mount_control_t* mount_control)
{
	return mavlink_msg_mount_control_pack(system_id, component_id, msg, mount_control->target_system, mount_control->target_component, mount_control->input_a, mount_control->input_b, mount_control->input_c, mount_control->save_position);
}

/**
 * @brief Send a mount_control message
 * @param chan MAVLink channel to send the message
 *
 * @param target_system System ID
 * @param target_component Component ID
 * @param input_a pitch(deg*100) or lat, depending on mount mode
 * @param input_b roll(deg*100) or lon depending on mount mode
 * @param input_c yaw(deg*100) or alt (in cm) depending on mount mode
 * @param save_position if "1" it will save current trimmed position on EEPROM (just valid for NEUTRAL and LANDING)
 */
#ifdef MAVLINK_USE_CONVENIENCE_FUNCTIONS

static inline void mavlink_msg_mount_control_send(mavlink_channel_t chan, uint8_t target_system, uint8_t target_component, int32_t input_a, int32_t input_b, int32_t input_c, uint8_t save_position)
{
	mavlink_message_t msg;
	mavlink_msg_mount_control_pack_chan(mavlink_system.sysid, mavlink_system.compid, chan, &msg, target_system, target_component, input_a, input_b, input_c, save_position);
	mavlink_send_uart(chan, &msg);
}

#endif
// MESSAGE MOUNT_CONTROL UNPACKING

/**
 * @brief Get field target_system from mount_control message
 *
 * @return System ID
 */
static inline uint8_t mavlink_msg_mount_control_get_target_system(const mavlink_message_t* msg)
{
	return (uint8_t)(msg->payload)[0];
}

/**
 * @brief Get field target_component from mount_control message
 *
 * @return Component ID
 */
static inline uint8_t mavlink_msg_mount_control_get_target_component(const mavlink_message_t* msg)
{
	return (uint8_t)(msg->payload+sizeof(uint8_t))[0];
}

/**
 * @brief Get field input_a from mount_control message
 *
 * @return pitch(deg*100) or lat, depending on mount mode
 */
static inline int32_t mavlink_msg_mount_control_get_input_a(const mavlink_message_t* msg)
{
	generic_32bit r;
	r.b[3] = (msg->payload+sizeof(uint8_t)+sizeof(uint8_t))[0];
	r.b[2] = (msg->payload+sizeof(uint8_t)+sizeof(uint8_t))[1];
	r.b[1] = (msg->payload+sizeof(uint8_t)+sizeof(uint8_t))[2];
	r.b[0] = (msg->payload+sizeof(uint8_t)+sizeof(uint8_t))[3];
	return (int32_t)r.i;
}

/**
 * @brief Get field input_b from mount_control message
 *
 * @return roll(deg*100) or lon depending on mount mode
 */
static inline int32_t mavlink_msg_mount_control_get_input_b(const mavlink_message_t* msg)
{
	generic_32bit r;
	r.b[3] = (msg->payload+sizeof(uint8_t)+sizeof(uint8_t)+sizeof(int32_t))[0];
	r.b[2] = (msg->payload+sizeof(uint8_t)+sizeof(uint8_t)+sizeof(int32_t))[1];
	r.b[1] = (msg->payload+sizeof(uint8_t)+sizeof(uint8_t)+sizeof(int32_t))[2];
	r.b[0] = (msg->payload+sizeof(uint8_t)+sizeof(uint8_t)+sizeof(int32_t))[3];
	return (int32_t)r.i;
}

/**
 * @brief Get field input_c from mount_control message
 *
 * @return yaw(deg*100) or alt (in cm) depending on mount mode
 */
static inline int32_t mavlink_msg_mount_control_get_input_c(const mavlink_message_t* msg)
{
	generic_32bit r;
	r.b[3] = (msg->payload+sizeof(uint8_t)+sizeof(uint8_t)+sizeof(int32_t)+sizeof(int32_t))[0];
	r.b[2] = (msg->payload+sizeof(uint8_t)+sizeof(uint8_t)+sizeof(int32_t)+sizeof(int32_t))[1];
	r.b[1] = (msg->payload+sizeof(uint8_t)+sizeof(uint8_t)+sizeof(int32_t)+sizeof(int32_t))[2];
	r.b[0] = (msg->payload+sizeof(uint8_t)+sizeof(uint8_t)+sizeof(int32_t)+sizeof(int32_t))[3];
	return (int32_t)r.i;
}

/**
 * @brief Get field save_position from mount_control message
 *
 * @return if "1" it will save current trimmed position on EEPROM (just valid for NEUTRAL and LANDING)
 */
static inline uint8_t mavlink_msg_mount_control_get_save_position(const mavlink_message_t* msg)
{
	return (uint8_t)(msg->payload+sizeof(uint8_t)+sizeof(uint8_t)+sizeof(int32_t)+sizeof(int32_t)+sizeof(int32_t))[0];
}

/**
 * @brief Decode a mount_control message into a struct
 *
 * @param msg The message to decode
 * @param mount_control C-struct to decode the message contents into
 */
static inline void mavlink_msg_mount_control_decode(const mavlink_message_t* msg, mavlink_mount_control_t* mount_control)
{
	mount_control->target_system = mavlink_msg_mount_control_get_target_system(msg);
	mount_control->target_component = mavlink_msg_mount_control_get_target_component(msg);
	mount_control->input_a = mavlink_msg_mount_control_get_input_a(msg);
	mount_control->input_b = mavlink_msg_mount_control_get_input_b(msg);
	mount_control->input_c = mavlink_msg_mount_control_get_input_c(msg);
	mount_control->save_position = mavlink_msg_mount_control_get_save_position(msg);
}
