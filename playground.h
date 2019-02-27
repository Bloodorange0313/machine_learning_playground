#include<iostream>
#include<vector>
#include<random>

#include <time.h>

using namespace std;


int white = 0;
int black = 1;
int board_size = 8;
int cells[8][8];
int index1, index2;


//ボードを初期化する
int board_initialize(int i, int j){
  //int cells[board_size][board_size];
  if(i == 3 && j == 3){
    cells[j][i] = white;
  }
  else if(i == 3 && j == 4){
    cells[j][i] = black;
  }
  else if(i == 4 && j == 3){
    cells[j][i] = black;
  }
  else if(i == 4 && j == 4){
    cells[j][i] = white;
  }
  else{
    cells[j][i] = -1;
  }
  
  return cells[j][i];
}

int player_reverse(int player){
  if(player == 1){
    return 0;
  }else{
    return 1;
  }
}

//(x, y)に置いた時に、(s, t)をひっくり返すことができるか
//dx = 1||dy = 1のとき、1つしか反転しないバグがある
bool list_flippable_disk2(int x, int y, int s, int t, int player){
  //int prev = -1;
  //int next = 1;
  //int direction[3] = {prev, 0, next};
  
  vector<pair<int, int> >flippable;
  for(int dy = -1; dy < 2; ++dy){
    for(int dx = -1; dx < 2; ++dx){
      
      
      //if(!(dx == 0 && dy == 0)){
        //continue;
        //break;
        int depth = 0;
        vector<pair<int, int> >tmp;
        while(true){
          //if(!(dx == 0 && dy == 0)){
          depth++;
          int rx = x + (dx * depth);
          int ry = y + (dy * depth);

          if(0 <= rx && rx < board_size && 0 <= ry && ry < board_size && (rx != x || ry != y)){
            int request = cells[ry][rx];
            if(request == -1){
              break;
            }
            //隣り合っている自分と同じ石を除外したい
            if(request == player && depth == 1/*(abs(rx - x) == 1 || abs(ry - y) == 1)/*/ ){
              break;
            }
            if(request == player){
              if(!tmp.empty()){
                //flippableにtmpの石を追加したい
                int cnt = tmp.size();
                while(cnt > 0){
                  flippable.push_back(make_pair(tmp[cnt - 1].first,tmp[cnt - 1].second));
                  cnt--;
                  //flippable.erase(flippable.front());
                  tmp.pop_back();
                  //cells[flippable[cnt].second][flippable[cnt].first] = player;
                }
                break;
              }
            }else{
              tmp.push_back(make_pair(rx, ry));
            }
          }else{
            break;
          }
          //}
          //depth++;
        }
      //}//else{
        //break;
        //continue;
      //}
      
    }
  }
  
  if(flippable.empty()){
    return false;
  }
  bool dd = false;
  
  for(int i = 0; i < flippable.size(); ++i){
      if(flippable[i].first == s && flippable[i].second == t){
        dd = true;
        
      }
  }
  
  
  return dd;
  //flippable.clear();
}


//石を置く関数
bool put_disk(int x, int y, int player){
  //すでに石が置いてあると置くことができない
  if(cells[y][x] != -1){
    return false;
  }
  //獲得できる石がないときも置くことができない
  bool flippable2 = false;//list_flippable_disk(x, y, player);
  
  for(int j = 0; j < board_size; ++j){
    for(int i = 0; i < board_size; ++i){
      if(list_flippable_disk2(x, y, i, j, player) == true){
        flippable2 = true;
      }
    }
  }
  
  //vector<int>flippable;
  if(flippable2 == false){
    return false;
  }

  //実際に石をおく処理
  cells[y][x] = player;
  for(int j = 0; j < board_size; ++j){
    for(int i = 0; i < board_size; ++i){
      if(list_flippable_disk2(x, y, i, j, player) != false){

        cells[j][i] = player;
        
      }
    }
  }
  
  
  
  return true;
  
}

//オセロの盤面を表示する
void show_board(){
  cout << "--";
  for(int i = 0; i < 8; ++i){
    cout << i << "-";
  }
  cout << endl;
  for(int j = 0; j < board_size; ++j){
    for(int i = 0; i < board_size; ++i){
      //cells[j][i] = board_initialize(i, j);
    }
  }
  for(int j = 0; j < board_size; ++j){
    cout << j << " ";
    for(int i = 0; i < board_size; ++i){
      //put_disk(i, j, player);
      //cout << j << " ";
      if(cells[j][i] == white){
        cout << "W ";
      }else if(cells[j][i] == black){
        cout << "B ";
      }else{
        cout << "* ";
      }
    }
    cout << endl;
  }
}

int winner = -1;

/*
//白の石の個数を数える
int get_white_disk(){
  int cnt = 0;
  for(int i = 0; i < board_size; ++i){
    for(int j = 0; j < board_size; ++j){
      if(cells[i][j] == 0){
        cnt++;
      }
    }
  }
  return cnt;
}

//黒の石の個数を数える
int get_black_disk(){
  int cnt = 0;
  for(int i = 0; i < board_size; ++i){
    for(int j = 0; j < board_size; ++j){
      if(cells[i][j] == 1){
        cnt++;
      }
    }
  }
  return cnt;
}
*/

int get_count_disk(int player){
  int cnt = 0;
  for(int j = 0; j < board_size; ++j){
    for(int i = 0; i < board_size; ++i){
      if(cells[j][i] == player){
        cnt++;
      }
    }
  }
  return cnt;
}

//石を置く場所があるかの判定
bool putable(int player){
  bool judge = false;
  
  for(int j = 0; j < board_size; ++j){
    for(int i = 0; i < board_size; ++i){
      for(int y = 0; y < board_size; ++y){
        for(int x = 0; x < board_size; ++x){
          if(list_flippable_disk2(i, j, x, y, player) == true){
            judge = true;
          }
        }
      }
    }
  }
  return true;
}

//ゲームの終了の判定
bool game_finish_judge(int player){
  bool judge = false;
  /*
  if(get_count_disk(1) == 0 && get_count_disk(0) == 0){
    judge = true;
  }
  */
  if(putable(player) == false){
    judge = true;
  }
  return judge;
}
