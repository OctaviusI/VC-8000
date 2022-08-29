//
//		Assembler class.  This is a container for all the components
//		that make up the assembler.
//
#pragma once 

#include "SymTab.h"
#include "Instruction.h"
#include "FileAccess.h"
#include "Emulator.h"


class Assembler {

public:
    Assembler( int argc, char *argv[] );
    


    /*

    NAME

             PassI - Do the initial first Pass to look over a file.

    SYNOPSIS

               void PassI();

    DESCRIPTION

            This function goes through the input file of the user, and attempts to parse the fields one by one to create the instructions that are to be 
            translated in Pass II, and additionally, if there are 
            labels, put them in the symbol table for further use. Comments and Errors are ignored until Pass II. 

    RETURNS

            void


    */
    void PassI( );

   


    /*

    NAME

             PassII - Do the second Pass, translating the input per line and creating errors..

    SYNOPSIS

               void PassII();

    DESCRIPTION

            This function goes through the input file of the user once again, however now records errors and translates the content created from Pass I, and puts it into the 
            VC8000 Emulator's Memory if there are no errors. The errors checked in Pass II are primarily using the Symbol Table filled in Pass I to see if there are undefined 
            or multiply defined symbols. 

    RETURNS

            void


    */

    void PassII();

    // Display the symbols in the symbol table.
    void DisplaySymbolTable() { m_symtab.DisplaySymbolTable(); }
    
   
    /*

NAME

         TranslateMachineLanguage - Do the second Pass, translating the input per line and creating errors..

SYNOPSIS

           void TranslateMachineLanguage(Instruction& a_instruction, int a_location);

                a_instruction -> the current instruction being translated. 
                a_location -> the current location of the line.

DESCRIPTION

        This is responsible for translating and outputing the translated version of the Machine Language. It does this by breaking down the machine language into 4 categories based on 
        what their arguments are, such as two registers, one register and one label, etc.. and filling them as appropriately as possible. This function also checked for multiply defined symbols
        or undefined symbols.

RETURNS

        void


    */

    void TranslateMachineLanguage(Instruction& a_instruction, int a_location);

    /*

NAME

         TranslateAssemblyInstruction - Translate the Assembly Instructions...

SYNOPSIS

           void TranslateAssemblyInstruction(Instruction& a_instruction, int a_location);

                a_instruction -> the current instruction being translated.
                a_location -> the current location of the line.

DESCRIPTION

        This is responsible for translating and outputing the translated version of the Assembly Language. It does this by breaking down the machine language into the 3 Assembly Instructions
        (excluding END) and filling them based on how they are formatted accordingly. Only DC is filled, whereas the others are merely outputted. 

RETURNS

        void


    */


    void TranslateAssemblyInstruction(Instruction& a_instruction, int a_location);
    
    /*

NAME

         TranslateComment - Translate (format) the inputted line as a comment...

SYNOPSIS

           void TranslateAssemblyInstruction(Instruction& a_instruction);

                a_instruction -> the current instruction being translated.

DESCRIPTION

       Simply outputs the formatted line of the original line, and can be used by other functions to do the same. 

RETURNS

        void


    */
    
    
    
    
    void TranslateComment(Instruction& a_instruction);
    
    
    /*

NAME

         TranslateError - "Translate" the Error as best as possible...

SYNOPSIS

           void TranslateComment(Instruction& a_instruction);

                a_instruction -> the current instruction being translated.
                a_location -> the current location of the line.

DESCRIPTION

        This function gathers the Errors of the formatter in the Instruction class, and also reroutes the error to where it would be filled
        where it not an error type using its sub error variable accordingly, where they will deal with how to format the error.

RETURNS

        void


    */
    
    void TranslateError(Instruction& a_instruction, int a_location);

    
    
    /*

    NAME

         FillContents - Fill the string as best as possible with the given variables.

    SYNOPSIS

           FillContents(int a_case=0, string a_numOP = "", string a_OP1 = "", string a_OP2 = "", string a_Address = "");

                a_case -> the selected fill case to determine type of filling.
                a_numOP -> the numeric version of the operand, in string form.
                a_OP1 -> The first operand of the instruction. 
                a_OP2 -> The second operand of the instruction. 
                a_Address -> The address of the instruction, if applicable.

    DESCRIPTION

        This functions fills the contents based on 3 types: Assembly where the number is just filled with a single number, 2 registers, and other(1 register, 1 operand).
        It also fills any empty spaces with 0 based on what type of filling. 

    RETURNS
        string - empty string if there's the filling is blank, or returns the filled contents in string form, ready to be translated to memory. 


    */
    
    
    
    
    string FillContents(int a_case=0, string a_numOP = "", string a_Reg1 = "", string a_Reg2 = "", string a_Address = "");

    // Run emulator on the translation.
    
    /*

    NAME

         RunProgramInEmulator - Runs the stored Program in memory in the Emulator

    SYNOPSIS

        RunProgramInEmulator;

    DESCRIPTION

        This functions simply calls the emulator to run if there are no errors, if not, don't run. If the emulator is run, display if it has run with errors.

    RETURNS
       void


    */
    
    
    void RunProgramInEmulator();

    
    
    
    
    /*

   NAME

        isValidAddress - Checks if the Address is Valid, that is, not defined more than once or undefined

   SYNOPSIS

       bool IsValidAddress(string& a_labelOperand, int& a_address) 
        a_labelOperand -> the label associated with the address. 
        a_address -> the address of the operand.
        

   DESCRIPTION

       This functions simply calls the emulator to run if there are no errors, if not, don't run. If the emulator is run, display if it has run with errors.

   RETURNS
      bool - returns true if there are no errors, false if the address is multiply defined or undefined.


   */
    
    
    
    
    
    bool IsValidAddress(string& a_labelOperand, int& a_address);

private:

    FileAccess m_facc;	    // File Access object
    SymbolTable m_symtab;   // Symbol table object
    Instruction m_inst;	    // Instruction object
    emulator m_emul;        // Emulator object
};

