#!/usr/bin/env python

# the 0x27 bytes that we are interested in.
encoded_bytes  = '\x69\x02\x0c\x4d\x40\x01\x42\x48'
encoded_bytes += '\x17\x13\x0d\x0a\x26\x73\x47\x45'
encoded_bytes += '\x5f\x09\x56\x6e\x6f\x44\x2b\x17'
encoded_bytes += '\x2f\x12\x45\x5e\x5d\x6c\x2b\x44'
encoded_bytes += '\x78\x17\x2a\x45\x49\x26\x0d'

# our initial key 0x04
key = 0x04

decoded_bytes = list()

for i in encoded_bytes:
    decoded = ord(i) ^ key
    decoded_bytes.append(chr(decoded))
    key = decoded

print 'The flag is: ', ''.join(decoded_bytes[::-1])


