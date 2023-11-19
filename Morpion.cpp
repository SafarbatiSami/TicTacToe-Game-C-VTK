#include <vtkSmartPointer.h>
#include <vtkCellArray.h>
#include <vtkPolyData.h>
#include <vtkPolyDataMapper.h>
#include <vtkActor.h>
#include <vtkRenderer.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkInteractorStyleTrackballCamera.h>
#include <format> 
#include <vtkNamedColors.h>
#include <vtkProperty.h>
#include <vtkCallbackCommand.h>
#include <vector>
#include <vtkTextActor.h>
#include <vtkTextProperty.h>


// ----------------------------------- SOME GLOBAL DECLARATIONS --------------------------------------------

// Container to store actors will need that later for the game
std::vector<vtkSmartPointer<vtkActor>> actors;
bool is_Red = false;
std::vector<std::string> actors_Colors(11);

// Initialize Scores 
int red_Score = 0;
int blue_Score = 0;

// Create text Actors for the scores
vtkSmartPointer<vtkTextActor> redScoreActor = vtkSmartPointer<vtkTextActor>::New();
vtkSmartPointer<vtkTextActor> blueScoreActor = vtkSmartPointer<vtkTextActor>::New();

// Create render window
vtkSmartPointer<vtkRenderWindow> renderWindow = vtkSmartPointer<vtkRenderWindow>::New();

// ---------------------------------------------------------------------------------------------------------


void restart_Game(std::string which_color_won)
{
    vtkNew<vtkNamedColors> colors;

    // Increment score for the winner 
    if (which_color_won == "Red")
    {
        red_Score += 1;
    }
    if (which_color_won == "Blue")
    {
        blue_Score += 1;
    }
    for (int i{}; i < actors.size() ; ++i) actors[i]->GetProperty()->SetColor(colors->GetColor3d("White").GetData());
    for (int i{}; i < actors_Colors.size(); ++i) actors_Colors[i] = "White";

    
    // Update the text for the RED PLAYER score
    std::string red_scoreString = "Red player score : " + std::to_string(red_Score);
    redScoreActor->SetInput(red_scoreString.c_str());

    // Update the text for the BLUE PLAYER score
    std::string blue_scoreString = "Blue player score : " + std::to_string(blue_Score);
    blueScoreActor->SetInput(blue_scoreString.c_str());
    cout << "New Game Started ! " << endl;
    // Trigger a render update
    renderWindow->Render();

}

void is_Winner()
{
    if (actors_Colors[0] == actors_Colors[1] && actors_Colors[0]== actors_Colors[2] && (actors_Colors[0] == "Red" || actors_Colors[0] == "Blue") )
    {
        cout << "winner winner chicken dinner ! "<<endl;
        cout << actors_Colors[1] << " PLAYER IS THE MVP !" << endl;
        restart_Game(actors_Colors[1]);
    }
    if (actors_Colors[3] == actors_Colors[4] && actors_Colors[3] == actors_Colors[5] && (actors_Colors[3] == "Red" || actors_Colors[3] == "Blue"))
    {
        cout << "winner winner chicken dinner ! " << endl;
        cout << actors_Colors[3] << " PLAYER IS THE MVP !" << endl;
        restart_Game(actors_Colors[3]);
    }
    if (actors_Colors[6] == actors_Colors[7] && actors_Colors[6] == actors_Colors[8] && (actors_Colors[6] == "Red" || actors_Colors[6] == "Blue"))
    {
        cout << "winner winner chicken dinner ! " << endl;
        cout << actors_Colors[6] << " PLAYER IS THE MVP !" << endl;
        restart_Game(actors_Colors[6]);
    }
    if (actors_Colors[0] == actors_Colors[3] && actors_Colors[0] == actors_Colors[6] && (actors_Colors[0] == "Red" || actors_Colors[0] == "Blue"))
    {
        cout << "winner winner chicken dinner ! " << endl;
        cout << actors_Colors[0] << " PLAYER IS THE MVP !" << endl;
        restart_Game(actors_Colors[0]);
    }
    if (actors_Colors[1] == actors_Colors[4] && actors_Colors[1] == actors_Colors[7] && (actors_Colors[1] == "Red" || actors_Colors[1] == "Blue"))
    {
        cout << "winner winner chicken dinner ! " << endl;
        cout << actors_Colors[1] << " PLAYER IS THE MVP !" << endl;
        restart_Game(actors_Colors[1]);
    }
    if (actors_Colors[2] == actors_Colors[5] && actors_Colors[2] == actors_Colors[8] && (actors_Colors[2] == "Red" || actors_Colors[2] == "Blue"))
    {
        cout << "winner winner chicken dinner ! " << endl;
        cout << actors_Colors[2] << " PLAYER IS THE MVP !" << endl;
        restart_Game(actors_Colors[2]);
    }
    if (actors_Colors[0] == actors_Colors[4] && actors_Colors[0] == actors_Colors[8] && (actors_Colors[0] == "Red" || actors_Colors[0] == "Blue"))
    {
        cout << "winner winner chicken dinner ! " << endl;
        cout << actors_Colors[0] << " PLAYER IS THE MVP !" << endl;
        restart_Game(actors_Colors[0]);
    }
    if (actors_Colors[2] == actors_Colors[4] && actors_Colors[2] == actors_Colors[6] && (actors_Colors[2] == "Red" || actors_Colors[2] == "Blue"))
    {
        cout << "winner winner chicken dinner ! " << endl;
        cout << actors_Colors[2] << " PLAYER IS THE MVP !" << endl;
        restart_Game(actors_Colors[2]);
    }
}

void change_color(int i) 
{
   // vtkActor* actor = nullptr;
    vtkNew<vtkNamedColors> colors;
    if (actors_Colors[i] != "Red" && actors_Colors[i] != "Blue")
    {
        if (is_Red)
    {
        // test for test 
        // test if colored in Red before painting
       
        actors[i]->GetProperty()->SetColor(colors->GetColor3d("Blue").GetData());
    
        actors_Colors.at(i) = "Blue";
        //cout << "this is " << actors_Colors[i] << endl;
        is_Red = false;
        
    }
    else
    {
        // test if colored in Blue before painting
        
        actors[i]->GetProperty()->SetColor(colors->GetColor3d("Red").GetData());
        
        actors_Colors.at(i) = "Red";
       // cout << "this is " << actors_Colors[i] << endl;
        is_Red = true;
        
    }
    }
   
    is_Winner();

}

void HandleKeyPress(vtkObject* caller, long unsigned int eventId, void* clientData, void* callData)
{
    vtkRenderWindowInteractor* interactor = static_cast<vtkRenderWindowInteractor*>(caller);
    std::string key = interactor->GetKeySym();

    if (key == "1") {
     
        change_color(0); // Change the color of the square
    }
    else if (key == "4") {
        change_color(1); // Change the color of the square 
       
    }
    else if (key == "7") {
        change_color(2); // Change the color of the square
       
    }
    else if (key == "2") {
        change_color(3); // Change the color of the square
       
    }
    else if (key == "5") {
        change_color(4); // Change the color of the square 
        
    }
    else if (key == "8") {
        change_color(5); // Change the color of the square
       
    }
    else if (key == "3") {
        change_color(6); // Change the color of the square
        
    }
    else if (key == "6") {
        change_color(7); // Change the color of the square
       
    }
    else if (key == "9") {
        change_color(8); // Change the color of the square
       
    }

    interactor->GetRenderWindow()->Render();

}

int main() {
    // Create renderer
    vtkSmartPointer<vtkRenderer> renderer = vtkSmartPointer<vtkRenderer>::New();

    renderWindow->AddRenderer(renderer);

    // Create render window interactor
    vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor =
        vtkSmartPointer<vtkRenderWindowInteractor>::New();
    renderWindowInteractor->SetRenderWindow(renderWindow);

    // Set up the render window and interactor
    renderWindow->SetSize(900, 900); // Taille de la fenetre 

    // taille des carrés
    double size = 0.1;

    // espace entre chaque carré
    double spacing = 0.01;
 

    // Loop to create a 3x3 grid of squares with size and spacing
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            // Create points for a square with size
            vtkSmartPointer<vtkPoints> points = vtkSmartPointer<vtkPoints>::New();
            points->InsertNextPoint(0, 0, 0);
            points->InsertNextPoint(size, 0, 0);
            points->InsertNextPoint(size, size, 0);
            points->InsertNextPoint(0, size, 0);

            // Create cells
            vtkSmartPointer<vtkCellArray> cells = vtkSmartPointer<vtkCellArray>::New();
            cells->InsertNextCell(4);
            cells->InsertCellPoint(0);
            cells->InsertCellPoint(1);
            cells->InsertCellPoint(2);
            cells->InsertCellPoint(3);

            // Create polydata
            vtkSmartPointer<vtkPolyData> polyData = vtkSmartPointer<vtkPolyData>::New();
            polyData->SetPoints(points);
            polyData->SetPolys(cells);

            // Create mapper
            vtkSmartPointer<vtkPolyDataMapper> mapper = vtkSmartPointer<vtkPolyDataMapper>::New();
            mapper->SetInputData(polyData);

            // Create actor
            vtkSmartPointer<vtkActor> actor = vtkSmartPointer<vtkActor>::New();
            actor->SetMapper(mapper);

            // Set the position of each actor to achieve spacing
            actor->SetPosition(i * (size + spacing), j * (size + spacing), 0);

            // Add actor to the container
            actors.push_back(actor);

            // Add actor to the renderer
            renderer->AddActor(actor);
        }
    }
    //
    

    // Welcome Message
    std::cout << " The Game Started ! Enjoy " << endl;
   
    // Create a text actor for the title 
    vtkSmartPointer<vtkTextActor> TitleActor = vtkSmartPointer<vtkTextActor>::New();
    vtkSmartPointer<vtkTextProperty> textTitleProperty = TitleActor->GetTextProperty();
    TitleActor->SetTextScaleModeToNone(); // Disable text scaling

    TitleActor->SetPosition(175, 800); // Set the position of the text
    textTitleProperty->SetFontSize(24);
    // Set the text
    TitleActor->SetInput(" Welcome to TicTacToe Game, Made by Sam :)");
    renderer->AddActor(TitleActor);

    // Create a text actor for the RED PLAYER score

    vtkSmartPointer<vtkTextProperty> redScoretextProperty = redScoreActor->GetTextProperty();
    redScoreActor->SetTextScaleModeToNone(); // Disable text scaling

    redScoreActor->SetPosition(50, 750); // Set the position of the text
    redScoretextProperty->SetFontSize(24);
    redScoretextProperty->SetColor(1.0, 0.0, 0.0); // White text color

    // Set the text
    std::string red_scoreString = "Red player score : " + std::to_string(blue_Score);
    redScoreActor->SetInput(red_scoreString.c_str());
    renderer->AddActor(redScoreActor);

    // Create a text actor for the BLUE PLAYER score 
   
    vtkSmartPointer<vtkTextProperty> blueScoretextProperty = blueScoreActor->GetTextProperty();
    blueScoreActor->SetTextScaleModeToNone(); // Disable text scaling

    blueScoreActor->SetPosition(600, 750); // Set the position of the text
    blueScoretextProperty->SetFontSize(24);
    blueScoretextProperty->SetColor(0.0, 0.0, 1.0); // White text color
    // Set the text
    //blueScoreActor->SetInput("Blue player score : ");
    std::string blue_scoreString = "Blue player score : " + std::to_string(blue_Score);
    blueScoreActor->SetInput(blue_scoreString.c_str());
    renderer->AddActor(blueScoreActor);

    // Disable interactor style interactions (no rotation, zoom, etc.)
    vtkSmartPointer<vtkInteractorStyle> style = vtkSmartPointer<vtkInteractorStyle>::New();
    renderWindowInteractor->SetInteractorStyle(style);


    // Utilise vtkCallbackCommand pour gérer les événements clavier
    vtkSmartPointer<vtkCallbackCommand> keyPressCallback = vtkSmartPointer<vtkCallbackCommand>::New();
    keyPressCallback->SetCallback(HandleKeyPress);

    renderWindowInteractor->AddObserver(vtkCommand::KeyPressEvent, keyPressCallback);


    // Render the scene
    renderWindow->Render();

    // Initialize and start the render window interactor
    renderWindowInteractor->Initialize();
    renderWindowInteractor->Start();

    return 0;
}
