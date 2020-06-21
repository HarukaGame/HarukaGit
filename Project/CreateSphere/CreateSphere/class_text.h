#pragma once

#ifndef __CLASS_TEXT_H__
#define __CLASS_TEXT_H__
#include <iostream>
#include <fstream>
#include <string>


class CClassText {
public:
	CClassText(std::string _className);
	void WriteHeader(std::ofstream& _ofs);
	void WriteHooter(std::ofstream& _ofs);
private:
	std::string m_className = "";
};

#endif // !__CLASS_TEXT_H__
