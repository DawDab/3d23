Wektor przed zmianą:
    std::vector<GLfloat> vertices = {
        // Roof
        -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
        0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
        0.0f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f,

        // House walls
        -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f,
        -0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f,
        0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f,
        -0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f,
        0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f,
        0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f
    };

54 zmienne typu GLfloat mającego rozmiar 4 bajty dają nam sumarycznie 216 bajtów

Wektor po zmianie:
    std::vector<GLfloat> vertices = {
        // Roof
        -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
        0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
        0.0f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f,

        // House walls
        -0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f,
        0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f,
    };
    
30 zmienne typu GLfloat mającego rozmiar 4 bajty dają nam sumarycznie 120 bajtów

Patrząc z perspektywy redukcji ilości samych wierzchołków zaoszczędziliśmy 96 bajtów. 

Jednak uwzględniając resztę programu w koszta należy jednak wliczyć nowy wektor z indeksami.
   
    std::vector<GLushort> indices = {
        0, 1, 2, 0, 3, 1, 3, 4, 1
    };
9 zmiennych tpyu GLushort mającego rozmiar 2 bajty daje nam sumarycznie 18 bajtów

Ilość zaoszczędonych bajtów: 78 bajtów
