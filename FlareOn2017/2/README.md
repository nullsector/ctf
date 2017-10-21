# Flare-On 2007 Challenge #2 - IgniteMe.exe

You solved that last on really quickly! Have
you ever tried to reverse engineer a compiled
x86 binary? Let's see if you are still as quick.

## Write-up
We are given a 32-bit PE file called IgniteMe.exe. When run it
asks for a flag.

![Here](FlareOnChal2Run.JPG)

### Solution

We open the challenge up in IDA Pro to take a look at it.
It looks pretty straight forward. There are clear paths
to both the good-boy and bad-boy messages.

![Here](FlareOnChal2GoodBad.JPG)

It's the call at sub_401050 that we are interested in. This is the call
that does all of the flag checking logic.

