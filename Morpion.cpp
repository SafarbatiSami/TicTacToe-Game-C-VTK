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



// Container to store actors will need that later for the game
std::vector<vtkSmartPointer<vtkActor>> actors;
bool is_Red = false;
void is_Winner()
{
    if (actors[0]->GetProperty()->GetColor() == actors[1]->GetProperty()->GetColor() && actors[0]->GetProperty()->GetColor() == actors[2]->GetProperty()->GetColor())
    {
        cout << "winner winner chicken dinner ! ";
    }
}
void change_color(int i) 
{
    vtkActor* actor;
    vtkNew<vtkNamedColors> colors;
    
    if (is_Red)
    {
        actors[i]->GetProperty()->SetColor(colors->GetColor3d("Blue").GetData());
        cout << "this is " << actors[i]->GetProperty()->GetColor() << endl;
        is_Red = false;
    }
    else
    {
        actors[i]->GetProperty()->SetColor(colors->GetColor3d("Red").GetData());
        cout << "this is " << actors[i]->GetProperty()->GetColor() << endl;
        is_Red = true;
    }
    is_Winner();



}


void HandleKeyPress(vtkObject* caller, long unsigned int eventId, void* clientData, void* callData)
{
    vtkRenderWindowInteractor* interactor = static_cast<vtkRenderWindowInteractor*>(caller);
    std::string key = interactor->GetKeySym();

    if (key == "1") {
        //MovePawn(0, 1.25); // Déplace la dame vers le haut
        change_color(0);
    }
    else if (key == "4") {
        change_color(1);
       // MovePawn(0, -1.25); // Déplace la dame vers le bas
    }
    else if (key == "7") {
        change_color(2);
       // MovePawn(-1.25, 0); // Déplace la dame vers la gauche
    }
    else if (key == "2") {
        change_color(3);
        //MovePawn(1.25, 0); // Déplace la dame vers la droite
    }
    else if (key == "5") {
        change_color(4);
        // MovePawn(0, -1.25); // Déplace la dame vers le bas
    }
    else if (key == "8") {
        change_color(5);
        // MovePawn(-1.25, 0); // Déplace la dame vers la gauche
    }
    else if (key == "3") {
        change_color(6);
        //MovePawn(1.25, 0); // Déplace la dame vers la droite
    }
    else if (key == "6") {
        change_color(7);
        // MovePawn(-1.25, 0); // Déplace la dame vers la gauche
    }
    else if (key == "9") {
        change_color(8);
        //MovePawn(1.25, 0); // Déplace la dame vers la droite
    }

    interactor->GetRenderWindow()->Render();

}

int main() {
    // Create renderer
    vtkSmartPointer<vtkRenderer> renderer = vtkSmartPointer<vtkRenderer>::New();

    // Create render window
    vtkSmartPointer<vtkRenderWindow> renderWindow = vtkSmartPointer<vtkRenderWindow>::New();
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
    

    // for testing purposes
    for (vtkSmartPointer<vtkActor> i : actors)
        std::cout << i << ' '; // print all the actors
    std::cout << actors[0] << endl;
    // for test purposes color the square
    //vtkNew<vtkNamedColors> colors;
    //actors[3]->GetProperty()->SetColor(colors->GetColor3d("Red").GetData());

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
