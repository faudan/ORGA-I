#!/usr/bin/python

import sys
import os
import re

instruction_length = 1
starting_mem_value = 0x00
# starting_mem_value = 0x60

type2Rinstructions = ['mov', 'add', 'sub', 'and', 'or']
type1Rinstructions = ['inc', 'dec', 'set', 'shift']
typeNoPinstructions = ['halt']
typeMEMinstructions = ['load', 'store']
typeJMPinstructions = ['jmp', 'je', 'jn']
typeDWinstructions = ['dw']

instruction2opcode = {
	'add': 0x0,
	'sub': 0x1,
	'and': 0x2,
	'or': 0x3,
	'store': 0x4,
	'load': 0x5,
	'halt': 0x6,
	'mov': 0x7,
	'jmp': 0x8,
	'je': 0x9,
	'jn': 0xA,
	'libre': 0xB,
	'inc': 0xC,
	'dec': 0xD,
	'set': 0xE,
	'shift': 0xF,
}

reservedwords = type2Rinstructions + type1Rinstructions + typeNoPinstructions + typeMEMinstructions + typeJMPinstructions + typeDWinstructions

labels = dict()

def isinmm(word):
	return (word[0] in map(str, range(10)))

def isreg(word):
	return (word[0] == '$') or (word in map(str, range(32)))

def isdirective(line):
	return line[0] == '.'

def getlinelabelandinstruction(line):
	if ";" in line:
		line = line.split(';')[0]

	label,sep,instruction = map(str.strip, line.partition(':'))

	if (sep == '') and (instruction == ''):
		label,instruction = instruction,label
	label = label.lower()
	return (label, instruction)


def definelabels(linesplittedcode):
	global labels

	i = starting_mem_value - instruction_length
	for line in linesplittedcode:
		# Saltear lineas en blanco
		if line.strip() == '':
			continue
		i = i + instruction_length

		label, instruction = getlinelabelandinstruction(line)

		if label != '':
			assert(not (label in reservedwords))
			assert(not (label[0] in map(str, range(10))))
			labels[label] = i

		if instruction == '':
			i = i - instruction_length

def micro_assembler(startaddr, code):
	global labels
	labels = dict()
	lines = map(str.strip, code.split('\n'))

	# Primera pasada para buscar las etiquetas
	definelabels(lines)

	# Segunda pasada para  ensamblar
	i = -1
	i = starting_mem_value - instruction_length
	memory = {}
	for line in lines:
		# Saltear lineas en blanco
		if line.strip() == '':
			continue
		i = i + instruction_length

		label, instruction = getlinelabelandinstruction(line)
		if instruction == '':
			i = i - instruction_length
			continue

		# print instruction
		if instruction.count(" "):
			operation, operands = map(str.lower, re.split('\s+', instruction, 1))
			operands = map(str.strip, operands.split(','))
		else:
			operation, operands = instruction.lower(), []

		# print operation, operands
		if operation in type2Rinstructions:
			reg_d = int(operands[0][1])
			reg_s = int(operands[1][1])
			opcode = instruction2opcode[operation]

			memory[i] = "{:04b}{:03b}{:03b}00 // {}".format(opcode, reg_d, reg_s, line)

		elif operation in typeMEMinstructions:
			reg = int(operands[0][1])
			addr = int(operands[1], 16)
			opcode = instruction2opcode[operation]

			memory[i] = "{:04b}{:03b}{:05b} // {}".format(opcode, reg, addr, line)

		elif operation in typeJMPinstructions:
			addr = labels[operands[0]]
			opcode = instruction2opcode[operation]

			memory[i] = "{:04b}{:08b} // {}".format(opcode, addr, line)

		elif operation in type1Rinstructions:
			reg = int(operands[0][1])
			opcode = instruction2opcode[operation]

			memory[i] = "{:04b}{:03b}00000 // {}".format(opcode, reg, line)

		elif operation in typeNoPinstructions:
			opcode = instruction2opcode[operation]

			memory[i] = "{:04b}00000000 // {}".format(opcode, line)

		elif operation in typeDWinstructions:
			val = int(operands[0], 16)

			memory[i] = "{:012b} // {}".format(val, line)
		else:
			assert(False)

	print "Valores de las etiquetas:"
	for k,v in labels.iteritems():
		print k, "0x{:02X}".format(v)

	print "\nContenido de las posiciones de memoria:"

	for k in sorted(memory.keys()):
		print "{:02X}: 0x{:03X} ; ".format(k, int(memory[k].split(" ")[0],2)), #memory[k].split("//")[1],
		print memory[k].split(" ")[0][0:4],
		print memory[k].split(" ")[0][4:8],
		print memory[k].split(" ")[0][8:12], "-",
		print memory[k].split("//")[1]

	out = "v2.0 raw\n"
	for k in sorted(memory.keys()):
		out += "{:03X} ".format(int(memory[k].split(" ")[0],2))

	f_out = open(filename.split(".")[0] + ".mem", 'w')
	f_out.write(out)
	f_out.close()

	print "\n\nFormato para logisim:"
	print out

if __name__ == '__main__':
	if len(sys.argv) != 2:
		print "Uso: ensamblador.py archivo.asm"
		exit(1)

	filename = sys.argv[1]

	if not os.path.isfile(filename):
		print "No se encuentra el archivo {}".format(filename)
		exit(1)

	f = open(filename, 'r')
	filecontent = f.read()
	f.close()

	micro_assembler(0, filecontent)
