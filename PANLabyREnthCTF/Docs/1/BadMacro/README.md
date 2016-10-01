# PAN LabyREnth CTF 2016: Docs Level 1 - BadMacro

## Write-up

We are given a Microsoft Word Document which contains obfuscated VBA macros.

![Obfuscation](BadMacro.PNG)

### Solution

Running the macro you can see that it creates a GET request to an IP address. The URL contains clues on how to solve the challenge.

![Clue](Get.PNG)

#### Flag
> PAN{}
