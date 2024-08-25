//In the name of God
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <stdlib.h>
#include <time.h> 
#include "rsdl.hpp"
#include "audio.h"
/* Comments by Neetha */
// code forked from https://github.com/mhyousefi/ZombiesVsPlants
// to compile g++ -o CircuitLand audio.cpp  CircuitLand.cpp  rsdl.cpp -l SDL2  -l SDL2_ttf -l SDL2_image
//*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*
// Speed properties: increase or decrease the following 9 define values to speed up or speed down entities in the game
#define CLK_LENGTH 5
#define ELECTROBYTE_GEN_SKY_CLK_COUNT 2000
#define ELECTROBYTE_GEN_CAPPY_CLK_COUNT 4000
#define VIRUS_CREATE_CLK_COUNT 1200
#define FIRE_ELECTROBOLT_CLK_COUNT 300
#define BYTE_CLK_COUNT 100 
#define VIRUS_CLK_COUNT 22
#define ELECTROBYTE_CLK_COUNT 8
#define ELECTROBOLT_CLK_COUNT 4
//*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*

//*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*
// Alter the 4 define values bellow to increase or decrease the price of Characters and the initial Electrobyte count
#define INIT_ELECTROBYTE_COUNT 200
#define REX_100_PRICE 100
#define CAPPY_PRICE 50
#define INDIE_PRICE 50
//*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*

#define VIRUS_INIT_X 900
#define VIRUS_DX 1
#define ELECTROBOLT_DX 15
#define ELECTROBYTE_DY 1
#define INDIE_BYTE_LIMIT 72
#define CAPPY_BYTE_LIMIT 5
#define REX_BYTE_LIMIT 5

#define WINDOW_WIDTH 1050
#define WINDOW_HEIGHT 600
#define BLOCK_WIDTH 81
#define BLOCK_HEIGHT 101
#define HORIZ_BLOCK_COUNT 9
#define VERT_BLOCK_COUNT 5

#define X_UPPER_LEFT 250 
#define Y_UPPER_LEFT 70
#define TAP_TO_START_X1 230
#define TAP_TO_START_X2 796
#define TAP_TO_START_Y1 520
#define TAP_TO_START_Y2 585
#define ICON_BAR_X1 20
#define ICON_BAR_X2 113
#define ICON_BAR_Y1 102
#define ICON_BAR_Y2 292

#define INIT_ELECTROBYTE_Y 5
#define CAPPY_ICON_Y1 103
#define REX_100_ICON_Y1 167
#define INDIE_ICON_Y1 231

#define ICON_BAR_WIDTH 95
#define ICON_BAR_HEIGHT 194
#define ICON_WIDTH 89
#define ICON_HEIGHT 60
#define ELECTROBYTE_COUNT_WIDTH 70
#define ELECTROBYTE_COUNT_HEIGHT 30
#define ELECTROBYTE_WIDTH 80
#define ELECTROBYTE_HEIGHT 80
#define ELECTROBOLT_WIDTH 20
#define ELECTROBOLT_HEIGHT 20
#define ELEMENT_WIDTH 65
#define ELEMENT_HEIGHT 80

#define STARTING_SCREEN_DIRECTORY "./Image_Assets/Starting_Screen.png"
#define BACKGROUND_DIRECTORY "./Image_Assets/Frontyard.png"
#define BACKGROUND_DIM_DIRECTORY "./Image_Assets/Frontyard_dim.jpeg"
#define LOSING_MESSAGE_DIRECTORY "./Image_Assets/Losing_Message.png"
#define WINNING_MESSAGE_DIRECTORY "./Image_Assets/Winning_Pic.png"
#define BLACK_SCREEN_DIRECTORY "./Image_Assets/Black_Screen.png"
#define VIRUS_HEALTHY_DIRECTORY "./Image_Assets/Virus_healthy.png"
#define VIRUS_INJURED_DIRECTORY "./Image_Assets/Virus_Injured.png"
#define ELECTROBYTE_DIRECTORY "./Image_Assets/Electrobyte.png"
#define CAPPY_DIRECTORY "./Image_Assets/Cappy.png"
#define REX_DIRECTORY "./Image_Assets/Rex.png"
#define ELECTROBOLT_DIRECTORY "./Image_Assets/electrobolt.png"
#define INDIE_UNTOUCHED_DIRECTORY "./Image_Assets/Indie_body.png"
#define INDIE_CRACKED_1_DIRECTORY "./Image_Assets/Indie_cracked1.png"
#define INDIE_CRACKED_2_DIRECTORY "./Image_Assets/Indie_cracked2.png"
#define ICON_BAR_DIRECTORY "./Image_Assets/Item_Bar.png"
#define ELECTROBYTE_COUNT_TEXT_FIELD_DIRECTORY "./Image_Assets/Electrobyte_count_text_field.png"
#define REX_100_ICON_BRIGHT_DIRECTORY "./Image_Assets/icon_rex_100.png"
#define REX_100_ICON_DIM_DIRECTORY "./Image_Assets/icon_rex_100_dim.png"
#define CAPPY_ICON_BRIGHT_DIRECTORY "./Image_Assets/icon_cappy.png"
#define CAPPY_ICON_DIM_DIRECTORY "./Image_Assets/icon_cappy_dim.png"
#define INDIE_ICON_BRIGHT_DIRECTORY "./Image_Assets/icon_indie.png"
#define INDIE_ICON_DIM_DIRECTORY "./Image_Assets/icon_indie_dim.png"

using namespace std;

struct Block{
	int x1, x2;
	int y1, y2;
};

struct Electrobyte{
	int final_col;
	int final_row;
	int y_location;
	int wait_seconds;
};

struct Cappy{
	int row, col;
	int byte;
};

struct Indie{
	int row, col;
	int byte;
	string directory;
};

struct Rex{
	int row, col;
	int byte;
};

struct Electrobolt{
	int row;
	int x_location;
};

struct Virus{
	int row;
	int x_location;
	int health;
	bool is_moving;
	string directory;
};

struct Elements{
	vector<Electrobyte> Electrobytes;
	vector<Virus> viruses;
	vector<Rex> rexs;
	vector<Electrobolt> electrobolts;
	vector<Cappy> cappys;
	vector<Indie> Indies;
};

struct Player{
	string name;
	int Electrobyte_count;
	int level;
	bool is_first_click_made;
};

struct Icons{
	bool is_cappy_chosen;
	bool is_rex_chosen;
	bool is_Indie_chosen;
	string cappy_icon_directory;
	string rex_icon_directory;
	string Indie_icon_directory;
};

struct Level{
	int level_num;
	int wave_count;
	int cur_wave;
	int cur_sec;
	bool waves_finished;

	vector<vector<int> > virus_distr_for_wave;
	vector<int> wave_virus_count;
	vector<int> wave_duration;
};

typedef vector<vector<Block> > Map;

//*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*
//*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*
//*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*
//*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*

bool has_electrobolt_reached_virus(Electrobolt electrobolt, Virus virus);
bool has_virus_reached_element(Virus virus, int row, int col, Map & map);
bool has_virus_reached_any_elements(Elements & elements, Virus & virus, Map & map);


void handle_changes(Elements & elements, Map & map, Level & level, int clk);
void update_moving_status_for_viruses(Elements & elements, Map & map);
void determine_Indie_appearance(Indie & Indie);
void determine_virus_appearanc(Virus & virus);
void handle_electrobolt_virus_encounter(Elements & elements, Map & map);
void apply_electrobolt_hitting_virus(Elements & elements, int p_ind, int z_ind);
void handle_virus_rex_encounter(Elements & elements, Map & map);
void apply_virus_byte_on_rex(Elements & elements, int z_ind, int p_ind, Map & map);
void handle_virus_cappy_encounter(Elements & elements, Map & map);
void apply_virus_byte_on_cappy(Elements & elements, int z_ind, int s_ind, Map & map);
void handle_virus_Indie_encounter(Elements & elements, Map & map);
void apply_virus_byte_on_Indie(Elements & elements, int z_ind, int w_ind, Map & map);
void gen_random_Electrobyte_from_sky(Elements & elements);
void gen_random_Electrobyte_from_cappy(Elements & elements, Cappy cappy, Map & map);
void fire_electrobolts(Elements & elements, Map & map);
void create_new_viruses(Elements & elements, Level & level);
bool are_there_viruses_in_rex_row(Rex rex, Elements & elements);
void remove_Electrobytes(Elements & elements);


void handle_movements(Elements & elements, Map & map, int clk);
void move_viruses(vector<Virus> & viruses, Elements & elements, Map & map);
void move_Electrobytes(vector<Electrobyte> & Electrobytes, Map & map);
void move_electrobolts(vector<Electrobolt> & electrobolts, Elements & elements, Map & map);
bool can_electrobolt_move(Electrobolt & electrobolt, Elements & elements, Map & map);
bool can_virus_move(Virus & virus, Elements & elements, Map & map);


void display_game_elements(window & win, Elements & elements, Map & map);
void display_game_layout(window & win, Player player, Icons icons);
void display_icons_in_icon_bar(Icons icons, Player player, window & win);
void display_losing_message(window & win);
void display_Electrobytes(window & win, vector<Electrobyte> Electrobytes, Map & map);
void display_viruses(window & win, vector<Virus> & viruses, Map & map);
void display_rexs(window & win, vector<Rex> & rexs, Map & map);
void display_electrobolts(window & win, vector<Electrobolt> & electrobolts, Map & map);
void display_cappys(window & win, vector<Cappy> & cappys, Map & map);
void display_Indies(window & win, vector<Indie> & Indies, Map & map);


void handle_user_click(Player & player, Icons & icons, Elements & elements, Map & map, int mouse_x, int mouse_y);
void remove_element_if_clicked_on(Map & map, Elements & elements, int mouse_x, int mouse_y);
void pick_Electrobyte_if_clicked_on(Elements & elements, Map & map, int mouse_x, int mouse_y, bool & Electrobyte_picked, Player & player);
bool is_an_icon_chosen(int mouse_x, int mouse_y);
void determine_icon_chosen(Icons & icons, int mouse_y);
bool click_is_in_frontyard(Map & map, int mouse_x, int mouse_y);
void determine_row_and_col_chosen_by_second_click(Map & map, int mouse_x, int mouse_y, int & row, int & col);
void create_new_Character(Player & player, Map & map, Elements & elements, Icons & icons, int mouse_x, int mouse_y);
bool is_Electrobyte_chosen(Elements & elements, int mouse_x, int mouse_y);
bool is_click_made_in_element_block(int row, int col, int mouse_x, int mouse_y, Map & map);


Map create_a_collection_of_blocks ();
void read_savedata(Player & player, Level & level);
void read_level(Level & level);
void save_wave_cnt_str_as_int(Level & level, string wave_cnt);
void save_virus_seq_str_as_int_vect(Level & level, string virus_seq);
void save_wave_dur_str_as_int_vect(Level & level, string wave_dur);
void init_game(window & win, Level & level, Player & player, Map & map);
void decide_virus_cnt_for_each_sec(Level & level);
void desplay_starting_screen(window & win);
bool user_clicked_on_start(int mouse_x, int mouse_y);
bool has_player_lost(Elements & elements);
bool has_player_won(Level & level, Elements & elements);

//*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*
//*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*
//*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*
//*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*

void handle_changes(Elements & elements, Map & map, Level & level, int clk){
	update_moving_status_for_viruses(elements, map);
	
	handle_electrobolt_virus_encounter(elements, map);
	if (level.waves_finished == false && clk % VIRUS_CREATE_CLK_COUNT == 0)
		create_new_viruses(elements, level);
	if (clk % BYTE_CLK_COUNT == 0){
		handle_virus_Indie_encounter(elements, map);
		handle_virus_rex_encounter(elements, map);
		handle_virus_cappy_encounter(elements, map);
	}
	if (clk % FIRE_ELECTROBOLT_CLK_COUNT == 0)
		fire_electrobolts(elements, map);
	if (clk % ELECTROBYTE_GEN_SKY_CLK_COUNT == 0)
		gen_random_Electrobyte_from_sky(elements);
	if (clk % ELECTROBYTE_GEN_CAPPY_CLK_COUNT == 0)
		for (int i = 0; i < elements.cappys.size(); i++)
			gen_random_Electrobyte_from_cappy(elements, elements.cappys[i], map);

	remove_Electrobytes(elements);
}

void update_moving_status_for_viruses(Elements & elements, Map & map){
	for (int i = 0; i < elements.viruses.size(); i++){
		if (has_virus_reached_any_elements(elements, elements.viruses[i], map))
			elements.viruses[i].is_moving = false;
		elements.viruses[i].is_moving = true;
	}
}

void handle_electrobolt_virus_encounter(Elements & elements, Map & map){
	for (int i = 0; i < elements.viruses.size(); i++)
		for (int j = 0; j < elements.electrobolts.size(); j++)
			apply_electrobolt_hitting_virus(elements, j, i);
}

void apply_electrobolt_hitting_virus(Elements & elements, int p_ind, int z_ind){
	if (has_electrobolt_reached_virus(elements.electrobolts[p_ind], elements.viruses[z_ind])){
		elements.viruses[z_ind].health --;
		elements.electrobolts.erase(elements.electrobolts.begin() + p_ind);
		determine_virus_appearanc(elements.viruses[z_ind]);
		if (elements.viruses[z_ind].health == 0)
			elements.viruses.erase(elements.viruses.begin() + z_ind);
	}
}

void handle_virus_Indie_encounter(Elements & elements, Map & map){
	for (int i = 0; i < elements.Indies.size(); i++)
		for (int j = 0; j < elements.viruses.size(); j++)
			apply_virus_byte_on_Indie(elements, j, i, map);
}

void handle_virus_rex_encounter(Elements & elements, Map & map){
	for (int i = 0; i < elements.rexs.size(); i++)
		for (int j = 0; j < elements.viruses.size(); j++)
			apply_virus_byte_on_rex(elements, j, i, map);
}

void handle_virus_cappy_encounter(Elements & elements, Map & map){
	for (int i = 0; i < elements.cappys.size(); i++)
		for (int j = 0; j < elements.viruses.size(); j++)
			apply_virus_byte_on_cappy(elements, j, i, map);
}

void apply_virus_byte_on_cappy(Elements & elements, int z_ind, int s_ind, Map & map){
	if (has_virus_reached_element(elements.viruses[z_ind], elements.cappys[s_ind].row, elements.cappys[s_ind].col, map)){
		elements.cappys[s_ind].byte ++;
		if (elements.cappys[s_ind].byte == CAPPY_BYTE_LIMIT){
			elements.viruses[z_ind].is_moving = true;
			elements.cappys.erase(elements.cappys.begin() + s_ind);
		}
	}
}

void apply_virus_byte_on_rex(Elements & elements, int z_ind, int p_ind, Map & map){
	if (has_virus_reached_element(elements.viruses[z_ind], elements.rexs[p_ind].row, elements.rexs[p_ind].col, map)){
		elements.rexs[p_ind].byte ++;
		if (elements.rexs[p_ind].byte == REX_BYTE_LIMIT){
			elements.viruses[z_ind].is_moving = true;
			elements.rexs.erase(elements.rexs.begin() + p_ind);
		}
	}
}

void apply_virus_byte_on_Indie(Elements & elements, int z_ind, int w_ind, Map & map){
	if (has_virus_reached_element(elements.viruses[z_ind], elements.Indies[w_ind].row, elements.Indies[w_ind].col, map)){
		elements.Indies[w_ind].byte ++;
		determine_Indie_appearance(elements.Indies[w_ind]);
		if (elements.Indies[w_ind].byte == INDIE_BYTE_LIMIT){
			elements.viruses[z_ind].is_moving = true;
			elements.Indies.erase(elements.Indies.begin() + w_ind);
		}
	}
}

void determine_Indie_appearance(Indie & Indie){
	if (Indie.byte <= 4)
		Indie.directory = INDIE_UNTOUCHED_DIRECTORY;
	else if (Indie.byte > 4 && Indie.byte <= 7)
		Indie.directory = INDIE_CRACKED_1_DIRECTORY;
	else
		Indie.directory = INDIE_CRACKED_2_DIRECTORY;
}

void determine_virus_appearanc(Virus & virus){
	if (virus.health > 4)
		virus.directory = VIRUS_HEALTHY_DIRECTORY;
	else
		virus.directory = VIRUS_INJURED_DIRECTORY;
}

void gen_random_Electrobyte_from_sky(Elements & elements){
	srand(time(NULL));
	Electrobyte temp;
	temp.final_row = rand() % 5;
	temp.final_col = rand() % 9;
	temp.y_location = INIT_ELECTROBYTE_Y;
	temp.wait_seconds = 0;
	elements.Electrobytes.push_back(temp);
}

void gen_random_Electrobyte_from_cappy(Elements & elements, Cappy cappy, Map & map){
	Electrobyte temp;
	temp.final_col = cappy.col;
	temp.final_row = cappy.row;
	temp.y_location = map[cappy.row][cappy.col].y1 - 20;
	temp.wait_seconds = 0;
	elements.Electrobytes.push_back(temp);
}

void fire_electrobolts(Elements & elements, Map & map){
	for (int i = 0; i < elements.rexs.size(); i++){
		Electrobolt temp;
		int row = elements.rexs[i].row;
		int col = elements.rexs[i].col;
		temp.row = row;
		temp.x_location = map[row][col].x2 - 10;
		if (are_there_viruses_in_rex_row(elements.rexs[i], elements))
			elements.electrobolts.push_back(temp);
	}
}

void create_new_viruses(Elements & elements, Level & level){
	srand(time(NULL));
	Virus temp;
	temp.x_location = VIRUS_INIT_X;
	temp.health = 10;
	temp.is_moving = true;
	temp.directory = VIRUS_HEALTHY_DIRECTORY;

	if (level.waves_finished == false){
		int virus_cnt = level.virus_distr_for_wave[level.cur_wave][level.cur_sec];
		temp.row = rand() % 5;
		for (int i = 0; i < virus_cnt; i++){
			elements.viruses.push_back(temp);
			temp.row = (temp.row + 1 < 4) ? temp.row + 1 : 0;
		}
		if (level.cur_sec + 1 < level.wave_duration[level.cur_wave])
			level.cur_sec ++;
		else if (level.cur_wave + 1 < level.wave_count){
			level.cur_sec = 0;
			level.cur_wave ++;
		}
		else 
			level.waves_finished = true;
	}	
}

bool are_there_viruses_in_rex_row(Rex rex, Elements & elements){
	for (int i = 0; i < elements.viruses.size(); i++)
		if (rex.row == elements.viruses[i].row)
			return true;
	return false;
}

void remove_Electrobytes(Elements & elements){
	for (int i = 0; i < elements.Electrobytes.size(); i++)
		if (elements.Electrobytes[i].wait_seconds >= 100)
			elements.Electrobytes.erase(elements.Electrobytes.begin() + i);
}

//*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*
//*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*

void handle_movements(Elements & elements, Map & map, int clk){
	if (clk % VIRUS_CLK_COUNT == 0)	
		move_viruses(elements.viruses, elements, map);
	if (clk % ELECTROBYTE_CLK_COUNT == 0)	
		move_Electrobytes(elements.Electrobytes, map);
	if (clk % ELECTROBOLT_CLK_COUNT == 0)	
		move_electrobolts(elements.electrobolts, elements, map);
}

void move_Electrobytes(vector<Electrobyte> & Electrobytes, Map & map){
	for (int i = 0; i < Electrobytes.size(); i++){
		int row = Electrobytes[i].final_row;
		int col = Electrobytes[i].final_col;
		int lower_limit = map[row][col].y1 + 30;
		if (Electrobytes[i].y_location + ELECTROBYTE_DY < lower_limit)
			Electrobytes[i].y_location += ELECTROBYTE_DY;
		else 
			Electrobytes[i].wait_seconds ++;
	}
}

bool has_electrobolt_reached_virus(Electrobolt electrobolt, Virus virus){
	if (virus.row == electrobolt.row &&
		electrobolt.x_location + ELECTROBOLT_DX > virus.x_location + 30)
			return true;
	return false;
}

bool has_virus_reached_element(Virus virus, int row, int col, Map & map){
	int right_limit = map[row][col].x2 - 35;
	int left_limit  = map[row][col].x1;
	int virus_new_location = virus.x_location - VIRUS_DX;
	if (virus.row == row &&
		virus_new_location < right_limit &&
		virus_new_location > left_limit)
		return true;
	return false;	
}

bool can_electrobolt_move(Electrobolt & electrobolt, Elements & elements, Map & map){
	int right_bound = map[electrobolt.row][8].x2 - 20;
	if (electrobolt.x_location + ELECTROBOLT_DX > right_bound)
		return false;
	for (int i = 0; i < elements.viruses.size(); i++)
		if (has_electrobolt_reached_virus(electrobolt, elements.viruses[i]))
			return false;
	return true;
}

bool can_virus_move(Virus & virus, Elements & elements, Map & map){
	int left_bound = map[0][0].x1;
	int virus_new_location = virus.x_location - VIRUS_DX;
	if (virus_new_location < left_bound)
		return false;
	if (!virus.is_moving)
		return false;
	if (has_virus_reached_any_elements(elements, virus, map))
		return false;
	return true;
}

bool has_virus_reached_any_elements(Elements & elements, Virus & virus, Map & map){
	for (int i = 0; i < elements.Indies.size(); i++)
		if (has_virus_reached_element(virus, elements.Indies[i].row, elements.Indies[i].col, map)){
			virus.is_moving = false;
			return true;
		}
	for (int i = 0; i < elements.rexs.size(); i++)
		if (has_virus_reached_element(virus, elements.rexs[i].row, elements.rexs[i].col, map)){
			virus.is_moving = false;
			return true;
		}
	for (int i = 0; i < elements.cappys.size(); i++)
		if (has_virus_reached_element(virus, elements.cappys[i].row, elements.cappys[i].col, map)){
			virus.is_moving = false;
			return true;
		}
	virus.is_moving = true;
	return false;
}

void move_viruses(vector<Virus> & viruses, Elements & elements, Map & map){
	for (int i = 0; i < viruses.size(); i++){
		if (can_virus_move(viruses[i], elements, map))
			viruses[i].x_location -= VIRUS_DX;
	}
}

void move_electrobolts(vector<Electrobolt> & electrobolts, Elements & elements, Map & map){
	for (int i = 0; i < electrobolts.size(); i++){
		if (can_electrobolt_move(electrobolts[i], elements, map))
			electrobolts[i].x_location += ELECTROBOLT_DX;
	}
}

//*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*
//*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*

void display_game_layout(window & win, Player player, Icons icons){
	win.draw_bg(BLACK_SCREEN_DIRECTORY);
	win.draw_bg(BACKGROUND_DIRECTORY);
	win.draw_png(ICON_BAR_DIRECTORY, 20, 100, ICON_BAR_WIDTH, ICON_BAR_HEIGHT);
	win.draw_png(ELECTROBYTE_DIRECTORY, 5, 5, ELECTROBYTE_WIDTH, ELECTROBYTE_HEIGHT);
	win.draw_png(ELECTROBYTE_COUNT_TEXT_FIELD_DIRECTORY, 85, 33, ELECTROBYTE_COUNT_WIDTH, ELECTROBYTE_COUNT_HEIGHT);
	win.show_text(to_string(player.Electrobyte_count), 100, 33);
	display_icons_in_icon_bar(icons, player, win);
}

void display_icons_in_icon_bar(Icons icons, Player player, window & win){
	if (player.Electrobyte_count < 50){
		win.draw_png(CAPPY_ICON_DIM_DIRECTORY, ICON_BAR_X1 + 3, CAPPY_ICON_Y1, ICON_WIDTH, ICON_HEIGHT);
		win.draw_png(REX_100_ICON_DIM_DIRECTORY, ICON_BAR_X1 + 3, REX_100_ICON_Y1, ICON_WIDTH, ICON_HEIGHT);
		win.draw_png(INDIE_ICON_DIM_DIRECTORY, ICON_BAR_X1 + 3, INDIE_ICON_Y1, ICON_WIDTH, ICON_HEIGHT);
	}
	else if (player.Electrobyte_count >= 50){
		win.draw_png(CAPPY_ICON_BRIGHT_DIRECTORY, ICON_BAR_X1 + 3, CAPPY_ICON_Y1, ICON_WIDTH, ICON_HEIGHT);
		win.draw_png(INDIE_ICON_BRIGHT_DIRECTORY, ICON_BAR_X1 + 3, INDIE_ICON_Y1, ICON_WIDTH, ICON_HEIGHT);
		if (player.Electrobyte_count >= 100)
			win.draw_png(REX_100_ICON_BRIGHT_DIRECTORY, ICON_BAR_X1 + 3, REX_100_ICON_Y1, ICON_WIDTH, ICON_HEIGHT);
		else
			win.draw_png(REX_100_ICON_DIM_DIRECTORY, ICON_BAR_X1 + 3, REX_100_ICON_Y1, ICON_WIDTH, ICON_HEIGHT);
	}
	return;
}

void display_game_elements(window & win, Elements & elements, Map & map){
	display_viruses(win, elements.viruses, map);
	display_rexs(win, elements.rexs, map);
	display_cappys(win, elements.cappys, map);
	display_Indies(win, elements.Indies, map);
	display_electrobolts(win, elements.electrobolts, map);
	display_Electrobytes(win, elements.Electrobytes, map);
}

void display_losing_message(window & win){
	win.draw_bg(BLACK_SCREEN_DIRECTORY);
	win.draw_bg(BACKGROUND_DIM_DIRECTORY);
	win.draw_png(LOSING_MESSAGE_DIRECTORY, WINDOW_WIDTH/4, WINDOW_HEIGHT/8 - 40, 500, 500);
}

void display_winning_message(window & win){
	win.draw_bg(BLACK_SCREEN_DIRECTORY);
	win.draw_bg(BACKGROUND_DIM_DIRECTORY);
	win.draw_png(WINNING_MESSAGE_DIRECTORY, WINDOW_WIDTH/3, WINDOW_HEIGHT/8 - 60, 300, 550);
}

void display_Electrobytes(window & win, vector<Electrobyte> Electrobytes, Map & map){
	for (int i = 0; i < Electrobytes.size(); i++){
		int col = Electrobytes[i].final_col;
		int x_location = map[0][col].x1;
		win.draw_png(ELECTROBYTE_DIRECTORY, x_location, Electrobytes[i].y_location, ELEMENT_WIDTH, ELEMENT_HEIGHT);
	}
}

void display_viruses(window & win, vector<Virus> & viruses, Map & map){
	for (int i = 0; i < viruses.size(); i++){
		int row = viruses[i].row;
		int y_location = map[row][0].y1;
		win.draw_png(viruses[i].directory, viruses[i].x_location, y_location, ELEMENT_WIDTH, ELEMENT_HEIGHT);
	}
}

void display_rexs(window & win, vector<Rex> & rexs, Map & map){
	for (int i = 0; i < rexs.size(); i++){
		int col = rexs[i].col;
		int row = rexs[i].row;
		win.draw_png(REX_DIRECTORY, map[row][col].x1 + 9, map[row][col].y1 + 9, ELEMENT_WIDTH, ELEMENT_HEIGHT);
	}
}

void display_electrobolts(window & win, vector<Electrobolt> & electrobolts, Map & map){
	for (int i = 0; i < electrobolts.size(); i++){
		int row = electrobolts[i].row;
		int y_location = map[row][0].y1 + 20;
		if (electrobolts[i].x_location < (map[0][8].x2 - 35))	
			win.draw_png(ELECTROBOLT_DIRECTORY, electrobolts[i].x_location, y_location, ELECTROBOLT_WIDTH, ELECTROBOLT_HEIGHT);
	}
}

void display_cappys(window & win, vector<Cappy> & cappys, Map & map){
	for (int i = 0; i < cappys.size(); i++){
		int col = cappys[i].col;
		int row = cappys[i].row;
		win.draw_png(CAPPY_DIRECTORY, map[row][col].x1 + 9, map[row][col].y1 + 9, ELEMENT_WIDTH, ELEMENT_HEIGHT);
	}
}

void display_Indies(window & win, vector<Indie> & Indies, Map & map){
	for (int i = 0; i < Indies.size(); i++){
		int col = Indies[i].col;
		int row = Indies[i].row;
		win.draw_png(Indies[i].directory, map[row][col].x1 + 9, map[row][col].y1 + 9, ELEMENT_WIDTH, ELEMENT_HEIGHT);
	}
}

//*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*
//*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*

void handle_user_click(Player & player, Icons & icons, Elements & elements, Map & map, int mouse_x, int mouse_y){
	bool Electrobyte_picked = false;
	if (player.is_first_click_made == false){
		if (is_an_icon_chosen(mouse_x, mouse_y)){
			determine_icon_chosen(icons, mouse_y);
			player.is_first_click_made = true;
		}
		pick_Electrobyte_if_clicked_on(elements, map, mouse_x, mouse_y, Electrobyte_picked, player);
		if (!Electrobyte_picked && click_is_in_frontyard(map, mouse_x, mouse_y))
			remove_element_if_clicked_on(map, elements, mouse_x, mouse_y);
	}
	else if (player.is_first_click_made == true)
		if (click_is_in_frontyard(map, mouse_x, mouse_y)){
			create_new_Character(player, map, elements, icons, mouse_x, mouse_y);
			player.is_first_click_made = false;
		}
}

bool is_an_icon_chosen(int mouse_x, int mouse_y){
	if (mouse_x > ICON_BAR_X1 && mouse_x < ICON_BAR_X2 &&
		mouse_y > ICON_BAR_Y1 && mouse_y < ICON_BAR_Y2)
		return true;
	return false;
}

void determine_icon_chosen(Icons & icons, int mouse_y){
	icons.is_rex_chosen = false;
	icons.is_Indie_chosen = false;
	icons.is_cappy_chosen = false;
	if (mouse_y > CAPPY_ICON_Y1 && mouse_y < CAPPY_ICON_Y1 + ICON_HEIGHT)
		icons.is_cappy_chosen = true;
	else if (mouse_y > REX_100_ICON_Y1 && 
		mouse_y < REX_100_ICON_Y1 + ICON_HEIGHT)
		icons.is_rex_chosen = true;
	else
		icons.is_Indie_chosen = true;
}

bool click_is_in_frontyard(Map & map, int mouse_x, int mouse_y){
	int right_bound = map[0][8].x2;
	int left_bound = map[0][0].x1;
	int upper_bound = map[0][0].y1;
	int lower_bound = map[4][0].y2;
	if (mouse_x > left_bound && mouse_x < right_bound &&
		mouse_y > upper_bound && mouse_y < lower_bound)
		return true;
	return false;
}

void determine_row_and_col_chosen_by_second_click(Map & map, int mouse_x, int mouse_y, int & row, int & col){
	for (int y = 0; y < VERT_BLOCK_COUNT; y++)
		for (int x = 0; x < HORIZ_BLOCK_COUNT; x++)
			if (mouse_x > map[y][x].x1 && mouse_x < map[y][x].x2 &&
				mouse_y > map[y][x].y1 && mouse_y < map[y][x].y2){
				row = y; col = x;
			return;
			}
}

void create_new_Character(Player & player, Map & map, Elements & elements, Icons & icons, int mouse_x, int mouse_y){
	int row, col;
	determine_row_and_col_chosen_by_second_click(map, mouse_x, mouse_y, row, col);
	if (icons.is_cappy_chosen && player.Electrobyte_count >= 50){
		Cappy temp; 
		temp.row = row; temp.col = col;
		temp.byte = 0;
		elements.cappys.push_back(temp);
		player.Electrobyte_count -= CAPPY_PRICE;
	}
	else if (icons.is_rex_chosen && player.Electrobyte_count >= 100){
		Rex temp;
		temp.row = row; temp.col = col;
		temp.byte = 0;
		elements.rexs.push_back(temp);
		player.Electrobyte_count -= REX_100_PRICE;
	}
	else if (icons.is_Indie_chosen && player.Electrobyte_count >= 50){
		Indie temp;
		temp.row = row; temp.col = col;
		temp.byte = 0;
		temp.directory = INDIE_UNTOUCHED_DIRECTORY;
		elements.Indies.push_back(temp);
		player.Electrobyte_count -= INDIE_PRICE;
	}
}

void remove_element_if_clicked_on(Map & map, Elements & elements, int mouse_x, int mouse_y){
	for (int i = 0; i < elements.cappys.size(); i++){
		if (is_click_made_in_element_block(elements.cappys[i].row, elements.cappys[i].col, mouse_x, mouse_y, map))
			elements.cappys.erase(elements.cappys.begin() + i);
	}
	for (int i = 0; i < elements.rexs.size(); i++){
		if (is_click_made_in_element_block(elements.rexs[i].row, elements.rexs[i].col, mouse_x, mouse_y, map))
			elements.rexs.erase(elements.rexs.begin() + i);
	}
	for (int i = 0; i < elements.Indies.size(); i++){
		if (is_click_made_in_element_block(elements.Indies[i].row, elements.Indies[i].col, mouse_x, mouse_y, map))
			elements.Indies.erase(elements.Indies.begin() + i);
	}
}

bool is_click_made_in_element_block(int row, int col, int mouse_x, int mouse_y, Map & map){
	if (mouse_x > map[row][col].x1 && mouse_x < map[row][col].x2 &&
		mouse_y > map[row][col].y1 && mouse_y < map[row][col].y2)
		return true;
	return false;
}

void pick_Electrobyte_if_clicked_on(Elements & elements, Map & map, int mouse_x, int mouse_y, bool & Electrobyte_picked, Player & player){
	for (int i = 0; i < elements.Electrobytes.size(); i++){
		int row = elements.Electrobytes[i].final_row; int col = elements.Electrobytes[i].final_col;
		int right_bound = map[row][col].x2;
		int left_bound = map[row][col].x1;
		int upper_bound = elements.Electrobytes[i].y_location;
		int lower_bound = elements.Electrobytes[i].y_location + ELEMENT_HEIGHT;
		if (mouse_x > left_bound && mouse_x < right_bound &&
			mouse_y > upper_bound && mouse_y < lower_bound){
			elements.Electrobytes.erase(elements.Electrobytes.begin() + i);
			Electrobyte_picked = true;
			player.Electrobyte_count += 50;
			return;
		}
		Electrobyte_picked = false;
	}
}

//*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*
//*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*

Map create_a_collection_of_blocks (){
	Map result;
	vector<Block> temps;
	Block temp;
	for (int y = 0; y < VERT_BLOCK_COUNT; y++){
		temps.clear();
		for (int x = 0; x < HORIZ_BLOCK_COUNT; x++){
			temp.x1 = X_UPPER_LEFT + (x * BLOCK_WIDTH);
			temp.x2 = X_UPPER_LEFT + ((x+1) * BLOCK_WIDTH);
			temp.y1 = Y_UPPER_LEFT + (y * BLOCK_HEIGHT);
			temp.y2 = Y_UPPER_LEFT + ((y+1) * BLOCK_HEIGHT);

			temps.push_back(temp);
		}
		result.push_back(temps);
	}
	return result;
}

void read_savedata(Player & player, Level & level){
	string line;
  	ifstream myfile ("savedata.txt");
  	if (myfile.is_open()){
      	getline (myfile,line);
      	player.name = line;
      	getline (myfile, line);
      	level.level_num = stoi(line);
      	myfile.close();
  	}
	else cout << "Unable to open file";
}

void read_level(Level & level){
	string wave_cnt, virus_seq, wave_dur, temp;
	string file_name = "";
	file_name.push_back(level.level_num + '0');
	file_name += ".level.txt";
	ifstream myfile (file_name);
	int num_ind = 0;
	getline(myfile, wave_cnt);
	getline(myfile, virus_seq);
	getline(myfile, wave_dur);

	save_wave_cnt_str_as_int(level, wave_cnt);
	save_virus_seq_str_as_int_vect(level, virus_seq);
	save_wave_dur_str_as_int_vect(level, wave_dur);
	level.cur_wave = 0;
	level.cur_sec = 0;
	level.waves_finished = false;
}

void save_wave_cnt_str_as_int(Level & level, string wave_cnt){
	string temp;
	int num_ind = wave_cnt.find(":") + 2;
	temp = wave_cnt.substr(num_ind, wave_cnt.size() - num_ind);
	level.wave_count = stoi(temp);
}

void save_virus_seq_str_as_int_vect(Level & level, string virus_seq){
	string temp;
	int num_ind = virus_seq.find(":") + 2;
	int space_ind = virus_seq.find(" ", num_ind);
	for (int i = 0; i < level.wave_count; i++){
		temp = virus_seq.substr(num_ind, space_ind - num_ind);
		level.wave_virus_count.push_back(stoi(temp));
		num_ind = space_ind + 1;
		space_ind = virus_seq.find(" ", num_ind);
	}
}

void save_wave_dur_str_as_int_vect(Level & level, string wave_dur){
	string temp;
	int num_ind = wave_dur.find(":") + 2;
	int space_ind = wave_dur.find(" ", num_ind);
	for (int i = 0; i < level.wave_count; i++){
		temp = wave_dur.substr(num_ind, space_ind - num_ind);
		level.wave_duration.push_back(stoi(temp));
		num_ind = space_ind + 1;
		space_ind = wave_dur.find(" ", num_ind);
	}
}

void init_game(window & win, Level & level, Player & player, Map & map){
	desplay_starting_screen(win);
	read_savedata(player, level);
	read_level(level);
	decide_virus_cnt_for_each_sec(level);
	map = create_a_collection_of_blocks();
	player.Electrobyte_count = INIT_ELECTROBYTE_COUNT;
	player.is_first_click_made = false;
}

void decide_virus_cnt_for_each_sec(Level & level){
	srand(time(NULL));
	bool enough_viruses = false;
	int z_cnt, sum;

	for (int wave = 0; wave < level.wave_count; wave++){
		vector<int> temp;
		enough_viruses = false;

		for(int sec = 0; sec < level.wave_duration[wave]; sec++){
			z_cnt = (rand() % 5) + 1;
			sum = 0;
			for (int i = 0; i < temp.size(); i++)
				sum += temp[i];

			if (enough_viruses)
				temp.push_back(0);

			else {	
				if (z_cnt + sum <= level.wave_virus_count[wave])
					temp.push_back(z_cnt);
				else {
					temp.push_back(level.wave_virus_count[wave] - sum);
					enough_viruses = true;
				}
			}
		}
		level.virus_distr_for_wave.push_back(temp);
	}
}

void desplay_starting_screen(window & win){
	bool game_started = false;
	bool quit = false;
	while (quit || !game_started){
		win.draw_png(STARTING_SCREEN_DIRECTORY, 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
		HANDLE(
			QUIT(quit = true);
			KEY_PRESS(q, quit = true);
			LCLICK({
				if (user_clicked_on_start(mouse_x, mouse_y))	
					game_started = true;
			});
		);

		win.update_screen();
		DELAY(10);
	}
}

bool user_clicked_on_start(int mouse_x, int mouse_y){
	if (mouse_x > TAP_TO_START_X1 && mouse_y < TAP_TO_START_X2 &&
		mouse_y > TAP_TO_START_Y1 && mouse_y < TAP_TO_START_Y2)
		return true;
	return false;
}

bool has_player_lost(Elements & elements){
	for (int i = 0; i < elements.viruses.size(); i++){
		if (elements.viruses[i].x_location < X_UPPER_LEFT + 5)
			return true;
	}
	return false;
}

bool has_player_won(Level & level, Elements & elements){
	if (level.waves_finished && elements.viruses.size() == 0)
		return true;
	return false;
}

//*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*
//*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*


int main(){
	bool quit = false;
	long int clk = 0;
	Level level;
	Elements game_characters;
	Icons icons;
	Player player;
	Map map;

	window win(WINDOW_WIDTH, WINDOW_HEIGHT);
   //Audio initialization 
   //Audio init has to be done here else it does not work
   Audio sound;
   sound.load("background_music.wav");
   sound.play();

	init_game(win, level, player, map);

	while(!quit){
		
		if (has_player_lost(game_characters))
			display_losing_message(win);
		else if (has_player_won(level, game_characters))
			display_winning_message(win);
		else {
			display_game_layout(win, player, icons);
			display_game_elements(win, game_characters, map);
			handle_movements(game_characters, map, clk);
			handle_changes(game_characters, map, level, clk);
		}

		HANDLE(
			QUIT(quit = true);
			KEY_PRESS(q, quit = true);
			LCLICK({
				handle_user_click(player, icons, game_characters, map, mouse_x, mouse_y);
			});
		);

		clk ++;
		win.update_screen();
		DELAY(CLK_LENGTH);
	}
	return 0;
}

