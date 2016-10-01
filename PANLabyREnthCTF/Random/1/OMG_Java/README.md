# PAN LabyREnth CTF 2016: Random Level 1 - OMG_Java

## Write-up

We are given a Java jar file which fails to run.

### Solution

Unarchive the jar file to extract the class file. Then I used the java decompile dirtyJOE to see what was going on. There we can
an interesting string.

![String](DirtyJOE.PNG)

> W5SSA2DPOBSSA6LPOUQGK3TKN54SA5DINFZSASTBOZQSAYLQOAQGC4ZAO5QXE3JNOVYC4ICUNBSSA4TFON2CA53JNRWCAYTFEBWXKY3IEBWW64TFEBZWK6DDNF2GS3THEEQFI2DFEBTGYYLHEBUXGICQIFHHWRBQL5MTA5K7IV3DG3S7IJQXGZJTGJ6Q

This string is Base32 encoded.

It contains our flag.

###Flag
> We hope you enjoy this Java app as warm-up. The rest will be much more sexciting! The flag is PAN{D0_Y0u_Ev3n_Base32}
