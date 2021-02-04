#ifndef INC_CSTDIO
#define INC_CSTDIO
#include <cstdio>
#endif

#ifndef INC_UTILITY
#define INC_UTILITY
#include <utility>
#endif

#ifndef INC_VECTOR
#define INC_VECTOR
#include <vector>
#endif

#ifndef INC_IOSTREAM
#define INC_IOSTREAM
#include <iostream>
#endif

#ifndef INC_CTIME
#define INC_CTIME
#include <ctime>
#endif

using namespace std;

class VAL{
	public:
		string id;
		double used_time1, used_time2;
		int wrong_time1, wrong_time2;
};

extern double start_time, end_time;
extern int dataCNT, wrong_time;
extern string name;
extern vector<pair<double, int> > record;
extern vector<VAL> data;

VAL make_VAL(string s, double db1, int in1, double db2, int in2);
void LoadData();
void UpdateData();
