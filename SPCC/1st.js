const readline = require('readline');

// Define OpCode and Size tables
const motOpCode = {
    "MOV": 1, "A": 2, "S": 3, "M": 4, "D": 5, "AN": 6, "O": 7,
    "ADD": 8, "SUB": 9, "MUL": 10, "DIV": 11, "AND": 12, "OR": 13,
    "LOAD": 14, "STORE": 15, "DCR": 16, "INC": 17, "JMP": 18, "JNZ": 19, "HALT": 20
};

const motSize = {
    "MOV": 1, "A": 1, "S": 1, "M": 1, "D": 1, "AN": 1, "O": 1,
    "ADD": 1, "SUB": 2, "MUL": 2, "DIV": 2, "AND": 2, "OR": 2,
    "LOAD": 3, "STORE": 3, "DCR": 1, "INC": 1, "JMP": 3, "JNZ": 3, "HALT": 1
};

const rl = readline.createInterface({
    input: process.stdin,
    output: process.stdout
});

const instructions = [];
const relativeAddress = [];
const machineCode = [];
let RA = 0;
let current = 0;
let count = 0;
let n = 0;

const readInstruction = () => {
    rl.question("Enter the no of instruction lines: ", (input) => {
        n = parseInt(input);
        readNextInstruction(0);
    });
};

const readNextInstruction = (i) => {
    if (i < n) {
        rl.question(`Enter instruction line ${i + 1}: `, (instruction) => {
            instructions.push(instruction.toUpperCase());
            readNextInstruction(i + 1);
        });
    } else {
        rl.close();
        processInstructions();
    }
};

const processInstructions = () => {
    instructions.forEach((x, i) => {
        if (x.includes(" ")) {
            const [a, b] = x.split(' ');
            const value = motOpCode[a];
            const size = motSize[a];
            const previous = size;
            RA += current;
            current = previous;
            relativeAddress.push(RA);

            if (/^[a-zA-Z]+$/.test(b)) {
                machineCode.push(value);
            } else {
                const temp = b.split('').map((c, index) => {
                    if (count === 2) {
                        count = 0;
                        return ',' + c;
                    } else {
                        count++;
                        return c;
                    }
                }).join('');
                machineCode.push(`${value},${temp}`);
            }
        } else {
            const value = motOpCode[x];
            const size = motSize[x];
            const previous = size;
            RA += current;
            current = previous;
            relativeAddress.push(RA);
            machineCode.push(value);
        }
    });

    // Print the result
    console.log("Relative Address    Instruction        OpCode");
    for (let i = 0; i < n; i++) {
        console.log(`${relativeAddress[i]}                 ${instructions[i]}          ${machineCode[i]}`);
    }
};

// Start the process by reading the number of instruction lines
readInstruction();
