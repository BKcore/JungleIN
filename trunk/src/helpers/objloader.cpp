#include "objloader.h"

#include <QDebug>

#include "../materials/materialbasic.h"

//http://www.limegarden.net/2010/03/02/wavefront-obj-mesh-loader/

struct MeshFace
{
    int pos_index[3];
    int tex_index[3];
    int nor_index[3];
};

Mesh* ObjLoader::loadObj(QString fileName)
{
    QFile file(fileName);

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        qDebug()<<"Erreur ouverture fichier"<<fileName;
        return 0;
    }

    QList<float> verticeList;
    QList<float> textList;
    QList<float> normalList;
    QList<MeshFace> indiceList;

    QList<QList<int> > vertTex;
    QList<QList<int> > duplicate;

    QTextStream in(&file);
    while (!in.atEnd())
    {
        QString line = in.readLine();
        line.replace("\t"," ");
        QStringList list = line.split(" ",QString::SkipEmptyParts);

        if(!list.isEmpty())
        {
            if(list.at(0) == "v")
            {
                verticeList.append(list.at(1).toFloat());
                verticeList.append(list.at(2).toFloat());
                verticeList.append(list.at(3).toFloat());

                QList<int> l;
                l<<-1;
                vertTex.append(l);
                duplicate.append(l);

            }else if(list.at(0) == "vt")
            {
                textList.append(list.at(1).toFloat());
                textList.append(list.at(2).toFloat());

            }else if(list.at(0) == "vn")
            {
                normalList.append(list.at(1).toFloat());
                normalList.append(list.at(2).toFloat());
                normalList.append(list.at(3).toFloat());

            }else if(list.at(0) == "f")
            {
                MeshFace face_index;
                for(int i = 1; i < 4; ++i)
                {
                    QStringList subList = list.at(i).split("/",QString::SkipEmptyParts);

                    if(vertTex.at(subList.at(0).toInt()-1).contains(-1) || vertTex.at(subList.at(0).toInt()-1).contains(subList.at(1).toInt()-1) )
                    {    // cas normal

                        face_index.pos_index[i-1] = subList.at(0).toInt();
                        face_index.tex_index[i-1] = subList.at(1).toInt();
                        face_index.nor_index[i-1] = subList.at(2).toInt();

                        QList<int> l;
                        l.append(subList.at(1).toInt()-1);
                        vertTex.replace(subList.at(0).toInt()-1,l);
                    }else
                    {

                        // cas duplication de vertice
                        if(duplicate.at(subList.at(0).toInt()-1).at(0) == subList.at(1).toInt()-1)
                        {
                            face_index.pos_index[i-1] = duplicate.at(subList.at(0).toInt()-1).at(1)+1;
                            face_index.tex_index[i-1] = subList.at(1).toInt();
                            face_index.nor_index[i-1] = subList.at(2).toInt();;
                        }
                        else
                        {
                            verticeList.append(verticeList.at((subList.at(0).toInt()-1)*3));
                            verticeList.append(verticeList.at((subList.at(0).toInt()-1)*3+1));
                            verticeList.append(verticeList.at((subList.at(0).toInt()-1)*3+2));

                            normalList.append(normalList.at((subList.at(2).toInt()-1)*3));
                            normalList.append(normalList.at((subList.at(2).toInt()-1)*3+1));
                            normalList.append(normalList.at((subList.at(2).toInt()-1)*3+2));

                            face_index.pos_index[i-1] = verticeList.size()/3 ;
                            face_index.tex_index[i-1] = subList.at(1).toInt();
                            face_index.nor_index[i-1] = normalList.size()/3 ;

                            QList<int> l;
                            l.append( subList.at(1).toInt()-1);
                            vertTex.insert(verticeList.size()/3 -1,l);

                            QList<int> l2;
                            l2.append(subList.at(1).toInt()-1);
                            l2.append(verticeList.size()/3 -1);
                            duplicate.insert(subList.at(0).toInt()-1,l2);
                        }



                    }

                }
                indiceList.append(face_index);
            }
        }
    }


    file.close();

    int size = verticeList.size();
    int faceCount = indiceList.size();


    float verticeTab[size];
    float textTab[(size/3)*2];
    float normalTab[size];
    int indiceTab[faceCount*3];

    //vertice tab
    for(int i=0; i<size;i++)
    {
        verticeTab[i]=verticeList.at(i);

    }



    //indice tab
    for(int i=0; i<faceCount;i++)
    {
        int posIndex0 = (indiceList.at(i).pos_index[0])-1;
        int posIndex1 = (indiceList.at(i).pos_index[1])-1;
        int posIndex2 = (indiceList.at(i).pos_index[2])-1;
        indiceTab[i*3]= posIndex0;
        indiceTab[i*3+1]= posIndex1;
        indiceTab[i*3+2]=posIndex2;


    }

     //normal tab
    for (int i=0; i<faceCount; i++)
    {
        int posIndex0 = (indiceList.at(i).pos_index[0])-1;
        int posIndex1 = (indiceList.at(i).pos_index[1])-1;
        int posIndex2 = (indiceList.at(i).pos_index[2])-1;

        normalTab[posIndex0*3]=normalList.at((indiceList.at(i).nor_index[0]-1)*3);
        normalTab[posIndex0*3+1]=normalList.at((indiceList.at(i).nor_index[0]-1)*3+1);
        normalTab[posIndex0*3+2]=normalList.at((indiceList.at(i).nor_index[0]-1)*3+2);

        normalTab[posIndex1*3]=normalList.at((indiceList.at(i).nor_index[1]-1)*3);
        normalTab[posIndex1*3+1]=normalList.at((indiceList.at(i).nor_index[1]-1)*3+1);
        normalTab[posIndex1*3+2]=normalList.at((indiceList.at(i).nor_index[1]-1)*3+2);

        normalTab[posIndex2*3]=normalList.at((indiceList.at(i).nor_index[2]-1)*3);
        normalTab[posIndex2*3+1]=normalList.at((indiceList.at(i).nor_index[2]-1)*3+1);
        normalTab[posIndex2*3+2]=normalList.at((indiceList.at(i).nor_index[2]-1)*3+2);
    }


    //text Coords tab
    for (int i=0; i<faceCount; i++)
    {
        int vertexPos0 = (indiceList.at(i).pos_index[0])-1;
        int vertexPos1 = (indiceList.at(i).pos_index[1])-1;
        int vertexPos2 = (indiceList.at(i).pos_index[2])-1;

        textTab[vertexPos0*2]= textList.at((indiceList.at(i).tex_index[0]-1)*2);
        textTab[vertexPos0*2+1]= textList.at((indiceList.at(i).tex_index[0]-1)*2+1);
        textTab[vertexPos1*2]= textList.at((indiceList.at(i).tex_index[1]-1)*2);
        textTab[vertexPos1*2+1]= textList.at((indiceList.at(i).tex_index[1]-1)*2+1);
        textTab[vertexPos2*2]= textList.at((indiceList.at(i).tex_index[2]-1)*2);
        textTab[vertexPos2*2+1]= textList.at((indiceList.at(i).tex_index[2]-1)*2+1);
    }

    Geometry* geometry = new Geometry(verticeTab,indiceTab,size,faceCount*3);
    geometry->setNormals(normalTab);
    geometry->setTexCoords(textTab);

    Mesh* mesh = new Mesh(geometry,new MaterialBasic(Vector3(0.4f, 0.6f, 0.2f)));

    return mesh;

}
