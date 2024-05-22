#Modbus Rtu

The goal of the LibmodbusRtu library is to create a scalable, dependable, and efficient Modbus RTU protocol stack that supports ModbusRTU function codes 0x03, 0x06, and 0x10 and allows industrial devices to communicate seamlessly over Ethernet networks. Compatible with all popular compilers, it offers the tools needed to create specialized Modbus RTU clients and servers or incorporate Modbus RTU-based communication into already-existing applications. Because it is platform-neutral, the library is more adaptable and simple to integrate with different systems.

##Requirements

modbusRtuFrame (&modbusRtuRxBuf[0], &dataMemory[0], &modbusRtuTxBuf[0],&modBusframeLength);

###modbusRtuRxBuf - Incoming data packets received through the Modbus RTU communication portt.

###dataMemory - Memory buffer needed for configuring, monitoring, controlling device I/O, or manipulation.

###modbusRtuTxBuf -  Output buffer used to store Modbus RTU response frames after processing the query.

###modbusframeLength - This parameter holds the length of the response frame.


***Length of the frame varies from one function code to another function code***
***The function code in the request tells the addressed slave device what kind of action to perform***

##Usage

The libModbusRtu library consists of source files that can be directly added to your project directory by importing or including the library module.

The library is developed in the MPLAB X IDE version 6.20