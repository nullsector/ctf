# PAN LabyREnth CTF 2016: Windows Level 1 - AntiD

## Write-up
We're given a 32-bit windows binary named AntiD.exe. When running, it asks for a key. 
![Initial Output](https://github.com/nullsector/ctf/edit/master/PANLabyREnthCTF/Windows/1/AntiD/AntiD1.PNG)

Loading it in Stud_PE indicates that it is packed with UPX, although the sections in the binary are named .ups0 and .ups1 rather than .upx*. I try to unpack it using upx to no avail. What I need to do is unpack the binary 

### Solution



#### Flag
``
