#include "airline_ticket.h"
#include "test_runner.h"

using namespace std;

#define UPDATE_FIELD(ticket, field, values) \
    if (values.count(#field)) { \
        istringstream is(values.at(#field)); \
        is >> ticket.field; \
    }

bool operator<(const Date & lhs, const Date & rhs) {
    return std::tie(lhs.year, lhs.month, lhs.day) < std::tie(rhs.year, rhs.month, rhs.day);
}

bool operator==(const Date & lhs, const Date & rhs) {
    return std::tie(lhs.year, lhs.month, lhs.day) == std::tie(rhs.year, rhs.month, rhs.day);
}

std::istream& operator>>(std::istream & is, Date & date) {
    char delimiter;
    is >> date.year >> delimiter >> date.month >> delimiter >> date.day;
    return is;
}

std::ostream& operator<<(std::ostream & os, const Date & date) {
    return os << date.year << '-' << date.month << '-' << date.day;
}

bool operator<(const Time & lhs, const Time & rhs) {
    return std::tie(lhs.hours, lhs.minutes) < std::tie(rhs.hours, rhs.minutes);
}

bool operator==(const Time & lhs, const Time & rhs) {
    return std::tie(lhs.hours, lhs.minutes) == std::tie(rhs.hours, rhs.minutes);
}

std::istream& operator>>(std::istream & is, Time & time) {
    char delimiter;
    is >> time.hours >> delimiter >> time.minutes;
    return is;
}

std::ostream& operator<<(std::ostream & os, const Time & time) {
    return os << time.hours << ':' << time.minutes;
}

void TestUpdate() {
    AirlineTicket t;
    t.price = 0;

    const map<string, string> updates1 = {
      {"departure_date", "2022-2-28"},
      {"departure_time", "17:40"},
    };
    UPDATE_FIELD(t, departure_date, updates1);
    UPDATE_FIELD(t, departure_time, updates1);
    UPDATE_FIELD(t, price, updates1);

    ASSERT_EQUAL(t.departure_date, (Date{ 2022, 2, 28 }));
    ASSERT_EQUAL(t.departure_time, (Time{ 17, 40 }));
    ASSERT_EQUAL(t.price, 0);

    const map<string, string> updates2 = {
      {"price", "12550"},
      {"arrival_time", "20:33"},
    };
    UPDATE_FIELD(t, departure_date, updates2);
    UPDATE_FIELD(t, departure_time, updates2);
    UPDATE_FIELD(t, arrival_time, updates2);
    UPDATE_FIELD(t, price, updates2);

    // updates2 �� ������ ����� "departure_date" � "departure_time", ����
    // �������� ��� ���� �� ������� ��������
    ASSERT_EQUAL(t.departure_date, (Date{ 2022, 2, 28 }));
    ASSERT_EQUAL(t.departure_time, (Time{ 17, 40 }));
    ASSERT_EQUAL(t.price, 12550);
    ASSERT_EQUAL(t.arrival_time, (Time{ 20, 33 }));
}
int main() {
    TestRunner tr;
    RUN_TEST(tr, TestUpdate);
};