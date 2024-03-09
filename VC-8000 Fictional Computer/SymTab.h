#pragma once



class SymbolTable {

public:
    
    const int multiplyDefinedSymbol = -999;

    // Add a new symbol to the symbol table.
       /*
    NAME

        AddSymbol - adds a new symbol to the symbol table.

    SYNOPSIS

        void AddSymbol( const string &a_symbol, int a_loc );
            a_symbol	-> The name of the symbol to be added to the symbol table.
            a_loc		-> the location to be associated with the symbol.

    DESCRIPTION

        This function will place the symbol "a_symbol" and its location "a_loc"
        in the symbol table.
    */
    
    
    void AddSymbol( const string &a_symbol, int a_loc );




        /*
    NAME

        DisplaySymbolTable - displays the currently stored symboltable by three values:
        the number of symbol, opcode name, and address location. 

    SYNOPSIS

        void DisplaySymbolTable();

    DESCRIPTION

        This function will set the labels of the table using setw(), an output manipulator, and then will
        iterate through the parts of the symboltable (map) using a for each loop ulitizing the variable const
        variable reference symbol alongside a counter to track the number of symbols, alongside printing out
        the opcode name and the address location by using key value pair .first and .second using the map syntax.

    */



    void DisplaySymbolTable();

    

        /*
    NAME

        LookupSymbol - returns true or false if a symbol is found in the Symbol Table.

    SYNOPSIS

        void DisplaySymbolTable();

    DESCRIPTION

        This function will set the labels of the table using setw(), an output manipulator, and then will
        iterate through the parts of the symboltable (map) using a for each loop ulitizing the variable const
        variable reference symbol alongside a counter to track the number of symbols, alongside printing out
        the opcode name and the address location by using key value pair .first and .second using the map syntax.

    */
    // Lookup a symbol in the symbol table.
    bool LookupSymbol( const string &a_symbol, int &a_loc );

private:

    // Underlying data of the Symbol Table. The symbol is the key to the map.  The value is the location.
    map<string, int> m_symbolTable;
};
