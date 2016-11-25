class Terminal
{
    public:
        Terminal(AutomatedParkingStructure);
        Ticket StoreCurrentVehicle();
        Vehicle RetrieveVehicle(Ticket);
        void SetCurrentCustomer(Customer);
        void SetCurrentVehicle(Vehicle);
}