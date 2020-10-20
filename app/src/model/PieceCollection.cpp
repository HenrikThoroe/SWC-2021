#include "PieceCollection.hpp"

namespace Model {

    const std::array<Piece, 21> PieceCollection::allPieces = {
        Piece(
            0, 
            "MONO", 
            1, 
            
            {
                Rotation::ZERO
            }, 
            
            {
                std::tuple<Piece::Shape, Piece::AttachPoints>(
                    
                    {
                        Util::Vector2D(0, 0)
                    }, 
                    
                    {
                        
                        {
                            Util::Vector2D(-1, -1), 
                            Util::Vector2D(-1, -1)
                        }, 
                        
                        {
                            Util::Vector2D(1, -1), 
                            Util::Vector2D(1, -1)
                        }, 
                        
                        {
                            Util::Vector2D(-1, 1), 
                            Util::Vector2D(-1, 1)
                        }, 
                        
                        {
                            Util::Vector2D(1, 1), 
                            Util::Vector2D(1, 1)
                        }
                    }
                )
            }, 
            
            {
                0, 
                0, 
                0, 
                0, 
                0, 
                0, 
                0, 
                0
            }
        ),
        Piece(
            1, 
            "DOMINO", 
            2, 
            
            {
                Rotation::ZERO, 
                Rotation::ONEHALFPI
            }, 
            
            {
                std::tuple<Piece::Shape, Piece::AttachPoints>(
                    
                    {
                        Util::Vector2D(0, 0), 
                        Util::Vector2D(1, 0)
                    }, 
                    
                    {
                        
                        {
                            Util::Vector2D(-1, -1), 
                            Util::Vector2D(-1, -1)
                        }, 
                        
                        {
                            Util::Vector2D(-1, 1), 
                            Util::Vector2D(-1, 1)
                        }, 
                        
                        {
                            Util::Vector2D(2, -1), 
                            Util::Vector2D(1, -1)
                        }, 
                        
                        {
                            Util::Vector2D(2, 1), 
                            Util::Vector2D(1, 1)
                        }
                    }
                ), 
                std::tuple<Piece::Shape, Piece::AttachPoints>(
                    
                    {
                        Util::Vector2D(0, 0), 
                        Util::Vector2D(0, 1)
                    }, 
                    
                    {
                        
                        {
                            Util::Vector2D(1, -1), 
                            Util::Vector2D(1, -1)
                        }, 
                        
                        {
                            Util::Vector2D(-1, -1), 
                            Util::Vector2D(-1, -1)
                        }, 
                        
                        {
                            Util::Vector2D(1, 2), 
                            Util::Vector2D(1, 1)
                        }, 
                        
                        {
                            Util::Vector2D(-1, 2), 
                            Util::Vector2D(-1, 1)
                        }
                    }
                )
            }, 
            
            {
                0, 
                1, 
                0, 
                1, 
                0, 
                1, 
                0, 
                1
            }
        ),
        Piece(
            2, 
            "TRIO-L", 
            3, 
            
            {
                Rotation::ZERO, 
                Rotation::ONEHALFPI, 
                Rotation::PI, 
                Rotation::THREEHALFPI
            }, 
            
            {
                std::tuple<Piece::Shape, Piece::AttachPoints>(
                    
                    {
                        Util::Vector2D(0, 0), 
                        Util::Vector2D(0, 1), 
                        Util::Vector2D(1, 1)
                    }, 
                    
                    {
                        
                        {
                            Util::Vector2D(-1, -1), 
                            Util::Vector2D(-1, -1)
                        }, 
                        
                        {
                            Util::Vector2D(1, -1), 
                            Util::Vector2D(1, -1)
                        }, 
                        
                        {
                            Util::Vector2D(-1, 2), 
                            Util::Vector2D(-1, 1)
                        }, 
                        
                        {
                            Util::Vector2D(2, 0), 
                            Util::Vector2D(1, -1)
                        }, 
                        
                        {
                            Util::Vector2D(2, 2), 
                            Util::Vector2D(1, 1)
                        }
                    }
                ), 
                std::tuple<Piece::Shape, Piece::AttachPoints>(
                    
                    {
                        Util::Vector2D(0, 0), 
                        Util::Vector2D(-1, 0), 
                        Util::Vector2D(-1, 1)
                    }, 
                    
                    {
                        
                        {
                            Util::Vector2D(1, -1), 
                            Util::Vector2D(1, -1)
                        }, 
                        
                        {
                            Util::Vector2D(1, 1), 
                            Util::Vector2D(1, 1)
                        }, 
                        
                        {
                            Util::Vector2D(-2, -1), 
                            Util::Vector2D(-1, -1)
                        }, 
                        
                        {
                            Util::Vector2D(0, 2), 
                            Util::Vector2D(1, 1)
                        }, 
                        
                        {
                            Util::Vector2D(-2, 2), 
                            Util::Vector2D(-1, 1)
                        }
                    }
                ), 
                std::tuple<Piece::Shape, Piece::AttachPoints>(
                    
                    {
                        Util::Vector2D(0, 0), 
                        Util::Vector2D(0, -1), 
                        Util::Vector2D(-1, -1)
                    }, 
                    
                    {
                        
                        {
                            Util::Vector2D(1, 1), 
                            Util::Vector2D(1, 1)
                        }, 
                        
                        {
                            Util::Vector2D(-1, 1), 
                            Util::Vector2D(-1, 1)
                        }, 
                        
                        {
                            Util::Vector2D(1, -2), 
                            Util::Vector2D(1, -1)
                        }, 
                        
                        {
                            Util::Vector2D(-2, 0), 
                            Util::Vector2D(-1, 1)
                        }, 
                        
                        {
                            Util::Vector2D(-2, -2), 
                            Util::Vector2D(-1, -1)
                        }
                    }
                ), 
                std::tuple<Piece::Shape, Piece::AttachPoints>(
                    
                    {
                        Util::Vector2D(0, 0), 
                        Util::Vector2D(1, 0), 
                        Util::Vector2D(1, -1)
                    }, 
                    
                    {
                        
                        {
                            Util::Vector2D(-1, 1), 
                            Util::Vector2D(-1, 1)
                        }, 
                        
                        {
                            Util::Vector2D(-1, -1), 
                            Util::Vector2D(-1, -1)
                        }, 
                        
                        {
                            Util::Vector2D(2, 1), 
                            Util::Vector2D(1, 1)
                        }, 
                        
                        {
                            Util::Vector2D(0, -2), 
                            Util::Vector2D(-1, -1)
                        }, 
                        
                        {
                            Util::Vector2D(2, -2), 
                            Util::Vector2D(1, -1)
                        }
                    }
                )
            }, 
            
            {
                0, 
                1, 
                2, 
                3, 
                3, 
                0, 
                1, 
                2
            }
        ),
        Piece(
            3, 
            "TRIO-I", 
            3, 
            
            {
                Rotation::ZERO, 
                Rotation::ONEHALFPI
            }, 
            
            {
                std::tuple<Piece::Shape, Piece::AttachPoints>(
                    
                    {
                        Util::Vector2D(0, 0), 
                        Util::Vector2D(0, 1), 
                        Util::Vector2D(0, 2)
                    }, 
                    
                    {
                        
                        {
                            Util::Vector2D(-1, -1), 
                            Util::Vector2D(-1, -1)
                        }, 
                        
                        {
                            Util::Vector2D(1, -1), 
                            Util::Vector2D(1, -1)
                        }, 
                        
                        {
                            Util::Vector2D(-1, 3), 
                            Util::Vector2D(-1, 1)
                        }, 
                        
                        {
                            Util::Vector2D(1, 3), 
                            Util::Vector2D(1, 1)
                        }
                    }
                ), 
                std::tuple<Piece::Shape, Piece::AttachPoints>(
                    
                    {
                        Util::Vector2D(0, 0), 
                        Util::Vector2D(-1, 0), 
                        Util::Vector2D(-2, 0)
                    }, 
                    
                    {
                        
                        {
                            Util::Vector2D(1, -1), 
                            Util::Vector2D(1, -1)
                        }, 
                        
                        {
                            Util::Vector2D(1, 1), 
                            Util::Vector2D(1, 1)
                        }, 
                        
                        {
                            Util::Vector2D(-3, -1), 
                            Util::Vector2D(-1, -1)
                        }, 
                        
                        {
                            Util::Vector2D(-3, 1), 
                            Util::Vector2D(-1, 1)
                        }
                    }
                )
            }, 
            
            {
                0, 
                1, 
                0, 
                1, 
                0, 
                1, 
                0, 
                1
            }
        ),
        Piece(
            4, 
            "TETRO-I", 
            4, 
            
            {
                Rotation::ZERO, 
                Rotation::ONEHALFPI
            }, 
            
            {
                std::tuple<Piece::Shape, Piece::AttachPoints>(
                    
                    {
                        Util::Vector2D(0, 0), 
                        Util::Vector2D(0, 1), 
                        Util::Vector2D(0, 2), 
                        Util::Vector2D(0, 3)
                    }, 
                    
                    {
                        
                        {
                            Util::Vector2D(-1, -1), 
                            Util::Vector2D(-1, -1)
                        }, 
                        
                        {
                            Util::Vector2D(1, -1), 
                            Util::Vector2D(1, -1)
                        }, 
                        
                        {
                            Util::Vector2D(-1, 4), 
                            Util::Vector2D(-1, 1)
                        }, 
                        
                        {
                            Util::Vector2D(1, 4), 
                            Util::Vector2D(1, 1)
                        }
                    }
                ), 
                std::tuple<Piece::Shape, Piece::AttachPoints>(
                    
                    {
                        Util::Vector2D(0, 0), 
                        Util::Vector2D(-1, 0), 
                        Util::Vector2D(-2, 0), 
                        Util::Vector2D(-3, 0)
                    }, 
                    
                    {
                        
                        {
                            Util::Vector2D(1, -1), 
                            Util::Vector2D(1, -1)
                        }, 
                        
                        {
                            Util::Vector2D(1, 1), 
                            Util::Vector2D(1, 1)
                        }, 
                        
                        {
                            Util::Vector2D(-4, -1), 
                            Util::Vector2D(-1, -1)
                        }, 
                        
                        {
                            Util::Vector2D(-4, 1), 
                            Util::Vector2D(-1, 1)
                        }
                    }
                )
            }, 
            
            {
                0, 
                1, 
                0, 
                1, 
                0, 
                1, 
                0, 
                1
            }
        ),
        Piece(
            5, 
            "TETRO-L", 
            4, 
            
            {
                Rotation::ZERO, 
                Rotation::ONEHALFPI, 
                Rotation::PI, 
                Rotation::THREEHALFPI, 
                Rotation::ZERO_FLIPPED, 
                Rotation::ONEHALFPI_FLIPPED, 
                Rotation::PI_FLIPPED, 
                Rotation::THREEHALFPI_FLIPPED
            }, 
            
            {
                std::tuple<Piece::Shape, Piece::AttachPoints>(
                    
                    {
                        Util::Vector2D(0, 0), 
                        Util::Vector2D(0, 1), 
                        Util::Vector2D(0, 2), 
                        Util::Vector2D(1, 2)
                    }, 
                    
                    {
                        
                        {
                            Util::Vector2D(-1, -1), 
                            Util::Vector2D(-1, -1)
                        }, 
                        
                        {
                            Util::Vector2D(1, -1), 
                            Util::Vector2D(1, -1)
                        }, 
                        
                        {
                            Util::Vector2D(-1, 3), 
                            Util::Vector2D(-1, 1)
                        }, 
                        
                        {
                            Util::Vector2D(2, 1), 
                            Util::Vector2D(1, -1)
                        }, 
                        
                        {
                            Util::Vector2D(2, 3), 
                            Util::Vector2D(1, 1)
                        }
                    }
                ), 
                std::tuple<Piece::Shape, Piece::AttachPoints>(
                    
                    {
                        Util::Vector2D(0, 0), 
                        Util::Vector2D(-1, 0), 
                        Util::Vector2D(-2, 0), 
                        Util::Vector2D(-2, 1)
                    }, 
                    
                    {
                        
                        {
                            Util::Vector2D(1, -1), 
                            Util::Vector2D(1, -1)
                        }, 
                        
                        {
                            Util::Vector2D(1, 1), 
                            Util::Vector2D(1, 1)
                        }, 
                        
                        {
                            Util::Vector2D(-3, -1), 
                            Util::Vector2D(-1, -1)
                        }, 
                        
                        {
                            Util::Vector2D(-1, 2), 
                            Util::Vector2D(1, 1)
                        }, 
                        
                        {
                            Util::Vector2D(-3, 2), 
                            Util::Vector2D(-1, 1)
                        }
                    }
                ), 
                std::tuple<Piece::Shape, Piece::AttachPoints>(
                    
                    {
                        Util::Vector2D(0, 0), 
                        Util::Vector2D(0, -1), 
                        Util::Vector2D(0, -2), 
                        Util::Vector2D(-1, -2)
                    }, 
                    
                    {
                        
                        {
                            Util::Vector2D(1, 1), 
                            Util::Vector2D(1, 1)
                        }, 
                        
                        {
                            Util::Vector2D(-1, 1), 
                            Util::Vector2D(-1, 1)
                        }, 
                        
                        {
                            Util::Vector2D(1, -3), 
                            Util::Vector2D(1, -1)
                        }, 
                        
                        {
                            Util::Vector2D(-2, -1), 
                            Util::Vector2D(-1, 1)
                        }, 
                        
                        {
                            Util::Vector2D(-2, -3), 
                            Util::Vector2D(-1, -1)
                        }
                    }
                ), 
                std::tuple<Piece::Shape, Piece::AttachPoints>(
                    
                    {
                        Util::Vector2D(0, 0), 
                        Util::Vector2D(1, 0), 
                        Util::Vector2D(2, 0), 
                        Util::Vector2D(2, -1)
                    }, 
                    
                    {
                        
                        {
                            Util::Vector2D(-1, 1), 
                            Util::Vector2D(-1, 1)
                        }, 
                        
                        {
                            Util::Vector2D(-1, -1), 
                            Util::Vector2D(-1, -1)
                        }, 
                        
                        {
                            Util::Vector2D(3, 1), 
                            Util::Vector2D(1, 1)
                        }, 
                        
                        {
                            Util::Vector2D(1, -2), 
                            Util::Vector2D(-1, -1)
                        }, 
                        
                        {
                            Util::Vector2D(3, -2), 
                            Util::Vector2D(1, -1)
                        }
                    }
                ), 
                std::tuple<Piece::Shape, Piece::AttachPoints>(
                    
                    {
                        Util::Vector2D(0, 0), 
                        Util::Vector2D(0, 1), 
                        Util::Vector2D(0, 2), 
                        Util::Vector2D(-1, 2)
                    }, 
                    
                    {
                        
                        {
                            Util::Vector2D(-1, -1), 
                            Util::Vector2D(-1, -1)
                        }, 
                        
                        {
                            Util::Vector2D(1, -1), 
                            Util::Vector2D(1, -1)
                        }, 
                        
                        {
                            Util::Vector2D(1, 3), 
                            Util::Vector2D(1, 1)
                        }, 
                        
                        {
                            Util::Vector2D(-2, 1), 
                            Util::Vector2D(-1, -1)
                        }, 
                        
                        {
                            Util::Vector2D(-2, 3), 
                            Util::Vector2D(-1, 1)
                        }
                    }
                ), 
                std::tuple<Piece::Shape, Piece::AttachPoints>(
                    
                    {
                        Util::Vector2D(0, 0), 
                        Util::Vector2D(-1, 0), 
                        Util::Vector2D(-2, 0), 
                        Util::Vector2D(-2, -1)
                    }, 
                    
                    {
                        
                        {
                            Util::Vector2D(1, -1), 
                            Util::Vector2D(1, -1)
                        }, 
                        
                        {
                            Util::Vector2D(1, 1), 
                            Util::Vector2D(1, 1)
                        }, 
                        
                        {
                            Util::Vector2D(-3, 1), 
                            Util::Vector2D(-1, 1)
                        }, 
                        
                        {
                            Util::Vector2D(-1, -2), 
                            Util::Vector2D(1, -1)
                        }, 
                        
                        {
                            Util::Vector2D(-3, -2), 
                            Util::Vector2D(-1, -1)
                        }
                    }
                ), 
                std::tuple<Piece::Shape, Piece::AttachPoints>(
                    
                    {
                        Util::Vector2D(0, 0), 
                        Util::Vector2D(0, -1), 
                        Util::Vector2D(0, -2), 
                        Util::Vector2D(1, -2)
                    }, 
                    
                    {
                        
                        {
                            Util::Vector2D(1, 1), 
                            Util::Vector2D(1, 1)
                        }, 
                        
                        {
                            Util::Vector2D(-1, 1), 
                            Util::Vector2D(-1, 1)
                        }, 
                        
                        {
                            Util::Vector2D(-1, -3), 
                            Util::Vector2D(-1, -1)
                        }, 
                        
                        {
                            Util::Vector2D(2, -1), 
                            Util::Vector2D(1, 1)
                        }, 
                        
                        {
                            Util::Vector2D(2, -3), 
                            Util::Vector2D(1, -1)
                        }
                    }
                ), 
                std::tuple<Piece::Shape, Piece::AttachPoints>(
                    
                    {
                        Util::Vector2D(0, 0), 
                        Util::Vector2D(1, 0), 
                        Util::Vector2D(2, 0), 
                        Util::Vector2D(2, 1)
                    }, 
                    
                    {
                        
                        {
                            Util::Vector2D(-1, 1), 
                            Util::Vector2D(-1, 1)
                        }, 
                        
                        {
                            Util::Vector2D(-1, -1), 
                            Util::Vector2D(-1, -1)
                        }, 
                        
                        {
                            Util::Vector2D(3, -1), 
                            Util::Vector2D(1, -1)
                        }, 
                        
                        {
                            Util::Vector2D(1, 2), 
                            Util::Vector2D(-1, 1)
                        }, 
                        
                        {
                            Util::Vector2D(3, 2), 
                            Util::Vector2D(1, 1)
                        }
                    }
                )
            }, 
            
            {
                0, 
                1, 
                2, 
                3, 
                4, 
                5, 
                6, 
                7
            }
        ),
        Piece(
            6, 
            "TETRO-O", 
            4, 
            
            {
                Rotation::ZERO
            }, 
            
            {
                std::tuple<Piece::Shape, Piece::AttachPoints>(
                    
                    {
                        Util::Vector2D(0, 0), 
                        Util::Vector2D(0, 1), 
                        Util::Vector2D(1, 1), 
                        Util::Vector2D(1, 0)
                    }, 
                    
                    {
                        
                        {
                            Util::Vector2D(-1, -1), 
                            Util::Vector2D(-1, -1)
                        }, 
                        
                        {
                            Util::Vector2D(-1, 2), 
                            Util::Vector2D(-1, 1)
                        }, 
                        
                        {
                            Util::Vector2D(2, 2), 
                            Util::Vector2D(1, 1)
                        }, 
                        
                        {
                            Util::Vector2D(2, -1), 
                            Util::Vector2D(1, -1)
                        }
                    }
                )
            }, 
            
            {
                0, 
                0, 
                0, 
                0, 
                0, 
                0, 
                0, 
                0
            }
        ),
        Piece(
            7, 
            "TETRO-T", 
            4, 
            
            {
                Rotation::ZERO, 
                Rotation::ONEHALFPI, 
                Rotation::PI, 
                Rotation::THREEHALFPI
            }, 
            
            {
                std::tuple<Piece::Shape, Piece::AttachPoints>(
                    
                    {
                        Util::Vector2D(0, 0), 
                        Util::Vector2D(1, 0), 
                        Util::Vector2D(2, 0), 
                        Util::Vector2D(1, 1)
                    }, 
                    
                    {
                        
                        {
                            Util::Vector2D(-1, -1), 
                            Util::Vector2D(-1, -1)
                        }, 
                        
                        {
                            Util::Vector2D(-1, 1), 
                            Util::Vector2D(-1, 1)
                        }, 
                        
                        {
                            Util::Vector2D(3, -1), 
                            Util::Vector2D(1, -1)
                        }, 
                        
                        {
                            Util::Vector2D(3, 1), 
                            Util::Vector2D(1, 1)
                        }, 
                        
                        {
                            Util::Vector2D(0, 2), 
                            Util::Vector2D(-1, 1)
                        }, 
                        
                        {
                            Util::Vector2D(2, 2), 
                            Util::Vector2D(1, 1)
                        }
                    }
                ), 
                std::tuple<Piece::Shape, Piece::AttachPoints>(
                    
                    {
                        Util::Vector2D(0, 0), 
                        Util::Vector2D(0, 1), 
                        Util::Vector2D(0, 2), 
                        Util::Vector2D(-1, 1)
                    }, 
                    
                    {
                        
                        {
                            Util::Vector2D(1, -1), 
                            Util::Vector2D(1, -1)
                        }, 
                        
                        {
                            Util::Vector2D(-1, -1), 
                            Util::Vector2D(-1, -1)
                        }, 
                        
                        {
                            Util::Vector2D(1, 3), 
                            Util::Vector2D(1, 1)
                        }, 
                        
                        {
                            Util::Vector2D(-1, 3), 
                            Util::Vector2D(-1, 1)
                        }, 
                        
                        {
                            Util::Vector2D(-2, 0), 
                            Util::Vector2D(-1, -1)
                        }, 
                        
                        {
                            Util::Vector2D(-2, 2), 
                            Util::Vector2D(-1, 1)
                        }
                    }
                ), 
                std::tuple<Piece::Shape, Piece::AttachPoints>(
                    
                    {
                        Util::Vector2D(0, 0), 
                        Util::Vector2D(-1, 0), 
                        Util::Vector2D(-2, 0), 
                        Util::Vector2D(-1, -1)
                    }, 
                    
                    {
                        
                        {
                            Util::Vector2D(1, 1), 
                            Util::Vector2D(1, 1)
                        }, 
                        
                        {
                            Util::Vector2D(1, -1), 
                            Util::Vector2D(1, -1)
                        }, 
                        
                        {
                            Util::Vector2D(-3, 1), 
                            Util::Vector2D(-1, 1)
                        }, 
                        
                        {
                            Util::Vector2D(-3, -1), 
                            Util::Vector2D(-1, -1)
                        }, 
                        
                        {
                            Util::Vector2D(0, -2), 
                            Util::Vector2D(1, -1)
                        }, 
                        
                        {
                            Util::Vector2D(-2, -2), 
                            Util::Vector2D(-1, -1)
                        }
                    }
                ), 
                std::tuple<Piece::Shape, Piece::AttachPoints>(
                    
                    {
                        Util::Vector2D(0, 0), 
                        Util::Vector2D(0, -1), 
                        Util::Vector2D(0, -2), 
                        Util::Vector2D(1, -1)
                    }, 
                    
                    {
                        
                        {
                            Util::Vector2D(-1, 1), 
                            Util::Vector2D(-1, 1)
                        }, 
                        
                        {
                            Util::Vector2D(1, 1), 
                            Util::Vector2D(1, 1)
                        }, 
                        
                        {
                            Util::Vector2D(-1, -3), 
                            Util::Vector2D(-1, -1)
                        }, 
                        
                        {
                            Util::Vector2D(1, -3), 
                            Util::Vector2D(1, -1)
                        }, 
                        
                        {
                            Util::Vector2D(2, 0), 
                            Util::Vector2D(1, 1)
                        }, 
                        
                        {
                            Util::Vector2D(2, -2), 
                            Util::Vector2D(1, -1)
                        }
                    }
                )
            }, 
            
            {
                0, 
                1, 
                2, 
                3, 
                0, 
                1, 
                2, 
                3
            }
        ),
        Piece(
            8, 
            "TETRO-Z", 
            4, 
            
            {
                Rotation::ZERO, 
                Rotation::ONEHALFPI, 
                Rotation::ZERO_FLIPPED, 
                Rotation::ONEHALFPI_FLIPPED
            }, 
            
            {
                std::tuple<Piece::Shape, Piece::AttachPoints>(
                    
                    {
                        Util::Vector2D(0, 0), 
                        Util::Vector2D(1, 0), 
                        Util::Vector2D(1, 1), 
                        Util::Vector2D(2, 1)
                    }, 
                    
                    {
                        
                        {
                            Util::Vector2D(-1, -1), 
                            Util::Vector2D(-1, -1)
                        }, 
                        
                        {
                            Util::Vector2D(-1, 1), 
                            Util::Vector2D(-1, 1)
                        }, 
                        
                        {
                            Util::Vector2D(2, -1), 
                            Util::Vector2D(1, -1)
                        }, 
                        
                        {
                            Util::Vector2D(0, 2), 
                            Util::Vector2D(-1, 1)
                        }, 
                        
                        {
                            Util::Vector2D(3, 0), 
                            Util::Vector2D(1, -1)
                        }, 
                        
                        {
                            Util::Vector2D(3, 2), 
                            Util::Vector2D(1, 1)
                        }
                    }
                ), 
                std::tuple<Piece::Shape, Piece::AttachPoints>(
                    
                    {
                        Util::Vector2D(0, 0), 
                        Util::Vector2D(0, 1), 
                        Util::Vector2D(-1, 1), 
                        Util::Vector2D(-1, 2)
                    }, 
                    
                    {
                        
                        {
                            Util::Vector2D(1, -1), 
                            Util::Vector2D(1, -1)
                        }, 
                        
                        {
                            Util::Vector2D(-1, -1), 
                            Util::Vector2D(-1, -1)
                        }, 
                        
                        {
                            Util::Vector2D(1, 2), 
                            Util::Vector2D(1, 1)
                        }, 
                        
                        {
                            Util::Vector2D(-2, 0), 
                            Util::Vector2D(-1, -1)
                        }, 
                        
                        {
                            Util::Vector2D(0, 3), 
                            Util::Vector2D(1, 1)
                        }, 
                        
                        {
                            Util::Vector2D(-2, 3), 
                            Util::Vector2D(-1, 1)
                        }
                    }
                ), 
                std::tuple<Piece::Shape, Piece::AttachPoints>(
                    
                    {
                        Util::Vector2D(0, 0), 
                        Util::Vector2D(-1, 0), 
                        Util::Vector2D(-1, 1), 
                        Util::Vector2D(-2, 1)
                    }, 
                    
                    {
                        
                        {
                            Util::Vector2D(1, -1), 
                            Util::Vector2D(1, -1)
                        }, 
                        
                        {
                            Util::Vector2D(1, 1), 
                            Util::Vector2D(1, 1)
                        }, 
                        
                        {
                            Util::Vector2D(-2, -1), 
                            Util::Vector2D(-1, -1)
                        }, 
                        
                        {
                            Util::Vector2D(0, 2), 
                            Util::Vector2D(1, 1)
                        }, 
                        
                        {
                            Util::Vector2D(-3, 0), 
                            Util::Vector2D(-1, -1)
                        }, 
                        
                        {
                            Util::Vector2D(-3, 2), 
                            Util::Vector2D(-1, 1)
                        }
                    }
                ), 
                std::tuple<Piece::Shape, Piece::AttachPoints>(
                    
                    {
                        Util::Vector2D(0, 0), 
                        Util::Vector2D(0, -1), 
                        Util::Vector2D(-1, -1), 
                        Util::Vector2D(-1, -2)
                    }, 
                    
                    {
                        
                        {
                            Util::Vector2D(1, 1), 
                            Util::Vector2D(1, 1)
                        }, 
                        
                        {
                            Util::Vector2D(-1, 1), 
                            Util::Vector2D(-1, 1)
                        }, 
                        
                        {
                            Util::Vector2D(1, -2), 
                            Util::Vector2D(1, -1)
                        }, 
                        
                        {
                            Util::Vector2D(-2, 0), 
                            Util::Vector2D(-1, 1)
                        }, 
                        
                        {
                            Util::Vector2D(0, -3), 
                            Util::Vector2D(1, -1)
                        }, 
                        
                        {
                            Util::Vector2D(-2, -3), 
                            Util::Vector2D(-1, -1)
                        }
                    }
                )
            }, 
            
            {
                0, 
                1, 
                0, 
                1, 
                2, 
                3, 
                2, 
                3
            }
        ),
        Piece(
            9, 
            "PENTO-I", 
            5, 
            
            {
                Rotation::ZERO, 
                Rotation::ONEHALFPI
            }, 
            
            {
                std::tuple<Piece::Shape, Piece::AttachPoints>(
                    
                    {
                        Util::Vector2D(0, 0), 
                        Util::Vector2D(0, 1), 
                        Util::Vector2D(0, 2), 
                        Util::Vector2D(0, 3), 
                        Util::Vector2D(0, 4)
                    }, 
                    
                    {
                        
                        {
                            Util::Vector2D(-1, -1), 
                            Util::Vector2D(-1, -1)
                        }, 
                        
                        {
                            Util::Vector2D(1, -1), 
                            Util::Vector2D(1, -1)
                        }, 
                        
                        {
                            Util::Vector2D(-1, 5), 
                            Util::Vector2D(-1, 1)
                        }, 
                        
                        {
                            Util::Vector2D(1, 5), 
                            Util::Vector2D(1, 1)
                        }
                    }
                ), 
                std::tuple<Piece::Shape, Piece::AttachPoints>(
                    
                    {
                        Util::Vector2D(0, 0), 
                        Util::Vector2D(-1, 0), 
                        Util::Vector2D(-2, 0), 
                        Util::Vector2D(-3, 0), 
                        Util::Vector2D(-4, 0)
                    }, 
                    
                    {
                        
                        {
                            Util::Vector2D(1, -1), 
                            Util::Vector2D(1, -1)
                        }, 
                        
                        {
                            Util::Vector2D(1, 1), 
                            Util::Vector2D(1, 1)
                        }, 
                        
                        {
                            Util::Vector2D(-5, -1), 
                            Util::Vector2D(-1, -1)
                        }, 
                        
                        {
                            Util::Vector2D(-5, 1), 
                            Util::Vector2D(-1, 1)
                        }
                    }
                )
            }, 
            
            {
                0, 
                1, 
                0, 
                1, 
                0, 
                1, 
                0, 
                1
            }
        ),
        Piece(
            10, 
            "PENTO-U", 
            5, 
            
            {
                Rotation::ZERO, 
                Rotation::ONEHALFPI, 
                Rotation::PI, 
                Rotation::THREEHALFPI
            }, 
            
            {
                std::tuple<Piece::Shape, Piece::AttachPoints>(
                    
                    {
                        Util::Vector2D(0, 0), 
                        Util::Vector2D(0, 1), 
                        Util::Vector2D(1, 1), 
                        Util::Vector2D(2, 1), 
                        Util::Vector2D(2, 0)
                    }, 
                    
                    {
                        
                        {
                            Util::Vector2D(-1, -1), 
                            Util::Vector2D(-1, -1)
                        }, 
                        
                        {
                            Util::Vector2D(1, -1), 
                            Util::Vector2D(1, -1)
                        }, 
                        
                        {
                            Util::Vector2D(-1, 2), 
                            Util::Vector2D(-1, 1)
                        }, 
                        
                        {
                            Util::Vector2D(3, 2), 
                            Util::Vector2D(1, 1)
                        }, 
                        
                        {
                            Util::Vector2D(1, -1), 
                            Util::Vector2D(-1, -1)
                        }, 
                        
                        {
                            Util::Vector2D(3, -1), 
                            Util::Vector2D(1, -1)
                        }
                    }
                ), 
                std::tuple<Piece::Shape, Piece::AttachPoints>(
                    
                    {
                        Util::Vector2D(0, 0), 
                        Util::Vector2D(-1, 0), 
                        Util::Vector2D(-1, 1), 
                        Util::Vector2D(-1, 2), 
                        Util::Vector2D(0, 2)
                    }, 
                    
                    {
                        
                        {
                            Util::Vector2D(1, -1), 
                            Util::Vector2D(1, -1)
                        }, 
                        
                        {
                            Util::Vector2D(1, 1), 
                            Util::Vector2D(1, 1)
                        }, 
                        
                        {
                            Util::Vector2D(-2, -1), 
                            Util::Vector2D(-1, -1)
                        }, 
                        
                        {
                            Util::Vector2D(-2, 3), 
                            Util::Vector2D(-1, 1)
                        }, 
                        
                        {
                            Util::Vector2D(1, 1), 
                            Util::Vector2D(1, -1)
                        }, 
                        
                        {
                            Util::Vector2D(1, 3), 
                            Util::Vector2D(1, 1)
                        }
                    }
                ), 
                std::tuple<Piece::Shape, Piece::AttachPoints>(
                    
                    {
                        Util::Vector2D(0, 0), 
                        Util::Vector2D(0, -1), 
                        Util::Vector2D(-1, -1), 
                        Util::Vector2D(-2, -1), 
                        Util::Vector2D(-2, 0)
                    }, 
                    
                    {
                        
                        {
                            Util::Vector2D(1, 1), 
                            Util::Vector2D(1, 1)
                        }, 
                        
                        {
                            Util::Vector2D(-1, 1), 
                            Util::Vector2D(-1, 1)
                        }, 
                        
                        {
                            Util::Vector2D(1, -2), 
                            Util::Vector2D(1, -1)
                        }, 
                        
                        {
                            Util::Vector2D(-3, -2), 
                            Util::Vector2D(-1, -1)
                        }, 
                        
                        {
                            Util::Vector2D(-1, 1), 
                            Util::Vector2D(1, 1)
                        }, 
                        
                        {
                            Util::Vector2D(-3, 1), 
                            Util::Vector2D(-1, 1)
                        }
                    }
                ), 
                std::tuple<Piece::Shape, Piece::AttachPoints>(
                    
                    {
                        Util::Vector2D(0, 0), 
                        Util::Vector2D(1, 0), 
                        Util::Vector2D(1, -1), 
                        Util::Vector2D(1, -2), 
                        Util::Vector2D(0, -2)
                    }, 
                    
                    {
                        
                        {
                            Util::Vector2D(-1, 1), 
                            Util::Vector2D(-1, 1)
                        }, 
                        
                        {
                            Util::Vector2D(-1, -1), 
                            Util::Vector2D(-1, -1)
                        }, 
                        
                        {
                            Util::Vector2D(2, 1), 
                            Util::Vector2D(1, 1)
                        }, 
                        
                        {
                            Util::Vector2D(2, -3), 
                            Util::Vector2D(1, -1)
                        }, 
                        
                        {
                            Util::Vector2D(-1, -1), 
                            Util::Vector2D(-1, 1)
                        }, 
                        
                        {
                            Util::Vector2D(-1, -3), 
                            Util::Vector2D(-1, -1)
                        }
                    }
                )
            }, 
            
            {
                0, 
                1, 
                2, 
                3, 
                0, 
                1, 
                2, 
                3
            }
        ),
        Piece(
            11, 
            "PENTO-L", 
            5, 
            
            {
                Rotation::ZERO, 
                Rotation::ONEHALFPI, 
                Rotation::PI, 
                Rotation::THREEHALFPI, 
                Rotation::ZERO_FLIPPED, 
                Rotation::ONEHALFPI_FLIPPED, 
                Rotation::PI_FLIPPED, 
                Rotation::THREEHALFPI_FLIPPED
            }, 
            
            {
                std::tuple<Piece::Shape, Piece::AttachPoints>(
                    
                    {
                        Util::Vector2D(0, 0), 
                        Util::Vector2D(0, 1), 
                        Util::Vector2D(0, 2), 
                        Util::Vector2D(0, 3), 
                        Util::Vector2D(1, 3)
                    }, 
                    
                    {
                        
                        {
                            Util::Vector2D(-1, -1), 
                            Util::Vector2D(-1, -1)
                        }, 
                        
                        {
                            Util::Vector2D(1, -1), 
                            Util::Vector2D(1, -1)
                        }, 
                        
                        {
                            Util::Vector2D(-1, 4), 
                            Util::Vector2D(-1, 1)
                        }, 
                        
                        {
                            Util::Vector2D(2, 2), 
                            Util::Vector2D(1, -1)
                        }, 
                        
                        {
                            Util::Vector2D(2, 4), 
                            Util::Vector2D(1, 1)
                        }
                    }
                ), 
                std::tuple<Piece::Shape, Piece::AttachPoints>(
                    
                    {
                        Util::Vector2D(0, 0), 
                        Util::Vector2D(-1, 0), 
                        Util::Vector2D(-2, 0), 
                        Util::Vector2D(-3, 0), 
                        Util::Vector2D(-3, 1)
                    }, 
                    
                    {
                        
                        {
                            Util::Vector2D(1, -1), 
                            Util::Vector2D(1, -1)
                        }, 
                        
                        {
                            Util::Vector2D(1, 1), 
                            Util::Vector2D(1, 1)
                        }, 
                        
                        {
                            Util::Vector2D(-4, -1), 
                            Util::Vector2D(-1, -1)
                        }, 
                        
                        {
                            Util::Vector2D(-2, 2), 
                            Util::Vector2D(1, 1)
                        }, 
                        
                        {
                            Util::Vector2D(-4, 2), 
                            Util::Vector2D(-1, 1)
                        }
                    }
                ), 
                std::tuple<Piece::Shape, Piece::AttachPoints>(
                    
                    {
                        Util::Vector2D(0, 0), 
                        Util::Vector2D(0, -1), 
                        Util::Vector2D(0, -2), 
                        Util::Vector2D(0, -3), 
                        Util::Vector2D(-1, -3)
                    }, 
                    
                    {
                        
                        {
                            Util::Vector2D(1, 1), 
                            Util::Vector2D(1, 1)
                        }, 
                        
                        {
                            Util::Vector2D(-1, 1), 
                            Util::Vector2D(-1, 1)
                        }, 
                        
                        {
                            Util::Vector2D(1, -4), 
                            Util::Vector2D(1, -1)
                        }, 
                        
                        {
                            Util::Vector2D(-2, -2), 
                            Util::Vector2D(-1, 1)
                        }, 
                        
                        {
                            Util::Vector2D(-2, -4), 
                            Util::Vector2D(-1, -1)
                        }
                    }
                ), 
                std::tuple<Piece::Shape, Piece::AttachPoints>(
                    
                    {
                        Util::Vector2D(0, 0), 
                        Util::Vector2D(1, 0), 
                        Util::Vector2D(2, 0), 
                        Util::Vector2D(3, 0), 
                        Util::Vector2D(3, -1)
                    }, 
                    
                    {
                        
                        {
                            Util::Vector2D(-1, 1), 
                            Util::Vector2D(-1, 1)
                        }, 
                        
                        {
                            Util::Vector2D(-1, -1), 
                            Util::Vector2D(-1, -1)
                        }, 
                        
                        {
                            Util::Vector2D(4, 1), 
                            Util::Vector2D(1, 1)
                        }, 
                        
                        {
                            Util::Vector2D(2, -2), 
                            Util::Vector2D(-1, -1)
                        }, 
                        
                        {
                            Util::Vector2D(4, -2), 
                            Util::Vector2D(1, -1)
                        }
                    }
                ), 
                std::tuple<Piece::Shape, Piece::AttachPoints>(
                    
                    {
                        Util::Vector2D(0, 0), 
                        Util::Vector2D(0, 1), 
                        Util::Vector2D(0, 2), 
                        Util::Vector2D(0, 3), 
                        Util::Vector2D(-1, 3)
                    }, 
                    
                    {
                        
                        {
                            Util::Vector2D(-1, -1), 
                            Util::Vector2D(-1, -1)
                        }, 
                        
                        {
                            Util::Vector2D(1, -1), 
                            Util::Vector2D(1, -1)
                        }, 
                        
                        {
                            Util::Vector2D(1, 4), 
                            Util::Vector2D(1, 1)
                        }, 
                        
                        {
                            Util::Vector2D(-2, 2), 
                            Util::Vector2D(-1, -1)
                        }, 
                        
                        {
                            Util::Vector2D(-2, 4), 
                            Util::Vector2D(-1, 1)
                        }
                    }
                ), 
                std::tuple<Piece::Shape, Piece::AttachPoints>(
                    
                    {
                        Util::Vector2D(0, 0), 
                        Util::Vector2D(-1, 0), 
                        Util::Vector2D(-2, 0), 
                        Util::Vector2D(-3, 0), 
                        Util::Vector2D(-3, -1)
                    }, 
                    
                    {
                        
                        {
                            Util::Vector2D(1, -1), 
                            Util::Vector2D(1, -1)
                        }, 
                        
                        {
                            Util::Vector2D(1, 1), 
                            Util::Vector2D(1, 1)
                        }, 
                        
                        {
                            Util::Vector2D(-4, 1), 
                            Util::Vector2D(-1, 1)
                        }, 
                        
                        {
                            Util::Vector2D(-2, -2), 
                            Util::Vector2D(1, -1)
                        }, 
                        
                        {
                            Util::Vector2D(-4, -2), 
                            Util::Vector2D(-1, -1)
                        }
                    }
                ), 
                std::tuple<Piece::Shape, Piece::AttachPoints>(
                    
                    {
                        Util::Vector2D(0, 0), 
                        Util::Vector2D(0, -1), 
                        Util::Vector2D(0, -2), 
                        Util::Vector2D(0, -3), 
                        Util::Vector2D(1, -3)
                    }, 
                    
                    {
                        
                        {
                            Util::Vector2D(1, 1), 
                            Util::Vector2D(1, 1)
                        }, 
                        
                        {
                            Util::Vector2D(-1, 1), 
                            Util::Vector2D(-1, 1)
                        }, 
                        
                        {
                            Util::Vector2D(-1, -4), 
                            Util::Vector2D(-1, -1)
                        }, 
                        
                        {
                            Util::Vector2D(2, -2), 
                            Util::Vector2D(1, 1)
                        }, 
                        
                        {
                            Util::Vector2D(2, -4), 
                            Util::Vector2D(1, -1)
                        }
                    }
                ), 
                std::tuple<Piece::Shape, Piece::AttachPoints>(
                    
                    {
                        Util::Vector2D(0, 0), 
                        Util::Vector2D(1, 0), 
                        Util::Vector2D(2, 0), 
                        Util::Vector2D(3, 0), 
                        Util::Vector2D(3, 1)
                    }, 
                    
                    {
                        
                        {
                            Util::Vector2D(-1, 1), 
                            Util::Vector2D(-1, 1)
                        }, 
                        
                        {
                            Util::Vector2D(-1, -1), 
                            Util::Vector2D(-1, -1)
                        }, 
                        
                        {
                            Util::Vector2D(4, -1), 
                            Util::Vector2D(1, -1)
                        }, 
                        
                        {
                            Util::Vector2D(2, 2), 
                            Util::Vector2D(-1, 1)
                        }, 
                        
                        {
                            Util::Vector2D(4, 2), 
                            Util::Vector2D(1, 1)
                        }
                    }
                )
            }, 
            
            {
                0, 
                1, 
                2, 
                3, 
                4, 
                5, 
                6, 
                7
            }
        ),
        Piece(
            12, 
            "PENTO-V", 
            5, 
            
            {
                Rotation::ZERO, 
                Rotation::ONEHALFPI, 
                Rotation::PI, 
                Rotation::THREEHALFPI
            }, 
            
            {
                std::tuple<Piece::Shape, Piece::AttachPoints>(
                    
                    {
                        Util::Vector2D(0, 0), 
                        Util::Vector2D(0, 1), 
                        Util::Vector2D(0, 2), 
                        Util::Vector2D(1, 2), 
                        Util::Vector2D(2, 2)
                    }, 
                    
                    {
                        
                        {
                            Util::Vector2D(-1, -1), 
                            Util::Vector2D(-1, -1)
                        }, 
                        
                        {
                            Util::Vector2D(1, -1), 
                            Util::Vector2D(1, -1)
                        }, 
                        
                        {
                            Util::Vector2D(-1, 3), 
                            Util::Vector2D(-1, 1)
                        }, 
                        
                        {
                            Util::Vector2D(3, 1), 
                            Util::Vector2D(1, -1)
                        }, 
                        
                        {
                            Util::Vector2D(3, 3), 
                            Util::Vector2D(1, 1)
                        }
                    }
                ), 
                std::tuple<Piece::Shape, Piece::AttachPoints>(
                    
                    {
                        Util::Vector2D(0, 0), 
                        Util::Vector2D(-1, 0), 
                        Util::Vector2D(-2, 0), 
                        Util::Vector2D(-2, 1), 
                        Util::Vector2D(-2, 2)
                    }, 
                    
                    {
                        
                        {
                            Util::Vector2D(1, -1), 
                            Util::Vector2D(1, -1)
                        }, 
                        
                        {
                            Util::Vector2D(1, 1), 
                            Util::Vector2D(1, 1)
                        }, 
                        
                        {
                            Util::Vector2D(-3, -1), 
                            Util::Vector2D(-1, -1)
                        }, 
                        
                        {
                            Util::Vector2D(-1, 3), 
                            Util::Vector2D(1, 1)
                        }, 
                        
                        {
                            Util::Vector2D(-3, 3), 
                            Util::Vector2D(-1, 1)
                        }
                    }
                ), 
                std::tuple<Piece::Shape, Piece::AttachPoints>(
                    
                    {
                        Util::Vector2D(0, 0), 
                        Util::Vector2D(0, -1), 
                        Util::Vector2D(0, -2), 
                        Util::Vector2D(-1, -2), 
                        Util::Vector2D(-2, -2)
                    }, 
                    
                    {
                        
                        {
                            Util::Vector2D(1, 1), 
                            Util::Vector2D(1, 1)
                        }, 
                        
                        {
                            Util::Vector2D(-1, 1), 
                            Util::Vector2D(-1, 1)
                        }, 
                        
                        {
                            Util::Vector2D(1, -3), 
                            Util::Vector2D(1, -1)
                        }, 
                        
                        {
                            Util::Vector2D(-3, -1), 
                            Util::Vector2D(-1, 1)
                        }, 
                        
                        {
                            Util::Vector2D(-3, -3), 
                            Util::Vector2D(-1, -1)
                        }
                    }
                ), 
                std::tuple<Piece::Shape, Piece::AttachPoints>(
                    
                    {
                        Util::Vector2D(0, 0), 
                        Util::Vector2D(1, 0), 
                        Util::Vector2D(2, 0), 
                        Util::Vector2D(2, -1), 
                        Util::Vector2D(2, -2)
                    }, 
                    
                    {
                        
                        {
                            Util::Vector2D(-1, 1), 
                            Util::Vector2D(-1, 1)
                        }, 
                        
                        {
                            Util::Vector2D(-1, -1), 
                            Util::Vector2D(-1, -1)
                        }, 
                        
                        {
                            Util::Vector2D(3, 1), 
                            Util::Vector2D(1, 1)
                        }, 
                        
                        {
                            Util::Vector2D(1, -3), 
                            Util::Vector2D(-1, -1)
                        }, 
                        
                        {
                            Util::Vector2D(3, -3), 
                            Util::Vector2D(1, -1)
                        }
                    }
                )
            }, 
            
            {
                0, 
                1, 
                2, 
                3, 
                3, 
                0, 
                1, 
                2
            }
        ),
        Piece(
            13, 
            "PENTO-P", 
            5, 
            
            {
                Rotation::ZERO, 
                Rotation::ONEHALFPI, 
                Rotation::PI, 
                Rotation::THREEHALFPI, 
                Rotation::ZERO_FLIPPED, 
                Rotation::ONEHALFPI_FLIPPED, 
                Rotation::PI_FLIPPED, 
                Rotation::THREEHALFPI_FLIPPED
            }, 
            
            {
                std::tuple<Piece::Shape, Piece::AttachPoints>(
                    
                    {
                        Util::Vector2D(0, 0), 
                        Util::Vector2D(0, 1), 
                        Util::Vector2D(0, 2), 
                        Util::Vector2D(1, 0), 
                        Util::Vector2D(1, 1)
                    }, 
                    
                    {
                        
                        {
                            Util::Vector2D(-1, -1), 
                            Util::Vector2D(-1, -1)
                        }, 
                        
                        {
                            Util::Vector2D(-1, 3), 
                            Util::Vector2D(-1, 1)
                        }, 
                        
                        {
                            Util::Vector2D(1, 3), 
                            Util::Vector2D(1, 1)
                        }, 
                        
                        {
                            Util::Vector2D(2, -1), 
                            Util::Vector2D(1, -1)
                        }, 
                        
                        {
                            Util::Vector2D(2, 2), 
                            Util::Vector2D(1, 1)
                        }
                    }
                ), 
                std::tuple<Piece::Shape, Piece::AttachPoints>(
                    
                    {
                        Util::Vector2D(0, 0), 
                        Util::Vector2D(-1, 0), 
                        Util::Vector2D(-2, 0), 
                        Util::Vector2D(0, 1), 
                        Util::Vector2D(-1, 1)
                    }, 
                    
                    {
                        
                        {
                            Util::Vector2D(1, -1), 
                            Util::Vector2D(1, -1)
                        }, 
                        
                        {
                            Util::Vector2D(-3, -1), 
                            Util::Vector2D(-1, -1)
                        }, 
                        
                        {
                            Util::Vector2D(-3, 1), 
                            Util::Vector2D(-1, 1)
                        }, 
                        
                        {
                            Util::Vector2D(1, 2), 
                            Util::Vector2D(1, 1)
                        }, 
                        
                        {
                            Util::Vector2D(-2, 2), 
                            Util::Vector2D(-1, 1)
                        }
                    }
                ), 
                std::tuple<Piece::Shape, Piece::AttachPoints>(
                    
                    {
                        Util::Vector2D(0, 0), 
                        Util::Vector2D(0, -1), 
                        Util::Vector2D(0, -2), 
                        Util::Vector2D(-1, 0), 
                        Util::Vector2D(-1, -1)
                    }, 
                    
                    {
                        
                        {
                            Util::Vector2D(1, 1), 
                            Util::Vector2D(1, 1)
                        }, 
                        
                        {
                            Util::Vector2D(1, -3), 
                            Util::Vector2D(1, -1)
                        }, 
                        
                        {
                            Util::Vector2D(-1, -3), 
                            Util::Vector2D(-1, -1)
                        }, 
                        
                        {
                            Util::Vector2D(-2, 1), 
                            Util::Vector2D(-1, 1)
                        }, 
                        
                        {
                            Util::Vector2D(-2, -2), 
                            Util::Vector2D(-1, -1)
                        }
                    }
                ), 
                std::tuple<Piece::Shape, Piece::AttachPoints>(
                    
                    {
                        Util::Vector2D(0, 0), 
                        Util::Vector2D(1, 0), 
                        Util::Vector2D(2, 0), 
                        Util::Vector2D(0, -1), 
                        Util::Vector2D(1, -1)
                    }, 
                    
                    {
                        
                        {
                            Util::Vector2D(-1, 1), 
                            Util::Vector2D(-1, 1)
                        }, 
                        
                        {
                            Util::Vector2D(3, 1), 
                            Util::Vector2D(1, 1)
                        }, 
                        
                        {
                            Util::Vector2D(3, -1), 
                            Util::Vector2D(1, -1)
                        }, 
                        
                        {
                            Util::Vector2D(-1, -2), 
                            Util::Vector2D(-1, -1)
                        }, 
                        
                        {
                            Util::Vector2D(2, -2), 
                            Util::Vector2D(1, -1)
                        }
                    }
                ), 
                std::tuple<Piece::Shape, Piece::AttachPoints>(
                    
                    {
                        Util::Vector2D(0, 0), 
                        Util::Vector2D(0, 1), 
                        Util::Vector2D(0, 2), 
                        Util::Vector2D(-1, 0), 
                        Util::Vector2D(-1, 1)
                    }, 
                    
                    {
                        
                        {
                            Util::Vector2D(1, -1), 
                            Util::Vector2D(1, -1)
                        }, 
                        
                        {
                            Util::Vector2D(-1, 3), 
                            Util::Vector2D(-1, 1)
                        }, 
                        
                        {
                            Util::Vector2D(1, 3), 
                            Util::Vector2D(1, 1)
                        }, 
                        
                        {
                            Util::Vector2D(-2, -1), 
                            Util::Vector2D(-1, -1)
                        }, 
                        
                        {
                            Util::Vector2D(-2, 2), 
                            Util::Vector2D(-1, 1)
                        }
                    }
                ), 
                std::tuple<Piece::Shape, Piece::AttachPoints>(
                    
                    {
                        Util::Vector2D(0, 0), 
                        Util::Vector2D(-1, 0), 
                        Util::Vector2D(-2, 0), 
                        Util::Vector2D(0, -1), 
                        Util::Vector2D(-1, -1)
                    }, 
                    
                    {
                        
                        {
                            Util::Vector2D(1, 1), 
                            Util::Vector2D(1, 1)
                        }, 
                        
                        {
                            Util::Vector2D(-3, -1), 
                            Util::Vector2D(-1, -1)
                        }, 
                        
                        {
                            Util::Vector2D(-3, 1), 
                            Util::Vector2D(-1, 1)
                        }, 
                        
                        {
                            Util::Vector2D(1, -2), 
                            Util::Vector2D(1, -1)
                        }, 
                        
                        {
                            Util::Vector2D(-2, -2), 
                            Util::Vector2D(-1, -1)
                        }
                    }
                ), 
                std::tuple<Piece::Shape, Piece::AttachPoints>(
                    
                    {
                        Util::Vector2D(0, 0), 
                        Util::Vector2D(0, -1), 
                        Util::Vector2D(0, -2), 
                        Util::Vector2D(1, 0), 
                        Util::Vector2D(1, -1)
                    }, 
                    
                    {
                        
                        {
                            Util::Vector2D(-1, 1), 
                            Util::Vector2D(-1, 1)
                        }, 
                        
                        {
                            Util::Vector2D(1, -3), 
                            Util::Vector2D(1, -1)
                        }, 
                        
                        {
                            Util::Vector2D(-1, -3), 
                            Util::Vector2D(-1, -1)
                        }, 
                        
                        {
                            Util::Vector2D(2, 1), 
                            Util::Vector2D(1, 1)
                        }, 
                        
                        {
                            Util::Vector2D(2, -2), 
                            Util::Vector2D(1, -1)
                        }
                    }
                ), 
                std::tuple<Piece::Shape, Piece::AttachPoints>(
                    
                    {
                        Util::Vector2D(0, 0), 
                        Util::Vector2D(1, 0), 
                        Util::Vector2D(2, 0), 
                        Util::Vector2D(0, 1), 
                        Util::Vector2D(1, 1)
                    }, 
                    
                    {
                        
                        {
                            Util::Vector2D(-1, -1), 
                            Util::Vector2D(-1, -1)
                        }, 
                        
                        {
                            Util::Vector2D(3, 1), 
                            Util::Vector2D(1, 1)
                        }, 
                        
                        {
                            Util::Vector2D(3, -1), 
                            Util::Vector2D(1, -1)
                        }, 
                        
                        {
                            Util::Vector2D(-1, 2), 
                            Util::Vector2D(-1, 1)
                        }, 
                        
                        {
                            Util::Vector2D(2, 2), 
                            Util::Vector2D(1, 1)
                        }
                    }
                )
            }, 
            
            {
                0, 
                1, 
                2, 
                3, 
                4, 
                5, 
                6, 
                7
            }
        ),
        Piece(
            14, 
            "PENTO-W", 
            5, 
            
            {
                Rotation::ZERO, 
                Rotation::ONEHALFPI, 
                Rotation::PI, 
                Rotation::THREEHALFPI
            }, 
            
            {
                std::tuple<Piece::Shape, Piece::AttachPoints>(
                    
                    {
                        Util::Vector2D(0, 0), 
                        Util::Vector2D(0, 1), 
                        Util::Vector2D(1, 1), 
                        Util::Vector2D(1, 2), 
                        Util::Vector2D(2, 2)
                    }, 
                    
                    {
                        
                        {
                            Util::Vector2D(-1, -1), 
                            Util::Vector2D(-1, -1)
                        }, 
                        
                        {
                            Util::Vector2D(1, -1), 
                            Util::Vector2D(1, -1)
                        }, 
                        
                        {
                            Util::Vector2D(-1, 2), 
                            Util::Vector2D(-1, 1)
                        }, 
                        
                        {
                            Util::Vector2D(2, 0), 
                            Util::Vector2D(1, -1)
                        }, 
                        
                        {
                            Util::Vector2D(0, 3), 
                            Util::Vector2D(-1, 1)
                        }, 
                        
                        {
                            Util::Vector2D(3, 1), 
                            Util::Vector2D(1, -1)
                        }, 
                        
                        {
                            Util::Vector2D(3, 3), 
                            Util::Vector2D(1, 1)
                        }
                    }
                ), 
                std::tuple<Piece::Shape, Piece::AttachPoints>(
                    
                    {
                        Util::Vector2D(0, 0), 
                        Util::Vector2D(-1, 0), 
                        Util::Vector2D(-1, 1), 
                        Util::Vector2D(-2, 1), 
                        Util::Vector2D(-2, 2)
                    }, 
                    
                    {
                        
                        {
                            Util::Vector2D(1, -1), 
                            Util::Vector2D(1, -1)
                        }, 
                        
                        {
                            Util::Vector2D(1, 1), 
                            Util::Vector2D(1, 1)
                        }, 
                        
                        {
                            Util::Vector2D(-2, -1), 
                            Util::Vector2D(-1, -1)
                        }, 
                        
                        {
                            Util::Vector2D(0, 2), 
                            Util::Vector2D(1, 1)
                        }, 
                        
                        {
                            Util::Vector2D(-3, 0), 
                            Util::Vector2D(-1, -1)
                        }, 
                        
                        {
                            Util::Vector2D(-1, 3), 
                            Util::Vector2D(1, 1)
                        }, 
                        
                        {
                            Util::Vector2D(-3, 3), 
                            Util::Vector2D(-1, 1)
                        }
                    }
                ), 
                std::tuple<Piece::Shape, Piece::AttachPoints>(
                    
                    {
                        Util::Vector2D(0, 0), 
                        Util::Vector2D(0, -1), 
                        Util::Vector2D(-1, -1), 
                        Util::Vector2D(-1, -2), 
                        Util::Vector2D(-2, -2)
                    }, 
                    
                    {
                        
                        {
                            Util::Vector2D(1, 1), 
                            Util::Vector2D(1, 1)
                        }, 
                        
                        {
                            Util::Vector2D(-1, 1), 
                            Util::Vector2D(-1, 1)
                        }, 
                        
                        {
                            Util::Vector2D(1, -2), 
                            Util::Vector2D(1, -1)
                        }, 
                        
                        {
                            Util::Vector2D(-2, 0), 
                            Util::Vector2D(-1, 1)
                        }, 
                        
                        {
                            Util::Vector2D(0, -3), 
                            Util::Vector2D(1, -1)
                        }, 
                        
                        {
                            Util::Vector2D(-3, -1), 
                            Util::Vector2D(-1, 1)
                        }, 
                        
                        {
                            Util::Vector2D(-3, -3), 
                            Util::Vector2D(-1, -1)
                        }
                    }
                ), 
                std::tuple<Piece::Shape, Piece::AttachPoints>(
                    
                    {
                        Util::Vector2D(0, 0), 
                        Util::Vector2D(1, 0), 
                        Util::Vector2D(1, -1), 
                        Util::Vector2D(2, -1), 
                        Util::Vector2D(2, -2)
                    }, 
                    
                    {
                        
                        {
                            Util::Vector2D(-1, 1), 
                            Util::Vector2D(-1, 1)
                        }, 
                        
                        {
                            Util::Vector2D(-1, -1), 
                            Util::Vector2D(-1, -1)
                        }, 
                        
                        {
                            Util::Vector2D(2, 1), 
                            Util::Vector2D(1, 1)
                        }, 
                        
                        {
                            Util::Vector2D(0, -2), 
                            Util::Vector2D(-1, -1)
                        }, 
                        
                        {
                            Util::Vector2D(3, 0), 
                            Util::Vector2D(1, 1)
                        }, 
                        
                        {
                            Util::Vector2D(1, -3), 
                            Util::Vector2D(-1, -1)
                        }, 
                        
                        {
                            Util::Vector2D(3, -3), 
                            Util::Vector2D(1, -1)
                        }
                    }
                )
            }, 
            
            {
                0, 
                1, 
                2, 
                3, 
                3, 
                0, 
                1, 
                2
            }
        ),
        Piece(
            15, 
            "PENTO-R", 
            5, 
            
            {
                Rotation::ZERO, 
                Rotation::ONEHALFPI, 
                Rotation::PI, 
                Rotation::THREEHALFPI, 
                Rotation::ZERO_FLIPPED, 
                Rotation::ONEHALFPI_FLIPPED, 
                Rotation::PI_FLIPPED, 
                Rotation::THREEHALFPI_FLIPPED
            }, 
            
            {
                std::tuple<Piece::Shape, Piece::AttachPoints>(
                    
                    {
                        Util::Vector2D(0, 0), 
                        Util::Vector2D(1, 0), 
                        Util::Vector2D(2, 0), 
                        Util::Vector2D(2, -1), 
                        Util::Vector2D(1, 1)
                    }, 
                    
                    {
                        
                        {
                            Util::Vector2D(-1, -1), 
                            Util::Vector2D(-1, -1)
                        }, 
                        
                        {
                            Util::Vector2D(-1, 1), 
                            Util::Vector2D(-1, 1)
                        }, 
                        
                        {
                            Util::Vector2D(3, 1), 
                            Util::Vector2D(1, 1)
                        }, 
                        
                        {
                            Util::Vector2D(1, -2), 
                            Util::Vector2D(-1, -1)
                        }, 
                        
                        {
                            Util::Vector2D(3, -2), 
                            Util::Vector2D(1, -1)
                        }, 
                        
                        {
                            Util::Vector2D(0, 2), 
                            Util::Vector2D(-1, 1)
                        }, 
                        
                        {
                            Util::Vector2D(2, 2), 
                            Util::Vector2D(1, 1)
                        }
                    }
                ), 
                std::tuple<Piece::Shape, Piece::AttachPoints>(
                    
                    {
                        Util::Vector2D(0, 0), 
                        Util::Vector2D(0, 1), 
                        Util::Vector2D(0, 2), 
                        Util::Vector2D(1, 2), 
                        Util::Vector2D(-1, 1)
                    }, 
                    
                    {
                        
                        {
                            Util::Vector2D(1, -1), 
                            Util::Vector2D(1, -1)
                        }, 
                        
                        {
                            Util::Vector2D(-1, -1), 
                            Util::Vector2D(-1, -1)
                        }, 
                        
                        {
                            Util::Vector2D(-1, 3), 
                            Util::Vector2D(-1, 1)
                        }, 
                        
                        {
                            Util::Vector2D(2, 1), 
                            Util::Vector2D(1, -1)
                        }, 
                        
                        {
                            Util::Vector2D(2, 3), 
                            Util::Vector2D(1, 1)
                        }, 
                        
                        {
                            Util::Vector2D(-2, 0), 
                            Util::Vector2D(-1, -1)
                        }, 
                        
                        {
                            Util::Vector2D(-2, 2), 
                            Util::Vector2D(-1, 1)
                        }
                    }
                ), 
                std::tuple<Piece::Shape, Piece::AttachPoints>(
                    
                    {
                        Util::Vector2D(0, 0), 
                        Util::Vector2D(-1, 0), 
                        Util::Vector2D(-2, 0), 
                        Util::Vector2D(-2, 1), 
                        Util::Vector2D(-1, -1)
                    }, 
                    
                    {
                        
                        {
                            Util::Vector2D(1, 1), 
                            Util::Vector2D(1, 1)
                        }, 
                        
                        {
                            Util::Vector2D(1, -1), 
                            Util::Vector2D(1, -1)
                        }, 
                        
                        {
                            Util::Vector2D(-3, -1), 
                            Util::Vector2D(-1, -1)
                        }, 
                        
                        {
                            Util::Vector2D(-1, 2), 
                            Util::Vector2D(1, 1)
                        }, 
                        
                        {
                            Util::Vector2D(-3, 2), 
                            Util::Vector2D(-1, 1)
                        }, 
                        
                        {
                            Util::Vector2D(0, -2), 
                            Util::Vector2D(1, -1)
                        }, 
                        
                        {
                            Util::Vector2D(-2, -2), 
                            Util::Vector2D(-1, -1)
                        }
                    }
                ), 
                std::tuple<Piece::Shape, Piece::AttachPoints>(
                    
                    {
                        Util::Vector2D(0, 0), 
                        Util::Vector2D(0, -1), 
                        Util::Vector2D(0, -2), 
                        Util::Vector2D(-1, -2), 
                        Util::Vector2D(1, -1)
                    }, 
                    
                    {
                        
                        {
                            Util::Vector2D(-1, 1), 
                            Util::Vector2D(-1, 1)
                        }, 
                        
                        {
                            Util::Vector2D(1, 1), 
                            Util::Vector2D(1, 1)
                        }, 
                        
                        {
                            Util::Vector2D(1, -3), 
                            Util::Vector2D(1, -1)
                        }, 
                        
                        {
                            Util::Vector2D(-2, -1), 
                            Util::Vector2D(-1, 1)
                        }, 
                        
                        {
                            Util::Vector2D(-2, -3), 
                            Util::Vector2D(-1, -1)
                        }, 
                        
                        {
                            Util::Vector2D(2, 0), 
                            Util::Vector2D(1, 1)
                        }, 
                        
                        {
                            Util::Vector2D(2, -2), 
                            Util::Vector2D(1, -1)
                        }
                    }
                ), 
                std::tuple<Piece::Shape, Piece::AttachPoints>(
                    
                    {
                        Util::Vector2D(0, 0), 
                        Util::Vector2D(-1, 0), 
                        Util::Vector2D(-2, 0), 
                        Util::Vector2D(-2, -1), 
                        Util::Vector2D(-1, 1)
                    }, 
                    
                    {
                        
                        {
                            Util::Vector2D(1, -1), 
                            Util::Vector2D(1, -1)
                        }, 
                        
                        {
                            Util::Vector2D(1, 1), 
                            Util::Vector2D(1, 1)
                        }, 
                        
                        {
                            Util::Vector2D(-3, 1), 
                            Util::Vector2D(-1, 1)
                        }, 
                        
                        {
                            Util::Vector2D(-3, -2), 
                            Util::Vector2D(-1, -1)
                        }, 
                        
                        {
                            Util::Vector2D(-1, -2), 
                            Util::Vector2D(1, -1)
                        }, 
                        
                        {
                            Util::Vector2D(-2, 2), 
                            Util::Vector2D(-1, 1)
                        }, 
                        
                        {
                            Util::Vector2D(0, 2), 
                            Util::Vector2D(1, 1)
                        }
                    }
                ), 
                std::tuple<Piece::Shape, Piece::AttachPoints>(
                    
                    {
                        Util::Vector2D(0, 0), 
                        Util::Vector2D(0, -1), 
                        Util::Vector2D(0, -2), 
                        Util::Vector2D(1, -2), 
                        Util::Vector2D(-1, -1)
                    }, 
                    
                    {
                        
                        {
                            Util::Vector2D(1, 1), 
                            Util::Vector2D(1, 1)
                        }, 
                        
                        {
                            Util::Vector2D(-1, 1), 
                            Util::Vector2D(-1, 1)
                        }, 
                        
                        {
                            Util::Vector2D(-1, -3), 
                            Util::Vector2D(-1, -1)
                        }, 
                        
                        {
                            Util::Vector2D(2, -3), 
                            Util::Vector2D(1, -1)
                        }, 
                        
                        {
                            Util::Vector2D(2, -1), 
                            Util::Vector2D(1, 1)
                        }, 
                        
                        {
                            Util::Vector2D(-2, -2), 
                            Util::Vector2D(-1, -1)
                        }, 
                        
                        {
                            Util::Vector2D(-2, 0), 
                            Util::Vector2D(-1, 1)
                        }
                    }
                ), 
                std::tuple<Piece::Shape, Piece::AttachPoints>(
                    
                    {
                        Util::Vector2D(0, 0), 
                        Util::Vector2D(1, 0), 
                        Util::Vector2D(2, 0), 
                        Util::Vector2D(2, 1), 
                        Util::Vector2D(1, -1)
                    }, 
                    
                    {
                        
                        {
                            Util::Vector2D(-1, 1), 
                            Util::Vector2D(-1, 1)
                        }, 
                        
                        {
                            Util::Vector2D(-1, -1), 
                            Util::Vector2D(-1, -1)
                        }, 
                        
                        {
                            Util::Vector2D(3, -1), 
                            Util::Vector2D(1, -1)
                        }, 
                        
                        {
                            Util::Vector2D(3, 2), 
                            Util::Vector2D(1, 1)
                        }, 
                        
                        {
                            Util::Vector2D(1, 2), 
                            Util::Vector2D(-1, 1)
                        }, 
                        
                        {
                            Util::Vector2D(2, -2), 
                            Util::Vector2D(1, -1)
                        }, 
                        
                        {
                            Util::Vector2D(0, -2), 
                            Util::Vector2D(-1, -1)
                        }
                    }
                ), 
                std::tuple<Piece::Shape, Piece::AttachPoints>(
                    
                    {
                        Util::Vector2D(0, 0), 
                        Util::Vector2D(0, 1), 
                        Util::Vector2D(0, 2), 
                        Util::Vector2D(-1, 2), 
                        Util::Vector2D(1, 1)
                    }, 
                    
                    {
                        
                        {
                            Util::Vector2D(-1, -1), 
                            Util::Vector2D(-1, -1)
                        }, 
                        
                        {
                            Util::Vector2D(1, -1), 
                            Util::Vector2D(1, -1)
                        }, 
                        
                        {
                            Util::Vector2D(1, 3), 
                            Util::Vector2D(1, 1)
                        }, 
                        
                        {
                            Util::Vector2D(-2, 3), 
                            Util::Vector2D(-1, 1)
                        }, 
                        
                        {
                            Util::Vector2D(-2, 1), 
                            Util::Vector2D(-1, -1)
                        }, 
                        
                        {
                            Util::Vector2D(2, 2), 
                            Util::Vector2D(1, 1)
                        }, 
                        
                        {
                            Util::Vector2D(2, 0), 
                            Util::Vector2D(1, -1)
                        }
                    }
                )
            }, 
            
            {
                0, 
                1, 
                2, 
                3, 
                4, 
                5, 
                6, 
                7
            }
        ),
        Piece(
            16, 
            "PENTO-X", 
            5, 
            
            {
                Rotation::ZERO
            }, 
            
            {
                std::tuple<Piece::Shape, Piece::AttachPoints>(
                    
                    {
                        Util::Vector2D(0, 0), 
                        Util::Vector2D(1, 0), 
                        Util::Vector2D(2, 0), 
                        Util::Vector2D(1, -1), 
                        Util::Vector2D(1, 1)
                    }, 
                    
                    {
                        
                        {
                            Util::Vector2D(-1, -1), 
                            Util::Vector2D(-1, -1)
                        }, 
                        
                        {
                            Util::Vector2D(-1, 1), 
                            Util::Vector2D(-1, 1)
                        }, 
                        
                        {
                            Util::Vector2D(3, -1), 
                            Util::Vector2D(1, -1)
                        }, 
                        
                        {
                            Util::Vector2D(3, 1), 
                            Util::Vector2D(1, 1)
                        }, 
                        
                        {
                            Util::Vector2D(0, -2), 
                            Util::Vector2D(-1, -1)
                        }, 
                        
                        {
                            Util::Vector2D(2, -2), 
                            Util::Vector2D(1, -1)
                        }, 
                        
                        {
                            Util::Vector2D(0, 2), 
                            Util::Vector2D(-1, 1)
                        }, 
                        
                        {
                            Util::Vector2D(2, 2), 
                            Util::Vector2D(1, 1)
                        }
                    }
                )
            }, 
            
            {
                0, 
                0, 
                0, 
                0, 
                0, 
                0, 
                0, 
                0
            }
        ),
        Piece(
            17, 
            "PENTO-Z", 
            5, 
            
            {
                Rotation::ZERO, 
                Rotation::ONEHALFPI, 
                Rotation::ZERO_FLIPPED, 
                Rotation::ONEHALFPI_FLIPPED
            }, 
            
            {
                std::tuple<Piece::Shape, Piece::AttachPoints>(
                    
                    {
                        Util::Vector2D(0, 0), 
                        Util::Vector2D(1, 0), 
                        Util::Vector2D(1, 1), 
                        Util::Vector2D(1, 2), 
                        Util::Vector2D(2, 2)
                    }, 
                    
                    {
                        
                        {
                            Util::Vector2D(-1, -1), 
                            Util::Vector2D(-1, -1)
                        }, 
                        
                        {
                            Util::Vector2D(-1, 1), 
                            Util::Vector2D(-1, 1)
                        }, 
                        
                        {
                            Util::Vector2D(2, -1), 
                            Util::Vector2D(1, -1)
                        }, 
                        
                        {
                            Util::Vector2D(0, 3), 
                            Util::Vector2D(-1, 1)
                        }, 
                        
                        {
                            Util::Vector2D(3, 1), 
                            Util::Vector2D(1, -1)
                        }, 
                        
                        {
                            Util::Vector2D(3, 3), 
                            Util::Vector2D(1, 1)
                        }
                    }
                ), 
                std::tuple<Piece::Shape, Piece::AttachPoints>(
                    
                    {
                        Util::Vector2D(0, 0), 
                        Util::Vector2D(0, 1), 
                        Util::Vector2D(-1, 1), 
                        Util::Vector2D(-2, 1), 
                        Util::Vector2D(-2, 2)
                    }, 
                    
                    {
                        
                        {
                            Util::Vector2D(1, -1), 
                            Util::Vector2D(1, -1)
                        }, 
                        
                        {
                            Util::Vector2D(-1, -1), 
                            Util::Vector2D(-1, -1)
                        }, 
                        
                        {
                            Util::Vector2D(1, 2), 
                            Util::Vector2D(1, 1)
                        }, 
                        
                        {
                            Util::Vector2D(-3, 0), 
                            Util::Vector2D(-1, -1)
                        }, 
                        
                        {
                            Util::Vector2D(-1, 3), 
                            Util::Vector2D(1, 1)
                        }, 
                        
                        {
                            Util::Vector2D(-3, 3), 
                            Util::Vector2D(-1, 1)
                        }
                    }
                ), 
                std::tuple<Piece::Shape, Piece::AttachPoints>(
                    
                    {
                        Util::Vector2D(0, 0), 
                        Util::Vector2D(-1, 0), 
                        Util::Vector2D(-1, 1), 
                        Util::Vector2D(-1, 2), 
                        Util::Vector2D(-2, 2)
                    }, 
                    
                    {
                        
                        {
                            Util::Vector2D(1, -1), 
                            Util::Vector2D(1, -1)
                        }, 
                        
                        {
                            Util::Vector2D(1, 1), 
                            Util::Vector2D(1, 1)
                        }, 
                        
                        {
                            Util::Vector2D(-2, -1), 
                            Util::Vector2D(-1, -1)
                        }, 
                        
                        {
                            Util::Vector2D(0, 3), 
                            Util::Vector2D(1, 1)
                        }, 
                        
                        {
                            Util::Vector2D(-3, 1), 
                            Util::Vector2D(-1, -1)
                        }, 
                        
                        {
                            Util::Vector2D(-3, 3), 
                            Util::Vector2D(-1, 1)
                        }
                    }
                ), 
                std::tuple<Piece::Shape, Piece::AttachPoints>(
                    
                    {
                        Util::Vector2D(0, 0), 
                        Util::Vector2D(0, -1), 
                        Util::Vector2D(-1, -1), 
                        Util::Vector2D(-2, -1), 
                        Util::Vector2D(-2, -2)
                    }, 
                    
                    {
                        
                        {
                            Util::Vector2D(1, 1), 
                            Util::Vector2D(1, 1)
                        }, 
                        
                        {
                            Util::Vector2D(-1, 1), 
                            Util::Vector2D(-1, 1)
                        }, 
                        
                        {
                            Util::Vector2D(1, -2), 
                            Util::Vector2D(1, -1)
                        }, 
                        
                        {
                            Util::Vector2D(-3, 0), 
                            Util::Vector2D(-1, 1)
                        }, 
                        
                        {
                            Util::Vector2D(-1, -3), 
                            Util::Vector2D(1, -1)
                        }, 
                        
                        {
                            Util::Vector2D(-3, -3), 
                            Util::Vector2D(-1, -1)
                        }
                    }
                )
            }, 
            
            {
                0, 
                1, 
                0, 
                1, 
                2, 
                3, 
                2, 
                3
            }
        ),
        Piece(
            18, 
            "PENTO-Y", 
            5, 
            
            {
                Rotation::ZERO, 
                Rotation::ONEHALFPI, 
                Rotation::PI, 
                Rotation::THREEHALFPI, 
                Rotation::ZERO_FLIPPED, 
                Rotation::ONEHALFPI_FLIPPED, 
                Rotation::PI_FLIPPED, 
                Rotation::THREEHALFPI_FLIPPED
            }, 
            
            {
                std::tuple<Piece::Shape, Piece::AttachPoints>(
                    
                    {
                        Util::Vector2D(0, 0), 
                        Util::Vector2D(0, 1), 
                        Util::Vector2D(0, 2), 
                        Util::Vector2D(0, 3), 
                        Util::Vector2D(-1, 1)
                    }, 
                    
                    {
                        
                        {
                            Util::Vector2D(-1, -1), 
                            Util::Vector2D(-1, -1)
                        }, 
                        
                        {
                            Util::Vector2D(1, -1), 
                            Util::Vector2D(1, -1)
                        }, 
                        
                        {
                            Util::Vector2D(-1, 4), 
                            Util::Vector2D(-1, 1)
                        }, 
                        
                        {
                            Util::Vector2D(1, 4), 
                            Util::Vector2D(1, 1)
                        }, 
                        
                        {
                            Util::Vector2D(-2, 0), 
                            Util::Vector2D(-1, -1)
                        }, 
                        
                        {
                            Util::Vector2D(-2, 2), 
                            Util::Vector2D(-1, 1)
                        }
                    }
                ), 
                std::tuple<Piece::Shape, Piece::AttachPoints>(
                    
                    {
                        Util::Vector2D(0, 0), 
                        Util::Vector2D(-1, 0), 
                        Util::Vector2D(-2, 0), 
                        Util::Vector2D(-3, 0), 
                        Util::Vector2D(-1, -1)
                    }, 
                    
                    {
                        
                        {
                            Util::Vector2D(1, -1), 
                            Util::Vector2D(1, -1)
                        }, 
                        
                        {
                            Util::Vector2D(1, 1), 
                            Util::Vector2D(1, 1)
                        }, 
                        
                        {
                            Util::Vector2D(-4, -1), 
                            Util::Vector2D(-1, -1)
                        }, 
                        
                        {
                            Util::Vector2D(-4, 1), 
                            Util::Vector2D(-1, 1)
                        }, 
                        
                        {
                            Util::Vector2D(0, -2), 
                            Util::Vector2D(1, -1)
                        }, 
                        
                        {
                            Util::Vector2D(-2, -2), 
                            Util::Vector2D(-1, -1)
                        }
                    }
                ), 
                std::tuple<Piece::Shape, Piece::AttachPoints>(
                    
                    {
                        Util::Vector2D(0, 0), 
                        Util::Vector2D(0, -1), 
                        Util::Vector2D(0, -2), 
                        Util::Vector2D(0, -3), 
                        Util::Vector2D(1, -1)
                    }, 
                    
                    {
                        
                        {
                            Util::Vector2D(1, 1), 
                            Util::Vector2D(1, 1)
                        }, 
                        
                        {
                            Util::Vector2D(-1, 1), 
                            Util::Vector2D(-1, 1)
                        }, 
                        
                        {
                            Util::Vector2D(1, -4), 
                            Util::Vector2D(1, -1)
                        }, 
                        
                        {
                            Util::Vector2D(-1, -4), 
                            Util::Vector2D(-1, -1)
                        }, 
                        
                        {
                            Util::Vector2D(2, 0), 
                            Util::Vector2D(1, 1)
                        }, 
                        
                        {
                            Util::Vector2D(2, -2), 
                            Util::Vector2D(1, -1)
                        }
                    }
                ), 
                std::tuple<Piece::Shape, Piece::AttachPoints>(
                    
                    {
                        Util::Vector2D(0, 0), 
                        Util::Vector2D(1, 0), 
                        Util::Vector2D(2, 0), 
                        Util::Vector2D(3, 0), 
                        Util::Vector2D(1, 1)
                    }, 
                    
                    {
                        
                        {
                            Util::Vector2D(-1, 1), 
                            Util::Vector2D(-1, 1)
                        }, 
                        
                        {
                            Util::Vector2D(-1, -1), 
                            Util::Vector2D(-1, -1)
                        }, 
                        
                        {
                            Util::Vector2D(4, 1), 
                            Util::Vector2D(1, 1)
                        }, 
                        
                        {
                            Util::Vector2D(4, -1), 
                            Util::Vector2D(1, -1)
                        }, 
                        
                        {
                            Util::Vector2D(0, 2), 
                            Util::Vector2D(-1, 1)
                        }, 
                        
                        {
                            Util::Vector2D(2, 2), 
                            Util::Vector2D(1, 1)
                        }
                    }
                ), 
                std::tuple<Piece::Shape, Piece::AttachPoints>(
                    
                    {
                        Util::Vector2D(0, 0), 
                        Util::Vector2D(0, 1), 
                        Util::Vector2D(0, 2), 
                        Util::Vector2D(0, 3), 
                        Util::Vector2D(1, 1)
                    }, 
                    
                    {
                        
                        {
                            Util::Vector2D(-1, -1), 
                            Util::Vector2D(-1, -1)
                        }, 
                        
                        {
                            Util::Vector2D(1, -1), 
                            Util::Vector2D(1, -1)
                        }, 
                        
                        {
                            Util::Vector2D(-1, 4), 
                            Util::Vector2D(-1, 1)
                        }, 
                        
                        {
                            Util::Vector2D(1, 4), 
                            Util::Vector2D(1, 1)
                        }, 
                        
                        {
                            Util::Vector2D(2, 0), 
                            Util::Vector2D(1, -1)
                        }, 
                        
                        {
                            Util::Vector2D(2, 2), 
                            Util::Vector2D(1, 1)
                        }
                    }
                ), 
                std::tuple<Piece::Shape, Piece::AttachPoints>(
                    
                    {
                        Util::Vector2D(0, 0), 
                        Util::Vector2D(-1, 0), 
                        Util::Vector2D(-2, 0), 
                        Util::Vector2D(-3, 0), 
                        Util::Vector2D(-1, 1)
                    }, 
                    
                    {
                        
                        {
                            Util::Vector2D(1, -1), 
                            Util::Vector2D(1, -1)
                        }, 
                        
                        {
                            Util::Vector2D(1, 1), 
                            Util::Vector2D(1, 1)
                        }, 
                        
                        {
                            Util::Vector2D(-4, -1), 
                            Util::Vector2D(-1, -1)
                        }, 
                        
                        {
                            Util::Vector2D(-4, 1), 
                            Util::Vector2D(-1, 1)
                        }, 
                        
                        {
                            Util::Vector2D(0, 2), 
                            Util::Vector2D(1, 1)
                        }, 
                        
                        {
                            Util::Vector2D(-2, 2), 
                            Util::Vector2D(-1, 1)
                        }
                    }
                ), 
                std::tuple<Piece::Shape, Piece::AttachPoints>(
                    
                    {
                        Util::Vector2D(0, 0), 
                        Util::Vector2D(0, -1), 
                        Util::Vector2D(0, -2), 
                        Util::Vector2D(0, -3), 
                        Util::Vector2D(-1, -1)
                    }, 
                    
                    {
                        
                        {
                            Util::Vector2D(1, 1), 
                            Util::Vector2D(1, 1)
                        }, 
                        
                        {
                            Util::Vector2D(-1, 1), 
                            Util::Vector2D(-1, 1)
                        }, 
                        
                        {
                            Util::Vector2D(1, -4), 
                            Util::Vector2D(1, -1)
                        }, 
                        
                        {
                            Util::Vector2D(-1, -4), 
                            Util::Vector2D(-1, -1)
                        }, 
                        
                        {
                            Util::Vector2D(-2, 0), 
                            Util::Vector2D(-1, 1)
                        }, 
                        
                        {
                            Util::Vector2D(-2, -2), 
                            Util::Vector2D(-1, -1)
                        }
                    }
                ), 
                std::tuple<Piece::Shape, Piece::AttachPoints>(
                    
                    {
                        Util::Vector2D(0, 0), 
                        Util::Vector2D(1, 0), 
                        Util::Vector2D(2, 0), 
                        Util::Vector2D(3, 0), 
                        Util::Vector2D(1, -1)
                    }, 
                    
                    {
                        
                        {
                            Util::Vector2D(-1, 1), 
                            Util::Vector2D(-1, 1)
                        }, 
                        
                        {
                            Util::Vector2D(-1, -1), 
                            Util::Vector2D(-1, -1)
                        }, 
                        
                        {
                            Util::Vector2D(4, 1), 
                            Util::Vector2D(1, 1)
                        }, 
                        
                        {
                            Util::Vector2D(4, -1), 
                            Util::Vector2D(1, -1)
                        }, 
                        
                        {
                            Util::Vector2D(0, -2), 
                            Util::Vector2D(-1, -1)
                        }, 
                        
                        {
                            Util::Vector2D(2, -2), 
                            Util::Vector2D(1, -1)
                        }
                    }
                )
            }, 
            
            {
                0, 
                1, 
                2, 
                3, 
                4, 
                5, 
                6, 
                7
            }
        ),
        Piece(
            19, 
            "PENTO-T", 
            5, 
            
            {
                Rotation::ZERO, 
                Rotation::ONEHALFPI, 
                Rotation::PI, 
                Rotation::THREEHALFPI
            }, 
            
            {
                std::tuple<Piece::Shape, Piece::AttachPoints>(
                    
                    {
                        Util::Vector2D(0, 0), 
                        Util::Vector2D(1, 0), 
                        Util::Vector2D(2, 0), 
                        Util::Vector2D(1, 1), 
                        Util::Vector2D(1, 2)
                    }, 
                    
                    {
                        
                        {
                            Util::Vector2D(-1, -1), 
                            Util::Vector2D(-1, -1)
                        }, 
                        
                        {
                            Util::Vector2D(-1, 1), 
                            Util::Vector2D(-1, 1)
                        }, 
                        
                        {
                            Util::Vector2D(3, -1), 
                            Util::Vector2D(1, -1)
                        }, 
                        
                        {
                            Util::Vector2D(3, 1), 
                            Util::Vector2D(1, 1)
                        }, 
                        
                        {
                            Util::Vector2D(0, 3), 
                            Util::Vector2D(-1, 1)
                        }, 
                        
                        {
                            Util::Vector2D(2, 3), 
                            Util::Vector2D(1, 1)
                        }
                    }
                ), 
                std::tuple<Piece::Shape, Piece::AttachPoints>(
                    
                    {
                        Util::Vector2D(0, 0), 
                        Util::Vector2D(0, 1), 
                        Util::Vector2D(0, 2), 
                        Util::Vector2D(-1, 1), 
                        Util::Vector2D(-2, 1)
                    }, 
                    
                    {
                        
                        {
                            Util::Vector2D(1, -1), 
                            Util::Vector2D(1, -1)
                        }, 
                        
                        {
                            Util::Vector2D(-1, -1), 
                            Util::Vector2D(-1, -1)
                        }, 
                        
                        {
                            Util::Vector2D(1, 3), 
                            Util::Vector2D(1, 1)
                        }, 
                        
                        {
                            Util::Vector2D(-1, 3), 
                            Util::Vector2D(-1, 1)
                        }, 
                        
                        {
                            Util::Vector2D(-3, 0), 
                            Util::Vector2D(-1, -1)
                        }, 
                        
                        {
                            Util::Vector2D(-3, 2), 
                            Util::Vector2D(-1, 1)
                        }
                    }
                ), 
                std::tuple<Piece::Shape, Piece::AttachPoints>(
                    
                    {
                        Util::Vector2D(0, 0), 
                        Util::Vector2D(-1, 0), 
                        Util::Vector2D(-2, 0), 
                        Util::Vector2D(-1, -1), 
                        Util::Vector2D(-1, -2)
                    }, 
                    
                    {
                        
                        {
                            Util::Vector2D(1, 1), 
                            Util::Vector2D(1, 1)
                        }, 
                        
                        {
                            Util::Vector2D(1, -1), 
                            Util::Vector2D(1, -1)
                        }, 
                        
                        {
                            Util::Vector2D(-3, 1), 
                            Util::Vector2D(-1, 1)
                        }, 
                        
                        {
                            Util::Vector2D(-3, -1), 
                            Util::Vector2D(-1, -1)
                        }, 
                        
                        {
                            Util::Vector2D(0, -3), 
                            Util::Vector2D(1, -1)
                        }, 
                        
                        {
                            Util::Vector2D(-2, -3), 
                            Util::Vector2D(-1, -1)
                        }
                    }
                ), 
                std::tuple<Piece::Shape, Piece::AttachPoints>(
                    
                    {
                        Util::Vector2D(0, 0), 
                        Util::Vector2D(0, -1), 
                        Util::Vector2D(0, -2), 
                        Util::Vector2D(1, -1), 
                        Util::Vector2D(2, -1)
                    }, 
                    
                    {
                        
                        {
                            Util::Vector2D(-1, 1), 
                            Util::Vector2D(-1, 1)
                        }, 
                        
                        {
                            Util::Vector2D(1, 1), 
                            Util::Vector2D(1, 1)
                        }, 
                        
                        {
                            Util::Vector2D(-1, -3), 
                            Util::Vector2D(-1, -1)
                        }, 
                        
                        {
                            Util::Vector2D(1, -3), 
                            Util::Vector2D(1, -1)
                        }, 
                        
                        {
                            Util::Vector2D(3, 0), 
                            Util::Vector2D(1, 1)
                        }, 
                        
                        {
                            Util::Vector2D(3, -2), 
                            Util::Vector2D(1, -1)
                        }
                    }
                )
            }, 
            
            {
                0, 
                1, 
                2, 
                3, 
                0, 
                1, 
                2, 
                3
            }
        ),
        Piece(
            20, 
            "PENTO-S", 
            5, 
            
            {
                Rotation::ZERO, 
                Rotation::ONEHALFPI, 
                Rotation::PI, 
                Rotation::THREEHALFPI, 
                Rotation::ZERO_FLIPPED, 
                Rotation::ONEHALFPI_FLIPPED, 
                Rotation::PI_FLIPPED, 
                Rotation::THREEHALFPI_FLIPPED
            }, 
            
            {
                std::tuple<Piece::Shape, Piece::AttachPoints>(
                    
                    {
                        Util::Vector2D(0, 0), 
                        Util::Vector2D(1, 0), 
                        Util::Vector2D(1, -1), 
                        Util::Vector2D(2, -1), 
                        Util::Vector2D(3, -1)
                    }, 
                    
                    {
                        
                        {
                            Util::Vector2D(-1, -1), 
                            Util::Vector2D(-1, -1)
                        }, 
                        
                        {
                            Util::Vector2D(-1, 1), 
                            Util::Vector2D(-1, 1)
                        }, 
                        
                        {
                            Util::Vector2D(2, 1), 
                            Util::Vector2D(1, 1)
                        }, 
                        
                        {
                            Util::Vector2D(0, -2), 
                            Util::Vector2D(-1, -1)
                        }, 
                        
                        {
                            Util::Vector2D(4, -2), 
                            Util::Vector2D(1, -1)
                        }, 
                        
                        {
                            Util::Vector2D(4, 0), 
                            Util::Vector2D(1, 1)
                        }
                    }
                ), 
                std::tuple<Piece::Shape, Piece::AttachPoints>(
                    
                    {
                        Util::Vector2D(0, 0), 
                        Util::Vector2D(0, 1), 
                        Util::Vector2D(1, 1), 
                        Util::Vector2D(1, 2), 
                        Util::Vector2D(1, 3)
                    }, 
                    
                    {
                        
                        {
                            Util::Vector2D(1, -1), 
                            Util::Vector2D(1, -1)
                        }, 
                        
                        {
                            Util::Vector2D(-1, -1), 
                            Util::Vector2D(-1, -1)
                        }, 
                        
                        {
                            Util::Vector2D(-1, 2), 
                            Util::Vector2D(-1, 1)
                        }, 
                        
                        {
                            Util::Vector2D(2, 0), 
                            Util::Vector2D(1, -1)
                        }, 
                        
                        {
                            Util::Vector2D(2, 4), 
                            Util::Vector2D(1, 1)
                        }, 
                        
                        {
                            Util::Vector2D(0, 4), 
                            Util::Vector2D(-1, 1)
                        }
                    }
                ), 
                std::tuple<Piece::Shape, Piece::AttachPoints>(
                    
                    {
                        Util::Vector2D(0, 0), 
                        Util::Vector2D(-1, 0), 
                        Util::Vector2D(-1, 1), 
                        Util::Vector2D(-2, 1), 
                        Util::Vector2D(-3, 1)
                    }, 
                    
                    {
                        
                        {
                            Util::Vector2D(1, 1), 
                            Util::Vector2D(1, 1)
                        }, 
                        
                        {
                            Util::Vector2D(1, -1), 
                            Util::Vector2D(1, -1)
                        }, 
                        
                        {
                            Util::Vector2D(-2, -1), 
                            Util::Vector2D(-1, -1)
                        }, 
                        
                        {
                            Util::Vector2D(0, 2), 
                            Util::Vector2D(1, 1)
                        }, 
                        
                        {
                            Util::Vector2D(-4, 2), 
                            Util::Vector2D(-1, 1)
                        }, 
                        
                        {
                            Util::Vector2D(-4, 0), 
                            Util::Vector2D(-1, -1)
                        }
                    }
                ), 
                std::tuple<Piece::Shape, Piece::AttachPoints>(
                    
                    {
                        Util::Vector2D(0, 0), 
                        Util::Vector2D(0, -1), 
                        Util::Vector2D(-1, -1), 
                        Util::Vector2D(-1, -2), 
                        Util::Vector2D(-1, -3)
                    }, 
                    
                    {
                        
                        {
                            Util::Vector2D(-1, 1), 
                            Util::Vector2D(-1, 1)
                        }, 
                        
                        {
                            Util::Vector2D(1, 1), 
                            Util::Vector2D(1, 1)
                        }, 
                        
                        {
                            Util::Vector2D(1, -2), 
                            Util::Vector2D(1, -1)
                        }, 
                        
                        {
                            Util::Vector2D(-2, 0), 
                            Util::Vector2D(-1, 1)
                        }, 
                        
                        {
                            Util::Vector2D(-2, -4), 
                            Util::Vector2D(-1, -1)
                        }, 
                        
                        {
                            Util::Vector2D(0, -4), 
                            Util::Vector2D(1, -1)
                        }
                    }
                ), 
                std::tuple<Piece::Shape, Piece::AttachPoints>(
                    
                    {
                        Util::Vector2D(0, 0), 
                        Util::Vector2D(-1, 0), 
                        Util::Vector2D(-1, -1), 
                        Util::Vector2D(-2, -1), 
                        Util::Vector2D(-3, -1)
                    }, 
                    
                    {
                        
                        {
                            Util::Vector2D(1, -1), 
                            Util::Vector2D(1, -1)
                        }, 
                        
                        {
                            Util::Vector2D(1, 1), 
                            Util::Vector2D(1, 1)
                        }, 
                        
                        {
                            Util::Vector2D(-2, 1), 
                            Util::Vector2D(-1, 1)
                        }, 
                        
                        {
                            Util::Vector2D(0, -2), 
                            Util::Vector2D(1, -1)
                        }, 
                        
                        {
                            Util::Vector2D(-4, -2), 
                            Util::Vector2D(-1, -1)
                        }, 
                        
                        {
                            Util::Vector2D(-4, 0), 
                            Util::Vector2D(-1, 1)
                        }
                    }
                ), 
                std::tuple<Piece::Shape, Piece::AttachPoints>(
                    
                    {
                        Util::Vector2D(0, 0), 
                        Util::Vector2D(0, -1), 
                        Util::Vector2D(1, -1), 
                        Util::Vector2D(1, -2), 
                        Util::Vector2D(1, -3)
                    }, 
                    
                    {
                        
                        {
                            Util::Vector2D(1, 1), 
                            Util::Vector2D(1, 1)
                        }, 
                        
                        {
                            Util::Vector2D(-1, 1), 
                            Util::Vector2D(-1, 1)
                        }, 
                        
                        {
                            Util::Vector2D(-1, -2), 
                            Util::Vector2D(-1, -1)
                        }, 
                        
                        {
                            Util::Vector2D(2, 0), 
                            Util::Vector2D(1, 1)
                        }, 
                        
                        {
                            Util::Vector2D(2, -4), 
                            Util::Vector2D(1, -1)
                        }, 
                        
                        {
                            Util::Vector2D(0, -4), 
                            Util::Vector2D(-1, -1)
                        }
                    }
                ), 
                std::tuple<Piece::Shape, Piece::AttachPoints>(
                    
                    {
                        Util::Vector2D(0, 0), 
                        Util::Vector2D(1, 0), 
                        Util::Vector2D(1, 1), 
                        Util::Vector2D(2, 1), 
                        Util::Vector2D(3, 1)
                    }, 
                    
                    {
                        
                        {
                            Util::Vector2D(-1, 1), 
                            Util::Vector2D(-1, 1)
                        }, 
                        
                        {
                            Util::Vector2D(-1, -1), 
                            Util::Vector2D(-1, -1)
                        }, 
                        
                        {
                            Util::Vector2D(2, -1), 
                            Util::Vector2D(1, -1)
                        }, 
                        
                        {
                            Util::Vector2D(0, 2), 
                            Util::Vector2D(-1, 1)
                        }, 
                        
                        {
                            Util::Vector2D(4, 2), 
                            Util::Vector2D(1, 1)
                        }, 
                        
                        {
                            Util::Vector2D(4, 0), 
                            Util::Vector2D(1, -1)
                        }
                    }
                ), 
                std::tuple<Piece::Shape, Piece::AttachPoints>(
                    
                    {
                        Util::Vector2D(0, 0), 
                        Util::Vector2D(0, 1), 
                        Util::Vector2D(-1, 1), 
                        Util::Vector2D(-1, 2), 
                        Util::Vector2D(-1, 3)
                    }, 
                    
                    {
                        
                        {
                            Util::Vector2D(-1, -1), 
                            Util::Vector2D(-1, -1)
                        }, 
                        
                        {
                            Util::Vector2D(1, -1), 
                            Util::Vector2D(1, -1)
                        }, 
                        
                        {
                            Util::Vector2D(1, 2), 
                            Util::Vector2D(1, 1)
                        }, 
                        
                        {
                            Util::Vector2D(-2, 0), 
                            Util::Vector2D(-1, -1)
                        }, 
                        
                        {
                            Util::Vector2D(-2, 4), 
                            Util::Vector2D(-1, 1)
                        }, 
                        
                        {
                            Util::Vector2D(0, 4), 
                            Util::Vector2D(1, 1)
                        }
                    }
                )
            }, 
            
            {
                0, 
                1, 
                2, 
                3, 
                4, 
                5, 
                6, 
                7
            }
        )
    };

    const Piece& PieceCollection::getPiece(const int& index) {
        return allPieces.at(index);
    }   

}
