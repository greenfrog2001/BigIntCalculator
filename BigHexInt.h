// Big Hex Integer class

#pragma once

class BigHexInt {
	public:
		static const int SIZE = 100; // Max size of array 
		int digits[SIZE] = {}; // Array of max size and full of zeros that will contain the digits
		int numSigDigits; // Number of significant digits
		int converted_digits[SIZE] = {}; // int-converted digits array for calculating
		
		// Constructor with empty, represents 0
		BigHexInt () {
			numSigDigits = 1;
		}
		
		// Constructor with para as an array and its length
		BigHexInt (int arr[], int arr_length) {
			if(arr_length > SIZE) {
				printf("Wrong input!");
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
						int digit = arr[count + i];
						if (digit < 0 || (digit >= 10 && digit < 65) || digit > 70) {
							throw "Invalid input";
						}
						digits[SIZE - numSigDigits + i] = digit;
						if (digit >= 0 && digit < 10) {
							converted_digits[SIZE - numSigDigits + i] = digit;
						}
						else {
							converted_digits[SIZE - numSigDigits + i] = digit - 55;
						}
					}
				}
			}
		}
		
		// Constructor with para as a char array (contains digits and characters as ints)
		BigHexInt (char* str) {
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
					if ((int) str[count + i] > 47 && (int) str[count + i] < 58) {
						digits[SIZE - numSigDigits + i] = (int) str[count + i] - 48;
						converted_digits[SIZE - numSigDigits + i] = (int) str[count + i] - 48;
					}
					else if ((int) str[count + i] > 64 && (int) str[count + i] < 71) {
						digits[SIZE - numSigDigits + i] = (int) str[count + i];
						converted_digits[SIZE - numSigDigits + i] = (int) str[count + i] - 55;
					}
					else {
						throw "Invalid input";
					}
				}
			}
		}
		
		// Returns number of significant digits
		int getNumSigDigits () {
			return numSigDigits;
		}
		
		// print out the representation of the number
		void repr() {
			if (numSigDigits == 1 && digits[SIZE-1] == 0) {
				printf("0\n");
			} else {
				for (int i = SIZE - numSigDigits; i < SIZE; i++) {
					if (digits[i] >= 0 && digits[i] < 10) {
						printf("%d", digits[i]);
					}
					else {
						printf("%c", digits[i]);
					}
				}
				printf("\n");
			}
		}
		
		// print out the representation of the number with converted characters
		void convert_repr() {
			if (numSigDigits == 1 && digits[SIZE-1] == 0) {
				printf("0\n");
			} else {
				for (int i = SIZE - numSigDigits; i < SIZE; i++) {
						printf("%d\t", converted_digits[i]);
					}
				printf("\n");
			}
		}
//		
		// returns 1 if bigger, -1 if smaller, 0 if equal
		int compareTo (BigHexInt other) {
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
//		
		// returns sum of two 2 BigHexInts as a BigHexInt
		BigHexInt add(BigHexInt other) {
			int result[SIZE] = {};
	        int index = SIZE - 1;
	        int carry = 0;
	        while (index > 0) {
	        	int sum = converted_digits[index] + other.converted_digits[index] + carry;
	        	if (sum >= 16) {
	        		result[index] = sum - 16;
	            	carry = 1;
	            	index--;
	        	}
				else {
	            	carry = 0;
	            	result[index] = sum;
	            	index--;
	        	}
	        }
	        
	        for (int i = 0; i < SIZE; i++) {
	        	if (result[i] >= 10) {
	        		result[i] += 55;
				}
			}
	        
	        if (carry == 0) {
	            BigHexInt res = BigHexInt (result, SIZE);
	            return res;
	        }
			else {
	            printf("Over upperbound!");
        	}
		}
		
		BigHexInt diff (BigHexInt other) {
			if (compareTo(other) == -1) {
				printf("Negative result");
			}
			else if (compareTo(other) == 0) {
				BigHexInt res = BigHexInt();
				return res;
			}
			else {
				int result[SIZE] = {};
				int index = SIZE - 1;
				int carry = 0;
				while (index > 0) {
					int diff = converted_digits[index] - other.converted_digits[index] - carry;
					if (diff < 0) {
						result[index] = diff + 16;
						carry = 1;
						index --;
					}
					else {
						carry = 0;
						result[index] = diff;
						index --;
					}
				}
				
				for (int i = 0; i < SIZE; i++) {
		        	if (result[i] >= 10) {
		        		result[i] += 55;
					}
				}
				
				BigHexInt res = BigHexInt(result, SIZE);
				return res;
			}
		}
//		
//		// Helper method for multiplying two BigInts
//		// Returns product of a BigHexInt with an int digit as a BigHexInt
		BigHexInt mul_digit(int n) {
			int result[SIZE] = {};
			int index = SIZE - 1;
			int carry = 0;
			while (index >= 0) {
				int prod = converted_digits[index] * n + carry;
				if (prod >= 16) {
					result[index] = prod % 16;
					carry = prod / 16;
					index --;
				}
				else {
					carry = 0;
					result[index] = prod;
					index --;
				}
			}
			
			for (int i = 0; i < SIZE; i++) {
	        	if (result[i] >= 10) {
	        		result[i] += 55;
				}
			}
			
			if (carry == 0) {
				BigHexInt res = BigHexInt(result, SIZE);
				return res;
			}
			else {
				printf("Over upperbound!");
			}
		}
		
		// Returns product of two BigHexInts as a BigHexInt
		BigHexInt mul(BigHexInt other) {
			BigHexInt res = BigHexInt();
			for (int i = SIZE - 1; i > SIZE - numSigDigits -1; i--) {
				int mulBy = converted_digits[i];
				BigHexInt otherProd = other.mul_digit(mulBy);
				for (int j = i+1; j < SIZE; j++) {
					otherProd = otherProd.mul_digit(16);
				}
				res = res.add(otherProd);
			}
			return res;
		}
//		
//		BigInt divide_int (int divisor) {
//			int result[SIZE] = {};
//			int index = SIZE - numSigDigits;
//			int temp = digits[index];
//			while (temp < divisor) {
//				temp = temp * 10 + digits[++index];
//			}
//			// correct initial temp
//			int count = 0;
//			while (index < SIZE) {
//				result[index] = (temp / divisor);
//				temp = (temp % divisor) * 10 + digits[++index];
//				count ++;
//			}
//			
//			BigInt res = BigInt(result, SIZE);
//			return res;
//		}
//		
//		// mod_2(), isPositive() and last_digit() are helper methods for convertToBinary() method
//		int mod_2() {
//			int res = digits[SIZE-1] % 2;
//			return res;
//		}
//		
//		bool isPositive () {
//			BigInt zero = BigInt();
//			if (compareTo(zero) == 1) {
//				return true;
//			}
//			return false;
//		}
//		
//		int last_digit () {
//			int res = digits[SIZE-1];
//			return res;
//		}
};
