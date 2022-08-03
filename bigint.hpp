/*
    DPPL_ASSIGNMENT-1
    BT20CSE105
    BT20CSE119
    BT20CSE122
*/
#include <iostream>
#include <string>

using namespace std;

/**
 * @brief
 * BigInt Class
 */
class bigint
{

private:
    string num;                     // actual inputed string
    int numEle = 0;                 // total number of elements in the array
    int sign = 0;                   // 0 -> +ve , 1 -> -ve
    int digits = 0;                 // total number of digits in the BigInt
    unsigned long long int *bigArr; // BigInt array for easy calulation

public:
    bigint(string bigNum);
    ~bigint() {}
    unsigned long long int *StringToArray(string num, int elements, int size);
    int numOfDigit(unsigned long long int num);
    string add(unsigned long long int *arr1, int digits1, int numEle1, unsigned long long int *arr2, int digits2, int numEle2);
    string sub(unsigned long long int *arr1, int digits1, int numEle1, unsigned long long int *arr2, int digits2, int numEle2);
    /**
     * @brief
     * This function returns the signed string of the corresponding bigint object.
     * @return string
     */
    string printBigInt()
    {
        string strTemp = num;
        if (sign == 1)
        {
            strTemp.insert(0, "-"); // adding - sign if sign bit is 1
        }
        return strTemp;
    }

    /**
     * @brief
     * Using operator overloading we overloaded + operator for the addition of two bigint. This function checks the sign of both the big integers and decides according to what sign the final big integer have and what operations to perform.
     * @return bigint
     */
    bigint operator+(bigint const &num1)
    {
        if (num1.sign == sign)
        { // if both number have the same sign we will do addition
            if ((digits > num1.digits) || (num.compare(num1.num) > 0 && (digits >= num1.digits)))
            {
                // checking which number is greater to send it first in the function for easy calculation
                bigint num3(add(bigArr, digits, numEle, num1.bigArr, num1.digits, num1.numEle));
                num3.sign = num1.sign;
                return num3;
            }
            else
            {
                bigint num3(add(num1.bigArr, num1.digits, num1.numEle, bigArr, digits, numEle));
                num3.sign = num1.sign;
                return num3;
            }
        }
        else
        { // if both number have the opposite sign we will do substraction
            if ((digits > num1.digits) || (num.compare(num1.num) > 0 && (digits >= num1.digits)))
            {
                // checking which number is greater to send it first in the function for easy calculation
                bigint num3(sub(bigArr, digits, numEle, num1.bigArr, num1.digits, num1.numEle));
                num3.sign = sign;
                return num3;
            }
            else
            {
                bigint num3(sub(num1.bigArr, num1.digits, num1.numEle, bigArr, digits, numEle));
                num3.sign = num1.sign;
                return num3;
            }
        }
    }

    /**
     * @brief
     * Using operator overloading we overloaded - operator for the subtraction of two bigint. This function checks the sign of both the big integers and decides according to what sign the final big integer have and what operations to perform.
     * @return bigint
     */
    bigint operator-(bigint const &num1)
    {
        if (num1.sign == sign)
        { // if both number have the same sign we will do substraction
            if ((digits > num1.digits) || (num.compare(num1.num) > 0 && (digits >= num1.digits)))
            {
                // checking which number is greater to send it first in the function for easy calculation
                bigint num3(sub(bigArr, digits, numEle, num1.bigArr, num1.digits, num1.numEle));
                num3.sign = sign;
                return num3;
            }
            else
            {
                bigint num3(sub(num1.bigArr, num1.digits, num1.numEle, bigArr, digits, numEle));
                if (num1.sign == 1)
                {
                    num3.sign = 0;
                }
                else
                {
                    num3.sign = 1;
                }
                return num3;
            }
        }
        else
        { // if both number have the opposite sign we will do addition
            if ((digits > num1.digits) || (num.compare(num1.num) > 0 && (digits >= num1.digits)))
            {
                // checking which number is greater to send it first in the function for easy calculation
                bigint num3(add(bigArr, digits, numEle, num1.bigArr, num1.digits, num1.numEle));
                num3.sign = sign;
                return num3;
            }
            else
            {
                bigint num3(add(num1.bigArr, num1.digits, num1.numEle, bigArr, digits, numEle));
                num3.sign = sign;
                return num3;
            }
        }
    }
};

/**
 * @brief
 * Initialises BigInt Object. It initialises all the variables in the object and converts the input string to a dynamic array.
 */
bigint::bigint(string bigNum)
{

    // Saving String
    num = bigNum;

    // Assigning Sign Bit
    if (num[0] == '-')
    {
        sign = 1;
        num.erase(num.begin());
    }
    else
    {
        sign = 0;
    }

    // Number of digits
    digits = num.length();

    // Number of elements in array
    if (digits % 17 == 0)
    {
        numEle = digits / 17;
    }
    else
    {
        numEle = (digits / 17) + 1;
    }

    // Array
    bigArr = StringToArray(num, numEle, digits);
}

/**
 * @brief
 * This function is used to convert the given string into a dynamic array. The number of elements the dynamic memory should have is stored in int elements. And the total number of digits in the string is stored in int size. Each element of the array contains 17 digits. Except for the 1st element if size%17!=0.
 * @return unsigned long long int *
 */
unsigned long long int *bigint::StringToArray(string num, int elements, int size)
{

    unsigned long long int *arr = new unsigned long long int[elements];
    int temp = size;
    for (int i = elements - 1; i >= 0; i--)
    {
        if (temp < 17)
        {
            arr[i] = stoll(num.substr(0, temp));
        }
        else
        {
            arr[i] = stoll(num.substr(temp - 17, 17));
        }
        temp = temp - 17;
    }
    return arr;
}

/**
 * @brief
 * This function is used to find the number of digits in an integer recursively.
 * @return int
 */
int bigint::numOfDigit(unsigned long long int num)
{
    if (num / 10 == 0)
        return 1;
    return 1 + numOfDigit(num / 10);
}

/**
 * @brief
 * This function essentially has the logic for addition. We pass 2 dynamic arrays that are to be added. Then we perform the addition of the array and loop through the elements until one of the arrays runs out of elements to add.
 * @return string
 */
string bigint::add(unsigned long long int *arr1, int digits1, int numEle1, unsigned long long int *arr2, int digits2, int numEle2)
{

    string str;
    string strTemp;
    int carry = 0;
    int i = 0, j = numEle1 - 1;

    for (i = numEle2 - 1; i >= 0; i--)
    {
        unsigned long long int tempNum = arr1[j] + arr2[i] + carry;
        carry = 0;

        if (numOfDigit(tempNum) == 18)
        {
            carry = 1;
            tempNum = tempNum - 100000000000000000;
        }

        if ((numOfDigit(tempNum) == 17) || j == 0)
        {
            string strTemp = to_string(tempNum);
            str.insert(0, strTemp);
        }
        else
        {
            string strTemp = to_string(tempNum);
            str.insert(0, strTemp);
            for (int k = 0; k < 17 - numOfDigit(tempNum); k++)
            {
                str.insert(0, "0");
            }
        }
        j--;
    }

    if (carry == 1)
    {
        for (j; j >= 0; j--)
        {
            unsigned long long int tempNum = arr1[j] + carry;
            carry = 0;

            if (numOfDigit(tempNum) == 18)
            {
                carry = 1;
                tempNum = tempNum - 100000000000000000;
            }

            if ((numOfDigit(tempNum) == 17) || j == 0)
            {
                string strTemp = to_string(tempNum);
                str.insert(0, strTemp);
            }
            else
            {
                string strTemp = to_string(tempNum);
                str.insert(0, strTemp);
                for (int k = 0; k < 17 - numOfDigit(tempNum); k++)
                {
                    str.insert(0, "0");
                }
            }
        }
    }
    else
    {
        for (j; j >= 0; j--)
        {
            if ((numOfDigit(arr1[j]) == 17) || j == 0)
            {
                string strTemp = to_string(arr1[j]);
                str.insert(0, strTemp);
            }
            else
            {
                string strTemp = to_string(arr1[j]);
                str.insert(0, strTemp);
                for (int k = 0; k <= 17 - numOfDigit(arr1[j]); k++)
                {
                    str.insert(0, "0");
                }
            }
        }
    }

    return str;
}

/**
 * @brief
 * Same as add. This function essentially has the logic for subtraction. We pass 2 dynamic arrays that are to be subtracted. Then we perform the subtraction of the array and loop through the elements until one of the arrays runs out of elements.
 * @return string
 */
string bigint::sub(unsigned long long int *arr1, int digits1, int numEle1, unsigned long long int *arr2, int digits2, int numEle2)
{

    string str;
    string strTemp;
    int borrow = 0;
    int i = 0, j = numEle1 - 1;

    for (i = numEle2 - 1; i >= 0; i--)
    {
        unsigned long long int tempNum = 0;

        if (arr1[j] >= arr2[i])
        {
            tempNum = arr1[j] - arr2[i] - borrow;
            borrow = 0;
        }
        else
        {
            tempNum = 100000000000000000 + arr1[j] - borrow - arr2[i];
            borrow = 1;
        }

        if ((numOfDigit(tempNum) == 17) || j == 0)
        {
            string strTemp = to_string(tempNum);
            str.insert(0, strTemp);
        }
        else
        {
            for (int k = 0; k < 17 - numOfDigit(tempNum); k++)
            {
                str.insert(0, "0");
            }
            string strTemp = to_string(tempNum);
            str.insert(0, strTemp);
        }

        j--;
    }

    if (borrow == 1)
    {
        for (j; j >= 0; j--)
        {
            unsigned long long int tempNum = arr1[j] - borrow;
            borrow = 0;

            if ((numOfDigit(tempNum) == 17) || j == 0)
            {
                string strTemp = to_string(tempNum);
                str.insert(0, strTemp);
            }
            else
            {
                for (int k = 0; k < 17 - numOfDigit(tempNum); k++)
                {
                    str.insert(0, "0");
                }
                string strTemp = to_string(tempNum);
                str.insert(0, strTemp);
            }
        }
    }
    else
    {
        for (j; j >= 0; j--)
        {
            if ((numOfDigit(arr1[j]) == 17) || j == 0)
            {
                string strTemp = to_string(arr1[j]);
                str.insert(0, strTemp);
            }
            else
            {
                for (int k = 0; k <= 17 - numOfDigit(arr1[j]); k++)
                {
                    str.insert(0, "0");
                }
                string strTemp = to_string(arr1[j]);
                str.insert(0, strTemp);
            }
        }
    }
    return str;
}