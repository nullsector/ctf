# PAN LabyREnth CTF 2016: Windows Level 4 - JugsOfBeer

## Write-up
This is a 64-bit Windows Gui file. I used x64dbg to do my reversing on this challenge. This challenge is based on the jugs of
water riddle that was in the movie Die Hard with a Vengence. This riddle has 3 "jugs of beer", one is 7 gallons, one is 13 gallons,
and the last one is 19 gallons. The 7 and 13 gallon jugs start full, and you need to get 10 gallons in the 19 gallon jug, and 10 gallons in the 13 gallon jug.

Initially running the program, it asks you to enter a serial.
![Here](InitialRun.PNG)

### Solution

First, set a breakpoint at the call to GetDlgItemTextW so that we can step though to see how the program processes the input.
The program first checks to see if the input is an even number of characters, then it checks to see if the serial entered is at least 0x20 in length.

![Here](EvenNCount.PNG)

Then the program check for valid characters. We can see by the disassembly that the only valid characters are 1, 2, and 3.
![Here](ValidChars.PNG)



#### Flag
> PAN{C0ngr47ulaT1ons_buddy_y0Uv3_solved_the_re4l__prObL3M}
