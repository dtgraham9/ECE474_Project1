#include "ReservationStation.h"

void ReservationStation::ClearResrvStat()
{
}

ReservationStation::ReservationStation(){
    busy = false;
    op = 0;
    result = 0;
    result_ready = false;
    tag1 = -2;
    tag2 = 2;
    value1 = 0;
    value2 = 0;
    issue_lat = 0;
	ext_lat = 0;
    broadcast_lat= 0;
}

ReservationStation::ReservationStation(int OP, int RSoperandAvailable){
	busy = false;
	op = OP;
	result = 0;
	result_ready = false;
	tag1 = RSoperandAvailable;
	tag2 = RSoperandAvailable;
	value1 = 0;
	value2 = 0;
	issue_lat = 0;
	ext_lat = 0;
	broadcast_lat = 0;
}