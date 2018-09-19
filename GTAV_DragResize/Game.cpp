#include "stdafx.h"

static Game g_game;

bool Game::Initialize() {

    auto patternSearch = Utility::BytePattern( "40 38 35 ? ? ? ? 74 21 0F 10 05 ? ? ? ?", false );

    if ( patternSearch.size() <= 0 ) {

        return false;
    }

    auto address = ( uintptr_t )patternSearch.get().get();

    m_pShouldUpdateWindow = ( PBYTE )( *( int32_t* )( address + 3 ) + address + 7 );

    address += 9;

    m_pRenderInfo = ( CRenderSettingsInfo* )( *( int32_t* )( address + 3 ) + address + 7 );

    return true;
}

void Game::UpdateWindowRect( int width, int height ) {

    m_pRenderInfo->width = width;
    m_pRenderInfo->height = height;

    *m_pShouldUpdateWindow = 1;
}

Game * Game::Instance() {

    return &g_game;
}
