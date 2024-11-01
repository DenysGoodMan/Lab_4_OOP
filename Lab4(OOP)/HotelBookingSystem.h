#pragma once

#ifndef HOTELBOOKINGSYSTEM_H
#define HOTELBOOKINGSYSTEM_H

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
using namespace std;

class Room;
class Service;


class Person {
protected:
    string name;
    string contactInfo;

public:
    Person(const string& name, const string& contactInfo) /*: name(name), contactInfo(contactInfo)*/ {}
    virtual void displayInfo() const = 0; // Абстрактний метод
    ~Person();

    string getName() const { return name; }
    string getContactInfo() const { return contactInfo; }
};
// Запит на бронювання
class BookingRequest {
private:
    string clientName;
    int roomCapacity; // Кількість місць у кімнаті
    string roomClass; // Клас кімнати
    int stayDuration; // Тривальсть перебування
    bool isConfirmed; // Підтвердження бронювання
    double prepayment; // Передоплата
    double totalCost; // Загальна вартість
    vector<Service> additionalServices; // Додаткові послуги



    // Статичне поле для підрахунку кількості бронювань
    static int totalBookings;
    //const int bookingID;         // Константне поле для ID бронювання
    ////static Room defaultRoom;   // Статичний об'єкт Room за замовчуванням
    //const Room& bookedRoom;      // Поле-посилання на об'єкт Room
    static void incrementBookings(); // Статичний метод для збільшення кількості бронювань

public:
    BookingRequest(); // Конструктор без параметрів
    BookingRequest(string clientName, int roomCapacity, string roomClass, int stayDuration, double totalCost/*, int id, const Room& room*/); // Конструктор з параметрами
    BookingRequest(const BookingRequest& other); // Конструктор копіювання
    /* BookingRequest(int id, const Room& room);*/
    ~BookingRequest();

    string getClientName() const;
    int getRoomCapacity() const;
    string getRoomClass() const;
    int getStayDuration() const;
    double getPrepayment() const;
    double getTotalCost() const;
    bool  getIsConfirmed() const;

    static int getTotalBookings(); // Статичний метод для отримання кількості бронювань




    //int getBookingID() const;             // Геттер для bookingID
    //const Room& getBookedRoom() const;    // Геттер для bookedRoom

    void confirmBooking(); // Підтвердити бронювання
    void cancelBooking(); // Відхилити бронювання
    void setPrepayment(double amount); // Встановити предоплату
    void addService(const Service& service); // Додати послугу
    void displayBookingInfo() const; // Відображення інформації про бронювання
    string toFileFormat() const;  // Новий метод для форматування інформації у вигляді рядка

    /* void loadClientsFromFile(BookingRequest clients[], int n, const string& filename);*/
    static void loadClientsFromFile(BookingRequest clients[], int size, const string& filename);
};

class Service {
private:
    string serviceName;
    double price;

    string serviceType;
    int serviceDuration; // тривалість у хвилинах
    bool isAvailable;    // доступність послуги
public:
    Service();
    /* Service(string serviceName, double price);*/
    Service(const string& name, double price, const string& type = "Standard", int duration = 60, bool available = true);
    /*virtual ~Service() = default;*/
    virtual string getServiceInfo() const;
    virtual double getPrice() const;
    Service(const Service& other);  // Конструктор копіювання
    ~Service();

    string getServiceName() const; // Отримати ім'я послуги
    /*double getPrice() const;*/ // Отримати ціну послуги 
    string getServiceType() const;  // Метод для отримання типу (назви) послуги
};
// Підклас PremiumService
class PremiumService : public Service {
private:
    bool isPersonalized;  // персоналізована послуга
    string staffMember;   // відповідальний працівник
    int loyaltyPoints;    // бонусні бали за послугу

public:
    PremiumService(const string& name, double price, const string& staff, int points, bool personalized = true);
    ~PremiumService();
    string getServiceInfo() const override;
    double calculateDiscountedPrice(double discount) const;
};



class Room {
protected:
    int roomCapacity; // Місткість кімнати
    string roomClass; // Клас кімнати
    double pricePerNight; // Ціна за добу
    bool isAvailable; // Метод, який показує чи є в наявності така кімната
    string view; // Переглянути
    int floor; // Поверх

public:
    /*  Room();*/
    Room(int capacity, const string& classType, double price, bool available = true, const string& view = "Standard", int floor = 1);
    virtual ~Room() = default;
    virtual double calculateCost(int nights) const;
    virtual void displayRoomInfo() const;
    Room(const Room& other);  // Конструктор копіювання
    /* ~Room();*/
    bool checkAvailability() const; // Перевірити наявність

    /* double calculateCost(int nights) const;*/ // Розрахунок вартості
    void bookRoom(); // 
    void releaseRoom();

    /*void displayRoomInfo() const;*/ // Метод для відображення інформації про кімнату
    //static
};
// Підклас SuiteRoom
class SuiteRoom : private Room {
private:
    bool hasJacuzzi;
    bool hasBalcony;
    string suiteCategory;

public:
    SuiteRoom(int capacity, double price, bool jacuzzi, bool balcony, const string& category = "VIP Suite");
    ~SuiteRoom();
    double calculateCost(int nights) const override;
    void displayRoomInfo() const override;
};


Room createDeluxeRoom();  // Функція, яка створює і повертає об'єкт Room
void displayBookingSummary(const BookingRequest& booking);
// Додаємо знижку
void displayBookingSummary(const BookingRequest& booking, double discountRate);  // Перевантаження





// 1. Ассоціація
class Customer {
protected:
    string name;
    string contactInfo;
    int loyaltyPoints;
    bool hasDiscount;       // наявність знижки

public:
    Customer(const string& name, const string& contactInfo, int points = 0, bool discount = false);
    virtual ~Customer() = default;
    virtual void displayCustomerInfo() const;
    int getLoyaltyPoints() const;

    /* void displayCustomerInfo() const;*/
};
// Підклас VIPCustomer
class VIPCustomer : public Customer {
private:
    int vipLevel;
    string personalAssistant;
    bool accessToLounge;


public:
    VIPCustomer(const string& name, const string& contactInfo, int level, const string& assistant, bool lounge = true);

    void displayCustomerInfo() const override;
    double applyDiscount(double basePrice) const;
    void showBaseClassAccess() const;
    ~VIPCustomer();

    // Доступ до методу getLoyaltyPoints базового класу через оператор using
    using Customer::getLoyaltyPoints;
};


// Демонстрація множинного наслідування
class SpecialCustomer : public Customer, public Service {
private:
    int loyaltyPoints;
    bool hasSpecialPrivileges;
public:
    SpecialCustomer(const string& name, const string& contactInfo, int points, bool discount, const string& serviceName, double price, bool privileges);
    ~SpecialCustomer();
    void displaySpecialCustomerInfo() const;
    double calculateDiscountedServicePrice(double discountRate) const;
};

// 2. Агрегація
class Hotel {
private:
    string hotelName;
    vector<Room> rooms; // Агрегація: Hotel має Rooms

public:
    Hotel(string hotelName);
    ~Hotel();
    void addRoom(const Room& room);
    void displayRooms() const;
};

// 3. Композиція
class Booking {
private:
    BookingRequest bookingRequest; // Композиція: Booking містить BookingRequest
    Room room;
    vector<Service> services;

public:
    Booking(const BookingRequest& bookingRequest, const Room& room);
    void addService(const Service& service);
    void displayBookingDetails() const;
};

#endif // HOTELBOOKINGSYSTEM_H