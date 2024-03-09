# VC8000 Fictional Computer

The VC8000 is a fictional decimal computer C++ built to be run on both Windows 32-bit and 64-bit systems.
## Features

 - An Assembler and Emulator for running programs through the use of a .txt file for input.
 - An assembly language, written with four instructions, alongside seventeen machine language opcodes which are case insensitive.
 - Extensive error checking, alongside a list of errors at the end of execution.
 - Comments, denoted by the symbol ;.
 - Input/Output, with the READ and WRITE opcode.
 - 1,000,000 words of memory, with each word of memory consisting of 9 decimal digits.
 - 10 Registers.

## Installation & Usage 

This Project requires that Visual C++ 2019 Redistributable be installed. If you do not already have it installed, click [here](https://learn.microsoft.com/en-US/cpp/windows/latest-supported-vc-redist?view=msvc-170#visual-studio-2015-2017-2019-and-2022).

Afterward, simply download the release that matches your system the best. Extract the release, open your preferred Windows CLI (e.g. Command Prompt, Powershell, etc..), and switch to the directory (via cd) in which you extracted the release. 

To run a program on the VC8000, simply type the name of the downloaded exe and the directory of your selected source file. 

For example, running the 64-bit exe with the sample program(that comes with either release), the corresponding command would be: `vc8000_64.exe testinput.txt` 

If done correctly, one should see something similar to the following: 
![An image showing the results of running the VC8000's test input command. Here, each number is output. If the number is negative, that number is outputted and then stops the program. Additionally, the symbol table is also printed prior to input.](https://github.com/pw45000/VC-8000/blob/master/VC-8000%20Fictional%20Computer/test_input.png?raw=true)
Note that here every number following question marks is an inputted number. So, for instance, the line `? 7' is the user inputting 7.  

### Developer Information
The VC8000 is capable of running programs via executing [Machine Instructions](https://github.com/pw45000/VC-8000/wiki/VC8000-Computer-and-OPCodes) and utilizing the VC8000's [Assembly Language](https://github.com/pw45000/VC-8000/wiki/VC8000-Assembly-Language). 

A generally good place to learn how to develop programs with the VC8000 is the [sample output page](https://github.com/pw45000/VC-8000/wiki/VC8000-Sample-Output), however, the VC8000 was developed with the **assumption that the end-user has experience in other assembly languages, such as x86, MASM, etc..** Hence, it is **highly** recommended that one have experience in assembly language before attempting to develop with the VC8000. 

However, potentially a more robust tutorial will be made for beginners in the future.  

## Compilation/Building

Upon opening Visual Studio, simply choose "Clone a repository" and enter this project's url, and after the project is fully cloned, simply click "Local Windows Debugger" to run, and you should be all set! You can also change the build to release for faster performance. 

For more information on cloning repositories in Visual Studio, click [here.](https://docs.microsoft.com/en-us/visualstudio/get-started/tutorial-open-project-from-repo?view=vs-2022)


### Selecting Source File For Use
To set the input .txt file for use, select the following: 
    **Project -> Properties -> Debugging -> Command Arguments**
and type in the input file you want to use, the default text document, type "testinput.txt", or the name of your text file followed by the .txt extension. 

## Acknowledgements 

 - Much of the external documentation(i.e. the wiki) is in part thanks to Professor V. Miller, for a class in which this was the term project, and was posted with permission, although this repository will aim to expand upon it.  
