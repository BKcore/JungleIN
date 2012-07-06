#include "scenebuilder.h"

Scene* SceneBuilder::scene2 = NULL;
Ground* SceneBuilder::ground2 = NULL;
int SceneBuilder::NB_INSTANCE = 1400;

Scene* SceneBuilder::build()
{
    Camera* camera = new Camera();
    camera->setMouse(QCursor::pos().x(), QCursor::pos().y());
    camera->setMouse(QCursor::pos().x(), QCursor::pos().y());
    camera->reset();

    SkyBox* skyBox = new SkyBox(new MaterialSkyBox(new TextureCube("resources/cubemaps/miramar/")));
    skyBox->setPosition(camera->getPosition());

    // SUN
    Texture::resetUnit();
    Texture* sunDiffuse = Texture::newFromNextUnit();
    Texture* sunAlpha = Texture::newFromNextUnit();
    sunDiffuse->load("resources/maps/sun/sun_1k.jpg");
    sunDiffuse->setFilters(Texture::MIPMAP, Texture::MIPMAP);
    sunDiffuse->init();
    sunAlpha->load("resources/maps/sun/sun_1k_alpha.jpg");
    sunAlpha->setFilters(Texture::MIPMAP, Texture::MIPMAP);
    sunAlpha->init();
    MaterialSun* sunMat = new MaterialSun(sunDiffuse, sunAlpha);
    Sun* sun = new Sun(sunMat);


    // GROUND
    Texture::resetUnit();
    // diffuses
    Texture* groundMoss = Texture::newFromNextUnit();
    Texture* groundEarth = Texture::newFromNextUnit();
    Texture* groundShatter = Texture::newFromNextUnit();
    groundMoss->load("resources/maps/ground/moss.jpg");
    groundMoss->setFilters(Texture::MIPMAP, Texture::MIPMAP);
    groundMoss->init();
    groundEarth->load("resources/maps/ground/earth.jpg");
    groundEarth->setFilters(Texture::MIPMAP, Texture::MIPMAP);
    groundEarth->init();
    groundShatter->load("resources/maps/ground/shatter.jpg");
    groundShatter->setFilters(Texture::MIPMAP, Texture::MIPMAP);
    groundShatter->init();
    // normals
    Texture* groundNormalMoss = Texture::newFromNextUnit();
    Texture* groundNormalEarth = Texture::newFromNextUnit();
    Texture* groundNormalShatter = Texture::newFromNextUnit();
    groundNormalMoss->load("resources/maps/ground/moss_normal.png");
    groundNormalMoss->setFilters(Texture::MIPMAP, Texture::MIPMAP);
    groundNormalMoss->init();
    groundNormalEarth->load("resources/maps/ground/earth_normal.png");
    groundNormalEarth->setFilters(Texture::MIPMAP, Texture::MIPMAP);
    groundNormalEarth->init();
    groundNormalShatter->load("resources/maps/ground/shatter_normal.png");
    groundNormalShatter->setFilters(Texture::MIPMAP, Texture::MIPMAP);
    groundNormalShatter->init();
    // init
    MaterialGround* groundMat = new MaterialGround(groundMoss, groundEarth, groundShatter, groundNormalMoss, groundNormalEarth, groundNormalShatter);
    Ground* ground = new Ground("resources/heightmaps/heightmap.png", groundMat);

    // ROCK 1
    Texture::resetUnit();
    Texture* rock1Diffuse = Texture::newFromNextUnit();
    Texture* rock1Alpha = Texture::newFromNextUnit();
    Mesh* rock1 = ObjLoader::loadObj("resources/meshes/rock1/rock1.obj");
    rock1Diffuse->load("resources/maps/rock1/rock1_1k.jpg");
    rock1Diffuse->setFilters(Texture::MIPMAP, Texture::MIPMAP);
    rock1Diffuse->init();
    rock1Alpha->load("resources/maps/noalpha.jpg");
    rock1Alpha->setFilters(Texture::NEAREST, Texture::NEAREST);
    rock1Alpha->init();
    ((MaterialBasic*)(rock1->getMaterial()))->setDiffuse(rock1Diffuse);
    ((MaterialBasic*)(rock1->getMaterial()))->setAlpha(rock1Alpha);
    rock1->setPosition(Vector3(-3,0.5,0));
    rock1->setScale(Vector3(0.6,0.6,0.6));
    rock1->setScale(Vector3(0.0,0.0,0.0));
    rock1->setScaleRdn(0.2);
    rock1->setHeightRdn(0.5);
    rock1->setPourcentage(0.2);
    rock1->setInstanceType(Mesh::INSTANCE_ROCK);
    rock1->setRangeScale(0.4);
    createInstances(rock1,ground,NB_INSTANCE * rock1->getPourcentage());


    // PALM TREE
    Texture::resetUnit();
    Texture* palmDiffuse = Texture::newFromNextUnit();
    Texture* palmAlpha = Texture::newFromNextUnit();
    Mesh* palm = ObjLoader::loadObj("resources/meshes/palmtree/palmtree.obj");
    palmDiffuse->load("resources/maps/palmtree/palmtree_1k.jpg");
    palmDiffuse->setFilters(Texture::MIPMAP, Texture::MIPMAP);
    palmDiffuse->init();
    palmAlpha->load("resources/maps/palmtree/palmtree_1k_alpha.jpg");
    palmAlpha->setFilters(Texture::MIPMAP, Texture::MIPMAP);
    palmAlpha->init();
    ((MaterialBasic*)(palm->getMaterial()))->setDiffuse(palmDiffuse);
    ((MaterialBasic*)(palm->getMaterial()))->setAlpha(palmAlpha);
    palm->setPosition(Vector3(0,0,-10));
    palm->setScale(Vector3(2,2,2));
    palm->setScale(Vector3(0,0,0));
    palm->setScaleRdn(0.8);
    palm->setHeightRdn(-2.5);
    palm->setPourcentage(0.07);
    palm->setInstanceType(Mesh::INSTANCE_PALM);
    palm->setRangeScale(0.8);
    createInstances(palm,ground,NB_INSTANCE * palm->getPourcentage());


    // HIGH TREE
    Texture::resetUnit();
    Texture* htreeDiffuse = Texture::newFromNextUnit();
    Texture* htreeAlpha = Texture::newFromNextUnit();
    Mesh* htree = ObjLoader::loadObj("resources/meshes/hightree/hightree.obj");
    htreeDiffuse->load("resources/maps/hightree/hightree_1k.jpg");
    htreeDiffuse->setFilters(Texture::MIPMAP, Texture::MIPMAP);
    htreeDiffuse->init();
    htreeAlpha->load("resources/maps/hightree/hightree_1k_alpha.jpg");
    htreeAlpha->setFilters(Texture::MIPMAP, Texture::MIPMAP);
    htreeAlpha->init();
    ((MaterialBasic*)(htree->getMaterial()))->setDiffuse(htreeDiffuse);
    ((MaterialBasic*)(htree->getMaterial()))->setAlpha(htreeAlpha);
    htree->setPosition(Vector3(-6,2,-16));
    htree->setScale(Vector3(0.6,0.6,0.6));
    htree->setScale(Vector3(0,0,0));
    htree->setScaleRdn(0.3);
    htree->setHeightRdn(-2.0);
    htree->setPourcentage(0.3);
    htree->setInstanceType(Mesh::INSTANCE_HTREE);
    htree->setRangeScale(0.4);
    createInstances(htree,ground,NB_INSTANCE * htree->getPourcentage());


    // BAMBOO PALM
    Texture::resetUnit();
    Texture* btreeDiffuse = Texture::newFromNextUnit();
    Texture* btreeAlpha = Texture::newFromNextUnit();
    Mesh* btree = ObjLoader::loadObj("resources/meshes/bamboopalm/bamboopalm.obj");
    btreeDiffuse->load("resources/maps/bamboopalm/bamboopalm_1k.jpg");
    btreeDiffuse->setFilters(Texture::MIPMAP, Texture::MIPMAP);
    btreeDiffuse->init();
    btreeAlpha->load("resources/maps/bamboopalm/bamboopalm_1k_alpha.jpg");
    btreeAlpha->setFilters(Texture::MIPMAP, Texture::MIPMAP);
    btreeAlpha->init();
    ((MaterialBasic*)(btree->getMaterial()))->setDiffuse(btreeDiffuse);
    ((MaterialBasic*)(btree->getMaterial()))->setAlpha(btreeAlpha);
    btree->setPosition(Vector3(-4,-2,4));
    btree->setScale(Vector3(0.6,0.6,0.6));
    btree->setScale(Vector3(0,0,0));
    btree->setScaleRdn(0.3);
    btree->setHeightRdn(-2.0);
    btree->setPourcentage(0.15);
    btree->setInstanceType(Mesh::INSTANCE_BTREE);
    btree->setRangeScale(1.0);
    createInstances(btree,ground,NB_INSTANCE * btree->getPourcentage());


    // GROUND PALM
    Texture::resetUnit();
    Texture* gpalmDiffuse = Texture::newFromNextUnit();
    Texture* gpalmAlpha = Texture::newFromNextUnit();
    Mesh* gpalm = ObjLoader::loadObj("resources/meshes/groundpalm/groundpalm.obj");
    gpalmDiffuse->load("resources/maps/groundpalm/groundpalm_1k.jpg");
    gpalmDiffuse->setFilters(Texture::MIPMAP, Texture::MIPMAP);
    gpalmDiffuse->init();
    gpalmAlpha->load("resources/maps/groundpalm/groundpalm_1k_alpha.jpg");
    gpalmAlpha->setFilters(Texture::MIPMAP, Texture::MIPMAP);
    gpalmAlpha->init();
    ((MaterialBasic*)(gpalm->getMaterial()))->setDiffuse(gpalmDiffuse);
    ((MaterialBasic*)(gpalm->getMaterial()))->setAlpha(gpalmAlpha);
    gpalm->setPosition(Vector3(-3,-1,0));
    gpalm->setScaleRdn(0.9);
    gpalm->setScale(Vector3(0,0,0));
    gpalm->setHeightRdn(-1.0);
    gpalm->setPourcentage(0.14);
    gpalm->setInstanceType(Mesh::INSTANCE_GPALM);
    gpalm->setRangeScale(0.4);
    createInstances(gpalm,ground,NB_INSTANCE * gpalm->getPourcentage());


    // SMALL PLANT 1
    /*Texture::resetUnit();
    Texture* splant1Diffuse = Texture::newFromNextUnit();
    Texture* splant1Alpha = Texture::newFromNextUnit();
    Mesh* splant1 = ObjLoader::loadObj("resources/meshes/smallplant1/smallplant1.obj");
    splant1Diffuse->load("resources/maps/smallplant1/smallplant1.jpg");
    splant1Diffuse->setFilters(Texture::MIPMAP, Texture::MIPMAP);
    splant1Diffuse->init();
    splant1Alpha->load("resources/maps/smallplant1/smallplant1_alpha.jpg");
    splant1Alpha->setFilters(Texture::MIPMAP, Texture::MIPMAP);
    splant1Alpha->init();
    ((MaterialBasic*)(splant1->getMaterial()))->setDiffuse(splant1Diffuse);
    ((MaterialBasic*)(splant1->getMaterial()))->setAlpha(splant1Alpha);
    splant1->setPosition(Vector3(2,4,-8));
    splant1->setScale(Vector3(0.6,0.6,0.6));
    splant1->castsShadows(true);*/

    // BUSH 1
    Texture::resetUnit();
    Texture* bush1Diffuse = Texture::newFromNextUnit();
    Texture* bush1Alpha = Texture::newFromNextUnit();
    Mesh* bush1 = ObjLoader::loadObj("resources/meshes/bush1/bush1.obj");
    bush1Diffuse->load("resources/maps/bush1/bush1_1k.jpg");
    bush1Diffuse->setFilters(Texture::MIPMAP, Texture::MIPMAP);
    bush1Diffuse->init();
    bush1Alpha->load("resources/maps/bush1/bush1_1k_alpha.jpg");
    bush1Alpha->setFilters(Texture::MIPMAP, Texture::MIPMAP);
    bush1Alpha->init();
    ((MaterialBasic*)(bush1->getMaterial()))->setDiffuse(bush1Diffuse);
    ((MaterialBasic*)(bush1->getMaterial()))->setAlpha(bush1Alpha);
    bush1->setPosition(Vector3(-3,0,0));
    bush1->setScale(Vector3(0.6,0.6,0.6));
    bush1->setScale(Vector3(0,0,0));
    bush1->setScaleRdn(0.3);
    bush1->setHeightRdn(0.0);
    bush1->setPourcentage(0.14);
    bush1->setInstanceType(Mesh::INSTANCE_BUSH);
    bush1->setRangeScale(0.4);
    createInstances(bush1,ground,NB_INSTANCE * bush1->getPourcentage());


    Scene* scene = new Scene();
    scene->addCamera(camera);
    scene->setCurrentCamera(camera);
    scene->setSky(skyBox);
    scene->setSun(sun);
    scene->setGround(ground);

    scene->addMesh(rock1);
    scene->addMesh(palm);
    scene->addMesh(gpalm);
    //scene->addMesh(splant1);
    scene->addMesh(htree);
    scene->addMesh(btree);
    scene->addMesh(bush1);


    scene2 = scene;
    ground2 = ground;
    return scene;
}

void SceneBuilder::createInstances(Mesh* mesh, Ground* ground, int nbInstance)
{
    for(int i = 0; i < nbInstance; ++i)
    {
        double scale = Utils::random(mesh->getScaleRdn(), mesh->getScaleRdn() + mesh->getRangeScale());
        Instance* instance = mesh->newInstance();
        if (mesh->getInstanceType() == Mesh::INSTANCE_ROCK)
            instance->setPosition(ground->randomMapPos(mesh->getHeightRdn(), true));
        else
            instance->setPosition(ground->randomMapPos(mesh->getHeightRdn(), false));
        instance->setRotation(Vector3(0,Utils::random(0.0, 360.0),0));
        instance->setScale(Vector3(scale, scale, scale));
    }

}

void SceneBuilder::reloadGo(int density, int spacing)
{

    ground2->removeRockPos();

    Ground::MAP_MAX = spacing;
    Ground::MAP_MIN = -spacing;
    scene2->setRenderAble(false);

    foreach (Mesh* mesh, scene2->getMeshes())
    {
        if (mesh->getInstanceType() != Mesh::INSTANCE_NONE) {
            mesh->clearInstances();
            createInstances(mesh, ground2, density * mesh->getPourcentage());
        }
    }

    NB_INSTANCE = density;
    scene2->setRenderAble(true);
}

