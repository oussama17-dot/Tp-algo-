# Password Strength Validator

## Description
A C program that validates password strength against 6 requirements
and provides colored feedback showing exactly what is missing.

## How to Compile
gcc -o password_validator password_validator.c -Wall

## How to Run
./password_validator

## Features
- Checks 6 requirements: length, uppercase, lowercase, digit, special character, no spaces
- Score from 0 to 6
- Colored output based on strength level
- Lists exactly which requirements are not yet met
- Bonus: generates a random strong password

## Example
Enter password (or q to quit): hello
Score: 2/6  Weak - significant improvements needed.
Missing: length, uppercase, digit, special character

Enter password (or q to quit): H3llo_World!
Score: 6/6  Very Strong - excellent password.
All requirements satisfied.
