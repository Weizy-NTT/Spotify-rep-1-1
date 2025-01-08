#ifndef EXCEPTION_H
#define EXCEPTION_H

#include<bits/stdc++.h>

class InvalidIDException : public std::exception {
public:
    const char* what() const noexcept override {
        return "Invalid ID number. The ID student has 6 numeric characters.";
    }
};

class InvalidFullNameException : public std::exception {
public:
    const char* what() const noexcept override {
        return "The full name has a length of 10 to 50 characters. Only alpha characters are allowed.";
    }
};

class InvalidDOBException  : public std::exception {
public:
    const char* what() const noexcept override {
        return "Invalid birthday. Date of birth must be in dd/MM/YYYY format.";
    }
};

class InvalidEntryYearException  : public std::exception {
public:
    const char* what() const noexcept override {
        return "Entry year must be between 2017 and 2025.";
    }
};

class InvalidScoreException  : public std::exception {
public:
    const char* what() const noexcept override {
        return "Entry score must be between 0 and 10 and is a numeric value.";
    }
};

class InvalidTrainningCeterException  : public std::exception {
public:
    const char* what() const noexcept override {
        return "Trainning center has only alpha characters(Dong Nai, Ca Mau, …).";
    }
};

class InvalidSemesterNameException  : public std::exception {
public:
    const char* what() const noexcept override {
        return "Invalid semester name. The format should be HKxx, where xx are two numeric characters";
    }
};

class InvalidInputIntegerException  : public std::exception {
public:
    const char* what() const noexcept override {
        return "Invalid input. Input must be an integer value";
    }
};

void validateIDNumber(const std::string& ID);
void validateFullName(const std::string& fullName);
void validateDoB(const std::string& dob);
void validateEntryYear(const std::string& entry_year);
void validateScore(const double& score);
void validateTrainningCenter(const std::string& trainning_center);
void validateSemesterName(const std::string& semester_name);
void validatePosInteger(const size_t& value);
void Exception_Handler(const std::string& str,std::string& variable, void(*func)(const std::string&));
void Exception_Handler(const std::string& str,size_t& variable, void(*func)(const size_t&));
void Exception_Handler(const std::string& str,double& variable, void(*func)(const double&));
#endif // EXCEPTION_H
