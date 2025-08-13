#include <iostream>
#include <cstring>
#include <unistd.h>
#include <arpa/inet.h>
#include <bitset>

using namespace std;

int detectError(string codeword) {
    int code[12];
    for (int i = 0; i < 12; ++i)
        code[i] = codeword[i] - '0';

    int errorPos = 0;
    for (int i = 0; i < 4; ++i) {
        int pos = (1 << i);
        int parity = 0;
        for (int k = 0; k < 12; ++k) {
            if ((k+1) & pos)
                parity ^= code[k];
        }
        if (parity != 0)
            errorPos += pos;
    }

    return errorPos;
}

char decodeData(string codeword) {
    int code[12];
    for (int i = 0; i < 12; ++i)
        code[i] = codeword[i] - '0';

    // Extract data bits (positions not 1,2,4,8)
    string dataBits = "";
    for (int i = 0; i < 12; ++i) {
        if ((i+1) != 1 && (i+1) != 2 && (i+1) != 4 && (i+1) != 8) {
            dataBits += to_string(code[i]);
        }
    }

    bitset<8> b(dataBits);
    return static_cast<char>(b.to_ulong());
}

void printParityBits(string codeword) {
    cout << "Parity Bits:\n";
    cout << "p1 (position 1): " << codeword[0] << endl;
    cout << "p2 (position 2): " << codeword[1] << endl;
    cout << "p3 (position 4): " << codeword[3] << endl;
    cout << "p4 (position 8): " << codeword[7] << endl;
}

int main() {
    int serverSock, clientSock;
    sockaddr_in serverAddr{}, clientAddr{};
    socklen_t addrSize = sizeof(clientAddr);

    serverSock = socket(AF_INET, SOCK_STREAM, 0);
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(9999);
    serverAddr.sin_addr.s_addr = inet_addr("127.0.0.12");

    bind(serverSock, (struct sockaddr*)&serverAddr, sizeof(serverAddr));
    listen(serverSock, 5);

    cout << "Waiting for connection on 127.0.0.12:9999...\n";
    clientSock = accept(serverSock, (struct sockaddr*)&clientAddr, &addrSize);
    cout << "Connected.\n";

    char buffer[1024] = {0};
    recv(clientSock, buffer, 1024, 0);
    string codeword(buffer);

    cout << "Received Codeword: " << codeword << endl;
    printParityBits(codeword);

    int errorBit = detectError(codeword);

    cout << "\nMenu:\n";
    if (errorBit == 0) {
        cout << "1. Data received without error\n";
    } else {
        cout << "2. Data received with error at bit position: " << errorBit << endl;
    }

    char decodedChar = decodeData(codeword);
    cout << "Received Data: " << decodedChar << endl;

    cout << "3. Exit\n";

    close(clientSock);
    close(serverSock);
    return 0;
}
