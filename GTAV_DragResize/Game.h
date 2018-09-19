#pragma once
#include "Types.h"

class Game {
    PBYTE m_pShouldUpdateWindow;
    CRenderSettingsInfo * m_pRenderInfo;
  public:
    bool Initialize();
    void UpdateWindowRect( int width, int height );
    static Game * Instance();
};

