#include <iostream>
#include <string>
#include <cstring>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

const int PORT = 80;

int main() {
    // Создаем сокет
    int server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (server_socket == -1) {
        std::cerr << "Error: socket creation failed\n";
        return 1;
    }

    // Настраиваем адрес сервера
    sockaddr_in server_address {};
    server_address.sin_family = AF_INET;
    server_address.sin_addr.s_addr = INADDR_ANY;
    server_address.sin_port = htons(PORT); // Произвольный порт

    // Связываем сокет с адресом сервера
    if (bind(server_socket, (sockaddr*)&server_address, sizeof(server_address)) == -1) {
        std::cerr << "Error: socket bind failed\n";
        close(server_socket);
        return 1;
    }

    // Прослушиваем входящие соединения
    if (listen(server_socket, 1) == -1) {
        std::cerr << "Error: socket listen failed\n";
        close(server_socket);
        return 1;
    }

    std::cout << "Server is running on port 5000\n";

    // Принимаем входящее соединение
    sockaddr_in client_address {};
    socklen_t client_address_size = sizeof(client_address);
    int client_socket = accept(server_socket, (sockaddr*)&client_address, &client_address_size);
    if (client_socket == -1) {
        std::cerr << "Error: socket accept failed\n";
        close(server_socket);
        return 1;
    }

    std::cout << "Client connected\n";

    // Получаем сообщение от клиента
    char buffer[1024] {};
    int bytes_received = recv(client_socket, buffer, sizeof(buffer), 0);
    if (bytes_received == -1) {
        std::cerr << "Error: socket receive failed\n";
        close(client_socket);
        close(server_socket);
        return 1;
    }

    std::cout << "Received message: " << buffer << "\n";

    // Отправляем ответ клиенту
    std::string message = "Hello from server!";
    int bytes_sent = send(client_socket, message.c_str(), message.size(), 0);
    if (bytes_sent == -1) {
        std::cerr << "Error: socket send failed\n";
        close(client_socket);
        close(server_socket);
        return 1;
    }

    std::cout << "Sent message: " << message << "\n";

    // Закрываем соединение
    close(client_socket);
    close(server_socket);

    return 0;
}
