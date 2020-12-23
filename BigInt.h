// Big Integer class

#pragma once

class BigInt {
	public:
		static const int SIZE = 100; // Max size of array 
		int digits[SIZE] = {}; // Create array of max size and full of zeros
		int numSigDigits; // Number of significant digits 
		
		// Constructor with empty, represents 0
		BigInt () {
			numSigDigits = 1;
		}
		
		// Constructor with 2 parameters: an array and its length
		BigInt (int arr[], int arr_length) {
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
						if (arr[count + i] >= 10) {
							throw "Invalid digits input!";
						}
						digits[SIZE - numSigDigits + i] = arr[count + i];
					}
				}
			}
		}
		
		// Constructor with 1 parameter as an int
		BigInt (int n) {
			if (n < 0) {
	            throw "Invalid input";
	        } else if (n == 0) {
	            numSigDigits = 1;
	        } else {
	            int count = 0;
	            int index = SIZE - 1;
	            while (n > 0) {
	                digits[index] = n % 10;
	                n = n / 10;
	                count++;
	                index --;
	            }
	            numSigDigits = count;
	        }
		}
		
		// Constructor with 1 parameter as a char array (contains digits only)
		BigInt (char* str) {
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
					digits[SIZE - numSigDigits + i] = (int) str[count + i] - 48;
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
					printf("%d", digits[i]);
				}
				printf("\n");
			}
		}
		
		// returns 1 if bigger, -1 if smaller, 0 if equal
		int compareTo (BigInt other) {
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
		
		// returns sum of two 2 BigInts as a BigInt
		BigInt add(BigInt other) {
			int result[SIZE] = {};
	        int index = SIZE - 1;
	        int carry = 0;
	        while (index > 0) {
	        	int sum = digits[index] + other.digits[index] + carry;
	        	if (sum >= 10) {
	        		result[index] = sum - 10;
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
	            BigInt res = BigInt (result, SIZE);
	            return res;
	        }
			else {
	            throw "Over upperbound!";
        	}
		}
		
		// returns the difference between 2 BigInts as a BigInt
		BigInt diff (BigInt other) {
			if (compareTo(other) == -1) {
				throw "Negative result";
			}
			else if (compareTo(other) == 0) {
				BigInt res = BigInt();
				return res;
			}
			else {
				int result[SIZE] = {};
				int index = SIZE - 1;
				int carry = 0;
				while (index > 0) {
					int diff = digits[index] - other.digits[index] - carry;
					if (diff < 0) {
						result[index] = diff + 10;
						carry = 1;
						index --;
					}
					else {
						carry = 0;
						result[index] = diff;
						index --;
					}
				}
				BigInt resBigInt = BigInt(result, SIZE);
				return resBigInt;
			}
		}
		
		// Helper method for multiplying two BigInts
		// Returns product of a BigInt with an int as a BigInt
		BigInt mul_digit(int n) {
			int result[SIZE] = {};
			int index = SIZE - 1;
			int carry = 0;
			while (index >= 0) {
				int prod = digits[index] * n + carry;
				if (prod >= 10) {
					result[index] = prod % 10;
					carry = prod / 10;
					index --;
				}
				else {
					carry = 0;
					result[index] = prod;
					index --;
				}
			}
			if (carry == 0) {
				BigInt res = BigInt(result, SIZE);
				return res;
			}
			else {
				throw "Over upperbound!";
			}
		}
		
		// Returns product of two BigInts as a BigInt
		BigInt mul(BigInt other) {
			BigInt resBigInt = BigInt();
			for (int i = SIZE - 1; i > SIZE - numSigDigits -1; i--) {
				int mulBy = digits[i];
				BigInt otherProd = other.mul_digit(mulBy);
				for (int j = i+1; j < SIZE; j++) {
					otherProd = otherProd.mul_digit(10);
				}
				resBigInt = resBigInt.add(otherProd);
			}
			return resBigInt;
		}
		
		// Helper method for remainder() method
		BigInt divide_int (int divisor) {
			int result[SIZE] = {};
			int index = SIZE - numSigDigits;
			int temp = digits[index];
			while (temp < divisor) {
				temp = temp * 10 + digits[++index];
			}
			int count = 0;
			while (index < SIZE) {
				result[index] = (temp / divisor);
				temp = (temp % divisor) * 10 + digits[++index];
				count ++;
			}
			
			BigInt res = BigInt(result, SIZE);
			return res;
		}
		
		// Helper method for converting methods		
		// returns true if > 0, false if < 0
		bool isPositive () {
			BigInt zero = BigInt();
			if (compareTo(zero) == 1) {
				return true;
			}
			return false;
		}
		
		// Helper method for remainder() method
		// returns a BigInt as an int value
		int convertToInt () {
			int res = 0;
			for (int i = 0; i < numSigDigits; i++) {
				int tens = 1;
				for (int j = 0; j < i; j ++) {
					tens *= 10;
				}
				res += (digits[SIZE-1-i] * tens);
			}
			return res;
		}
		
		// Helper method for DecToHex method
		// returns the remainder when dividing BigInt to an int n
		int remainder (int n) {
			BigInt res = diff(divide_int(n).mul_digit(n));
			int resInt = res.convertToInt();
			return resInt;
		}
};
