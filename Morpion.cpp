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

    // Container to store actors will need that later for the game
    std::vector<vtkSmartPointer<vtkActor>> actors;

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
    vtkNew<vtkNamedColors> colors;
    actors[3]->GetProperty()->SetColor(colors->GetColor3d("Red").GetData());

    // Disable interactor style interactions (no rotation, zoom, etc.)
    vtkSmartPointer<vtkInteractorStyle> style = vtkSmartPointer<vtkInteractorStyle>::New();
    renderWindowInteractor->SetInteractorStyle(style);

    // Render the scene
    renderWindow->Render();

    // Initialize and start the render window interactor
    renderWindowInteractor->Initialize();
    renderWindowInteractor->Start();

    return 0;
}
