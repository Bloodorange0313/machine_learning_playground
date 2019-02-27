

#include<iostream>
#include<vector>
#include<random>

#include <time.h>
#include "playground.h"

inline void InitRand(){
  srand((unsigned int)time(NULL));
}

using namespace std;
/*
int white = 0;
int black = 1;
int board_size = 8;
int cells[9][9];
int index1, index2;
*/


int human_player(int player){
  int index1, index2;
  cout << "場所を選んでください" << endl;
  cin >> index1 >> index2;
  if(put_disk(index2, index1, player) != false){
    //put_disk(index1, index2, player);
    return put_disk(index2, index1, player);
  }else{
    return human_player(player);
  }
}






int main(){
  InitRand();
  //cout << board_initialize(3,3) << endl;
  for(int j = 0; j < board_size; ++j){
    for(int i = 0; i < board_size; ++i){
      //cout << board_initialize(i, j);
      board_initialize(i, j); //cellsの初期化
      
    }
    //cout << endl;
  }
  
  int player = 0;
  
  while(putable(1) != false && putable(0) != false){//!game_finish_judge(player)
    if(player==0){
      cout << "白のターンです" << endl;
      cout << "現在の白の個数　" << get_count_disk(0) << endl;
      cout << "現在の黒の個数　" << get_count_disk(1) << endl;
    }else{
      cout << "黒のターンです" << endl;
      cout << "現在の黒の個数　" << get_count_disk(1) << endl;
      cout << "現在の白の個数　" << get_count_disk(0) << endl;
    }
    //黒の石はランダムプレーヤー
    if(player == 1 && putable(1) != false){
      show_board();
      //minimax_player(1, 0);
      randomplayer(1);
      //human_player(0);
      
    }
    else if(player == 0 && putable(0) != false){
      show_board();
      //human_player(0);
      //randomplayer(0);
      human_player(0);
     
      
    }
    if(player==1){
      player = 0;
      //cout << "白のターンです" << endl;
    }else{
      player = 1;
      //cout << "黒のターンです" << endl;
    }
  }
  if(game_finish_judge(player)){
    if(get_count_disk(0) > get_count_disk(1)){
      cout << "勝者は白です" << endl;
    }else if(get_count_disk(1) > get_count_disk(0)){
      cout << "勝者は黒です" << endl;
    }else{
      cout << "引き分けです" << endl;
    }
  
  }
}