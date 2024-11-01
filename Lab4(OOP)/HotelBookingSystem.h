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
    virtual void displayInfo() const = 0; // ����������� �����
    ~Person();

    string getName() const { return name; }
    string getContactInfo() const { return contactInfo; }
};
// ����� �� ����������
class BookingRequest {
private:
    string clientName;
    int roomCapacity; // ʳ������ ���� � �����
    string roomClass; // ���� ������
    int stayDuration; // ���������� �����������
    bool isConfirmed; // ϳ����������� ����������
    double prepayment; // �����������
    double totalCost; // �������� �������
    vector<Service> additionalServices; // �������� �������



    // �������� ���� ��� ��������� ������� ���������
    static int totalBookings;
    //const int bookingID;         // ���������� ���� ��� ID ����������
    ////static Room defaultRoom;   // ��������� ��'��� Room �� �������������
    //const Room& bookedRoom;      // ����-��������� �� ��'��� Room
    static void incrementBookings(); // ��������� ����� ��� ��������� ������� ���������

public:
    BookingRequest(); // ����������� ��� ���������
    BookingRequest(string clientName, int roomCapacity, string roomClass, int stayDuration, double totalCost/*, int id, const Room& room*/); // ����������� � �����������
    BookingRequest(const BookingRequest& other); // ����������� ���������
    /* BookingRequest(int id, const Room& room);*/
    ~BookingRequest();

    string getClientName() const;
    int getRoomCapacity() const;
    string getRoomClass() const;
    int getStayDuration() const;
    double getPrepayment() const;
    double getTotalCost() const;
    bool  getIsConfirmed() const;

    static int getTotalBookings(); // ��������� ����� ��� ��������� ������� ���������




    //int getBookingID() const;             // ������ ��� bookingID
    //const Room& getBookedRoom() const;    // ������ ��� bookedRoom

    void confirmBooking(); // ϳ��������� ����������
    void cancelBooking(); // ³������� ����������
    void setPrepayment(double amount); // ���������� ����������
    void addService(const Service& service); // ������ �������
    void displayBookingInfo() const; // ³���������� ���������� ��� ����������
    string toFileFormat() const;  // ����� ����� ��� ������������ ���������� � ������ �����

    /* void loadClientsFromFile(BookingRequest clients[], int n, const string& filename);*/
    static void loadClientsFromFile(BookingRequest clients[], int size, const string& filename);
};

class Service {
private:
    string serviceName;
    double price;

    string serviceType;
    int serviceDuration; // ��������� � ��������
    bool isAvailable;    // ���������� �������
public:
    Service();
    /* Service(string serviceName, double price);*/
    Service(const string& name, double price, const string& type = "Standard", int duration = 60, bool available = true);
    /*virtual ~Service() = default;*/
    virtual string getServiceInfo() const;
    virtual double getPrice() const;
    Service(const Service& other);  // ����������� ���������
    ~Service();

    string getServiceName() const; // �������� ��'� �������
    /*double getPrice() const;*/ // �������� ���� ������� 
    string getServiceType() const;  // ����� ��� ��������� ���� (�����) �������
};
// ϳ����� PremiumService
class PremiumService : public Service {
private:
    bool isPersonalized;  // �������������� �������
    string staffMember;   // ������������ ���������
    int loyaltyPoints;    // ������ ���� �� �������

public:
    PremiumService(const string& name, double price, const string& staff, int points, bool personalized = true);
    ~PremiumService();
    string getServiceInfo() const override;
    double calculateDiscountedPrice(double discount) const;
};



class Room {
protected:
    int roomCapacity; // ̳������ ������
    string roomClass; // ���� ������
    double pricePerNight; // ֳ�� �� ����
    bool isAvailable; // �����, ���� ������ �� � � �������� ���� ������
    string view; // �����������
    int floor; // ������

public:
    /*  Room();*/
    Room(int capacity, const string& classType, double price, bool available = true, const string& view = "Standard", int floor = 1);
    virtual ~Room() = default;
    virtual double calculateCost(int nights) const;
    virtual void displayRoomInfo() const;
    Room(const Room& other);  // ����������� ���������
    /* ~Room();*/
    bool checkAvailability() const; // ��������� ��������

    /* double calculateCost(int nights) const;*/ // ���������� �������
    void bookRoom(); // 
    void releaseRoom();

    /*void displayRoomInfo() const;*/ // ����� ��� ����������� ���������� ��� ������
    //static
};
// ϳ����� SuiteRoom
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


Room createDeluxeRoom();  // �������, ��� ������� � ������� ��'��� Room
void displayBookingSummary(const BookingRequest& booking);
// ������ ������
void displayBookingSummary(const BookingRequest& booking, double discountRate);  // ��������������





// 1. ����������
class Customer {
protected:
    string name;
    string contactInfo;
    int loyaltyPoints;
    bool hasDiscount;       // �������� ������

public:
    Customer(const string& name, const string& contactInfo, int points = 0, bool discount = false);
    virtual ~Customer() = default;
    virtual void displayCustomerInfo() const;
    int getLoyaltyPoints() const;

    /* void displayCustomerInfo() const;*/
};
// ϳ����� VIPCustomer
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

    // ������ �� ������ getLoyaltyPoints �������� ����� ����� �������� using
    using Customer::getLoyaltyPoints;
};


// ������������ ���������� �����������
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

// 2. ���������
class Hotel {
private:
    string hotelName;
    vector<Room> rooms; // ���������: Hotel �� Rooms

public:
    Hotel(string hotelName);
    ~Hotel();
    void addRoom(const Room& room);
    void displayRooms() const;
};

// 3. ����������
class Booking {
private:
    BookingRequest bookingRequest; // ����������: Booking ������ BookingRequest
    Room room;
    vector<Service> services;

public:
    Booking(const BookingRequest& bookingRequest, const Room& room);
    void addService(const Service& service);
    void displayBookingDetails() const;
};

#endif // HOTELBOOKINGSYSTEM_H