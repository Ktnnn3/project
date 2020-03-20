//Project Compro
#include<iostream>
#include<string>
#include<cstring>
#include<fstream>
#include<vector>
#include<cctype>
#include<ctime>
#include<cstdlib>
#include<iomanip>
using namespace std;
int gameover=0;
int gamestart=0,howtoplay=0,leaderB=0;


struct Card{
	string type;
	string namecard;
	int score;
};

class unit{
		string name;
		string typeofp;
		vector<string> onhand;  //การ์ดที่มีบนมือตอนนี้
		int money;		//เงินที่มี
		int score;		//คะแนนการ์ดที่มีบนมือตอนนี้
		int betm;		//เงินที่ลงเดิมพัน
		bool stand_on;		
	public:	
        void showStatus(); //แสดง		
		bool betmoney(); //ใส่เงินที่จะ bet
		void Addmoney(); //จำนวนเงินที่เพิ่ม
		void removemoney();//จำนวนเงินที่ลด
		bool checkgameover();
		void Hit(vector<Card> &);//ใส่สำรับที่จะเอาการ์ดออกมา
		void newTurn();
		void create(string);//ใส่ hero หรือ bot
		bool scorecheck();
		void gamelost();
		bool stand();
		int getscore();
		void gamedraw();
		void gamewin();
};

bool stand();

bool betmoney();

void Addmoney();

void removemoney();

bool checkgameover();

void checkgamemode(int);

void Hit(vector<Card> &);

void newTurn();

void create(string);

bool scorecheck();  //เช็คว่าเกิน 21 มั้ย

int getscore(); //เอาscore ออกจาก private

void gamelost();

void gamedraw();

void gamewin();

int main(){
    cout<<"--------------------------------------------\n";
    cout<<setw(35)<<"I N F O M A T I O N S\n";
    cout<<"--------------------------------------------\n";
    cout<<"        Welcome to the 'Pirate's Sea'.\n        and you are one of pirates.\n";
    cout<<"        Because fighting on the sea \n";
    cout<<"         is the most important. \n";
    cout<<"          Hence you must protect\n";
    cout<<"          your ship from others. \n";
    cout<<"--------------------------------------------\n";
    for(int i=0;i<3;i++){
        cout<<endl;
    }
	cout<<"--------------------------------------------\n";
    cout<<setw(35)<<"W A R N I N G ! ! ! \n";
    cout<<"--------------------------------------------\n";
	cout<<"        Now doubt ship is coming.\n";
    cout<<"   Becareful and prepare for fighting \n";
	cout<<"--------------------------------------------\n";
	int menu=0;	
	srand(time(0));
	while (menu==0){
		unit player,bot;
		char player_action = '\0',bot_action = '\0';
		int player_bit;
		player.create("Player");
		bot.create("bot");
		cout<<"Type [1] to start game"<<endl;
		cout<<"Type [2] how to play the game"<<endl;
		cout<<"Type [3] check leader board"<<endl;
		int input_menu;
		cin>>input_menu;
		checkgamemode(input_menu);
		

		while(gamestart==1){
		
			vector<Card> cc;
			ifstream cards;
			cards.open("cards.txt");
			string ccard;
	
	
			while(getline(cards,ccard)){
				Card c;
				char desk[100];
				char name[100];
				sscanf(ccard.c_str(),"%[^;];%[^;];%d",desk,name,&c.score);
				c.type = desk;
				c.namecard = name;
				cc.push_back(c);
			}
			


			while(true){

				player.newTurn();
				while(player.betmoney());
				bot.newTurn();
				bot.Hit(cc);
				bot.Hit(cc);
				while(player.scorecheck() == true){
					cout << "[H] Hit [S] Stand [E] Exit";
					cout << "Enter your action: ";
					cin >> player_action;
					player_action = toupper(player_action);
					if(player_action == 'E'){
						//ไปร้านค้า
						//ไปstory
					} 
					if(player_action == 'H') {
                        player.Hit(cc);
                        player.showStatus();
                    }
					if(player_action == 'S'){
						player.stand();
						break;
					}



				}
				while(player.scorecheck() == false){
					player.removemoney();
					player.gamelost();
					break;
				}
				
				while(player.stand() == true){ //การกระทำของ bot เมื่อ player เลือก stand


					while(bot.scorecheck() == true){
						
						if(bot.getscore()<player.getscore()){
							bot.Hit(cc);
                            cin.get();
						}else if(bot.getscore()==player.getscore() && bot.getscore()==21){
							player.gamedraw();
							bot_action = 'E';
							break;
						}



					}
					while(bot.scorecheck()==false){
						player.Addmoney();
						player.gamewin();
						bot_action = 'E';
						break;
					}
					if(bot_action = 'E')break;

				}

				//ใส่โค้ดเช็คว่าการ์ดบน cc จะหมดรึยัง ถ้าจะหมดให้รีใหม่


				//ใส่โค้ด gameover โดยเช็คว่าเงินเหลือน้อยกว่า 0 รึยังให้จบเกม


				//ยังนึกไม่ออกอะ

				






			}
		





			
			
			
			
			
			
		}
		while(howtoplay==1){
			cout<<"ihi";
			
			
			
			
		}
		
		while(leaderB==1){
		cout<<"iejiwofjp";	
			
			
			
		}
		
		
		
		
		
		
		
		
		
		
		
	}
	
	
	
	

}



bool unit::betmoney(){ //x cin from player
	cout << "Enter your bet: ";
	int player_bit;
	cin >> player_bit;
	if(player_bit>money){
		cout << "not enough money";
		return true;
	}
	else{
		betm = player_bit;
		return false;
	} 
	
}



void unit::Addmoney(){ //x from function bet.
	money += betm*2;
}




void unit::removemoney(){ //x from function bet.
	money -= betm;
}




bool unit::checkgameover (){
	if(money<=0) return true;
	else return false;
}




void checkgamemode(int x){
	if(x==1) gamestart=1;
	else if(x==2) howtoplay=1;
	else if(x==3) leaderB=1;
	
}




void unit::Hit(vector<Card> &a){
	int i = rand()%a.size();
	string x = a[i].type ;
	string y = a[i].namecard;
	int z = a[i].score;
	onhand.push_back(x+" "+y);
	a.erase(a.begin() + i);
	score += z;	
}


bool unit::stand(){
	stand_on = true;
	return true;

}

void unit::newTurn(){
	onhand.clear();
	score = 0;
	stand_on = false;
}





void unit::create(string t){
		if(t == "Player"){
			cout << "Please input your name: ";
			getline(cin,name);
			money = 500;
		}else if(t == "bot"){
			name = "more money";

		}
}

bool unit::scorecheck(){
	if(score > 21){
		return false;
	}else return true;
}


/////////////////////////////////////////////////

void unit::gamelost(){
    cout<<""<<name<<"'s money is: "<<money<<"\n";
	cout<<"*************************\n";
	cout<<"*                       *\n";
	cout<<"*        You lost       *\n";
	cout<<"*                       *\n";
	cout<<"*************************\n";

}

void unit::gamedraw(){
    cout<<""<<name<<"'s money is: "<<money;
	cout<<"\n*************************\n";
	cout<<"*                       *\n";
	cout<<"*         Draw          *\n";
	cout<<"*                       *\n";
	cout<<"\n*************************\n";

}

void unit::gamewin(){
    cout<<""<<name<<"'s money is: "<<money; 
	cout<<"\n*************************\n";
	cout<<"*                       *\n";
	cout<<"*        You win!       *\n";
	cout<<"*                       *\n";
	cout<<"\n*************************\n";

}

//////////////////////////////////////////////



int unit::getscore(){
	int scorenow ;
	scorenow = score;
	return scorenow;
}

void unit::showStatus(){

	cout<<"*************************\n";
    for(int i=0;i<onhand.size();i++)
	cout<<""<<name<<"'s card is: "<<onhand[i]<<"\n";
	cout<<""<<name<<"'s score is: "<<score<<"\n";
	cout<<"*************************\n";
}
