# PAN LabyREnth CTF 2016: Linux Level 1

## Write-up

We are given a perl script named bowie.pl which prompts you for input. It also includes a lot of base64 encoded instructions.

### Solution

Much of the base64 encode data is a gif file. The rest of the base64 are the perl instructions that process further user input. 

The solution is in the decoded gif.
![Bowie](entrevue.gif)

#### Flag
> PAN{L3ts_533_h0W_U_deal_w_th1s_little_511CE}
