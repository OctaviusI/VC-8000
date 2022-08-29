//
//		Emulator class - supports the emulation of VC8000 programs
//
#ifndef _EMULATOR_H      // UNIX way of preventing multiple inclusions.
#define _EMULATOR_H

class emulator {

public:

    const static int MEMSZ = 1'000'000;	// The size of the memory of the VC8000.
    const static int REGSZ = 10; //The size of the registers of the VC8000.
    emulator() {

         m_memory.resize(MEMSZ, 0); //Prepares the size of both the registers and memory. 
         m_register.resize(REGSZ, 0);
    }
    


    /*

    NAME

             insertMemory - Inserts the contents into the given location.

    SYNOPSIS

               bool insertMemory( int a_location, long long a_contents );
                    a_location --> the location for which to be inserted. 
                    a_contents --> the contents to insert into the location in memory.

    DESCRIPTION

            This function will attempt to insert the contents into the location of the memory of the VC8000, and cause errors if it is out of bounds.

    RETURNS

            Returns true if there were no errors when inserting the contents. Returns false if there were errors when inserting the contents, such as not enough memory.


    */

    bool insertMemory( int a_location, long long a_contents );
    
    
    /**/
/*

NAME

         ml_Read - Reads input from the user in the emulator.

SYNOPSIS

            bool ml_Read(int a_location);
            a_location        --> the current location in memory.

DESCRIPTION

        This function will read an input from the user, convert it to a number, and
        put it in memory appropriately. 

RETURNS

        Returns true if the reading was a success, false if there was an issue in the reading.


*/
/**/

    bool ml_Read(int a_location);




    /**/
/*

NAME

         runProgram - Runs commands based on memory in the Emulator. 

SYNOPSIS

            bool runProgram();

DESCRIPTION

        This function will iteratively go through the memory of the emulator, parse all related information such as opcode, address, memory, etc..
        and then run commands based upon the opcodes, and present errors if there are any, such as illegal opcodes or if the program goes past it's own memory.

RETURNS

        Returns true if there were no errors when running the program. Returns false if there were errors when emulating the program.


*/
/**/


    // Runs the program recorded in memory.
    bool runProgram( );

private:

    vector<long long> m_memory;  	// Memory for the VC8000
    vector<long long> m_register; //Registers for the VC8000
    const static int m_ADDRESS_ORIGIN = 100;
};

#endif

