class Location
    attr_accessor :num_coord, :char_coord
    
    def initialize(num_coord, char_coord)
        @num_coord = num_coord
        @char_coord = char_coord
    end

    def ==(another_location)
        @num_coord == another_location.num_coord && @char_coord == another_location.char_coord
    end

    def to_s
        "#{@num_coord}, #{@char_coord}"
    end
end