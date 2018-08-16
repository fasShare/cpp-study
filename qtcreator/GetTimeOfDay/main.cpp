#include <iostream>
#include <sys/time.h>
#include <string.h>

using namespace std;

int main() {
    struct timeval time;
    struct timezone zone;

    if (gettimeofday(&time, &zone) < 0) {
        cout << "gettimeofday error : " << strerror(errno) << std::endl;
        return -1;
    }

    cout << "second = " << time.tv_sec << " usecond = " << time.tv_usec << endl;
    cout << "tz_minuteswest = " << zone.tz_minuteswest << " tz_dsttime = " << zone.tz_dsttime << endl;

    struct tm *ptr = localtime(&time.tv_sec);
    if (!ptr) {
        cout << "localtime error : " << strerror(errno) << std::endl;
        return -1;
    }

    printf("当前的本地时间和日期：%s", asctime(ptr));
    return 0;
}
