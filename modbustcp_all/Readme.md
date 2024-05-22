#Modbus Tcp

Libmodbus library aims to develop a reliable, efficient, and scalable Modbus TCP protocol stack for seamless industrial device communication over 
Ethernet networks for the modbus function codes 0x03, 0x06 and 0x10.

The library is usable with all major compilers and provides the necessary tools to implement dedicated modbus tcp client and servers or to integrate modbus tcp based communication into existing application.
Libmodbus library is platform independent.

##Requirements

modbusTxframeLength = modbusTcpFrame (&modbusTcpRxBuf[0], &dataMemory[0], &modbusTcpTxBuf[0],modBusframeLength);

###modbusTcpRxBuf - Incomming Data packets received through modbus TCP communication protocol.

###dataMemory - This Parameter refers to the Memory Buffer that is needed to be configure,monitored,control device I/O or manipulated.

###modbusTcpTxBuf - This parameter represents the output buffer used to store Modbus TCP response frames after processing the query.

###modbusframeLength - This parameter holds the length of response frame.


***Length of the frame varies from one function code to another function code***
***The function code in the request tells the addressed slave device what kind of action to perform***

##Usage

libModbus library contains source files that can be added directly by importing or including the library module into your project directory.

This libray is developed in MPLAB x IDE version 6.20









