#ifndef INC_DATA_H
#define INC_DATA_H
#include "data.h"
#endif

#ifndef INC_FUNCTIONS_H
#define INC_FUNCTIONS_H
#include "functions.h"
#endif

using namespace std;

double start_time, end_time;
int dataCNT, wrong_time;
vector<pair<double, int> > record;
vector<VAL> data;

VAL make_VAL(string s, double db1, int in1, double db2, int in2){
	VAL ret;
	ret.id = s;
	ret.used_time1 = db1;
	ret.wrong_time1 = in1;
	ret.used_time2 = db2;
	ret.wrong_time2 = in2;
	return ret;
}

void LoadData(){
	freopen("data.txt", "r", stdin);
	cin >> dataCNT;
	data.resize(dataCNT);
	for(int i = 0; i < dataCNT; i ++){
		cin >> data[i].id >> data[i].used_time1 >> data[i].wrong_time1 >> data[i].used_time2 >> data[i].wrong_time2;
	}
	fclose(stdin);
}

void UpdateData(){
	freopen("data.txt", "w", stdout);
	if(!quit){
		dataCNT += 1;
		data.push_back(make_VAL("test", record[0].first, record[0].second, record[1].first, record[1].second));
	}
	cout << dataCNT << '\n';
	for(auto i : data){
		cout << i.id << ' ' << i.used_time1 << ' ' << i.wrong_time1 << ' ' << i.used_time2 << ' ' << i.wrong_time2 << '\n';
	}
	fclose(stdout);
}
