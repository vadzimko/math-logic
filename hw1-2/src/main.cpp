#include <utility>

#include <iostream>
#include <fstream>
#include <vector>
#include <set>
#include <map>
#include <unordered_map>
#include <stdio.h>

using namespace std;

ifstream fin("output.txt");
ofstream fout("ans.txt");

const string ax1 = "(->,A,(->,B,A))";
const string ax2 = "(->,(->,A,B),(->,(->,A,(->,B,C)),(->,A,C)))";
const string ax3 = "(->,A,(->,B,(&,A,B)))";
const string ax4 = "(->,(&,A,B),A)";
const string ax5 = "(->,(&,A,B),B)";
const string ax6 = "(->,A,(|,A,B))";
const string ax7 = "(->,B,(|,A,B))";
const string ax8 = "(->,(->,A,C),(->,(->,B,C),(->,(|,A,B),C)))";
const string ax9 = "(->,(->,A,B),(->,(->,A,(!B)),(!A)))";
const string ax10 = "(->,(!(!A)),A)";

const string AND = "&";
const string NOT = "!";
const string OR = "|";
const string IMPL = "->";

bool isSign(const string &value) {
    return value == AND || value == OR || value == NOT || value == IMPL;
}

bool isUnary(const string &sign) {
    return sign == NOT;
}

bool isLetter(char c) {
    return c >= 'A' && c <= 'Z';
}

string parseVar(string str, int &pos) {
    int begin = pos;
    while ((str[pos] >= 'A' && str[pos] <= 'Z') || (str[pos] >= '0' && str[pos] <= '9') || str[pos] == '\'') {
        pos++;
    }

    return str.substr(begin, pos - begin);
}

struct Solution {
    string type;
    int line;

    Solution *from_1;
    Solution *from_2;

    Solution(string str, int exp, Solution *fr1 = nullptr, Solution *fr2 = nullptr) {
        type = std::move(str);
        line = exp;
        from_1 = fr1;
        from_2 = fr2;
    }
};

struct expr {
    expr *left;
    expr *right;
    Solution *solution = nullptr;

    string value;
    bool is_axi = false;
    size_t just_hash = 0;

    void init_hash() {
        just_hash = std::hash<std::string>()(to_string());
    }

    expr(string const &str, int &pos, bool is_axi = false) {
        this->is_axi = is_axi;

        if (isLetter(str[pos])) {
            value = parseVar(str, pos);
            left = nullptr;
            right = nullptr;
            init_hash();
            return;
        }

        pos++;
        while (str[pos] == '(' || str[pos] == ')' || str[pos] == ',') {
            pos++;
        }
        int begin = pos;

        if (isLetter(str[pos])) {
            value = parseVar(str, pos);
            left = nullptr;
            right = nullptr;
            init_hash();
            return;
        }

        if (str[pos] == '!') {
            value = NOT;
            left = new expr(str, pos);
            right = nullptr;
        } else {
            while (pos < str.length() && str[pos] != ',') {
                pos++;
            }

            value = str.substr(begin, pos - begin);
            left = new expr(str, pos);
            right = new expr(str, pos);
        }
        init_hash();
    }

    string create_view() const {
        if (isSign(value)) {
            if (isUnary(value)) {
                return value + left->create_view();
            } else {
                return "(" + left->create_view() + " " + value + " " + right->create_view() + ")";
            }
        } else {
            return value;
        }
    }

    string to_string() const {
        return create_view();
    }

    bool equals(const expr &other) const {
        if (is_axi || other.is_axi) {
            map<string, string> ma;
            return comp(this, &other, ma);
        } else {
            return to_string() == other.to_string();
        }
    }

    bool operator==(const expr &other) const {
        return equals(other);
    }

    size_t hash() const {
        return just_hash;
    }

    bool isImpl() {
        return value == IMPL;
    }

    bool static comp(const expr *lhs, const expr *other, map<string, string> &ma) {
        if (isSign(other->value) && !isSign(lhs->value)) {
            if (!ma.count(lhs->value)) {
                ma[lhs->value] = other->to_string();
                return true;
            } else {
                return ma[lhs->value] == other->to_string();
            }
        }

        if ((lhs->left == nullptr && other->left != nullptr)
            || (lhs->right == nullptr && other->right != nullptr)
            || (lhs->left != nullptr && other->left == nullptr)
            || (lhs->right != nullptr && other->right == nullptr)) {

            return false;
        }

        if ((isSign(lhs->value) || isSign(other->value))) {
            if (lhs->value != other->value) {
                return false;
            } else {
                return ((lhs->left == nullptr && other->left == nullptr) || comp(lhs->left, other->left, ma))
                       &&
                       ((lhs->right == nullptr && other->right == nullptr) || comp(lhs->right, other->right, ma));
            }
        }

        if (!ma.count(lhs->value)) {
            ma[lhs->value] = other->value;
            return true;
        } else {
            return ma[lhs->value] == other->value;
        }
    }
};

struct Hash {
    size_t operator()(const expr &k) const {
        return k.hash();
    }
};

unordered_map<expr, int, Hash> hypo_map;
unordered_map<expr, int, Hash> left_map;
unordered_map<expr, vector<pair<expr *, expr *>>, Hash> modus_map;
unordered_map<int, pair<int, int>> modus_map_fake;
unordered_map<int, Solution const *> solve_map;
vector<expr> axi_map;
vector<expr> lines;
string first_line;
string fact;

void init_axis() {
    int pos = 0;
    axi_map.push_back(expr(ax1, pos, true));
    pos = 0;
    axi_map.push_back(expr(ax2, pos, true));
    pos = 0;
    axi_map.push_back(expr(ax3, pos, true));
    pos = 0;
    axi_map.push_back(expr(ax4, pos, true));
    pos = 0;
    axi_map.push_back(expr(ax5, pos, true));
    pos = 0;
    axi_map.push_back(expr(ax6, pos, true));
    pos = 0;
    axi_map.push_back(expr(ax7, pos, true));
    pos = 0;
    axi_map.push_back(expr(ax8, pos, true));
    pos = 0;
    axi_map.push_back(expr(ax9, pos, true));
    pos = 0;
    axi_map.push_back(expr(ax10, pos, true));
}

int getAxiNumber(expr const &line) {
    for (int i = 0; i < 10; i++) {
        if (axi_map[i] == line) {
            return i + 1;
        }
    }

    return 0;
}

Solution *find_back(expr & line) {
    int line_number = left_map[line];
    if (line.solution) {
        return line.solution;
    }

    int axi_number = getAxiNumber(line);
    if (axi_number) {
        line.solution = new Solution("axi", line_number);
        return line.solution;
    }

    if (hypo_map.count(line)) {
        line.solution = new Solution("hypo", line_number);
        return line.solution;
    }

    auto &poses = modus_map_fake[line_number];
    line.solution = new Solution("mp", line_number);
    line.solution->from_1 = find_back(lines[poses.first]);
    line.solution->from_2 = find_back(lines[poses.second]);
    return line.solution;
}

void print_solution(Solution const &solution) {
    if (solution.from_1 != nullptr)
        print_solution(*solution.from_1);
    if (solution.from_2 != nullptr)
        print_solution(*solution.from_2);

    solve_map[solution.line] = &solution;
}

int main() {
    init_axis();
    getline(fin, first_line);
    string answer;
    getline(fin, answer);
    getline(fin, fact);
    if (first_line[0] == '|' && fact == answer) {
        getline(fin, fact);
    }
    int pos = 0;
    while (fact.find("---") == std::string::npos) {
        expr e = expr(fact, pos);
        if (!hypo_map.count(e)) {
            hypo_map[e] = hypo_map.size() + 1;
        }
        pos = 0;
        getline(fin, fact);
    }
    fact = first_line.substr(fact.find("|-") + 3);

    string s = " ";
    int key = -1;
    expr ans(answer, pos);
    while (!fin.eof()) {
        getline(fin, s);
        pos = 0;
        if (s.empty()) {
            break;
        }
        lines.emplace_back(s, pos, false);
        if (key == -1 && lines.back() == ans) {
            key = lines.size() - 1;
        }
    }
    fin.close();
//    remove("output.txt");

    if (!(lines.back() == ans)) {
        cout << "Proof is incorrect\n";
        return 0;
    }
    pos = 0;

    int line_number = 1;
    for (auto &line : lines) {
        if (left_map.count(line)) {
            line_number++;
            continue;
            // nothing
        } else if (getAxiNumber(line) || hypo_map.count(line)) {
            left_map[line] = line_number - 1;

            if (line.right != nullptr && line.isImpl()) {
                modus_map[*line.right].push_back({line.left, &line});
            }
        } else if (modus_map.count(line)) {
            auto &list = modus_map[line];
            bool good = false;
            for (auto &par : list) {
                if (left_map.count(*par.first)) {
                    good = true;
                    left_map[line] = line_number - 1;
                    modus_map_fake[line_number - 1] = {left_map[*par.first], left_map[*par.second]};

                    if (line.right != nullptr && line.isImpl()) {
                        modus_map[*line.right].push_back({line.left, &line});
                    }
                    break;
                }
            }

            if (!good) {
                cout << "Proof is incorrect " << line_number << "\n";
                return 0;
            }
        } else {
            cout << "Proof is incorrect " << line_number << "\n";
            return 0;
        }

        line_number++;
    }
    modus_map.clear();

    map<int, string> hypos;
    for (auto &it : hypo_map) {
        hypos[it.second] = it.first.to_string();
    }
    for (int i = 1; i < hypos.size(); i++) {
        cout << hypos[i] << ", ";
    }
    if (!hypos.empty()) {
        cout << hypos[hypos.size()] << " ";
    }
    hypos.clear();

    Solution *sol = find_back(lines[key]);
    cout << "|- " << lines[lines.size() - 1].to_string() << endl;
    print_solution(*sol);

    int num = 1;
    map<int, int> numbers;
    for (int i = 0; i <= lines.size(); i++) {
        numbers[i] = num;
        if (solve_map.count(i)) {
//            Solution const *sol = solve_map[i];
//            cout << "[" << num++ << ". ";
//
//            if (sol->type == "axi") {
//                cout << "Ax. sch. " << to_string(getAxiNumber(lines[sol->line]));
//                cout << "Ax. sch. " << to_string(getAxiNumber(lines[sol->line]));
//            } else if (sol->type == "hypo") {
//                cout << "Hypothesis " + to_string(hypo_map[lines[sol->line]]);
//                cout << "Hypothesis " + to_string(hypo_map[lines[sol->line]]);
//            } else {
//                string temp = to_string(numbers[lines[i].solution->from_2->line]) + ", " +
//                              to_string(numbers[lines[i].solution->from_1->line]);
//                cout << "M.P. " << temp;
//            }
//            cout << "] " <<  lines[i].to_string() << endl;
            fout << lines[i].to_string() << endl;
        }

    }

    ofstream a("answer");
    return 0;
}
