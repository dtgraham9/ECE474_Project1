#pragma once
class ReservationStation //Abbrv to RS
{
public:
	bool busy;
	int tag1;
	int tag2;
	int value1;
	int value2;
	int op;
	int result;
	bool result_ready;
	int ext_lat; //Track execution of RS in execute
	int issue_lat;  //track issue latency
	int broadcast_lat; //track broadcast latency

	//**** Methods
public:
	ReservationStation();
	ReservationStation(int, int);
	void ClearResrvStat();
};


