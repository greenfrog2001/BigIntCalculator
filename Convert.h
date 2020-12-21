// Convert BigInt to BinBinInt, BigHexInt and vice versa

#pragma once

#include "BigInt.h"
#include "BigBinInt.h"
#include "BigHexInt.h"

BigBinInt DecToBin (BigInt x) {
	int size = x.SIZE;
	int result[size] = {};
	int index = 0;
	BigInt copy = BigInt(x.digits, size); // copy of x

	do {
		result[index] = copy.remainder(2);
		copy = copy.divide_int(2);
		index++;
	} while (copy.isPositive());
	
	if (index > size) {
		printf("Over upperbound.\n");
	}
	else if (index != size) {
		for (int i = 0; i < index; i++) {
			result[size-1-i] = result[i];
			result[i] = 0;
		}
	}
	BigBinInt res = BigBinInt(result, size);
	return res;
}

BigHexInt DecToHex (BigInt x) {
	int size = x.SIZE;
	int result[size] = {};
	int index = 0;
	BigInt copy = BigInt (x.digits, size); // copy of x

	do {
		result[index] = copy.remainder(16);
		copy = copy.divide_int(16);
		index++;
	} while (copy.isPositive());
	
	if (index > size) {
		printf("Over upperbound.\n");
	}
	else if (index != size) {
		for (int i = 0; i < index; i++) {
			result[size-1-i] = result[i];
			result[i] = 0;
		}
	}
	
	for (int i = 0; i < size; i++) {
    	if (result[i] >= 10) {
    		result[i] += 55;
		}
	}
	
	BigHexInt res = BigHexInt(result, size);
	return res;
}

BigInt BinToDec (BigBinInt x) {
	int size = x.SIZE;
	BigInt copy = BigInt(x.digits, size);
	BigInt res = BigInt();
	BigInt base = BigInt("1");
	while (copy.isPositive()) {
		res = res.add(base.mul_digit(copy.remainder(10)));
		copy = copy.divide_int(10);
		base = base.mul_digit(2);
	}
	return res;
}

BigInt HexToDec (BigHexInt x) {
	int size = x.SIZE;
	int numSigDigits = x.getNumSigDigits();
	BigInt res = BigInt();
	for (int i = 0; i < numSigDigits; i++) {
		int sixteens = 1;
		for (int j = 0; j < i; j++) {
			sixteens *= 16;
		}
		BigInt mulBy = BigInt(sixteens);
		res = res.add(mulBy.mul_digit(x.converted_digits[size-1-i]));
	}
	return res;
}

BigHexInt BinToHex (BigBinInt x) {
	BigHexInt res = DecToHex(BinToDec(x));
	return res;
}

BigBinInt HexToBin (BigHexInt x) {
	BigBinInt res = DecToBin(HexToDec(x));
	return res;
}
