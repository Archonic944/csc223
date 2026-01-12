# Big Integer Notes - Pages 35-44

## The Subtraction Algorithm

To subtract, we rely on the algebraic relationship:

$$a - b = a + (-b)$$

Prototypes for both + and - operators appear in bigint.h.

We toggle the sign in the subtraction operator based on the output. It checks each case for positive and negative values. We always subtract with the bigger number in the `a` paramter and do this using one-deep recursion.

## Study Questions

1. Describe test data for the calculator program for testing addition
and subtraction. Give an explanation for each data set describing
its importance.

We will need to test the following cases:

- Adding two positive numbers
- Adding two negative numbers
- Adding a positive and a negative number where the positive number is larger
- Adding a positive and a negative number where the negative number is larger
- Subtracting two positive numbers where the first is larger
- Subtracting two positive numbers where the second is larger
- Subtracting two negative numbers where the first is larger
- Subtracting two negative numbers where the second is larger
- Subtracting a positive number from a negative number
- Subtracting a negative number from a positive number

2. Write functions (for prefix operators) operator ++ and operator --
similar to the corresponding integer functions. Call the addition and
subtraction functions as needed.

```cpp
bigint& bigint::operator++() {
    *this = *this + BigInt(1);
    return *this;
}
bigint& bigint::operator--() {
    *this = *this - BigInt(1);
    return *this;
}
```

3. Write functions operator ++ and operator -- directly (i.e., without using
your addition and subtraction functions). What is gained or lost in
terms of time efficiency?

```cpp
bigint& bigint::operator++() {
    if (myIsNegative) {
        // -X + 1 = -(X - 1). Decrement magnitude.
        int k = 0;
        while (myDigits[k] == '0') {
            myDigits[k] = '9';
            k++;
        }
        myDigits[k]--;
        // Remove leading zero if necessary
        if (myDigits[k] == '0' && k == myDigits.size() - 1 && myDigits.size() > 1) {
            myDigits.pop_back();
        }
        // Handle -1 + 1 = 0
        if (myDigits.size() == 1 && myDigits[0] == '0') {
            myIsNegative = false;
        }
    } else {
        // X + 1. Increment magnitude.
        int k = 0;
        while (k < myDigits.size() && myDigits[k] == '9') {
            myDigits[k] = '0';
            k++;
        }
        if (k == myDigits.size()) {
            myDigits.push_back('1');
        } else {
            myDigits[k]++;
        }
    }
    return *this;
}

bigint& bigint::operator--() {
    if (myIsNegative) {
        // -X - 1 = -(X + 1). Increment magnitude.
        int k = 0;
        while (k < myDigits.size() && myDigits[k] == '9') {
            myDigits[k] = '0';
            k++;
        }
        if (k == myDigits.size()) {
            myDigits.push_back('1');
        } else {
            myDigits[k]++;
        }
    } else {
        // X - 1
        if (myDigits.size() == 1 && myDigits[0] == '0') {
            // 0 - 1 = -1
            myDigits[0] = '1';
            myIsNegative = true;
        } else {
            // Decrement magnitude.
            int k = 0;
            while (myDigits[k] == '0') {
                myDigits[k] = '9';
                k++;
            }
            myDigits[k]--;
            // Remove leading zero
            if (myDigits[k] == '0' && k == myDigits.size() - 1 && myDigits.size() > 1) {
                myDigits.pop_back();
            }
        }
    }
    return *this;
}
```

What is gained:
- Increased efficiency: We avoid the overhead of constructing a temporary `bigint` object for "1".
- On average, we only need to visit a few digits to handle carries/borrows, making it significantly faster than a general addition/subtraction which processes every digit.

What is lost:
- Code complexity: We are essentially duplicating logic from our addition and subtraction routines.
- Maintenance: If the internal representation of `bigint` changes, we now have more places to update.

## Multiplication By A Single Digit

We overload the * operator to multiply a bigint by a single digit (0-10). That one takes an int. Interestingly, we handle 10.

As "defensive programming", we handle numbers higher than 10.

## Study Questions

1. The multiplication algorithm multiplies the top number by 10 each time
through the loop over the digits of the bottom number. An alternative
method is to work from the leftmost digit down to the rightmost digit
of the bottom number. For example, to multiply 456 by 123, we do
the following:
Multiply 456 by the leftmost digit in 123: 1 * 456 = 456
Multiply the result by 10: 456 * 10 = 4560
Multiply 456 by the next digit of 123
and add to previous result: 4560 + 2 * 456 = 5472
Multiply the result by 10: 5472 * 10 = 54720
Multiply 456 by the next digit of 123
and add to previous result: 54720 + 3 * 456 = 56088
Modify operator *= (const BigInt & big) to use this approach.

```cpp
BigInt& BigInt::operator*=(const BigInt & big) {
    BigInt result("0");
    BigInt temp = *this;

    for (int i = big.myDigits.size() - 1; i >= 0; --i) {
        int digit = big.myDigits[i] - '0';
        result *= 10; // Multiply the current result by 10
        BigInt partial = temp; // Copy of the original number
        partial *= digit; // Multiply by the current digit
        result += partial; // Add to the result
    }

    *this = result;
    return *this;
}
```

2. (AB Only) Find a big-Oh expression for the runtime of operator *= (const
BigInt & big) when applied to two N-digit numbers. Find an expression
for multiplying one N-digit BigInt by a digit using operator *= (int num).
41

The runtime for operator *= (const BigInt & big) when applied to two N-digit numbers is O(N^2). This is because for each of the N digits in the second BigInt, we perform a multiplication operation that itself takes O(N) time (due to the addition of partial results).

3. It’s possible to write functions to handle adding BigInt and int values
specially just as we developed two operators for multiplication: one for
BigInt values and one for int values. We can implement addition and
subtraction operators in two ways:
(a) by converting the integer to a BigInt and calling the appropriate
BigInt operator; or
(b) by writing special code to implement the operation via low-level
reference to the internals of BigInt.
Discuss the advantages and disadvantages of (a) vs (b).

Advantages of (a):
- Simplicity: The code is easier to read and maintain since it leverages existing Big
Int operations.
- Consistency: Ensures that all addition and subtraction operations behave the same way.
Disadvantages of (a):
- Performance: Converting an int to a BigInt incurs overhead, which can be significant
for frequent operations.
Advantages of (b):
- Efficiency: Directly manipulating the internals can be faster, especially for small
integers.
Disadvantages of (b):
- Complexity: The code becomes more complex and harder to maintain.
- Risk of Errors: Direct manipulation increases the risk of bugs if not handled carefully.
4. Develop a precondition for BigInt::operator *= (int num) that describes the
range of values for num that do not result in overflow.

A precondition could be:

```cpp
// Precondition: num must be in the range [0, 9]
```

## Aliasing

After implementing the exponentiation function, we need to consider aliasing issues.

Algorithm:

```cpp

BigInt power(const BigInt & a, int n)
// precondition: 0 <= n
// postcondition: returns a^n, a raised to the n-th power
{
    if (n == 0) return 1;
    if (n == 1) return a;
    BigInt semi = power(a,n/2);
    semi *= semi; // this is semi^2
    if (n % 2 == 0) return semi;
    else return semi * a;
}
```

For some bigint values, it gives incorrect results, for example, 12^2 being 164 instead of 144.

The multiplication of semi *= semi is the cause of this problem. The same bigint in memory is used for the right hand side and the left hand side semi, leading to incorrect results. So, when we perform intermediate calculations, such as multiplying by 10, that modifies the original bigint too.

To fix this, we make a clone.