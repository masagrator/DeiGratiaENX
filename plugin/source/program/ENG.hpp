#include <array>

namespace ENG {
	//0x10F898 - string pointers array
	//0x133430 - replacement pointer
	std::array CHAPTER_TITLES = {
		"AUG",
		"Aqua Stripe",
		"Sea of silence",
		"Route",
		"Separation",
		"Without Two",
		"Blind spot in the dark",
		"Calculation",
		"Bottom of the sea",
		"Sleeping doll",
		"Night on the board",
		"Confession",
		"Blue Regret",
		"Memories of murder foretold",
		"Happy table",
		"One more lie",
		"Lie",
		"Vanishing gradiation",
		"Promised land",
		"Flower dragon palace",
		"Spider thread",
		"Girl",
		"Rats and levers",
		"Capture",
		"Maria's finger",
		"In the dark",
		"Mission",
		"Sunspot",
		"Pride and prejudice",
		"Origin of species",
		"Shadow",
		"Rescue ship",
		"Node",
		"Artificial Selection",
		"Confusion",
		"Ghost ship",
		"Pathway",
		"Rhythm",
		"Deontology",
		"What could've been",
		"Blank space",
		"Light",
		"Der bestirnte Himmel",
		"Third coffin",
		"Spear",
		"Only one",
		"Infection",
		"From hell",
		"Colour study",
		"Rescue",
		"Holy ground",
		"Shortage",
		"Stay",
		"Godless",
		"Sea of beginning",
		"Human selection",
		"Electromagnetism",
		"Boundary of life",
		"Bamboo boat",
		"Steam",
		"Logic bomb",
		"Town of refuge",
		"Sacrifice",
		"Alice",
		"Not waking in summer kingdom",
		"Neglect",
		"Sinner's boat",
		"Cocoon summer",
		"Balance",
		"Closed box",
		"1/2",
		"Oedipus syndrome",
		"Just the two of us",
		"Another",
		"Bottleneck",
		"Wicked bird's shadow",
		"Time bomb",
		"It's not mermaids in the sea",
		"Crystal gauge",
		"Quest for knowledge",
		"Sleeping beauty",
		"ABYSS",
		"The Fifth Day",
		"Colour Out Of Space",
		"Cry",
		"For the awakening",
		"Dei Gratia",
		"Great sleep",
		"Unmistakable",
		"Letter in a bottle",
		"Lost time",
		"Messenger",
		"Oracle machine",
		"Temperature of the sea is",
		"Cold ozone",
		"Only two clever ways",
		"Not yet for prayer",
		"Sin",
		"To a sunny sea without water",
		"Exodus",
		"UAG",
		"EXTRA STORY Yukari",
		"EXTRA STORY Sousuke",
		"EXTRA STORY Touri",
		"EXTRA STORY Reiri",
		"EXTRA STORY Tokiwa",
		"EXTRA STORY Hikari"
	};

	static_assert(CHAPTER_TITLES.size() == 107);


	std::array SAVE_EXIT = {
		"Exit game and return to title screen?",
		"All unsaved data will be lost.",
		"Proceed?"	
	};

	static_assert(SAVE_EXIT.size() == 3);

	//0x10FBF8 - string array
	//0x133A20 - replacement pointer
	std::array NOTIFICATIONS = {
		"記録メディアの空き容量が不足しています。",
		"セーブするには%s以上の空き容量が必要です。",
		"ゲームを開始してもよろしいですか？",
		//
		"メモリースティックが挿入されていません。",
		"セーブするには%s以上の空き容量が必要です。",
		"ゲームを開始してもよろしいですか？",
		//
		"Save data may be corrupted.",
		"セーブするには%s以上の空き容量が必要です。",
		"ゲームを開始してもよろしいですか？",
		//
		"メモリースティックが挿入されていません。",
		"もう一度チェックしますか？",
		"",
		//
		"Save data may be corrupted.",
		"Check again?",
		"",
		//
		"「\"TITLE_NAME L\"」の",
		"There is no save data,",
		"Check again?",
		//
		"メモリースティックが挿入されていません。",
		"セーブするには%s以上の空き容量が必要です。",
		"もう一度チェックしますか？",
		//
		"セーブデータが破損している可能性があります。",
		"このままセーブを行うと破損データに上書きすることになりますが、",
		"よろしいですか？",
		//
		"Save system data?",
		"",
		"",
		//
		"処理が中断されました。",
		"",
		"",
		//
		"Load system data?",
		"",
		"",
		//
		"System data loaded.",
		"",
		"",
		//
		"サインインされていないため、セーブを行うことは出来ません。",
		"セーブを行うには、サインインを行ってください。",
		"",
		//
		"サインインされていないため、ロードを行うことは出来ません。",
		"ロードを行うには、サインインを行ってください。",
		"",
		//
		"ストレージデバイスが選択されていないため、",
		"セーブを行うことは出来ません。セーブを行うには、",
		"ゲームを再起動してストレージデバイスを選択してください。",
		//
		"ストレージデバイスが選択されていないため、",
		"ロードを行うことは出来ません。ロードを行うには、",
		"ゲームを再起動してストレージデバイスを選択してください。",
		//
		"Overwrite data?",
		"",
		"",
		//
		"Failed to save data,",
		"Please try again.",
		"",
		//
		"Save data is corrupted.",
		"An error occurred while loading.",
		"",
		//
		"Loading data.",
		"All unsaved data will be lost.",
		"Proceed?",
		//
		"You can erase save data, and begin the [Game] from a clean slate.",
		"Your erased save data cannot be recovered.",
		"Are you sure you want to erase your save data?"
	};

	static_assert(NOTIFICATIONS.size() == 63);

	std::array YES_NO = {
		"YES",
		"NO",
		"YES／NO",
		"YES／"
	};

	static_assert(YES_NO.size() == 4);

	std::array QUICK_SAVE = {
		"Quick saving and jumping to selected point.",
		"Proceed?"
	};

	static_assert(QUICK_SAVE.size() == 2);

	//0x10D170 - strings pointer
	//0x133418 - replacement pointer
	std::array PLAYING_LOG_MAIN = {
		"Endings",
		"Scene Titles",
		"Music",
		"Total Text Read"
	};

	static_assert(PLAYING_LOG_MAIN.size() == 4);

	//0x10F3C0 - string array
	//0x133838 - replacement pointer
	std::array MUSIC = {
		"Shizunda Ato ni wa Nanimonai (沈んだあとには何もない)",
		"Akai Umi (あかいうみ)",
		"Umi ga Mieru (海が見える)",
		"Meeting",
		"Meeting",
		"Meeting",
		"Danryuu (暖流)",
		"Suimen (水面)",
		"Suimen (水面)",
		"Seppaku (切迫)",
		"Oshaberi (おしゃべり)",
		"Oshaberi (おしゃべり)",
		"Ofuzake (おふざけ)",
		"Kokuhaku (告白)",
		"Kurai Sennai (暗い船内)",
		"Kurai Sennai (暗い船内)",
		"Moshi, Nara (もし、なら)",
		"Fact",
		"Kako (過去)",
		"Kairyuu (回遊)",
		"Shinkai (深海)",
		"Sakusou (錯綜)",
		"Sakusou (錯綜)",
		"Sakusou (錯綜)",
		"Creature",
		"Creature",
		"Attack",
		"Attack",
		"Aimless",
		"Aimless",
		"Tatakai (戦い)",
		"Exod.",
		"Invisible Disaster",
		"Ellipse Jail",
		""
	};

	static_assert(MUSIC.size() == 35);

	//0x10F4D8 - string array
	//0x133868 - replacement pointer
	std::array SETTINGS_DESCRIPTIONS = {
		"Adjusts the opacity of the%N"
		"textbox.%N%N"
		"The window will grow more%N"
		"transparent the closer it is%N"
		"to 'Min', and vice-versa.",

		"Adjusts the speed messages%N"
		"display at.%N%N"
		"They will display slower the%N"
		"closer it is set to 'Min',%N"
		"and faster the closer it is%N"
		"set to 'Max'.%N"
		"Messages will display%N"
		"instantly if set all the way%N"
		"to 'Max'.",

		"Synchronizes messages with%N"
		"the corresponding voice-line%N"
		"if applicable.%N%N"
		"When set to 'On', messages%N"
		"will be displayed in sync%N"
		"with the voice line.%N%N"
		"If set to 'Off', they will%N"
		"display at the same speed as%N"
		"non-voiced messages.",

		"Changes the buttons with%N"
		"which text can be advanced.%N%N"
		"When set to 'A Button', only%N"
		"the A Button will advance%N"
		"text, but if set to%N"
		"'A Button/D-Pad', then both%N"
		"the A button, the D-Pad,%N"
		"and the right stick will%N"
		"advance text.",

		"Adjusts the speed at which%N"
		"messages display during Auto%N"
		"Mode.%N%N"
		"They will display slower the%N"
		"closer it is set to 'Min',%N"
		"and faster the closer it is%N"
		"set to 'Max'.",

		"Sets how the game skips when%N"
		"the ZR Button is held down.%N%N"
		"If set to 'Read Only', it%N"
		"will only skip messages%N"
		"you've already read and will%N"
		"stop at previously unread%N"
		"messages.%N%N"
		"If set to 'All', it will skip%N"
		"all messages, previously read%N"
		"or otherwise.",

		"Sets how the game skips when%N"
		"the R Button is pressed to%N"
		"enter Skip Mode.%N%N"
		"If set to 'Read Only', it%N"
		"will only skip messages%N"
		"you've already read and will%N"
		"stop at previously unread%N"
		"messages.%N%N"
		"If set to 'All', it will skip%N"
		"all messages, previously read%N"
		"or otherwise.",

		"Sets whether to display scene%N"
		"titles when the scene%N"
		"changes.%N%N"
		"If set to 'On', the scene%N"
		"title will display when the%N"
		"scene changes.%N%N"
		"If set to 'Off', the scene%N"
		"title will not be displayed%N"
		"when the scene changes.",

		"Adjusts the volume of the%N"
		"game's BGM.%N%N"
		"The closer it is to 'Min',%N"
		"the quieter it will be.%N%N"
		"The closer it is to 'Max',%N"
		"the louder it will be.",

		"Adjusts the volume of in-game%N"
		"sound effects.%N%N"
		"The closer it is to 'Min',%N"
		"the quieter they will be.%N%N"
		"The closer it is to 'Max',%N"
		"the louder they will be.",

		"Adjusts the volume of system%N"
		"sound effects.%N%N"
		"The closer it is to 'Min',%N"
		"the quieter they will be.%N%N"
		"The closer it is to 'Max',%N"
		"the louder they will be."
	};

	static_assert(SETTINGS_DESCRIPTIONS.size() == 11);

	char SAVING[] = "Saving...";

	char CUSTOM_NAME[] = "Is %s %s okay?";

	std::array NAME_PROMPT = {
		"Please enter your name",
		"Last",
		"First"
	};

	static_assert(NAME_PROMPT.size() == 3);

	std::array NAME_ERROR = {
		"First name window is blank. Please fill it.",
		"Last name window is blank. Please fill it.",
		"You cannot use this name. Please change it.",
		"Character '%s' cannot be used. "
	};

	static_assert(NAME_ERROR.size() == 4);

	std::array MC_NAME = {
		"Katagiri",
		"Hitoha"
	};

	static_assert(MC_NAME.size() == 2);

	//0x10D190 - strings pointer
	//0x133438 - replacement pointer
	std::array ENDINGS = {
		"Ending 1",
		"Ending 2",
		"Ending 3"
	};

	static_assert(ENDINGS.size() == 3);
}