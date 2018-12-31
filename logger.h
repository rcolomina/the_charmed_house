#ifndef _logger_
#define _logger_

// Logger.h
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <mutex>

using namespace std;

// Definition of a multithread safe singleton logger class
class Logger
{
public:
	static const string kLogLevelDebug;
	static const string kLogLevelInfo;
	static const string kLogLevelError;
	static const string kLogLevelWarning;
	  
	// Returns a reference to the singleton Logger object
	static Logger& instance();

	// Logs a single message at the given log level
	void log(const string& inMessage, 
		const string& inLogLevel);

	// Logs a vector of messages at the given log level
	void log(const vector<string>& inMessages, 
		const string& inLogLevel);

protected:
	// Static variable for the one-and-only instance  
	static Logger* pInstance;

	// Constant for the filename
	static const char* const kLogFileName;

	// Data member for the output stream
	ofstream mOutputStream;

	// Embedded class to make sure the single Logger
	// instance gets deleted on program shutdown.
	friend class Cleanup;
	class Cleanup
	{
	public:
		~Cleanup();
	};

	// Logs message. The thread should own a lock on sMutex
	// before calling this function.
	void logHelper(const string& inMessage, 
		const string& inLogLevel);

private:
	Logger();
	virtual ~Logger();
	Logger(const Logger&);
	Logger& operator=(const Logger&);
	static mutex sMutex;
};

#endif
