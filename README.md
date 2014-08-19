Exploit Development
=======

- Alphanumeric shellcode encoder utility uses opcodes' 2's complement to generate a series of SUB instructions ergo alphanum bytecode
- PyCommand for finding pointers when a vulnerability leads to indirect EIP control (function pointer overwrite), it'll find a desired instruction and calculate it's "pointer to pointer"

Example, typical function pointer overwrite "Easy File Management WebServer Stack b0f":

1. We control EDI
2. Instruction 	_CALL DWORD PTR [EDI+28]_  is called
3. _ESI_ points to our buffer
4. _EDI+28_ contains a DWORD used as pointer to some memory address
5. EIP executes the opcodes contained in that memory address
Solution:
* Place an address in EDI such that when added +28 will point to a place in memory where there's a pointer to JMP ESI



Hotpatch API Hooking
=======

- Inline/hotpatch API hook for HttpSendRequestW
- Tested on Internet Explorer 8
- Desktop change & full screen


PHP Shell
=======

- Command history for commands executed from PHP objects :)
- Base64 encoding - command & output

Authentication, tunneling, info

