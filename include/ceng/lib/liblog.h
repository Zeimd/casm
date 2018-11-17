/*****************************************************************************
*
* ce-log.h
*
* By Jari Korkala 2/6/2011
*
* Concept Engine global log mechanism
*
*****************************************************************************/

#ifndef _CONCEPT2_LOG_H
#define _CONCEPT2_LOG_H

#include <fstream>

#include <ceng/datatypes/basic-types.h>
#include <ceng/datatypes/return-val.h>
#include <ceng/datatypes/ce-string.h>

namespace Ceng
{

	class LogType
	{
	public:
		LogType();
		virtual ~LogType();
	
		virtual CRESULT Print(const Ceng::String &text);

		virtual LogType& operator << (const Ceng::String &source)
		{
			return *this;
		}

		virtual LogType& operator << (const Ceng::String::CONST_REF_TYPE &source)
		{
			return *this;
		}

		virtual LogType& operator << (std::wostream& (*f)(std::wostream&))
		{
			return *this;
		}
	};

	// Abstract logging mechanism
	class Log
	{
	private:

		static LogType nullLog;

		static LogType *globalLog;

	public:
		Log();
		virtual ~Log();

		static CRESULT SetLog(LogType *log);
		static void UnsetLog();
		
		static CRESULT Print(const Ceng::String &text);
	};

	//****************************************************************************
	// Console log

	class ConsoleLog : public LogType
	{
	public:

		ConsoleLog();
		virtual ~ConsoleLog();

		virtual CRESULT Print(const Ceng::String &text);

		virtual LogType& operator << (const Ceng::String &source);

		virtual LogType& operator << (const Ceng::String::CONST_REF_TYPE &source);

		virtual LogType& operator << (std::wostream& (*f)(std::wostream&));
	};

	//****************************************************************************
	// Log types

	class FileLog : public LogType
	{
	protected:
		std::ofstream outputFile;

	public:
		FileLog();
		virtual ~FileLog();
	
		CRESULT OpenFile(const char *fileName);
	
		CRESULT CloseFile();
		
		virtual CRESULT Print(const Ceng::String &text);
		
	};

}

#endif