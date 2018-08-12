#ifndef MOXIE_TIMESTAMP_H
#define MOXIE_TIMESTAMP_H
#include <string>

namespace moxie {

using std::string;

class Timestamp {
public:
    Timestamp();
    explicit Timestamp(int64_t microSecondsSinceEpoch);
    void swap(Timestamp& that);
    string toString() const;
    string toFormattedString() const;
    static Timestamp invalid();
    bool isvalid() const;
    // for internal usage.
    int64_t get_microSecondsSinceEpoch() const;
    time_t secondsSinceEpoch() const;
    static Timestamp now();
    static const int kMicroSecondsPerSecond = 1000 * 1000;
private:
    int64_t microSecondsSinceEpoch_;
};


bool operator<(Timestamp lhs, Timestamp rhs);
bool operator>(Timestamp lhs, Timestamp rhs);
bool operator==(Timestamp lhs, Timestamp rhs);
double timeDifference(Timestamp high, Timestamp low);
Timestamp addTime(Timestamp timestamp, double seconds);

}
#endif  // MOXIE_TIMESTAMP_H
