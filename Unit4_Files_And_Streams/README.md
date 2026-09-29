Name : Krishna Kadale
ZPRN : 125UAD1240
Div : B
Course : B.Tech (AI & DS)
Unit : 4
List of Programs :  01_Write_Text_To_File
                    02_Read_File_Line_By_Line
                    03_Append_Data_To_File
                    04_Copy_Text_File
                    05_Count_Lines_Words_Characters
                    06_Search_Word_In_File
                    07_Store_Student_Records
                    08_Read_Search_Student_Records
                    09_Update_Student_Record
                    10_File_Pointer_Navigation
                    11_Binary_File_Read_Write
                    12_Random_Access_Binary_File
                    13_File_Error_Handling
                    14_File_Statistics
                    15_Student_Record_Manager
                    16_Library_Record_System
Brief Description :

1. Write Text to File

This program creates or replaces message.txt and writes several lines of text to it. It checks whether the output file opened successfully and reports the result.

2. Read File Line by Line

The program opens message.txt and reads it one line at a time with getline(). Each displayed line is prefixed with its 1-based line number.

3. Append Data to File

The program asks for a name and a date, then appends both as a labeled line to message.txt. Append mode preserves the file's existing contents.

4. Copy Text File

The program scans message.txt line by line and copies only lines containing C++ into cpp_lines.txt. The destination file is created or replaced for each run.

5. Count Lines, Words, and Characters

This program analyzes message.txt character by character and reports line, word, and character totals. It also counts vowels, consonants, digits, literal spaces, and punctuation characters.

6. Search Word in File

The user enters a word to search for in message.txt. Comparisons ignore letter case and punctuation, and the program reports the number of matching tokens.

7. Store Student Records

The program appends a student record to students.txt. Each record contains a roll number, name, course, mobile number, and marks separated by vertical bars.

8. Read and Search Student Records

The program reads all five-field student records from students.txt and displays them in a table. Column widths adjust to fit the stored values.

9. Update Student Record

The user selects a student by roll number and enters a replacement name and marks value. The program rewrites the records while preserving the student's course and mobile number and leaving other records unchanged.

10. File Pointer Navigation

The program demonstrates tellg(), tellp(), seekg(), and seekp() using navigation.txt. It reads the first, a selected, and the last character while also writing to the file.

11. Binary File Read and Write

This program writes three StudentRecord objects to students.dat as raw binary data. It then reads each record in a loop and displays its roll number, name, and marks.

12. Random Access Binary File

The program creates sample binary records and searches them by roll number. It uses seekg() to inspect each fixed-size record at its byte offset.

13. File Error Handling

The program repeatedly asks for a filename until it can open the file. It then displays the file contents and reports whether reading ended normally or encountered an I/O error.

14. File Statistics

The user selects an input file, and the program reports its lines, words, characters, vowels, consonants, digits, spaces, punctuation, and most frequent character. The same report is displayed and saved to report.txt.

15. Student Record Manager

This menu-driven program can add, display, search, update, and delete student records. It prevents duplicate roll numbers, validates marks from 0 to 100, stores course and department details, and calculates letter grades.

16. Library Record System

The menu supports adding books, displaying records, searching by book ID, and issuing or returning books. It prevents duplicate IDs, records student borrower details and due dates, and assesses a fine of 1 unit per overdue day when a book is returned.
