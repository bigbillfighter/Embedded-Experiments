#!/bin/sh
for i in *
do
    if [ -f $i ]
    then
        echo "$i is a file"
    elif [ -d $i ]
    then 
        echo "$i is a dictionary"
    fi
done
