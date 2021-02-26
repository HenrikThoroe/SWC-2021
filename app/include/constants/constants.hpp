#pragma once

namespace Constants {

    constexpr int BOARD_SIZE = 400;

    constexpr int BOARD_COLUMNS = 20;

    constexpr int BOARD_ROWS = 20;

    constexpr int PIECE_VARIANTS = 268800;

    constexpr int PIECE_VARIANTS_NO_COLOR = 67200;

    constexpr int TURNS = 100;

    constexpr int PIECE_SHAPES = 21;

    constexpr int WIN_POINTS = 1000000000;

    constexpr int LOSE_POINTS = -1000000000;

    constexpr int64_t SEARCH_TIMEOUT = 1800000000; 

    /// The maximum score of each player. 1 Mono + 1 Duo + 2 Trio + 5 Tetro + 12 Pento + 20 Extra
    constexpr int MAX_COLOR_POINTS = 1 + 2 + 2 * 3 + 5 * 4 + 12 * 5 + 20; 

    constexpr const char* REPLAY_HOSTNAME = "swc-blokus.net";

    constexpr const char* REPLAY_SERVER_PATH = "https://swc-blokus.net";

    constexpr const char* REPLAY_RESERVATION_PATH = "/api/v1/replay/reservation/";

}
