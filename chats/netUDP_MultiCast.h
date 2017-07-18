/**
 * @file netUDP_MultiCast.h
 *
 *  @date Jul 18, 2017
 *  @author Yuval Hamberg
 *
 *  @brief all the network setup for a simple multi-cast UDP communication.
 */

#ifndef NETUDP_MULTICAST_H_
#define NETUDP_MULTICAST_H_

#include "defines.h"

/* ~~~ Defines ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
#define MSG_MAX_SIZE 1024 /** the length in bytes of the msg buffer */


/* ~~~ Globals ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

/* ~~~ Struct ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
typedef struct UDP_MultiCast UDP_MultiCast_t;

/* ~~~ API function ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

/**
 * @brief create and setup for sending udp multi cast messages
 * @param _ip the address in a XXX.XXX.XXX.XXX fomat
 * @param _port port number to communicate on
 * @return a pointer to the new struct
 */
UDP_MultiCast_t* UDP_MultiCast_Sender_Create(const char* _ip, uint _port);

/**
 * @brief destroy and clean up
 * @param _net pointer to struct
 */
void UDP_MultiCast_Sender_Destroy(UDP_MultiCast_t* _net);

/**
 * @brief actually sending the caller message
 * @param _net pointer to struct
 * @param _msg the message to send
 * @param _msgLength the length in bytes of the msg
 * @return the length of bytes send. negative values represent errors.
 */
int UDP_MultiCast_Send(UDP_MultiCast_t* _net, void* _msg, uint _msgLength);



/**
 * @brief create and setup for receiving udp multi cast messages
 * @param _ip the address in a XXX.XXX.XXX.XXX fomat
 * @param _port port number to receive on
 * @return a pointer to the new struct
 */
UDP_MultiCast_t* UDP_MultiCast_Reciver_Create(const char* _ip, uint _port);

/**
 * @brief destroy and clean up
 * @param _net pointer to struct
 */
void UDP_MultiCast_Reciver_Destroy(UDP_MultiCast_t* _net);

/**
 * @brief perform a read of the address given at create. if nothing to read, would go to block until there would.
 * @param _netRecive a pointer to the new struct
 * @param _buffer the read information would be writing to this buffer.
 * @param _bufferSize the length in bytes of the buffer. no overflow would ocuur.
 * @return the size in bytes read. negative values represent errors.
 */
int UDP_MultiCast_Recive(UDP_MultiCast_t* _netRecive, void* _buffer, size_t _bufferSize);






#endif /* NETUDP_MULTICAST_H_ */
