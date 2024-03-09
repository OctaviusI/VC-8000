//
// Note: all members are static so we can access them anywhere. 
// Necessary in the sense that an error can occur in multiple places- the assembler, emulator, etc..
//
#ifndef _ERRORS_H
#define _ERRORS_H

#include <string>
#include <vector>

class Errors {

public:
    
    
    /*
   NAME

     InitErrorReporting- Initalize the Error Reporting.

   SYNOPSIS

                 static void InitErrorReporting( );



   DESCRIPTION

       Clears the Error vector and makes it fresh for new errors to be reported.


   RETURNS
       void
   */


    static void InitErrorReporting( );

        /*
     NAME

       RecordError- Record an error.

     SYNOPSIS

                  static void RecordError( string a_emsg );
                    a_emsg  -> the error to be recorded.



     DESCRIPTION

         Records the error and puts it into the vector. 


     RETURNS
         void
     */


    static void RecordError( string a_emsg );

    // Displays the collected error message.

    /*
     NAME

       DisplayErrors- Displays all errors.

     SYNOPSIS

            static void DisplayErrors( );



     DESCRIPTION

         Displays all the errors in the m_ErrorMsgs vector. 


     RETURNS
         void
     */


    static void DisplayErrors( );



        

     /*
     NAME

       DisplayErrors- Displays all errors.

     SYNOPSIS

            static bool HasErrors( );



     DESCRIPTION

         Displays the collected error message.


     RETURNS
         bool: returns true if there are errors in the m_ErrorMsgs vector, false if otherwise.
     */


    static bool HasErrors(); 

private:

    static vector<string> m_ErrorMsgs; 
    static bool m_ProgramHasErrors;
};
#endif