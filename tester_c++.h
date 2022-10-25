#ifndef FILE_TESTING_INOUT_TESTER_C_H
#define FILE_TESTING_INOUT_TESTER_C_H
#define IN_FILE_PATH "../in.txt"
//OUT_E stands for expected program output
#define OUT_E_FILE_PATH "../out_e.txt"
#define OUT_FILE_PATH "../out.txt"
#include <fstream>
#include <string>

//Default function to read from files for char
void read_c(char &variable){
    std::ifstream program_input(IN_FILE_PATH);
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
    std::ofstream program_output(OUT_FILE_PATH, std::ofstream::app);
    program_output << thing_to_write_to_file;
    program_output.close();
}

void clear_program_output_file(){
    std::ofstream clear_output(OUT_FILE_PATH);
    clear_output << "";
    clear_output.close();
}

//Main function to test difference between out file and out_e
bool test_output_file(){
    std::ifstream in_program_output(OUT_FILE_PATH);
    std::ifstream in_expected_output(OUT_E_FILE_PATH);

    std::string program_output_line;
    std::string expected_output_line;
    int line_number = 1;

    while(in_expected_output.peek() != EOF){
        std::getline(in_program_output, program_output_line);
        std::getline(in_expected_output, expected_output_line);

        if(program_output_line != expected_output_line){
            std::cout<<"Output from program is different than in expected output!\n";
            std::cout<<"Line number : "<<line_number<<"\n";
            std::cout<<"Expected : "<<expected_output_line<<"\n";
            std::cout<<"Got : "<<program_output_line<<"\n";

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
