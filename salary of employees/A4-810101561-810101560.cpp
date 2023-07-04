#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <cmath>

using namespace std;

class Data_base;
class Employee;
class Working_hour;
class Team;
class Salary_config;

const string CSV_EMPLOYEES = "assets/employees.csv";
const string CSV_SALARY_CONFIGS = "assets/salary_configs.csv";
const string CSV_TEAMS = "assets/teams.csv";
const string CSV_WORKING_HOURS = "assets/working_hours.csv";
const int FIRST_WORD = 0;
const int SECOND_WORD = 1;
const int THIRD_WORD = 2;
const int FOURTH_WORD = 3;
const int FIFTH_WORD = 4;
const int SIXTH_WORD = 5;
const int JUNK = -1;
const int LEVELS_COUNT = 4;
const double MONTH_DAYS = 30;
const int EMPTY_VECTOR = 0;
const string REPORT_SALARIES = "report_salaries";
const string REPORT_EMPLOYEE_SALARY = "report_employee_salary";
const string REPORT_TEAM_SALARY = "report_team_salary";
const string REPORT_TOTAL_HOURS_PER_DAY = "report_total_hours_per_day";
const string REPORT_EMPLOYEE_PER_HOUR = "report_employee_per_hour";
const string SHOW_SALARY_CONFIG = "show_salary_config";
const string UPDATE_SALARY_CONFIG = "update_salary_config";
const string ADD_WORKING_HOURS = "add_working_hours";
const string DELETE_WROKING_HOURS = "delete_working_hours";
const string UPDATE_TEAM_BONUS = "update_team_bonus";
const string FIND_TEAM_FOR_BONUS = "find_team_for_bonus";
const double FIRST_DAY = 1;
const double LAST_DAY = 30;
const double DAY_LENGTH = 24;
const int DAY_START = 0;
const string ARGUMENT_ERROR = "INVALID_ARGUMENTS";
const string EMPLOYEE_ERROR = "EMPLOYEE_NOT_FOUND";
const string LEVEL_ERROR = "INVALID_LEVEL";
const string TEAM_ERROR = "TEAM_NOT_FOUND";
const string INTERVAL_ERROR = "INVALID_INTERVAL";
const string BONUS_ERROR = "NO_BONUS_TEAMS";
const string COMMAND_ERROR = "invalid command";
const string SUCCESSFUL_OPERATION = "OK";
const int SUCCESS = 1;
const int FAIL = 0;
const string THE_NULL = "\0";
const string THE_EOF = "\04";

class Salary_config
{
public:
    int get_official_working_hours() { return official_working_hours; };
    int get_salary_per_hour() { return salary_per_hour; };
    int get_salary_per_extra_hour() { return salary_per_extra_hour; };
    string get_level_name() { return level; };
    int get_base_salary() { return base_salray; };
    int get_tax_percentage() { return tax_percentage; };
    void set_level(string the_level) { level = the_level; };
    void set_base_salary(int the_base_salary) { base_salray = the_base_salary; };
    void set_salary_per_hour(int the_salary_per_hour) { salary_per_hour = the_salary_per_hour; };
    void set_salary_per_extra_hour(int the_salary_per_extra_hour) { salary_per_extra_hour = the_salary_per_extra_hour; };
    void set_official_working_hours(int the_official_working_hours) { official_working_hours = the_official_working_hours; };
    void set_tax_percentage(int the_tax_percentage) { tax_percentage = the_tax_percentage; };

private:
    string level;
    int base_salray;
    int salary_per_hour;
    int salary_per_extra_hour;
    int official_working_hours;
    int tax_percentage;
};

class Working_hour
{
public:
    int get_start_time() { return start; };
    int get_end_time() { return end; };
    int get_interval_duration() { return end - start; };
    int get_day() { return day; };
    int get_emp_id() { return employee_id; };
    void set_employee_id(int emp_id) { employee_id = emp_id; };
    void set_day(int the_day) { day = the_day; };
    void set_start_time(int start_time) { start = start_time; };
    void set_end_time(int end_time) { end = end_time; };

private:
    int employee_id;
    int day;
    int start;
    int end;
};

class Team
{
public:
    void set_team_id(int id) { team_id = id; };
    void set_team_lead_id(int lead_id) { team_lead_id = lead_id; };
    void set_member_ids(string members);
    void set_bonus_min_working_hours(int bonus_min) { bonus_min_working_hours = bonus_min; };
    void set_bonus_working_hours_max_variance(double bonus_var) { bonus_working_hours_max_variance = bonus_var; };
    void set_bonus(int the_bonus) { bonus = the_bonus; };
    int get_team_id() { return team_id; };
    vector<int> get_member_ids() { return member_ids; };
    double get_bonus_working_hours_max_variance() { return bonus_working_hours_max_variance; };
    int get_lead_id() { return team_lead_id; };
    int get_bonus_min_working_hours() { return bonus_min_working_hours; };
    int get_bonus() { return bonus; };
    int calculate_team_totalWH(vector<Working_hour> whs);
    double calculate_team_average_totalWH(vector<Working_hour> whs);
    double calculate_variance_of_team_working_hours(vector<Working_hour> whs);
    bool is_team_capable_for_bonus(vector<Working_hour> whs);

private:
    int team_id;
    int team_lead_id;
    vector<int> member_ids;
    int bonus_min_working_hours;
    double bonus_working_hours_max_variance;
    int bonus = 0;
};

class Employee
{
public:
    int get_emp_id() { return id; };
    string get_emp_name() { return name; };
    string get_emp_level() { return level; };
    int get_emp_age() { return age; };
    Salary_config *get_salary_config() { return employee_salary_config; };
    Team *get_emp_team() { return employee_team; };
    int get_team_id() { return employee_team->get_team_id(); };
    void set_emp_id(int the_emp_id) { id = the_emp_id; };
    void set_emp_name(string the_name) { name = the_name; };
    void set_emp_age(int the_age) { age = the_age; };
    void set_emp_level(string the_level) { level = the_level; };
    void set_salary_config(Data_base *all_information);
    void set_team(Data_base *all_information);
    int calculate_salary(int total_working_hour);
    int calculate_tax_amount(int total_working_hour);
    int calculate_bonus_amount(int total_working_hour);
    int calculate_total_earning(int total_working_hour);

private:
    int id;
    string name;
    int age;
    string level;
    Team *employee_team = new Team;
    Salary_config *employee_salary_config = new Salary_config;
};

class Data_base
{
public:
    Data_base(int a = JUNK);
    void add_working_hour(Working_hour new_working_hour) { all_working_hours.push_back(new_working_hour); };
    void read_csv_teams();
    void read_csv_employees();
    void read_csv_salary_configs();
    void read_csv_working_hours();
    vector<Team> get_the_teams() { return all_teams; };
    vector<Working_hour> get_the_working_hours() { return all_working_hours; };
    vector<Salary_config> get_the_salary_configs() { return all_salary_configs; };
    vector<Employee> get_the_employees() { return all_employees; };
    vector<Salary_config *> get_the_salary_configs_pointers();
    vector<Team *> get_the_teams_pointers();
    vector<Working_hour *> get_the_working_hours_pointers();
    vector<Employee *> get_the_employees_pointers();

private:
    vector<Employee> all_employees;
    vector<Team> all_teams;
    vector<Salary_config> all_salary_configs;
    vector<Working_hour> all_working_hours;
};

Data_base::Data_base(int a)
{
    this->read_csv_teams();
    this->read_csv_working_hours();
    this->read_csv_salary_configs();
    this->read_csv_employees();
}

vector<Salary_config *> Data_base::get_the_salary_configs_pointers()
{
    vector<Salary_config *> pointers;
    for (int i = 0; i < LEVELS_COUNT; i++)
        pointers.push_back(&(all_salary_configs[i]));
    return pointers;
};

vector<Team *> Data_base::get_the_teams_pointers()
{
    vector<Team *> pointers;
    for (int i = 0; i < all_teams.size(); i++)
        pointers.push_back(&(all_teams[i]));
    return pointers;
}

vector<Employee *> Data_base::get_the_employees_pointers()
{
    vector<Employee *> pointers;
    for (int i = 0; i < all_employees.size(); i++)
        pointers.push_back(&(all_employees[i]));
    return pointers;
}

vector<Working_hour *> Data_base::get_the_working_hours_pointers()
{
    vector<Working_hour *> pointers;
    for (int i = 0; i < all_working_hours.size(); i++)
        pointers.push_back(&(all_working_hours[i]));
    return pointers;
}

Employee *find_employee_by_id(vector<Employee *> employees, int id)
{
    for (Employee *e : employees)
        if (e->get_emp_id() == id)
            return e;
    return NULL;
}
Team *find_team_by_id(vector<Team *> teams, int id)
{
    for (Team *t : teams)
        if (t->get_team_id() == id)
            return t;
    return NULL;
}
Salary_config *find_salaryconfig_by_level(vector<Salary_config *> salary_configs, string level)
{
    for (Salary_config *s : salary_configs)
        if (s->get_level_name() == level)
            return s;
    return NULL;
}
vector<int> find_workinghours_by_employee_id_and_day(vector<Working_hour> whs, int employee_id, int day)
{
    vector<int> v;
    for (int i = 0; i < whs.size(); i++)
        if ((whs[i].get_emp_id() == employee_id) && (whs[i].get_day() == day))
            v.push_back(i);
    return v;
}
int calculate_sum_of_WH_per_employee(vector<Working_hour> whs, int employee_id)
{
    int sum = 0;
    for (Working_hour wh : whs)
        if (wh.get_emp_id() == employee_id)
            sum += wh.get_interval_duration();
    return sum;
}
int calculate_sum_of_WH_per_day(vector<Working_hour> whs, int day)
{
    int sum = 0;
    for (Working_hour wh : whs)
        if (wh.get_day() == day)
            sum += wh.get_interval_duration();
    return sum;
}
int calculate_sum_of_emp_per_hour(vector<Working_hour> whs, int start_of_period)
{
    int sum = 0;
    for (Working_hour wh : whs)
        if ((wh.get_start_time() <= start_of_period) && (wh.get_end_time() >= start_of_period + 1))
            sum++;
    return sum;
}
int calculate_absent_days_per_employee(vector<Working_hour> whs, int employee_id)
{
    int present_days = 0;
    for (int d = 1; d <= MONTH_DAYS; d++)
        if (find_workinghours_by_employee_id_and_day(whs, employee_id, d).size() > 0)
            present_days++;
    return MONTH_DAYS - present_days;
}
double find_max_value(vector<double> v)
{
    double result = v[0];
    for (auto i : v)
        if (i > result)
            result = i;
    return result;
}
double find_min_value(vector<double> v)
{
    double result = v[0];
    for (auto i : v)
        if (i < result)
            result = i;
    return result;
}
vector<int> find_indexes_of_value(vector<double> v, double value)
{
    vector<int> result;
    for (int i = 0; i < v.size(); i++)
        if (v[i] == value)
            result.push_back(i);
    return result;
}
double take_avg_with_one_place(int ec)
{
    return round((ec / MONTH_DAYS) * 10.0) / 10.0;
}
bool compare_team(pair<int, int> a, pair<int, int> b)
{
    return a.second > b.second;
}
void print_bonus_team(vector<pair<int, int>> capable_teams)
{
    for (auto t : capable_teams)
        cout << "Team ID: " << t.first << endl;
}

void Employee::set_team(Data_base *all_information)
{
    vector<Team *> all_teams_pointers = all_information->get_the_teams_pointers();
    for (int i = 0; i < all_teams_pointers.size(); i++)
    {
        vector<int> all_members = all_teams_pointers[i]->get_member_ids();
        for (int j = 0; j < all_members.size(); j++)
            if (all_members[j] == id)
            {
                employee_team = all_teams_pointers[i];
                return;
            }
    }
    employee_team->set_team_id(JUNK);
}
void Employee::set_salary_config(Data_base *all_information)
{
    string level_name = this->level;
    vector<Salary_config *> all_salary_configs = all_information->get_the_salary_configs_pointers();
    for (int i = 0; i < LEVELS_COUNT; i++)
    {
        string config_level_name = all_salary_configs[i]->get_level_name();

        if (config_level_name == level_name)
        {
            employee_salary_config = all_salary_configs[i];
        }
    }
}
int Employee::calculate_salary(int total_working_hour)
{
    int salary;
    int base_salary = employee_salary_config->get_base_salary();
    int official_working_hours = employee_salary_config->get_official_working_hours();
    int salary_per_hour = employee_salary_config->get_salary_per_hour();
    int salary_per_extra_hour = employee_salary_config->get_salary_per_extra_hour();
    if (total_working_hour > official_working_hours)
        return official_working_hours * salary_per_hour +
               (total_working_hour - official_working_hours) * salary_per_extra_hour + base_salary;
    else
        return total_working_hour * salary_per_hour + base_salary;
};
int Employee::calculate_bonus_amount(int total_working_hour)
{
    return round(this->calculate_salary(total_working_hour) * this->employee_team->get_bonus() / 100.0);
};
int Employee::calculate_tax_amount(int total_working_hour)
{
    return round((this->calculate_salary(total_working_hour) + this->calculate_bonus_amount(total_working_hour)) *
                 this->employee_salary_config->get_tax_percentage() / 100.0);
};
int Employee::calculate_total_earning(int total_working_hour)
{
    return this->calculate_salary(total_working_hour) -
           this->calculate_tax_amount(total_working_hour) + calculate_bonus_amount(total_working_hour);
};
void Team::set_member_ids(string members)
{
    vector<int> ids;
    string word;
    stringstream members_stream(members);
    while (getline(members_stream, word, '$'))
    {
        ids.push_back(stoi(word));
    }
    sort(ids.begin(), ids.end());
    member_ids = ids;
};
int Team::calculate_team_totalWH(vector<Working_hour> whs)
{
    int sum = 0;
    for (int id : member_ids)
        sum += calculate_sum_of_WH_per_employee(whs, id);
    return sum;
}
double Team::calculate_team_average_totalWH(vector<Working_hour> whs)
{
    return static_cast<double>(this->calculate_team_totalWH(whs)) / member_ids.size();
}
double Team::calculate_variance_of_team_working_hours(vector<Working_hour> whs)
{
    double avg = this->calculate_team_average_totalWH(whs);
    double s;
    for (int id : member_ids)
        s += (calculate_sum_of_WH_per_employee(whs, id) - avg) * (calculate_sum_of_WH_per_employee(whs, id) - avg);
    return s / member_ids.size();
}
bool Team::is_team_capable_for_bonus(vector<Working_hour> whs)
{
    if (this->calculate_team_totalWH(whs) > bonus_min_working_hours &&
        this->calculate_variance_of_team_working_hours(whs) < bonus_working_hours_max_variance)
        return true;
    return false;
}

vector<string> init_all_words(string line)
{
    stringstream working_hour_stream(line);
    string word;
    vector<string> all_words;
    while (getline(working_hour_stream, word, ','))
        all_words.push_back(word);
    return all_words;
}
Team set_team_id(Team new_team, vector<string> all_words)
{
    int id = stoi(all_words[FIRST_WORD]);
    new_team.set_team_id(id);
    return new_team;
}
Team set_lead_id(Team new_team, vector<string> all_words)
{

    int lead_id = stoi(all_words[SECOND_WORD]);
    new_team.set_team_lead_id(lead_id);
    return new_team;
}
Team set_member_ids(Team new_team, vector<string> all_words)
{

    string memebr_ids = all_words[THIRD_WORD];
    new_team.set_member_ids(memebr_ids);
    return new_team;
}
Team set_bonus_min(Team new_team, vector<string> all_words)
{

    int bonus_min = stoi(all_words[FOURTH_WORD]);
    new_team.set_bonus_min_working_hours(bonus_min);
    return new_team;
}
Team set_bonus_var(Team new_team, vector<string> all_words)
{

    double bonus_var;
    istringstream fifth_word_stream(all_words[FIFTH_WORD]);
    fifth_word_stream >> bonus_var;
    new_team.set_bonus_working_hours_max_variance(bonus_var);
    return new_team;
}

bool compare_teams_by_id(Team first, Team second)
{
    return first.get_team_id() < second.get_team_id();
}

void Data_base::read_csv_teams()
{
    ifstream csv_teams(CSV_TEAMS);
    string line;
    getline(csv_teams, line);
    while (getline(csv_teams, line))
    {
        Team new_team;
        vector<string> all_words;
        all_words = init_all_words(line);

        new_team = set_team_id(new_team, all_words);
        new_team = set_lead_id(new_team, all_words);
        new_team = set_member_ids(new_team, all_words);
        new_team = set_bonus_min(new_team, all_words);
        new_team = set_bonus_var(new_team, all_words);

        all_teams.push_back(new_team);
    }
    sort(all_teams.begin(), all_teams.end(), compare_teams_by_id);
}

Working_hour set_emp_id(Working_hour new_working_hour, vector<string> all_words)
{
    int emp_id = stoi(all_words[FIRST_WORD]);
    new_working_hour.set_employee_id(emp_id);
    return new_working_hour;
}
Working_hour set_day(Working_hour new_working_hour, vector<string> all_words)
{
    int the_day = stoi(all_words[SECOND_WORD]);
    new_working_hour.set_day(the_day);
    return new_working_hour;
}
Working_hour set_interval_start_time(Working_hour new_working_hour, vector<string> all_words)
{
    int start_time = stoi(all_words[THIRD_WORD].substr(0, all_words[THIRD_WORD].find('-')));
    new_working_hour.set_start_time(start_time);
    return new_working_hour;
}
Working_hour set_interval_end_time(Working_hour new_working_hour, vector<string> all_words)
{
    int end_time = stoi(all_words[THIRD_WORD].substr(all_words[THIRD_WORD].find('-') + 1));
    new_working_hour.set_end_time(end_time);
    return new_working_hour;
}

void Data_base::read_csv_working_hours()
{
    ifstream csv_working_hours(CSV_WORKING_HOURS);
    string line;
    getline(csv_working_hours, line);
    while (getline(csv_working_hours, line))
    {
        Working_hour new_working_hour;
        vector<string> all_words;
        all_words = init_all_words(line);

        new_working_hour = set_emp_id(new_working_hour, all_words);
        new_working_hour = set_day(new_working_hour, all_words);
        new_working_hour = set_interval_start_time(new_working_hour, all_words);
        new_working_hour = set_interval_end_time(new_working_hour, all_words);

        all_working_hours.push_back(new_working_hour);
    }
}

Salary_config set_level(Salary_config new_salary_config, vector<string> all_words)
{
    string level = all_words[FIRST_WORD];
    new_salary_config.set_level(level);
    return new_salary_config;
}
Salary_config set_base_salary(Salary_config new_salary_config, vector<string> all_words)
{
    int base_salary = stoi(all_words[SECOND_WORD]);
    new_salary_config.set_base_salary(base_salary);
    return new_salary_config;
}
Salary_config set_salary_per_hour(Salary_config new_salary_config, vector<string> all_words)
{
    int salary_per_hour = stoi(all_words[THIRD_WORD]);
    new_salary_config.set_salary_per_hour(salary_per_hour);
    return new_salary_config;
}
Salary_config set_salary_per_extra_hour(Salary_config new_salary_config, vector<string> all_words)
{
    int salary_per_extra_hour = stoi(all_words[FOURTH_WORD]);
    new_salary_config.set_salary_per_extra_hour(salary_per_extra_hour);
    return new_salary_config;
}
Salary_config set_official_working_hours(Salary_config new_salary_config, vector<string> all_words)
{
    int official_working_hours = stoi(all_words[FIFTH_WORD]);
    new_salary_config.set_official_working_hours(official_working_hours);
    return new_salary_config;
}
Salary_config set_tax_percentage(Salary_config new_salary_config, vector<string> all_words)
{
    int tax_percentage = stoi(all_words[SIXTH_WORD]);
    new_salary_config.set_tax_percentage(tax_percentage);
    return new_salary_config;
}

void Data_base::read_csv_salary_configs()
{
    ifstream csv_salary_configs(CSV_SALARY_CONFIGS);
    string line;
    getline(csv_salary_configs, line);
    while (getline(csv_salary_configs, line))
    {
        Salary_config new_salary_config;
        vector<string> all_words;
        all_words = init_all_words(line);

        new_salary_config = set_level(new_salary_config, all_words);
        new_salary_config = set_base_salary(new_salary_config, all_words);
        new_salary_config = set_salary_per_hour(new_salary_config, all_words);
        new_salary_config = set_salary_per_extra_hour(new_salary_config, all_words);
        new_salary_config = set_official_working_hours(new_salary_config, all_words);
        new_salary_config = set_tax_percentage(new_salary_config, all_words);

        all_salary_configs.push_back(new_salary_config);
    }
}

Employee set_emp_id(Employee new_employee, vector<string> all_words)
{
    int id = stoi(all_words[FIRST_WORD]);
    new_employee.set_emp_id(id);
    return new_employee;
}
Employee set_emp_name(Employee new_employee, vector<string> all_words)
{
    string name = all_words[SECOND_WORD];
    new_employee.set_emp_name(name);
    return new_employee;
}
Employee set_emp_age(Employee new_employee, vector<string> all_words)
{
    int age = stoi(all_words[THIRD_WORD]);
    new_employee.set_emp_age(age);
    return new_employee;
}
Employee set_emp_level(Employee new_employee, vector<string> all_words)
{
    string level = all_words[FOURTH_WORD];
    new_employee.set_emp_level(level);
    return new_employee;
}

bool compare_ids(Employee first, Employee second)
{
    return first.get_emp_id() < second.get_emp_id();
}

void Data_base::read_csv_employees()
{
    ifstream csv_employees(CSV_EMPLOYEES);
    string line;
    getline(csv_employees, line);
    while (getline(csv_employees, line))
    {
        Employee new_employee;
        vector<string> all_words;
        all_words = init_all_words(line);

        new_employee = set_emp_id(new_employee, all_words);
        new_employee = set_emp_name(new_employee, all_words);
        new_employee = set_emp_age(new_employee, all_words);
        new_employee = set_emp_level(new_employee, all_words);
        new_employee.set_salary_config(this);
        new_employee.set_team(this);

        all_employees.push_back(new_employee);
    }
    sort(all_employees.begin(), all_employees.end(), compare_ids);
}

void report_salaries(Data_base *db)
{
    for (Employee e : db->get_the_employees())
    {
        int total_WH = calculate_sum_of_WH_per_employee(db->get_the_working_hours(), e.get_emp_id());
        cout << "ID: " << e.get_emp_id() << endl
             << "Name: " << e.get_emp_name() << endl
             << "Total Working Hours: " << total_WH << endl
             << "Total Earning: " << e.calculate_total_earning(total_WH) << endl
             << "---" << endl;
    }
}
int report_employee_salary(Data_base *db, int id)
{
    vector<Working_hour> whs = db->get_the_working_hours();
    int total_WH = calculate_sum_of_WH_per_employee(whs, id);
    Employee *the_employee = find_employee_by_id(db->get_the_employees_pointers(), id);
    if (the_employee)
    {
        cout << "ID: " << the_employee->get_emp_id() << endl
             << "Name: " << the_employee->get_emp_name() << endl
             << "Age: " << the_employee->get_emp_age() << endl
             << "Level: " << the_employee->get_emp_level() << endl;
        if (the_employee->get_team_id() == JUNK)
            cout << "Team ID: "
                 << "N/A" << endl;
        else
            cout << "Team ID: " << the_employee->get_team_id() << endl;
        cout << "Total Working Hours: " << calculate_sum_of_WH_per_employee(whs, id) << endl
             << "Absent Days: " << calculate_absent_days_per_employee(whs, id) << endl
             << "Salary: " << the_employee->calculate_salary(total_WH) << endl
             << "Bonus: " << the_employee->calculate_bonus_amount(total_WH) << endl
             << "Tax: " << the_employee->calculate_tax_amount(total_WH) << endl
             << "Total Earning: " << the_employee->calculate_total_earning(total_WH) << endl;
        return SUCCESS;
    }
    else
        return FAIL;
}
int report_team_salary(Data_base *db, int id)
{
    Team *t = find_team_by_id(db->get_the_teams_pointers(), id);
    if (t)
    {
        vector<Working_hour> whs = db->get_the_working_hours();
        cout << "ID: " << t->get_team_id() << endl
             << "Head ID: " << t->get_lead_id() << endl
             << "Head Name: " << find_employee_by_id(db->get_the_employees_pointers(), t->get_lead_id())->get_emp_name() << endl
             << "Team Total Working Hours: " << t->calculate_team_totalWH(whs) << endl
             << "Average Member Working Hours: " << fixed << setprecision(1) << t->calculate_team_average_totalWH(whs) << endl
             << "Bonus: " << t->get_bonus() << endl
             << "---" << endl;
        for (int id : t->get_member_ids())
            cout << "Member ID: " << id << endl
                 << "Total Earning: "
                 << find_employee_by_id(db->get_the_employees_pointers(), id)->calculate_total_earning(calculate_sum_of_WH_per_employee(whs, id)) << endl
                 << "---" << endl;
        return SUCCESS;
    }
    else
        return FAIL;
}
void report_total_hours_per_day(Data_base *db, int start, int end)
{
    vector<Working_hour> whs = db->get_the_working_hours();
    vector<double> wh_amounts;
    for (int day = start; day <= end; day++)
    {
        int wh = calculate_sum_of_WH_per_day(whs, day);
        cout << "Day #" << day << ": " << wh << endl;
        wh_amounts.push_back(wh);
    }
    cout << "---" << endl;
    vector<int> maxs = find_indexes_of_value(wh_amounts, find_max_value(wh_amounts));
    vector<int> mins = find_indexes_of_value(wh_amounts, find_min_value(wh_amounts));
    cout << "Day(s) with Max Working Hours:";
    for (int i : maxs)
        cout << " " << i + start;
    cout << endl
         << "Day(s) with Min Working Hours:";
    for (int i : mins)
        cout << " " << i + start;
    cout << endl;
}
void report_employee_per_hour(Data_base *db, int start, int end)
{
    vector<Working_hour> whs = db->get_the_working_hours();
    vector<double> emp_avg_counts;
    for (int start_of_period = start; start_of_period < end; start_of_period++)
    {
        int ec = calculate_sum_of_emp_per_hour(whs, start_of_period);
        double avg = take_avg_with_one_place(ec);
        cout << start_of_period << "-" << start_of_period + 1 << ": " << avg << endl;
        emp_avg_counts.push_back(avg);
    }
    cout << "---" << endl;
    vector<int> maxs = find_indexes_of_value(emp_avg_counts, find_max_value(emp_avg_counts));
    vector<int> mins = find_indexes_of_value(emp_avg_counts, find_min_value(emp_avg_counts));
    cout << "Period(s) with Max Working Employees: ";
    for (int i : maxs)
        cout << i + start << "-" << i + 1 + start << " ";
    cout << endl
         << "Period(s) with Min Working Employees: ";
    for (int i : mins)
        cout << i + start << "-" << i + 1 + start << " ";
    cout << endl;
}
int show_salary_config(Data_base *db, string level)
{
    Salary_config *sc = find_salaryconfig_by_level(db->get_the_salary_configs_pointers(), level);
    if (sc)
    {
        cout << "Base Salary: " << sc->get_base_salary() << endl
             << "Salary Per Hour: " << sc->get_salary_per_hour() << endl
             << "Salary Per Extra Hour: " << sc->get_salary_per_extra_hour() << endl
             << "Official Working Hours: " << sc->get_official_working_hours() << endl
             << "Tax: " << sc->get_tax_percentage() << "%" << endl;
        return SUCCESS;
    }
    else
        return FAIL;
}
void update_salary_config(Salary_config *desired_salary_config)
{
    string base_salray;
    string salary_per_hour;
    string salary_per_extra_hour;
    string official_working_hours;
    string tax_percentage;
    cin >> base_salray >> salary_per_hour >> salary_per_extra_hour >> official_working_hours >> tax_percentage;
    if (base_salray != "-")
        desired_salary_config->set_base_salary(stoi(base_salray));
    if (salary_per_hour != "-")
        desired_salary_config->set_salary_per_hour(stoi(salary_per_hour));
    if (salary_per_extra_hour != "-")
        desired_salary_config->set_salary_per_extra_hour(stoi(salary_per_extra_hour));
    if (official_working_hours != "-")
        desired_salary_config->set_official_working_hours(stoi(official_working_hours));
    if (tax_percentage != "-")
        desired_salary_config->set_tax_percentage(stoi(tax_percentage));
}
int delete_working_hour(Data_base *all_information, int employee_id, int day)
{
    vector<Working_hour *> all_working_hours = all_information->get_the_working_hours_pointers();
    vector<int> periods_to_delete =
        find_workinghours_by_employee_id_and_day(all_information->get_the_working_hours(), employee_id, day);
    if (periods_to_delete.size() == EMPTY_VECTOR)
        return FAIL;
    for (int i = 0; i < periods_to_delete.size(); i++)
    {
        all_working_hours[periods_to_delete[i]]->set_day(JUNK);
        all_working_hours[periods_to_delete[i]]->set_employee_id(JUNK);
        all_working_hours[periods_to_delete[i]]->set_start_time(JUNK);
        all_working_hours[periods_to_delete[i]]->set_end_time(JUNK);
    }
    return SUCCESS;
}
void add_working_hour_to_data_base(Data_base *db, int day, int start, int end, int employee_id)
{
    Working_hour new_working_hour;
    new_working_hour.set_day(day);
    new_working_hour.set_employee_id(employee_id);
    new_working_hour.set_start_time(start);
    new_working_hour.set_end_time(end);
    db->add_working_hour(new_working_hour);
}
vector<pair<int, int>> find_team_for_bonus(Data_base *db)
{
    vector<Working_hour> whs = db->get_the_working_hours();
    vector<pair<int, int>> capable_teams;
    for (Team *t : db->get_the_teams_pointers())
        if (t->is_team_capable_for_bonus(whs))
        {
            pair<int, int> p;
            p.first = t->get_team_id();
            p.second = t->calculate_team_totalWH(whs);
            capable_teams.push_back(p);
        }
    sort(capable_teams.begin(), capable_teams.end(), compare_team);
    return capable_teams;
}

bool validate_arg_of_report_TH_per_day(int start, int end)
{
    if (start > end || start > LAST_DAY || end > LAST_DAY || start < FIRST_DAY || end < FIRST_DAY)
        return false;
    return true;
}
bool validate_arg_of_report_employee_per_hour(int start, int end)
{
    if (start >= end || start > DAY_LENGTH || end > DAY_LENGTH || start < 0 || end < 0)
        return false;
    return true;
}
bool validate_level_of_salary_config(vector<Salary_config> all_salary_configs, string level)
{
    for (auto x : all_salary_configs)
        if (x.get_level_name() == level)
            return true;
    return false;
}
bool validate_arg_of_add_working_hours(int day, int start, int end)
{
    if (day > LAST_DAY || day < FIRST_DAY || start > end || start > DAY_LENGTH || end > DAY_LENGTH || start < 0 || end < 0)
        return false;
    return true;
}
bool validate_time_interval_of_add_working_hours(Data_base *db, int emp_id, int day, int start, int end)
{
    vector<Working_hour> whs = db->get_the_working_hours();
    vector<int> v = find_workinghours_by_employee_id_and_day(whs, emp_id, day);
    bool has_time_interval_conflict = false;
    if (v.size() != EMPTY_VECTOR)
        for (int i : v)
            if ((start <= whs[i].get_start_time() && whs[i].get_start_time() < end) ||
                (start < whs[i].get_end_time() && whs[i].get_end_time() <= end) ||
                (whs[i].get_start_time() <= start && start < whs[i].get_end_time()))
                has_time_interval_conflict = true;
    return has_time_interval_conflict;
}
bool validate_employee_id(Data_base *db, int employee_id)
{
    vector<Employee *> all_employees = db->get_the_employees_pointers();
    for (auto x : all_employees)
        if (x->get_emp_id() == employee_id)
            return true;
    return false;
}
bool validate_arg_of_delete_working_hours(int day)
{
    if (day > LAST_DAY || day < FIRST_DAY)
        return false;
    return true;
}
bool validate_arg_of_update_team_bouns(int bonus)
{
    if (bonus > 100 || bonus < 0)
        return false;
    return true;
}

bool execute_command(Data_base *all_information)
{
    string command;
    cin >> command;
    if (command == REPORT_SALARIES)
        report_salaries(all_information);
    else if (command == REPORT_EMPLOYEE_SALARY)
    {
        int id;
        cin >> id;
        if (!report_employee_salary(all_information, id))
            cout << EMPLOYEE_ERROR << endl;
    }
    else if (command == REPORT_TEAM_SALARY)
    {
        int id;
        cin >> id;
        if (!report_team_salary(all_information, id))
            cout << TEAM_ERROR << endl;
    }
    else if (command == REPORT_TOTAL_HOURS_PER_DAY)
    {
        int start, end;
        cin >> start >> end;
        if (!validate_arg_of_report_TH_per_day(start, end))
            cout << ARGUMENT_ERROR << endl;
        else
            report_total_hours_per_day(all_information, start, end);
    }
    else if (command == REPORT_EMPLOYEE_PER_HOUR)
    {
        int start, end;
        cin >> start >> end;
        if (!validate_arg_of_report_employee_per_hour(start, end))
            cout << ARGUMENT_ERROR << endl;
        else
            report_employee_per_hour(all_information, start, end);
    }
    else if (command == SHOW_SALARY_CONFIG)
    {
        string level;
        cin >> level;
        if (!show_salary_config(all_information, level))
            cout << LEVEL_ERROR << endl;
    }
    else if (command == UPDATE_SALARY_CONFIG)
    {
        string level;
        cin >> level;
        Salary_config *desired_salary_config =
            find_salaryconfig_by_level(all_information->get_the_salary_configs_pointers(), level);
        if (desired_salary_config)
        {
            update_salary_config(desired_salary_config);
            cout << SUCCESSFUL_OPERATION << endl;
        }
        else
        {
            string junk;
            getline(cin, junk);
            cout << LEVEL_ERROR << endl;
        }
    }
    else if (command == ADD_WORKING_HOURS)
    {
        string junk;
        int employee_id, day, start, end;
        cin >> employee_id >> day >> start >> end;
        if (!validate_arg_of_add_working_hours(day, start, end))
            cout << ARGUMENT_ERROR << endl;
        else if (!validate_employee_id(all_information, employee_id))
            cout << EMPLOYEE_ERROR << endl;
        else if (validate_time_interval_of_add_working_hours(all_information, employee_id, day, start, end))
            cout << INTERVAL_ERROR << endl;
        else
        {
            add_working_hour_to_data_base(all_information, day, start, end, employee_id);
            cout << SUCCESSFUL_OPERATION << endl;
        }
    }
    else if (command == DELETE_WROKING_HOURS)
    {
        int employee_id, day;
        cin >> employee_id >> day;
        if (!validate_arg_of_delete_working_hours(day))
            cout << ARGUMENT_ERROR << endl;
        else if (delete_working_hour(all_information, employee_id, day))
            cout << SUCCESSFUL_OPERATION << endl;
        else
            cout << EMPLOYEE_ERROR << endl;
    }
    else if (command == UPDATE_TEAM_BONUS)
    {
        int team_id, bonus;
        cin >> team_id >> bonus;
        if (!validate_arg_of_update_team_bouns(bonus))
            cout << ARGUMENT_ERROR << endl;
        else
        {
            Team *desired_team = find_team_by_id(all_information->get_the_teams_pointers(), team_id);
            if (!desired_team)
                cout << TEAM_ERROR << endl;
            else
            {
                desired_team->set_bonus(bonus);
                cout << SUCCESSFUL_OPERATION << endl;
            }
        }
    }
    else if (command == FIND_TEAM_FOR_BONUS)
    {
        vector<pair<int, int>> capable_teams = find_team_for_bonus(all_information);
        if (capable_teams.size())
            print_bonus_team(capable_teams);
        else
            cout << BONUS_ERROR << endl;
    }
    else if (command == THE_EOF || command == THE_NULL)
        return false;
    else
        cout << COMMAND_ERROR << endl;
    return true;
}

int main()
{
    Data_base all_information(JUNK);
    bool program_continues = true;
    while (program_continues)
        program_continues = execute_command(&all_information);
    return 0;
}
