# Proof of concept reverse shell with mixed boolean arithmetics
![](https://github.com/tanc7/mixedbooleanarithmeticspayload/raw/main/Screenshot%20from%202023-03-19%2018-55-09.png)

All I did was execute ordinal-loading using the MAKEINTRESOURCE macro. I took the ordinal, and added 4096 1's to it, and then subtracted 4096 1's to deobfuscate it.

5/69 detections Sun Mar 19 07:03:18 PM PDT 2023

https://www.virustotal.com/gui/file/ec9506794c9b622afdcc74e2c70b49020c0b2cebb4819d08d0ec6ceb5573339e/behavior
**New Payload**
https://www.virustotal.com/gui/file/e37a602ba7320e5b62ae97db75285eef4fb51dbff7dfa4a863718a1c163a449d?nocache=1
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

1. I did not use bitwise operators to further obfuscate my ordinals (I just did, check new VirusTotal link)
2. I did not use more convoluted tricks like shifting the bits or rotating them
3. I kept it simple to demonstrate how to easily bypass antivirus

# Applying simple mixed boolean arithmetics to a example implant (ThreadContext Injection)

# Combination of IAT-hiding and ordinal load via mixed boolean arithmetics
Use multiples of 0x1000 to ordinal load these and XOR it back

1. XOR out the value to a multiple of 0x1000
2. Compute the value of that multiple in a for-loop
3. The final ordinal is resolved as the ordinals listed below
4. Remember these are functions from kernel32.dll

# (WriteProcessMemory) Remember that 99 is decimal, not hex, so #define XORKEY 99
0x637 + 0x2000 = 0x2637^99 = 0x2654
# (VirtualAllocEx)
0x5e3 + 0x2000 = 0x25e3^99 = 0x2580
# SetThreadContext
0x56f p/x (0x2000+0x56f)^99 = 0x250c
# SuspendThread
0x5a1 p/x (0x2000+0x5a1)^99 = 0x25c2
# GetThreadContext
0x30d p/x (0x2000+0x30d)^99 = 0x236e 
# SetThreadContext
0x56f p/x (0x2000+0x56f)^99 = 0x250c
# CreateToolhelp32Snapshot
0x108 p/x (0x2000+0x108)^99 = 0x216b

# Example deobfuscator before MAKEINTRESOURCE macro is used.
```
#define XORKEY 99

int deobfuscate(int x) {
    x ^= XORKEY;
    for (int i = 0; i < 0x2000; i++) {
        x -= 0x1;
    }
    return x;
}

```
