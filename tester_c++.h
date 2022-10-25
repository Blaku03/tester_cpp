#ifndef FILE_TESTING_INOUT_TESTER_C_H
#define FILE_TESTING_INOUT_TESTER_C_H
#include <fstream>
#include <string>

//Default function to read from files
void read_c(char &variable){
    std::ifstream program_input("../in.txt");
    static int input_file_iterator = 0;
    char trash_temp;

    for(int i = 0; i < input_file_iterator;i++)
        program_input >> trash_temp;

    program_input >> variable;
    input_file_iterator++;
    program_input.close();
}

//Auto use for different types of int ex: long short
void read(auto &variable){
    char variable_char;
    read_c(variable_char);

    variable = variable_char - '0';
}

void write(auto thing_to_write_to_file){
    std::ofstream program_output("../out.txt", std::ofstream::app);
    program_output << thing_to_write_to_file;
    program_output.close();
}

void clear_program_output_file(){
    std::ofstream clear_output("../out.txt");
    clear_output << "";
    clear_output.close();
}

bool test_output_file(){
    std::ifstream in_program_output("../out.txt");
    std::ifstream in_expected_output("../out_e.txt");

    std::string program_output_line;
    std::string expected_output_line;
    int line_number = 1;

    while(in_expected_output.peek() != EOF){
        std::getline(in_program_output, program_output_line);
        std::getline(in_expected_output, expected_output_line);

        if(program_output_line != expected_output_line){
            std::cout<<"Output from program is different than in expected output!\n";
            std::cout<<"Line number : "<<line_number;
            std::cout<<"Expected : "<<expected_output_line;
            std::cout<<"Got : "<<program_output_line;

            in_program_output.close();
            in_expected_output.close();
            return false;
        }

        line_number++;
    }

    in_program_output.close();
    in_expected_output.close();

    return true;
}

#endif //FILE_TESTING_INOUT_TESTER_C_H
