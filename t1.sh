#!/bin/bash

ORIGINAL="in.txt"
ENCRYPTED="in.enc"
DECRYPTED="out.txt"
KEY="0123456789abcdef"

echo "Encrypting!" 
echo "./cipher DES $KEY ENC $ORIGINAL $ENCRYPTED"
./cipher DES $KEY ENC $ORIGINAL $ENCRYPTED

echo
echo

echo "Decrypting!" 
echo "./cipher DES $KEY DEC $ENCRYPTED $DECRYPTED"
./cipher DES $KEY DEC $ENCRYPTED $DECRYPTED
