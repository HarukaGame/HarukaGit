#include "file_writer.h"
#include <stdio.h>
#include "debug_print.h"
#  pragma warning(disable: 4996)

namespace PREMIUM {

	bool CFileWriter::OpenFile(const char* _filePath, const FILE_OPEN_MODE _mode) {
		if (m_isOpened == true) {
			PRINT("CFileWriter::OpenFile already opened\n");
			return false;
		}

		if (_mode == FILE_OPEN_MODE::FILE_OPEN_MODE_OVER_WRITE) {
			m_pFile = fopen(_filePath, "w");
		}
		else if (_mode == FILE_OPEN_MODE::FILE_OPEN_MODE_ADD) {
			m_pFile = fopen(_filePath, "a");
		}
		else {
			PRINT("CFileWriter::OpenFile _mode is invalid\n");
			return false;
		}
		if (m_pFile == nullptr) {
			PRINT("CFileWriter::OpenFile open failed\n");
			return false;
		}
		m_isOpened = true;
		return true;
	}
	void CFileWriter::Write(const char* _str){
		if (m_isOpened == false) {
			PRINT("CFileWriter::Write file is not opened\n");
			return;
		}

		if (m_pFile == nullptr) {
			PRINT("CFileWriter::Write m_pFile is nullptr\n");
			return;
		}
		fprintf(m_pFile, _str);
	}
	void CFileWriter::WriteLine(const char* _str)
	{
		Write(_str);
		Write("\n");
	}
	void CFileWriter::CloseFile(){
		fclose(m_pFile);
		m_isOpened = false;
	}
}