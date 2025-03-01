#include <iostream>
//For Sleep
#include <Windows.h>
//For to_string
#include <string>
//For setprecision
#include <iomanip>
//Program adapted from GeeksForGeeks at https://www.geeksforgeeks.org/find-root-of-a-number-using-newtons-method/ and https://www.geeksforgeeks.org/find-square-root-number-upto-given-precision-using-binary-search/
//Example of Newton's Method https://www.youtube.com/watch?v=r0WV2Kcv6H0
// 
// n is the number to find the root of and t is the tolerance limit.
double newtonRoot(double n, double t, int* newtonCount);
//g is the previous guess.
double newtonAnyRoot(double k, double t, int* newtonCount, double n);
double newtonRootRecursive(double n, double t, double g);

double binarySearch(double n, double t, int* binaryCount);

int main()
{
	std::string choice;
	double n;
	double t;
	double root = 0;
	double power = 0;
	double binRoot = 0;
	int newtonCount;
	int binaryCount;
	while (true) {
		bool imaginary = false;
		bool zero = false;
		std::cout << "Enter 1 to find the square root of a number.\n";
		std::cout << "Enter 2 to find the nth root of a number.\n";
		std::cout << "Enter 3 to quit.\n";
		std::cin >> choice;
		if (choice == "1") {
			std::cout << "Please enter the number that you want to find the square root of: ";
			std::cin >> n;
			if (n < 0) {
				imaginary = true;
				n = abs(n);
			}
			std::cout << "Please enter the level of tolerance for the root: ";
			std::cin >> t;
			if (n == 0 || t == 0) {
				zero = true;
			}
			if (zero) {
				std::cout << std::endl << "Because zero will not resolve, it will not be calculated." << std::endl << std::endl;
			}
			else {
				root = newtonRoot(n, t, &newtonCount);
				binRoot = binarySearch(n, t, &binaryCount);
			}
			if (imaginary) {
				std::cout << std::endl << "Newton root: " + std::to_string(root) + " * i" << std::endl;
				std::cout << "Binary Search: " + std::to_string(binRoot) + " * i" << std::endl;
				std::cout << "C++ root:    " + std::to_string(sqrt(n)) + " * i" << std::endl << std::endl;
			}
			else if (!zero) {
				std::cout << std::endl << "Newton root: " + std::to_string(root) + ", Count: " + std::to_string(newtonCount) << std::endl;
				std::cout << "Binary Search: " + std::to_string(binRoot) + ", Count: " + std::to_string(binaryCount) << std::endl;
				std::cout << "C++ root:    " + std::to_string(sqrt(n)) << std::endl << std::endl;
			}
		}
		else if (choice == "2") {
			std::cout << "Please enter the degree of the root you want to find: ";
			std::cin >> power;
			std::cout << "Please enter the number that you want to find the square root of: ";
			std::cin >> n;
			if (n < 0) {
				imaginary = true;
				n = abs(n);
			}
			std::cout << "Please enter the level of tolerance for the root: ";
			std::cin >> t;
			if (n == 0 || t == 0) {
				zero = true;
			}
			if (zero) {
				std::cout << std::endl << "Because zero will not resolve, it will not be calculated." << std::endl << std::endl;
			}
			else {
				root = newtonAnyRoot(n, t, &newtonCount, power);
			}
			if (imaginary) {
				std::cout << std::endl << "a ^ 1 / " + std::to_string(power) + "th root: " + std::to_string(root) + " * i" << std::endl;
				std::cout << "C++ root:    " + std::to_string(pow(n, 1.0 / power)) + " * i" << std::endl << std::endl;
			}
			else if (!zero) {
				std::cout << std::endl << "a ^ 1 / " + std::to_string(power) + "th root: " + std::to_string(root) << std::endl;
				std::cout << "C++ root:    " + std::to_string(pow(n, 1.0 / power)) << std::endl << std::endl;
			}
		}
		else if (choice == "3") {
			std::cout << std::endl << "Goodbye!" << std::endl;
			Sleep(1000);
			return 0;
		}
		else {
			std::cout << "Choice was not entered correctly. Please try again.\n";
		}
	}
	return 0;
}

double newtonRoot(double n, double t, int* newtonCount) {
	double x = n;
	double root;
	int count = 0;

	while (true) {
		count++;
		root = 0.5 * (x + (n / x));
		if (std::abs(root - x) < t) {
			break;
		}
		x = root;
	}
	*newtonCount = count;
	return root;
}

double newtonAnyRoot(double n, double t, int* newtonCount, double power) {
	double x = n;
	double root;
	int count = 0;
	double powerReciprocal = 1 / n;
	while (true) {
		count++;
		root = 1 / power * (x * (power - 1) + n / (pow(x, power - 1)));
		if (std::abs(root - x) < t) {
			break;
		}
		x = root;
	}
	*newtonCount = count;
	return root;
}

double newtonRootRecursive(double n, double t, double g) {
	if (g == 0) {
		g = n / 2;
	}
	double next = (g + n / g) / 2;
	if (abs(g - next) <= t) {
		return next;
	}
	else {
		return newtonRootRecursive(n, t, next);
	}
}

double binarySearch(double n, double t, int* binaryCount) {
	long long int start = 0, end = n;
	long long int mid;
	int precision = 0;
	int count = 0;

	//Translates tolerance to precision
	while (t < 1) {
		t *= 10;
		precision += 1;
	}

	// variable to store the answer
	double ans = 0;

	// for computing integral part
	// of square root of number
	while (start <= end) {
		mid = (start + end) / 2;
		count++;
		if (mid * mid == n) {
			ans = mid;
			break;
		}

		// incrementing start if integral
		// part lies on right side of the mid
		if (mid * mid < n) {
			start = mid + 1;
			ans = mid;
		}

		// decrementing end if integral part
		// lies on the left side of the mid
		else {
			end = mid - 1;
		}
	}

	// For computing the fractional part
	// of square root upto given precision
	double increment = 0.1;
	for (int i = 0; i < precision; i++) {
		while (ans * ans <= n) {
			ans += increment;
		}

		// loop terminates when ans * ans > number
		ans = ans - increment;
		increment = increment / 10;
	}
	*binaryCount = count;
	return ans;
}

// double binarySearch(double x, double t, int* binaryCount) {
//	long left = 0;
//	long right = x;
//
//	if (x < 2) {
//		return x;
//	}
//	while (left < right) {
//		long mid = left + ((right - left) / 2);
//
//		if (mid * mid == x) {
//			return (int)mid;
//
//		}
//		else if (mid * mid < x) {
//			left = mid + 1;
//		}
//		else {
//			right = mid;
//		}
//	}
//	*binaryCount = 0;
//	return (double)(left - 1);
//}