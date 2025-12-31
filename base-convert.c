#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_DIGITS 100
#define MAX_BASE 36   // We’ll allow bases up to 36 (0–9, A–Z)

// Converts one character (like 'A' or '7') into its numeric value
int valueOfDigit(char ch) 
{
    if (isdigit(ch)) return ch - '0';
    if (isalpha(ch)) return toupper(ch) - 'A' + 10;
    return -1;  // Invalid character
}

// Converts a numeric value (like 10 or 15) back into a single character ('A' or 'F')
char digitOfValue(int val) 
{
    if (val >= 0 && val <= 9) return '0' + val;
    if (val >= 10 && val < MAX_BASE) return 'A' + (val - 10);
    return '?'; // Just in case something unexpected happens
}

// Converts a number string from a given base to its decimal (base 10) value
long long toDecimal(const char *num, int base) 
{
    long long value = 0;
    int digitVal;

    for (int i = 0; num[i]; i++) {
        digitVal = valueOfDigit(num[i]);
        if (digitVal < 0 || digitVal >= base) {
            printf("Error: Invalid digit '%c' for base %d\n", num[i], base);
            return -1;
        }
        value = value * base + digitVal;  // Multiply previous result by base and add new digit
    }
    return value;
}

// Converts a decimal value into another base (like binary, octal, or hex)
void fromDecimal(long long decimalValue, int base, char result[]) 
{
    int index = 0;

    // Special case for 0
    if (decimalValue == 0) 
    {
        result[0] = '0';
        result[1] = '\0';
        return;
    }

    // Keep dividing by the base and storing remainders
    while (decimalValue > 0) 
    {
        int remainder = decimalValue % base;
        result[index++] = digitOfValue(remainder);
        decimalValue /= base;
    }
    result[index] = '\0';

    // Reverse the string (since digits are generated in reverse order)
    for (int i = 0; i < index / 2; i++) 
    {
        char temp = result[i];
        result[i] = result[index - i - 1];
        result[index - i - 1] = temp;
    }
}

// Prints the digits available in a given base (for example, base 16 → 0 1 2 3 ... F)
void printDigitSet(int base) 
{
    for (int i = 0; i < base; i++)
        printf("%c ", digitOfValue(i));
    printf("\n");
}

int main(int argc, char *argv[]) 
{
    // The program needs 6 arguments (including the program name)
    // Example: ./test -i 2 -o 8 1011
    if (argc != 6) 
    {
        printf("Usage: %s -i <input_base> -o <output_base> <number>\n", argv[0]);
        return 1;
    }

    int inputBase = 0, outputBase = 0;
    char inputNumber[MAX_DIGITS], outputNumber[MAX_DIGITS];

    // Read input base (after -i)
    if (strcmp(argv[1], "-i") == 0)
        inputBase = atoi(argv[2]);
    else 
    {
        printf("Error: Missing or incorrect -i argument\n");
        return 1;
    }

    // Read output base (after -o)
    if (strcmp(argv[3], "-o") == 0)
        outputBase = atoi(argv[4]);
    else 
    {
        printf("Error: Missing or incorrect -o argument\n");
        return 1;
    }

    // The actual number to convert
    strcpy(inputNumber, argv[5]);

    // Make sure the bases are valid
    if (inputBase < 2 || inputBase > MAX_BASE || outputBase < 2 || outputBase > MAX_BASE) 
    {
        printf("Error: Base must be between 2 and %d\n", MAX_BASE);
        return 1;
    }

    // Show input details
    printf("Input base: %d\nInput digits: ", inputBase);
    printDigitSet(inputBase);
    printf("Input number: %s\n\n", inputNumber);

    // Show output base details
    printf("Output base: %d\nOutput digits: ", outputBase);
    printDigitSet(outputBase);

    // Step 1: Convert to decimal
    long long decimalValue = toDecimal(inputNumber, inputBase);
    if (decimalValue < 0) return 1;  // Error already printed

    // Step 2: Convert from decimal to target base
    fromDecimal(decimalValue, outputBase, outputNumber);

    // Print the final result
    printf("Output number: %s\n", outputNumber);

    return 0;
}
