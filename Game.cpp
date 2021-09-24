#include"Game.h"
#include"SDL_image.h"
#include<iostream>

SDL_Window* m_pWindow = 0;
SDL_Renderer* m_pRenderer = 0;
bool m_bRunning = false;

bool Game::init(const char *title, int xpos, int ypos, int width, int height, int flags) //초기값
{
  if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
  {
    m_pWindow = SDL_CreateWindow(title, xpos, ypos, width, height, flags);
    if (m_pWindow !=0)
    {
      m_pRenderer = SDL_CreateRenderer(m_pWindow, -1, 0);
      if (m_pRenderer !=0)
      {
        
        SDL_SetRenderDrawColor(m_pRenderer, 255, 255, 255, 255);

        SDL_Surface* pTempSurface = IMG_Load("Assets/abc12.png");
        m_pTexture = SDL_CreateTextureFromSurface(m_pRenderer, pTempSurface);
        SDL_FreeSurface(pTempSurface);
        
        SDL_QueryTexture(m_pTexture, NULL, NULL, &m_sourceRectangle.w, &m_sourceRectangle.h);

        m_destinationRectangle.w = width;
        m_destinationRectangle.h = height; // = 는 대입

        m_destinationRectangle.x = 0; 
        m_destinationRectangle.y = 0;
        m_sourceRectangle.x = 0;
        m_sourceRectangle.y = 0;
       
        std::cout<< "check"<<std::endl;

      } 
      else // SDL_CreateRenderer  가 정상적으로 작동 x
      {
        return false;
      }
    } 
    else // SDL_CreateWindow 가 정상적으로 작동 x
    {
      return false;
    }
  } 
  else // SDL_ Init 이 정상적으로 작동 x = 정의 확인
  {
    return false;
  }

  m_bRunning = true;
  return true;

}

void Game::update()
{


}

void Game::render()
{
  
  SDL_RenderClear(m_pRenderer);
  SDL_RenderCopy(m_pRenderer, m_pTexture, &m_sourceRectangle, &m_destinationRectangle);
  SDL_RenderPresent(m_pRenderer);
  
}

bool Game::running()
{
 return m_bRunning;
}

void Game::handleEvents()
{
  SDL_Event event;
  if(SDL_PollEvent(&event))
  {
    switch (event.type)
    {
      case SDL_QUIT:
      m_bRunning = false;
      break;
      default:
      break;
    }
  }
}

void Game::clean()
{
  SDL_DestroyWindow(m_pWindow);
  SDL_DestroyRenderer(m_pRenderer);
  SDL_Quit();
}