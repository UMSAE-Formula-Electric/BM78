/*
 * bm78.h
 *
 *  Created on: Jul 30, 2023
 */

#ifndef SRC_BM78_H_
#define SRC_BM78_H_

typedef enum {
	// Common
    BM78_CMD_READ_LOCAL_INFORMATION = 0x01,
    BM78_CMD_RESET = 0x02,
    BM78_CMD_READ_STATUS = 0x03,
    //BM78_CMD_READ_ADC_VALUE = 0x04,
    BM78_CMD_INTO_POWER_DOWN_MODE = 0x05,
    //BM78_CMD_DEBUG = 0x06,
    BM78_CMD_READ_DEVICE_NAME = 0x07,
    BM78_CMD_WRITE_DEVICE_NAME = 0x08,
    BM78_CMD_ERASE_ALL_PAIRED_DEVICE_INFO = 0x09,
    BM78_CMD_READ_PAIRING_MODE_SETTING = 0x0A,
    BM78_CMD_WRITE_PAIRING_MODE_SETTING = 0x0B,
    BM78_CMD_READ_ALL_PAIRED_DEVICE_INFO = 0x0C,
    BM78_CMD_DELETE_PAIRED_DEVICE = 0x0D,
} BM78_CommandOpCode_t;

typedef enum {
    // Common Events
    BM78_EVENT_COMMAND_COMPLETE = 0x80,
    BM78_EVENT_STATUS_REPORT = 0x81,
} BM78_EventOpCode_t;

// Single event states
typedef enum {
    BM78_STATE_IDLE = 0x00,
    BM78_EVENT_STATE_LENGTH_HIGH = 0x01,
    BM78_EVENT_STATE_LENGTH_LOW = 0x02,
    BM78_EVENT_STATE_OP_CODE = 0x03,
    BM78_EVENT_STATE_ADDITIONAL = 0x04,

    BM78_ISSC_EVENT_STATE_INIT = 0x81,
    BM78_ISSC_EVENT_STATE_LENGTH = 0x82,
    BM78_ISSC_EVENT_STATE_PACKET_TYPE = 0x83,
    BM78_ISSC_EVENT_STATE_OCF = 0x84,
    BM78_ISSC_EVENT_STATE_OGF = 0x85,
    BM78_ISSC_EVENT_STATE_STATUS = 0x86,
    BM78_ISSC_EVENT_STATE_DATA_ADDRESS_HIGH = 0x87,
    BM78_ISSC_EVENT_STATE_DATA_ADDRESS_LOW = 0x88,
    BM78_ISSC_EVENT_STATE_DATA_LENGTH = 0x89,
    BM78_ISSC_EVENT_STATE_DATA = 0x8A
} BM78_EventState_t;

/*
 * @brief Transmit the given message (data) to the BM78 module.
 *
 * @param length: The length of the message to be sent.
 * @param data: The message or data payload to be sent.
 *
 * @retval None.
 */
void BM78_sendPacket(uint8_t length, uint8_t *data);

/*
 * @brief Load the message buffer (data) with the sync value, command op code and length values.
 *
 * @param command: The op code representing the command to send to the BM78 module.
 * @param length: The length of the message.
 *
 * @retval None.
 *
 * Note:
 * - CRC value must be calculated and added to the message before transmission.
 * - Refer to section 2.2 in https://ww1.microchip.com/downloads/en/DeviceDoc/IS1678S_UARTCommandSet_UserGuide.pdf.
 */
inline void BM78_commandPrepareBuffer(BM78_CommandOpCode_t command, uint8_t length);

/*
 * @brief Calculate the CRC for the given message.
 *
 * @param length: The length of the message.
 *
 * @retval uint8_t: The calculated CRC for the given message.
 */
inline uint8_t BM78_commandCalculateChecksum(uint8_t length);

/*
 * @brief Send the message to the BM78 module and reset the idle counter.
 *
 * @param: length: The length of the message.
 *
 * @retval None.
 */
inline void BM78_commandCommit(uint8_t length);

/*
 * @brief Send the message to the BM78 module and reset the idle counter.
 *
 * @param command: The op code representing the command to send to the BM78 module.
 * @param length: The length of the message.
 * @param ...: Other relevant content for the command message.
 *
 * @retval None.
 *
 * Note:
 * = This function would be the only one called from main.c for the time being.
 */
void BM78_execute(BM78_CommandOpCode_t command, uint8_t length, ...);

#endif /* SRC_BM78_H_ */
