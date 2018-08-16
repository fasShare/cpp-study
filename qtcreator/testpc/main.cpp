#include <iostream>
#include <vector>
#include <utility>
#include <map>

using namespace std;

// 根据d字符串中提供的字符分割字符串
std::vector<std::string> StringSplit(const std::string& str, const std::string& d) {
    std::string::size_type pos = 0;
    std::vector<std::string> ret;
    while (pos < str.size() && pos != std::string::npos) {
        std::string::size_type start = str.find_first_not_of(d, pos);
        if (start == std::string::npos) {
            break;
        }
        pos = start;
        std::string::size_type end = str.find_first_of(d, pos);
        if (end == std::string::npos) {
            end = str.size();
        }
        pos = end;

        ret.push_back(str.substr(start, end - start));
    }

    return ret;
}

int64_t Max(int64_t left, int64_t right) {
    return left >= right ? left : right;
}

void combine(vector<vector<pair<int, int>>>& mp, int start, int end, map<int, int>& result) {
    if (end - start < 1) {
        return;
    }
    if (end - start == 1) {
        for (int i = 0; i < mp[start].size(); ++i) {
            result[mp[start][i].first] = mp[start][i].second;
        }
        return ;
    }

    cout << start << " " << end << endl;

    int mid = (start + end ) / 2;

    map<int, int> left, right;

    combine(mp, start, mid, left);
    combine(mp, mid, end, right);

    for (auto riter = right.begin(); riter != right.end(); ++riter) {
        auto re = left.lower_bound(riter->first);
        if (re == left.end()) {
            continue;
        }

        for (auto ll = re; ll != left.end(); ++ll) {
            if (ll->first <= riter->second) {
                result[riter->first] = Max(riter->second, ll->second);
            }
        }
    }
}

int main()
{
    int M;

    cin >> M;

    string line;

    vector<vector<pair<int, int>>> mp;

    for (int i = 0; i < M; ++i) {
        getline(cin, line);
        auto tmp = StringSplit(line, ";");
        vector<pair<int, int>> vc;
        for (int i = 0; i < tmp.size(); ++i) {
            auto ttmp = StringSplit(tmp[i], ",");
            vc.push_back(std::pair<int, int>(std::atoi(ttmp[0].c_str()), std::atoi(ttmp[1].c_str())));
        }
        mp.push_back(vc);
    }

    map<int, int> result;

    combine(mp, 0, mp.size(), result);

    for (auto iter = result.begin(); iter != result.end(); ) {

        std::cout << iter->first << "," << iter->second;
        if (++iter != result.end()) {
            std::cout << ";";
        }
    }

    std::cout << endl;

   return 0;
}
