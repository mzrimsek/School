require_relative './models/location'
require_relative './models/ship'
require_relative './getters/ship_getter'

class Game
    def initialize(num_ships)
        @num_ships = num_ships
        @fleet = ShipGetter.get_ships(num_ships)
        @sunk_ships = 0
    end

    def all_ships_sunk
        all_sunk = true

        @fleet.each do |ship|
            if !ship.is_sunk
                all_sunk = false
            end
        end

        all_sunk
    end

    def print_intro
        puts "Welcome to Battleship. The objective of the game is to sink all the ships in the ocean."
        puts "There are #{@num_ships} ships total. You will be asked to guess locations for the ships."
        puts "The ships locations are made of a number between 0 and 4, followed by a letter between A and E."
        puts "Good Luck!\n\n"
    end

    def print_congrats
        puts "Congrats you sunk all the ships"
    end

    def get_fire_location
        puts "\nEnter a location!"
        puts "Choose your first coordinate (integer between 0 and 4):"
        fire_num_coord = gets
        fire_num_coord = fire_num_coord.chomp
        puts "Choose your second coordinate (character between A and E):"
        fire_char_coord = gets
        fire_char_coord = fire_char_coord.chomp

        Location.new(fire_num_coord.to_i, fire_char_coord.to_s.upcase)
    end

    def update_ship(ship)
        if ship.is_sunk
            puts "You already hit that ship!\n"
        else
            ship.is_sunk = true
            @sunk_ships += 1
            puts "You hit a ship! (#{@sunk_ships}/#{@num_ships})\n"
        end
    end

    def take_turn
        fire_location = get_fire_location
        
        @fleet.each do |ship|
            if ship.location == fire_location
                update_ship(ship)
                return
            end
        end

        puts "Sorry, no ship here!\n"
    end

    def run
        print_intro
        while !all_ships_sunk do
            take_turn
        end
        print_congrats
    end
end

game = Game.new(5)
game.run