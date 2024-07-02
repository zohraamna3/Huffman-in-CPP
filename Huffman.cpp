
#include<iostream>
#include<string>
#include<fstream>
using namespace std;

// Node class represents a node in the Huffman tree
class node {
public:
    char ch;          // Character stored in the node
    int data;         // Frequency of the character
    node* left, * right;  // Pointers to the left and right child nodes

    // Default constructor
    node() {
        ch = ' ';
        data = 0;
        left = right = NULL;
    }

    // Parameterized constructor
    node(char c, int d) {
        ch = c;
        data = d;
        left = right = NULL;
    }

    // Copy constructor
    node(node* str) {
        ch = str->ch;
        data = str->data;
        left = str->left;
        right = str->right;
    }
};

// Huffman class contains the main Huffman coding logic
class huffman {
public:
    node* arr;       // Array of nodes representing character frequencies
    node root;       // Root of the Huffman tree
    int size;        // Size of the array
    string code;     // Huffman code for a character
    string strr, strr1;  // Input string and a modified version
    ifstream file;   // File stream for input
    bool f, l;       // Flags
    int count;       // Counter

    // Default constructor
    huffman() {
        l = f = 0;
        count++;
    }

    // Function to delete duplicate characters from a string
    string delete_duplicate(string str) {
        string str2 = "";
        for (int i = 0; str[i] != '\0'; i++) {
            for (int j = i + 1; str[j] != '\0'; j++) {
                if (str[i] == str[j]) {
                    str[j] = '/';
                }
            }
        }
        for (int i = 0; str[i] != '\0'; i++) {
            if (str[i] != '/') {
                str2 = str2 + str[i];
            }
        }
        return str2;
    }

    // Function to store character frequencies in the array
    void store_frequency(string str1, string str2) {
        size = 0;
        int arr_index = 0;
        for (int i = 0; str2[i] != '\0'; i++) {
            size++;
        }
        arr = new node[size];
        for (int i = 0; str2[i] != '\0'; i++) {
            count = 0;
            for (int j = 0; str1[j] != '\0'; j++) {
                if (str2[i] == str1[j]) {
                    count++;
                }
            }
            arr[arr_index].ch = str2[i];
            arr[arr_index].data = count;
            arr_index++;
        }
    }

    // Function to read input from a file and perform initial processing
    void insertion() {
        file.open("input.txt");
        if (!file) {
            cout << "Error! File not open\n";
        }
        else {
            while (!file.eof()) {
                string temp;
                getline(file, temp);
                strr += temp;
            }
            file.close();
            string str2 = delete_duplicate(strr);
            store_frequency(strr, str2);
        }
    }

    // Function to sort the array of nodes based on frequency
    void sort(int n) {
        node temp;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n - 1; j++) {
                if (arr[j].data > arr[j + 1].data) {
                    temp = arr[j];
                    arr[j] = arr[j + 1];
                    arr[j + 1] = temp;
                }
            }
        }
    }

    // Function to build the Huffman tree
    void huffmanTree() {
        sort(size);
        int n = size;
        for (int i = 0; i < size; i++) {
            node newnode;
            if (n > 1) {
                newnode.data = arr[0].data + arr[1].data;
                newnode.ch = '#';
                if (arr[0].data == arr[1].data) {
                    newnode.right = new node(arr[0]);
                    newnode.left = new node(arr[1]);
                }
                else {
                    newnode.left = new node(arr[0]);
                    newnode.right = new node(arr[1]);
                }
                for (int j = 0; j < n - 2; j++) {
                    arr[j] = arr[j + 2];
                }
                arr[n - 2] = new node(newnode);
                n--;
                sort(n);
            }
            else {
                break;
            }
        }
        root = new node(arr[0]);
    }

    // Function to generate Huffman codes for each character
    void generate_code(node* temp, char ch, string str = "") {
        if (temp == NULL) {
            return;
        }
        if (temp->ch == ch) {
            code = str;
            return;
        }
        generate_code(temp->left, ch, str + '0');
        generate_code(temp->right, ch, str + '1');
    }

    // Function to display the frequency table
    void dispaly() {
        cout << " \033[35m \t\t   Character\t\t\t   Frequency \033[0m \t\t\n";
        for (int i = 0; i < size; i++) {
            cout << "\t\t\t" << arr[i].ch << "\t\t \033[31m " << "| " << " \033[0m \t\t" << arr[i].data << "\t\t" << "\n";
        }
        sort(size);
        cout << "\n\n\n \n\n\t\t\t\033[35m Sorted Array By Ascending Order \033[0m \n\n\n\n\n\n";
        for (int i = 0; i < size; i++) {
            cout << "  " << "(" << arr[i].ch << "/" << arr[i].data << ")" << "  ";
        }

        cout << "\n\n";
    }

    // Function to display the Huffman tree in pre-order traversal
    void preorder_display(node* temp) {
        if (temp != NULL) {
            cout << "\t" << "(" << temp->ch << "/" << temp->data << ")" << "-->";
            preorder_display(temp->left);
            preorder_display(temp->right);
        }
    }

    // Function to display the Huffman codes for each character
    void display_of_code() {
        string str = delete_duplicate(strr);
        cout << "\n \t\t\t\033[35m \tCharacter\t\tCode \033[0m \n";

        for (int i = 0; str[i] != '\0'; i++) {
            generate_code(&root, str[i]);
            cout << "\t\t\t\t " << str[i] << "\t\t" << "|" << "\t" << code << "\n";
        }
    }

    // Function to decode an encoded string
    string decode(string encoded) {
        node* temp = &root;
        string str = "";
        for (int i = 0; encoded[i] != '\0'; i++) {
            if (encoded[i] == '0') {
                temp = temp->left;
            }
            else if (encoded[i] == '1') {
                temp = temp->right;
            }
            if (temp->left == NULL && temp->right == NULL) {
                str = str + temp->ch;
                temp = &root;
            }
        }
        return str;
    }
};

// Main function
int main() {
    ofstream file2;
    huffman h1;
    string str;
    cout << " \n\n\033[34m \t\t\t\tFrequency Table \033[0m \n\n\n";
    h1.insertion();
    h1.dispaly();
    h1.huffmanTree();
    cout << "\n\n\n\n\t\t\t \033[34m Pre-Order Display of Huffman Tree \033[0m \n\n\n";
    h1.preorder_display(&h1.root);
    cout << "\n\n\n\n \t\t\t\033[33m  Table of code of Unique characters \033[0m\n\n \n\n";
    h1.display_of_code();

    file2.open("encoded.txt");
    string encoded_str = "";
    for (int i = 0; h1.strr[i] != '\0'; i++) {
        h1.generate_code(&h1.root, h1.strr[i]);
        encoded_str = encoded_str + h1.code;
    }
    file2 << encoded_str;
    file2.close();
    cout << " \n\n\n\n\n\t\t\t\t\033[32m The Huffman Encode of Given String \033[0m\n\n\n" << encoded_str << "\n\n\n\n";
    cout << "\n\n\n\n\n\n\n";
    ofstream file3;
    file3.open("decoded.txt");
    if (!file3) {
        cout << "Error! File not open\n";
    }
    else {
        file3 << h1.decode(encoded_str);
    }
    cout << "\n\n \n\n\t\t\t\t\033[34m This is Huffman Decode of Given String \033[0m \n\n\n\n\n" << h1.decode(encoded_str) << "\n\n\n\n\n\n";

    return 0;
}
