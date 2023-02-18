#ifndef PREFRENCE_H
#define PREFRENCE_H
#include <string>
#include <vector>

class Preference
{
    private:
        std::vector<int> data;

    public:
        Preference() = default;
        ~Preference() = default;
        
        Preference(const Preference& rhs);
        Preference& operator=(const Preference& rhs);

        int getPreference(int preference);
        void addPreference(int preference);

        int size();
};

class ProgrammerSorter
{
    private:
        std::vector<Preference *> departments;
        std::vector<Preference *> programmers;

        const int numOfDepartments;
        const int numOfProgrammers;

        bool arrayNotEmpty(bool arr[], int size);

    public:
        ProgrammerSorter(std::string fileName, int nod, int nof);
        ~ProgrammerSorter();

        Preference& getDepartment(int departmentNumber);
        Preference& getProgrammer(int programmerNumber);

        void addDepartment();
        void addProgrammer();

        int demand(int preference, int programmerNumber, bool arr[]);

        void sort();
};
#endif