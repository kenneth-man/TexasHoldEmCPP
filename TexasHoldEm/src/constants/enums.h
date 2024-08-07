#pragma once

namespace Enums {
	enum GameState {
		AUTH,
		LOGIN,
		REGISTER,
		TITLE,
		NEWGAME,
		NEWGAME_0,
		NEWGAME_1,
		CONTINUE,
		RANKIRON,
		RANKBRONZE,
		RANKSILVER,
		RANKGOLD,
		RANKPLATNIUM,
		RANKDIAMOND,
		RANKMASTER,
		RANKCHALLENGER,
		INGAME,
		INSTRUCTIONS,
		LEADERBOARD,
		OPTIONS,
		QUIT,
		QUIT_0,
		QUIT_1
	};
	enum InGameState {
		SMALLBLINDBET,
		BIGBLINDBET,
		DEALING,
		PREFLOPBET,
		FLOP,
		FLOPBET,
		TURN,
		TURNBET,
		RIVER,
		RIVERBET,
		SHOWDOWN,
		END,
		EARLYEND,
		FOLD,
		CALL,
		RAISE,
		BET,
		CHECK
	};
	enum Crypt {
		ENCRYPT,
		DECRYPT
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
}