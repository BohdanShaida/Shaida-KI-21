#pragma once

#ifndef AIRLINE_TICKET_H
#define AIRLINE_TICKET_H

#include <string>
#include <iostream>
#include <tuple>
#include <vector>
#include <map>
#include <sstream>


using namespace std;

struct Date {
	int year, month, day;
};

bool operator < (const Date& lhs, const Date& rhs);
bool operator == (const Date& lhs, const Date& rhs);
ostream& operator << (ostream& out, const Date& date);

struct Time {
	int hours, minutes;
};

bool operator < (const Time& lhs, const Time& rhs);
bool operator == (const Time& lhs, const Time& rhs);
ostream& operator << (ostream& out, const Time& time);

struct AirlineTicket {
    std::string from;
    std::string to;
    std::string airline;
    Date departure_date;
    Time departure_time;
    Date arrival_date;
    Time arrival_time;
    uint64_t price;
};

std::ostream& operator<<(std::ostream& os, const Date& date);
std::ostream& operator<<(std::ostream& os, const Time& time);

#endif // AIRLINE_TICKET_H