#include <iostream>
#include <string>
#include <cstring>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

const char* IP = "172.18.0.2";
const int PORT = 8080;

int main() {
    // Создаем сокет
    int client_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (client_socket == -1) {
        std::cerr << "Error: socket creation failed\n";
        return 1;
    }

    // Настраиваем адрес сервера
    sockaddr_in server_address;
    server_address.sin_family = AF_INET;
    server_address.sin_addr.s_addr = inet_addr(IP); // Локальный адрес
    server_address.sin_port = htons(PORT); // Произвольный порт

    // Устанавливаем соединение с сервером
    if (connect(client_socket, (sockaddr*)&server_address, sizeof(server_address)) == -1) {
        std::cerr << "Error: socket connect failed\n";
        close(client_socket);
        return 1;
    }

    std::cout << "Connected to server on port 5000\n";

    // Отправляем сообщение серверу
    std::string message = "Hello from client!";
    int bytes_sent = send(client_socket, message.c_str(), message.size(), 0);
    if (bytes_sent == -1) {
        std::cerr << "Error: socket send failed\n";
        close(client_socket);
        return 1;
    }

    std::cout << "Sent message: " << message << "\n";

    // Получаем ответ от сервера
    char buffer[1024] {};
    int bytes_received = recv(client_socket, buffer, sizeof(buffer), 0);
    if (bytes_received == -1) {
        std::cerr << "Error: socket receive failed\n";
        close(client_socket);
        return 1;
    }

    std::cout << "Received message: " << buffer << "\n";

    // Закрываем соединение
    close(client_socket);

    return 0;
}
