#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

/*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*
This program will read character data from text files and from standard input from the keyboard
and then, a matrix stores and processes input data to accommodate an irregular shape.
--------------------------------
Sabanci University
CS 204 - Advanced Programming
Homework Assignment #1
--------------------------------
Student Name: Kerem Tatari
Student ID: 29208
*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*/

bool isPlaceShape(vector<vector<char>> & matrix, vector<vector<char>> & shape) {
    // This function checks if the shape can be placed or not

    int shapeRows = shape.size();
    int shapeCols = shape[0].size();

    int row_of_table = matrix.size();
    int col_of_table = matrix[0].size();

    // checking if the shape exceeds the boundary
    if (shapeRows > matrix.size() || shapeCols > matrix[0].size()){
        return false;
    }

    // iterating over all possible positions to place the shape
    for (int i = 0; i <= row_of_table - shapeRows; i++){
        for (int j = 0; j <= col_of_table - shapeCols; j++){
            // checking for # and -'s for matching with blanks and *'s
            bool canPlaceShape = true;
            for (int k = 0; k < shapeRows; k++){
                for (int l = 0; l < shapeCols; l++){
                    char c = shape[k][l];
                    if (c != ' ' && matrix[i+k][j+l] != '-'){
                        canPlaceShape = false;
                        break;
                    }
                }
                if (!canPlaceShape) break;
            }
            if (canPlaceShape) return true;
        }
    }
    return false;
}

/* Begin: code taken from strutils.cpp */

int atoi(const string & s)
// precondition: s is a sequence of digits
// postcondition: returns integer equivalent of s
// exception: if s is not valid integer, 0 is returned
{
    return atoi(s.c_str());
}

/* End: code taken from strutils.cpp */

int main() {

    // variables for input from file
    vector<vector<char>> text_matrix; // matrix to store file input
    string file_name, line_of_txt;
    ifstream input_from_text;
    int row_length = -1; // initializing row length to -1 to check if it is set later

    // variables for input from keyboard
    string input_from_keyboard;


    cout << "Please enter the file name: " << endl;
    cin >> file_name;
    input_from_text.open(file_name.c_str());

    // This part makes the program ask for a filename until it gets a valid filename
    while (!input_from_text.is_open()) {
        cout << "Could not open the file. Please enter a valid file name: " << endl;
        cin >> file_name;
        input_from_text.open(file_name.c_str());
    }
    if (input_from_text.is_open()) {
        // Here, program takes from file to matrix (line by line ---> row)
        while (getline(input_from_text, line_of_txt)) {
            if (row_length == -1) {
                // first row, taking max row length
                row_length = line_of_txt.length();
            } else if (line_of_txt.length() != row_length) {
                // this checks for row length consistency
                cout << "Erroneous file content. Program terminates." << endl;
                return 1;
            }
            vector<char> row_matrix; // vector for adding characters to the matrix
            for (int i = 0; i < row_length; i++) {
                char c = line_of_txt[i];

                // checking every char for their validity
                if (c != '-' && c != '#') {
                    cout << "Erroneous file content. Program terminates." << endl;
                    return 1;
                }
                row_matrix.push_back(c); // adding chars to the row vector
            }
            text_matrix.push_back(row_matrix); // adding everything in row to the matrix vector
        }

        // Showing the matrix to the user
        cout << "The matrix file contains: " << endl;
        for (int j = 0; j < text_matrix.size(); j++) {
            for (int k = 0; k < row_length; k++) {
                cout << text_matrix[j][k] << "";
            }
            cout << endl;
        }
    }
    input_from_text.close();

    while (true) {

        cout << "Enter the string query for a shape, or \"Quit\" to terminate the program: " << endl;
        cin >> input_from_keyboard;

        if (input_from_keyboard == "Quit") {
            return 0;
        } else {
            // Counting the number of rows and maximum row length
            int numRows = 1; // if there is no slash, that means there is one row
            int maxRowLength = 0;
            int currentRowLength = 0;
            for (int i = 0; i < input_from_keyboard.length(); i++) {
                char c = input_from_keyboard[i];
                if (c == '/') {
                    numRows++;
                    if (currentRowLength > maxRowLength) {
                        maxRowLength = currentRowLength;
                    }
                    currentRowLength = 0;
                } else if (isdigit(c)) {
                    currentRowLength += c - '0';
                }
            }
            if (currentRowLength > maxRowLength) {
                maxRowLength = currentRowLength;
            }

            vector<vector<char>> keyboard_matrix(numRows, vector<char>(maxRowLength, ' '));
            // Adding everything to the matrix
            int row = 0;
            int col = 0;
            for (int i = 0; i < input_from_keyboard.length(); i++) {
                char c = input_from_keyboard[i];
                char c1 = input_from_keyboard[i + 1];
                if (c == '/') {
                    row++;
                    col = 0;
                } else if (isdigit(c)) {
                    if (c1 == 'b') {
                        string s(1, c); // convert char c to string s
                        int c_num = atoi(s);
                        for (int a = 0; a < c_num; a++) {
                            col++;
                        }
                    } else if (c1 == 's') {
                        string s(1, c); // convert char c to string s
                        int c_num = atoi(s);
                        for (int b = 0; b < c_num; b++) {
                            keyboard_matrix[row][col] = '*';
                            col++;
                        }
                    }
                } else {
                    continue;
                }
            }
            if (input_from_keyboard == "Quit") {
                return 0;
            } else if (isPlaceShape(text_matrix, keyboard_matrix) == false) {
                cout << "No placements found." << endl;
            } else if (isPlaceShape(text_matrix, keyboard_matrix) == true) {
                vector<vector<int>> row_indices;
                vector<vector<int>> col_indices;
                //vector<vector<int>> placements;
                int prev_count = 0;
                int rowindex = 0;
                int colindex = 0;
                int greater = 0;
                int shape_rows = keyboard_matrix.size();
                int shape_cols = keyboard_matrix[0].size();
                char ctrl = 'Y';

                for (int i = 0; i <= text_matrix.size() - keyboard_matrix.size(); i++) {
                    for (int j = 0; j <= text_matrix[0].size() - keyboard_matrix[0].size(); j++) {

                        vector<int> rows;
                        vector<int> cols;
                        for (int k = 0; k < shape_rows; k++) {
                            for (int l = 0; l < shape_cols; l++) {
                                int row = i + k;
                                int col = j + l;
                                if (text_matrix[row][col] == '-' && keyboard_matrix[k][l] == '*') {
                                    rows.push_back(row);
                                    cols.push_back(col);
                                    ctrl = 'Y';
                                } else {
                                    ctrl = 'N';
                                }
                            }
                        }
                        if (ctrl == 'Y') {
                            row_indices.push_back(rows);
                            col_indices.push_back(cols);
                            prev_count++;
                        }
                        //prev_count++;
                        if (ctrl == 'Y') {
                            cout << "Placement number " << prev_count << ":" << endl;
                        }
                        string placementStr = "";

                        int counter = 0;
                        for (int a = 0; a < row_indices.size(); a++) {
                            for (int b = 0; b < row_indices[a].size(); b++) {
                                if (counter < greater) {
                                    break;
                                } else {
                                    placementStr +=
                                            "(" + to_string(row_indices[a][b]) + "," + to_string(col_indices[a][b]) +
                                            ") ";
                                }
                                counter++;
                            }
                        }
                        if (ctrl == 'Y') {
                            cout << placementStr << endl;
                            placementStr = "";
                        }
                    }
                }
            }
        }
        return 0;
    }
}