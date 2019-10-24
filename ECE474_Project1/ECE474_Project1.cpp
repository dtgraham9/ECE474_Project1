#include <iostream>
#include <vector>
#include "ReservationStation.h"
#include "Instruction.h"
#include <fstream>
#include "Reg_Rat.h"
const int ADD_SUB_RS = 3;
const int MUL_DIV_RS = 2;

//Latencies for different stages
const int ISSUE_LAT = 1;
const int BROADCAST_LAT = 1;
//Reservation Station Latency for different opcodes at execution
const int ADD_SUB_LAT = 2;
const int MULT_LAT = 10;
const int DIV_LAT = 40;
// Opcode Values
const int AddOp = 0;
const int SubOp = 1;
const int MultOp = 2;
const int DivOp = 3;

const int OPERAND_READY = -1;
const int OPERAND_EMPTY = -2;
const int CLEAR_OPERAND = -3;


const int NUM_REG = 8;

struct RS_DIVIDER {
	int ADD_START = 0;
	int ADD_END = ADD_SUB_RS;
	int MUL_START = ADD_SUB_RS;
	int MUL_END = MUL_DIV_RS + ADD_SUB_RS;
}RS_Bounds;

int Issue(std::vector<Instruction>& instructions, 
	ReservationStation res_unit[], 
	Reg_Rat registers[],
	int instr_counter);
//void EXECUTE(vector<Instruction>& Inst,
//	ReservationStation[] & res_unit,
//	vector<RegisterStatus>& RegStat,
//	vector<int>& Register);
//void WRITEBACK(vector<Instruction>& Inst,
//	ReservationStation[] & res_unit,
//	vector<RegisterStatus>& RegStat,
//	vector<int>& Register);

std::string Opcode(int op) {
	switch (op)
	{
	case AddOp:
		return "Add";
		break;
	case SubOp:
		return "Sub";
		break;
	case MultOp:
		return "MUL";
		break;
	case DivOp:
		return "DIV";
		break;
	default:
		break;
	}
}


int main()
{
	std::ifstream instr_file;
	instr_file.open("test.txt", std::ios_base::in);
	if (!instr_file) {
		std::cerr << "Unable to open file";
		exit(1);   // call system to stop
	}
	int amount;
	int num_cycles;
	instr_file >> amount;
	const int instr_amount = amount;
	instr_file >> num_cycles;
	// Load all instructions into memory
	std::vector<Instruction> instructions;
	for (int i = 0; i < instr_amount; ++i) {
		int Op, Rd, Rs, Rt;
		instr_file >> Op >> Rd >> Rs >> Rt;
		instructions.push_back(Instruction(Op, Rd, Rs, Rt));
	}
	// load all register values into memory
	Reg_Rat registers[NUM_REG];
	for (int i = 0; i < NUM_REG; ++i) {
		int value;
		instr_file >> value;
		registers[i] = Reg_Rat(value, "R" + std::to_string(i));
	}

	instr_file.close();

	
	//debugging purposes
	//for (int i = 0; i < instructions.size(); ++i) {
	//	std::string op = Opcode(instructions[i].op);
	//	std::cout << op << " R" << instructions[i].rd << ", R" << instructions[i].rs << ", R" << instructions[i].rt << std::endl;
	//}

	//debugging
	/*std::cout << "\tRF\t\tRAT" << std::endl;
	for (int i = 0; i < NUM_REG; ++i) {
		std::cout << "R" << i << ":\t" << registers[i].value << "\t\t" << registers[i].Name_Resolver() << std::endl;
	}*/

	ReservationStation reservation_unit[ADD_SUB_RS + MUL_DIV_RS];
	//Create Reservation Unit of reservation stations
	bool no_instr = false; 
	for (int i = 0; i < ADD_SUB_RS+MUL_DIV_RS; ++i) {
		reservation_unit[i] = ReservationStation();
	}
	int instr_counter = 0;
	do {

	} while (!no_instr);

}
/*
return values of instr_counter meaning
-1:  instr_counter has completed all instructions
instr_counter: waiting for RS to become free or has incremented by 1

Pass all Instructions, may convert from vector to queue.
*/
int Issue(std::vector<Instruction>& instructions,
	ReservationStation res_unit[],
	Reg_Rat registers[], int instr_counter) {

	if (instructions.size() >= instr_counter) {
		return -1;
	}

	bool RS_free = false;
	int opcode = instructions[instr_counter].op;
	int rs_slot;
	//If add or sub loop through looking for free RS.
	if (opcode == 0 || opcode == 1) {
		for (int i = RS_Bounds.ADD_START; i < RS_Bounds.ADD_START; ++i) {
			if (!res_unit[i].busy) {
				rs_slot = i;
				++instr_counter;
				res_unit[i].op = opcode; //Will assign either add or sub
				RS_free = true;
				break;
			}
		}
		if (!RS_free) {
			return instr_counter;
		}
	}
	//If Mul or div loop through looking for free RS.
	else if (opcode == 2 || opcode == 3) {
		for (int i = RS_Bounds.MUL_START; i < RS_Bounds.MUL_END; i++) {
			if (!res_unit[i].busy) {
				rs_slot = i;
				++instr_counter;
				res_unit[i].op = opcode; //Will assign either Mul or Div
				RS_free = true;
				break;
			}
		}
		if (!RS_free) {
			return instr_counter;
		}
	}

	//Implement logic from page 180
	// Tackle RS 
	Instruction instr = instructions[instr_counter - 1];
	if (registers[instr.rs].rat == OPERAND_EMPTY) {
		res_unit[rs_slot].value1 = registers[instr.rs].value;
		res_unit[rs_slot].tag1 = OPERAND_READY;
	}
	else {
		res_unit[rs_slot].tag1 = registers[instr.rs].rat;
	}

	//Tackle Rd
	if (registers[instr.rt].rat == OPERAND_EMPTY) {
		res_unit[rs_slot].value2 = registers[instr.rt].value;
		res_unit[rs_slot].tag2 = OPERAND_READY;
	}
	else {
		res_unit[rs_slot].tag2 = registers[instr.rt].rat;
	}

	res_unit[rs_slot].busy = true;
	res_unit[rs_slot].issue_lat = 0;
	registers[instr.rd].rat = rs_slot;
	return instr_counter;

}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

