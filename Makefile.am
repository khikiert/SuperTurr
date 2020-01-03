SUBDIRS = src data

ACLOCAL_AMFLAGS = -I mk/autoconf
AUTOMAKE_OPTIONS = 1.6 dist-bzip2

desktopdir = $(datadir)/applications
desktop_DATA = superturr.desktop

icondir = $(datadir)/pixmaps
icon_DATA = superturr.png

EXTRA_DIST = AUTHORS README COPYING INSTALL NEWS LEVELDESIGN ChangeLog \
	     superturr.desktop superturr.png autogen.sh \
	     @DOLLAR_SIGN@(wildcard mk/autoconf/*.m4)
