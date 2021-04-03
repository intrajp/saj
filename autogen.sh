#!/bin/sh
# Run this to generate all the initial makefiles, etc.

test -n "$srcdir" || srcdir=`dirname "$0"`
test -n "$srcdir" || srcdir=.
test -n "$srcdir" || srcdir=./src

olddir=`pwd`
cd $srcdir

AUTORECONF=`which autoconf`
if test -z $AUTORECONF; then
    echo "*** No autoconf found, please install autoconf package. ***"
        exit 1
else
    echo "autoconf is installed. I proceed."
fi

GS=`which gs`
if test -z $GS; then
        echo "*** No gs found, please install the ghostscript package. ***"
        exit 1
else
    echo "gs is installed. I proceed."
fi

INTLTOOLIZE=`which intltoolize`
if test -z $INTLTOOLIZE; then
        echo "*** No intltoolize found, please install the intltool package. ***"
        exit 1
else
    echo "intltoolize is installed. I proceed."
fi

LIBTOOLIZE=`which libtoolize`
if test -z $LIBTOOLIZE; then
        echo "*** No libtoolize found, please install the libtool package. ***"
        exit 1
else
    echo "libtoolize is installed. I proceed."
fi


AUTOPOINT='intltoolize --automake --copy' autoreconf --force --install --verbose

cd $olddir
test -n "$NOCONFIGURE" || "$srcdir/configure" "$@"
automake
