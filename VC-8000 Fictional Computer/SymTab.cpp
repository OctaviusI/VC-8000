
#include "stdafx.h"
#include "SymTab.h"


void SymbolTable::AddSymbol( const string &a_symbol, int a_loc )
{
    // If the symbol is already in the symbol table, record it as multiply defined.
    map<string, int>::iterator st = m_symbolTable.find( a_symbol );
    if( st != m_symbolTable.end() ) {

        st->second = multiplyDefinedSymbol;
        return;
    }
    // Record a the  location in the symbol table.
    m_symbolTable[a_symbol] = a_loc;
}





void SymbolTable::DisplaySymbolTable() {
    stringstream stringFormatter; 
    
    cout << "Symbol Table:" << endl << endl;
    cout << setfill(' ') << "Symbol #" << setw(13) << "Symbol" << setw(11) << "Location" << endl;
    unsigned counter = 0;


    for (auto const& symbol : m_symbolTable) { //iterate through the symbol table and display in a formatted order.
        cout << right <<  setw(2) << counter << setw(15) << symbol.first << setw(11) << symbol.second << endl;
        counter++;
    }
}






bool SymbolTable::LookupSymbol(const string& a_symbol, int& a_loc) { 
    auto foundvalue = m_symbolTable.find(a_symbol) ; // Check if the passed symbol is recorded.
    if (foundvalue != m_symbolTable.end()) { // If it's found, put the location as the value.
        a_loc = foundvalue->second;
        return true;
    }
    else
        return false; 
}
