/*
2023-06-22
https://github.com/HaydenD100
Simple Demo using SDL2 and SDL mixer too create blocks that move with diffrent speeds and make a sound when the block touches the sides of the screen.
This is my first SDL2 project and this project was used too get a basic grasp on the concepts 
*/


#include <iostream>
#include <SDL_mixer.h>
#include <SDL.h>


//Rectanlge class which holds all the data for the rectangles that move on the screen
class Rectangle {
public:
    Rectangle(float xvelocity, int y, SDL_Color Colour, Mix_Chunk* Audio) {
        x = 0;
        rect = { (int)x,y,75,75 };
        xVeloctiy = xvelocity;
        colour = Colour;
        audio = Audio;
    }

    //audio that plays when the rectangle hits the side
    Mix_Chunk* audio;
    //SDL rectangle data structure 
    SDL_Rect rect;

    //SDL draw rect only takes int so this float is used so the x postion of the rectangle can increase 
    float x;
    //X velocity
    float xVeloctiy;
    //direction of the rectangle either 1 for right and -1 for left
    int direction = 1;
    //colour of the Rectangle
    SDL_Color colour;

    //called in the main method
    void Draw(SDL_Renderer* renderer) {
        //checks if the rectangle is touching the edges and changes direction and plays sound if so
        if (x <= 0)
        {
            direction = 1;
            Mix_PlayChannel(-1, audio, 0);
        }
        if (x + 75 >= 800)
        {
            direction = -1;
            Mix_PlayChannel(-1, audio, 0);
        }
        //adds velocity and direction
        x += xVeloctiy * direction;
        //updates rec pos
        rect.x = x;

        //sets colour for drawing rectangle
        SDL_SetRenderDrawColor(renderer, colour.r, colour.b, colour.g, colour.a);
        //draws rectangle
        SDL_RenderFillRect(renderer, &rect);

    }



};
//screen height and width
const int WIDTH = 800, HEIGHT = 600;


int main(int argc, char* argv[]) {

    
    //initialize SDL and SDL mixer
    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_Init(SDL_INIT_AUDIO);

    //the audio for all the rectangles from 1-5
    Mix_Chunk* one = NULL;
    Mix_Chunk *two = NULL;
    Mix_Chunk *three = NULL;
    Mix_Chunk *four = NULL;
    Mix_Chunk *five = NULL;

    //creates the window and gives it the name Note Blocks
    SDL_Window* window = SDL_CreateWindow("Note Block", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WIDTH, HEIGHT, SDL_WINDOW_ALLOW_HIGHDPI);

    //initialize the default audio device with the standard frequncy 44100
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
    {
        //error message
        printf("SDL_mixer could not initialize");
        
    }

    //loads all the notes wav files
    one = Mix_LoadWAV("1.wav");
    two = Mix_LoadWAV("2.wav");
    three = Mix_LoadWAV("3.wav");
    four = Mix_LoadWAV("4.wav");
    five = Mix_LoadWAV("5.wav");

    

    SDL_Event windowEvent;
    //creates renderer
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    
    //creates all the rectangles with diffrent pos and colour and assigns the note audio too each one
    Rectangle rectangleBlue = Rectangle(1.25f, 0, { 0,0,255,255 },one);
    Rectangle rectangleGreen = Rectangle(1.0f, 100, { 0,255,0,255 },two);
    Rectangle rectangleRed = Rectangle(0.75f, 200, { 255,0,0,255 },three);
    Rectangle rectangleYellow = Rectangle(0.5f, 300, { 0,255,255,255 }, four);
    Rectangle rectanglePurple = Rectangle(0.25f, 400, { 255,255,0,255 }, five);
    

    //while loop for the drawing
    while (true) {

        if (SDL_PollEvent(&windowEvent)) {
            if (SDL_QUIT == windowEvent.type) break;
        }

        

        //Clear screen set to white
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        //clears render of any previous drawings
        SDL_RenderClear(renderer);

        //Draws rectangles and updates pos
        rectangleBlue.Draw(renderer);
        rectangleRed.Draw(renderer);
        rectangleGreen.Draw(renderer);
        rectangleYellow.Draw(renderer);
        rectanglePurple.Draw(renderer);




        //updates screen
        SDL_RenderPresent(renderer);


    }

    //destorys render and window when exiting
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return EXIT_SUCCESS;
}

