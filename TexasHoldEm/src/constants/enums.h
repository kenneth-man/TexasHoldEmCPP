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
		QUIT
	};
	enum Rank {
		IRON,
		BRONZE,
		SILVER,
		GOLD,
		PLATINUM,
		DIAMOND,
		MASTER,
		CHALLENGER
	};
	enum Crypt {
		ENCRYPT,
		DECRYPT
	};
}