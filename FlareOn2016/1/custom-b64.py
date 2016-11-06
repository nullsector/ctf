#Anthony Sasadeusz
#flareon2016 challenge 1
import string
import base64
import re

custom_alphabet = raw_input("Enter your custom alphabet (custom sequence of all uppercase, lowercase, digits, characters '+' and '/'):\n")
#Verification
#checkB64 = re.match('^(?:[A-Za-z0-9+/]{4})+(?:[A-Za-z0-9+/]{2}==|[A-Za-z0-9+/]{3}=)?$', custom_alphabet)
#if not checkB64:
#    print "Dictionary is invalid"
#    exit()

str_to_decode = raw_input("Enter the string you would like to decode:\n")

#Functions
def convertCustomB64(str):
    #maketrans() takes 2 params: our custom alphabet and the standard one ([A-Z][a-z][0-9][+/])
    newB64Table = string.maketrans(custom_alphabet, string.uppercase + string.lowercase + string.digits + "+/")
    new_str = str.translate(newB64Table)
    # Add '=' char at the end of the string if needed
    miss_padding = 4-len(new_str)%4
    if miss_padding:
         new_str += '='*miss_padding
    result = base64.b64decode(new_str)
    return result
    
print "Here is the result:\n" + convertCustomB64(str_to_decode)