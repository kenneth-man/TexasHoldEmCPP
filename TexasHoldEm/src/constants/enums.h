#pragma once

namespace Enums {
	enum GameState {
		AUTH,
		LOGIN,
		REGISTER,
		TITLE,
		NEWGAME,
		CONTINUE,
		INSTRUCTIONS,
		LEADERBOARD,
		OPTIONS,
		QUIT,
		QUIT_0,
		QUIT_1
	};
	enum Rank {
		IRON,
		BRONZE = 100,
		SILVER = 1000,
		GOLD = 10000,
		PLATINUM = 100000,
		DIAMOND = 500000,
		MASTER = 1000000,
		CHALLENGER = 2000000
	};
	enum Crypt {
		ENCRYPT,
		DECRYPT
	};
}