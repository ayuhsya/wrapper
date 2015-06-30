# wrapper
C++ wrapper code for fingerprint verification in Python

Install notes

## Install Hamster DX driver (included) as follows:

$ tar -zxvf VenusDrv-v1.0.4-3-Ubuntu14.04-64bit-2015.03.30
$ cd VenusDrv-v1.0.4-3-Ubuntu14.04-64bit
$ sudo ./CreateModule
$ sudo ./install.sh
$ sudo ./NBioBSP_Signer

# enter the following key when asked for :
010701-A48AF5C406F6368A-27F631236B47E480

## For compiling use the following command on terminal :
$ g++ -shared -I/usr/include/python2.7/ -lpython2.7 -o veripy.so veripy.cpp -fPIC -lNBioBSP
