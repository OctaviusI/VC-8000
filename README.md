# VC8000 Fictional Computer

The VC8000 is a fictional decimal computer C++ designed to be compiled in Visual Studio. 
## Features

 - An Assembler and Emulator for running programs through the use of a .txt file for input
 - An assembly language, written with four instructions, alongside seventeen machine language opcodes which are case insensitive.
 - Extensive error checking, alongside a list of errors at the end of execution.
 - Comments, denoted by the symbol ;
 - Input/Output, with the READ and WRITE opcode.
 - 1,000,000 words of memory, with each word of memory consisting of 9 decimal digits.
 - 10 Registers for "on-chip memory".

## Running/Compilation

Upon opening Visual Studio, simply choose "Clone a repository" and enter this project's url, and after the project is fully cloned, simply click "Local Windows Debugger" to run, and you should be all set! You can also change the build to release for faster performance. 

For more information on cloning repositories in Visual Studio, click [here](https://docs.microsoft.com/en-us/visualstudio/get-started/tutorial-open-project-from-repo?view=vs-2022)

## Troubleshooting/Changing The Input File
Occasionally, the project will not save settings for some users. If this happens, go to:
**Project->Properties->Debugging->Command Arguments**
and type in the input file you want to use, the default text document, type "testinput.txt", or the name of your text file followed by the .txt extension. 

## Acknowledgements 

 - Much of the documentation is in part thanks to Professor V. Miller, for a class which this was the term project, and was posted with permission, although this project will aim to expand upon it.  
