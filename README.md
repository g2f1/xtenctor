------------------------------------------------------------------------------------
xtenctor
------------------------------------------------------------------------------------
xtenctor stands for extension detector is linux command line tool that detect the real extension of file based on the magic header not only the last character of the filename which can be easly changed without corrupting the file. The program extract the ending character from the file name which may represent the real extension and then exttract the header from that file then comparing it to an internal database that contains 46 most used extension with their magic headers and the offset used. I used a public database [here](https://gist.github.com/Qti3e/6341245314bf3513abb080677cd1c93b), and I'll try to improve it to support more extensions. User can choose to use their own database of extensions using a file with a pecific format that I described in the help menu.

To build the project a Makefile is provided in the repo, user just need to clone this repo in his local machine, install `make` and run it to get the final ELF ready for use.

