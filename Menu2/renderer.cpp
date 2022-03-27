#include "includes.hpp"
#include "utils.hpp"

static ID3D11Device           * g_pd3dDevice           = nullptr;
static ID3D11DeviceContext    * g_pd3dDeviceContext    = nullptr;
static IDXGISwapChain         * g_pSwapChain           = nullptr;
static ID3D11RenderTargetView * g_mainRenderTargetView = nullptr;

bool CreateDeviceD3D( HWND );
void CleanupDeviceD3D( );
void CreateRenderTarget( );
void CleanupRenderTarget( );
LRESULT __stdcall WndProc( HWND, UINT , WPARAM, LPARAM );

int CurrentTab = 0;

void Colors()
{
    ImGuiStyle& style = ImGui::GetStyle();
    style.Colors[ImGuiCol_ChildBg] = ImColor(58, 58, 58);
    style.Colors[ImGuiCol_WindowBg] = ImColor(40, 145, 40);//40, 33, 57
    style.Colors[ImGuiCol_Border] = ImColor(40, 145, 40);
    style.Colors[ImGuiCol_ScrollbarGrab] = ImColor(40, 145, 40);
    style.ScrollbarRounding = 0;
    style.FramePadding = ImVec2(0, 0);
    style.ItemSpacing = ImVec2(0, 0);
    style.WindowPadding = ImVec2(0, 0);
    style.WindowMinSize = ImVec2(690, 660);
}
int StartRendering( ) 
{   
    const auto title = utils::random_string( );
    utils::spoof_exe( false );

    WNDCLASSEX wc = 
    { 
        sizeof( WNDCLASSEX ),
        CS_CLASSDC,
        WndProc, 
        0, 
        0, 
        0, 
        0, 
        0, 
        0, 
        0, 
        title.c_str(),
        0
    };

    RegisterClassExA( &wc );
    HWND hwnd = CreateWindowExA(0, wc.lpszClassName , title.c_str() , WS_SYSMENU , 100 , 100 , 1280 , 800 , 0 , 0 , wc.hInstance , 0 );

    if ( !CreateDeviceD3D( hwnd ) )
    {
        CleanupDeviceD3D( );
        UnregisterClassA( wc.lpszClassName , wc.hInstance );

        return 1;
    }

    ShowWindow( GetConsoleWindow( ) , SW_HIDE );
    ShowWindow( hwnd , SW_SHOWDEFAULT );
    UpdateWindow( hwnd );

    ImGui::CreateContext( );

    ImGuiIO& io = ImGui::GetIO( ); 

    io.IniFilename = nullptr;
    io.LogFilename = nullptr;

    io.WantSaveIniSettings = false;

    Colors();

    ImGui_ImplWin32_Init( hwnd );
    ImGui_ImplDX11_Init( g_pd3dDevice , g_pd3dDeviceContext );

    const auto clear_color = ImVec4( 0.45f , 0.55f , 0.60f , 1.00f );
    const float clear_color_with_alpha[4] = { clear_color.x * clear_color.w, clear_color.y * clear_color.w, clear_color.z * clear_color.w, clear_color.w };

    while ( true )
    {
        MSG msg;

        while ( PeekMessageA( &msg , NULL , 0U , 0U , PM_REMOVE ) )
        {
            TranslateMessage( &msg );
            DispatchMessageA( &msg );

            if ( msg.message == WM_QUIT )
                break;
        }

        ImGui_ImplDX11_NewFrame( );
        ImGui_ImplWin32_NewFrame( );
        ImGui::NewFrame( );

        ImGui::Begin("Toxic", nullptr, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoBackground | ImGuiWindowFlags_NoResize);
        {
            ImDrawList* draw = ImGui::GetWindowDrawList();
            ImVec2 pos = ImGui::GetWindowPos();
            draw->AddRectFilled(pos, ImVec2(pos.x + 600, pos.y + 50), ImColor(40, 145, 40));
            ImGui::SetCursorPos(ImVec2(0, 0));
            ImGui::BeginGroup();
            {
                if (ImGui::Tab("LegitBot", 0 == CurrentTab, 90))
                    CurrentTab = 0;
                ImGui::SameLine();
                if (ImGui::Tab("ESP", 1 == CurrentTab, 90))
                    CurrentTab = 1;
                ImGui::SameLine();
                if (ImGui::Tab("Visuals", 2 == CurrentTab, 90))
                    CurrentTab = 2;
                ImGui::SameLine();
                if (ImGui::Tab("Changer", 3 == CurrentTab, 90))
                    CurrentTab = 3;
                ImGui::SameLine();
                if (ImGui::Tab("Config", 4 == CurrentTab, 90))
                    CurrentTab = 4;
            }
            ImGui::EndGroup();
            ImGui::SetCursorPos(ImVec2(10, 50));
            ImGui::BeginChild("MainFrame", ImVec2(580, 375));
            {
                if (CurrentTab == 0)
                {

                }
                else if (CurrentTab == 1)
                {
                    ImGui::SetCursorPos(ImVec2(20, 20));
                    ImGui::BeginFeaturesChild("Players", false, ImVec2(260, 310));
                    {

                    }
                    ImGui::EndChild();
                    ImGui::SetCursorPos(ImVec2(20, 340));
                    ImGui::BeginFeaturesChild("Playerss", false, ImVec2(260, 310));
                    {

                    }
                    ImGui::EndChild();
                }
                else if (CurrentTab == 2)
                {

                }
                else if (CurrentTab == 3)
                {
                    ImGui::SetCursorPos(ImVec2(20, 20));
                    ImGui::BeginFeaturesChild("Preview", false, ImVec2(260, 160));
                    {

                    }
                    ImGui::EndChild();
                    ImGui::SetCursorPos(ImVec2(20, 190));
                    ImGui::BeginFeaturesChild("Models", false, ImVec2(260, 160));
                    {

                    }
                    ImGui::EndChild();
                    ImGui::SetCursorPos(ImVec2(300, 20));
                    ImGui::BeginFeaturesChild("Skins", false, ImVec2(260, 330));
                    {

                    }
                    ImGui::EndChild();
                }
                else if (CurrentTab == 4)
                {

                }
            }
            ImGui::EndChild();
            draw->AddRectFilled(ImVec2(pos.x + 10, pos.y + 425), ImVec2(pos.x + 590, pos.y + 450), ImColor(40, 145, 40));
            draw->AddText(ImVec2(pos.x + 20, pos.y + 430), ImColor(220, 220, 220), "Toxic Cheat DEV");
            draw->AddCircleFilled(ImVec2(pos.x + 570, pos.y + 25), 18, ImColor(220, 220, 220), 360);
            draw->AddText(ImVec2(pos.x + 547 - ImGui::CalcTextSize("Spook").x, pos.y + 20), ImColor(220, 220, 220), "Spook");
        }
        ImGui::End();

        ImGui::Render( );
       
        g_pd3dDeviceContext->OMSetRenderTargets( 1 , &g_mainRenderTargetView , NULL );
        g_pd3dDeviceContext->ClearRenderTargetView( g_mainRenderTargetView , clear_color_with_alpha );
       
        ImGui_ImplDX11_RenderDrawData( ImGui::GetDrawData( ) );

        g_pSwapChain->Present(0, 0); 
    }

    ImGui_ImplDX11_Shutdown( );
    ImGui_ImplWin32_Shutdown( );
    ImGui::DestroyContext( );

    CleanupDeviceD3D( );
    DestroyWindow( hwnd );
    UnregisterClassA( wc.lpszClassName , wc.hInstance );

    return 0;
}


bool CreateDeviceD3D( HWND hWnd )
{
    DXGI_SWAP_CHAIN_DESC sd;
    ZeroMemory( &sd , sizeof( sd ) );
    sd.BufferCount = 2;
    sd.BufferDesc.Width = 0;
    sd.BufferDesc.Height = 0;
    sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    sd.BufferDesc.RefreshRate.Numerator = 60;
    sd.BufferDesc.RefreshRate.Denominator = 1;
    sd.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;
    sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
    sd.OutputWindow = hWnd;
    sd.SampleDesc.Count = 1;
    sd.SampleDesc.Quality = 0;
    sd.Windowed = TRUE;
    sd.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;

    UINT createDeviceFlags = 0;

    D3D_FEATURE_LEVEL featureLevel;
    const D3D_FEATURE_LEVEL featureLevelArray[2] = { D3D_FEATURE_LEVEL_11_0, D3D_FEATURE_LEVEL_10_0, };

    if ( D3D11CreateDeviceAndSwapChain( NULL , D3D_DRIVER_TYPE_HARDWARE , NULL , createDeviceFlags , featureLevelArray , 2 , D3D11_SDK_VERSION , &sd , &g_pSwapChain , &g_pd3dDevice , &featureLevel , &g_pd3dDeviceContext ) != S_OK )
        return false;

    CreateRenderTarget( );
    return true;
}

void CleanupDeviceD3D( )
{
    CleanupRenderTarget( );
    if ( g_pSwapChain ) { g_pSwapChain->Release( ); g_pSwapChain = NULL; }
    if ( g_pd3dDeviceContext ) { g_pd3dDeviceContext->Release( ); g_pd3dDeviceContext = NULL; }
    if ( g_pd3dDevice ) { g_pd3dDevice->Release( ); g_pd3dDevice = NULL; }
}

void CreateRenderTarget( )
{
    ID3D11Texture2D* pBackBuffer;
    g_pSwapChain->GetBuffer( 0 , IID_PPV_ARGS( &pBackBuffer ) );
    g_pd3dDevice->CreateRenderTargetView( pBackBuffer , NULL , &g_mainRenderTargetView );
    pBackBuffer->Release( );
}

void CleanupRenderTarget( )
{
    if ( g_mainRenderTargetView ) { g_mainRenderTargetView->Release( ); g_mainRenderTargetView = NULL; }
}

extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler( HWND hWnd , UINT msg , WPARAM wParam , LPARAM lParam );

LRESULT WINAPI WndProc( HWND hWnd , UINT msg , WPARAM wParam , LPARAM lParam )
{
    if ( ImGui_ImplWin32_WndProcHandler( hWnd , msg , wParam , lParam ) )
        return true;

    switch ( msg )
    {
    case WM_SIZE:
        if ( g_pd3dDevice != NULL && wParam != SIZE_MINIMIZED )
        {
            CleanupRenderTarget( );
            g_pSwapChain->ResizeBuffers( 0 , (UINT)LOWORD( lParam ) , (UINT)HIWORD( lParam ) , DXGI_FORMAT_UNKNOWN , 0 );
            CreateRenderTarget( );
        }
        return 0;
    case WM_SYSCOMMAND:
        if ( ( wParam & 0xfff0 ) == SC_KEYMENU )
            return 0;
        break;
    case WM_DESTROY:
        PostQuitMessage( 0 );
        return 0;
    }
    return ::DefWindowProc( hWnd , msg , wParam , lParam );
}