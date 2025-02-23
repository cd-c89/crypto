"""
- Accept 3 command line arguments:
  - A flag `-d` or `-e` for decrypt or encrypt
  - The file name of an input file.
  - The file name of an output file.
- It should:
  - Read the content of the input file.
  - Encrypt or decrypt, as specified, the file contents.
    - It should read `n` and `d` from "unsafe.bad" to decrypt.
    - It should read `n` and `e` from "unsafe.pub" to encrypt.
  - Write the encrypted or decrypted content to the output file.
"""

if __name__ != "__main__":
    exit()

import sys

def modexp(m, e, n):
    if e == 0:
        return 1
    if e == 1:
        return m % n
    if e % 2:
        return (m * modexp(m*m % n, e//2, n)) % n
    return  modexp(m*m % n, e//2, n) % n

if 'e' in sys.argv[1]:
    lines = open("unsafe.pub").readlines()
    n, e = int(lines[1], 16), int(lines[2], 16) 
elif 'd' in sys.argv[1]:
    lines = open("unsafe.bad").readlines()
    n, e = int(lines[1], 16), int(lines[3], 16) # have to call it e, not d
else:
    exit()
s = open(sys.argv[2], "rb").read()
m = int.from_bytes(s, byteorder=sys.byteorder, signed=False)
c = modexp(m,e,n)
s = open(sys.argv[3], "wb").write(c.to_bytes(4, byteorder=sys.byteorder))