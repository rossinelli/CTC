struct VTK;
struct VTKConf;

struct MeshRead;
struct Vectors;
struct Scalars;

void vtk_conf_ini(MeshRead*, /**/ VTKConf**);
void vtk_conf_fin(VTKConf*);

void vtk_conf_tri(VTKConf*, const char *keys);

void vtk_ini(int maxn, char const *path, VTKConf*, /**/ VTK**);
void vtk_points(VTK*, int nm, Vectors*);
void vtk_tri(VTK*, int nm, Scalars*, const char *keys);
void vtk_write(VTK*, MPI_Comm, int id);
void vtk_fin(VTK*);
