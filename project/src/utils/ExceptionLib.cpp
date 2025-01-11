#include "ExceptionLib.hpp"

void validateIDNumber(const std::string& ID) {
    std::regex IDTemplate("\\d{6}$");
    if (!std::regex_match(ID, IDTemplate)) {
        throw InvalidIDException();
    }
}

void validateFullName(const std::string& fullName) {
    std::regex nameTemplate(R"([a-zA-Z\s]+)");
    if (fullName.length() < 10 || fullName.length() > 50 || !std::regex_match(fullName,nameTemplate)) {
        throw InvalidFullNameException();
    }
}

void validateDoB(const std::string& dob) {
    std::regex birthdayTemplate(R"((\d{2})/(\d{2})/(\d{4}))");
    std::smatch match;

    if (std::regex_match(dob, match, birthdayTemplate)) {
        int day = std::stoi(match[1].str());
        int month = std::stoi(match[2].str());
        int year = std::stoi(match[3].str());

        if (year < 1964 || year > 2006) {
            throw InvalidDOBException();
        }

        if (month < 1 || month > 12) {
            throw InvalidDOBException();
        }

        int daysInMonth[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

        if ((year % 4 == 0 && year % 100 != 0) || year % 400 == 0) {
            daysInMonth[1] = 29;
        }

        if (day < 1 || day > daysInMonth[month - 1]) {
            throw InvalidDOBException();
        }
        return;
    }
    throw InvalidDOBException();
}

void validateEntryYear(const std::string& entry_year) {
    std::regex EntryYearTemplate("\\d{4}$");
    if (!std::regex_match(entry_year, EntryYearTemplate)) {
        throw InvalidEntryYearException();
    }
    int year = std::stoi(entry_year);
    if (year < 2017 || year > 2025) {
        throw InvalidEntryYearException();
    }
}

void validateScore(const double& score) {
    if (score < 0.0 || score > 10.0) {
        throw InvalidScoreException();
    }
}

void validateTrainningCenter(const std::string& trainning_center) {
    std::regex nameTemplate(R"([a-zA-Z\s]+)");
    if (!std::regex_match(trainning_center,nameTemplate)) {
        throw InvalidTrainningCeterException();
    } 
}

void validateSemesterName(const std::string& semester_name) {
    std::regex semesterTemplate(R"(HK\d{2})");
    if (!std::regex_match(semester_name, semesterTemplate)) {
        throw InvalidSemesterNameException();
    }
}

void validatePosInteger(const size_t& value) {
    if (value < 0) {
        throw InvalidInputIntegerException();
    }
}


void validateScanfMenu(const size_t& value) {
    if (value < 0 || value > 2) {
        throw InvalidInputIntegerException();
    }
}

void Exception_Handler(const std::string& str,std::string& variable, void(*func)(const std::string&)) {
    while(1) {
        try {
            std::cout << str;
            std::getline(std::cin,variable);     
            func(variable);
            break;
        }
        catch (const std::exception& e) {
            std::cout << "Caught exception: " << e.what() << std::endl;
        }
    }
}
void Exception_Handler(const std::string& str,size_t& variable, void(*func)(const size_t&)) {
    while(1) {
        try {
            std::cout << str;
            std::cin >> variable;
            if (std::cin.fail()) {
                throw InvalidInputIntegerException();
            }
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            func(variable);
            break;  
        }
        catch (const std::exception& e) {
        std::cout << "Caught exception: " << e.what() << std::endl;
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    }
}

void Exception_Handler(const std::string& str,double& variable, void(*func)(const double&)) {
    while(1) {
        try {
            std::cout << str;
            std::cin >> variable;

            if (std::cin.fail()) {
                throw InvalidScoreException();
            }
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            func(variable);
            break;  
        }
        catch (const std::exception& e) {
        std::cout << "Caught exception: " << e.what() << std::endl;
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    }
}