// ECUProtocol.h was generated by ProtoGen version 3.2.a

/*
 * This file is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This file is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 * Author: Oliver Walters / Currawong Engineering Pty Ltd
 */
 

#ifndef _ECUPROTOCOL_H
#define _ECUPROTOCOL_H

// Language target is C, C++ compilers: don't mangle us
#ifdef __cplusplus
extern "C" {
#endif

/*!
 * \file
 * \mainpage ECU protocol stack
 * 
 * ECU ICD
 * 
 * The protocol API enumeration is incremented anytime the protocol is changed
 * in a way that affects compatibility with earlier versions of the protocol.
 * The protocol enumeration for this version is: 11
 * 
 * The protocol version is 7.0
 */

#include <stdbool.h>
#include <stdint.h>

//! \return the protocol API enumeration
#define getECUApi() 11

//! \return the protocol version string
#define getECUVersion() "7.0"

// Translation provided externally. The macro takes a `const char *` and returns a `const char *`
#ifndef translateECU
    #define translateECU(x) x
#endif

/*!
 * Enumeration defining RESET commands for ECU settings
 */
typedef enum
{
    ECU_RESET_THROTTLE = 0x01,//!< Reset throttle settings to default values
    ECU_RESET_PUMP = 0x02,   //!< Reset pump settings to default values
    ECU_RESET_GOVERNOR = 0x04,//!< Reset governor settings to default values
    ECU_RESET_TELEMETRY = 0x08,//!< Reset telemetry settings to default values
    ECU_RESET_ALL = 0xFF     //!< Reset all ECU settings to default values
} ECUResetCommands;

typedef enum
{
    ECU_DEBUG_RESET_STACK_OVERFLOW = 0x01,
    ECU_DEBUG_RESET_STACK_UNDERFLOW,     
    ECU_DEBUG_RESET_DIVIDE_BY_ZERO,      
    ECU_DEBUG_RESET_INFINITE_LOOP        
} ECUDebugResetTests;

/*!
 * ECU throttle position signal source enumeration
 */
typedef enum
{
    ECU_TPS_SRC_NONE = 0x00, //!< No throttle source
    ECU_TPS_SRC_RPM = 0x01,  //!< Throttle is commanded by RPM governor
    ECU_TPS_SRC_PWM = 0x02,  //!< Throttle is commanded from PWM input
    ECU_TPS_SRC_SERIAL = 0x04,//!< Throttle is commanded from serial command packet
    ECU_TPS_SRC_CAN = 0x08,  //!< Throttle is commanded from CAN command packet
    ECU_TPS_SRC_ANALOG = 0x0F //!< Throttle is commanded from analog input
} ECUThrottleSource;

typedef enum
{
    ECU_DUAL_PUMP_MODE_DISABLED = 0x00,//!< Both pumps disabled
    ECU_DUAL_PUMP_MODE_PRIMARY_CE,   //!< Primary pump running
    ECU_DUAL_PUMP_MODE_SECONDARY_TSA,//!< Secondary pump running
    ECU_DUAL_PUMP_MODE_BOTH          //!< Both pumps running
} DualFuelPumpMode;

typedef enum
{
    ECU_DUAL_PUMP_STATE_RESET = 0x00,//!< Pump state machine is in the initial reset state
    ECU_DUAL_PUMP_STATE_CMD,         //!< Pump was explicitly commanded to the current state
    ECU_DUAL_PUMP_STATE_TEST,        //!< Pump is running in manual test mode
    ECU_DUAL_PUMP_STATE_FAILURE      //!< Pump has switched over due to detected failure
} DualFuelPumpState;

typedef enum
{
    ECU_DUAL_PUMP_CMD_SET_PUMP = 0x01,//!< Switch to a particular pump mode
    ECU_DUAL_PUMP_CMD_TEST_PUMP = 0x02 //!< Temporarily switch to a particular pump mode
} DualFuelPumpCommands;

/*!
 * ECU packet identifier (ID) definitions
 */
typedef enum
{
    PKT_ECU_TELEMETRY_FAST = 0x00,       //!< High priority telemetry data from the ECU
    PKT_ECU_TELEMETRY_SLOW_0,            //!< First low priority telemetry packet from the ECU
    PKT_ECU_TELEMETRY_SLOW_1,            //!< Second low priority telemetry packet from the ECU
    PKT_ECU_TELEMETRY_SLOW_2,            //!< Third low priority telemetry packet from the ECU
    PKT_ECU_TELEMETRY_SLOW_3,            //!< Fourth low priority telemetry packet from the ECU (reserved for future use)
    PKT_ECU_THROTTLE_CALIBRATION = 0x05, //!< Throttle calibration values
    PKT_ECU_THROTTLE,                    //!< ECU throttle command
    PKT_ECU_THROTTLE_COMBINED,           //!< ECU Throttle command (position and pulse)
    PKT_ECU_RPM_COMMAND,                 //!< RPM setpoint command
    PKT_ECU_RPM_CALIBRATION,             //!< RPM control loop calibration values
    PKT_ECU_HARDWARE_CONFIG,             //!< Serial number information
    PKT_ECU_SOFTWARE_VERSION,            //!< Firmware version information
    PKT_ECU_TPS_DELAY_CONFIG,            //!< Throttle delay configuration
    PKT_ECU_TELEMETRY_SETTINGS,          //!< Telemetry configuration
    PKT_ECU_PUMP_CONFIG,                 //!< ECU Pump configuration packet 1 of 2
    PKT_ECU_ERROR_MSG,                   //!< Error messages
    PKT_ECU_POWER_CYCLES = 0x10,         //!< System information
    PKT_ECU_PUMP_2_CONFIG,               //!< ECU Pump configuration packet 2 of 2
    PKT_ECU_PUMP_DEBUG,                  //!< Pump debug information
    PKT_ECU_TOTAL_ENGINE_TIME,           //!< Total engine run-time
    PKT_ECU_SYS_CMD,                     //!< ECU System command
    PKT_ECU_USER_DATA,                   //!< User-configurable data bytes
    PKT_ECU_THROTTLE_CURVE_0,            //!< Throttle curve data, packet 1 of 2
    PKT_ECU_THROTTLE_CURVE_1,            //!< Throttle curve data, packet 2 of 2
    PKT_ECU_GPIO,                        //!< GPIO settings
    PKT_ECU_SETTINGS_DATA,               //!< Non-volatile settings information
    PKT_ECU_AUTRONIC_MEMORY,             //!< Read or write Autronic RAM
    PKT_ECU_CHT_LOOP,                    //!< Control loop settings for the CHT control loop
    PKT_ECU_CANAUTRONIC_RELAY = 0x1F     //!< Relay Autronic data across CAN
} ECUPackets;

//! \return the label of a 'ECUPackets' enum entry, based on its value
const char* ECUPackets_EnumLabel(int value);

typedef enum
{
    ECU_CE_CAL_TITLE_1 = 0xA0,
    ECU_CE_CAL_TITLE_2,      
    ECU_CE_CAL_TITLE_3       
} ECUSpecialPackets;

/*!
 * These system command identifiers are used with the [system
 * command](#PKT_ECU_SYS_CMD) packet.
 */
typedef enum
{
    CMD_ECU_CALIBRATE_ANALOG_CLOSED = 0x01,//!< Save the current value of the analog throttle position input as the 'Closed' position. To calibrate the closed analog input position, set the desired analog input level, and send this command to the ECU.
    CMD_ECU_CALIBRATE_ANALOG_OPEN,       //!< Save the current value of the analog throttle position input as the 'Open' position. To calibrate the open analog input position, set the desired analog input level, and send this command to the ECU.
    CMD_ECU_CALIBRATE_PULSE_CLOSED,      //!< Save the current value of the throttle output pulse width to a temporary variable in the ECU. When the CALIBRATE_PULSE_WRITE command is sent to the ECU, this value will be saved as the 'Closed' pulse width.
    CMD_ECU_CALIBRATE_PULSE_OPEN,        //!< Save the current value of the throttle output pulse width to a temporary variable in the ECU. When the CALIBRATE_PULSE_WRITE command is sent to the ECU, this value will be saved as the 'Open' pulse width.
    CMD_ECU_CALIBRATE_PULSE_WRITE,       //!< Configure the throttle output positions. The CALIBRATE_PULSE_CLOSED and CALIBRATE_PULSE_OPEN commands should have already been sent to the ECU. The ECU then saves the temporary values as the 'Closed' and 'Open' throttle output values, respectively.
    CMD_ECU_SET_OUTPUT_DRIVER = 0x0A,    //!< Set one of four high-current output drivers. Send two bytes after the command byte. Byte 1: Driver - Select driver number (1, 2, 3 or 4) Byte 2: Status - Set driver status (1 = ON, 0 = OFF)
    CMD_ECU_SET_THROTTLE_CURVE_ACTIVE,   //!< Turn the throttle linearization curve either on or off. Byte 1: 1 = ON  0 = OFF
    CMD_ECU_SET_THROTTLE_CURVE_ELEMENT,  //!< Set individual elements in the throttle linearization lookup table. Byte 1 = Element number (0 to 10, inclusive) Byte 2 = Value (0 to 200 inclusive)  Each bit of the 'value' byte represents  0.5% throttle. So, 0 = 0% and 200 = 100%
    CMD_ECU_REQUEST_THROTTLE_CURVE_DATA, //!< Request the throttle curve lookup table data. If requested on CAN, the data will be returned on CAN. If requested on RS232, the data will be returned on RS232.
    CMD_ECU_RESET_FUEL_USED = 0x10,      //!< Reset the FuelUsed value. This will set the FuelUsed data to zero.
    CMD_ECU_SET_FUEL_USED_DIVISOR,       //!< Configure the FuelUsed divisor. This is an unsigned 16-bit value. The fuel used value is divided by this divisor before being transmitted by the auxiliary processor. Set this value to 1 to leave the fuel used data unaffected. If you use values greater than 100 the divisor is automatically interpreted as being in units of 0.01 (i.e. 100 times the resolution).
    CMD_ECU_FUEL_USED_RESET_ON_STARTUP,  //!< Set or clear the Fuel Used reset flag. If this flag is set, the FuelUsed data will reset (to zero) when the ECU is power cycled. 1 = Reset Fuel Used data on powerup 0 = Do not reset Fuel Used data on power up
    CMD_ECU_SET_GOVERNOR_MODE = 0x20,    //!< Manually set the RPM governor mode Byte1 = MODE 0 = Governor Off (Open loop throttle control) 1 = Governor based on throttle command 2 = Governor based on RPM command
    CMD_ECU_SET_SERVO_CAN_MODE = 0x28,   
    CMD_ECU_RESET_INTO_BOOTLOADER = 0x30,//!< Reset the ECU into bootloader mode
    CMD_ECU_RESET_DEFAULT_SETTINGS,      //!< Set ECU settings to their default values
    CMD_ECU_SET_SERIAL_MODE = 0x40,      //!< Set the serial relay mode used for Autronic relay
    CMD_ECU_SET_NODE_ID = 0x50,          //!< Set the address (CAN node ID) for the ECU
    CMD_ECU_SET_USER_DATA = 0x60,        //!< Save a single byte of USER_DATA in EEPROM Byte1 = USER_DATA address (0 to 7) Byte2 = USER_DATA variable (0x00 to 0xFF)
    CMD_ECU_RESET_ENGINE_TIME = 0xA5,    //!< Reset the engine time counter. If no further bytes are sent after the RESET_ENGINE_TIME command, this will set the engine time (in seconds) to zero. Note that the 'Total Engine Time' counter is not reset. To set the engine time to a specific value, send the engine time in seconds as a 3-byte (big endian) number after the RESET_ENGINE_TIME command.
    CMD_ECU_RESET_ECU = 0xD0             //!< Cause a system reset
} ECUSystemCommands;

//! \return the label of a 'ECUSystemCommands' enum entry, based on its value
const char* ECUSystemCommands_EnumLabel(int value);


// The prototypes below provide an interface to the packets.
// They are not auto-generated functions, but must be hand-written

//! \return the packet data pointer from the packet
uint8_t* getECUPacketData(void* pkt);

//! \return the packet data pointer from the packet, const
const uint8_t* getECUPacketDataConst(const void* pkt);

//! Complete a packet after the data have been encoded
void finishECUPacket(void* pkt, int size, uint32_t packetID);

//! \return the size of a packet from the packet header
int getECUPacketSize(const void* pkt);

//! \return the ID of a packet from the packet header
uint32_t getECUPacketID(const void* pkt);

#ifdef __cplusplus
}
#endif
#endif // _ECUPROTOCOL_H