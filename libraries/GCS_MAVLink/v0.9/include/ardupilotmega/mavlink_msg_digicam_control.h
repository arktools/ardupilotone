// MESSAGE DIGICAM_CONTROL PACKING

#define MAVLINK_MSG_ID_DIGICAM_CONTROL 155

typedef struct __mavlink_digicam_control_t 
{
	uint8_t target_system; ///< System ID
	uint8_t target_component; ///< Component ID
	uint8_t session; ///< 0: stop, 1: start or keep it up //Session control e.g. show/hide lens
	uint8_t zoom_pos; ///< 1 to N //Zoom's absolute position (0 means ignore)
	int8_t zoom_step; ///< -100 to 100 //Zooming step value to offset zoom from the current position
	uint8_t focus_lock; ///< 0: unlock focus or keep unlocked, 1: lock focus or keep locked, 3: re-lock focus
	uint8_t shot; ///< 0: ignore, 1: shot or start filming
	uint8_t command_id; ///< Command Identity (incremental loop: 0 to 255)//A command sent multiple times will be executed or pooled just once
	uint8_t extra_param; ///< Extra parameters enumeration (0 means ignore)
	float extra_value; ///< Correspondent value to given extra_param

} mavlink_digicam_control_t;



/**
 * @brief Pack a digicam_control message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 *
 * @param target_system System ID
 * @param target_component Component ID
 * @param session 0: stop, 1: start or keep it up //Session control e.g. show/hide lens
 * @param zoom_pos 1 to N //Zoom's absolute position (0 means ignore)
 * @param zoom_step -100 to 100 //Zooming step value to offset zoom from the current position
 * @param focus_lock 0: unlock focus or keep unlocked, 1: lock focus or keep locked, 3: re-lock focus
 * @param shot 0: ignore, 1: shot or start filming
 * @param command_id Command Identity (incremental loop: 0 to 255)//A command sent multiple times will be executed or pooled just once
 * @param extra_param Extra parameters enumeration (0 means ignore)
 * @param extra_value Correspondent value to given extra_param
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_digicam_control_pack(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg, uint8_t target_system, uint8_t target_component, uint8_t session, uint8_t zoom_pos, int8_t zoom_step, uint8_t focus_lock, uint8_t shot, uint8_t command_id, uint8_t extra_param, float extra_value)
{
	uint16_t i = 0;
	msg->msgid = MAVLINK_MSG_ID_DIGICAM_CONTROL;

	i += put_uint8_t_by_index(target_system, i, msg->payload); // System ID
	i += put_uint8_t_by_index(target_component, i, msg->payload); // Component ID
	i += put_uint8_t_by_index(session, i, msg->payload); // 0: stop, 1: start or keep it up //Session control e.g. show/hide lens
	i += put_uint8_t_by_index(zoom_pos, i, msg->payload); // 1 to N //Zoom's absolute position (0 means ignore)
	i += put_int8_t_by_index(zoom_step, i, msg->payload); // -100 to 100 //Zooming step value to offset zoom from the current position
	i += put_uint8_t_by_index(focus_lock, i, msg->payload); // 0: unlock focus or keep unlocked, 1: lock focus or keep locked, 3: re-lock focus
	i += put_uint8_t_by_index(shot, i, msg->payload); // 0: ignore, 1: shot or start filming
	i += put_uint8_t_by_index(command_id, i, msg->payload); // Command Identity (incremental loop: 0 to 255)//A command sent multiple times will be executed or pooled just once
	i += put_uint8_t_by_index(extra_param, i, msg->payload); // Extra parameters enumeration (0 means ignore)
	i += put_float_by_index(extra_value, i, msg->payload); // Correspondent value to given extra_param

	return mavlink_finalize_message(msg, system_id, component_id, i);
}

/**
 * @brief Pack a digicam_control message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message was sent over
 * @param msg The MAVLink message to compress the data into
 * @param target_system System ID
 * @param target_component Component ID
 * @param session 0: stop, 1: start or keep it up //Session control e.g. show/hide lens
 * @param zoom_pos 1 to N //Zoom's absolute position (0 means ignore)
 * @param zoom_step -100 to 100 //Zooming step value to offset zoom from the current position
 * @param focus_lock 0: unlock focus or keep unlocked, 1: lock focus or keep locked, 3: re-lock focus
 * @param shot 0: ignore, 1: shot or start filming
 * @param command_id Command Identity (incremental loop: 0 to 255)//A command sent multiple times will be executed or pooled just once
 * @param extra_param Extra parameters enumeration (0 means ignore)
 * @param extra_value Correspondent value to given extra_param
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_digicam_control_pack_chan(uint8_t system_id, uint8_t component_id, uint8_t chan, mavlink_message_t* msg, uint8_t target_system, uint8_t target_component, uint8_t session, uint8_t zoom_pos, int8_t zoom_step, uint8_t focus_lock, uint8_t shot, uint8_t command_id, uint8_t extra_param, float extra_value)
{
	uint16_t i = 0;
	msg->msgid = MAVLINK_MSG_ID_DIGICAM_CONTROL;

	i += put_uint8_t_by_index(target_system, i, msg->payload); // System ID
	i += put_uint8_t_by_index(target_component, i, msg->payload); // Component ID
	i += put_uint8_t_by_index(session, i, msg->payload); // 0: stop, 1: start or keep it up //Session control e.g. show/hide lens
	i += put_uint8_t_by_index(zoom_pos, i, msg->payload); // 1 to N //Zoom's absolute position (0 means ignore)
	i += put_int8_t_by_index(zoom_step, i, msg->payload); // -100 to 100 //Zooming step value to offset zoom from the current position
	i += put_uint8_t_by_index(focus_lock, i, msg->payload); // 0: unlock focus or keep unlocked, 1: lock focus or keep locked, 3: re-lock focus
	i += put_uint8_t_by_index(shot, i, msg->payload); // 0: ignore, 1: shot or start filming
	i += put_uint8_t_by_index(command_id, i, msg->payload); // Command Identity (incremental loop: 0 to 255)//A command sent multiple times will be executed or pooled just once
	i += put_uint8_t_by_index(extra_param, i, msg->payload); // Extra parameters enumeration (0 means ignore)
	i += put_float_by_index(extra_value, i, msg->payload); // Correspondent value to given extra_param

	return mavlink_finalize_message_chan(msg, system_id, component_id, chan, i);
}

/**
 * @brief Encode a digicam_control struct into a message
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 * @param digicam_control C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_digicam_control_encode(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg, const mavlink_digicam_control_t* digicam_control)
{
	return mavlink_msg_digicam_control_pack(system_id, component_id, msg, digicam_control->target_system, digicam_control->target_component, digicam_control->session, digicam_control->zoom_pos, digicam_control->zoom_step, digicam_control->focus_lock, digicam_control->shot, digicam_control->command_id, digicam_control->extra_param, digicam_control->extra_value);
}

/**
 * @brief Send a digicam_control message
 * @param chan MAVLink channel to send the message
 *
 * @param target_system System ID
 * @param target_component Component ID
 * @param session 0: stop, 1: start or keep it up //Session control e.g. show/hide lens
 * @param zoom_pos 1 to N //Zoom's absolute position (0 means ignore)
 * @param zoom_step -100 to 100 //Zooming step value to offset zoom from the current position
 * @param focus_lock 0: unlock focus or keep unlocked, 1: lock focus or keep locked, 3: re-lock focus
 * @param shot 0: ignore, 1: shot or start filming
 * @param command_id Command Identity (incremental loop: 0 to 255)//A command sent multiple times will be executed or pooled just once
 * @param extra_param Extra parameters enumeration (0 means ignore)
 * @param extra_value Correspondent value to given extra_param
 */
#ifdef MAVLINK_USE_CONVENIENCE_FUNCTIONS

static inline void mavlink_msg_digicam_control_send(mavlink_channel_t chan, uint8_t target_system, uint8_t target_component, uint8_t session, uint8_t zoom_pos, int8_t zoom_step, uint8_t focus_lock, uint8_t shot, uint8_t command_id, uint8_t extra_param, float extra_value)
{
	mavlink_message_t msg;
	mavlink_msg_digicam_control_pack_chan(mavlink_system.sysid, mavlink_system.compid, chan, &msg, target_system, target_component, session, zoom_pos, zoom_step, focus_lock, shot, command_id, extra_param, extra_value);
	mavlink_send_uart(chan, &msg);
}

#endif
// MESSAGE DIGICAM_CONTROL UNPACKING

/**
 * @brief Get field target_system from digicam_control message
 *
 * @return System ID
 */
static inline uint8_t mavlink_msg_digicam_control_get_target_system(const mavlink_message_t* msg)
{
	return (uint8_t)(msg->payload)[0];
}

/**
 * @brief Get field target_component from digicam_control message
 *
 * @return Component ID
 */
static inline uint8_t mavlink_msg_digicam_control_get_target_component(const mavlink_message_t* msg)
{
	return (uint8_t)(msg->payload+sizeof(uint8_t))[0];
}

/**
 * @brief Get field session from digicam_control message
 *
 * @return 0: stop, 1: start or keep it up //Session control e.g. show/hide lens
 */
static inline uint8_t mavlink_msg_digicam_control_get_session(const mavlink_message_t* msg)
{
	return (uint8_t)(msg->payload+sizeof(uint8_t)+sizeof(uint8_t))[0];
}

/**
 * @brief Get field zoom_pos from digicam_control message
 *
 * @return 1 to N //Zoom's absolute position (0 means ignore)
 */
static inline uint8_t mavlink_msg_digicam_control_get_zoom_pos(const mavlink_message_t* msg)
{
	return (uint8_t)(msg->payload+sizeof(uint8_t)+sizeof(uint8_t)+sizeof(uint8_t))[0];
}

/**
 * @brief Get field zoom_step from digicam_control message
 *
 * @return -100 to 100 //Zooming step value to offset zoom from the current position
 */
static inline int8_t mavlink_msg_digicam_control_get_zoom_step(const mavlink_message_t* msg)
{
	return (int8_t)(msg->payload+sizeof(uint8_t)+sizeof(uint8_t)+sizeof(uint8_t)+sizeof(uint8_t))[0];
}

/**
 * @brief Get field focus_lock from digicam_control message
 *
 * @return 0: unlock focus or keep unlocked, 1: lock focus or keep locked, 3: re-lock focus
 */
static inline uint8_t mavlink_msg_digicam_control_get_focus_lock(const mavlink_message_t* msg)
{
	return (uint8_t)(msg->payload+sizeof(uint8_t)+sizeof(uint8_t)+sizeof(uint8_t)+sizeof(uint8_t)+sizeof(int8_t))[0];
}

/**
 * @brief Get field shot from digicam_control message
 *
 * @return 0: ignore, 1: shot or start filming
 */
static inline uint8_t mavlink_msg_digicam_control_get_shot(const mavlink_message_t* msg)
{
	return (uint8_t)(msg->payload+sizeof(uint8_t)+sizeof(uint8_t)+sizeof(uint8_t)+sizeof(uint8_t)+sizeof(int8_t)+sizeof(uint8_t))[0];
}

/**
 * @brief Get field command_id from digicam_control message
 *
 * @return Command Identity (incremental loop: 0 to 255)//A command sent multiple times will be executed or pooled just once
 */
static inline uint8_t mavlink_msg_digicam_control_get_command_id(const mavlink_message_t* msg)
{
	return (uint8_t)(msg->payload+sizeof(uint8_t)+sizeof(uint8_t)+sizeof(uint8_t)+sizeof(uint8_t)+sizeof(int8_t)+sizeof(uint8_t)+sizeof(uint8_t))[0];
}

/**
 * @brief Get field extra_param from digicam_control message
 *
 * @return Extra parameters enumeration (0 means ignore)
 */
static inline uint8_t mavlink_msg_digicam_control_get_extra_param(const mavlink_message_t* msg)
{
	return (uint8_t)(msg->payload+sizeof(uint8_t)+sizeof(uint8_t)+sizeof(uint8_t)+sizeof(uint8_t)+sizeof(int8_t)+sizeof(uint8_t)+sizeof(uint8_t)+sizeof(uint8_t))[0];
}

/**
 * @brief Get field extra_value from digicam_control message
 *
 * @return Correspondent value to given extra_param
 */
static inline float mavlink_msg_digicam_control_get_extra_value(const mavlink_message_t* msg)
{
	generic_32bit r;
	r.b[3] = (msg->payload+sizeof(uint8_t)+sizeof(uint8_t)+sizeof(uint8_t)+sizeof(uint8_t)+sizeof(int8_t)+sizeof(uint8_t)+sizeof(uint8_t)+sizeof(uint8_t)+sizeof(uint8_t))[0];
	r.b[2] = (msg->payload+sizeof(uint8_t)+sizeof(uint8_t)+sizeof(uint8_t)+sizeof(uint8_t)+sizeof(int8_t)+sizeof(uint8_t)+sizeof(uint8_t)+sizeof(uint8_t)+sizeof(uint8_t))[1];
	r.b[1] = (msg->payload+sizeof(uint8_t)+sizeof(uint8_t)+sizeof(uint8_t)+sizeof(uint8_t)+sizeof(int8_t)+sizeof(uint8_t)+sizeof(uint8_t)+sizeof(uint8_t)+sizeof(uint8_t))[2];
	r.b[0] = (msg->payload+sizeof(uint8_t)+sizeof(uint8_t)+sizeof(uint8_t)+sizeof(uint8_t)+sizeof(int8_t)+sizeof(uint8_t)+sizeof(uint8_t)+sizeof(uint8_t)+sizeof(uint8_t))[3];
	return (float)r.f;
}

/**
 * @brief Decode a digicam_control message into a struct
 *
 * @param msg The message to decode
 * @param digicam_control C-struct to decode the message contents into
 */
static inline void mavlink_msg_digicam_control_decode(const mavlink_message_t* msg, mavlink_digicam_control_t* digicam_control)
{
	digicam_control->target_system = mavlink_msg_digicam_control_get_target_system(msg);
	digicam_control->target_component = mavlink_msg_digicam_control_get_target_component(msg);
	digicam_control->session = mavlink_msg_digicam_control_get_session(msg);
	digicam_control->zoom_pos = mavlink_msg_digicam_control_get_zoom_pos(msg);
	digicam_control->zoom_step = mavlink_msg_digicam_control_get_zoom_step(msg);
	digicam_control->focus_lock = mavlink_msg_digicam_control_get_focus_lock(msg);
	digicam_control->shot = mavlink_msg_digicam_control_get_shot(msg);
	digicam_control->command_id = mavlink_msg_digicam_control_get_command_id(msg);
	digicam_control->extra_param = mavlink_msg_digicam_control_get_extra_param(msg);
	digicam_control->extra_value = mavlink_msg_digicam_control_get_extra_value(msg);
}
