tinyfpp v0.1
============

This is my experimental FPP maze game. The code is currently quite messy - I
was learning while implementing things and would write a lot of things
differently now.

Usage
=====

Provided that you installed the necessary packages, a simple "make" command
should do. Tested on Fedora 20.

You can generate additional mazes using the following program:

http://thenerdshow.com/c/amaze.tar.gz
(website can be found here: http://thenerdshow.com/maze.html)

Use it like this:

amaze 30 30 'X' | sed -e 's/ /x/g' -e 's/X/ /g' > Data/maze.txt

Author, license
===============

This application was written by Jacek Wielemborek <d33tah@gmail.com>. My blog
can be found here: http://deetah.jogger.pl/kategoria/english/

If you're not a viagra vendor, feel free to write me an e-mail, I'd be happy
to hear that you use this program!

This program is Free Software and is protected by GNU General Public License
version 3. Basically, it gives you four freedoms:


Freedom 0: The freedom to run the program for any purpose.

Freedom 1: The freedom to study how the program works, and change it to make
    it do what you wish.

Freedom 2: The freedom to redistribute copies so you can help your neighbor.

Freedom 3: The freedom to improve the program, and release your improvements
    (and modified versions in general) to the public, so that the whole
     community benefits.

In order to protect that freedom, you must share any changes you did to the
program with me, under the same license. For details, read the COPYING.txt
file attached to the program.
