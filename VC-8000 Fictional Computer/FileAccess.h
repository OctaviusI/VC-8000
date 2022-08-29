//
//		File access to source file.
//
#ifndef _FILEACCESS_H  // This is the way that multiple inclusions are defended against often used in UNIX
#define _FILEACCESS_H  // We use pragmas in Visual Studio and g++.  See other include files

#include <fstream>
#include <stdlib.h>
#include <string>

class FileAccess {

public:




    // Opens the file.
    FileAccess( int argc, char *argv[] );

    // Closes the file.
    ~FileAccess( );

        /*
       NAME

           GetNextLine - Gets the next line in the file. 

       SYNOPSIS

              bool GetNextLine( string &a_line );

              a_line -> the next line to be parsed.
  



       DESCRIPTION

           Parses the next line in the file, returns false if there are none 


       RETURNS
           bool: true if there are still more lines to parse. False if there are not. 
       */

    
    
    
    



    bool GetNextLine( string &a_line );

    

    /*
      NAME

          rewind - rewinds the file back to the beginning.

      SYNOPSIS

            void rewind( );




      DESCRIPTION

          Returns the file pointer back to the beginning of the file.


      RETURNS
          void
      */


    void rewind( );

private:

    ifstream m_sfile;		// Source file object.
};
#endif

