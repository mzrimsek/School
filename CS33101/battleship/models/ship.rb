require_relative 'location' 

class Ship
    attr_accessor :location, :is_sunk

    def initialize(location, is_sunk)
        @location = location
        @is_sunk = is_sunk
    end

    def to_s
        "#{@location}\nSunk: #{@is_sunk}"
    end
end