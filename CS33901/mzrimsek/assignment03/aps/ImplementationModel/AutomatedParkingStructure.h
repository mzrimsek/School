class AutomatedParkingStructure
{
    public:
        AutomatedParkingStructure(int, int);
        Ticket StoreVehicle(Customer, Vehicle);
        Vehicle RetrieveVehicle(Customer, Ticket);
        int GetTotalSpaces();
        int GetAvailableSpaces();
}