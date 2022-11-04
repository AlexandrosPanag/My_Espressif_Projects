BearSSL is an implementation of the SSL/TLS protocol (RFC 5246) written in C. It aims at offering the following features:

Be correct and secure. In particular, insecure protocol versions and choices of algorithms are not supported, by design; cryptographic algorithm implementations are constant-time by default.

Be small, both in RAM and code footprint. For instance, a minimal server implementation may fit in about 20 kilobytes of compiled code and 25 kilobytes of RAM.

Be highly portable. BearSSL targets not only “big” operating systems like Linux and Windows, but also small embedded systems and even special contexts like bootstrap code.

Be feature-rich and extensible. SSL/TLS has many defined cipher suites and extensions; BearSSL should implement most of them, and allow extra algorithm implementations to be added afterwards, possibly from third parties.

SOURCE: https://www.bearssl.org



HelloCrypto
---------------------------------------------------------------

Original code > Files > Examples > HelloCrypto


This is an edit to the code to make more sense for less experienced users

Original code description : 
This example demonstrates the usage of the ESP8266 Crypto implementation, which aims to contain easy-to-use cryptographic functions.
Crypto is currently primarily a frontend for the cryptographic library BearSSL which is used by `BearSSL::WiFiClientSecure` and `BearSSL::WiFiServerSecure` in the ESP8266 Arduino Core.
   Extensive documentation can be found in the Crypto source code files and on the [BearSSL homepage](https://www.bearssl.org).
