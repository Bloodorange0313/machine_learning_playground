#include<iostream>
#include<vector>
#include<random>

#include <time.h>

using namespace std;


int white = 0;
int black = 1;
int board_size = 8;
int cells[9][9];
int index1, index2;


//ボードを初期化する
int board_initialize(int i, int j){
  //int cells[board_size][board_size];
  if(i == 3 && j == 3){
    cells[i][j] = white;
  }
  else if(i == 3 && j == 4){
    cells[i][j] = black;
  }
  else if(i == 4 && j == 3){
    cells[i][j] = black;
  }
  else if(i == 4 && j == 4){
    cells[i][j] = white;
  }
  else{
    cells[i][j] = -1;
  }
  
  return cells[i][j];
}

//(x, y)に置いた時に、(s, t)をひっくり返すことができるか
bool list_flippable_disk2(int x, int y, int s, int t, int player){
  int prev = -1;
  int next = 1;
  int direction[3] = {prev, 0, next};
  vector<pair<int, int> >flippable;
  for(int dx = 0; dx < 3; ++dx){
    for(int dy = 0; dy < 3; ++dy){
      if(direction[dx] == 0 && direction[dy] == 0){
        continue;
      }
      vector<pair<int, int>>tmp;
      int depth = 0;
      while(true){
        depth++;
        int rx = x + (direction[dx] * depth);
        int ry = y + (direction[dy] * depth);
        if(0 <= rx && rx < board_size && 0 <= ry && ry < board_size){
          int request = cells[rx][ry];
          if(request == -1){
            break;
          }
          if(request == player){
            if(!tmp.empty()){
              //flippableにtmpの石を追加したい
              int cnt = tmp.size();
              while(cnt != 0){
                flippable.push_back(make_pair(tmp[0].first,tmp[0].second));
                //flippable.pop_front();
                cnt--;
              }
            }
          }
          else{
            tmp.push_back(make_pair(rx, ry));
          }
        }else{
          break;
        }
      }
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
}


//石を置く関数
bool put_disk(int x, int y, int player){
  //すでに石が置いてあると置くことができない
  if(cells[x][y] != -1){
    return false;
  }
  //獲得できる石がないときも置くことができない
  bool flippable = false;//list_flippable_disk(x, y, player);
  for(int i = 0; i < board_size; ++i){
    for(int j = 0; j < board_size; ++j){
      if(list_flippable_disk2(x, y, i, j, player) == true){
        flippable = true;
      }
    }
  }
  //vector<int>flippable;
  if(flippable == false){
    return false;
  }

  //実際に石をおく処理
  cells[x][y] = player;
  for(int i = 0; i < board_size; ++i){
    for(int j = 0; j < board_size; ++j){
      if(list_flippable_disk2(x, y, i, j, player) != false){

        cells[i][j] = player;
        
      }
    }
  }
  
  for(int i = board_size - 1; i >= 0; --i){
    for(int j = board_size - 1; j >= 0; --j){
      if(list_flippable_disk2(x, y, i, j, player) != false){

        cells[i][j] = player;
        
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
  for(int i = 0; i < board_size; ++i){
    for(int j = 0; j < board_size; ++j){
      //cells[j][i] = board_initialize(i, j);
    }
  }
  for(int i = 0; i < board_size; ++i){
    cout << i << " ";
    for(int j = 0; j < board_size; ++j){
      //put_disk(i, j, player);
      //cout << j << " ";
      if(cells[i][j] == white){
        cout << "W ";
      }else if(cells[i][j] == black){
        cout << "B ";
      }else{
        cout << "* ";
      }
    }
    cout << endl;
  }
}

int winner = -1;


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

//石を置く場所があるかの判定
bool putable(int player){
  bool judge = false;
  
  for(int i = 0; i < board_size; ++i){
    for(int j = 0; j < board_size; ++j){
      for(int x = 0; x < board_size; ++x){
        for(int y = 0; y < board_size; ++y){
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
  if(get_black_disk() == 0 && get_white_disk() == 0){
    judge = true;
  }
  if(putable(player) == false){
    judge = true;
  }
  return judge;
}
