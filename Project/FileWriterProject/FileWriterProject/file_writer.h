#pragma once
#ifndef __FILE_WRITER_H__
#define __FILE_WRITER_H__

struct _iobuf;
typedef struct _iobuf FILE;

namespace PREMIUM {
	enum class FILE_OPEN_MODE {
		FILE_OPEN_MODE_OVER_WRITE,
		FILE_OPEN_MODE_ADD
	};

	class CFileWriter {
	private:
		FILE* m_pFile = nullptr;
		bool m_isOpened = false;
	public:
		bool OpenFile(const char* _filePath, const FILE_OPEN_MODE _mode);
		void Write(const char* _str);
		void WriteLine(const char* _str);
		void CloseFile();
	};

}

#endif // !__FILE_WRITER_H__
