#include "HotelBookingSystem.h"
#include <iostream>

void saveClientsToFile(const BookingRequest clients[], int size, const string& filename) {
    ofstream outFile(filename);
    if (outFile.is_open()) {
        for (int i = 0; i < size; i++) {
            outFile << clients[i].toFileFormat() << endl;
        }
        outFile.close();
        cout << "\n Clients saved to " << filename << "\n" << endl;
    }
    else {
        cerr << "Unable to open file " << filename << endl;
    }
}

int main() {
    // 5,6
    // ��������� ��'��� VIPCustomer
    VIPCustomer vipCustomer("Alice Johnson", "alice@vip.com", 3, "John Doe");

    cout << "----- VIP Customer Info -----" << endl;
    vipCustomer.displayCustomerInfo();

    // ������������ ������������ ������
    double originalPrice = 500.0;
    double discountedPrice = vipCustomer.applyDiscount(originalPrice);
    cout << "Original Price: $" << originalPrice << endl;
    cout << "Discounted Price for VIP Customer: $" << discountedPrice << "\n" << endl;
    // ������������ ������� showBaseClassAccess ��� ������� �� ����� �������� �����
    vipCustomer.showBaseClassAccess();



    // 4
    // �������� ��������� ��������� �����������

     // ��������� ��'���� SpecialCustomer
    SpecialCustomer specialCustomer("John Smith", "john@special.com", 150, true, "VIP Lounge Access", 25.0, true);
    cout << "----- Special Customer Info -----" << endl;
    specialCustomer.displaySpecialCustomerInfo();

    double discountedPrice_ = specialCustomer.calculateDiscountedServicePrice(0.2); // 20% ������
    cout << "Discounted Service Price: $" << discountedPrice_ << endl;


    cout << "*********New_updates********* " << endl;
    // ��������� ��'���� VIPCustomer
    VIPCustomer vipClient("Alice Johnson", "alice@vip.com", 5, "Emily Smith", true);
    vipClient.displayCustomerInfo();

    // ��������� ��'���� PremiumService
    PremiumService vipService("Personal Spa Session", 100.0, "Sarah Connor", 50);
    cout << vipService.getServiceInfo() << ", Price: $" << vipService.calculateDiscountedPrice(0.1) << endl;

    // ��������� ��'���� SuiteRoom
    SuiteRoom suiteRoom(4, 200.0, true, true, "Executive Suite");
    suiteRoom.displayRoomInfo();

    // ��������� �� ��������� ���������� ��� ���������� VIP-�볺���
    BookingRequest bookingRequest("Alice Johnson", 2, "Suite", 3, suiteRoom.calculateCost(3));
    cout << "Total Bookings: " << BookingRequest::getTotalBookings() << endl;

    cout << "***************************** " << endl;

    // ��������� ��'���� �������
    Service breakfast("Breakfast in room", 15.0);
    // ��������� ���������� ��� �������
    cout << "Service Name: " << breakfast.getServiceName() << endl;
    cout << "Service Price: $" << breakfast.getPrice() << endl;
    cout << "Service Type: " << breakfast.getServiceType() << "\n" << endl;
    cout << "\n********************************" << endl;
    cout << "************11,12,13************" << endl;
    // ��������� ��'���� Customer
    Customer customer("John Doe", "john@example.com");
    customer.displayCustomerInfo();

    // ��������� ��'���� Room
    Room rooms1(2, "Standard", 50.0);
    Room rooms2(3, "Deluxe", 80.0);

    // ��������� ��'���� Hotel �� ��������� �����
    Hotel hotel("Grand Hotel");
    hotel.addRoom(rooms1);
    hotel.addRoom(rooms2);
    hotel.displayRooms();

    // ��������� ������ �� ����������
    BookingRequest bookingRequest_("John Doe", 2, "Standard", 3, rooms1.calculateCost(3));
    Booking booking(bookingRequest, rooms1);

    // ��������� ������ �� ����������
    Service breakfast_t("Breakfast", 15.0);
    Service transfer_r("Airport Transfer", 30.0);

    booking.addService(breakfast_t);
    booking.addService(transfer_r);

    // ��������� ������� ����������
    booking.displayBookingDetails();
    cout << "********************************\n" << endl;



    // ��������� � ��������� ��'��� Room �� ��������� ������� createDeluxeRoom
    Room myRoom = createDeluxeRoom();
    // ��������� ��������� ����� ��� ��������
    if (!myRoom.checkAvailability()) {
        cout << "The room has been booked successfully" << endl;
    }
    cout << "\n---------Simple method---------" << endl;
    // 1. ������� �����
    Room simpleRoom(2, "Standard", 50.0);  // ������ ��������� ��'����
    simpleRoom.displayRoomInfo();
    cout << "---------Explicit method---------" << endl;
    // 2. ����� �����
    Room explicitRoom = Room(3, "Deluxe", 80.0);  // ����� ������ ������������
    explicitRoom.displayRoomInfo();
    cout << "---------Shorted method---------" << endl;
    // 3. ���������� �����
    Room shortRoom{ 4, "Suite", 120.0 };  // ������ �����������
    shortRoom.displayRoomInfo();

    cout << "\n\n *|___System Hotel___|*" << endl;
    // ������ ���������� ��� ������
    Room room1(2, "Standard", 50.0);
    Room room2(3, "Deluxe", 80.0);
    Room room3(4, "Suite", 120.0);

    Service* services = new Service[5];
    services[0] = Service("Breakfast in room", 15.0);
    services[1] = Service("Transfer", 30.0);
    services[2] = Service("Pool Access", 20.0);
    services[3] = Service("Spa Treatment", 50.0);
    services[4] = Service("Dinner Package", 40.0);


    // ��������� ����� �� 5 �볺���
    BookingRequest static  clients[5] = {
        BookingRequest("Alice Smith", 2, "Standard", 3, room1.calculateCost(3)),
        BookingRequest("Bob Johnson", 3, "Deluxe", 4, room2.calculateCost(4)),
        BookingRequest("Charlie Brown", 2, "Standard", 2, room1.calculateCost(2)),
        BookingRequest("David Williams", 4, "Suite", 1, room3.calculateCost(1)),
        BookingRequest("Eve Miller", 3, "Deluxe", 5, room2.calculateCost(5))
    };

    // 4 �����
    //Room room1(2, "Standard", 50.0);
    //BookingRequest request("Alice Smith", 2, "Standard", 3, room1.calculateCost(3), 101, room1);
    //
    //
    //// ��������� ���������� ��� ����������
    //request.displayBookingInfo();
    //cout << "Booking ID: " << request.getBookingID() << endl;
    //cout << "Booked Room Info:" << endl;
    //request.getBookedRoom().displayRoomInfo();

    //  ���� �������� ������� ���������
    cout << "------------------" << endl;
    cout << "Total Bookings: " << BookingRequest::getTotalBookings() << endl;
    cout << "------------------" << endl;
    // ������� ������� ���������
    for (int i = 0; i < 5; i++) {
        displayBookingSummary(clients[i]);
    }
    // ������ ������������� ������� � ������������ ������
    for (int i = 0; i < 5; i++) {
        displayBookingSummary(clients[i], 0.15); // ���������, 15% ������
    }
    // ������� ���� � �������� ������ 
    BookingRequest copiedClient = clients[0];
    // �������� ���������� ��� ����������� �� ����������� �������� �� ����������
    cout << "__________________________________" << endl;
    cout << "Original Booking:" << endl;
    clients[0].displayBookingInfo();
    cout << "\nCopied Booking:" << endl;
    copiedClient.displayBookingInfo();
    cout << "__________________________________\n\n" << endl;



    // ��������� ���������� ��� ������� �볺��� �� ������������ ����������
    cout << "Booking Requests Before Confirmation:\n" << endl;
    for (int i = 0; i < 5; i++) {
        clients[i].displayBookingInfo();
    }
    cout << endl;
    // ��������� ��������� ������ ��� ������� �볺���
    for (int i = 0; i < 5; i++) {
        int randomServiceCount = rand() % 5; // ��������� ����� �� 0 �� 2 (������� ������ ��� �볺���)

        if (randomServiceCount > 0) clients[i].addService(services[0]); // ������ breakfast, ���� > 0
        if (randomServiceCount > 1) clients[i].addService(services[1]); // ������ transfer, ���� > 1
        if (randomServiceCount > 3) clients[i].addService(services[3]); // ������ Spa Treatment ���� > 3
        if (randomServiceCount > 1) clients[i].addService(services[4]); // ������ Dinner Package ���� > 1
        if (rand() % 2 == 0) clients[i].addService(services[2]);        // ������ poolAccess ��������� (50% ����)
    }


    // ϳ����������� ���������� ��� ��� �볺��� �� ��������� ���������� ���� ������������
    cout << "Booking Requests After Confirmation:" << endl;
    for (int i = 0; i < 5; i++) {
        clients[i].confirmBooking();
    }

    // ���������� ���������� � ����
    saveClientsToFile(clients, 5, "clients.txt");

    // ������������ �볺��� � ����� �� ��������� ����������
    cout << "Loaded Booking Requests:" << endl;
    BookingRequest::loadClientsFromFile(clients, 5, "clients.txt");
    for (int i = 0; i < 5; i++) {
        clients[i].displayBookingInfo();
    }

    // ��������� ���'��
    delete[] services;

    return 0;
}
