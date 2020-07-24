# little-linux-crypter

This is a demo repo showing the basic functionality of a crypter in linux. Crypter take an executable file as an input and include them into a stub. The new created file extracts the payload when running and executes it.

To be honest, in fact this crypter does not crypt the payload at all. It just takes the binary and appends it to the stub. Also it puts the payload into /tmp/exec.me. If someone knows a runPe alternative working on linux please tell me.


# Compile

## stub
`g++ stub.cpp -o stub`

## crypter
`g++ crypter.cpp -o crypt`

## payload (or use any other executable)
`g++ payload.cpp -o payload`

## create crypted executable
`crypt payload`
