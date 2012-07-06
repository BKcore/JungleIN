#include <QDebug>

#include "ground.h"
#include <cmath>

//const used to define the ground's coordinates
const float Ground::MAP_SIZE = 900.0;
float Ground::MAP_MIN = -120.0;
float Ground::MAP_MAX = 120.0;
const float Ground::MAX_HEIGHT = 10.0;

Ground::Ground(QString path, MaterialGround *mat) : Mesh(NULL,NULL)
{
    this->path = new Path("resources/path/path.png");

    //temporary array initialized here, and then given to a Geometry
    float* verticesTab;
    int* indicesTab;
    float * normalsF;
    //used as array indice
    int i = 0;

    //load the heightmap picture
    QImage img = QImage(path);
    //init the size of the loaded picture
    this->numberVerticesX = img.width();
    this->numberVerticesZ = img.height();

    //init the array's sizes
    verticesTab = new float[this->numberVerticesX * this->numberVerticesZ * 3];
    //6 indices for each quad (made with 2 triangles)
    indicesTab = new int[(this->numberVerticesX-1) * (this->numberVerticesZ-1) * 6];
    //2 normals for each quad (made with 2 triangles)
    normals = new Vector3[(this->numberVerticesX-1) * (this->numberVerticesZ-1) * 2];
    //there is 3 coordinates for each normal
    normalsF = new float[(this->numberVerticesX-1) * (this->numberVerticesZ-1) * 6];

    double poolEffect = 0.0;
    double poolIntensity = 20.0;
    double centerx = this->numberVerticesX/2.0;
    double centery = this->numberVerticesZ/2.0;
    double curx, cury;
    double maxlen = std::sqrt(centerx*centerx+centery*centery);

    //get all the vertices from the picture
    //white is the hightest, black is the lowest
    for(int z = 0 ; z < this->numberVerticesZ ; ++z){
        for(int x = 0 ; x < this->numberVerticesX ; ++x){
            curx = x-centerx;
            cury = z-centery;
            poolEffect = (std::sqrt(curx*curx+cury*cury)/maxlen)*poolIntensity;

            //get the color of the pixel
            QRgb color = img.pixel(x,z);
            //the (0,0,0) point is at the center of the map
            verticesTab[i] = (MAP_SIZE * x / (numberVerticesX - 1)) - MAP_SIZE / 2;
            verticesTab[i + 1] = MAX_HEIGHT * poolEffect * qGray(color) / 255;
            verticesTab[i + 2] = (MAP_SIZE * z / (numberVerticesZ - 1)) - MAP_SIZE / 2;

            i+=3;
        }
    }

    i = 0;
    int j = 0;
    //initialize the array of indices
    for(int z = 0 ; z < this->numberVerticesZ - 1 ; ++z){
        for(int x = 0 ; x < this->numberVerticesX - 1 ; ++x){
            int indiceHoriz = x + z * this->numberVerticesX;
            int indiceVer = x + (z + 1) * this->numberVerticesX;
            //construct an indices array of squares, based on 2 triangles
            //first triangle
            indicesTab[i] = indiceHoriz;
            indicesTab[i + 1] = indiceVer;
            indicesTab[i + 2] = indiceHoriz + 1;

            //second triangle
            indicesTab[i + 3] = indiceHoriz + 1;
            indicesTab[i + 4] = indiceVer;
            indicesTab[i + 5] = indiceVer + 1;

            Vector3 u;
            Vector3 v;
            Vector3 temp;
            //make the match between the indices and the vertices' coordinates
            indiceHoriz *= 3;
            indiceVer *= 3;
            //first triangle
            //initialize u vector
            u.set(verticesTab[indiceVer] - verticesTab[indiceHoriz],
                  verticesTab[indiceVer + 1] - verticesTab[indiceHoriz + 1],
                  verticesTab[indiceVer + 2] - verticesTab[indiceHoriz + 2]);
            u = u.normalize();
            //initialize v vector
            v.set(verticesTab[indiceHoriz + 3] - verticesTab[indiceHoriz],
                  verticesTab[indiceHoriz + 4] - verticesTab[indiceHoriz + 1],
                  verticesTab[indiceHoriz + 5] - verticesTab[indiceHoriz + 2]);
            v = v.normalize();

            //set the normal in the normals array
            normals[j] = normals[j].copy(temp.cross(u,v));

            //second triangle
            //initialize u vector
            u.set(verticesTab[indiceHoriz + 3] - verticesTab[indiceVer + 3],
                  verticesTab[indiceHoriz + 4] - verticesTab[indiceVer + 4],
                  verticesTab[indiceHoriz + 5] - verticesTab[indiceVer + 5]);
            u = u.normalize();

            //initialize v vector
            v.set(verticesTab[indiceVer] - verticesTab[indiceVer + 3],
                  verticesTab[indiceVer + 1] - verticesTab[indiceVer + 4],
                  verticesTab[indiceVer + 2] - verticesTab[indiceVer + 5]);
            v = v.normalize();

            //set the normal in the normals array
            normals[j+1] = normals[j+1].copy(temp.cross(u,v));
            i += 6;
            j+=2;
        }
    }

    //compute the normals of the first line of vertices
    firstLineNormals(normalsF);
    //compute the normals of all the lines of vertices except for the first and the last lines
    middleGridNormals(normalsF);
    //compute the normals of the last line of vertices
    lastLineNormals(normalsF);

    //set the arrays in the Geometry
    this->geometry = new Geometry(verticesTab,
                                  indicesTab,
                                  this->numberVerticesX*this->numberVerticesZ*3,
                                  (this->numberVerticesX-1) * (this->numberVerticesZ-1) * 6);

    this->geometry->setNormals(normalsF);
    mat->setHeightRange(MAX_HEIGHT);
    this->material = mat;

    //release the memory master please!
    delete normalsF;
    delete verticesTab;
    delete indicesTab;
}

//put the values of the normal vector into the i, i+1, i+2 th positions of the floats array
void Ground::setVectorToFloat(Vector3 normals, float * normalsF, int i){
    //print all the normals
    //qDebug() << "indice : " <<i<<normals.toString();
    normalsF[i] = normals.x;
    normalsF[i + 1] = normals.y;
    normalsF[i + 2] = normals.z;
}

//compute the normals of the first line of vertices
void Ground::firstLineNormals(float *normalsF){
    int i, j;
    Vector3 tmp = normals[0];
    //normal of the first vertex
    setVectorToFloat(tmp, normalsF, 0);

    //normal of the first line exept the last vertice
    for(i = 3, j = 0; i < (this->numberVerticesX - 1)*3; i+=3, j+=2){
        tmp=(normals[j] + normals[j + 1] + normals[j + 2]);
        tmp.divideScalar(3);
        setVectorToFloat(tmp, normalsF, i);
    }

    //normal of the last vertice of the first line
    tmp = (normals[j] + normals[j + 1]);
    tmp.divideScalar(2);
    setVectorToFloat(tmp, normalsF, i);
}

//compute the normals of all the lines of vertices except for the first and the last
void Ground::middleGridNormals(float *normalsF){
    int k = (this->numberVerticesX - 1) * 2;
    Vector3 tmp;
    for (int l = 1 ; l < this->numberVerticesZ - 1 ; ++l){
        //first vertex of the line
        firstVertexNormal(normalsF, l);
        //all verices except the last
        for (int j = 1 ; j < k - 1 ; j += 2){
            int position = l * k + j;
            tmp = (normals[position - k] + normals[position - k + 1] + normals[position - k + 2] +
                   normals[position - 1] + normals[position] + normals[position + 1]
                   );
            tmp.divideScalar(6);
            setVectorToFloat(tmp, normalsF,(this->numberVerticesX * l + ((j+1)/2))* 3);
        }
        //last vertex of the line
        int t = l * k - 1;
        tmp = (normals[t] + normals[t + k - 1] + normals[t + k]);
        tmp.divideScalar(3);
        setVectorToFloat(tmp, normalsF, (this->numberVerticesX * (l + 1) - 1) * 3);
    }
}

//compute the normals of the last line of vertices
void Ground::lastLineNormals(float *normalsF){
    //indice of the first vertex of the last line
    int indice = this->numberVerticesX * (this->numberVerticesZ - 1);
    int l = this->numberVerticesZ - 2;
    int k = (this->numberVerticesX - 1) * 2;
    Vector3 tmp;

    //first vertex normal
    tmp = (normals[indice + 1] + normals[indice + 2]);
    tmp.divideScalar(2);
    setVectorToFloat(tmp, normalsF, indice * 3);
    //all vertices except the last
    for (int i = 1, j = 0 ; i < this->numberVerticesX - 1; ++i, j +=2){
        int indTmp = l * k + j;
        tmp = (normals[indTmp + 1] + normals[indTmp + 2] + normals[indTmp + 3]);
        tmp.divideScalar(3);
        setVectorToFloat(tmp, normalsF, (indice + i) * 3);
    }
    //last vertex of the last line. So, it's the last vertex of ALL the ground. Yeah!
    setVectorToFloat(normals[(this->numberVerticesX-1) * (this->numberVerticesZ-1) - 1],
                     normalsF,
                     (this->numberVerticesX * this->numberVerticesZ - 1) * 3);
}

//compute the normal of the first vertex of the line (doesn't work for the first ans the last line)
void Ground::firstVertexNormal(float *normalsF, int lineNumber){
    Vector3 tmp;
    int k = (this->numberVerticesX - 1) * 2;
    tmp = (normals[lineNumber * k - k] + normals[lineNumber * k - k + 1] + normals[lineNumber * k]);
    tmp.divideScalar(3);
    setVectorToFloat(tmp, normalsF, this->numberVerticesX * lineNumber * 3);
}

//return the y value depenting of the x and z values
float Ground::getY(float px, float pz){
    //check if the camera inside the ground square
    if(px < MAP_SIZE / 2 && px > -MAP_SIZE / 2 && pz < MAP_SIZE / 2 && pz > -MAP_SIZE / 2){
        int indx;
        int indz;
        Vector3 p,n;

        //compute the nearest known vertex
        indx = trunc((px + MAP_SIZE/2)*(this->numberVerticesX -1)/MAP_SIZE);
        indz = trunc((pz + MAP_SIZE/2)*(this->numberVerticesX -1)/MAP_SIZE);

        //point of the plane use to compute the constant value
        p.set(this->geometry->getVertices()[(indx + indz * this->numberVerticesX) * 3],
              this->geometry->getVertices()[(indx + indz * this->numberVerticesX) * 3 + 1],
              this->geometry->getVertices()[(indx + indz * this->numberVerticesX) * 3 + 2]);

        //get the normal of the current plane to construct the plane equation
        n = this->normals[(this->numberVerticesX - 1) * 2 * indz + indx * 2];
        //constant of the plane equation
        double d = -(p.x * n.x + p.y * n.y + p.z * n.z);
        //compute and return the interpolation
//        qDebug() << -(d + n.z * pz + n.x * px)/n.y;
        return -(d + n.z * pz + n.x * px)/n.y;
    }
    //default result returned if the camera is not above the ground
    return MAX_HEIGHT/2;
}

//compute the approximative value of y, based on the four planes around and the previous Y coordinate
float Ground::getYApprox(float x, float z, float prevY)
{
    return (prevY + (getY(x,z)
            + getY(x + MAP_SIZE / (this->numberVerticesX -1),z)
            + getY(x - MAP_SIZE / (this->numberVerticesX - 1),z)
            + getY(x ,z+ MAP_SIZE / (this->numberVerticesZ - 1))
            + getY(x ,z - MAP_SIZE / (this->numberVerticesZ - 1))) / 5) / 2;
}

Vector3 Ground::randomMapPos(double height, bool isRock)
{
    double x = 0;
    double z = 0;
    int samples = 20;

    do
    {
        x = Utils::random(MAP_MIN, MAP_MAX);
        z = Utils::random(MAP_MIN, MAP_MAX);
    } while ((!this->path->validate(x,z) || (!isRock && this->containInBoundingBox(x,z))) && samples-- > 0);

    if (isRock)
        rockPos.append(new Vector3(x,0,z));

    double y = getY(x, z) + height;
    return Vector3(x, y, z);
}

bool Ground::containInBoundingBox(double x, double z)
{

    foreach (Vector3* rock, this->rockPos) {
        if ((rock->x - x)*(rock->x - x) + (rock->z - z)*(rock->z - z) < 40) {
            return true;
        }
    }

    return false;
}

QList<Vector3 *> Ground::getRockPos()
{
    return this->rockPos;
}

void Ground::removeRockPos()
{
    foreach (Vector3* v, rockPos)
        delete v;
    rockPos.clear();
}

Ground::~Ground(){
    delete this->normals;
}
