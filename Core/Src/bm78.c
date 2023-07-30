/*
 * bm78.c
 *
 *  Created on: Jul 30, 2023
 *
 *  Note: The following code are primary sourced from https://github.com/kubovy/mclib/blob/master/modules/bm78.c.
 */
#include "main.h"
#include "bm78.h"

//struct {
//    uint8_t index;                           // Byte index in a message.
//    BM78_Response_t response;                // Response.
//} BM78_rx = {0};

struct {
    uint8_t buffer[SCOM_MAX_PACKET_SIZE + 7];
} BM78_tx;

// Temporary.
uint8_t receiveMessage[100];

BM78_EventState_t BM78_state = BM78_STATE_IDLE;

void BM78_sendPacket(uint8_t length, uint8_t *data) {
    BM78_counters.idle = 0; // Reset idle counter
	HAL_UART_Transmit_IT(BM78_uart, data, length); // Make sure that the uart instance is available in main.h. NOT DONE YET
    BM78_state = BM78_STATE_IDLE;
    // Receiving part, wait to receive command completed.
    HAL_UART_Receive_IT(BM78_uart, (uint8_t*)&receiveMessage, 100);
}

inline void BM78_commandPrepareBuffer(BM78_CommandOpCode_t command, uint8_t length) {
    BM78_counters.idle = 0; 				 // Reset idle counter
    BM78_tx.buffer[0] = 0xAA;                // Sync word.
    BM78_tx.buffer[1] = (length + 1) >> 8;   // Length high byte.
    BM78_tx.buffer[2] = (length + 1) & 0xFF; // Length low byte.
    BM78_tx.buffer[3] = command;             // Add command
}

inline uint8_t BM78_commandCalculateChecksum(uint8_t length) {
    uint8_t chksum = 0;
    // Add bytes 1-3 (inclusive) to the checksum.
    for (uint8_t i = 1; i < (length + 4); i++) {
        chksum += BM78_tx.buffer[i];
    }
    return chksum;
}

inline void BM78_commandCommit(uint8_t length) {
    BM78_sendPacket(length + 5, BM78_tx.buffer); // Send
    BM78_counters.idle = 0; // Reset idle counter
}

// Main function to be called.
void BM78_execute(BM78_CommandOpCode_t command, uint8_t length, ...) {
    va_list argp;
    va_start(argp, length);

    BM78_commandPrepareBuffer(command, length);
    for (uint8_t i = 0; i < length; i++) {
        BM78_tx.buffer[i + 4] = va_arg(argp, uint8_t);
    }
    va_end(argp);

    BM78_tx.buffer[length + 4] = 0xFF - BM78_commandCalculateChecksum(length) + 1;
    BM78_commandCommit(length);
}
