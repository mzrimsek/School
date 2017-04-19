require './location' 

class Ship
    attr_accessor :location
    attr_accessor :is_sunk

    def initialize(location, is_sunk)
        @location = location
        @is_sunk = is_sunk
    end
end