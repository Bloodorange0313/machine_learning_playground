//https://katoh4u.hatenablog.com/entry/2018/03/22/130105

#include<iostream>
#include<vector>

using namespace std;

int white = 0;
int black = 1;
int board_size = 8;
int cells[8][8];

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
/*
bool list_flippable_disk(int x, int y, int player){
  int prev = -1;
  int next = 1;
  int direction[3] = {prev, 0, next};
  vector<pair<int, int> >flippable;
  for(int dx = 0; dx < 3; ++dx){
    for(int dy = 0; dy < 3; ++dy){
      if(dx == 0 && dy == 0){
        continue;
      }
      vector<pair<int, int>>tmp;
      int depth = 0;
      while(true){
        depth++;
        int rx = x + (dx * depth);
        int ry = y + (dy * depth);
        if(0 <= rx && rx < board_size && 0 <= ry && ry < board_size){
          int request = cells[rx][ry];
          if(request == -1){
            break;
          }
          if(request == player){
            if(!tmp.empty()){
              //flippableにtmpの石を追加したい
              while(!tmp.empty()){
                flippable.push_back(make_pair(tmp[0].first,tmp[0].second));
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
  }else{
    return true;
  }
}
*/
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
          int request = cells[ry][rx];
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
      if(flippable[i].first == t && flippable[i].second == s){
        dd = true;
      }
  }
  return dd;
}

bool put_disk(int x, int y, int player){
  //すでに石が置いてあると置くことができない
  if(cells[y][x] != -1){
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
  cells[y][x] = player;
  for(int i = 0; i < board_size; ++i){
    for(int j = 0; j < board_size; ++j){
      if(list_flippable_disk2(x, y, i, j, player) != false){

        cells[j][i] = player;
        //flippableに追加されたものを入れる必要がある。
        for(int s = 0; s < board_size; ++s){
          for(int t = 0; t < board_size; ++t){
            if(list_flippable_disk2(i, j, t, s, player) == true){
              cells[y][x] = player;
            }
          }
        }
        
      }
    }
  }
  return true;
  
}





//string show_board()

int main(){
  //cout << board_initialize(3,3) << endl;
  for(int i = 0; i < board_size; ++i){
    for(int j = 0; j < board_size; ++j){
      cout << board_initialize(i, j);
      board_initialize(i, j); //cellsの初期化
      
    }
    cout << endl;
  }
  for(int i = 0; i < board_size; ++i){
    for(int j = 0; j < board_size; ++j){
      cout << list_flippable_disk2(3, 5,i,j, white); //<< endl;
      
      //cout << list_flippable_disk2(1, 5,i,j, white); //<< endl;
    }
    cout << endl;
    
  }
  cout << put_disk(3, 4, white) << endl;
  cout << put_disk(3, 5, white) << endl;
}