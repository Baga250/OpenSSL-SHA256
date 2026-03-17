#include <iostream>
#include <string>
#include <windows.h>
#include <openssl/evp.h>
#include <sstream>
#include <iomanip>
#include <vector>

void menu()
{
    std::cout << "Выберите действия из списка:" << std::endl;
    std::cout << "1. Сгенерировать хэш" << std::endl;
    std::cout << "2. Сравнить хэш" << std::endl;
    std::cout << "0. Выход" << std::endl;
}

std::string sha256_evp(const std::string& input) 
{
    // Создание переменной и массива
    EVP_MD_CTX* ctx = EVP_MD_CTX_new();
    unsigned char hash[EVP_MAX_MD_SIZE];
    unsigned int hash_len;
    
    EVP_DigestInit_ex(ctx, EVP_sha256(), nullptr); // Инициализация движка
    EVP_DigestUpdate(ctx, input.c_str(), input.size()); // Работа с хэширумемыми данными
    EVP_DigestFinal_ex(ctx, hash, &hash_len); // Финал хэширования
    EVP_MD_CTX_free(ctx); // Функция чистки
    
    // Обработка битов в hex-строку
    std::stringstream hex;
    for (int i = 0; i < hash_len; i++)
    {
        hex << std::hex << std::setw(2) << std::setfill('0') << (unsigned int)hash[i];
    }

    // Возвращаем строку
    return hex.str();
}

void generateHash()
{
    std::string password;
    std::cout << "Введите пароль для хэширования: ";
    std::cin >> password;
    std::cout << "Полученный хэш: " << sha256_evp(password) << std::endl;
}

void verifyHash() 
{
    std::string password;
    std::string user_hash;
    
    std::cout << "Введите пароль: ";
    std::cin >> password;
    
    std::cout << "Введите хэш для сравнения: ";
    std::cin >> user_hash;

    std::string calculated_hash = sha256_evp(password);
    
    std::cout << "Вычисленный хэш: " << calculated_hash << std::endl;
    
    if (calculated_hash == user_hash) 
    {
        std::cout << "Хэш верный! Пароль совпадает." << std::endl;
    } 
    else
    {
        std::cout << "Хэш неверный! Пароль не совпадает." << std::endl;
    }
}

int main()
{
    SetConsoleOutputCP(CP_UTF8);

    int choice;
    while (true)
    {
        menu();
        std::cin >> choice;

        switch (choice)
    {
        case 1:
            generateHash();
            break;

        case 2:
            verifyHash();
            break;

        case 0:
            return 0;
    }
    }
   
    return 0;
}
