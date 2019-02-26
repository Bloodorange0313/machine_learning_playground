

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

//ランダムプレーヤ
int randomplayer(int player){
  int index1, index2;
  index1 = rand() % 8;
  index2 = rand() % 8;
  if(put_disk(index2, index1, player) == true){
    return put_disk(index2, index1, player);
  }
  else{
    return randomplayer(player);
  }
}

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




//ボードの最初の位置を記憶する必要がある
//ミニマックス法による
//次の手が最大になるように選択する

vector<pair<int, int> >pd;
int minimax_player(int player, int depth){
  int index1 = 0, index2 = 0;
  int value = 0;

  

  
  for(int i = 0; i < board_size; ++i){
    for(int j = 0; j < board_size; ++j){

      //同時にひっくり返された者を元に戻したい
      for(int s = 0; s < board_size; ++s){
          for(int t = 0; t < board_size; ++t){
            if(list_flippable_disk2(i, j, s, t, player) == true){
              //cells[s][t] = player_reverse(player);
              pd.push_back(make_pair(s, t));
            }
          }
      }
      
      if(put_disk(i, j,player) == true){
        //put_disk(i, j, player);
        if(value < get_count_disk(player)){
          value = get_count_disk(player);
          index2 = j;
          index1 = i;
          //cout << value << endl;
        }
        //元に戻す処理
        cells[j][i] = -1;
        
        for(int g = 0; g < pd.size(); ++g){
          cells[pd[g].second][pd[g].first] = player_reverse(player);
          //cout << pd[g].first << endl;
        }
      }
      
      for(int g = 0; g < pd.size(); ++g){
          pd.pop_back();
      }
    }
  }
  
  
  cout << value << endl;
  
  //cout << index2 << endl;
  //cout << index1 << endl;
  
  //cout << get_count_disk(player) << endl;
  return put_disk(index1, index2, player);
}


int main(){
  InitRand();
  //cout << board_initialize(3,3) << endl;
  for(int i = 0; i < board_size; ++i){
    for(int j = 0; j < board_size; ++j){
      //cout << board_initialize(i, j);
      board_initialize(i, j); //cellsの初期化
      
    }
    cout << endl;
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
      
    }
    else if(player == 0 && putable(0) != false){
      show_board();
      //human_player(0);
      randomplayer(0);
      //minimax_player(0,0);
     
      
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