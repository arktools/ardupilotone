// MESSAGE MOUNT_CONFIGURE PACKING

#define MAVLINK_MSG_ID_MOUNT_CONFIGURE 156

typedef struct __mavlink_mount_configure_t 
{
	uint8_t target_system; ///< System ID
	uint8_t target_component; ///< Component ID
	uint8_t mount_mode; ///< mount operating mode (see MAV_MOUNT_MODE enum)
	uint8_t stab_roll; ///< (1 = yes, 0 = no)
	uint8_t stab_pitch; ///< (1 = yes, 0 = no)
	uint8_t stab_yaw; ///< (1 = yes, 0 = no)

} mavlink_mount_configure_t;



/**
 * @brief Pack a mount_configure message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 *
 * @param target_system System ID
 * @param target_component Component ID
 * @param mount_mode mount operating mode (see MAV_MOUNT_MODE enum)
 * @param stab_roll (1 = yes, 0 = no)
 * @param stab_pitch (1 = yes, 0 = no)
 * @param stab_yaw (1 = yes, 0 = no)
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_mount_configure_pack(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg, uint8_t target_system, uint8_t target_component, uint8_t mount_mode, uint8_t stab_roll, uint8_t stab_pitch, uint8_t stab_yaw)
{
	uint16_t i = 0;
	msg->msgid = MAVLINK_MSG_ID_MOUNT_CONFIGURE;

	i += put_uint8_t_by_index(target_system, i, msg->payload); // System ID
	i += put_uint8_t_by_index(target_component, i, msg->payload); // Component ID
	i += put_uint8_t_by_index(mount_mode, i, msg->payload); // mount operating mode (see MAV_MOUNT_MODE enum)
	i += put_uint8_t_by_index(stab_roll, i, msg->payload); // (1 = yes, 0 = no)
	i += put_uint8_t_by_index(stab_pitch, i, msg->payload); // (1 = yes, 0 = no)
	i += put_uint8_t_by_index(stab_yaw, i, msg->payload); // (1 = yes, 0 = no)

	return mavlink_finalize_message(msg, system_id, component_id, i);
}

/**
 * @brief Pack a mount_configure message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message was sent over
 * @param msg The MAVLink message to compress the data into
 * @param target_system System ID
 * @param target_component Component ID
 * @param mount_mode mount operating mode (see MAV_MOUNT_MODE enum)
 * @param stab_roll (1 = yes, 0 = no)
 * @param stab_pitch (1 = yes, 0 = no)
 * @param stab_yaw (1 = yes, 0 = no)
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_mount_configure_pack_chan(uint8_t system_id, uint8_t component_id, uint8_t chan, mavlink_message_t* msg, uint8_t target_system, uint8_t target_component, uint8_t mount_mode, uint8_t stab_roll, uint8_t stab_pitch, uint8_t stab_yaw)
{
	uint16_t i = 0;
	msg->msgid = MAVLINK_MSG_ID_MOUNT_CONFIGURE;

	i += put_uint8_t_by_index(target_system, i, msg->payload); // System ID
	i += put_uint8_t_by_index(target_component, i, msg->payload); // Component ID
	i += put_uint8_t_by_index(mount_mode, i, msg->payload); // mount operating mode (see MAV_MOUNT_MODE enum)
	i += put_uint8_t_by_index(stab_roll, i, msg->payload); // (1 = yes, 0 = no)
	i += put_uint8_t_by_index(stab_pitch, i, msg->payload); // (1 = yes, 0 = no)
	i += put_uint8_t_by_index(stab_yaw, i, msg->payload); // (1 = yes, 0 = no)

	return mavlink_finalize_message_chan(msg, system_id, component_id, chan, i);
}

/**
 * @brief Encode a mount_configure struct into a message
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 * @param mount_configure C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_mount_configure_encode(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg, const mavlink_mount_configure_t* mount_configure)
{
	return mavlink_msg_mount_configure_pack(system_id, component_id, msg, mount_configure->target_system, mount_configure->target_component, mount_configure->mount_mode, mount_configure->stab_roll, mount_configure->stab_pitch, mount_configure->stab_yaw);
}

/**
 * @brief Send a mount_configure message
 * @param chan MAVLink channel to send the message
 *
 * @param target_system System ID
 * @param target_component Component ID
 * @param mount_mode mount operating mode (see MAV_MOUNT_MODE enum)
 * @param stab_roll (1 = yes, 0 = no)
 * @param stab_pitch (1 = yes, 0 = no)
 * @param stab_yaw (1 = yes, 0 = no)
 */
#ifdef MAVLINK_USE_CONVENIENCE_FUNCTIONS

static inline void mavlink_msg_mount_configure_send(mavlink_channel_t chan, uint8_t target_system, uint8_t target_component, uint8_t mount_mode, uint8_t stab_roll, uint8_t stab_pitch, uint8_t stab_yaw)
{
	mavlink_message_t msg;
	mavlink_msg_mount_configure_pack_chan(mavlink_system.sysid, mavlink_system.compid, chan, &msg, target_system, target_component, mount_mode, stab_roll, stab_pitch, stab_yaw);
	mavlink_send_uart(chan, &msg);
}

#endif
// MESSAGE MOUNT_CONFIGURE UNPACKING

/**
 * @brief Get field target_system from mount_configure message
 *
 * @return System ID
 */
static inline uint8_t mavlink_msg_mount_configure_get_target_system(const mavlink_message_t* msg)
{
	return (uint8_t)(msg->payload)[0];
}

/**
 * @brief Get field target_component from mount_configure message
 *
 * @return Component ID
 */
static inline uint8_t mavlink_msg_mount_configure_get_target_component(const mavlink_message_t* msg)
{
	return (uint8_t)(msg->payload+sizeof(uint8_t))[0];
}

/**
 * @brief Get field mount_mode from mount_configure message
 *
 * @return mount operating mode (see MAV_MOUNT_MODE enum)
 */
static inline uint8_t mavlink_msg_mount_configure_get_mount_mode(const mavlink_message_t* msg)
{
	return (uint8_t)(msg->payload+sizeof(uint8_t)+sizeof(uint8_t))[0];
}

/**
 * @brief Get field stab_roll from mount_configure message
 *
 * @return (1 = yes, 0 = no)
 */
static inline uint8_t mavlink_msg_mount_configure_get_stab_roll(const mavlink_message_t* msg)
{
	return (uint8_t)(msg->payload+sizeof(uint8_t)+sizeof(uint8_t)+sizeof(uint8_t))[0];
}

/**
 * @brief Get field stab_pitch from mount_configure message
 *
 * @return (1 = yes, 0 = no)
 */
static inline uint8_t mavlink_msg_mount_configure_get_stab_pitch(const mavlink_message_t* msg)
{
	return (uint8_t)(msg->payload+sizeof(uint8_t)+sizeof(uint8_t)+sizeof(uint8_t)+sizeof(uint8_t))[0];
}

/**
 * @brief Get field stab_yaw from mount_configure message
 *
 * @return (1 = yes, 0 = no)
 */
static inline uint8_t mavlink_msg_mount_configure_get_stab_yaw(const mavlink_message_t* msg)
{
	return (uint8_t)(msg->payload+sizeof(uint8_t)+sizeof(uint8_t)+sizeof(uint8_t)+sizeof(uint8_t)+sizeof(uint8_t))[0];
}

/**
 * @brief Decode a mount_configure message into a struct
 *
 * @param msg The message to decode
 * @param mount_configure C-struct to decode the message contents into
 */
static inline void mavlink_msg_mount_configure_decode(const mavlink_message_t* msg, mavlink_mount_configure_t* mount_configure)
{
	mount_configure->target_system = mavlink_msg_mount_configure_get_target_system(msg);
	mount_configure->target_component = mavlink_msg_mount_configure_get_target_component(msg);
	mount_configure->mount_mode = mavlink_msg_mount_configure_get_mount_mode(msg);
	mount_configure->stab_roll = mavlink_msg_mount_configure_get_stab_roll(msg);
	mount_configure->stab_pitch = mavlink_msg_mount_configure_get_stab_pitch(msg);
	mount_configure->stab_yaw = mavlink_msg_mount_configure_get_stab_yaw(msg);
}
