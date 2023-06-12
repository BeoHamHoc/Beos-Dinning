#include <Functions.h>
#include <image.h>
#include<libxl.h>
#include <chrono>
#include <ctime>
using namespace libxl;
using namespace std;
using namespace chrono;

int main(int argc, char* args[])
{
    string savefile;
    fstream savefile1("Change/ChangeFileAdress.txt");
    if(savefile1.is_open())
	{
		cout<<"Mo thanh cong savefile!!"<<endl;
	}
	fflush(stdin);
	getline(savefile1,savefile);
	savefile1.close();
	cout <<'"'<< savefile << '"';

    RenderWindow window("BeoHamHoc", SCREEN_WIDTH ,SCREEN_HEIGHT);
    Init();
    //    Font
    char* font1  = "font/vni.common.VTIMESN.ttf";
    char* font7  = "font/DejaVuSerifCondensed-BoldItalic.ttf";
    char* font8  = "font/vni.common.VTIMESN.ttf";
    char* font10 = "font/MontserratAlternatesExtrabold-a0Ag.ttf";

    //Background
    SDL_Texture* background = window.loadTexture("Image/background.png");
    SDL_Texture* background2 = window.loadTexture("Image/background2.jpg");
    SDL_Texture* background3 = window.loadTexture("Image/background3.jpg");
    SDL_Texture* background4 = window.loadTexture("Image/background4.jpg");
    //Other
    SDL_Texture* qr = window.loadTexture("Change/qr_code_change.png");
    SDL_Texture* recipt = window.loadTexture("Image/recipt.png");
    SDL_Texture* aboutscreen = window.loadTexture("Image/about.png");
    SDL_Texture* button = window.loadTexture("image/button.png");
    SDL_Texture* heading = window.loadTextureFromText("Menu", 70, "font/AtomedBold-vmxj7.ttf");
	SDL_Texture* cart = window.loadTextureFromText("Cart", 60, "font/AtomedBold-vmxj7.ttf");
	SDL_Texture* Pay = window.loadTextureFromText("Total:$", 50, "font/vni.common.VTIMESN.ttf");

    //Food&&drink
    SDL_Texture* f[10];
    SDL_Texture* d[10];
    for(int i=1;i<=9;i++)
    {
        string temp = "Image/" + to_string(i)+ ".jpg";
        string temp2 = "Image/d" + to_string(i)+ ".jpg";
        f[i]= window.loadTexture(temp.c_str());
        d[i]= window.loadTexture(temp2.c_str());
    }

    //Xử lí tổng số tiền
    SDL_Texture* Total[1000] = {NULL};
    for(int i = 0; i < 1000 ; i++)
    {
        string temp2 = to_string(i);
        Total[i] = window.loadTextureFromText(temp2, 60);
    }

    //Xử lí tiền đơn lẻ
    int point[20];
    SDL_Texture* Point[20][100] = {NULL};
	for (int i = 0; i <20; i++) {
            point[i]=0;
            for(int j=0;j< 100;j++)
            {
                string temp = to_string(j);
                Point[i][j] = window.loadTextureFromText(temp, 60, font1);
            }
	}

	//Load Khung ảnh
	SDL_Texture* square[6];
    for (int i=0;i<6;i++)
    {
        square[i]=window.loadTexture("Image/square.png");
    }



//	Music
	Mix_Music* gMusic = NULL;
	gMusic = Mix_LoadMUS("NhacNen.mp3");
	if (gMusic == NULL)
	{
		cout << "Failed to load music\n";
	}

//	 play music
	if (Mix_PlayingMusic() == 0)
	{
//		Play the music
		Mix_PlayMusic(gMusic, -1);
	}
//	sound
	int sound = 1;
//	pause
//    food
    char buffer[80];
    int total = 0;
    int choice = 1;
    SDL_Rect rectCustomer[30];
//    Menu Name
    fstream input("Data/MenuName.txt");
    if(input.is_open())
	{
		cout<<"Mo thanh cong!!"<<endl;
	}
    string name[100];
    int k=1;
    fflush(stdin);
    while(!input.eof())
	{
		getline(input,name[k]);
		k++;
	}
	fstream input2("Data/Price.txt");
	if(input2.is_open())
	{
		cout<<"Mo thanh cong!!"<<endl;
	}
	int z=1;
	int price[19];
    fflush(stdin);
     while(!input2.eof())
	{
         input2 >> price[z];
		z++;
	}
	input.close();
	input2.close();


    cout << price[1];



//    Menu
    SDL_Event event;
    int start = 0;
    SDL_Rect buttonrect[6];
    SDL_Rect rectMenu[20]; // rectMenu[7]= none



//unknow

//unknow
	buttonrect[1].x = 16;
	buttonrect[1].y = 16;
	buttonrect[1].w = 16;
	buttonrect[1].h = 16;
//un Sound Button
	buttonrect[2].x = 32;
	buttonrect[2].y = 32;
	buttonrect[2].w = 16;
	buttonrect[2].h = 16;
//Sound button
	buttonrect[3].x = 16;
	buttonrect[3].y = 32;
	buttonrect[3].w = 16;
	buttonrect[3].h = 16;

// Menu button
	buttonrect[4].x = 0;
	buttonrect[4].y = 0;
	buttonrect[4].w = 345;
	buttonrect[4].h = 76;
//option button
	buttonrect[5].x = 0;
	buttonrect[5].y = 0;
	buttonrect[5].w = 1000;
	buttonrect[5].h = 667;

	bool gameRunning = true;
    while (gameRunning)
	{
        SDL_PollEvent(&event);
        {
            if (event.type == SDL_QUIT)
                gameRunning = false;
        }
        window.clear();
        if ( start ==0 )
            {
                total = 0;
                for(int i=0;i<20;i++)
                {
                    point[i]=0;
                }
                //render background
                window.render(background);

                //render khung
                window.renderPortion(170, 335, 345, 76, &buttonrect[4], square[0], rectMenu[0]);
                window.renderPortion(170, 455, 345, 76, &buttonrect[4], square[2], rectMenu[2]);
                window.renderPortion(170, 575, 345, 76, &buttonrect[4], square[3], rectMenu[3]);
                //render chữ
                window.rendertext("Customer",60, 230, 320, rectMenu[7],textColor1);
                window.rendertext("About",60, 275, 440, rectMenu[7],textColor1);
                window.rendertext("Exit",60, 308, 560, rectMenu[7],textColor1);

                window.handleMenuEvent(event, start, rectMenu, window,square);


                if (sound == 1)
                {
                    window.renderPortion(30, 620, 75, 75, &buttonrect[3], button, rectMenu[5]);
                }
                else
                {
                    window.renderPortion(30, 620, 75, 75, &buttonrect[2], button, rectMenu[5]);
                }
                    window.handleState(event, sound, rectMenu[5], window.window);
                if (sound == 0)
                {
                    Mix_PauseMusic();
                }
                else
                {
                    Mix_ResumeMusic();
                }
                window.display();
            }
        if ( start ==1 )
            {
                window.clear();
                window.render(background4);
                window.rendertext("+ right click",40,1000,100,textColor5,font1);
                window.rendertext(" - left click",40,1000,140,textColor5,font1);
                if(choice == 0 )
                        {
                             for(int i=1;i<=9;i++)
                            {
                                if(i%3==1)
                                {
                                    window.renderPortion(30, 40+220*(i-1)/3, 200, 200, &buttonrect[5], d[i], rectCustomer[i+9]);
                                }
                                else if(i%3 == 2)
                                {
                                    window.renderPortion(280, 40+220*(i-2)/3, 200, 200, &buttonrect[5], d[i], rectCustomer[i+9]);
                                }
                                else
                                {
                                    window.renderPortion(520, 40+220*(i-3)/3, 200, 200, &buttonrect[5], d[i], rectCustomer[i+9]);
                                }
                            }
                             for(int i=0;i<3;i++)
                            {
                                for(int j=1;j<=3;j++)
                                {
                                    string temp = '$' + to_string(price[i*3+j+9]);
                                    int x= 125 + (j-1)*250;
                                    int y= 215 + i*230;
                                    window.rendertext(temp.c_str(),20,x-80,y-30,textColor5,font10);
                                    SDL_SetTextureColorMod(Point[i*3+j+9][point[i*3+j+9]], 0,0, 0 );
                                    window.render(x+100, y,10,25, Point[i*3+j+9][point[i*3+j+9]]);
                                    window.rendertext(name[i*3+j+9].c_str(),20,x-80,y,textColor4,font10);
                                }
                            }

                        }
                if ( choice == 1)
                        {
                            for(int i=1;i<=9;i++)
                            {
                                if(i%3==1)
                                {
                                    window.renderPortion(30, 40+210*(i-1)/3, 300, 200, &buttonrect[5], f[i], rectCustomer[i]);
                                }
                                else if(i%3 == 2)
                                {
                                    window.renderPortion(340, 40+210*(i-2)/3, 300, 200, &buttonrect[5], f[i], rectCustomer[i]);
                                }
                                else
                                {
                                    window.renderPortion(650, 40+210*(i-3)/3, 300, 200, &buttonrect[5], f[i], rectCustomer[i]);
                                }
                            }
                            for(int i=0;i<3;i++)
                            {
                                for(int j=1;j<=3;j++)
                                {
                                    string temp = '$' + to_string(price[i*3+j]);
                                    int x= 100 + (j-1)*315;
                                    int y= 205 + i*225;
                                    window.rendertext(temp.c_str(),20,x-70,y-30,textColor5,font10);
                                    SDL_SetTextureColorMod(Point[i*3+j][point[i*3+j]], 0,0, 0 );
                                    window.render(x+150, y,10,25, Point[i*3+j][point[i*3+j]]);
                                    window.rendertext(name[i*3+j].c_str(),20,x-70,y,textColor4,font10);
                                }
                            }
                        }

                window.rendertext("Turn Back", 50, 1000, 590, rectMenu[6],textColor4);
                window.handleQuit(event, start, rectMenu[6], window.window);

                window.renderPortion(1000, 480, 230, 51, &buttonrect[4], square[4], rectCustomer[20]);
                window.rendertext("BUY", 50, 1080, 465, rectMenu[7],textColor1);

                window.renderPortion(1000, 550, 230, 51, &buttonrect[4], square[5], rectCustomer[21]);
                window.rendertext("FOOD/DRINK", 50, 1010, 535, rectMenu[8],textColor1);

                SDL_SetTextureColorMod(Pay, 150,50, 50 );
                window.render(1000,380,Pay);
                SDL_SetTextureColorMod(Total[total],0,163,0 );
                window.render(1150,360,Total[total]);


                SDL_SetTextureColorMod(heading, 150,50, 50 );

                window.render(390,-5,heading);

                // Handle
                window.handleChangeMenuEvent(event,choice, rectCustomer[21],window,square[5]);
                window.handleCustomerEvent(event, choice, rectCustomer, window, total,point,price);
                window.handleBuyEvent(event,start,rectCustomer[20], window, square[4]);
                if (sound == 1)
                {
                    window.renderPortion(1100, 10, 75, 75, &buttonrect[3], button, rectMenu[5]);
                }
                else
                {
                    window.renderPortion(1100, 10, 75, 75, &buttonrect[2], button, rectMenu[5]);
                }
                    window.handleState(event, sound, rectMenu[5], window.window);
                if (sound == 0)
                {
                    Mix_PauseMusic();
                }
                else
                {
                    Mix_ResumeMusic();
                }

                window.display();
            }
        if (start == 3)
        {
            window.render(background);
            window.render(50, 360, aboutscreen);
            window.rendertext("Turn Back", 50, 880, 590, rectMenu[6],textColor2);
            window.handleQuit(event, start, rectMenu[6], window.window);

                if (sound == 1)
                {
                    window.renderPortion(1000, 10, 75, 75, &buttonrect[3], button, rectMenu[5]);
                }
                else
                {
                    window.renderPortion(1000, 10, 75, 75, &buttonrect[2], button, rectMenu[5]);
                }
                    window.handleState(event, sound, rectMenu[5], window.window);
                if (sound == 0)
                {
                    Mix_PauseMusic();
                }
                else
                {
                    Mix_ResumeMusic();
                }
            window.display();
        }
        if (start == 4)
        {

            gameRunning = false;
            break;
        }
        if (start == 5)
        {

            window.clear();
            window.render(background2);



            bool purchase = false;

            SDL_SetTextureColorMod(cart, 150,50, 50 );
            window.render(350,-5,cart);

            SDL_SetTextureColorMod(Pay, 150,50, 50 );
            window.render(350,450,Pay);
            SDL_SetTextureColorMod(Total[total],0,163,0 );
            window.render(530,430,Total[total]);
            window.rendertext("Turn Back", 40, 70, 590, rectMenu[6],textColor2);
            window.handleQuit(event, start, rectMenu[6], window.window);
            window.rendertext("Purchase", 40, 630, 590, rectMenu[8],textColor2);
            window.handleFinish(event, purchase, rectMenu[8], window.window);


            int buyCount=0;
            int drinkCount=0;
            for (int i=1;i <= 18 ;i ++)
            {
                if( i<=9 && point[i] > 0){
                        string tmp = name[i];
                        string cost = '$' + to_string(point[i]*price[i]);
                        window.rendertext(cost.c_str(),20,360,100+30*buyCount,textColor3,font7);
                        window.rendertext(tmp.c_str(),20,50,100+30*buyCount,textColor2,font7);
                        SDL_SetTextureColorMod(Point[i][point[i]], 0,0, 0 );
                        window.render(280,95+30*buyCount,10,30, Point[i][point[i]]);
                        buyCount++;
                }
                if( i>9 && point[i] > 0){
                        string tmp = name[i];
                        string cost = '$' + to_string(point[i]*price[i]);
                        window.rendertext(cost.c_str(),20,750,100+30*drinkCount,textColor3,font7);
                        window.rendertext(tmp.c_str(),20,450,100+30*drinkCount,textColor2,font7);
                        SDL_SetTextureColorMod(Point[i][point[i]], 0,0, 0 );
                        window.render(670,95+30*drinkCount,10,30, Point[i][point[i]]);
                        drinkCount++;
                }

            }
        if(buyCount > 0)
        {
            window.rendertext("Product",20,50,70,textColor4,font7);
            window.rendertext("Vol.",20,280,70,textColor4,font7);
            window.rendertext("Cost",20,360,70,textColor4,font7);
        }

        if(drinkCount > 0)
        {
            window.rendertext("Product",20,450,70,textColor4,font7);
            window.rendertext("Vol.",20,670,70,textColor4,font7);
            window.rendertext("Cost",20,750,70,textColor4,font7);
        }
        if (purchase == true)
            {
                    system_clock::time_point now = system_clock::now();
                    time_t now_c = system_clock::to_time_t(now);

                    strftime(buffer, 80, "%Y-%m-%d %H:%M:%S",localtime(&now_c));
                Book* book = xlCreateXMLBook();

                if (!book->load(savefile.c_str())) {
                        cout <<endl<< "Khoi Tao That Bai.Vui Long thuc hien thay doi file theo huong dan su dung" << endl;
                        start = 6;
                    }
                else{
                book->load(savefile.c_str());
                Sheet* sheet = book->getSheet(0);
                sheet->clear(8, 25, 0, 2);
                sheet->writeStr(6,1,buffer);
                int reciptCount = 0;
                 for (int i=1;i <= 18 ;i++)
                    {
                        if( point[i] > 0)
                            {
                                string tmp = name[i];
                                string cost =to_string(point[i]*price[i]);
                                sheet->writeStr( 8+reciptCount,0, name[i].c_str());
                                sheet->writeNum( 8+reciptCount,1, point[i]);
                                sheet->writeNum( 8+reciptCount,2, point[i]*price[i]);
                                reciptCount++;

                            }
                    }


                // Lưu lại dữ liệu vào file Excel ban đầu
                book->save(savefile.c_str());

                // Giải phóng tài nguyên
                book->release();
                start =6;
//}

            }}
            window.display();
        }
    if(start == 6 )
    {
        window.clear();
        window.render(background3);
        window.render(300,0,recipt);
        window.render(630,20,164,164,qr);
        bool finish = false;
        window.rendertext("Finish", 40, 900, 590, rectMenu[9],textColor2);
        window.handleFinish(event, finish, rectMenu[9], window.window);
        int finalcount = 0;
        for (int i=1;i <= 18 ;i ++)
            {
                if( point[i] > 0)
                    {
                        string tmp = name[i];
                        string cost = '$' + to_string(point[i]*price[i]);
                        window.rendertext(cost.c_str(),15,720,250+17*finalcount,textColor4,font7);
                        window.rendertext(tmp.c_str(),15,360,250+17*finalcount,textColor4,font7);
                        SDL_SetTextureColorMod(Point[i][point[i]], 0,0, 0 );
                        window.render(600,250+17*finalcount,8,16, Point[i][point[i]]);
                        finalcount++;
                    }
            }
        if ( finish == true)
            {
                for (int i = 5; i >= 0; i--)
                    {
                    window.render(background2);
                    window.rendertext("Thank You !!", 80, 470, 260, textColor3, font8);
                    window.rendertext("BACK TO MAIN SCREEN IN", 60, 380, 350,textColor3);
                    string secondsleft = to_string(i);
                    SDL_Texture* secs = window.loadTextureFromText(secondsleft, 920, 350, 60);
                    window.render(920, 350, secs);
                    SDL_RenderPresent(window.renderer);
                    SDL_Delay(1000);
                    }
                start =0;
                window.clear();
            }
            int tota2 = total/10;
            int tmp = (int)(total) - tota2 * 10;
            string tmp2 = to_string(tota2)+'.' + to_string(tmp);
            window.rendertext(('$'+tmp2).c_str(), 20, 720, 600, textColor4, font7);
            window.rendertext(('$'+to_string(total)).c_str(), 20, 720, 620, textColor4, font7);
            window.rendertext(buffer, 15, 500, 190, textColor4, font7);

        window.display();

        }
	}

    window.cleanUp();
	SDL_Quit();
    Mix_Quit();

    return 0;
}
