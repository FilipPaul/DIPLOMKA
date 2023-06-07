
#include "lwip/opt.h"
#include "lwip/api.h"
#include "lwip/sys.h"

#include "tcpserver.h"
#include "string.h"
#include "main.h"
#include "commandParser.h"

#define TCP_SERVER_PORT 7
#define CMD_BUFFER_LENGTH 100

static void tcp_parse_command(char * command, struct netconn *conn){
	char buffer[1024];
	sprintf(buffer,"%s",command); // coppy data to the buffer
	commandTemplate current_command;
	updateCommandStruct(command, &current_command);
	runCommand(&current_command);
	
	printf("%s",current_command.response);
	netconn_write(conn, current_command.response, strlen(current_command.response), NETCONN_COPY);
	
}


static void tcp_byte_avaiable(uint8_t byte, struct netconn *conn)
{
	static uint16_t bfr_pointer;
	static char data[CMD_BUFFER_LENGTH];

	if(bfr_pointer < CMD_BUFFER_LENGTH && byte >= 32 && byte <=127) data[bfr_pointer++] = byte; //
	if ( (byte == '\n' || byte == '\r') && bfr_pointer > 0){
		data[bfr_pointer] = '\0'; //add null terminator -> make string from bytearray
		printf("Received: %s\n", data);
		tcp_parse_command(data, conn);
		bfr_pointer = 0; //reset buffer pointer
	}
}

static void tcp_thread(void *arg)
{
	struct netconn *conn; //conn is the listening socket,
	struct netconn *newconn; //newconn is the socket for the new connection
	err_t err, accept_err;
	static struct netbuf *buf;
	static ip_addr_t *client_IP_addr;
	static unsigned short client_port;
	uint8_t *message_from_client;
	u16_t message_from_client_length;
	LWIP_UNUSED_ARG(arg);

	conn = netconn_new(NETCONN_TCP);	
	if (conn!=NULL)
	{  
		/* Bind connection to well known port number 7. */
		err = netconn_bind(conn, NULL, TCP_SERVER_PORT);
		if (err == ERR_OK)
		{
			netconn_listen(conn);
			printf("TCP server: Running at port: %d\n", TCP_SERVER_PORT);
		
			while (1) 
			{
				/* Grab new connection. */
				accept_err = netconn_accept(conn, &newconn);
			
				/* Process the new connection. */
				if (accept_err == ERR_OK) 
				{
					//printf("IP address: %d",newconn.pcb->ip->remote_ip);
					while (netconn_recv(newconn, &buf) == ERR_OK) 
					{

						client_IP_addr = netbuf_fromaddr(buf);  // get the address of the client
						client_port = netbuf_fromport(buf);  // get the Port of the client
						printf("IP address: .... PORT:%u\n",client_port);
						do 
						{
							netbuf_data(buf, (void**)&message_from_client, &message_from_client_length);
							while(message_from_client_length--) tcp_byte_avaiable(*message_from_client++, newconn);
							//netconn_write(newconn, message_from_client, message_from_client_length, NETCONN_COPY);
						} 

						while (netbuf_next(buf) >= 0);
						netbuf_delete(buf);
					}
				
					/* Close connection and discard connection identifier. */
					netconn_close(newconn);
					netconn_delete(newconn);
				}
			}
		}//if (err == ERR_OK)
		else
		{
			netconn_delete(newconn);
		}
	}//if (conn!=NULL)
}


void tcp_server_init(void)
{
	sys_thread_new("tcp_thread", tcp_thread, NULL, DEFAULT_THREAD_STACKSIZE,osPriorityAboveNormal);
}
