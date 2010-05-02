#ifndef _LOGGER_H
#define _LOGGER_H

#include <iostream>
#include <string>
#include <cstring>

using std::string;
using std::cerr;
using std::endl;

namespace pv 
{

/**
 * LogElement constants, which can be used for Logger::elements
 */
enum LogElements
{
	ERRORS   = 1,
	WARNINGS = 2,
	MESSAGES = 4
};

/**
 * A class that handles logging.
 */
class Logger 
{
private:
	static string timestamp()
	{
		time_t rawtime;
		tm* timeinfo;
		time( &rawtime );
		timeinfo = localtime( &rawtime );
		string ret( asctime( timeinfo ) );
		ret[ret.length()-1] = '\0';
		return ret;
	}

public:
	static LogElements elements; //< What elements to log

	/**
	 * Log with tyoe appended to the beginning of the string (between []).
	 * @param type The type to append.
	 * @param msg The message to show.
	 */
	static void log( string type, string& msg )
	{
		cerr << "[" << type << "] @ " << timestamp() << ": " << msg << endl;
	}

	/**
	 * Log an error (if errors are enabled).
	 * @param msg The error message to display.
	 */
	static void error( string msg )
	{
		if ( Logger::elements & ERRORS )
		{
			log("ERR", msg);
		}
	}

	/**
	 * Log an warnings (if warnings are enabled).
	 * @param msg The warning message to display.
	 */
	static void warning(string msg)
	{
		if ( Logger::elements & WARNINGS )
		{
			log("WRN", msg);
		}
	}

	/**
	 * Log a message (if messages are enabled).
	 * @param msg The message to display.
	 */
	static void message(string msg)
	{
		if ( Logger::elements & MESSAGES )
		{
			log("MSG", msg);
		}
	}
};

}

#endif

