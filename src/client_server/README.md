# Inter-plugin communication (rpc-like)
[Back to home](../../README.md)

This example shows a possible way for plugins to communicate with each other, which supports a **bi-directional** remote procedure call like mechanism where 

 - a **client** sends a request (which can be of any C++ type) and *synchronously* waits for a response
 - a **server** executes a function using the given request as input, and finally sends the computed response to the client

 Since Xbot2.0 has a single process architecture, the word *remote* refers to "different components", possibly executing inside different threads. 
 
 Notice also that, since the client side will have to wait for the server side to respond, it is usually an error to have the client side running inside a high priority (RT) thread. Commonly, a component advertises a service to enable remote interaction with it, such as sending commands, setting gains, etc..