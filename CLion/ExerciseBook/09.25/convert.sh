#!/bin/bash

# converts xml and java files

DIR=$1
cd $DIR

#rmdir out
mkdir out
for i in $(find $DIR -name '*.c' -or -name '*.C' -or -name '*.h' -or -name '*.H'); do
 #iconv -f "WINDOWS-1254" -t "UTF8" $i -o $i;
 iconv -f "GB2312" -t "UTF8" $i  > $DIR/out/$i;
done

