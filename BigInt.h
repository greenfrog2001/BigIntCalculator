// Big Integer class

#pragma once

class BigInt {
	public:
		static const int SIZE = 1000; // Max size of array 
		int digits[SIZE] = {}; // Create array of max size and full of zeros
		int numSigDigits; // Number of significant digits
		bool isNegative = false; 
		
		// Constructor with empty, represents 0
		BigInt () {
			numSigDigits = 1;
		}
		
		// Constructor with 2 parameters: an array, its length and an optional 
		// parameter is_negative being set default to false 
		BigInt (int arr[], int arr_length, bool is_negative=false) {
			if(arr_length > SIZE) {
				throw "Input array size out of range!";
			}
			else {
				isNegative = is_negative;
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
			if (n == 0) {
	            numSigDigits = 1;
	        } else {
	        	if (n < 0) {
	        		isNegative = true;
	        		n *= -1;
				}
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
			if (str[count] == '-') {
				isNegative = true;
				count++;
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
		
		// Print out the representation of the number
		void repr() {
			if (numSigDigits == 1 && digits[SIZE-1] == 0) {
				printf("0");
			} else {
				if (isNegative) {
					printf("-");
				}
				for (int i = SIZE - numSigDigits; i < SIZE; i++) {
					printf("%d", digits[i]);
				}
			}
		}
		
		// Returns 1 if absolute value is bigger, -1 if smaller, 0 if equal
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
		
		// Returns sum of two 2 BigInts as a BigInt
		BigInt add(BigInt other) {
			
			if (isNegative && other.isNegative) {
				BigInt copy1 = BigInt(digits, SIZE);
				BigInt copy2 = BigInt(digits, SIZE);
				BigInt rev_res = copy1.add(copy2);
				BigInt res = BigInt(rev_res.digits, SIZE, true);
				return res;
			}
			else if (isNegative) {
				BigInt copy1 = BigInt(digits, SIZE);
				BigInt rev_res = copy1.diff(other);
				if (compareTo(other) > 0) {
					BigInt res = BigInt(rev_res.digits, SIZE, true);
					return res;
				}
				else if (compareTo(other) == 0) {
					BigInt res = BigInt();
					return res;
				}
				else {
					return rev_res;
				}
			}
			else if (other.isNegative) {
				BigInt copy2 = BigInt(other.digits, SIZE);
				BigInt rev_res = diff(copy2);
				if (compareTo(other) > 0) {
					return rev_res;
				}
				else if (compareTo(other) == 0) {
					BigInt res = BigInt();
					return res;
				}
				else {
					BigInt res = BigInt(rev_res.digits, SIZE, true);
					return res;
				}
			}
			else {
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
		}
		
		// Returns the difference between 2 BigInts as a BigInt
		BigInt diff (BigInt other) {
			if (compareTo(other) == -1) {
				BigInt copy = BigInt(digits, SIZE);
				return other.diff(copy);
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
		
		// Returns the subtraction of this BigInt to other BigInt
		BigInt subtract (BigInt other) {
			BigInt res;
			if (compareTo(other) == 0) {
				res = BigInt();
			}
			else if (isNegative && other.isNegative) {
				if (compareTo(other) > 0) {
					res = BigInt(diff(other).digits, SIZE, true);
				}
				else {
					res = BigInt(diff(other).digits, SIZE);
				}
			}
			else if ((!isNegative) && other.isNegative) {
				BigInt copy2 = BigInt(other.digits, SIZE);	
				res = BigInt(add(copy2).digits, SIZE);
			}
			else if (isNegative && (!other.isNegative)) {
				BigInt copy1 = BigInt(digits, SIZE);
				res = BigInt(copy1.add(other).digits, SIZE, true);
			}
			else {
				if (compareTo(other) > 0) {
					res = BigInt(diff(other).digits, SIZE);
				}
				else {
					res = BigInt(diff(other).digits, SIZE, true);
				}
			}
			BigInt resBigInt = BigInt (res.digits, SIZE, res.isNegative);
			return resBigInt;
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
			if ((isNegative && other.isNegative) || ( (!isNegative) && (!other.isNegative) ) ) {
				return resBigInt;
			}
			else {
				BigInt res = BigInt(resBigInt.digits, SIZE, true);
				return res;
			}	
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
		// Returns true if > 0, false if < 0
		bool isPositive () {
			BigInt zero = BigInt();
			if (isNegative || compareTo(zero) == 0) {
				return false;
			}
			return true;
		}
		
		// Helper method for remainder() method
		// Returns a BigInt as an int value
		// Note that this method applies only for positive big int
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
		// Returns the remainder when dividing BigInt to an int n
		// Note that this method applies only for positive big int
		int remainder (int n) {
			BigInt res = diff(divide_int(n).mul_digit(n));
			int resInt = res.convertToInt();
			return resInt;
		}
};
