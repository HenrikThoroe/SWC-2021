#include "PieceCollection.hpp"

namespace Model {

    const std::array<Piece, 21> PieceCollection::allPieces = {
        Piece { 0, 
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
	} },
        Piece { 1, 
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
				Util::Vector2D(-0, -1)
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
	} },
        Piece { 2, 
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
					Util::Vector2D(-0, -2), 
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
				Util::Vector2D(-0, -1), 
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
					Util::Vector2D(2, -0), 
					Util::Vector2D(1, 1)
				}, 
				
				{
					Util::Vector2D(2, -2), 
					Util::Vector2D(1, -1)
				}
			}
		)
	} },
        Piece { 3, 
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
				Util::Vector2D(-0, -1), 
				Util::Vector2D(-0, -2)
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
	} },
        Piece { 4, 
	{
		std::tuple<Piece::Shape, Piece::AttachPoints>(
			
			{
				Util::Vector2D(0, 0), 
				Util::Vector2D(1, 0), 
				Util::Vector2D(0, 1), 
				Util::Vector2D(1, 1)
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
					Util::Vector2D(-1, 2), 
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
				Util::Vector2D(-1, 0), 
				Util::Vector2D(-1, 1)
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
				Util::Vector2D(-0, -1), 
				Util::Vector2D(-1, -1)
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
				Util::Vector2D(-0, -1), 
				Util::Vector2D(1, -0), 
				Util::Vector2D(1, -1)
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
					Util::Vector2D(2, 1), 
					Util::Vector2D(1, 1)
				}, 
				
				{
					Util::Vector2D(2, -2), 
					Util::Vector2D(1, -1)
				}
			}
		)
	} },
        Piece { 5, 
	{
		std::tuple<Piece::Shape, Piece::AttachPoints>(
			
			{
				Util::Vector2D(0, 0), 
				Util::Vector2D(0, 1), 
				Util::Vector2D(-1, 1), 
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
				}
			}
		), 
		std::tuple<Piece::Shape, Piece::AttachPoints>(
			
			{
				Util::Vector2D(0, 0), 
				Util::Vector2D(-1, 0), 
				Util::Vector2D(-1, -1), 
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
					Util::Vector2D(-0, -2), 
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
				}
			}
		), 
		std::tuple<Piece::Shape, Piece::AttachPoints>(
			
			{
				Util::Vector2D(0, 0), 
				Util::Vector2D(-0, -1), 
				Util::Vector2D(1, -1), 
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
					Util::Vector2D(2, -0), 
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
				}
			}
		), 
		std::tuple<Piece::Shape, Piece::AttachPoints>(
			
			{
				Util::Vector2D(0, 0), 
				Util::Vector2D(1, -0), 
				Util::Vector2D(1, 1), 
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
					Util::Vector2D(0, 2), 
					Util::Vector2D(-1, 1)
				}, 
				
				{
					Util::Vector2D(2, 2), 
					Util::Vector2D(1, 1)
				}, 
				
				{
					Util::Vector2D(-0, -2), 
					Util::Vector2D(-1, -1)
				}, 
				
				{
					Util::Vector2D(2, -2), 
					Util::Vector2D(1, -1)
				}
			}
		)
	} },
        Piece { 6, 
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
				Util::Vector2D(-0, -1), 
				Util::Vector2D(-0, -2), 
				Util::Vector2D(-0, -3)
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
	} },
        Piece { 7, 
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
				Util::Vector2D(-0, -1), 
				Util::Vector2D(-0, -2), 
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
	} },
        Piece { 8, 
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
					Util::Vector2D(2, -0), 
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
				Util::Vector2D(-0, -1), 
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
					Util::Vector2D(-0, -3), 
					Util::Vector2D(1, -1)
				}
			}
		)
	} },
        Piece { 9, 
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
				Util::Vector2D(-0, -1), 
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
				Util::Vector2D(1, -0), 
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
					Util::Vector2D(-0, -4), 
					Util::Vector2D(-1, -1)
				}, 
				
				{
					Util::Vector2D(2, -4), 
					Util::Vector2D(1, -1)
				}
			}
		)
	} },
        Piece { 10, 
	{
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
				Util::Vector2D(-0, -1), 
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
		), 
		std::tuple<Piece::Shape, Piece::AttachPoints>(
			
			{
				Util::Vector2D(0, 0), 
				Util::Vector2D(-0, -1), 
				Util::Vector2D(1, -1), 
				Util::Vector2D(1, -0), 
				Util::Vector2D(-0, -2)
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
		)
	} },
        Piece { 11, 
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
				Util::Vector2D(-0, -1), 
				Util::Vector2D(-0, -2), 
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
				Util::Vector2D(1, -0), 
				Util::Vector2D(2, -0), 
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
	} },
        Piece { 12, 
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
					Util::Vector2D(2, -0), 
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
				Util::Vector2D(-0, -1), 
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
					Util::Vector2D(-0, -4), 
					Util::Vector2D(1, -1)
				}
			}
		)
	} },
        Piece { 13, 
	{
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
					Util::Vector2D(-3, 0), 
					Util::Vector2D(-1, -1)
				}, 
				
				{
					Util::Vector2D(-3, 3), 
					Util::Vector2D(-1, 1)
				}, 
				
				{
					Util::Vector2D(-1, 3), 
					Util::Vector2D(1, 1)
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
					Util::Vector2D(-0, -3), 
					Util::Vector2D(1, -1)
				}, 
				
				{
					Util::Vector2D(-3, -3), 
					Util::Vector2D(-1, -1)
				}, 
				
				{
					Util::Vector2D(-3, -1), 
					Util::Vector2D(-1, 1)
				}
			}
		), 
		std::tuple<Piece::Shape, Piece::AttachPoints>(
			
			{
				Util::Vector2D(0, 0), 
				Util::Vector2D(-0, -1), 
				Util::Vector2D(1, -1), 
				Util::Vector2D(2, -1), 
				Util::Vector2D(2, -2)
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
					Util::Vector2D(3, -0), 
					Util::Vector2D(1, 1)
				}, 
				
				{
					Util::Vector2D(3, -3), 
					Util::Vector2D(1, -1)
				}, 
				
				{
					Util::Vector2D(1, -3), 
					Util::Vector2D(-1, -1)
				}
			}
		), 
		std::tuple<Piece::Shape, Piece::AttachPoints>(
			
			{
				Util::Vector2D(0, 0), 
				Util::Vector2D(1, -0), 
				Util::Vector2D(1, 1), 
				Util::Vector2D(1, 2), 
				Util::Vector2D(2, 2)
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
					Util::Vector2D(0, 3), 
					Util::Vector2D(-1, 1)
				}, 
				
				{
					Util::Vector2D(3, 3), 
					Util::Vector2D(1, 1)
				}, 
				
				{
					Util::Vector2D(3, 1), 
					Util::Vector2D(1, -1)
				}
			}
		)
	} },
        Piece { 14, 
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
				Util::Vector2D(-0, -1), 
				Util::Vector2D(-0, -2), 
				Util::Vector2D(-0, -3), 
				Util::Vector2D(-0, -4)
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
				Util::Vector2D(1, -0), 
				Util::Vector2D(2, -0), 
				Util::Vector2D(3, -0), 
				Util::Vector2D(4, -0)
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
	} },
        Piece { 15, 
	{
		std::tuple<Piece::Shape, Piece::AttachPoints>(
			
			{
				Util::Vector2D(0, 0), 
				Util::Vector2D(0, 1), 
				Util::Vector2D(1, 1), 
				Util::Vector2D(1, 2), 
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
					Util::Vector2D(2, 0), 
					Util::Vector2D(1, -1)
				}, 
				
				{
					Util::Vector2D(2, 3), 
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
				Util::Vector2D(-1, 1), 
				Util::Vector2D(-2, 1), 
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
					Util::Vector2D(0, 2), 
					Util::Vector2D(1, 1)
				}, 
				
				{
					Util::Vector2D(-3, 2), 
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
				Util::Vector2D(-0, -1), 
				Util::Vector2D(-1, -1), 
				Util::Vector2D(-1, -2), 
				Util::Vector2D(-0, -2)
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
					Util::Vector2D(-2, 0), 
					Util::Vector2D(-1, 1)
				}, 
				
				{
					Util::Vector2D(-2, -3), 
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
				Util::Vector2D(1, -0), 
				Util::Vector2D(1, -1), 
				Util::Vector2D(2, -1), 
				Util::Vector2D(2, -0)
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
					Util::Vector2D(-0, -2), 
					Util::Vector2D(-1, -1)
				}, 
				
				{
					Util::Vector2D(3, -2), 
					Util::Vector2D(1, -1)
				}, 
				
				{
					Util::Vector2D(3, 1), 
					Util::Vector2D(1, 1)
				}
			}
		)
	} },
        Piece { 16, 
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
				Util::Vector2D(1, -0), 
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
					Util::Vector2D(3, -0), 
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
					Util::Vector2D(-0, -2), 
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
	} },
        Piece { 17, 
	{
		std::tuple<Piece::Shape, Piece::AttachPoints>(
			
			{
				Util::Vector2D(0, 0), 
				Util::Vector2D(1, 0), 
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
					Util::Vector2D(2, -1), 
					Util::Vector2D(1, -1)
				}, 
				
				{
					Util::Vector2D(2, 1), 
					Util::Vector2D(1, 1)
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
				Util::Vector2D(0, 1), 
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
					Util::Vector2D(1, 2), 
					Util::Vector2D(1, 1)
				}, 
				
				{
					Util::Vector2D(-1, 2), 
					Util::Vector2D(-1, 1)
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
				Util::Vector2D(-1, 0), 
				Util::Vector2D(-0, -1), 
				Util::Vector2D(-0, -2), 
				Util::Vector2D(-1, -2)
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
					Util::Vector2D(-2, -1), 
					Util::Vector2D(-1, -1)
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
				Util::Vector2D(-0, -1), 
				Util::Vector2D(1, -0), 
				Util::Vector2D(2, -0), 
				Util::Vector2D(2, -1)
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
					Util::Vector2D(1, -2), 
					Util::Vector2D(1, -1)
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
		)
	} },
        Piece { 18, 
	{
		std::tuple<Piece::Shape, Piece::AttachPoints>(
			
			{
				Util::Vector2D(0, 0), 
				Util::Vector2D(1, 0), 
				Util::Vector2D(0, 1), 
				Util::Vector2D(0, 2), 
				Util::Vector2D(-1, 1)
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
					Util::Vector2D(2, 1), 
					Util::Vector2D(1, 1)
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
				Util::Vector2D(0, 1), 
				Util::Vector2D(-1, 0), 
				Util::Vector2D(-2, 0), 
				Util::Vector2D(-1, -1)
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
					Util::Vector2D(-1, 2), 
					Util::Vector2D(-1, 1)
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
					Util::Vector2D(-0, -2), 
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
				Util::Vector2D(-1, 0), 
				Util::Vector2D(-0, -1), 
				Util::Vector2D(-0, -2), 
				Util::Vector2D(1, -1)
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
					Util::Vector2D(-2, -1), 
					Util::Vector2D(-1, -1)
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
					Util::Vector2D(2, -0), 
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
				Util::Vector2D(-0, -1), 
				Util::Vector2D(1, -0), 
				Util::Vector2D(2, -0), 
				Util::Vector2D(1, 1)
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
					Util::Vector2D(1, -2), 
					Util::Vector2D(1, -1)
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
					Util::Vector2D(0, 2), 
					Util::Vector2D(-1, 1)
				}, 
				
				{
					Util::Vector2D(2, 2), 
					Util::Vector2D(1, 1)
				}
			}
		)
	} },
        Piece { 19, 
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
					Util::Vector2D(-0, -2), 
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
				Util::Vector2D(-0, -1), 
				Util::Vector2D(1, -1), 
				Util::Vector2D(-1, -1), 
				Util::Vector2D(-0, -2)
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
					Util::Vector2D(2, -0), 
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
				Util::Vector2D(1, -0), 
				Util::Vector2D(1, 1), 
				Util::Vector2D(1, -1), 
				Util::Vector2D(2, -0)
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
					Util::Vector2D(-0, -2), 
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
	} },
        Piece { 20, 
	{
		std::tuple<Piece::Shape, Piece::AttachPoints>(
			
			{
				Util::Vector2D(0, 0), 
				Util::Vector2D(0, 1), 
				Util::Vector2D(-1, 1), 
				Util::Vector2D(1, 1), 
				Util::Vector2D(2, 1)
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
				Util::Vector2D(-1, -1), 
				Util::Vector2D(-1, 1), 
				Util::Vector2D(-1, 2)
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
					Util::Vector2D(-0, -2), 
					Util::Vector2D(1, -1)
				}, 
				
				{
					Util::Vector2D(-2, -2), 
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
				Util::Vector2D(-0, -1), 
				Util::Vector2D(1, -1), 
				Util::Vector2D(-1, -1), 
				Util::Vector2D(-2, -1)
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
					Util::Vector2D(2, -0), 
					Util::Vector2D(1, 1)
				}, 
				
				{
					Util::Vector2D(2, -2), 
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
		), 
		std::tuple<Piece::Shape, Piece::AttachPoints>(
			
			{
				Util::Vector2D(0, 0), 
				Util::Vector2D(1, -0), 
				Util::Vector2D(1, 1), 
				Util::Vector2D(1, -1), 
				Util::Vector2D(1, -2)
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
					Util::Vector2D(-0, -3), 
					Util::Vector2D(-1, -1)
				}, 
				
				{
					Util::Vector2D(2, -3), 
					Util::Vector2D(1, -1)
				}
			}
		)
	} }

    };

    const Piece& PieceCollection::getPiece(const int& index) {
        return allPieces.at(index);
    }   

}