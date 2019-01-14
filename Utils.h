//
// Created by USER on 12/4/2018.
//

#ifndef CONTINUOUSPROCESSING_UTILS_H
#define CONTINUOUSPROCESSING_UTILS_H


#pragma warning(disable:4996)


#include <time.h>
#include <string>
#include <sstream>
#include <vector>
#include <chrono>
#include <cstring>

#define random(a, b) (rand() % (b-a) + a)
#define randomInt(a, b) (rand() % b + a)

using namespace std;
class Utils {
public:
	//system wise id
	static unsigned long id;

    //get the current time, millisecond.
    static long long getTime();

    //static string getTimeStr();

    static double randomFloat(int min, int max);

    static string getRandomGroupName(int startRange = 0, int endRange = 100);

    static void lTrim(char * str);

    static void rTrim(char * str);

    static void trim(char * str);

    static string lTrim(const string& str);

    static string rTrim(const string& str);

    static string trim(const string& str);

    static string toLower(const string& s);

    static string toUpper(const string& s);

    static std::vector<std::string> split(const std::string &str, const std::string &delim);

    static void deleteAllMark(string &s, const string &mark);
};

#endif //CONTINUOUSPROCESSING_UTILS_H
