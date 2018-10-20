#include <iostream>
#include <fstream>
#include <cstdlib>
#include <bits/stdc++.h> 
#include <math.h>
#include <map>
#include <vector>
#include <stack>
using namespace std;


int registers[32] = {0};
map<int, int> data;
map<int,string> instructAddress;
map<int, vector<int> > operands;
int MFLO,MFHI = 0;
stack<char> ls;

string findTwoscomplement(string str) 
{ 
    int n = str.length(); 
    int i; 
    for (i = n-1 ; i >= 0 ; i--) 
        if (str[i] == '1') 
            break; 
    if (i == -1) 
        return '1' + str; 
    for (int k = i-1 ; k >= 0; k--) 
    {  
        if (str[k] == '1') 
            str[k] = '0'; 
        else
            str[k] = '1'; 
    } 
    return str; 
}

long binary_to_number(string binaryString) {
    // bool flag = false;
    long value = 0;
    int indexCounter = 0;
    // if (binaryString.at(0) == '1') {
    //     binaryString = findTwoscomplement(binaryString);
    //     flag = true;
    // }
    
    for(int i=binaryString.length()-1;i>=0;i--) {
        if(binaryString[i]=='1') {
            value += pow(2, indexCounter);
        }
    indexCounter++;
    }
    return value;
}

 

int main(int argc, char *argv[]) {
    
    string line;
    ifstream file(argv[1]);
    if (file.fail()) {
        cout <<"INCORRECT INPUT";
        exit(1);
    }
    
    ofstream disassembly;
    ofstream simulation;
    disassembly.open("disassembly.txt");
    simulation.open("simulation.txt");

    long prodiv;
    int pc = 256;
    int ex = pc;
    long d,s1,s2,iv;
    int cycle = 0;
    int jump = 0;
    string category,opcode,instruction,dest,src1,src2,immediate_value,linetwo;
    bool flag = true;
    
    

    while (getline(file,line)) {
        line = line.substr(0,32);
        if (flag) {
            category = line.substr(0,3);
            opcode = line.substr(3,3);
            if (category == "000") { //CATEGORY 1
                if (opcode == "000") {
                    instruction = "J";
                    src1 = line.substr(6,string::npos);
                    s1 = binary_to_number(src1) * 4; //Left shifted by 2 bits
                    // cout << line << "\t" << pc << "\t" << instruction << " #" << s1 << "\n";
                    disassembly << line << "\t" << pc << "\t" << instruction << " #" << s1 << "\n";
                    operands[pc].push_back(s1);
                }
                else if (opcode == "001") {
                    instruction = "BEQ";
                    src1 = line.substr(6,5);
                    src2 = line.substr(11,5);
                    s1 = binary_to_number(src1);
                    s2 = binary_to_number(src2);
                    immediate_value = line.substr(16,string::npos); //offset
                    // iv = binary_to_number(immediate_value) * 4; //left shifted by 2 bits which is equivalent to multiply by 4
                    if (immediate_value.at(0) == '1'){
                        immediate_value = findTwoscomplement(immediate_value);
                        iv = -binary_to_number(immediate_value) * 4;
                    }
                    else {
                        iv = binary_to_number(immediate_value) * 4;
                    
                    }
                    // cout << line << "\t" << pc << "\t" << instruction << " R" << s1 << ", R" << s2 << ", #" << iv <<"\n";
                    disassembly << line << "\t" << pc << "\t" << instruction << " R" << s1 << ", R" << s2 << ", #" << iv <<"\n";
                    operands[pc].push_back(s1);
                    operands[pc].push_back(s2);
                    operands[pc].push_back(iv);
                }
                else if (opcode == "010") {
                    instruction = "BNE";
                    src1 = line.substr(6,5);
                    src2 = line.substr(11,5);
                    s1 = binary_to_number(src1);
                    s2 = binary_to_number(src2);
                    immediate_value = line.substr(16,string::npos); //offset
                    // iv = binary_to_number(immediate_value) * 4; //left shifted by 2 bits which is equivalent to multiply by 4
                    if (immediate_value.at(0) == '1'){
                        immediate_value = findTwoscomplement(immediate_value);
                        iv = -binary_to_number(immediate_value) * 4;
                    }
                    else {
                        iv = binary_to_number(immediate_value) * 4;
                    
                    }
                    // cout << line << "\t" << pc << "\t" << instruction << " R" << s1 << ", R" << s2 << ", #" << iv <<"\n";
                    disassembly << line << "\t" << pc << "\t" << instruction << " R" << s1 << ", R" << s2 << ", #" << iv <<"\n";
                    operands[pc].push_back(s1);
                    operands[pc].push_back(s2);
                    operands[pc].push_back(iv);
                }
                else if (opcode == "011") {
                    instruction = "BGTZ";
                    src1 = line.substr(6,5);
                    s1 = binary_to_number(src1);
                    immediate_value = line.substr(16,string::npos); //offset
                    // iv = binary_to_number(immediate_value) * 4; //left shifted by 2 bits which is equivalent to multiply by 4
                    if (immediate_value.at(0) == '1'){
                        immediate_value = findTwoscomplement(immediate_value);
                        iv = -binary_to_number(immediate_value) * 4;
                    }
                    else {
                        iv = binary_to_number(immediate_value) * 4;
                    
                    }
                    // cout << line << "\t" << pc << "\t" << instruction << " R" << s1 << ", #" << iv <<"\n";
                    disassembly << line << "\t" << pc << "\t" << instruction << " R" << s1 << ", #" << iv <<"\n";
                    operands[pc].push_back(s1);
                    operands[pc].push_back(iv);
                }
                else if (opcode == "100") {
                    instruction = "SW";
                    src1 = line.substr(6,5); //base
                    src2 = line.substr(11,5);
                    s1 = binary_to_number(src1); 
                    s2 = binary_to_number(src2);
                    immediate_value = line.substr(16,string::npos); //offset
                    // iv = binary_to_number(immediate_value);
                    if (immediate_value.at(0) == '1'){
                        immediate_value = findTwoscomplement(immediate_value);
                        iv = -binary_to_number(immediate_value);
                    }
                    else {
                        iv = binary_to_number(immediate_value);
                    
                    }
                    // cout << line << "\t" << pc << "\t" << instruction << " R" << s2 << ", " << iv << "(R" << s1 << ")" << "\n";
                    disassembly << line << "\t" << pc << "\t" << instruction << " R" << s2 << ", " << iv << "(R" << s1 << ")" << "\n";
                    operands[pc].push_back(s2);
                    operands[pc].push_back(iv);
                    operands[pc].push_back(s1);
                    
                }
                else if (opcode == "101") {
                    instruction = "LW";
                    src1 = line.substr(6,5); //base
                    src2 = line.substr(11,5);
                    s1 = binary_to_number(src1); 
                    s2 = binary_to_number(src2);
                    immediate_value = line.substr(16,string::npos); //offset
                    // iv = binary_to_number(immediate_value);
                    if (immediate_value.at(0) == '1'){
                        immediate_value = findTwoscomplement(immediate_value);
                        iv = -binary_to_number(immediate_value);
                    }
                    else {
                        iv = binary_to_number(immediate_value);
                    
                    }
                    // cout << line << "\t" << pc << "\t" << instruction << " R" << s2 << ", " << iv << "(R" << s1 << ")" << "\n";
                    disassembly << line << "\t" << pc << "\t" << instruction << " R" << s2 << ", " << iv << "(R" << s1 << ")" << "\n";
                    operands[pc].push_back(s2);
                    operands[pc].push_back(iv);
                    operands[pc].push_back(s1); 
                }
                else if (opcode == "110") {
                    instruction = "BREAK";
                    // cout << line << "\t" << pc << "\t" << "BREAK" << "\n";
                    disassembly << line << "\t" << pc << "\t" << "BREAK" << "\n";
                    flag = false;
                    operands[pc].push_back(0);
                    
                    
                }
                else {
                    instruction = "INCORRECT";
                }
            }
            else if (category == "001") { //CATEGORY 2
                dest = line.substr(6,5);
                src1 = line.substr(11,5);
                src2 = line.substr(16,5);
                d = binary_to_number(dest);
                s1 = binary_to_number(src1);
                s2 = binary_to_number(src2);
                if (opcode == "000") {
                    instruction = "ADD";
                    disassembly << line << "\t" << pc << "\t" << instruction << " R" << d << ", R" << s1 << ", R" << s2 <<"\n";
                }
                else if (opcode == "001") {
                    instruction = "SUB";
                    disassembly << line << "\t" << pc << "\t" << instruction << " R" << d << ", R" << s1 << ", R" << s2 <<"\n";
                }
                else if (opcode == "010") {
                    instruction = "AND";
                    disassembly << line << "\t" << pc << "\t" << instruction << " R" << d << ", R" << s1 << ", R" << s2 <<"\n";              
                }
                else if (opcode == "011") {
                    instruction = "OR";
                    disassembly << line << "\t" << pc << "\t" << instruction << " R" << d << ", R" << s1 << ", R" << s2 <<"\n";
                }
                else if (opcode == "100") {
                    instruction = "SRL";
                    //s2 is SHIFT
                    disassembly << line << "\t" << pc << "\t" << instruction << " R" << d << ", R" << s1 << ", #" << s2 <<"\n";    
                }
                else if (opcode == "101") {
                    instruction = "SRA";
                    //s2 is shift
                    disassembly << line << "\t" << pc << "\t" << instruction << " R" << d << ", R" << s1 << ", #" << s2 <<"\n";
                }
                else {
                    instruction = "INCORRECT";
                    instruction = "INCORRECT";
                    cout << line << "\t" << "instruction";
                    break;
                }
                // cout << line << "\t" << pc << "\t" << instruction << " R" << d << ", R" << s1 << ", R" << s2 <<"\n";
                // disassembly << line << "\t" << pc << "\t" << instruction << " R" << d << ", R" << s1 << ", R" << s2 <<"\n";
                operands[pc].push_back(d);
                operands[pc].push_back(s1);
                operands[pc].push_back(s2);
                
            }
            else if (category == "010") { //CATEGORY 3
                dest = line.substr(6,5);
                src1 = line.substr(11,5);
                immediate_value = line.substr(16,16);
                if (opcode == "000") {
                    instruction = "ADDI";
                    if (immediate_value.at(0) == '1'){
                        immediate_value = findTwoscomplement(immediate_value);
                        iv = -binary_to_number(immediate_value);
                    }
                    else {
                        iv = binary_to_number(immediate_value);
                    }
                }
                else if (opcode == "001") {
                    instruction = "ANDI";
                    iv = binary_to_number(immediate_value);
                }
                else if (opcode == "010") {
                    instruction = "ORI";
                    iv = binary_to_number(immediate_value);
                }
                else {
                    instruction = "INCORRECT";
                    cout << line << "\t" << "instruction";
                    break;
                }
                d = binary_to_number(dest);
                s1 = binary_to_number(src1);
                
                // cout << line << "\t" << pc << "\t" << instruction << " R" << d << ", R" << s1 << ", #" << iv <<"\n";
                disassembly << line << "\t" << pc << "\t" << instruction << " R" << d << ", R" << s1 << ", #" << iv <<"\n";
                operands[pc].push_back(d);
                operands[pc].push_back(s1);
                operands[pc].push_back(iv);
            }
            else if (category == "011") { //CATEGORY 4
                src1 = line.substr(6,5);
                src2 = line.substr(11,5);
                s1 = binary_to_number(src1);
                s2 = binary_to_number(src2);
                if (opcode == "000") {
                    instruction = "MULT";
                }
                else if (opcode == "001") {
                    instruction = "DIV";
                }
                else {
                    instruction = "INCORRECT";
                    cout << line << "\t" << "instruction";
                    break;
                }
                // cout << line << "\t" << pc << "\t" << instruction << " R" << s1 << ", R" << s2 << "\n";
                disassembly << line << "\t" << pc << "\t" << instruction << " R" << s1 << ", R" << s2 << "\n";
                operands[pc].push_back(s1);
                operands[pc].push_back(s2);
                
            }
            else if (category == "100") { //CATEGORY 5
                dest = line.substr(6,5);
                if (opcode == "000") {
                    instruction = "MFHI";
                }
                else if (opcode == "001") {
                    instruction = "MFLO";
                }
                else {
                    instruction = "INCORRECT";
                    cout << line << "\t" << "instruction";
                    break;
                }
                d = binary_to_number(dest);
                // cout << line << "\t" << pc << "\t" << instruction << " R" << d << "\n";
                disassembly << line << "\t" << pc << "\t" << instruction << " R" << d << "\n";
                operands[pc].push_back(d);
            }
            instructAddress[pc] = instruction;
            // cout << instructAddress[pc] << "\t" <<  operands[pc][0] << "\n";
        }
        else {
            // if (line.substr(0,1) == "1") { //NEGATIVE NUMBERS
            //     dest = (bitset<32>(line) ^ bitset<32>(string("11111111111111111111111111111111"))).to_string();
            //     d = binary_to_number(dest) + 1;
            //     // cout << line << "\t" << pc << "\t" << "-" << d << "\n";
            //     disassembly << line << "\t" << pc << "\t" << "-" << d << "\n";
            //     data[pc] = -d;
            // }
            // else {
            //     d = binary_to_number(line);
            //     // cout << line << "\t" << pc << "\t" << d << "\n";
            //     // disassembly << line << "\t" << pc << "\t" << d << "\n";
            //     data[pc] = d;
            // }
            if (line.at(0) == '1'){
                linetwo = findTwoscomplement(line);
                d = -binary_to_number(linetwo);
                disassembly << line << "\t" << pc << "\t" <<  d << "\n";
                data[pc] = d;
            }
            else {
                d = binary_to_number(line);
                disassembly << line << "\t" << pc << "\t" << d << "\n";
                data[pc] = d;
            }
            
        }
        
         
        // disassembly << line<< "\t" << pc << "\n";
        pc = pc+4;
        d = s1 = s2  = iv = 0;
        dest = src1 = src2 = immediate_value = linetwo = "";
    }
    disassembly.close();
    
    flag = true;
    
    while (flag) {
        // cout << "--------------------\n";
        simulation << "--------------------\n";
        if (instructAddress[ex] == "J") {
            s1 = operands[ex][0];
            // cout << "Cycle " << ++cycle << ":\t" << ex << "\t" << instructAddress[ex] << " #" << s1 << "\n";
            simulation << "Cycle " << ++cycle << ":\t" << ex << "\t" << instructAddress[ex] << " #" << s1 << "\n";
            jump = s1 - ex - 4;
        }
        else if (instructAddress[ex] == "BEQ") {
            s1 = operands[ex][0];
            s2 = operands[ex][1];
            iv = operands[ex][2];
            registers[s1] == registers[s2] ? jump = iv: jump = 0;
            // cout << "Cycle " << ++cycle << ":\t" << ex << "\t" << instructAddress[ex] <<  " R" << s1 << ", R" << s2 << ", #" << iv <<"\n";
            simulation << "Cycle " << ++cycle << ":\t" << ex << "\t" << instructAddress[ex] <<  " R" << s1 << ", R" << s2 << ", #" << iv <<"\n";
        }
        else if (instructAddress[ex] == "BNE") {
            s1 = operands[ex][0];
            s2 = operands[ex][1];
            iv = operands[ex][2];
            registers[s1] != registers[s2] ? jump = iv: jump = 0;
            // cout << "Cycle " << ++cycle << ":\t" << ex << "\t" << instructAddress[ex] <<  " R" << s1 << ", R" << s2 << ", #" << iv <<"\n";
            simulation << "Cycle " << ++cycle << ":\t" << ex << "\t" << instructAddress[ex] <<  " R" << s1 << ", R" << s2 << ", #" << iv <<"\n";
        }
        else if (instructAddress[ex] == "BGTZ") {
            s1 = operands[ex][0];
            iv = operands[ex][1];
            registers[s1] > 0 ? jump = iv : jump = 0;
            // cout << "Cycle " << ++cycle << ":\t" << ex << "\t" << instructAddress[ex] << " R" << s1 << ", #" << iv <<"\n";
            simulation << "Cycle " << ++cycle << ":\t" << ex << "\t" << instructAddress[ex] << " R" << s1 << ", #" << iv <<"\n";
        }
        else if (instructAddress[ex] == "SW") {
            s2 = operands[ex][0];
            iv = operands[ex][1];
            s1 = operands[ex][2];
            data[iv + registers[s1]] = registers[s2];
            // cout << "Cycle " << ++cycle << ":\t" << ex << "\t" << instructAddress[ex] << " R" << s2 << ", " << iv << "(R" << s1 << ")" << "\n";
            simulation << "Cycle " << ++cycle << ":\t" << ex << "\t" << instructAddress[ex] << " R" << s2 << ", " << iv << "(R" << s1 << ")" << "\n";
        }
        else if (instructAddress[ex] == "LW") {
            s2 = operands[ex][0];
            iv = operands[ex][1];
            s1 = operands[ex][2];
            registers[s2] = data[iv + registers[s1]];
            // cout << "Cycle " << ++cycle << ":\t" << ex << "\t" << instructAddress[ex] << " R" << s2 << ", " << iv << "(R" << s1 << ")" << "\n";
            simulation << "Cycle " << ++cycle << ":\t" << ex << "\t" << instructAddress[ex] << " R" << s2 << ", " << iv << "(R" << s1 << ")" << "\n";

        }
        else if (instructAddress[ex] == "BREAK") {
            
            // cout << "Cycle " << ++cycle << ":\t" << ex << "\t" << instructAddress[ex] << "\n";
            simulation << "Cycle " << ++cycle << ":\t" << ex << "\t" << instructAddress[ex] << "\n";
            flag = false;
        }
        else if (instructAddress[ex] == "ADD") {
            d = operands[ex][0];
            s1 = operands[ex][1];
            s2 = operands[ex][2];
            registers[d] = registers[s1] + registers[s2];
            // cout << "Cycle " << ++cycle << ":\t" << ex << "\t" << instructAddress[ex] << " R" << d << ", R" << s1 << ", R" << s2 <<"\n";
            simulation << "Cycle " << ++cycle << ":\t" << ex << "\t" << instructAddress[ex] << " R" << d << ", R" << s1 << ", R" << s2 <<"\n";
             
        }
        else if (instructAddress[ex] == "SUB") {
            d = operands[ex][0];
            s1 = operands[ex][1];
            s2 = operands[ex][2];
            registers[d] = registers[s1] - registers[s2];
            // cout << "Cycle " << ++cycle << ":\t" << ex << "\t" << instructAddress[ex] << " R" << d << ", R" << s1 << ", R" << s2 <<"\n";
            simulation << "Cycle " << ++cycle << ":\t" << ex << "\t" << instructAddress[ex] << " R" << d << ", R" << s1 << ", R" << s2 <<"\n";
        }
        else if (instructAddress[ex] == "AND") {
            d = operands[ex][0];
            s1 = operands[ex][1];
            s2 = operands[ex][2];
            registers[d] = registers[s1] & registers[s2];
            // cout << "Cycle " << ++cycle << ":\t" << ex << "\t" << instructAddress[ex] << " R" << d << ", R" << s1 << ", R" << s2 <<"\n";
            simulation << "Cycle " << ++cycle << ":\t" << ex << "\t" << instructAddress[ex] << " R" << d << ", R" << s1 << ", R" << s2 <<"\n";
        }
        else if (instructAddress[ex] == "OR") {
            d = operands[ex][0];
            s1 = operands[ex][1];
            s2 = operands[ex][2];
            registers[d] = registers[s1] | registers[s2];
            // cout << "Cycle " << ++cycle << ":\t" << ex << "\t" << instructAddress[ex] << " R" << d << ", R" << s1 << ", R" << s2 <<"\n";
            simulation << "Cycle " << ++cycle << ":\t" << ex << "\t" << instructAddress[ex] << " R" << d << ", R" << s1 << ", R" << s2 <<"\n";
        }
        else if (instructAddress[ex] == "SRL") {
            d = operands[ex][0];
            s1 = operands[ex][1];
            s2 = operands[ex][2]; //shift
            if (registers[s1] < 0) {
                // src1 = findTwoscomplement(bitset<32>(-registers[s1]).to_string());
                // iv = binary_to_number(src1)
                // registers[d] = binary_to_number((bitset<32>(src1) & bitset<32>(string("01111111111111111111111111111111"))).to_string());
                // src1 = "";
                int n;
                int counter = 0;
                src2 = "";
                src1 = findTwoscomplement(bitset<32>(-registers[s1]).to_string());
                n = src1.length();
                for (int i = n-1; i>=0 ;i--){
                    ls.push(src1[i]);
                }
                for (int i = 0; i < s2; i++){
                    ls.push('0');
                }
                while (!ls.empty())
                {
                    //  cout << ' ' << l.top();
                    if (counter<32) {
                        src2+= ls.top();
                        counter ++;
                    }
                    ls.pop();
                }
                registers[d] = binary_to_number(src2);           
                src2 = src1 = "";
            }
            else {
                registers[d] = registers[s1] >> s2;
            } 
            // cout << "Cycle " << ++cycle << ":\t" << ex << "\t" << instructAddress[ex] << " R" << d << ", R" << s1 << ", R" << s2 <<"\n";
            simulation << "Cycle " << ++cycle << ":\t" << ex << "\t" << instructAddress[ex] << " R" << d << ", R" << s1 << ", #" << s2 <<"\n";
        }
        else if (instructAddress[ex] == "SRA") {
            d = operands[ex][0];
            s1 = operands[ex][1];
            s2 = operands[ex][2]; //shift
            registers[d] = registers[s1] >> s2;
            // cout << "Cycle " << ++cycle << ":\t" << ex << "\t" << instructAddress[ex] << " R" << d << ", R" << s1 << ", R" << s2 <<"\n";
            simulation << "Cycle " << ++cycle << ":\t" << ex << "\t" << instructAddress[ex] << " R" << d << ", R" << s1 << ", #" << s2 <<"\n";
        }
        else if (instructAddress[ex] == "ADDI") {
            d = operands[ex][0];
            s1 = operands[ex][1];
            iv = operands[ex][2];
            registers[d] = registers[s1] + iv;
            // cout << "Cycle " << ++cycle << ":\t" << ex << "\t" << instructAddress[ex] << " R" << d << ", R" << s1 << ", #" << iv << "\n";
            simulation << "Cycle " << ++cycle << ":\t" << ex << "\t" << instructAddress[ex] << " R" << d << ", R" << s1 << ", #" << iv <<"\n";
        }
        else if (instructAddress[ex] == "ANDI") {
            d = operands[ex][0];
            s1 = operands[ex][1];
            iv = operands[ex][2];
            registers[d] = registers[s1] & iv;
            // cout << "Cycle " << ++cycle << ":\t" << ex << "\t" << instructAddress[ex] << " R" << d << ", R" << s1 << ", #" << iv << "\n";
            simulation << "Cycle " << ++cycle << ":\t" << ex << "\t" << instructAddress[ex] << " R" << d << ", R" << s1 << ", #" << iv << "\n";
        }
        else if (instructAddress[ex] == "ORI") {
            d = operands[ex][0];
            s1 = operands[ex][1];
            iv = operands[ex][2];
            registers[d] = registers[s1] | iv;
            // cout << "Cycle " << ++cycle << ":\t" << ex << "\t" << instructAddress[ex] <<  " R" << d << ", R" << s1 << ", #" << iv << "\n";
            simulation << "Cycle " << ++cycle << ":\t" << ex << "\t" << instructAddress[ex] <<  " R" << d << ", R" << s1 << ", #" << iv << "\n";
        }
        else if (instructAddress[ex] == "MULT") {
            s1 = operands[ex][0];
            s2 = operands[ex][1];
            prodiv = long(registers[s1]) * long(registers[s2]);
            if (prodiv > INT_MAX) {
                src1 = bitset<64>(prodiv).to_string();
                if (src1.at(0)== '1') {
                    src2 = findTwoscomplement(src1.substr(0,32));
                    MFHI = - binary_to_number(src2);
                    src2 = "";
                }
                else {
                    MFHI = binary_to_number(src1.substr(0,32));
                }
                if(src1.at(32)=='1') {
                    src2 = findTwoscomplement(src1.substr(32,string::npos));
                    MFLO = -binary_to_number(src2);
                    src2 = "";
                }
                else {
                    MFLO = binary_to_number(src1.substr(32,string::npos));
                }
            }
            else if (prodiv < INT_MIN) {
                src1 = findTwoscomplement(bitset<64>(-prodiv).to_string());
                if (src1.at(0)== '1') {
                    src2 = findTwoscomplement(src1.substr(0,32));
                    MFHI = -binary_to_number(src2);
                    src2 = "";
                }
                else {
                    MFHI = binary_to_number(src1.substr(0,32));
                }
                if(src1.at(32)=='1') {
                    src2 = findTwoscomplement(src1.substr(32,string::npos));
                    MFLO = -binary_to_number(src2);
                    src2 = "";
                }
                else {
                    MFLO = binary_to_number(src1.substr(32,string::npos));
                }
            }
            else {
                MFLO = registers[s1] * registers[s2];
                MFHI = 0;
            }
            src1 = "";                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                        
            // cout << "Cycle " << ++cycle << ":\t" << ex << "\t" << instructAddress[ex] << " R" << s1 << ", R" << s2 << "\n";
            simulation << "Cycle " << ++cycle << ":\t" << ex << "\t" << instructAddress[ex] << " R" << s1 << ", R" << s2 << "\n";
            
        }
        else if (instructAddress[ex] == "DIV") {
            s1 = operands[ex][0];
            s2 = operands[ex][1];
            MFHI = registers[s1]%registers[s2];
            MFLO = registers[s1]/registers[s2];
            // cout << "Cycle " << ++cycle << ":\t" << ex << "\t" << instructAddress[ex] << " R" << s1 << ", R" << s2 << "\n";
            simulation << "Cycle " << ++cycle << ":\t" << ex << "\t" << instructAddress[ex] << " R" << s1 << ", R" << s2 << "\n";
        }
        else if (instructAddress[ex] == "MFHI") {
            d = operands[ex][0];
            // cout << "Cycle " << ++cycle << ":\t" << ex << "\t" << instructAddress[ex] << " R" << d << "\n";
            simulation << "Cycle " << ++cycle << ":\t" << ex << "\t" << instructAddress[ex] << " R" << d << "\n";
            registers[d] = MFHI;
        }
        else if (instructAddress[ex] == "MFLO") {
            d = operands[ex][0];                                                                
            // cout << "Cycle " << ++cycle << ":\t" << ex << "\t" << instructAddress[ex] << " R" << d <<"\n";
            simulation << "Cycle " << ++cycle << ":\t" << ex << "\t" << instructAddress[ex] << " R" << d <<"\n";
            registers[d] = MFLO;
        }
      
        // cout << "\nRegisters\n";
        // cout << "R00:\t" << registers[0] << "\t" << registers[1] << "\t" << registers[2] << "\t" << registers[3] << "\t" << registers[4] << "\t" << registers[5] << "\t" << registers[6] << "\t" << registers[7] << "\n";
        // cout << "R08:\t" << registers[8] << "\t" << registers[9] << "\t" << registers[10] << "\t" << registers[11] << "\t" << registers[12] << "\t" << registers[13] << "\t" << registers[14] << "\t" << registers[15] << "\n";
        // cout << "R16:\t" << registers[16] << "\t" << registers[17] << "\t" << registers[18] << "\t" << registers[19] << "\t" << registers[20] << "\t" << registers[21] << "\t" << registers[22] << "\t" << registers[23] << "\n";
        // cout << "R24:\t" << registers[24] << "\t" << registers[25] << "\t" << registers[26] << "\t" << registers[27] << "\t" << registers[28] << "\t" << registers[29] << "\t" << registers[30] << "\t" << registers[31] << "\n";
        // cout << "\nData";
        simulation << "\nRegisters\n";
        simulation << "R00:\t" << registers[0] << "\t" << registers[1] << "\t" << registers[2] << "\t" << registers[3] << "\t" << registers[4] << "\t" << registers[5] << "\t" << registers[6] << "\t" << registers[7] << "\n";
        simulation << "R08:\t" << registers[8] << "\t" << registers[9] << "\t" << registers[10] << "\t" << registers[11] << "\t" << registers[12] << "\t" << registers[13] << "\t" << registers[14] << "\t" << registers[15] << "\n";
        simulation << "R16:\t" << registers[16] << "\t" << registers[17] << "\t" << registers[18] << "\t" << registers[19] << "\t" << registers[20] << "\t" << registers[21] << "\t" << registers[22] << "\t" << registers[23] << "\n";
        simulation << "R24:\t" << registers[24] << "\t" << registers[25] << "\t" << registers[26] << "\t" << registers[27] << "\t" << registers[28] << "\t" << registers[29] << "\t" << registers[30] << "\t" << registers[31] << "\n";
        simulation << "\nData";
        {
            int i = 0;
            for(map<int,int>::iterator iter = data.begin(); iter != data.end(); ++iter){
                if (i%8 == 0) {
                    // cout<< "\n" << iter->first <<":";
                    simulation<< "\n" << iter->first <<":";
                }
                // cout << "\t" << iter->second;
                simulation << "\t" << iter->second;
                i++;
            }
            // cout << "\n";
            simulation << "\n";
        }
        d = s1 = s2  = iv = 0;
        ex = ex + 4 + jump;
        jump = 0;
        
    }
    simulation.close();
}