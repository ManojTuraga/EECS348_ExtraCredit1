#include <string>
#include <fstream>
#include <iostream>
#include "Preference.h"

Preference::Preference(const Preference& rhs)
{
    data = rhs.data;
}
Preference& Preference::operator=(const Preference& rhs)
{
    data = rhs.data;
    return *this;
}
int Preference::getPreference(int preference)
{
    return data[preference - 1];
}
void Preference::addPreference(int preference)
{
    data.push_back(preference);
}
int Preference::size()
{
    return data.size();
}

ProgrammerSorter::ProgrammerSorter(std::string fileName, int nod, int nof) : numOfDepartments{nod}, numOfProgrammers{nof}
{
    std::ifstream inputFile;
    inputFile.open(fileName);

    if (inputFile)
    {
        for (int programmer = 0; programmer < numOfProgrammers; programmer++)
        {
            for (int departmentIndex = 0; departmentIndex < numOfDepartments; departmentIndex++)
            {
                char tempChar[15];
                addDepartment();
                inputFile >> tempChar;

                departments[departmentIndex]->addPreference(atoi(tempChar));
            }
        }
        for (int department = 0; department < numOfDepartments; department++)
        {
            for (int programmerIndex = 0; programmerIndex < numOfProgrammers; programmerIndex++)
            {
                char tempChar[15];
                addProgrammer();
                inputFile >> tempChar;

                programmers[programmerIndex]->addPreference(atoi(tempChar));
            }
        }
        inputFile.close();
    }
    else
    {
        std::cerr << "Cannot find file named '" << fileName << "'\n";
    }

}

void ProgrammerSorter::addDepartment()
{
    departments.push_back(new Preference());
}

void ProgrammerSorter::addProgrammer()
{
    programmers.push_back(new Preference());
}

int ProgrammerSorter::demand(int preferenceLevel, int programmerNumber, bool arr[])
{
    int count = 0;

    for (int depts = 1; depts <= numOfDepartments; depts++)
    {
        if(getDepartment(depts).getPreference(preferenceLevel) == programmerNumber && !arr[depts-1])
        {
            count++;
        }
    }
    return count;
}
Preference& ProgrammerSorter::getDepartment(int departmentNumber)
{
    return *departments[departmentNumber-1];
}
Preference& ProgrammerSorter::getProgrammer(int programmerNumber)
{
    return *programmers[programmerNumber-1];
}

void ProgrammerSorter::sort()
{
    bool departmentsUsed[numOfDepartments];
    bool programmersUsed[numOfProgrammers];
    while (!arrayNotEmpty(departmentsUsed, numOfDepartments) && !arrayNotEmpty(programmersUsed, numOfProgrammers))
    {
        for (int dIndex = 1; dIndex <= numOfDepartments; dIndex++)
        {
            for (int iIndex = 1; iIndex <= numOfProgrammers; iIndex++)
            {
                int programmer = getDepartment(dIndex).getPreference(iIndex);
                int demand = this->demand(iIndex, programmer, departmentsUsed);

                if (demand > 1 && !departmentsUsed[dIndex - 1] && !programmersUsed[programmer - 1])
                {
                    for (int i = 1; i <= numOfDepartments; i++)
                    {
                        if (getDepartment(getProgrammer(programmer).getPreference(i)).getPreference(iIndex) == programmer && !departmentsUsed[getProgrammer(programmer).getPreference(i) - 1] && !programmersUsed[programmer - 1])
                        {
                            if (getProgrammer(programmer).getPreference(i) != dIndex) break;
                            departmentsUsed[getProgrammer(programmer).getPreference(i) - 1] = true;
                            programmersUsed[programmer - 1] = true;
                            std::cout << "Department #"<< getProgrammer(programmer).getPreference(i) <<" will get Programmer #"<< programmer << std::endl;
                        }
                    }
                }
                else if (demand == 1 && !departmentsUsed[dIndex - 1] && !programmersUsed[programmer - 1])
                {
                    bool higherPref = false;
                    for (int i = 0; i < iIndex; i++)
                    {
                        higherPref = higherPref | this->demand(i, programmer, departmentsUsed);
                    }
                    if (!higherPref)
                    {
                        departmentsUsed[dIndex - 1] = true;
                        programmersUsed[programmer - 1] = true;
                        std::cout << "Department #"<< dIndex <<" will get Programmer #"<< programmer << std::endl;
                    }  
                }
            }
        }    
    }
}

bool ProgrammerSorter::arrayNotEmpty(bool arr[], int size)
{
    for (int i = 0; i < size; i++)
    {
        if (!arr[i])
        {
            return false;
        }
    }
    return true;
}