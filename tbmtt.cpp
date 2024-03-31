#include <iostream>
#include <string>
#include <algorithm>

std::string generatePlayfairTable(std::string key) {
    std::string alphabet = "ABCDEFGHIKLMNOPQRSTUVWXYZ";
    std::transform(key.begin(), key.end(), key.begin(), ::toupper);
    key.erase(std::remove(key.begin(), key.end(), 'J'), key.end());
    key += alphabet;
    std::string table;

    for (std::string::size_type i = 0; i < key.length(); i++) {
        if (table.find(key[i]) == std::string::npos) {
            table += key[i];
        }
    }

    return table;
}

std::string preprocessMessage(std::string message) {
    std::transform(message.begin(), message.end(), message.begin(), ::toupper);
    message.erase(std::remove(message.begin(), message.end(), 'J'), message.end());

    std::string processedMessage;
    for (std::string::size_type i = 0; i < message.length(); i++) {
        processedMessage += message[i];
        if (i < message.length() - 1 && message[i] == message[i + 1]) {
            processedMessage += 'X';
        }
    }

    if (processedMessage.length() % 2 != 0) {
        processedMessage += 'X';
    }

    return processedMessage;
}

void findPosition(const std::string& table, char ch, int& row, int& col) {
    std::string::size_type index = table.find(ch);
    row = index / 5;
    col = index % 5;
}

std::string encrypt(const std::string& message, const std::string& key) {
    std::string table = generatePlayfairTable(key);
    std::string processedMessage = preprocessMessage(message);
    std::string encryptedMessage;

    for (std::string::size_type i = 0; i < processedMessage.length(); i += 2) {
        char ch1 = processedMessage[i];
        char ch2 = processedMessage[i + 1];

        int row1, col1, row2, col2;
        findPosition(table, ch1, row1, col1);
        findPosition(table, ch2, row2, col2);

        if (row1 == row2) {
            encryptedMessage += table[row1 * 5 + (col1 + 1) % 5];
            encryptedMessage += table[row2 * 5 + (col2 + 1) % 5];
        } else if (col1 == col2) {
            encryptedMessage += table[((row1 + 1) % 5) * 5 + col1];
            encryptedMessage += table[((row2 + 1) % 5) * 5 + col2];
        } else {
            encryptedMessage += table[row1 * 5 + col2];
            encryptedMessage += table[row2 * 5 + col1];
        }
    }

    return encryptedMessage;
}

int main() {
    std::string key, message;

    std::cout << "Nhap khoa: ";
    std::getline(std::cin, key);

    std::cout << "Nhap thong diep: ";
    std::getline(std::cin, message);

    std::string encryptedMessage = encrypt(message, key);
    std::cout << "Thong diep da ma hoa: " << encryptedMessage << std::endl;

    return 0;
}
