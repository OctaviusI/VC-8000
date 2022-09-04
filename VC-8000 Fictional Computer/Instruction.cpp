#include "stdafx.h"

#include "Instruction.h"

// parse an instruction and return its type.  Call by value to avoid any conflicts with referencing the line.
Instruction::InstructionType Instruction::ParseInstruction(string a_line)
{
    // Record the original statement.  This will be needed in the sceond pass.
    m_instruction = DeleteLeftWhitespaces(a_line);

    // Delete any comment from the line.
    DeleteComment( a_line );


    // Removes any white space, so the line can be neatened when outputted.
    //DeleteLeftWhitespaces(a_line);

    // Record label, opcode, and operands.  Up to you to deal with formatting errors.
    bool isNotFormatError = RecordFields( a_line );

    if (!isNotFormatError) {
        return InstructionType::ST_Error;
    }


    
    // Check if this is a comment.
    if (m_Label.empty() && m_OpCode.empty())
    {
        return InstructionType::ST_Comment;
    }

    if (m_OpCode == "end")
        return InstructionType::ST_End;

   



    // Return the instruction type.
    return m_type;

}
// Record the fields that make up the instructions.
bool Instruction::RecordFields( const string &a_line )
{
    m_formatError.clear();
    m_type = InstructionType::ST_Error;
    m_errorType = InstructionType::ST_Error;
    // Get the fields that make up the instruction.
    bool isNotFormatError = ParseLineIntoFields( a_line, m_Label, m_OpCode, m_Operand1, m_Operand2);

    // if code was a comment, there is nothing to do.
    if (m_OpCode.empty() && m_Label.empty()) return isNotFormatError;

    // Record whether the operands are numeric and their value if they are.
    m_IsNumericOperand1 = isStrNumber(m_Operand1);
    if (m_IsNumericOperand1) m_Operand1NumericValue = stoi(m_Operand1);

    m_IsNumericOperand2 = isStrNumber(m_Operand2);
    if (m_IsNumericOperand2) m_Operand2NumericValue = stoi(m_Operand2);

    // For the sake of comparing, convert the op code to upper case.
    transform(m_OpCode.begin(), m_OpCode.end(), m_OpCode.begin(), ::toupper);


    //Check for Assembly formatting in each OPCode given its
    //maximum and minimum range. If there's no errors, keep it as
    //an assembly instruction.
    if (m_OpCode == "DS") { 
        if (IsValidConstant(m_Operand1, m_Operand2, 0, 999'999))
            m_type = InstructionType::ST_AssemblerInstr;
        else {
            isNotFormatError = false;
        }
    }
    
    else if (m_OpCode == "DC") {

        if (IsValidConstant(m_Operand1, m_Operand2, -999'999, 999'999))
            m_type = InstructionType::ST_AssemblerInstr;
        else {
            isNotFormatError = false;
            m_errorType = InstructionType::ST_AssemblerInstr;
        }
    }

    else if (m_OpCode == "ORG") {
        if (IsValidConstant(m_Operand1, m_Operand2, 99, 999'999))
            m_type = InstructionType::ST_AssemblerInstr;
        else {
            isNotFormatError = false;
        }
    }
    
   else if (m_OpCode == "END") //If there's an end, it should have no operands.
       if (m_Operand1 == "" && m_Operand2 == "") {
           m_type = InstructionType::ST_End;
       }
       else {
           m_formatError.push_back("Statements such as END cannot have additional operands.");
           isNotFormatError = false;
       }
    //used to find if the specified OPcode is in OPcodestorage.  

    //Check if this is a machine language OPcode, if not, 
    else if (auto key = m_OPCodeStorage.find(m_OpCode); key != m_OPCodeStorage.end()) {

        m_NumOpCode = stoi(key->second); //Gather numeric opcode from the results
        m_type = InstructionType::ST_MachineLanguage;
        m_errorType = InstructionType::ST_MachineLanguage;
        switch (m_NumOpCode) {
            case 1:
            case 2:
            case 3:
            case 4:
            case 5:
            case 6: {
                //ADD to STORE excpect a Register and a Label.
                bool validArg1 = IsValidRegister(m_Operand1);
                bool validArg2 = IsValidLabel(m_Operand2);
                isNotFormatError = (validArg1 && validArg2) ? true : false;
                break;
            }
            case 7: 
            case 8: 
            case 9: 
            case 10: { //ADDREG to DIVREG expects two Registers.
                bool validArg1 = IsValidRegister(m_Operand1);
                bool validArg2 = IsValidRegister(m_Operand2);
                isNotFormatError = (validArg1 && validArg2) ? true : false;
                break;
            }
            case 11: 
            case 12:
            case 13: { //Read, Write, and Branch expect one label or an ignored register and label.
                bool validArg1 = IsValidLabel(m_Operand1,true);
                if (validArg1 && m_Operand2=="") {
                    break;
                }

                else if (!validArg1 && m_Operand2=="") {
                    isNotFormatError = false;
                    break;
                }

                else if (validArg1 && m_Operand2 != "") {
                    m_formatError.push_back("Expected 1 label, got extra argument: "+m_Operand2+". Use a register as a placeholder as the first argument as a placeholder.");
                    isNotFormatError = false;
                    break;
                }

                else {
                    bool validArg2 = IsValidLabel(m_Operand2);
                    isNotFormatError = validArg2;
                    break;
                }
            }
            case 14:
            case 15:
            case 16: { //Branch Positive to Branch Minus expects a Register and a Label.
                bool validArg1 = IsValidRegister(m_Operand1);
                bool validArg2 = IsValidLabel(m_Operand2);
                isNotFormatError = (validArg1 && validArg2) ? true : false;
                break;
            }
            case 17: { //Halt expects no operands. 
                if (m_Operand1 != "" || m_Operand2 != "") {
                    m_formatError.push_back("Statements such as HALT cannot have operands.");
                    isNotFormatError = false;
                }
                else
                    break;
            }
            default: { //Copy of below line just to make sure this works.
                m_formatError.push_back("Statement unparsable, no opcode fits the given line...");
                isNotFormatError = false; 
            }
                
        }

    }

    else {
       m_formatError.push_back("Statement unparsable, no opcode fits the given line...");
       isNotFormatError = false;
    }




    return isNotFormatError;
}

// Parse the intruction into fields.
bool Instruction::ParseLineIntoFields(string a_line, string& a_label, string& a_OpCode,
    string& a_Operand1, string& a_Operand2)
{
    // Get rid of any commas from the line.
    replace(a_line.begin(), a_line.end(), ',', ' ');

    // Get the elements of the line.  That is the label, op code, operand1, and operand2.
    string endStr;
    a_label = a_OpCode = a_Operand1 = a_Operand2 = "";
    istringstream ins(a_line);
    if (a_line[0] == ' ' || a_line[0] == '\t')
    {
        a_label = "";
        ins >> a_OpCode >> a_Operand1 >> a_Operand2 >> endStr;
    }
    else
    {
        ins >> a_label >> a_OpCode >> a_Operand1 >> a_Operand2 >> endStr;
    }
    // If there is extra data, return false.
    if (bool isEmpty = endStr.empty(); isEmpty) {
        return true;
    }
    else {
        m_formatError.push_back("Statement has 3 or more operands");
        return false;
    }
}

bool Instruction::isStrNumber(const string& a_str)
{
    if (a_str.empty()) return false;

    // If there is a - or a plus, make sure there are more characters.
    int ichar = 0;
    if (a_str[0] == '-' || a_str[0] == '+')
    {
        ichar++;
        if (a_str.length() < 2) return false;
    }
    // Make sure that the remaining characters are all digits
    for (; ichar < a_str.length(); ichar++)
    {
        if (!isdigit(a_str[ichar])) return false;
    }
    return true;
}



bool Instruction::IsValidRegister(string& a_register) {

    
    if (a_register == "") { //checks if register is blank.
        m_formatError.push_back( "Missing register operand or empty register field");
        return false;
    }

    bool isNum = isStrNumber(a_register); //checks if register is numeric.
    int translatedregister; 
    if (isNum) { //if numeric, translate it.
        translatedregister = stoi(a_register);
    }

    else { //Otherwise, record an error.
        m_formatError.push_back( "Register " + a_register + " is not numeric");
        a_register = "?";
        return false;
    }

    if (translatedregister > -1 && translatedregister < 10) { //If the register is between 1 and 10, we can return.
        return true;
    }
    else { //Otherwise, it's not a register, throw an error.
        a_register = "?";
        m_formatError.push_back("Unknown Register " + a_register + ": Registers are only from 0 to 9");
        return false;
    }
}



bool Instruction::IsValidLabel(string& a_label, bool a_nonDestructive) {
    
    if (a_label == "") {
        if (!a_nonDestructive) { //So we don't mess up the contents of the ignored register 
            m_formatError.push_back("Missing label operand or label field empty");
            a_label = "??????";
        }
        return false;
    }
    
    
    if (a_label.size() > 10) {
        if (!a_nonDestructive) { //So we don't mess up the contents of the ignored register
            m_formatError.push_back("label size cannot be greater than 10.");
            a_label = "??????";
        }
        return false;
    }

    if (!isalpha(a_label[0])) {
        if (!a_nonDestructive) { //So we don't mess up the contents of the ignored register 
            m_formatError.push_back("Start of label must be a letter, got label " + a_label + " instead.");
            a_label = "??????";
        }
        return false;
    }

    for (auto itr = a_label.begin(); itr!= a_label.end(); itr++)
        if (!isalnum(*itr)) { //So we don't mess up the contents of the ignored register 
            if (!a_nonDestructive) {
                m_formatError.push_back("Non alphanumeric character in label: " + *itr);
                a_label = "??????";
            }
            return false;
        }
    return true; 

}



bool Instruction::IsValidConstant(string& a_constant, string& extraArg, int lowerBound, int upperBound) {
    int translatedContent;
    
    if (extraArg != "") {
        m_formatError.push_back("Expected 1 argument, got extra argument" +extraArg);
        a_constant = "?????????";
        return false;
    }
   
    if (a_constant == "") {
        m_formatError.push_back("Missing constant or constant field empty");
        a_constant = "?????????";
        return false;
    }
        

    if (Instruction::isStrNumber(a_constant)) {
        translatedContent = stoi(a_constant);
        if (translatedContent < upperBound && translatedContent>lowerBound) {
            return true;
        }
        else {
            stringstream formatter;
            formatter << "Value too large or small, please choose a value between " << lowerBound << " and " << upperBound;
            m_formatError.push_back(formatter.str());
            a_constant = "?????????";;
            return false;
        }

    }
    
    else {
        m_formatError.push_back("Constant value " + a_constant + " is not numeric");
        a_constant = "?????????";
        return false;
    }

   
}



