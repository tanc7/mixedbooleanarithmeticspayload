# Proof of concept reverse shell with mixed boolean arithmetics
![](https://github.com/tanc7/mixedbooleanarithmeticspayload/raw/main/Screenshot%20from%202023-03-19%2018-55-09.png)

All I did was execute ordinal-loading using the MAKEINTRESOURCE macro. I took the ordinal, and added 4096 1's to it, and then subtracted 4096 1's to deobfuscate it.

5/69 detections Sun Mar 19 07:03:18 PM PDT 2023

https://www.virustotal.com/gui/file/ec9506794c9b622afdcc74e2c70b49020c0b2cebb4819d08d0ec6ceb5573339e/behavior

# Resources used

1. PE-Bear
2. Any IDE is fine
3. learn.microsoft.com

# Compile

`x86_64-w64-mingw32-g++ -lwsock32 -lws2_32 revshell.cpp`

# Why cant you compile it?

I don't want it flagged as malware on Github. Use this as a learning tool.

# Notes

This is not real "mixed boolean arithmetics". It's just arithmetics actually.

1. I did not use bitwise operators to further obfuscate my ordinals
2. I did not use more convoluted tricks like shifting the bits or rotating them
3. I kept it simple to demonstrate how to easily bypass antivirus

