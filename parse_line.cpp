
#include <iostream>
#include <list>
#include <sstream>
#include <string>
#include <vector>

#include "intersection-proj.hpp"
bool verbose1 = false;


// std::string replace_substring (std::string str, std::string to_find, std::string to_replace) {
//     // From https://stackoverflow.com/a/4643526
//     size_t index = 0;
//     int size_to_find = to_find.length();

//     while (true) {
//         // Locating the substring to replace

//         index = str.find(to_find, index);
//         if (index == std::string::npos) {

//             break;
//         }
//         // Replacing the "," for space
//         str.replace(index, size_to_find, to_replace);
//         //Advance the index forward
//         index++;
//     }
//     return str;
// }

bool parse_num (std::istringstream &input, std::list<unsigned> &nums){

    unsigned num;
    input >> num;
    if (input.fail()) {
        // std::cout << "Error: parsing a number" << num << std::endl;
        return false;
    } 
    nums.push_back(num);
    if (verbose1) {
        std::cout << num << std::endl;
    }
    return true;
}

bool parse_char (std::istringstream &input, char ch, char ch2 = '}'){
    char c;
    input >> c;
    if (!input.eof()){
        if (input.fail()) {
            // std::cout << "Error: parsing char" << ch << std::endl;
            return false;
        } 
        return(c == ch || c == ch2);        
    }
    return false;
}

bool parse_line (const std::string &line,
                 char &cmd, std::list<unsigned> &nums, std::string &err_msg) {

    std::istringstream input(line);

    // remove whitespace
    //std::ws(input);

    // Check for empty command
    if (input.eof()) {
        err_msg = "Empty command";
        return false;
    }

    // Read first caracter = command
    char ch;
    input >> ch;

    if (input.fail()) {
        err_msg = "Failed to read input";
        return false;
    }
    switch (ch) {
    // Command = 'V'
    case 'V': {
        // remove whitespace
        std::ws(input);
        unsigned num;
        input >> num;
        if (input.fail()) {
            err_msg = "Missing or bad argument for V";
            return false;
        }
        std::ws(input);
        if (!input.eof()) {
            err_msg = "Unexpected argument for V";
            return false;
        }
        cmd = ch;
        nums.push_back(num);
        // arg = std::to_string(num);
        if (verbose1){
            std::cout << "\nYour character: " << cmd << "\nYour arguments: ";
            for (int i : nums) {
                std::cout << i << " ";
            }
            std::cout << std::endl;
        }
        return true;
    }
    // Command = 'E'
    case 'E': {
        // remove whitespace
        std::ws(input);

        // std::string vertice = "";
        // input >> vertices;


        // std::stringstream input;
            
        // input << arg;
        const char curly_open = '{';
        const char curly_close = '}';
        const char comma = ',';
        const char angle_open = '<';
        const char angle_close = '>';
        // char c;
        
        // input >> c;

        // std::cout << c << std::endl;

        if (!parse_char(input, curly_open)) {
            err_msg = "Missing or bad argument for E. {";
            return false;
        }

        while (!input.eof()) {
            if (parse_char(input, angle_open)){
                // parse an integer
                if (parse_num(input, nums)) {

                    if (parse_char(input, comma)) {

                        if (parse_num(input, nums)) {

                            if (parse_char(input, angle_close)){
                                
                                if (!parse_char(input, comma, curly_close)){
                                    // if (input.eof()){
                                    //     break;
                                    // }
                                    // else { 
                                        err_msg = "Missing or bad argument for E. ,2";
                                        return false;
                                }
                            } else {
                            err_msg = "Missing or bad argument for E. >";

                            return false;
                            break;
                            }
                        } else {
                        err_msg = "Missing or bad argument for E. #";

                        return false;
                        break;
                        }
                    } else {
                    err_msg = "Missing or bad argument for E. ,";

                    return false;
                    break;
                    }
                } else {
                err_msg = "Missing or bad argument for E. #";

                return false;
                break;
                }
            } else {
                // if eof bail out
                if (input.eof()){
                    break;
                }
                err_msg = "Missing or bad argument for E. <";

                return false;
                   break;
                
            }
            
        //    std::cout << std::to_string(nums) << endl;
        }

        ws(input);
        if (!input.eof()) {
            err_msg = "Missing, bad or unexpected argument for E";
            return false;
        }
        cmd = ch;
        // arg = vertices;
        // arg = replace_substring(arg, ",", " ");
        // arg = replace_substring(arg, "<", " ");
        // arg = replace_substring(arg, ">", " ");
        if (verbose1){
            std::cout << "Your character: " << cmd << "\nYour arguments: ";
            for (unsigned i : nums) {
                std::cout << i << " ";
            }
            std::cout << std::endl;
        }
        return true;
    }
    // Command = 's'
    case 's': {
        // remove whitespace
        // std::ws(input);
        unsigned num;
        // 
        input >> num;

        if (input.fail()) {
            err_msg = "Missing or bad argument for s";
            return false;
        }

        nums.push_back(num);

        input >> num;
        
        if (input.fail()) {
            err_msg = "Missing or bad argument for s";
            return false;
        }
        nums.push_back(num);

        ws(input);
        if (!input.eof()) {
            err_msg = "Unexpected argument for s";
            return false;
        }
        cmd = ch;

        if (verbose1){
            std::cout << "Your character: " << cmd << "\nYour arguments: ";
            for (unsigned i : nums) {
                std::cout << i << " ";
            }
            std::cout << std::endl;
        }
        return true;
    } 
    default:
        err_msg = "Unknown command";
        return false;
    }

}

bool print_short_path (std::vector<unsigned> short_path) {

    for (auto i = short_path.rbegin(); i != short_path.rend(); ++i){
        if (i != short_path.rend() - 1){
            std::cout << *i << "-";
        } else {
            std::cout << *i;
        }
    }
    std::cout << std::endl;
    return true;
}