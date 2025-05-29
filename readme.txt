name: Jonathan Katsav
ID: 207982950

Special conditions:
1) I made everything in folders so the files will be as listed bellow:
	a) sbin will contain get_blocks.sh (the bash code that reads the blocks from https://www.blockcypher.com/dev/bitcoin/#blockchain-api
	b) usr will include 2 folders:
		1. include- contains all the h files
		2. src contain all the programs .cpp. one for each EX, 1 for Data management and 1 for printing.
	c) var will contain blocks.txt (the text fiels that the data will be saved on)
2) I used the makefile shown in class and modified it accordingly to my needs in the project. 
3) The makefile will make all the files needed to check the EX accordingly and will put all of them in a new folder named build
4) The makefile got a clean part where it delete folder build with all it contains
