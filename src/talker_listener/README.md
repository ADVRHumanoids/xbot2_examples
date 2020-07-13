# Inter-plugin communication (data stream)
[Back to home](../../README.md)

This example shows a possible way for plugins to communicate with each other, which supports a **mono-directional stream** of data in a **topic-like** fashion. The commented example shows how to exchange data of **arbitrary C++ type**, with special care for **real-time support**, including
 
 - pre-allocation of messages to avoid new memory being requested from the OS at runtime
 - zero-copy transport for big messages to avoid expensive copy operations