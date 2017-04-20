require_relative '../models/location'
require_relative '../models/ship'

class ShipGetter
    private_class_method def self.get_random_location
        rand_num_coord = rand(0...6)
        rand_char_coord = rand(65...70).chr

        Location.new(rand_num_coord, rand_char_coord)
    end

    private_class_method def self.get_random_locations(num_locations)
        locations = []

        i = 0
        while i < num_locations do
            new_loc = get_random_location
            if !locations.include?(new_loc)
                locations.push(new_loc)
                i += 1
            end
        end

        locations
    end
    
    def self.get_ships(num_ships)
        ships = []

        locations = get_random_locations(num_ships)
        locations.each do |loc|
            newShip = Ship.new(loc, false)
            ships.push(newShip)
        end
        
        ships
    end
end