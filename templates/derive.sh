#!/bin/sh
# $Id$


if [ $# = "2" ]
then
	PACKAGE=$1;
	NM=$2;
	H_FILE="template.h.t";
	CPP_FILE="template.cpp.t";
else 
	if [ $# = "1" ]
	then
		NM=$1;
		H_FILE="template_without_namespace.h.t";
		CPP_FILE="template_without_namespace.cpp.t";
	else 
		echo "Usage: ./derive.sh namspace className"
		echo "or"
		echo "./derive.sh className"
		exit 0
	fi
fi

#if [ -z "$1" ]; then echo 'Namespace:'; read PACKAGE ; else PACKAGE=$1 ; fi
#if [ -z "$2" ]; then echo 'Class name:'; read NM ; else NM=$2 ; fi

UUID=`uuidgen | tr 'abcdef-' 'ABCDEF_'`
AUTHOR=`git config --get user.name`
EMAIL=`git config --get user.email`
YEAR=`date +%Y`



NAME=$NM
NAMEH=$NM.h
NAMECPP=$NM.cpp


A="cat <<EOF
`cat $H_FILE`
EOF"

eval "$A" >$NAMEH

A="cat <<EOF
`cat $CPP_FILE`
EOF"

eval "$A" >$NAMECPP

