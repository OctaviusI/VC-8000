#include "stdafx.h"

#include "Errors.h"

vector<string> Errors::m_ErrorMsgs;
bool Errors::m_ProgramHasErrors;

void Errors::InitErrorReporting() {
	m_ErrorMsgs.clear();
}

void Errors::DisplayErrors() {
	for (auto errorItr = m_ErrorMsgs.begin(); errorItr != m_ErrorMsgs.end(); errorItr++)
		cout << "Error: " << *errorItr << endl;
}

void Errors::RecordError(string a_emsg) {
	//cout << a_emsg << endl;
	m_ErrorMsgs.push_back(a_emsg);
	m_ProgramHasErrors = true;
}

bool Errors::HasErrors() {
	return m_ProgramHasErrors;
}