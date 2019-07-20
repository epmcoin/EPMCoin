
Debian
====================
This directory contains files used to package extreme_private_masternoded/extreme_private_masternode-qt
for Debian-based Linux systems. If you compile extreme_private_masternoded/extreme_private_masternode-qt yourself, there are some useful files here.

## extreme_private_masternode: URI support ##


extreme_private_masternode-qt.desktop  (Gnome / Open Desktop)
To install:

	sudo desktop-file-install extreme_private_masternode-qt.desktop
	sudo update-desktop-database

If you build yourself, you will either need to modify the paths in
the .desktop file or copy or symlink your extreme_private_masternode-qt binary to `/usr/bin`
and the `../../share/pixmaps/extreme_private_masternode128.png` to `/usr/share/pixmaps`

extreme_private_masternode-qt.protocol (KDE)

