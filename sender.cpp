#include <iostream>
#include <bitset>
#include <cstring>
#include <unistd.h>
#include <arpa/inet.h>

using namespace std;

string hammingEncode(string data) {
    int codeword[12] = {0};
    int dataBits[8];

    for (int i = 0; i < 8; ++i)
        dataBits[i] = data[i] - '0';

    // Place data bits in codeword (positions that are not 1,2,4,8)
    int j = 0;
    for (int i = 0; i < 12; ++i) {
        if ((i+1) != 1 && (i+1) != 2 && (i+1) != 4 && (i+1) != 8) {
            codeword[i] = dataBits[j++];
        }
    }

    // Calculate parity bits
    for (int i = 0; i < 4; ++i) {
        int pos = (1 << i);  // positions 1,2,4,8
        int parity = 0;
        for (int k = 0; k < 12; ++k) {
            if ((k+1) & pos)
                parity ^= codeword[k];
        }
        codeword[pos - 1] = parity;
    }

    // Convert to string
    string result = "";
    for (int i = 0; i < 12; ++i)
        result += to_string(codeword[i]);

    return result;
}

int main() {
    char ch;
    cout << "Enter a single character: ";
    cin >> ch;

    bitset<8> binary(ch);
    string binStr = binary.to_string();
    cout << "8-bit binary: " << binStr << endl;

    string codeword = hammingEncode(binStr);
    cout << "Hamming Codeword: " << codeword << endl;

    // Socket setup
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    sockaddr_in serverAddr{};
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(9999);
    serverAddr.sin_addr.s_addr = inet_addr("127.0.0.12");

    if (connect(sock, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) < 0) {
        perror("Connect failed");
        return 1;
    }

    send(sock, codeword.c_str(), codeword.size(), 0);
    close(sock);

    return 0;
}
