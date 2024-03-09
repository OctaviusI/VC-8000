#pragma once

// The elements of an instruction.
class Instruction {

public:

    Instruction( ) {};

    // Codes to indicate the type of instruction we are processing.  
    // Each code is an enum for disambiguity in catching, and simplifies switch cases. 
    enum class InstructionType {
        ST_MachineLanguage, 	// A machine language instruction.
        ST_AssemblerInstr,      // Assembler Language instruction.
        ST_Comment,             // Comment or blank line
        ST_End,                 // end instruction.
        ST_Error                // Statement has an error.
    };
    // Parse the Instruction.
    InstructionType ParseInstruction(string a_line);

    // Compute the location of the next instruction based on
    // if the location has a location changing opcode.
    inline int LocationNextInstruction( int a_loc ) {
        if (m_OpCode == "ORG") //If the location is org, then change location. 
            return m_Operand1NumericValue;
        else if (m_OpCode == "DS")
            return a_loc + m_Operand1NumericValue; //If the location is a DS, then add storage plus location.
        return a_loc + 1;
    }

    // To access the label
    inline string &GetLabel( ) {
        return m_Label;
    };

    // Gathers the private body members of the class.
    inline const string GetOperand1() const { return m_Operand1; }
    inline const string GetOperand2() { return m_Operand2; }
    inline const string GetInstruction() { return m_instruction; }
    inline const string GetOpCode() { return m_OpCode; }
    inline const int GetNumOpCode() { return m_NumOpCode; }
    inline const bool GetIsNumOP1() { return m_IsNumericOperand1; }
    inline const bool GetIsNumOP2() { return m_IsNumericOperand2; }
    inline const vector<string> GetFormatError() { return m_formatError; }
    inline const InstructionType GetErrorType() { return m_errorType; }


   

    // To determine if a label is blank.
    inline bool isLabel( ) {
        return ! m_Label.empty();
    };


private:


    // The elemements of a instruction
    string m_Label;        // The label.
    string m_OpCode;       // The symbolic op code.
    string m_Operand1;     // The first operand. 
    string m_Operand2;     // The second operand.


    string m_instruction;    // The original instruction.

    // Derived values.
    int m_NumOpCode = 0;     // The numerical value of the op code for machine language equivalents.
    InstructionType m_type = InstructionType::ST_Error; // The type of instruction.

    bool m_IsNumericOperand1 = false;// == true if the operand 1 is numeric.
    int m_Operand1NumericValue = 0;   // The value of the operand 1 if it is numeric.
    
    bool m_IsNumericOperand2 = false;// == true if the operand 2 is numeric.
    int m_Operand2NumericValue = 0;   // The value of the operand 2 if it is numeric.

    vector <string> m_formatError; //The error message associated with the format. Empty by default.
    InstructionType m_errorType = InstructionType::ST_Error; //a subtype for the instruction. So we can attemtpt to translate the errormessage.
                                      
    // Delete any comments from the statement.
    void DeleteComment(string &a_line)
    {
        size_t isemi1 = a_line.find(';');
        if (isemi1 != string::npos)
        {
            a_line.erase(isemi1);
        }
    }

    // Delete any whitespaces to the left to fix identation.
    string DeleteLeftWhitespaces(string& a_line) {
        const string WHITESPACE = " \n\r\t\f\v";
        size_t start = a_line.find_first_not_of(WHITESPACE);
        return (start == std::string::npos) ? "" : a_line.substr(start);
    }

    // Record the fields of the instructions.
    
        // Add a new symbol to the symbol table.
       /*
    NAME

        RecordFields - Records the line into the fields of the instruction.

    SYNOPSIS

         bool RecordFields( const string &a_line );
            a_line = the line currently being parsed.

    DESCRIPTION

        This function Records the line and puts it into the fields of the instruction, as well as handling any formatting errors, such as extra and missing operands, 
        syntax errors, etc..


    RETURNS 
        bool: True if recording is successful (and has the instruction type with from the InstructionType enum). False if there are any errors. 
    */
    
    bool RecordFields( const string &a_line );

       /*
    NAME

        ParseLineIntoFields - Parses the line into the fields of the instruction.

    SYNOPSIS

         bool ParseLineIntoFields(string a_line, string& a_label, string& a_OpCode,
            string& a_Operand1, string& a_Operand2);

            a_line-> the line being parsed.
            a_label -> the label of the instruction edited by the function.
            a_OpCode -> the OpCode of the instruction edited by the function. 
            a_Operand1 -> the 1st Operand of the instruction edited by the function. 
            a_Operand2 -> the 2nd Operand of the instruction edited by the function. 

    DESCRIPTION

        This function Records the line and puts it into the fields of the instruction, as well as handling any formatting errors, such as extra and missing operands,
        syntax errors, etc..


    RETURNS
        bool: true if runs without any errors, in particular 3 operands. False if there's any errors(3 operands).
    */
    bool ParseLineIntoFields(string a_line, string& a_label, string& a_OpCode,
        string& a_Operand1, string& a_Operand2);

    

      /*
     NAME

         isStrNumber - Checks if the string can be converted to a number.

     SYNOPSIS

             bool isStrNumber(const string& a_str);
                a_str -> the string to be checked.
                


     DESCRIPTION

         This function checks if the passed string can be converted to a number. 


     RETURNS
         bool: true if the string can be successfully converted to a number, false if otherwise.
     */


    bool isStrNumber(const string& a_str);

        /*
    NAME

        IsValidRegister - Checks if the passed string is formatically valid as a register.

    SYNOPSIS

                bool IsValidRegister(string& a_register);
                    a_register -> the string that represents the potential register.



    DESCRIPTION

        This function checks for the format of the register, namely if it is numeric, and between 0 and 10.


    RETURNS
        bool: true the string meets the format of a register, false if otherwise. 
    */


    bool IsValidRegister(string& a_register);



        /*
    NAME

        isValidLabel - Checks if the passed string is formatically valid as a label..

    SYNOPSIS

                    bool IsValidLabel(string& a_label, bool a_nonDestructive=false);
                    a_label-> the label being checked to see if it is valid.
                    a_nonDestructive -> option to not throw errors and fill with question marks. 
                    Used by opcodes which ignore registers. 



    DESCRIPTION

        This function checks for the format of the label, such as the first digit having to be a letter, and being the correct size, 
        as well as executing the error checking or not depending on the nonDestructive variable, so that opcodes such as read can ignore registers
        without throwing errors.


    RETURNS
        bool: true the string meets the format of a label, false if otherwise.
    */



    bool IsValidLabel(string& a_label, bool a_nonDestructive=false);


    /*
  NAME

      isValidConstant - Checks if the passed string is formatically valid as a constant, depending on instruction.

  SYNOPSIS

        bool IsValidConstant(string& a_constant, string &extraArg, int lowerBound, int upperBound) 

            a_constant -> the constant to be checked for format. 
            extraArg -> checks to see if there's an extra argument. 
            lowerBound-> the lower bound of the range of constants.
            upperBound -> the higher bound of the range of constants.



  DESCRIPTION

      This function checks for the format of the constant, seeing if there's any extra arguments, and if it is in the 
      range of [lowerbound, upperBound]. 


  RETURNS
      bool: true the string meets the format of a constant, false if otherwise.
  */



    bool IsValidConstant(string& a_constant, string &extraArg, int lowerBound, int upperBound);



    // Storage of the title of each opcode and it's numeric value. 
    // Specifically, each is stored in a map due to being name and value pairs, 
    // and is a string so the numeric value is pre-formatted.
    // that and attempting to store as an integer with preformated
    // 0s gives the error 'invalid octal number'. 
    const map<string, string> m_OPCodeStorage =
    {
        {"ADD", "01"}, {"SUB", "02"}, {"MULT", "03"},{"DIV", "04"},
        {"LOAD", "05"}, {"STORE", "06"}, {"ADDR", "07"}, {"SUBR", "08"},
        {"MULTR", "09"}, {"DIVR", "10"}, {"READ", "11"}, {"WRITE", "12"},
        {"B", "13"}, {"BM", "14"}, {"BZ", "15"}, {"BP", "16"},
        {"HALT", "17"}
    };




};


