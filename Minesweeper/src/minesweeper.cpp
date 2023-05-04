#include "minesweeper.hpp"

#include <renderer.hpp>
#include <color.hpp>
#include <draw.hpp>
#include <constants.hpp>
#include <iostream>
#include <input.hpp>


Minesweeper::Minesweeper()
    : Game("Minesweeper")
{
    mountain::Renderer::ClearColor = mountain::Colorf(0, 0, 0, 1);
    board.size = Const::defaultBoardSize;
    board.tiles.resize(Const::defaultBoardSize.y, std::vector<Tile>(Const::defaultBoardSize.x, {false, 0, false, false}));
    Tile fake = {false, 0, false, false};
    for (int x = 0; x < Const::defaultBoardSize.x; x++)
        for (int y = 0; y < Const::defaultBoardSize.y; y++)
            board.tiles[x][y] = fake;
    InitBoard();
    mountain::Input::Initialize();
}

void Minesweeper::Update()
{
    srand(time(0));
    dl = ImGui::GetBackgroundDrawList();
    Draw();
    GameDiscover();
    GameFlag();
    timerBetweenFlagging += DeltaTime;
}

void Minesweeper::Render()
{
}

void Minesweeper::Initialize()
{
    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard; // Enable Keyboard Controls
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;     // Enable Docking

    ImGui::StyleColorsDark();
    ImGui_ImplGlfw_InitForOpenGL(mountain::Renderer::GetWindow(), true);
    ImGui_ImplOpenGL3_Init(mountain::Renderer::GetOpenGLVersion().glsl);
}

void Minesweeper::PreRender()
{
    // Start the Dear ImGui frame
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
}

void Minesweeper::PostRender()
{
    // End ImGui frame
    ImGui::Render();
    int display_w, display_h;
    glfwGetFramebufferSize(mountain::Renderer::GetWindow(), &display_w, &display_h);

    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

    GLFWwindow* backup_current_context = glfwGetCurrentContext();
    ImGui::UpdatePlatformWindows();
    ImGui::RenderPlatformWindowsDefault();
    glfwMakeContextCurrent(backup_current_context);
}

void Minesweeper::Shutdown()
{
    // Cleanup
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
}

bool Minesweeper::isPositionValid(int x, int y)
{
    bool notNegative = x >= 0 && y >= 0;
    bool notOverflow = x < board.size.x && y < board.size.y;
    return notNegative && notOverflow;
}
bool Minesweeper::isPositionValid(Vector2 pos)
{
    bool notNegative = pos.x >= 0 && pos.y >= 0;
    bool notOverflow = pos.x < board.size.x && pos.y < board.size.y;
    return notNegative && notOverflow;
}

int Minesweeper::checkAround(int x, int y, Vector2 size)
{
    int sum = 0;
    for (int dx = -1; dx < 2; dx++)
        for (int dy = -1; dy < 2; dy++)
            if (isPositionValid(x+dx,y+dy) && board.tiles[x+dx][y+dy].isMine)
                sum++;
    

    return sum;
}

void Minesweeper::InitBoard()
{
    //Chooses a random tile to be mine
    for (int i = 0; i < Const::defaultMinesNumber; i++)
        board.tiles[rand() % (int)(board.size.x)][rand() % (int)(board.size.y)].isMine = true;
    
    //Calculates numbers for each tile
    for (int x = 0; x < board.size.x; x++)
    {
        for (int y = 0; y < board.size.y; y++)
        {
            if (!board.tiles[x][y].isMine)
            {
                board.tiles[x][y].value = checkAround(x, y, board.size);
            }
        }
    }
}
