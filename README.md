Fan-Control-Daemon
====================

Introduction
---------------------

This is an enhanced version of [rvega's Fan-Control-Daemon](https://github.com/rvega/Fan-Control-Daemon),
which itself is an enhanced version of [Allan McRae mbpfan](http://allanmcrae.com/2010/05/simple-macbook-pro-fan-daemon/)

Fan-Control-Daemon is a daemon that uses input from coretemp module and sets the fan speed using the applesmc module. 
This enhanced version assumes any number of processors and fans (max. 10).

*  It only uses the temperatures from the processors as input.
*  It requires coretemp and applesmc kernel modules to be loaded.
*  It requires root use


Compile Instructions
---------------------

Compile with
   make

Manually compile with
   gcc -o bin/mbpfan src/mbpfan.c -lm


Install Instructions
--------------------

Install with
   sudo make install

It actually copies mbpfan to /usr/sbin.

An init file suitable for /lib/lsb/init-functions (Debian & Ubuntu fur sure)
Is located in the main folder of the source files. It is called mbpfan.init.
Rename it to mbpfan, give it execution permissions (chmod +x mbpfan)
and move it to /etc/init.d
Then, add it to the default runlevels with sudo update-rc.d mbpfan defaults (Ubuntu example)


Run Instructions
---------------------

If not installed, run with
sudo bin/mbpfan

If installed, manually run with
sudo mbpfan

If installed and using the init file, run with (Ubuntu example)
sudo service mbpfan start


License
---------------------
GNU General Public License version 3


Based On
---------------------

* http://allanmcrae.com/2010/05/simple-macbook-pro-fan-daemon/
* http://allanmcrae.com/2011/08/mbp-fan-daemon-update/
* https://launchpad.net/macfanctld
* http://paste2.org/p/862259
* http://www.lobotomo.com/products/FanControl/
