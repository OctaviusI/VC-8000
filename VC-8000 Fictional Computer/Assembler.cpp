//
//      Implementation of the Assembler class.
//
#include "stdafx.h"
#include "Assembler.h"
#include "Errors.h"

// Constructor for the assembler.  Note: we are passing argc and argv to the file access constructor.
// See main program.  
Assembler::Assembler( int argc, char *argv[] )
: m_facc( argc, argv )
{
    // Nothing else to do here at this point.
}  

//test

// Pass I establishes the location of the label. 
void Assembler::PassI( ) 
{
    int loc = 0;        // Tracks the location of the instructions to be generated.



    // Successively process each line of source code.
    for( ; ; ) {
        // Read the next line from the source file.
        string line; 
        if( ! m_facc.GetNextLine( line ) ) {

            // If there are no more lines, we are missing an end statement.
            // We will let this error be reported by Pass II.
            return;
        }
        // Parse the line and get the instruction type.
        Instruction::InstructionType st =  m_inst.ParseInstruction( line );

        // If this is an end statement, there is nothing left to do in pass I.
        // Pass II will determine if the end is the last statement and report an error if it isn't.
        if( st == Instruction::InstructionType::ST_End ) 
            return;

        // Labels can only be on machine language and assembler language
        // instructions.  So, skip comments.
        if( st == Instruction::InstructionType::ST_Comment )  
        {
        	continue;
	    }

        //Error handling will be done in Pass II.

        // If the instruction has a label, record it and its location in the
        // symbol table.
        if( m_inst.isLabel( ) ) {
            m_symtab.AddSymbol( m_inst.GetLabel( ), loc );
        }
        // Compute the location of the next instruction.
        loc = m_inst.LocationNextInstruction( loc );
    }

}

//Fills in the contents to pass to the emulator.
string Assembler::FillContents(int a_case, string a_numOP, string a_OP1, string a_OP2, string a_Address) {
    string modifiedContents;
    stringstream stringFiller; //To format the contents string in such a way that it's 
    //replaced by 0s.
    int test = 0;


    if (a_case==1) { //If the contents are an assembly instruction, format the string as such.
        
        stringFiller << right << setw(9) << setfill('0') << a_Address; //Manipulates the string to fill any empty spaces with 0.
        //sets with to 9.
        modifiedContents = stringFiller.str();
    }

    else if (a_case==2) { //If the contents have two registers, then the formatted string has 5 empty digits.
        stringFiller << right << setw(2) << setfill('0') << a_numOP << left << setw(1) << a_OP1 <<left<<setw(1)<< a_OP2<<setw(5)<<setfill('0')<<internal<<"";
        modifiedContents = stringFiller.str();
    }
    else { //Otherwise, fill it like there is 1 register and one label.
        a_OP1 == "" ? a_OP1 = "9" : "";
        a_OP2 == "" ? a_OP2 = "9" : "";
        stringFiller << right << setw(2) << setfill('0') << a_numOP << left << setw(1) << a_OP1 << right << setw(6) << a_Address;
        modifiedContents = stringFiller.str();
    }


    return modifiedContents;
}

void Assembler::TranslateError(Instruction& a_instruction, int a_location) {
    //If the error subtype is an AssemblyInstruction, format as such. 
    if (a_instruction.GetErrorType() == Instruction::InstructionType::ST_AssemblerInstr) {
        TranslateAssemblyInstruction(m_inst, a_location); 
    }
    //If the error subtype is an Machine Language Instruction, format as such. 
    else if (a_instruction.GetErrorType() == Instruction::InstructionType::ST_MachineLanguage) { //Uses to
        TranslateMachineLanguage(m_inst, a_location); //calls a function to "translate" the instruction
    }
    
    else {
        TranslateComment(m_inst); 
    }

    //Iterate through the format Errors and print. 
    vector<string> formatErrors = a_instruction.GetFormatError();
    for (auto itr = formatErrors.begin(); itr != formatErrors.end(); itr++) {
        Errors::RecordError(*itr);
    }
}



void Assembler::TranslateComment(Instruction& a_instruction) {  
    //Simply output the message.
    cout << setw(20)<< left << ""<< a_instruction.GetInstruction() << endl;
}


void Assembler::TranslateAssemblyInstruction(Instruction& a_instruction, int a_location) {
    string contentAddition = "";
    

     if (a_instruction.GetOpCode() == "ORG") { //If the instruction is an ORG, only send the
        //location and original message. Also, set the origin.
        m_emul.setOrigin(stoi(a_instruction.GetOperand1()));

     }
    
    else if (a_instruction.GetOpCode() == "DC") { //If the instruction is a DC, send all values,
        //filling contents with the value of the defined constant.
        contentAddition = a_instruction.GetOperand1();
        contentAddition = FillContents(1, "", "", "", contentAddition);
    }

    else if (a_instruction.GetOpCode() == "DS") { //If the instruction is a DS, 
        //only send the location and original message.
    }

    
    
    if (contentAddition != "" && contentAddition!= "?????????") { //Ensure the content is not empty or that it's not 
        //in an error state before translating the string to insert.
        long long x = stoll(contentAddition,nullptr, 10);
        m_emul.insertMemory(a_location, x);
    }

    //Since we already stored the contents, print out immeadiately.
    cout << setw(10) << left << a_location << setw(13) << contentAddition;
    cout << a_instruction.GetInstruction() << endl;

}



bool Assembler::IsValidAddress(string& a_labelOperand, int& a_address) {
    if (m_symtab.LookupSymbol(a_labelOperand, a_address)) { //Look and see if the symbol is defined, and if so, multiply defined..
        if (a_address == -999) { //If so, make an error.
            Errors::RecordError("Multi defined symbol " + a_labelOperand);
            a_labelOperand = "??????";
            return false;
        }
        return true;
    }
    else {  //If the symbol isn't present at all, make an error.
        Errors::RecordError("Undefined Symbol " + a_labelOperand);
        a_labelOperand = "??????";
        return false;
    }
    
   
}



void Assembler::TranslateMachineLanguage(Instruction& a_instruction, int a_location) {
    string OPcode = to_string(a_instruction.GetNumOpCode()); //The numeric opcode in string form.
    string OP1; //Operand1.
    string OP2; //Operand2.
    int address=0; //The address. 
    string formattedContent; //The smartly filled content in 9 digit address. 

    if (a_instruction.GetIsNumOP1() && a_instruction.GetIsNumOP2()) { //If the two operands are registers, then format appropriately.
        OP1 = a_instruction.GetOperand1();
        OP2 = a_instruction.GetOperand2();
        formattedContent = FillContents(2, OPcode, OP1, OP2);
    }


    else if (a_instruction.GetIsNumOP1()&& a_instruction.GetIsNumOP2()==false) {
        //If the first operand is a register and the other is not, then format appropriately.
        OP1 = a_instruction.GetOperand1();
        OP2 = a_instruction.GetOperand2();
        formattedContent = "";
        if (IsValidAddress(OP2, address)) { //Sees if the address operand is in the symbol table.
            formattedContent = FillContents(3,OPcode, OP1, "", to_string(address)); 
        }
        else {
            formattedContent = FillContents(3,OPcode, OP1, "", "??????");

        }
    }


    else if (a_instruction.GetOperand1() == "" && a_instruction.GetOperand2() == "") {         //If the instruction has no operands, format approprimately.
        formattedContent = FillContents(3, OPcode, "", "", ""); //Fills the content w opcode with their default values. Explicit call just to be safe.
    }

    else if (a_instruction.GetIsNumOP1() == false && a_instruction.GetOperand2() == "") { //if the instruciton  has 1 label and nothing else, format appropriately.
        OP1 = a_instruction.GetOperand1();
        if (IsValidAddress(OP1, address)) { //Checks if the symbol is defined. 
            formattedContent = FillContents(3,OPcode, "", "", to_string(address)); //Sends the opcode w opcode, and default values of 9 for the operands, alongside the address.
        }
        else {
            formattedContent = FillContents(3,OPcode, OP1, "", to_string(address)); //if it's not, then still fill, but record an error.
            Errors::RecordError("Undefined label " + OP1);
        }
    }


    string test = formattedContent; //inserts the Machine Language into memory. 
    if (formattedContent != "") {
        long long x = stoll(test, nullptr, 10);
        m_emul.insertMemory(a_location, x);
    }
  
    cout << setw(10) << left << a_location <<  setw(13) << formattedContent;
    cout << a_instruction.GetInstruction() << endl;
    //Output translated contents immeadiately after, since they're already stored.


}




void Assembler::PassII() {
    int loc = 0;        // Tracks the location of the instructions to be generated.
    bool should_End = false;
    bool should_Halt = false;
    cout << setfill(' ') << "Location" << setw(10) << "Contents" << setw(20) << "Original Statement" << endl;

    // Successively process each line of source code.
    m_facc.rewind(); //rewinds the file so that Pass II can go through the file again.
    


    for (; ; ) {

        Errors::InitErrorReporting();

        // Read the next line from the source file.
        string line;
        if (!m_facc.GetNextLine(line)) {

            // If there are no more lines, we are missing an end statement.
            // We will let this error be reported by Pass II.
            
            if (should_End)
                return;

            Errors::RecordError("Lacking an end statement!");
            Errors::DisplayErrors();
            return;
        }
        // Parse the line and get the instruction type.
       
        Instruction::InstructionType st = m_inst.ParseInstruction(line);

        if (should_End) {
            Errors::RecordError("Unexpected statement after end");
        }

        // If this is an end statement, there is nothing left to do in pass I.
        // Pass II will determine if the end is the last statement and report an error if it isn't.
        if (st == Instruction::InstructionType::ST_End) {
            should_End = true;
            cout << "\t\t" << "end" << endl;
            //return;
        }

        // Labels can only be on machine language and assembler language
        // instructions.  So, skip comments.
       if (st == Instruction::InstructionType::ST_Comment)
        {
           TranslateComment(m_inst);
        }
        // Handle the case where there is an error.

       //If there's an error, translate it via it's subtype.
       if (st == Instruction::InstructionType::ST_Error) {
           TranslateError(m_inst, loc);
       }


        //Handles the case when there is a machine language operand.
        if (st == Instruction::InstructionType::ST_MachineLanguage) {
            TranslateMachineLanguage(m_inst, loc); //calls a function to translate the instruction
            //and then put it into the instruction table.
            // Compute the location of the next instruction.k
            loc = m_inst.LocationNextInstruction(loc);
        }
        //Handles the cause if there is an assembler instruction. 
        if (st == Instruction::InstructionType::ST_AssemblerInstr) {
            TranslateAssemblyInstruction(m_inst, loc ); //calls a function to translate the instruction
            loc = m_inst.LocationNextInstruction(loc);  // Compute the location of the next instruction.

        }
        
        

        Errors::DisplayErrors();


        
    }

}

void Assembler::RunProgramInEmulator() {
    if (!Errors::HasErrors()) { //If the program has errors, don't run the emulator. 
        Errors::InitErrorReporting(); //Clear the error reporting for the emulator. 
        bool ranSuccessfully = m_emul.runProgram();
        if (!ranSuccessfully) { //If the emulator didn't run succesfully, display errors.
            Errors::DisplayErrors();
        }
    }
    else { //Exit program if there's errors preventing emulation
        cout << "Emulation halted: please fix the errors listed above^: " << endl;
        exit(-1);
    }
        
}


