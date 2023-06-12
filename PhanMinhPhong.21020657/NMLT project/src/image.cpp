    //#include "image.h"
#include "Functions.h"
using namespace std;

//create window
RenderWindow::RenderWindow(const char* p_title, int p_w, int p_h)
	:window(NULL), renderer(NULL)
{
	window = SDL_CreateWindow(p_title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, p_w, p_h, SDL_WINDOW_SHOWN);

	if (window == NULL)
	{
		cout << "Window failed to init. Error: " << SDL_GetError() << endl;
	}

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
}

//load texture
SDL_Texture* RenderWindow::loadTexture(const char* p_filePath)
{
	SDL_Texture* texture = NULL;
	texture = IMG_LoadTexture(renderer, p_filePath);

	if (texture == NULL)
		cout << "Failed to load texture. Error: " << SDL_GetError() << endl;

	return texture;
}
//close :
void RenderWindow::cleanUp()
{
	SDL_DestroyWindow(window);
}

void RenderWindow::clear()
{
	SDL_RenderClear(renderer);
}

//render full window
void RenderWindow::render(SDL_Texture* p_tex) {
	SDL_RenderCopy(renderer, p_tex, NULL, NULL);
}

void RenderWindow::renderPortion(int x, int y, int size_x, int size_y, SDL_Rect* clip, SDL_Texture* p_tex, SDL_Rect &rect)
{
	//Set rendering space and render to screen
	SDL_Rect renderQuad = { x, y, size_x, size_y };
	rect = renderQuad;

	//Render to screen
	SDL_RenderCopy(renderer, p_tex, clip, &renderQuad);
}

void RenderWindow::render(float x,float y, SDL_Texture* p_tex)
{
	SDL_Rect src;
	src.x = 0;
	src.y = 0;
	src.w = 0;
	src.h = 0;

	SDL_QueryTexture(p_tex, NULL, NULL, &src.w, &src.h);

	SDL_Rect dst;
	dst.x = x;
	dst.y = y;
	dst.w = src.w;
	dst.h = src.h;

	SDL_RenderCopy(renderer, p_tex, &src, &dst);
}
void RenderWindow::render(float x,float y, int size_x, int size_y, SDL_Texture* p_tex)
{
	SDL_Rect src;
	src.x = 0;
	src.y = 0;
	src.w= size_x;
	src.h= size_y;

	SDL_QueryTexture(p_tex, NULL, NULL, &src.w, &src.h);

	SDL_Rect dst;
	dst.x = x;
	dst.y = y;
	dst.w = size_x;
	dst.h = size_y;

	SDL_RenderCopy(renderer, p_tex, &src, &dst);
}

void RenderWindow::rendertext(const char* string, int size,int x,int y, SDL_Rect& rect,SDL_Color textColor) {

	gFont = TTF_OpenFont("font/Koulen-Regular.ttf", size);
	if (gFont == NULL)
	{
		printf("Failed to load lazy font! SDL_ttf Error: %s\n", TTF_GetError());
	}
	else
	{
		//Render text

		SDL_Surface* textSurface = TTF_RenderText_Solid(gFont, string, textColor);
		if (textSurface == NULL)
		{
			printf("Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError());
		}
		else
		{
			//Create texture from surface pixels
			SDL_Texture* Texture = SDL_CreateTextureFromSurface(renderer, textSurface);
			if (Texture == NULL)
			{
				printf("Unable to create texture from rendered text! SDL Error: %s\n", SDL_GetError());
			}
			SDL_Rect src;
			src.x = 0;
			src.y = 0;
			src.w;
			src.h;

			SDL_QueryTexture(Texture, NULL, NULL, &src.w, &src.h);

			SDL_Rect dst;
			dst.x = x;
			dst.y = y;
			dst.w = src.w;
			dst.h = src.h;
			rect = dst;
			//Get rid of old surface
			SDL_FreeSurface(textSurface);
			SDL_RenderCopy(renderer, Texture, &src, &dst);
			SDL_DestroyTexture(Texture);
			TTF_CloseFont(gFont);

		}


	}
}

void RenderWindow::rendertext(const char* string, int size, int x, int y,SDL_Color textColor) {

    gFont = TTF_OpenFont("font/Koulen-Regular.ttf", size);
	if (gFont == NULL)
	{
		cout << "Failed to load lazy font! SDL_ttf Error: ", TTF_GetError();
	}
	else
	{
		//Render text
		SDL_Surface* textSurface = TTF_RenderText_Solid(gFont, string, textColor);
		if (textSurface == NULL)
		{
			cout << "Unable to render text surface! SDL_ttf Error:" << TTF_GetError();
		}
		else
		{
			//Create texture from surface pixels
			SDL_Texture* Texture = SDL_CreateTextureFromSurface(renderer, textSurface);
			if (Texture == NULL)
			{
				cout << "Unable to create texture from rendered text! SDL Error:" << SDL_GetError();
			}
			SDL_Rect src;
			src.x = 0;
			src.y = 0;
			src.w = 0;
			src.h = 0;
			SDL_QueryTexture(Texture, NULL, NULL, &src.w, &src.h);
			SDL_Rect dst;
			dst.x = x;
			dst.y = y;
			dst.w = src.w;
			dst.h = src.h;
			//Get rid of old surface
			SDL_FreeSurface(textSurface);

			SDL_RenderCopy(renderer, Texture, &src, &dst);

			SDL_DestroyTexture(Texture);


		}

        TTF_CloseFont(gFont);
	}
}
void RenderWindow::rendertext(const char* string, int size, int x, int y,SDL_Color textColor,char* font) {

    gFont = TTF_OpenFont(font, size);
	if (gFont == NULL)
	{
		cout << "Failed to load lazy font! SDL_ttf Error: ", TTF_GetError();
	}
	else
	{
		//Render text
		SDL_Surface* textSurface = TTF_RenderText_Solid(gFont, string, textColor);
		if (textSurface == NULL)
		{
			cout << "Unable to render text surface! SDL_ttf Error:" << TTF_GetError();
		}
		else
		{
			//Create texture from surface pixels
			SDL_Texture* Texture = SDL_CreateTextureFromSurface(renderer, textSurface);
			if (Texture == NULL)
			{
				cout << "Unable to create texture from rendered text! SDL Error:" << SDL_GetError();
			}
			SDL_Rect src;
			src.x = 0;
			src.y = 0;
			src.w = 0;
			src.h = 0;
			SDL_QueryTexture(Texture, NULL, NULL, &src.w, &src.h);
			SDL_Rect dst;
			dst.x = x;
			dst.y = y;
			dst.w = src.w;
			dst.h = src.h;
			//Get rid of old surface
			SDL_FreeSurface(textSurface);

			SDL_RenderCopy(renderer, Texture, &src, &dst);

			SDL_DestroyTexture(Texture);


		}

        TTF_CloseFont(gFont);
	}
}
SDL_Texture* RenderWindow::loadTextureFromText(string textureText, int x , int y, int size ) {

	gFont = TTF_OpenFont("font/Koulen-Regular.ttf", size);

	SDL_Surface* loadedText = TTF_RenderText_Blended(gFont, textureText.c_str(), textColor);


	SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, loadedText);



	SDL_FreeSurface(loadedText);

	return texture;
}
SDL_Texture* RenderWindow::loadTextureFromText(string textureText, int x, int y, int size,SDL_Rect &rect) {

	gFont = TTF_OpenFont("font/Koulen-Regular.ttf", size);
	SDL_Surface* loadedText = TTF_RenderText_Blended(gFont, textureText.c_str(), textColor);
	SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, loadedText);

	TTF_SizeText(gFont, textureText.c_str(), &rect.w, &rect.h);
	SDL_FreeSurface(loadedText);
	TTF_CloseFont(gFont);
	return texture;
}
SDL_Texture* RenderWindow::loadTextureFromText(string textureText, int x, int y, int size,SDL_Rect &rect, SDL_Color textColor) {

	gFont = TTF_OpenFont("font/Koulen-Regular.ttf", size);
	SDL_Surface* loadedText = TTF_RenderText_Blended(gFont, textureText.c_str(), textColor);
	SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, loadedText);

	TTF_SizeText(gFont, textureText.c_str(), &rect.w, &rect.h);
	// dst.w = loadedText->w;
	// dst.h = loadedText->h;

	// rect = dst;
	SDL_FreeSurface(loadedText);
	TTF_CloseFont(gFont);
	return texture;
}
SDL_Texture* RenderWindow::loadTextureFromText(string textureText, int size ) {

	gFont = TTF_OpenFont("font/Koulen-Regular.ttf", size);


	SDL_Surface* loadedText = TTF_RenderText_Blended(gFont, textureText.c_str(), textColor);

	SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, loadedText);


	SDL_FreeSurface(loadedText);
	TTF_CloseFont(gFont);

	return texture;
}
SDL_Texture* RenderWindow::loadTextureFromText(string textureText, int size,char* font ) {

	gFont = TTF_OpenFont(font, size);


	SDL_Surface* loadedText = TTF_RenderText_Blended(gFont, textureText.c_str(), textColor);

	SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, loadedText);


	SDL_FreeSurface(loadedText);
	TTF_CloseFont(gFont);

	return texture;
}

void RenderWindow::changeColor(Uint8 x,Uint8 y,Uint8 z) {
	textColor = { x,y,z };
};

bool CheckInside(SDL_Rect Button, int x, int y) {
	if (x < Button.x) return false;
	if (x > Button.x + Button.w) return false;
	if (y < Button.y) return false;
	if (y > Button.y + Button.h) return false;
	return true;
}
void RenderWindow::handleMenuEvent(SDL_Event event, int& start, SDL_Rect rect[], RenderWindow &window,SDL_Texture* square[]) {
	if (event.type == SDL_MOUSEMOTION || event.type == SDL_MOUSEBUTTONDOWN || event.type == SDL_MOUSEBUTTONUP) {
		SDL_GetMouseState(&MouseX, &MouseY);
	}
	for (int i = 0; i < 4; i++) {
		if (CheckInside(rect[i], MouseX, MouseY))
			{
                SDL_SetTextureColorMod(square[i], 150, 250, 180);
			    switch (i)
                {
                    case 0:
                        switch (event.type)
                        {
                        case SDL_MOUSEMOTION:
                            break;
                        case SDL_MOUSEBUTTONDOWN:

                            break;
                        case SDL_MOUSEBUTTONUP:
                            start = 1;
                            break;

                        }
                        break;
                    case 1:
                        switch (event.type)
                        {
                        case SDL_MOUSEMOTION:
                            break;
                        case SDL_MOUSEBUTTONDOWN:
                            break;
                        case SDL_MOUSEBUTTONUP:
                             start = 2;
                            break;
                        }
                        break;
                    case 2:

                        switch (event.type)
                        {
                        case SDL_MOUSEMOTION:
                            break;
                        case SDL_MOUSEBUTTONDOWN:

                            break;
                        case SDL_MOUSEBUTTONUP:
                            start = 3;
                            break;
                        }
                        break;
                    case 3:
                        switch (event.type)
                        {
                        case SDL_MOUSEMOTION:
                            break;
                        case SDL_MOUSEBUTTONDOWN:
                            start = 4;
                            break;
                        case SDL_MOUSEBUTTONUP:

                            break;
                        }
                        break;
                    default:
                        break;
                }
            }
        else
        {
            SDL_SetTextureColorMod(square[i], 200, 240, 255);
        }
}
}
void RenderWindow::handleCustomerEvent(SDL_Event event, int& choice, SDL_Rect rect[], RenderWindow &window, int& total, int fcount[],int price[] ) {
	if (event.type == SDL_MOUSEMOTION || event.type == SDL_MOUSEBUTTONDOWN || event.type == SDL_MOUSEBUTTONUP) {
		SDL_GetMouseState(&MouseX, &MouseY);
	}
	for (int i = 0; i <= 18; i++) {
		if (CheckInside(rect[i], MouseX, MouseY))
			{
                if(choice == 1)
			    {switch (i)
                {

                    case 1:
                        switch (event.type)
                        {
                        case SDL_MOUSEMOTION:
                            break;
                        case SDL_MOUSEBUTTONDOWN:
                            if(event.button.button == SDL_BUTTON_LEFT)
                            {
                                total += price[i];
                                fcount[i] += 1;
                                cout << i << "  : " << fcount[i] << endl;
                            }
                            else if(event.button.button == SDL_BUTTON_RIGHT)
                            {
                                if(fcount[i]>0)
                                {
                                    total -= price[i] ;
                                    fcount[i] -= 1;
                                }
                            }
                            break;
                        case SDL_MOUSEBUTTONUP:
                            break;
                        }

                        break;
                    case 2:

                        switch (event.type)
                        {
                        case SDL_MOUSEMOTION:
                            break;
                        case SDL_MOUSEBUTTONDOWN:
                            if(event.button.button == SDL_BUTTON_LEFT)
                            {
                                total += price[i];
                                fcount[i] += 1;
                                cout << i << "  : " << fcount[i] << endl;
                            }
                            else if(event.button.button == SDL_BUTTON_RIGHT)
                            {
                                if(fcount[i]>0)
                                {
                                    total -= price[i] ;
                                    fcount[i] -= 1;
                                }
                            }
                            break;
                        case SDL_MOUSEBUTTONUP:
                            break;
                        }
                        break;
                    case 3:
                        switch (event.type)
                        {
                        case SDL_MOUSEMOTION:
                            break;
                        case SDL_MOUSEBUTTONDOWN:
                            if(event.button.button == SDL_BUTTON_LEFT)
                            {
                                total += price[i];
                                fcount[i] += 1;
                                cout << i << "  : " << fcount[i] << endl;
                            }
                            else if(event.button.button == SDL_BUTTON_RIGHT)
                            {
                                if(fcount[i]>0)
                                {
                                    total -= price[i] ;
                                    fcount[i] -= 1;
                                }
                            }
                            break;
                        case SDL_MOUSEBUTTONUP:

                            break;
                        }
                        break;
                    case 4:
                        switch (event.type)
                        {
                        case SDL_MOUSEMOTION:
                            break;
                        case SDL_MOUSEBUTTONDOWN:
                            if(event.button.button == SDL_BUTTON_LEFT)
                            {
                                total += price[i];
                                fcount[i] += 1;
                            }
                            else if(event.button.button == SDL_BUTTON_RIGHT)
                            {
                                if(fcount[i]>0)
                                {
                                    total -= price[i] ;
                                    fcount[i] -= 1;
                                }
                            }
                            break;
                        case SDL_MOUSEBUTTONUP:

                            break;
                        }
                        break;
                    case 5:
                        switch (event.type)
                        {
                        case SDL_MOUSEMOTION:
                            break;
                        case SDL_MOUSEBUTTONDOWN:
                            if(event.button.button == SDL_BUTTON_LEFT)
                            {
                                total += price[i];
                                fcount[i] += 1;
                            }
                            else if(event.button.button == SDL_BUTTON_RIGHT)
                            {
                                if(fcount[i]>0)
                                {
                                    total -= price[i] ;
                                    fcount[i] -= 1;
                                }
                            }
                            break;
                        case SDL_MOUSEBUTTONUP:

                            break;
                        }
                        break;
                    case 6:
                        switch (event.type)
                        {
                        case SDL_MOUSEMOTION:
                            break;
                        case SDL_MOUSEBUTTONDOWN:
                            if(event.button.button == SDL_BUTTON_LEFT)
                            {
                                total += price[i];
                                fcount[i] += 1;
                            }
                            else if(event.button.button == SDL_BUTTON_RIGHT)
                            {
                                if(fcount[i]>0)
                                {
                                    total -= price[i] ;
                                    fcount[i] -= 1;
                                }
                            }
                            break;
                        case SDL_MOUSEBUTTONUP:

                            break;
                        }
                        break;
                    case 7:
                        switch (event.type)
                        {
                        case SDL_MOUSEMOTION:
                            break;
                        case SDL_MOUSEBUTTONDOWN:
                            if(event.button.button == SDL_BUTTON_LEFT)
                            {
                                total += price[i];
                                fcount[i] += 1;
                            }
                            else if(event.button.button == SDL_BUTTON_RIGHT)
                            {
                                if(fcount[i]>0)
                                {
                                    total -= price[i] ;
                                    fcount[i] -= 1;
                                }
                            }
                            break;
                        case SDL_MOUSEBUTTONUP:

                            break;
                        }
                        break;
                    case 8:
                        switch (event.type)
                        {
                        case SDL_MOUSEMOTION:
                            break;
                        case SDL_MOUSEBUTTONDOWN:
                            if(event.button.button == SDL_BUTTON_LEFT)
                            {
                                total += price[i];
                                fcount[i] += 1;
                            }
                            else if(event.button.button == SDL_BUTTON_RIGHT)
                            {
                                if(fcount[i]>0)
                                {
                                    total -= price[i] ;
                                    fcount[i] -= 1;
                                }
                            }
                            break;
                        case SDL_MOUSEBUTTONUP:

                            break;
                        }
                        break;
                    case 9:
                        switch (event.type)
                        {
                        case SDL_MOUSEMOTION:
                            break;
                        case SDL_MOUSEBUTTONDOWN:
                            if(event.button.button == SDL_BUTTON_LEFT)
                            {
                                total += price[i];
                                fcount[i] += 1;
                            }
                            else if(event.button.button == SDL_BUTTON_RIGHT)
                            {
                                if(fcount[i]>0)
                                {
                                    total -= price[i] ;
                                    fcount[i] -= 1;
                                }
                            }
                            break;
                        case SDL_MOUSEBUTTONUP:

                            break;
                        }
                        break;

                     default:
                        break;
                }
                }
                else if(choice == 0)
                {
                    switch (i){
                    case 10:
                        switch (event.type)
                        {
                        case SDL_MOUSEMOTION:
                            break;
                        case SDL_MOUSEBUTTONDOWN:
                            if(event.button.button == SDL_BUTTON_LEFT)
                            {
                                total += price[i];
                                fcount[i] += 1;
                                cout << i << "  : " << fcount[i] << endl;
                            }
                            else if(event.button.button == SDL_BUTTON_RIGHT)
                            {
                                if(fcount[i]>0)
                                {
                                    total -= price[i] ;
                                    fcount[i] -= 1;
                                }
                            }
                            break;
                        case SDL_MOUSEBUTTONUP:

                            break;
                        }
                        break;
                        case 11:
                        switch (event.type)
                        {
                        case SDL_MOUSEMOTION:
                            break;
                        case SDL_MOUSEBUTTONDOWN:
                            if(event.button.button == SDL_BUTTON_LEFT)
                            {
                                total += price[i];
                                fcount[i] += 1;
                                cout << i << "  : " << fcount[i] << endl;
                            }
                            else if(event.button.button == SDL_BUTTON_RIGHT)
                            {
                                if(fcount[i]>0)
                                {
                                    total -= price[i] ;
                                    fcount[i] -= 1;
                                }
                            }
                            break;
                        case SDL_MOUSEBUTTONUP:

                            break;
                        }
                        break;
                        case 12 :
                        switch (event.type)
                        {
                        case SDL_MOUSEMOTION:
                            break;
                        case SDL_MOUSEBUTTONDOWN:
                            if(event.button.button == SDL_BUTTON_LEFT)
                            {
                                total += price[i];
                                fcount[i] += 1;
                                cout << i << "  : " << fcount[i] << endl;
                            }
                            else if(event.button.button == SDL_BUTTON_RIGHT)
                            {
                                if(fcount[i]>0)
                                {
                                    total -= price[i] ;
                                    fcount[i] -= 1;
                                }
                            }
                            break;
                        case SDL_MOUSEBUTTONUP:

                            break;
                        }
                        break;
                        case 13:
                        switch (event.type)
                        {
                        case SDL_MOUSEMOTION:
                            break;
                        case SDL_MOUSEBUTTONDOWN:
                            if(event.button.button == SDL_BUTTON_LEFT)
                            {
                                total += price[i];
                                fcount[i] += 1;
                            }
                            else if(event.button.button == SDL_BUTTON_RIGHT)
                            {
                                if(fcount[i]>0)
                                {
                                    total -= price[i] ;
                                    fcount[i] -= 1;
                                }
                            }
                            break;
                        case SDL_MOUSEBUTTONUP:

                            break;
                        }
                        break;
                        case 14:
                        switch (event.type)
                        {
                        case SDL_MOUSEMOTION:
                            break;
                        case SDL_MOUSEBUTTONDOWN:
                            if(event.button.button == SDL_BUTTON_LEFT)
                            {
                                total += price[i];
                                fcount[i] += 1;
                            }
                            else if(event.button.button == SDL_BUTTON_RIGHT)
                            {
                                if(fcount[i]>0)
                                {
                                    total -= price[i] ;
                                    fcount[i] -= 1;
                                }
                            }
                            break;
                        case SDL_MOUSEBUTTONUP:

                            break;
                        }
                        break;
                        case 15:
                        switch (event.type)
                        {
                        case SDL_MOUSEMOTION:
                            break;
                        case SDL_MOUSEBUTTONDOWN:
                            if(event.button.button == SDL_BUTTON_LEFT)
                            {
                                total += price[i];
                                fcount[i] += 1;
                            }
                            else if(event.button.button == SDL_BUTTON_RIGHT)
                            {
                                if(fcount[i]>0)
                                {
                                    total -= price[i] ;
                                    fcount[i] -= 1;
                                }
                            }
                            break;
                        case SDL_MOUSEBUTTONUP:

                            break;
                        }
                        break;
                        case 16:
                        switch (event.type)
                        {
                        case SDL_MOUSEMOTION:
                            break;
                        case SDL_MOUSEBUTTONDOWN:
                            if(event.button.button == SDL_BUTTON_LEFT)
                            {
                                total += price[i];
                                fcount[i] += 1;
                            }
                            else if(event.button.button == SDL_BUTTON_RIGHT)
                            {
                                if(fcount[i]>0)
                                {
                                    total -= price[i] ;
                                    fcount[i] -= 1;
                                }
                            }
                            break;
                        case SDL_MOUSEBUTTONUP:

                            break;
                        }
                        break;
                        case 17:
                        switch (event.type)
                        {
                        case SDL_MOUSEMOTION:
                            break;
                        case SDL_MOUSEBUTTONDOWN:
                            if(event.button.button == SDL_BUTTON_LEFT)
                            {
                                total += price[i];
                                fcount[i] += 1;
                            }
                            else if(event.button.button == SDL_BUTTON_RIGHT)
                            {
                                if(fcount[i]>0)
                                {
                                    total -= price[i] ;
                                    fcount[i] -= 1;
                                }
                            }
                            break;
                        case SDL_MOUSEBUTTONUP:

                            break;
                        }
                        break;
                        case 18:
                        switch (event.type)
                        {
                        case SDL_MOUSEMOTION:
                            break;
                        case SDL_MOUSEBUTTONDOWN:
                            if(event.button.button == SDL_BUTTON_LEFT)
                            {
                                total += price[i];
                                fcount[i] += 1;
                            }
                            else if(event.button.button == SDL_BUTTON_RIGHT)
                            {
                                if(fcount[i]>0)
                                {
                                    total -= price[i] ;
                                    fcount[i] -= 1;
                                }
                            }
                            break;
                        case SDL_MOUSEBUTTONUP:

                            break;
                        }
                        break;
                        default:
                        break;
                }
                }
            }

}
}
void RenderWindow::handleChangeMenuEvent(SDL_Event event, int& choice, SDL_Rect rect, RenderWindow &window,SDL_Texture* square)
{
    if (event.type == SDL_MOUSEMOTION || event.type == SDL_MOUSEBUTTONDOWN || event.type == SDL_MOUSEBUTTONUP) {
		SDL_GetMouseState(&MouseX, &MouseY);
	}
	if (CheckInside(rect, MouseX, MouseY))
    {
        SDL_SetTextureColorMod(square, 255, 255, 0);
        switch (event.type)
        {
        case SDL_MOUSEMOTION:
            break;
        case SDL_MOUSEBUTTONDOWN:
            if(choice == 1) choice =0;
            else            choice =1;
            break;
        case SDL_MOUSEBUTTONUP:
            break;
        }
    }
    else
        {
            SDL_SetTextureColorMod(square, 255, 255, 255);
        }
}
void RenderWindow::handleBuyEvent(SDL_Event event, int& start, SDL_Rect rect, RenderWindow &window,SDL_Texture* square)
{
    if (event.type == SDL_MOUSEMOTION || event.type == SDL_MOUSEBUTTONDOWN || event.type == SDL_MOUSEBUTTONUP) {
		SDL_GetMouseState(&MouseX, &MouseY);
	}
	if (CheckInside(rect, MouseX, MouseY))
    {
        SDL_SetTextureColorMod(square, 255, 255, 0);
        switch (event.type)
        {
        case SDL_MOUSEMOTION:
            break;
        case SDL_MOUSEBUTTONDOWN:

            break;
        case SDL_MOUSEBUTTONUP:
            start = 5;
            break;
        }
    }
    else
        {
            SDL_SetTextureColorMod(square, 255, 255, 255);
        }
}
void RenderWindow::handleQuit(SDL_Event event, int& start, SDL_Rect rect, SDL_Window* window) {
	if (event.type == SDL_MOUSEBUTTONDOWN) {
		SDL_GetMouseState(&MouseX, &MouseY);
	}
	if (CheckInside(rect, MouseX, MouseY)) {
		if ( event.type == SDL_MOUSEBUTTONDOWN )
        {
            if(start != 5)   start = 0;
            else             {
                    start = 1;
            cout << 0;}
		}
	}
        }
void RenderWindow::handleFinish(SDL_Event event, bool& finish, SDL_Rect rect, SDL_Window* window) {
	if (event.type == SDL_MOUSEBUTTONDOWN) {
		SDL_GetMouseState(&MouseX, &MouseY);
	}
	if (CheckInside(rect, MouseX, MouseY)) {
		if ( event.type == SDL_MOUSEBUTTONDOWN )
        {
   {
            finish = true;
            cout << 0;}
		}
	}
        }
void RenderWindow::display()
{
	SDL_RenderPresent(renderer);
}

void RenderWindow::handleState(SDL_Event event, int& state, SDL_Rect rect, SDL_Window* window) {
	if (event.type == SDL_MOUSEBUTTONDOWN) {
		SDL_GetMouseState(&MouseX, &MouseY);
	}
	if (CheckInside(rect, MouseX, MouseY)) {
		if (event.type == SDL_MOUSEBUTTONUP) {
			if (state == 1) {
				state = 0;
			}
			else {
				state = 1;
			}
		}
	}
}
