#include <iostream>
#include <cstring>
#include <cctype>
#include <cstdlib>

#define MAX_SIZE 100

// Define OpCode and Size tables
enum OpCode {
    MOV = 1, A, S, M, D, AN, O, ADD, SUB, MUL, DIV, AND, OR_, LOAD, STORE, DCR, INC, JMP, JNZ, HALT
};

int motOpCode[] = {
    0, MOV, A, S, M, D, AN, O, ADD, SUB, MUL, DIV, AND, OR_, LOAD, STORE, DCR, INC, JMP, JNZ, HALT
};

int motSize[] = {
    0, 1, 1, 1, 1, 1, 1, 1, 1, 2, 2, 2, 2, 2, 3, 3, 1, 1, 3, 3, 1
};

void printMachineCode(int relativeAddress[], std::string instructions[], int machineCode[], int n) {
    std::cout << "Relative Address    Instruction        OpCode\n";
    for (int i = 0; i < n; i++) {
        std::cout << std::left << std::setw(20) << relativeAddress[i] << std::setw(20) << instructions[i] << machineCode[i] << std::endl;
    }
}

int main() {
    std::string instructions[MAX_SIZE];
    int relativeAddress[MAX_SIZE];
    int machineCode[MAX_SIZE];
    int RA = 0, current = 0, count = 0, n;

    std::cout << "Enter the no of instruction lines: ";
    std::cin >> n;

    // Read instructions
    for (int i = 0; i < n; i++) {
        std::cout << "Enter instruction line " << i + 1 << ": ";
        std::getline(std::cin >> std::ws, instructions[i]);
    }

    // Convert instructions to upper case
    for (int i = 0; i < n; i++) {
        for (char &c : instructions[i]) {
            c = toupper(c);
        }
    }

    // Process instructions
    for (int i = 0; i < n; i++) {
        std::string x = instructions[i];
        std::string a, b;

        if (x.find(" ") != std::string::npos) {
            std::stringstream ss(x);
            ss >> a >> b;

            if (motOpCode[0] != 0) {  // Check if OpCode array is initialized
                int value = 0, size = 0;

                for (int j = 1; j <= HALT; j++) {
                    if (a == motOpCode[j]) {
                        value = motOpCode[j];
                        size = motSize[j];
                        break;
                    }
                }

                int previous = size;
                RA += current;
                current = previous;
                relativeAddress[i] = RA;

                if (isalpha(b[0])) {
                    machineCode[i] = value;
                } else {
                    std::string temp;
                    for (char c : b) {
                        if (count == 2) {
                            temp += ',';
                            count = 0;
                        } else {
                            temp += c;
                            count++;
                        }
                    }

                    machineCode[i] = std::stoi(temp);
                }
            } else {
                std::cout << "OpCode array is not initialized.\n";
                exit(EXIT_FAILURE);
            }
        } else {
            if (motOpCode[0] != 0) {  // Check if OpCode array is initialized
                int value = 0, size = 0;

                for (int j = 1; j <= HALT; j++) {
                    if (x == motOpCode[j]) {
                        value = motOpCode[j];
                        size = motSize[j];
                        break;
                    }
                }

                int previous = size;
                RA += current;
                current = previous;
                relativeAddress[i] = RA;
                machineCode[i] = value;
            } else {
                std::cout << "OpCode array is not initialized.\n";
                exit(EXIT_FAILURE);
            }
        }
    }

    // Print the result
    printMachineCode(relativeAddress, instructions, machineCode, n);

    return 0;
}
