#!/bin/bash

ORIGINAL="img.jpg"
ENCRYPTED="in.enc"
DECRYPTED="dec.jpg"

echo "Encrypting!" 
echo "./cipher AES "00112233445566778899aabbccddeeff" ENC $ORIGINAL $ENCRYPTED"
./cipher AES "00112233445566778899aabbccddeeff" ENC $ORIGINAL $ENCRYPTED

echo
echo

echo "Decrypting!" 
echo "./cipher AES "00112233445566778899aabbccddeeff" DEC $ENCRYPTED $DECRYPTED"
./cipher AES "00112233445566778899aabbccddeeff" DEC $ENCRYPTED $DECRYPTED
