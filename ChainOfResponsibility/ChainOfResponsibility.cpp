#include <iostream>
#include <string>
#include <regex>
#include <unordered_set>

class StringValidator {

public:

    virtual ~StringValidator() {}
    virtual StringValidator* set_next(StringValidator* next_validator) = 0;
    virtual std::string validate(std::string) = 0;


};

class BaseValidator: public StringValidator {

protected:

    StringValidator* next = nullptr;

public:

    virtual ~BaseValidator() { delete next; }
    
    StringValidator* set_next (StringValidator* next_validator) override {

        next = next_validator;
        return next_validator;
        
    }

    virtual std::string validate(std::string test_string) override {

        if (this->next) {

            return this->next->validate(test_string);

        }

        return "Success";
        
    }

};

class NotEmptyValidator: public BaseValidator {

public:

    NotEmptyValidator() {}
    
    std::string validate(std::string test_string) {
        
        std::cout << "Checking if empty..." << std::endl;

        if (test_string.empty()) {

            return "Please enter a value";

        }

        return BaseValidator::validate(test_string);
        
    }

};

class LengthValidator: public BaseValidator {

    int min_length;

public:

    LengthValidator(int new_min_length): min_length(new_min_length) {}

    std::string validate(std::string test_string) override {
        
        std::cout << "Checking length..." << std::endl;
        
        if (test_string.length() < min_length) {

            return "Enter a longer string";

        }

        return BaseValidator::validate(test_string);
        
    }

};

class RegexValidator: public BaseValidator {
    
    std::string pattern_name;
    std::string regex_string;

public:

    RegexValidator(std::string new_pattern_name, std::string new_regex_string):
                    pattern_name(new_pattern_name), regex_string(new_regex_string) {}

    std::string validate(std::string test_string) override {

        std::cout << "Checking regex match..." << std::endl;
        
        if (!std::regex_match(test_string, std::regex(regex_string))) {

            return "The entry does not match the correct format";

        }

        return BaseValidator::validate(test_string);

    }
};

class HistoryValidator: public BaseValidator {

    std::unordered_set<std::string> history_list;
    
public:
    
    HistoryValidator() {};

    std::string validate(std::string test_string) override {
        
        std::cout << "Checking if value has been used before" << std::endl;
        
        if (history_list.find(test_string) != history_list.end()) {
            
            return "Please enter a value you have not used before";
        
        }
        
        history_list.insert(test_string);
        
        return BaseValidator::validate(test_string);
        
    }

};

class ContainsAlphabetsValidator: public BaseValidator {
    
public:

    ContainsAlphabetsValidator() {}
    
    std::string validate(std::string test_string) override {

        std::cout << "Checking if alphabets preset" << std::endl;

        for (char ch: test_string) {
            
            if (isalpha(ch)) {

                return BaseValidator::validate(test_string);

            }
        }

        return "Must contain alphabets";

    }

};

class ContainsDigitsValidator: public BaseValidator {

public:
    
    ContainsDigitsValidator() {}

    std::string validate(std::string test_string) override {
        
        std::cout << "Checking if digits present" << std::endl;

        for (char ch: test_string) {

            if (isdigit(ch)) {

                return BaseValidator::validate(test_string);

            }

        }

        return "Must contain digits";
        
    }

};

class ContainsSpecialCharacterValidator: public BaseValidator {

public:

    ContainsSpecialCharacterValidator() {}

    std::string validate(std::string test_string) override {

        std::cout << "Checking if special characters present" << std::endl;

        for (char ch: test_string) {

            if (ch >= 33 && ch <= 47) {

                return BaseValidator::validate(test_string);

            }

        }

        return "Must contain Special Characters";

    }

};

int main (void) {

    StringValidator* email_validator  = new BaseValidator();
    
    email_validator->set_next(new NotEmptyValidator())
                   ->set_next(new RegexValidator("email address","^\\w+([-+.']\\w+)*@\\w+([-.]\\w+)*\\.\\w+([-.]\\w+)*$"));
    

    std::cout << "Checking emails..." << std::endl;
    std::cout << "Input: \n" << email_validator->validate("") << std::endl << std::endl;
    std::cout << "Input: shaun\n" << email_validator->validate("shaun") << std::endl << std::endl;
    std::cout << "Input: shaun@test.com \n" << email_validator->validate("shaun@test.com") << std::endl << std::endl;

    StringValidator* password_validator = new BaseValidator();
    password_validator->set_next(new LengthValidator(5))
                      ->set_next(new ContainsAlphabetsValidator())
                      ->set_next(new ContainsDigitsValidator())
                      ->set_next(new ContainsSpecialCharacterValidator())
                      ->set_next(new HistoryValidator());

    std::cout << "Checking passwords..." << std::endl;
    std::cout << "Input: \n" << password_validator->validate("") << std::endl << std::endl;
    std::cout << "Input: passw\n" << password_validator->validate("passw") << std::endl << std::endl;
    std::cout << "Input: pass1\n" << password_validator->validate("pass1") << std::endl << std::endl;
    std::cout << "Input: pass1!\n" << password_validator->validate("pass1!") << std::endl << std::endl;

    
    
    return 0;

}