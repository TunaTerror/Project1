#include <stdarg.h>
#include <iostream>
#include <time.h>
#include "logging.h"
bool restart_gl_log() {
	FILE* file = fopen(GL_LOG_FILE, "w");
	if (!file) {
		fprintf(stderr,
			"ERROR: could not open GL_LOG_FILE log file %s for writing\n",
			GL_LOG_FILE);
		return false;
	}
	time_t now = time(NULL);
	char* date = ctime(&now);
	fprintf(file, "GL_LOG_FILE log. local time %s\n", date);
	fclose(file);
	return true;
}
bool gl_log(const char* message, ...) {
	va_list argptr;
	errno_t err;
	FILE* file;
	err = fopen_s(&file, GL_LOG_FILE, "a");
	if (err) {
		fprintf(
			stderr,
			"ERROR: could not open GL_LOG_FILE %s file for appending: %s\n",
			GL_LOG_FILE, strerror(err)
		);
		return false;
	}
	va_start(argptr, message);
	vfprintf(file, message, argptr);
	va_end(argptr);
	fclose(file);
	return true;
}
bool gl_log_err(const char* message, ...) {
	va_list argptr;
	errno_t err;
	FILE* file;
	err = fopen_s(&file, GL_LOG_FILE, "a");
	if (err) {
		fprintf(
			stderr,
			"ERROR: could not open GL_LOG_FILE %s file for appending: %s\n",
			GL_LOG_FILE, strerror(err)
		);
		return false;
	}
	va_start(argptr, message);
	vfprintf(file, message, argptr);
	va_end(argptr);
	va_start(argptr, message);
	std::cout << "ERROR, WRITING TO LOG" << std::endl;
	vfprintf(stderr, message, argptr);
	std::cout << std::endl;
	va_end(argptr);
	fclose(file);
	return true;
}
