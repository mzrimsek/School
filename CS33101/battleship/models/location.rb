class Location
    attr_accessor :num_coord
    attr_accessor :char_coord
    
    def initialize(num_coord, char_coord)
        @num_coord = num_coord
        @char_coord = char_coord
    end

    def to_s
        "#{@num_coord}, #{@char_coord}"
    end
end