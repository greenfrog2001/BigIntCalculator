// Big Binary Integer class

#pragma once

#include "Convert.h"

class BigBinInt {
	public:
		static const int SIZE = 100; // Max size of array 
		int digits[SIZE] = {}; // Create array of max size and full of zeros
		int numSigDigits; // Number of significant digits 
		
		// Constructor with empty, represents 0
		BigBinInt () {
			numSigDigits = 1;
		}
		
		// Constructor with 2 parameters: an array and its length
		BigBinInt (int arr[], int arr_length) {
			if(arr_length > SIZE) {
				throw "Input array size out of range!";
			}
			else {
				int count = 0;
				for (int i = 0; i < arr_length; i++) {
					if (arr[i] != 0) {
						break;
					}
					count ++;
				}
				numSigDigits = arr_length - count;
				if (numSigDigits == 0) {
					digits[SIZE-1] = 0;
					numSigDigits = 1;
				}
				else {
					for (int i = 0; i < numSigDigits; i++) {
						if (arr[count + i] >= 2) {
							throw "Invalid digits input!";
						}
						digits[SIZE - numSigDigits + i] = arr[count + i];
					}
				}
			}
		}
		
		// Constructor with 1 parameter as an int
		BigBinInt (int n) {
			if (n < 0) {
	            throw "Invalid input";
	        } else if (n == 0) {
	            numSigDigits = 1;
	        } else {
	            int count = 0;
	            int index = SIZE - 1;
	            while (n > 0) {
	            	if (n % 10 >= 2) {
	            		throw "Invalid digits input!";
	            	}
	                digits[index] = n % 10;
	                n = n / 10;
	                count++;
	                index --;
	            }
	            numSigDigits = count;
	        }
		}
		
		// Constructor with 1 parameter as a char array (contains digits only)
		BigBinInt (char* str) {
			int count = 0;
			for (int i = 0; str[i] != '\0'; i++) {
				if (str[i] != '0') {
					break;
				}
				count ++;
			}
			numSigDigits = strlen(str) - count;
			if (numSigDigits == 0) {
				numSigDigits = 1;
				digits[SIZE-1] = 0;
			}
			else {
				for (int i = 0; i < numSigDigits; i++) {
					int char_digit = (int) str[count + i] - 48;
					if (char_digit >= 2 ) {
						throw "Invalid digits input!";
					}
					digits[SIZE - numSigDigits + i] = char_digit;
				}
			}
		}
		
		// Returns number of significant digits
		int getNumSigDigits () {
			return numSigDigits;
		}
		
		// Print out the representation of the number
		void repr() {
			if (numSigDigits == 1 && digits[SIZE-1] == 0) {
				printf("0\n");
			} else {
				for (int i = SIZE - numSigDigits; i < SIZE; i++) {
					printf("%d", digits[i]);
				}
				printf("\n");
			}
		}
		
		// Returns 1 if bigger, -1 if smaller, 0 if equal
		int compareTo (BigBinInt other) {
			if (numSigDigits > other.numSigDigits) {
				return 1;
			}
			else if (numSigDigits < other.numSigDigits) {
				return -1;
			}
			else {
				for (int i = SIZE - numSigDigits; i < SIZE; i++) {
					if (other.digits[i] < digits[i]) {
						return 1;
					}
					if (other.digits[i] > digits[i]) {
						return -1;
					}
				}
				return 0;
			}
		}
		
		// Returns sum of two 2 BigBinInts as a BigBinInt
		BigBinInt add(BigBinInt other) {
			int result[SIZE] = {};
	        int index = SIZE - 1;
	        int carry = 0;
	        while (index > 0) {
	        	int sum = digits[index] + other.digits[index] + carry;
	        	if (sum == 2) {
	        		result[index] = 0;
	            	carry = 1;
	            	index--;
	        	}
	        	else if (sum == 3) {
	        		result[index] = 1;
	        		carry = 1;
	        		index--;
				}
				else {
	            	carry = 0;
	            	result[index] = sum;
	            	index--;
	        	}
	        }
	        if (carry == 0) {
	            BigBinInt res = BigBinInt (result, SIZE);
	            return res;
	        }
			else {
	            throw "Over upperbound!";
        	}
		}
		
		// Returns the difference between 2 BigBinInts as a BigBinInt
		BigBinInt diff (BigBinInt other) {
			if (compareTo(other) == -1) {
				BigBinInt copy = BigBinInt (digits, SIZE);
				return other.diff(copy);
			}
			else if (compareTo(other) == 0) {
				BigBinInt res = BigBinInt();
				return res;
			}
			else {
				int result[SIZE] = {};
				int index = SIZE - 1;
				int carry = 0;
				while (index > 0) {
					int diff = digits[index] - other.digits[index] - carry;
					if (diff == -1) {
						result[index] = 1;
						carry = 1;
						index --;
					}
					else if (diff == -2) {
						result[index] = 0;
						carry = 1;
						index --;
					}
					else {
						carry = 0;
						result[index] = diff;
						index --;
					}
				}
				BigBinInt res = BigBinInt(result, SIZE);
				return res;
			}
		}
		
		// Helper method for multiplying two BigBinInts
		// Returns product of a BigBinInt with 0, 1 or 10 as a BigBinInt
		BigBinInt mul_digit(int n) {
			if (n == 0) {
				BigBinInt res = BigBinInt();
				return res;
			}
			if (n == 1) {
				BigBinInt res = BigBinInt(digits, SIZE);
				return res;
			}
			if (n == 10) {
				int res_digits[SIZE] = {};
				for (int i = 0; i < SIZE; i++) {
					res_digits[i] = digits[i];
				}
				for (int i = SIZE - numSigDigits; i < SIZE; i++) {
					res_digits[i-1] = res_digits[i];
				}
				res_digits[SIZE-1] = 0;
				BigBinInt res = BigBinInt(res_digits, SIZE);
				return res;
			}
		}
		
		// Returns product of two BigBinInts as a BigBinInt
		BigBinInt mul(BigBinInt other) {
			BigBinInt resBigBinInt = BigBinInt();
			for (int i = SIZE - 1; i > SIZE - numSigDigits -1; i--) {
				int mulBy = digits[i];
				BigBinInt otherProd = other.mul_digit(mulBy);
				otherProd.repr();
				for (int j = i+1; j < SIZE; j++) {
					otherProd = otherProd.mul_digit(10);
				}
				otherProd.repr();
				resBigBinInt = resBigBinInt.add(otherProd);
			}
			return resBigBinInt;
		}
};
