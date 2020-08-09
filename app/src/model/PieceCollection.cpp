#include "PieceCollection.hpp"

namespace Model {

    const std::array<Piece, 21> PieceCollection::allPieces = {
        Piece {
            0, 
            
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
                ), 
                std::tuple<Piece::Shape, Piece::AttachPoints>(
                    
                    {
                        Util::Vector2D(0, 0)
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
                            Util::Vector2D(-1, -1), 
                            Util::Vector2D(-1, -1)
                        }, 
                        
                        {
                            Util::Vector2D(-1, 1), 
                            Util::Vector2D(-1, 1)
                        }
                    }
                ), 
                std::tuple<Piece::Shape, Piece::AttachPoints>(
                    
                    {
                        Util::Vector2D(0, 0)
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
                            Util::Vector2D(1, -1), 
                            Util::Vector2D(1, -1)
                        }, 
                        
                        {
                            Util::Vector2D(-1, -1), 
                            Util::Vector2D(-1, -1)
                        }
                    }
                ), 
                std::tuple<Piece::Shape, Piece::AttachPoints>(
                    
                    {
                        Util::Vector2D(0, 0)
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
                            Util::Vector2D(1, 1), 
                            Util::Vector2D(1, 1)
                        }, 
                        
                        {
                            Util::Vector2D(1, -1), 
                            Util::Vector2D(1, -1)
                        }
                    }
                )
            }
        },
        Piece {
            1, 
            
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
                ), 
                std::tuple<Piece::Shape, Piece::AttachPoints>(
                    
                    {
                        Util::Vector2D(0, 0), 
                        Util::Vector2D(-1, 0)
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
                            Util::Vector2D(-2, 1), 
                            Util::Vector2D(-1, 1)
                        }, 
                        
                        {
                            Util::Vector2D(-2, -1), 
                            Util::Vector2D(-1, -1)
                        }
                    }
                ), 
                std::tuple<Piece::Shape, Piece::AttachPoints>(
                    
                    {
                        Util::Vector2D(0, 0), 
                        Util::Vector2D(0, -1)
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
                            Util::Vector2D(-1, -2), 
                            Util::Vector2D(-1, -1)
                        }, 
                        
                        {
                            Util::Vector2D(1, -2), 
                            Util::Vector2D(1, -1)
                        }
                    }
                )
            }
        },
        Piece {
            2, 
            
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
                            Util::Vector2D(2, -1), 
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
                            Util::Vector2D(1, 2), 
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
                            Util::Vector2D(-2, 1), 
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
                            Util::Vector2D(-1, -2), 
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
                )
            }
        },
        Piece {
            3, 
            
            {
                Rotation::ZERO, 
                Rotation::ONEHALFPI
            }, 
            
            {
                std::tuple<Piece::Shape, Piece::AttachPoints>(
                    
                    {
                        Util::Vector2D(0, 0), 
                        Util::Vector2D(1, 0), 
                        Util::Vector2D(2, 0)
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
                        }
                    }
                ), 
                std::tuple<Piece::Shape, Piece::AttachPoints>(
                    
                    {
                        Util::Vector2D(0, 0), 
                        Util::Vector2D(0, 1), 
                        Util::Vector2D(0, 2)
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
                        }
                    }
                ), 
                std::tuple<Piece::Shape, Piece::AttachPoints>(
                    
                    {
                        Util::Vector2D(0, 0), 
                        Util::Vector2D(0, -1), 
                        Util::Vector2D(0, -2)
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
                        }
                    }
                )
            }
        },
        Piece {
            4, 
            
            {
                Rotation::ZERO
            }, 
            
            {
                std::tuple<Piece::Shape, Piece::AttachPoints>(
                    
                    {
                        Util::Vector2D(0, 0), 
                        Util::Vector2D(1, 0), 
                        Util::Vector2D(1, 1), 
                        Util::Vector2D(0, 1)
                    }, 
                    
                    {
                        
                        {
                            Util::Vector2D(-1, -1), 
                            Util::Vector2D(-1, -1)
                        }, 
                        
                        {
                            Util::Vector2D(2, -1), 
                            Util::Vector2D(1, -1)
                        }, 
                        
                        {
                            Util::Vector2D(2, 2), 
                            Util::Vector2D(1, 1)
                        }, 
                        
                        {
                            Util::Vector2D(-1, 2), 
                            Util::Vector2D(-1, 1)
                        }
                    }
                ), 
                std::tuple<Piece::Shape, Piece::AttachPoints>(
                    
                    {
                        Util::Vector2D(0, 0), 
                        Util::Vector2D(0, 1), 
                        Util::Vector2D(-1, 1), 
                        Util::Vector2D(-1, 0)
                    }, 
                    
                    {
                        
                        {
                            Util::Vector2D(1, -1), 
                            Util::Vector2D(1, -1)
                        }, 
                        
                        {
                            Util::Vector2D(1, 2), 
                            Util::Vector2D(1, 1)
                        }, 
                        
                        {
                            Util::Vector2D(-2, 2), 
                            Util::Vector2D(-1, 1)
                        }, 
                        
                        {
                            Util::Vector2D(-2, -1), 
                            Util::Vector2D(-1, -1)
                        }
                    }
                ), 
                std::tuple<Piece::Shape, Piece::AttachPoints>(
                    
                    {
                        Util::Vector2D(0, 0), 
                        Util::Vector2D(-1, 0), 
                        Util::Vector2D(-1, -1), 
                        Util::Vector2D(0, -1)
                    }, 
                    
                    {
                        
                        {
                            Util::Vector2D(1, 1), 
                            Util::Vector2D(1, 1)
                        }, 
                        
                        {
                            Util::Vector2D(-2, 1), 
                            Util::Vector2D(-1, 1)
                        }, 
                        
                        {
                            Util::Vector2D(-2, -2), 
                            Util::Vector2D(-1, -1)
                        }, 
                        
                        {
                            Util::Vector2D(1, -2), 
                            Util::Vector2D(1, -1)
                        }
                    }
                ), 
                std::tuple<Piece::Shape, Piece::AttachPoints>(
                    
                    {
                        Util::Vector2D(0, 0), 
                        Util::Vector2D(0, -1), 
                        Util::Vector2D(1, -1), 
                        Util::Vector2D(1, 0)
                    }, 
                    
                    {
                        
                        {
                            Util::Vector2D(-1, 1), 
                            Util::Vector2D(-1, 1)
                        }, 
                        
                        {
                            Util::Vector2D(-1, -2), 
                            Util::Vector2D(-1, -1)
                        }, 
                        
                        {
                            Util::Vector2D(2, -2), 
                            Util::Vector2D(1, -1)
                        }, 
                        
                        {
                            Util::Vector2D(2, 1), 
                            Util::Vector2D(1, 1)
                        }
                    }
                )
            }
        },
        Piece {
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
                        Util::Vector2D(1, -1)
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
                        }
                    }
                ), 
                std::tuple<Piece::Shape, Piece::AttachPoints>(
                    
                    {
                        Util::Vector2D(0, 0), 
                        Util::Vector2D(0, 1), 
                        Util::Vector2D(0, 2), 
                        Util::Vector2D(1, 1)
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
                        Util::Vector2D(-1, 1)
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
                        Util::Vector2D(-1, -1)
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
                            Util::Vector2D(-2, 0), 
                            Util::Vector2D(-1, 1)
                        }, 
                        
                        {
                            Util::Vector2D(-2, -2), 
                            Util::Vector2D(-1, -1)
                        }
                    }
                )
            }
        },
        Piece {
            6, 
            
            {
                Rotation::ZERO, 
                Rotation::ONEHALFPI
            }, 
            
            {
                std::tuple<Piece::Shape, Piece::AttachPoints>(
                    
                    {
                        Util::Vector2D(0, 0), 
                        Util::Vector2D(1, 0), 
                        Util::Vector2D(2, 0), 
                        Util::Vector2D(3, 0)
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
                            Util::Vector2D(4, -1), 
                            Util::Vector2D(1, -1)
                        }, 
                        
                        {
                            Util::Vector2D(4, 1), 
                            Util::Vector2D(1, 1)
                        }
                    }
                ), 
                std::tuple<Piece::Shape, Piece::AttachPoints>(
                    
                    {
                        Util::Vector2D(0, 0), 
                        Util::Vector2D(0, 1), 
                        Util::Vector2D(0, 2), 
                        Util::Vector2D(0, 3)
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
                            Util::Vector2D(1, 4), 
                            Util::Vector2D(1, 1)
                        }, 
                        
                        {
                            Util::Vector2D(-1, 4), 
                            Util::Vector2D(-1, 1)
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
                            Util::Vector2D(1, 1), 
                            Util::Vector2D(1, 1)
                        }, 
                        
                        {
                            Util::Vector2D(1, -1), 
                            Util::Vector2D(1, -1)
                        }, 
                        
                        {
                            Util::Vector2D(-4, 1), 
                            Util::Vector2D(-1, 1)
                        }, 
                        
                        {
                            Util::Vector2D(-4, -1), 
                            Util::Vector2D(-1, -1)
                        }
                    }
                ), 
                std::tuple<Piece::Shape, Piece::AttachPoints>(
                    
                    {
                        Util::Vector2D(0, 0), 
                        Util::Vector2D(0, -1), 
                        Util::Vector2D(0, -2), 
                        Util::Vector2D(0, -3)
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
                            Util::Vector2D(-1, -4), 
                            Util::Vector2D(-1, -1)
                        }, 
                        
                        {
                            Util::Vector2D(1, -4), 
                            Util::Vector2D(1, -1)
                        }
                    }
                )
            }
        },
        Piece {
            7, 
            
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
                        Util::Vector2D(2, -1)
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
                        }
                    }
                ), 
                std::tuple<Piece::Shape, Piece::AttachPoints>(
                    
                    {
                        Util::Vector2D(0, 0), 
                        Util::Vector2D(0, 1), 
                        Util::Vector2D(0, 2), 
                        Util::Vector2D(1, 2)
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
                        }
                    }
                )
            }
        },
        Piece {
            8, 
            
            {
                Rotation::ZERO, 
                Rotation::ONEHALFPI
            }, 
            
            {
                std::tuple<Piece::Shape, Piece::AttachPoints>(
                    
                    {
                        Util::Vector2D(0, 0), 
                        Util::Vector2D(1, 0), 
                        Util::Vector2D(1, -1), 
                        Util::Vector2D(2, -1)
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
                            Util::Vector2D(3, -2), 
                            Util::Vector2D(1, -1)
                        }, 
                        
                        {
                            Util::Vector2D(3, 0), 
                            Util::Vector2D(1, 1)
                        }
                    }
                ), 
                std::tuple<Piece::Shape, Piece::AttachPoints>(
                    
                    {
                        Util::Vector2D(0, 0), 
                        Util::Vector2D(0, 1), 
                        Util::Vector2D(1, 1), 
                        Util::Vector2D(1, 2)
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
                            Util::Vector2D(2, 3), 
                            Util::Vector2D(1, 1)
                        }, 
                        
                        {
                            Util::Vector2D(0, 3), 
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
                            Util::Vector2D(-3, 2), 
                            Util::Vector2D(-1, 1)
                        }, 
                        
                        {
                            Util::Vector2D(-3, 0), 
                            Util::Vector2D(-1, -1)
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
                            Util::Vector2D(-2, -3), 
                            Util::Vector2D(-1, -1)
                        }, 
                        
                        {
                            Util::Vector2D(0, -3), 
                            Util::Vector2D(1, -1)
                        }
                    }
                )
            }
        },
        Piece {
            9, 
            
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
                        Util::Vector2D(3, 1)
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
                            Util::Vector2D(4, 0), 
                            Util::Vector2D(1, -1)
                        }, 
                        
                        {
                            Util::Vector2D(4, 2), 
                            Util::Vector2D(1, 1)
                        }
                    }
                ), 
                std::tuple<Piece::Shape, Piece::AttachPoints>(
                    
                    {
                        Util::Vector2D(0, 0), 
                        Util::Vector2D(-1, 0), 
                        Util::Vector2D(-1, 1), 
                        Util::Vector2D(-1, 2), 
                        Util::Vector2D(-1, 3)
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
                            Util::Vector2D(0, 4), 
                            Util::Vector2D(1, 1)
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
                        Util::Vector2D(0, -1), 
                        Util::Vector2D(-1, -1), 
                        Util::Vector2D(-2, -1), 
                        Util::Vector2D(-3, -1)
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
                            Util::Vector2D(-4, 0), 
                            Util::Vector2D(-1, 1)
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
                        Util::Vector2D(1, 0), 
                        Util::Vector2D(1, -1), 
                        Util::Vector2D(1, -2), 
                        Util::Vector2D(1, -3)
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
                            Util::Vector2D(0, -4), 
                            Util::Vector2D(-1, -1)
                        }, 
                        
                        {
                            Util::Vector2D(2, -4), 
                            Util::Vector2D(1, -1)
                        }
                    }
                )
            }
        },
        Piece {
            10, 
            
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
                        Util::Vector2D(1, -1), 
                        Util::Vector2D(1, -2)
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
                            Util::Vector2D(0, -3), 
                            Util::Vector2D(-1, -1)
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
                        Util::Vector2D(0, 1), 
                        Util::Vector2D(0, 2), 
                        Util::Vector2D(1, 1), 
                        Util::Vector2D(2, 1)
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
                        Util::Vector2D(-1, 0), 
                        Util::Vector2D(-2, 0), 
                        Util::Vector2D(-1, 1), 
                        Util::Vector2D(-1, 2)
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
                        Util::Vector2D(0, -1), 
                        Util::Vector2D(0, -2), 
                        Util::Vector2D(-1, -1), 
                        Util::Vector2D(-2, -1)
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
                            Util::Vector2D(-3, 0), 
                            Util::Vector2D(-1, 1)
                        }, 
                        
                        {
                            Util::Vector2D(-3, -2), 
                            Util::Vector2D(-1, -1)
                        }
                    }
                )
            }
        },
        Piece {
            11, 
            
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
            }
        },
        Piece {
            12, 
            
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
                )
            }
        },
        Piece {
            13, 
            
            {
                Rotation::ZERO, 
                Rotation::ONEHALFPI
            }, 
            
            {
                std::tuple<Piece::Shape, Piece::AttachPoints>(
                    
                    {
                        Util::Vector2D(0, 0), 
                        Util::Vector2D(0, -1), 
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
                            Util::Vector2D(1, 1), 
                            Util::Vector2D(1, 1)
                        }, 
                        
                        {
                            Util::Vector2D(-1, -2), 
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
                ), 
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
                            Util::Vector2D(1, -1), 
                            Util::Vector2D(1, -1)
                        }, 
                        
                        {
                            Util::Vector2D(-2, 1), 
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
                )
            }
        },
        Piece {
            14, 
            
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
                ), 
                std::tuple<Piece::Shape, Piece::AttachPoints>(
                    
                    {
                        Util::Vector2D(0, 0), 
                        Util::Vector2D(0, -1), 
                        Util::Vector2D(0, -2), 
                        Util::Vector2D(0, -3), 
                        Util::Vector2D(0, -4)
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
                            Util::Vector2D(1, -5), 
                            Util::Vector2D(1, -1)
                        }, 
                        
                        {
                            Util::Vector2D(-1, -5), 
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
                        Util::Vector2D(4, 0)
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
                            Util::Vector2D(5, 1), 
                            Util::Vector2D(1, 1)
                        }, 
                        
                        {
                            Util::Vector2D(5, -1), 
                            Util::Vector2D(1, -1)
                        }
                    }
                )
            }
        },
        Piece {
            15, 
            
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
                        Util::Vector2D(0, -1), 
                        Util::Vector2D(1, -1), 
                        Util::Vector2D(1, 0), 
                        Util::Vector2D(0, -2)
                    }, 
                    
                    {
                        
                        {
                            Util::Vector2D(-1, 1), 
                            Util::Vector2D(-1, 1)
                        }, 
                        
                        {
                            Util::Vector2D(2, -2), 
                            Util::Vector2D(1, -1)
                        }, 
                        
                        {
                            Util::Vector2D(2, 1), 
                            Util::Vector2D(1, 1)
                        }, 
                        
                        {
                            Util::Vector2D(-1, -3), 
                            Util::Vector2D(-1, -1)
                        }, 
                        
                        {
                            Util::Vector2D(1, -3), 
                            Util::Vector2D(1, -1)
                        }
                    }
                ), 
                std::tuple<Piece::Shape, Piece::AttachPoints>(
                    
                    {
                        Util::Vector2D(0, 0), 
                        Util::Vector2D(1, 0), 
                        Util::Vector2D(1, 1), 
                        Util::Vector2D(0, 1), 
                        Util::Vector2D(2, 0)
                    }, 
                    
                    {
                        
                        {
                            Util::Vector2D(-1, -1), 
                            Util::Vector2D(-1, -1)
                        }, 
                        
                        {
                            Util::Vector2D(2, 2), 
                            Util::Vector2D(1, 1)
                        }, 
                        
                        {
                            Util::Vector2D(-1, 2), 
                            Util::Vector2D(-1, 1)
                        }, 
                        
                        {
                            Util::Vector2D(3, -1), 
                            Util::Vector2D(1, -1)
                        }, 
                        
                        {
                            Util::Vector2D(3, 1), 
                            Util::Vector2D(1, 1)
                        }
                    }
                ), 
                std::tuple<Piece::Shape, Piece::AttachPoints>(
                    
                    {
                        Util::Vector2D(0, 0), 
                        Util::Vector2D(0, 1), 
                        Util::Vector2D(-1, 1), 
                        Util::Vector2D(-1, 0), 
                        Util::Vector2D(0, 2)
                    }, 
                    
                    {
                        
                        {
                            Util::Vector2D(1, -1), 
                            Util::Vector2D(1, -1)
                        }, 
                        
                        {
                            Util::Vector2D(-2, 2), 
                            Util::Vector2D(-1, 1)
                        }, 
                        
                        {
                            Util::Vector2D(-2, -1), 
                            Util::Vector2D(-1, -1)
                        }, 
                        
                        {
                            Util::Vector2D(1, 3), 
                            Util::Vector2D(1, 1)
                        }, 
                        
                        {
                            Util::Vector2D(-1, 3), 
                            Util::Vector2D(-1, 1)
                        }
                    }
                ), 
                std::tuple<Piece::Shape, Piece::AttachPoints>(
                    
                    {
                        Util::Vector2D(0, 0), 
                        Util::Vector2D(-1, 0), 
                        Util::Vector2D(-1, -1), 
                        Util::Vector2D(0, -1), 
                        Util::Vector2D(-2, 0)
                    }, 
                    
                    {
                        
                        {
                            Util::Vector2D(1, 1), 
                            Util::Vector2D(1, 1)
                        }, 
                        
                        {
                            Util::Vector2D(-2, -2), 
                            Util::Vector2D(-1, -1)
                        }, 
                        
                        {
                            Util::Vector2D(1, -2), 
                            Util::Vector2D(1, -1)
                        }, 
                        
                        {
                            Util::Vector2D(-3, 1), 
                            Util::Vector2D(-1, 1)
                        }, 
                        
                        {
                            Util::Vector2D(-3, -1), 
                            Util::Vector2D(-1, -1)
                        }
                    }
                )
            }
        },
        Piece {
            16, 
            
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
                        Util::Vector2D(0, -1), 
                        Util::Vector2D(1, -1), 
                        Util::Vector2D(1, -2), 
                        Util::Vector2D(2, -2)
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
                            Util::Vector2D(-1, -2), 
                            Util::Vector2D(-1, -1)
                        }, 
                        
                        {
                            Util::Vector2D(2, 0), 
                            Util::Vector2D(1, 1)
                        }, 
                        
                        {
                            Util::Vector2D(0, -3), 
                            Util::Vector2D(-1, -1)
                        }, 
                        
                        {
                            Util::Vector2D(3, -3), 
                            Util::Vector2D(1, -1)
                        }, 
                        
                        {
                            Util::Vector2D(3, -1), 
                            Util::Vector2D(1, 1)
                        }
                    }
                ), 
                std::tuple<Piece::Shape, Piece::AttachPoints>(
                    
                    {
                        Util::Vector2D(0, 0), 
                        Util::Vector2D(1, 0), 
                        Util::Vector2D(1, 1), 
                        Util::Vector2D(2, 1), 
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
                            Util::Vector2D(0, 2), 
                            Util::Vector2D(-1, 1)
                        }, 
                        
                        {
                            Util::Vector2D(3, 0), 
                            Util::Vector2D(1, -1)
                        }, 
                        
                        {
                            Util::Vector2D(3, 3), 
                            Util::Vector2D(1, 1)
                        }, 
                        
                        {
                            Util::Vector2D(1, 3), 
                            Util::Vector2D(-1, 1)
                        }
                    }
                ), 
                std::tuple<Piece::Shape, Piece::AttachPoints>(
                    
                    {
                        Util::Vector2D(0, 0), 
                        Util::Vector2D(0, 1), 
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
                            Util::Vector2D(-3, 3), 
                            Util::Vector2D(-1, 1)
                        }, 
                        
                        {
                            Util::Vector2D(-3, 1), 
                            Util::Vector2D(-1, -1)
                        }
                    }
                ), 
                std::tuple<Piece::Shape, Piece::AttachPoints>(
                    
                    {
                        Util::Vector2D(0, 0), 
                        Util::Vector2D(-1, 0), 
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
                            Util::Vector2D(1, -1), 
                            Util::Vector2D(1, -1)
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
                            Util::Vector2D(-3, 0), 
                            Util::Vector2D(-1, 1)
                        }, 
                        
                        {
                            Util::Vector2D(-3, -3), 
                            Util::Vector2D(-1, -1)
                        }, 
                        
                        {
                            Util::Vector2D(-1, -3), 
                            Util::Vector2D(1, -1)
                        }
                    }
                )
            }
        },
        Piece {
            17, 
            
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
                ), 
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
                )
            }
        },
        Piece {
            18, 
            
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
                        Util::Vector2D(1, 1), 
                        Util::Vector2D(1, -1), 
                        Util::Vector2D(2, -1)
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
                            Util::Vector2D(0, 2), 
                            Util::Vector2D(-1, 1)
                        }, 
                        
                        {
                            Util::Vector2D(2, 2), 
                            Util::Vector2D(1, 1)
                        }, 
                        
                        {
                            Util::Vector2D(0, -2), 
                            Util::Vector2D(-1, -1)
                        }, 
                        
                        {
                            Util::Vector2D(3, -2), 
                            Util::Vector2D(1, -1)
                        }, 
                        
                        {
                            Util::Vector2D(3, 0), 
                            Util::Vector2D(1, 1)
                        }
                    }
                ), 
                std::tuple<Piece::Shape, Piece::AttachPoints>(
                    
                    {
                        Util::Vector2D(0, 0), 
                        Util::Vector2D(0, 1), 
                        Util::Vector2D(-1, 1), 
                        Util::Vector2D(1, 1), 
                        Util::Vector2D(1, 2)
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
                            Util::Vector2D(-2, 0), 
                            Util::Vector2D(-1, -1)
                        }, 
                        
                        {
                            Util::Vector2D(-2, 2), 
                            Util::Vector2D(-1, 1)
                        }, 
                        
                        {
                            Util::Vector2D(2, 0), 
                            Util::Vector2D(1, -1)
                        }, 
                        
                        {
                            Util::Vector2D(2, 3), 
                            Util::Vector2D(1, 1)
                        }, 
                        
                        {
                            Util::Vector2D(0, 3), 
                            Util::Vector2D(-1, 1)
                        }
                    }
                ), 
                std::tuple<Piece::Shape, Piece::AttachPoints>(
                    
                    {
                        Util::Vector2D(0, 0), 
                        Util::Vector2D(-1, 0), 
                        Util::Vector2D(-1, -1), 
                        Util::Vector2D(-1, 1), 
                        Util::Vector2D(-2, 1)
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
                            Util::Vector2D(0, -2), 
                            Util::Vector2D(1, -1)
                        }, 
                        
                        {
                            Util::Vector2D(-2, -2), 
                            Util::Vector2D(-1, -1)
                        }, 
                        
                        {
                            Util::Vector2D(0, 2), 
                            Util::Vector2D(1, 1)
                        }, 
                        
                        {
                            Util::Vector2D(-3, 2), 
                            Util::Vector2D(-1, 1)
                        }, 
                        
                        {
                            Util::Vector2D(-3, 0), 
                            Util::Vector2D(-1, -1)
                        }
                    }
                ), 
                std::tuple<Piece::Shape, Piece::AttachPoints>(
                    
                    {
                        Util::Vector2D(0, 0), 
                        Util::Vector2D(0, -1), 
                        Util::Vector2D(1, -1), 
                        Util::Vector2D(-1, -1), 
                        Util::Vector2D(-1, -2)
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
                            Util::Vector2D(2, 0), 
                            Util::Vector2D(1, 1)
                        }, 
                        
                        {
                            Util::Vector2D(2, -2), 
                            Util::Vector2D(1, -1)
                        }, 
                        
                        {
                            Util::Vector2D(-2, 0), 
                            Util::Vector2D(-1, 1)
                        }, 
                        
                        {
                            Util::Vector2D(-2, -3), 
                            Util::Vector2D(-1, -1)
                        }, 
                        
                        {
                            Util::Vector2D(0, -3), 
                            Util::Vector2D(1, -1)
                        }
                    }
                )
            }
        },
        Piece {
            19, 
            
            {
                Rotation::ZERO
            }, 
            
            {
                std::tuple<Piece::Shape, Piece::AttachPoints>(
                    
                    {
                        Util::Vector2D(0, 0), 
                        Util::Vector2D(0, 1), 
                        Util::Vector2D(-1, 1), 
                        Util::Vector2D(1, 1), 
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
                            Util::Vector2D(-2, 0), 
                            Util::Vector2D(-1, -1)
                        }, 
                        
                        {
                            Util::Vector2D(-2, 2), 
                            Util::Vector2D(-1, 1)
                        }, 
                        
                        {
                            Util::Vector2D(2, 0), 
                            Util::Vector2D(1, -1)
                        }, 
                        
                        {
                            Util::Vector2D(2, 2), 
                            Util::Vector2D(1, 1)
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
                        Util::Vector2D(-1, -1), 
                        Util::Vector2D(-1, 1), 
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
                            Util::Vector2D(0, -2), 
                            Util::Vector2D(1, -1)
                        }, 
                        
                        {
                            Util::Vector2D(-2, -2), 
                            Util::Vector2D(-1, -1)
                        }, 
                        
                        {
                            Util::Vector2D(0, 2), 
                            Util::Vector2D(1, 1)
                        }, 
                        
                        {
                            Util::Vector2D(-2, 2), 
                            Util::Vector2D(-1, 1)
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
                ), 
                std::tuple<Piece::Shape, Piece::AttachPoints>(
                    
                    {
                        Util::Vector2D(0, 0), 
                        Util::Vector2D(0, -1), 
                        Util::Vector2D(1, -1), 
                        Util::Vector2D(-1, -1), 
                        Util::Vector2D(0, -2)
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
                            Util::Vector2D(2, 0), 
                            Util::Vector2D(1, 1)
                        }, 
                        
                        {
                            Util::Vector2D(2, -2), 
                            Util::Vector2D(1, -1)
                        }, 
                        
                        {
                            Util::Vector2D(-2, 0), 
                            Util::Vector2D(-1, 1)
                        }, 
                        
                        {
                            Util::Vector2D(-2, -2), 
                            Util::Vector2D(-1, -1)
                        }, 
                        
                        {
                            Util::Vector2D(1, -3), 
                            Util::Vector2D(1, -1)
                        }, 
                        
                        {
                            Util::Vector2D(-1, -3), 
                            Util::Vector2D(-1, -1)
                        }
                    }
                ), 
                std::tuple<Piece::Shape, Piece::AttachPoints>(
                    
                    {
                        Util::Vector2D(0, 0), 
                        Util::Vector2D(1, 0), 
                        Util::Vector2D(1, 1), 
                        Util::Vector2D(1, -1), 
                        Util::Vector2D(2, 0)
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
                            Util::Vector2D(0, 2), 
                            Util::Vector2D(-1, 1)
                        }, 
                        
                        {
                            Util::Vector2D(2, 2), 
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
                            Util::Vector2D(3, 1), 
                            Util::Vector2D(1, 1)
                        }, 
                        
                        {
                            Util::Vector2D(3, -1), 
                            Util::Vector2D(1, -1)
                        }
                    }
                )
            }
        },
        Piece {
            20, 
            
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
                        Util::Vector2D(3, 0), 
                        Util::Vector2D(1, -1)
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
                            Util::Vector2D(4, -1), 
                            Util::Vector2D(1, -1)
                        }, 
                        
                        {
                            Util::Vector2D(4, 1), 
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
                            Util::Vector2D(1, -1), 
                            Util::Vector2D(1, -1)
                        }, 
                        
                        {
                            Util::Vector2D(-1, -1), 
                            Util::Vector2D(-1, -1)
                        }, 
                        
                        {
                            Util::Vector2D(1, 4), 
                            Util::Vector2D(1, 1)
                        }, 
                        
                        {
                            Util::Vector2D(-1, 4), 
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
                        Util::Vector2D(-2, 0), 
                        Util::Vector2D(-3, 0), 
                        Util::Vector2D(-1, 1)
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
                            Util::Vector2D(-4, 1), 
                            Util::Vector2D(-1, 1)
                        }, 
                        
                        {
                            Util::Vector2D(-4, -1), 
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
                        Util::Vector2D(0, -2), 
                        Util::Vector2D(0, -3), 
                        Util::Vector2D(-1, -1)
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
                            Util::Vector2D(-1, -4), 
                            Util::Vector2D(-1, -1)
                        }, 
                        
                        {
                            Util::Vector2D(1, -4), 
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
                )
            }
        }
    };

    const Piece& PieceCollection::getPiece(const int& index) {
        return allPieces.at(index);
    }   

}