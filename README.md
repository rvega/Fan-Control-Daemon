Fan-Control-Daemon
====================

Introduction
---------------------

This is an enhanced version of [CeRiAl's Fan-Control-Daemon](https://github.com/CeRiAl/Fan-Control-Daemon), which itself is an enhanced version of [rvega's Fan-Control-Daemon](https://github.com/rvega/Fan-Control-Daemon),
which itself is an enhanced version of [Allan McRae mbpfan](http://allanmcrae.com/2010/05/simple-macbook-pro-fan-daemon/)

Fan-Control-Daemon is a daemon that uses input from coretemp module and sets the fan speed using the applesmc module. 
This enhanced version assumes any number of processors and fans (max. 10).

*  It only uses the temperatures from the processors as input.
*  It requires coretemp and applesmc kernel modules to be loaded.
*  It requires root use
*  It daemonizes or stays in foreground
*  Verbose mode for both syslog and stdout


Compile Instructions
---------------------

Compile with
   make

Manually compile with
   gcc -o bin/mbpfan src/mbpfan.c -lm

Run The Tests (Recommended)
---------------------------

It is recommended to run the tests before installing the program
	sudo ./bin/mbpfan -t

Install Instructions
--------------------

Install with
   sudo make install

It actually copies mbpfan to /usr/sbin.

An init file suitable for /lib/lsb/init-functions (Debian & Ubuntu fur sure)
is located in the main folder of the source files. It is called mbpfan.init.debian
Rename it to mbpfan, give it execution permissions (chmod +x mbpfan)
and move it to /etc/init.d
Then, add it to the default runlevels with sudo update-rc.d mbpfan defaults (Ubuntu example)

An init file suitable for Fedora (and probably RedHat) can be found
in the file mbpfan.init.fedora

An init file is available for gentoo users: mbpfan.init.gentoo
To install, run # cp mbpfan.init.gentoo /etc/init.d/mbpfan
To automatically run mbpfan at boot, run # rc-update add mbpfan default

Run Instructions
---------------------

If not installed, run with
sudo bin/mbpfan

If installed, manually run with
sudo mbpfan

If installed and using the init file, run with (Ubuntu example)
sudo service mbpfan start

Usage
-------

Usage: ./mbpfan OPTION(S)
-h Show the help screen
-f Run in foreground
-t Run the tests
-v Be (a lot) verbose


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
