Terminal Copy
=============
It is a very simple utility to copy the path of your current working directory 
which you can get in another terminal or script. 

Use Case # 1
Suppose there is a modified file in your current working directory which is say `~/a/b/c/d/e/modified.file`, and you want to compare with the original file which you have downloaded at `~/Downloads`. In your current working directory you will invoke

`tcp -c`

then you go to `~/Downloads` to compare it with the original file

`cd ~/Download` <br/>
`diff original.file `tcp`/modified.file` <br/>

In short wherever you have a lengthy path which you want to reuse in another terminal, you can save this path with 

`tcp -c`

and reuse this path as

`tcp`

I have just started this and it has not been tested very extensively. 

Build the Program
=================

`make`

Installing the Program
======================

This will install the output to /usr/bin

`sudo make install`
