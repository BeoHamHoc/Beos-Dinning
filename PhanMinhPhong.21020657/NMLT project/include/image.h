#ifndef IMAGE_H
#define IMAGE_H
#include<Functions.h>
using namespace std;
class RenderWindow{
public:
	RenderWindow(const char* p_title, int p_w, int p_h);
	SDL_Texture* loadTexture(const char* p_filePath);
	void cleanUp();
	void clear();
    void render(SDL_Texture* p_tex);
	void render(float x,float y, SDL_Texture* p_tex);
	void render(float x,float y, int size_x, int size_y, SDL_Texture* p_tex);
	void rendertext(const char* string, int size, int x, int y, SDL_Rect& rect,SDL_Color textColor);
	void rendertext(const char* string, int size, int x, int y, SDL_Color textColor);
	void rendertext(const char* string1, int size, int x, int y,SDL_Color textColor,char* font);
	SDL_Texture* loadTextureFromText(string textureText, int size);
	SDL_Texture* loadTextureFromText(string textureText, int x, int y, int size, SDL_Rect& rect,SDL_Color textColor);
	SDL_Texture* loadTextureFromText(string textureText, int x, int y, int size, SDL_Rect& rect);
	SDL_Texture* loadTextureFromText(string textureText, int size, char* font );
	SDL_Texture* loadTextureFromText(string textureText, int x , int y, int size );
	void renderPortion(int x, int y, int size_x, int size_y, SDL_Rect* button, SDL_Texture* p_tex, SDL_Rect &rect);
	void changeColor(Uint8 x,Uint8 y,Uint8 z);
	void handleMenuEvent(SDL_Event event, int& start ,SDL_Rect rect[],RenderWindow &window,SDL_Texture* square[]);
	void handleCustomerEvent(SDL_Event event, int& choice, SDL_Rect rect[], RenderWindow &window, int& total,int fcount[], int price[]);
	void handleState(SDL_Event event, int& state, SDL_Rect rect, SDL_Window* window);
	void handleBuyEvent(SDL_Event event, int& start, SDL_Rect rect, RenderWindow &window,SDL_Texture* square);
	void handleChangeMenuEvent(SDL_Event event, int& choice, SDL_Rect rect, RenderWindow &window,SDL_Texture* square);
	void handleQuit(SDL_Event event, int& start, SDL_Rect rect, SDL_Window* window);
	void handleFinish(SDL_Event event, bool& finish, SDL_Rect rect, SDL_Window* window);

	void display();
    SDL_Color textColor ={255,255,255};
	SDL_Window* window;
	SDL_Renderer* renderer;
	TTF_Font* gFont =TTF_OpenFont("font/Koulen-Regular.ttf", 60);
	int MouseX=0, MouseY=0;

};

#endif // IMAGE_H
