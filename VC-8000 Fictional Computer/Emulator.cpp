#include "stdafx.h"
#include "Emulator.h"
#include "Errors.h"



bool emulator::insertMemory(int a_location, long long a_contents) {
	if (a_location > 10000 || a_location < 0 ) { // Checks if the memory will be inserted within bounds.
		Errors::RecordError("Error: out of bounds"); // If it is not, record an error.
		return false;
	}
	m_memory[a_location] = a_contents; // If it is, insert it. 

	return true;
}



bool emulator::ml_Read(int a_location) {
	cout << "? ";
	string parser;
	cin >> parser; 

	// If there's a sign infront of the string, then skip over it.
	auto itr = (parser[0] == '-' || parser[0] == '+') ? parser.begin() + 1 : parser.begin();

	// Uses an stl method to check if everything in the string is a digit.
	if (!(all_of(itr, parser.end(), ::isdigit))) {
		Errors::RecordError("Error: inputted string is not numeric.");
		return false;
	}

	// Since the emulator has a set memory size since we are using a long long. This is to avoid going over the size.
	if (parser.size() > 20) {
		Errors::RecordError("Error: inputted string is too large for the VC-8000 Memory.");
		return false;
	}


	long long parsedinput = stoll(parser, nullptr, 10); // converts to long long
	m_memory[a_location] = parsedinput;
	return true;
}




bool emulator::runProgram() {
	int address = m_ADDRESS_ORIGIN;
	
	while (address < MEMSZ) {
		long long lastOPCode=0; // The last opcode to check for a halt.
		if (m_memory[address] != 0) {
			long long opCode = m_memory[address] / 10'000'000; //extracts the opcode from memory
			lastOPCode = opCode; // Stores the last opcode to check for a halt. 
			int op1 = (m_memory[address] % 10'000'000) / 1'000'000; // Extracts the first operand from memory
			int op2, location, constant = 0; 
			op2 = ((m_memory[address] % 10'000'000) % 100'000) == 0 ? (m_memory[address] % 1'000'000)/ 100'000 : 0;
			// Extracts the second operand if there is nothing in the address portion of the memory.
			location = (op2 == 0 ? ((m_memory[address] % 10'000'000) % 100'000) : 0); // Extracts the address part of a label from memory. 


			switch (opCode) {
				case 1: { // Add
					m_register[op1] += m_memory[location];
					break;
				}
				case 2: { // Subtract
					m_register[op1] -= m_memory[location];
					break;
				}
				case 3: { // Multiply
					m_register[op1] *= m_memory[location];
					break;
				}
				case 4: { // Divide
					m_register[op1] /= m_memory[location];
					break;
				}
				case 5: { // Load
					m_register[op1] = m_memory[location];
					break;
				}
				case 6: { // Store
					m_memory[location] = m_register[op1];
					break;
				}
				case 7: { // Add reg
					m_register[op1] += m_register[op2];
					break;
				}
				case 8: { // Sub reg
					m_register[op1] -= m_register[op2];
					break;
				}
				case 9: { // Multi reg
					m_register[op1] *= m_register[op2];
					break;
				}
				case 10: { // Divide reg 
					m_register[op1] /= m_register[op2];
					break;
				}
				case 11: { // Read
					bool isReadSuccessfully = ml_Read(location);
					if (isReadSuccessfully)
						break;
					else
						return false;
				}
				case 12: { // Write
					cout << m_memory[location] << endl;
					break;
				}
				case 13: { // Branch
					address = location;
					continue;
					break;
				}
				case 14: { // Branch minus
					if (m_register[op1] < 0) {
						address = location;
						continue;
					}
					break;
				}
				case 15: { // Branch zero
					if (m_register[op1] == 0) {
						address = location;
						continue;
					}
					break;
				}
				case 16: { // Branch positive
					if (m_register[op1] > 0) {
						address = location;
						continue;
					}
					break;
				}
				case 17: { // Halt
					return true;
					break;
				}
				default: { // Unknown/Illegal OPCODE
					stringstream errmsg; // Helps format the message we are going to throw. 
					errmsg << "Illegal OPcode " << opCode << " at address " << address << endl;
					Errors::RecordError(errmsg.str());
					break;
					return false;
				}
			}
		}
		else {
			if (lastOPCode != 17) { // If the last OPcode wasn't a halt, make an error.
				Errors::RecordError("Code statements did not stop executing with a halt, exiting...");
			}
			return false;
		}
		
		address++; // Iterate the Emulator loop.
	}
	Errors::RecordError("Emulator ran past memory. Terminating..."); 
	return false;

}


void emulator::setOrigin(int a_location) {
	m_ADDRESS_ORIGIN = a_location;
}